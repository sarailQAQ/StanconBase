/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by WangYunlai on 2023/06/28.
//

#include <sstream>
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"
#include "common/date.h"

const char *ATTR_TYPE_NAME[] = {"undefined", "nulls","chars", "ints", "dates", "floats", "booleans","texts"};

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= TEXTS) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/) { set_string(s, len); }

void Value::set_data(char *data, int length)
{
  switch (attr_type_) {
    case NULLS: {
      set_null();
    }break;
    case TEXTS:
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_               = length;
    } break;
    case DATES: {
      num_value_.int_value_ = *(int *)data;
      //      string_to_date(data, num_value_.int_value_);
      length_ = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_                 = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_                = length;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  attr_type_            = INTS;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_              = FLOATS;
  num_value_.float_value_ = val;
  length_                 = sizeof(val);
}
void Value::set_date(int val)
{
  attr_type_            = DATES;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}
void Value::set_boolean(bool val)
{
  attr_type_             = BOOLEANS;
  num_value_.bool_value_ = val;
  length_                = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_null(){
  attr_type_ = NULLS;
  length_ = 0;
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case NULLS:{
      set_null();
    } break;
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case DATES: {
      int date = 0;
      RC  rc   = string_to_date(value.get_string().c_str(), date);
      if (rc != RC::SUCCESS) {
        ASSERT(false, "date convert error");
        return;
      }
      set_date(date);
    }
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case TEXTS: {
      set_text(value.get_string().c_str());
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

void Value::set_text(const char* s) {
  attr_type_ = TEXTS;
  // 截断输入字符串为不超过 4096 个字符
  if (strlen(s) > 65535) {
    str_value_.assign(s, 65535);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

const char *Value::data() const
{
  switch (attr_type_) {
    case CHARS:
    case TEXTS:{
      return str_value_.c_str();
    }break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case NULLS: {
      os << "NULL";
    }break;
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case DATES: {
      os << date_to_string(num_value_.int_value_);
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS:
    case TEXTS:{
      os << str_value_;
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

int Value::compare(const Value &other) const
{
  // NULL 和任何值比较都是 false,is null 比较符则另外处理
  if(attr_type_ == AttrType::NULLS){
    // 如果都是 null，返回0，否则，null将视为最小值
    return other.attr_type_ == NULLS ? 0 : -1;
  }
  if (other.attr_type_ == AttrType::NULLS) return 1;

  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case DATES:  // 日期和整形本质都是比较数字
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      }
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == DATES && other.attr_type_ == CHARS) {
    int res = 0;
    RC  rc  = string_to_date(other.get_string().c_str(), res);
    if (rc == RC::SUCCESS) {
      return common::compare_int((void *)&this->num_value_.int_value_, (void *)&res);
    }
    LOG_WARN("date convert error: %s", other.get_string().c_str());
    return -1;
  } else if (this->attr_type_ == CHARS && other.attr_type_ == DATES) {
    int res = 0;
    RC  rc  = string_to_date(this->get_string().c_str(), res);
    if (rc == RC::SUCCESS) {
      return common::compare_int((void *)&res, (void *)&other.num_value_.int_value_);
    }
    LOG_WARN("date convert error: %s", other.get_string().c_str());
    return -1;
  } else if (this->attr_type_ == INTS && other.attr_type_ == DATES) {
    return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
  } else if (this->attr_type_ == DATES && other.attr_type_ == INTS) {
    return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  }

  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}
// like函数实现
bool Value::like(const Value &other) const
{
  // LIKE情况只会出现在字符串匹配中
  if (this->attr_type_ == CHARS && other.attr_type_ == CHARS) {
    const std::string pattern   = other.get_string();
    const std::string text      = this->get_string();
    size_t pattern_p = 0;  // 模式字符串索引
    size_t text_p = 0;  // 文本字符串索引
    size_t match_index = std::string::npos; //上一个匹配的位置
    size_t wildcard_index = std::string::npos; //上一个%的位置

    while (text_p < text.length())
    {
      //当前为字符匹配或者为通配符'_'
      if (pattern_p < pattern.length() && (pattern[pattern_p] == text[text_p] || pattern[pattern_p] == '_'))
      {
        pattern_p++;
        text_p++;
      }
      //当前字符为通配符'%'
      else if(pattern_p < pattern.length() && pattern[pattern_p] == '%')
      {
        wildcard_index = pattern_p;
        match_index = text_p;
        pattern_p++;
      }
      //当前字符不匹配，之前存在通配符'%'
      else if (wildcard_index != std::string::npos)
      {
        pattern_p = wildcard_index + 1;
        match_index++;
        text_p = match_index;
      }
      else
      {
        return false;
      }
    }
    // 检查是否匹配完整的模式字符串
    while (pattern_p < pattern.length() && pattern[pattern_p] == '%') {pattern_p++;}
    return pattern_p == pattern.length() && text_p == text.length();
  }
  LOG_WARN(" LIKE unsupported type: %d %d", this->attr_type_,other.attr_type_);
  return false;
}

// 字符串转double，如果字符串前缀是个double 也允许转，不能转则默认返回0
static double str_to_double(const std::string &str)
{
  std::size_t pos       = 0;
  bool        has_point = false;
  while (pos < str.length() && (std::isdigit(str[pos]) || str[pos] == '.')) {
    if (has_point && str[pos] == '.') {
      break;
    }
    if (!has_point && str[pos] == '.') {
      has_point = true;
    }
    pos++;
  }
  if(pos == 0){
    return 0;
  }

  std::string numberStr = str.substr(0, pos);
  try {
    double number = std::stod(numberStr);
    return number;
  } catch (const std::exception &e) {
    return 0;
  }
  return 0.0;
}

int Value::get_int() const
{
  switch (attr_type_) {
    case TEXTS:
    case CHARS: {
      try {
        return (int)str_to_double(str_value_);
//        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        // 非合法数字转换成0
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case DATES: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case TEXTS:
    case CHARS: {
      try {
        return (double)str_to_double(str_value_);
//        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case DATES: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case TEXTS:
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case DATES: {
      return num_value_.int_value_ >= 19000101 && num_value_.int_value_ <= 99991231;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

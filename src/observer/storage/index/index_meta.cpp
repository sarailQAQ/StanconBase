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
// Created by Wangyunlai.wyl on 2021/5/18.
//

#include "storage/index/index_meta.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "json/json.h"

const static Json::StaticString FIELD_NAME("name");
const static Json::StaticString FIELD_FIELD_NAME("field_names");

RC IndexMeta::init(const char *name, const std::vector<const FieldMeta *>& field_metas)
{
  if (common::is_blank(name)) {
    LOG_ERROR("Failed to init index, name is empty.");
    return RC::INVALID_ARGUMENT;
  }

  name_ = name;
  fields_.clear();
  fields_str = "";
  for (const auto& field_meta : field_metas) {
    fields_.emplace_back(field_meta->name());
    if (!fields_str.empty()) fields_str += ","; // 多个列名用 , 分割
    fields_str += field_meta->name();
  }
  return RC::SUCCESS;
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value[FIELD_NAME] = name_;
  Json::Value json_arr(Json::arrayValue);
  for (auto& field : fields_) json_arr.append(field);
  json_value[FIELD_FIELD_NAME] = json_arr;
}

RC IndexMeta::from_json(const TableMeta &table, const Json::Value &json_value, IndexMeta &index)
{
  const Json::Value &name_value = json_value[FIELD_NAME];
  const Json::Value &fields_value = json_value[FIELD_FIELD_NAME];
  if (!name_value.isString()) {
    LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  if (!fields_value.isArray()) {
    LOG_ERROR("Field name of index [%s] is not a string. json value=%s",
        name_value.asCString(),
        fields_value.toStyledString().c_str());
    return RC::INTERNAL;
  }

  std::vector<const FieldMeta *> field_metas;
  for (auto& val : fields_value) {
    if (!val.isString()) {
      LOG_ERROR("Index name is not a string. json value=%s", name_value.toStyledString().c_str());
      return RC::INTERNAL;
    }
    const FieldMeta *field_meta = table.field(val.asString().c_str());
    if (nullptr == field_meta) {
      LOG_ERROR("Deserialize index [%s]: no such field: %s", name_value.asCString(), val.asCString());
      return RC::SCHEMA_FIELD_MISSING;
    }

    field_metas.push_back(field_meta);
  }


  return index.init(name_value.asCString(), field_metas);
}

const char *IndexMeta::name() const
{
  return name_.c_str();
}

const char *IndexMeta::field() const
{
  return fields_str.c_str();
}

void IndexMeta::desc(std::ostream &os) const
{
  os << "index name=" << name_ << ", field=" << fields_str;
}
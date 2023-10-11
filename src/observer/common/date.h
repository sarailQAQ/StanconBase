//
// Created by weizhi on 23-9-26.
//

#include "string"
#include "rc.h"
#include "sql/parser/parse_defs.h"
#include "sstream"

// 判断是否为闰年
inline bool is_leap_year(int year) { return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; }

// 字符串转日期
inline RC string_to_date(const char *str, int32_t &date)
{
  int year = 0, month = 0, day = 0;
  int ret = sscanf(str, "%d-%d-%d", &year, &month, &day);
  if (ret != 3) {
    return RC::INVALID_ARGUMENT;
  }
  if (year < 1900 || year > 9999 || month < 1 || month > 12 || day < 1) {
    return RC::INVALID_ARGUMENT;
  }
  int  leap_days[]    = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int  un_leap_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  bool over_max_day   = is_leap_year(year) ? (day > leap_days[month - 1]) : (day > un_leap_days[month - 1]);
  if (over_max_day) {
    return RC::INVALID_ARGUMENT;
  }

  date = year * 10000 + month * 100 + day;
  return RC::SUCCESS;
}

// 日期转字符串
inline std::string date_to_string(int32_t date)
{
  //  20230101
  std::stringstream ss;
  ss << date / 10000 << "-" << date % 10000 / 100 << "-" << date % 100;
  return ss.str();
}
// Copyright (c) 2013 Tencent Inc.
// Author: Fucen Zeng (brucetzeng@tencent.com)

#include "demo_memory_mysql.h"

#include "thirdparty/glog/logging.h"
#include "mysql/mysql.h"

namespace cocktail {
namespace common {

DemoMemoryMysql::DemoMemoryMysql() {
  mysql_ = mysql_init(NULL);
  if (!mysql_real_connect(mysql_, NULL , NULL , NULL , NULL, 0, NULL, 0)) {
    LOG(ERROR) << "failed to connect to mysql.";
  }
}

DemoMemoryMysql::~DemoMemoryMysql() {
  mysql_close(mysql_);
}

bool DemoMemoryMysql::Query(const std::string& query_str, std::string* error) {
  int ret = mysql_query(mysql_, query_str.c_str());
  if (ret)
    *error = mysql_error(mysql_);
  return ret == 0;
}

bool DemoMemoryMysql::QueryData(const std::string& query_str,
                                QueryResult* query_res,
                                std::string* error) {
  if (!Query(query_str, error)) {
    LOG(ERROR) << "failed to execute: " << query_str;
    return false;
  }

  MYSQL_RES* select_result = mysql_store_result(mysql_);
  MYSQL_ROW row;
  MYSQL_FIELD *field;
  int size = mysql_num_fields(select_result);

  std::vector<std::string> column_name;
  for (int i = 0; i < size; ++i) {
    field = mysql_fetch_field_direct(select_result, i);
    column_name.push_back(field->name);
  }

  // Store data.
  query_res->clear();
  while ((row = mysql_fetch_row(select_result)) != NULL) {
    std::map<std::string, std::string> row_data;
    for (int i = 0; i < size; ++i) {
      row_data[column_name[i]] = row[i];
    }
    query_res->push_back(row_data);
  }

  mysql_free_result(select_result);
  return true;
}

}  // namespace common
}  // namespace cocktail


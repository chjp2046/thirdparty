// Copyright (c) 2013 Tencent Inc.
// Author: Fucen Zeng (brucetzeng@tencent.com)

#ifndef COCKTAIL_COMMON_DEMO_MEMORY_MYSQL_H_
#define COCKTAIL_COMMON_DEMO_MEMORY_MYSQL_H_

#include <map>
#include <string>
#include <vector>

struct st_mysql;
typedef struct st_mysql MYSQL;

namespace cocktail {
namespace common {

class DemoMemoryMysql {
 public:
  typedef std::vector<std::map<std::string, std::string> > QueryResult;

  DemoMemoryMysql();
  virtual ~DemoMemoryMysql();

  bool Query(const std::string& query_str, std::string* error);
  bool QueryData(const std::string& query_str, QueryResult* query_res,
                 std::string* error);

 private:
  MYSQL* mysql_;
};

}  // namespace common
}  // namespace cocktail

#endif  // COCKTAIL_COMMON_DEMO_MEMORY_MYSQL_H_


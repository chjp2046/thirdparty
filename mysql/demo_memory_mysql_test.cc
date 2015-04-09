// Copyright (c) 2013 Tencent Inc.
// Author: Fucen Zeng (brucetzeng@tencent.com)

#include "demo_memory_mysql.h"

#include "thirdparty/glog/logging.h"
#include "thirdparty/gtest/gtest.h"

namespace cocktail {
namespace common {

class DemoMemoryMysqlTest : public testing::Test {
 protected:
  virtual void SetUp() {
    std::string error;
    EXPECT_TRUE(memory_mysql_.Query("create database if not exists mydb",
                                    &error));
    EXPECT_TRUE(memory_mysql_.Query("use mydb", &error));
  }

  virtual void TearDown() {
    std::string error;
    EXPECT_TRUE(memory_mysql_.Query("drop database mydb", &error));
  }

  DemoMemoryMysql memory_mysql_;
};

TEST_F(DemoMemoryMysqlTest, Query) {
  std::string error;
  EXPECT_TRUE(memory_mysql_.Query(
      "create table if not exists mytable (id int not null, col int not null)",
      &error));
  EXPECT_TRUE(memory_mysql_.Query(
      "insert into mytable (id, col) values (1,100)",
      &error));
}

TEST_F(DemoMemoryMysqlTest, QueryData) {
  std::string error;
  EXPECT_TRUE(memory_mysql_.Query(
      "create table if not exists mytable (id int not null, col int not null)",
      &error));
  EXPECT_TRUE(memory_mysql_.Query(
      "insert into mytable (id, col) values (1, 100)", &error));

  DemoMemoryMysql::QueryResult query_res;
  EXPECT_TRUE(memory_mysql_.QueryData("select * from mytable where id = 1",
                                      &query_res, &error));
  EXPECT_EQ("100", query_res[0]["col"]);
}

}  // namespace common
}  // namespace cocktail


// Copyright (c) 2013 Tencent Inc.
// Author: Fucen Zeng (brucetzeng@tencent.com)

#include "common/base/module.h"
#include "thirdparty/glog/logging.h"

#include "mysql.h"

// To use this module, you need to link this module and put this module before
// libmysqlclient in your BLADE-BUILD deps. Then call InitAllModules in your
// main().
//
// If you are writing a unit test using gtest, just link this module. Because
// our gtest have already called InitAllModules().

static char *server_options[] = { (char *)"mock_mysql",
                                  (char *)"--datadir=./",
                                  (char *)"--skip-innodb",
                                  (char *)"--skip-grant-tables=1",
                                  NULL };
int num_elements = (sizeof(server_options) / sizeof(char *)) - 1;

DEFINE_MODULE(memory_mysql) {
  if(int ok = mysql_library_init(num_elements, server_options, NULL)) {
    LOG(ERROR) << "failed to initialize server. code: " << ok;
    return false;
  }
  return true;
}

DEFINE_MODULE_DTOR(memory_mysql) {
  mysql_library_end();
}

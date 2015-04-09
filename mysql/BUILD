cc_library(name = "mysqlclient", prebuilt = 1, deps = [ '#z', '#dl' ])
cc_library(name = "mysqlclient_r", prebuilt = 1, deps = [ '#z', '#dl', '#rt', '#pthread' ])
cc_library(name = "strings", prebuilt = 1)
cc_library(name = "mystrings", deps = [ ':strings' ])
cc_library(name = "mysys", prebuilt = 1)
cc_library(name = "vio", prebuilt = 1)
cc_library(name = "mysqld", prebuilt = 1, deps = [ '#z', '#m', '#crypt', '#nsl', '#pthread', '#aio', '#rt' ])

cc_library(
    name = 'memory_mysql',
    srcs = 'memory_mysql.cc',
    deps = [
        ':mysqld',
        '//common/base:module',
        '//thirdparty/glog:glog',
    ],
    link_all_symbols = True,
)

cc_library(
    name = 'demo_memory_mysql',
    srcs = 'demo_memory_mysql.cc',
    deps = [
        ':mysqlclient',
        '//thirdparty/glog:glog',
    ],
)

cc_test(
    name = "demo_memory_mysql_test",
    srcs = 'demo_memory_mysql_test.cc',
    deps = [
        ':memory_mysql',
        ':demo_memory_mysql',
    ],
)

cc_library(
    name = 'zookeeper_mt',
    deps = '//thirdparty/zookeeper-3.4.6/src/c:zookeeper_mt'
)

cc_binary(
    name = 'zoo_children_watch',
    srcs = 'zoo_children_watch.c',
    deps = ':zookeeper_mt'
)

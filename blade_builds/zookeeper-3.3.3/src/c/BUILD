cc_library(
    name = 'zookeeper_generated',
    srcs = [
        'src/recordio.cc',
        'generated/zookeeper.jute.cc',
    ],
    incs = [
        'include',
        'generated'
    ],
    warning = 'no'
)

cc_library(
    name = 'zookeeper_mt',
    srcs = [
        'src/mt_adaptor.cc',
        'src/zk_hashtable.cc',
        'src/zk_log.cc',
        'src/zookeeper.cc',
        'src/hashtable/hashtable_itr.cc',
        'src/hashtable/hashtable.cc',
    ],
    deps = [
        '#pthread',
        '//common/crypto/credential:credential',
        '//thirdparty/gflags:gflags',
        '//thirdparty/glog:glog',
        ':zookeeper_generated',
    ],
    incs = [
        'include',
        'generated'
    ],
    defs = [
        'THREADED',
        '_GNU_SOURCE'
    ],
    warning = 'no'
)

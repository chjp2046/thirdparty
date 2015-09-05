cc_library(
    name = 'hashtable',
    srcs = [
        'src/hashtable/hashtable_itr.c',
        'src/hashtable/hashtable.c',
    ],
    incs = [
        'include',
        'generated'
    ],
    defs = [
        'HAVE_CONFIG_H',
        '_GNU_SOURCE'
    ],
    warning = 'no'
)

cc_library(
    name = 'zookeeper_mt',
    srcs = [
		'src/zookeeper.c',
		'src/recordio.c',
		'generated/zookeeper.jute.c',
		'src/zk_log.c',
		'src/zk_hashtable.c',
        'src/mt_adaptor.c'
    ],
    deps = [
        '#pthread',
        ':hashtable',
    ],
    incs = [
        'include',
        'generated'
    ],
    defs = [
        'THREADED',
        '_GNU_SOURCE',
        'HAVE_CONFIG_H'
    ],
    warning = 'no'
)

cc_binary(
    name = 'cli_mt',
    srcs = [
        'src/cli.c'
    ],
    deps = [
        ':zookeeper_mt'
    ],
    incs = [
        'include',
        'generated'
    ],
    defs = [
        'THREADED'
    ],
    warning = 'no'
)

cc_binary(
    name = 'load_gen',
    srcs = [
        'src/load_gen.c'
    ],
    deps = [
        ':zookeeper_mt'
    ],
    incs = [
        'include',
        'generated'
    ],
    defs = [
        'THREADED'
    ],
    warning = 'no'
)

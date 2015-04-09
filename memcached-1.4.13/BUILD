cc_binary(
    name = 'memcached',
    srcs = [
        'assoc.c',
        'cache.c',
        'daemon.c',
        'hash.c',
        'items.c',
        'memcached.c',
        'slabs.c',
        'stats.c',
        'thread.c',
        'util.c',
    ],
    deps = [
        '//thirdparty/libevent:event',
        '#pthread',
        '#rt',
    ],
    defs = [
        'HAVE_CONFIG_H',
    ],
    warning='no',
    extra_cppflags = [
         '-std=c99'
    ]
)

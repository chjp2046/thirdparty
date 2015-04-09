cc_library(
    name = 'hiredis',
    srcs = [
        'net.c',
        'hiredis.c',
        'sds.c',
        'async.c'
    ],
    deps = [
    ],
    extra_cppflags = [
        '-std=c99',
        '-O3',
        '-fPIC'
    ],
    warning = 'no'
)


cc_binary(
    name = 'example',
    srcs = [
        'examples/example.c'
    ],
    deps = [
        ':hiredis'
    ]
)

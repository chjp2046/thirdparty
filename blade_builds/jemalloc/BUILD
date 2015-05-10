cc_library(
    name = 'jemalloc',
    deps = '//thirdparty/jemalloc-2.2.5/:jemalloc'
)

cc_test(
    name = 'jemalloc_test',
    srcs = 'jemalloc_test.cpp',
    deps = ':jemalloc'
)

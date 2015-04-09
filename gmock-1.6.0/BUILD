cc_library(
    name = 'gmock',
    srcs = [
        'src/gmock-cardinalities.cc',
        'src/gmock.cc',
        'src/gmock-internal-utils.cc',
        'src/gmock-matchers.cc',
        'src/gmock-spec-builders.cc'
    ],
    incs = 'include',
    deps = '//thirdparty/gtest:gtest'
)

cc_library(
    name = 'gmock_main',
    srcs = [
        'src/gmock_main.cc',
    ],
    incs = 'include',
    deps = ':gmock'
)



cc_library(
    name = 'gmockgtest',
    srcs = [
        'gtest/src/gtest-all.cc',
        'src/gmock-all.cc'
    ],
    deps = [
        '//thirdparty/glog:glog'
    ],
    incs = [
        'include',
        '.',
        'gtest'
    ]
)

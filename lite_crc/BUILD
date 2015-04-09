cc_library(
    name = 'lite_crc',
    srcs = [
        'source/fast_crc.cc'
    ],
    always_optimize = 1
)

cc_test(
    name = 'lite_crc_test',
    srcs = [
        './source/fast_crc_test.cc'
    ],
    deps = [
        ':lite_crc',
        '//thirdparty/glog:glog'
    ]
)

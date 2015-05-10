package(default_visibility = ["//visibility:public"])

cc_library(
    name = 'cgicc',
	hdrs = [":headers"],
    deps = '//thirdparty/cgicc-3.2.15/cgicc:cgicc'
)

filegroup(
    name = "headers",
    srcs = glob([
        "*.h"
    ]),
)
package(default_visibility = ["//visibility:public"])

cc_library(
	name = 'ctemplate',
    deps = ['//thirdparty/ctemplate-0.99/src:ctemplate'],
	hdrs = [":headers"],
)

filegroup(
    name = "headers",
    srcs = glob([
        "*.h"
    ]),
)
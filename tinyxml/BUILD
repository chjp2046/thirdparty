package(default_visibility = ["//visibility:public"])

cc_library(
    name = "tinyxml",
    srcs = [
        "tinyxml.cpp",
        "tinyxmlparser.cpp",
        "tinyxmlerror.cpp",
		"tinystr.cpp"
    ],
	hdrs = [":headers"],
    deps = [
    ]
)


filegroup(
    name = "headers",
    srcs = glob([
        "*.h"
    ]),
)


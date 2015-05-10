cc_library(
    name = "ctemplate",
    srcs = [
        'per_expand_data.cc',
        'template_cache.cc',
        'template_dictionary.cc',
        'template_namelist.cc',
        'template_string.cc',
        'template_annotator.cc',
        'template.cc',
        'template_modifiers.cc',
        'template_pathops.cc',
        'base/arena.cc',
        'htmlparser/htmlparser.cc',
        'htmlparser/jsparser.cc',
        'htmlparser/statemachine.cc'
    ],
	hdrs = [":headers"],
    linkopts = ["-pthread"],
	visibility = ["//thirdparty/ctemplate:__pkg__"],
)

filegroup(
    name = "headers",
    srcs = glob([
        "*.h"
    ]),
)
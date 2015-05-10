cc_library(
    name = 'cgicc',
    srcs = [
        'CgiEnvironment.cpp',
		'CgiInput.cpp',
        'CgiUtils.cpp',
        'Cgicc.cpp',
        'FormEntry.cpp',
        'FormFile.cpp',
        'HTMLAttribute.cpp',
        'HTMLAttributeList.cpp',
        'HTMLDoctype.cpp',
        'HTMLElement.cpp',
        'HTMLElementList.cpp',
        'HTTPContentHeader.cpp',
        'HTTPCookie.cpp',
        'HTTPHTMLHeader.cpp',
        'HTTPHeader.cpp',
        'HTTPPlainHeader.cpp',
        'HTTPRedirectHeader.cpp',
        'HTTPResponseHeader.cpp',
        'HTTPStatusHeader.cpp',
        'MStreamable.cpp',
        'HTTPXHTMLHeader.cpp',
        'XHTMLDoctype.cpp',
        'XMLPI.cpp'
    ],
	hdrs = [":headers"],
	visibility = ["//thirdparty/cgicc:__pkg__"],
)

filegroup(
    name = "headers",
    srcs = glob([
        "*.h"
    ]),
)

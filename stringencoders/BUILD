cc_library(
    name = 'stringencoders',
    deps = [
        '//thirdparty/stringencoders-v3.10.3/src:stringencoders',
        ':base64_url_safe_rfc'
    ]
)

cc_library(
    name = 'base64_url_safe_rfc',
    srcs = [
        'modp_b64r.c',
    ],
    deps = [
        '//thirdparty/stringencoders-v3.10.3/src:stringencoders',
    ],
    warning = 'no'
)


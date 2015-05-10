cc_library(
        name = "qrencode",
        srcs = [
                    'qrencode.c',
                    'qrinput.c',
                    'bitstream.c',
                    'qrspec.c',
                    'rscode.c',
                    'split.c',
                    'mask.c',
                    'mqrspec.c',
                    'mmask.c'
                ],
        deps = [
                    "//thirdparty/zlib:zlib",
                    "#m"
                ],
        incs = [
                ],
        extra_cppflags = [
                     '-DHAVE_CONFIG_H',
                     '-fPIC',
                     '-DPIC'
                ],
        warning = 'no'
)

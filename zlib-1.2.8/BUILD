cc_library(
        name = "zlib",
        srcs = [
                    'adler32.c',
                    'crc32.c',
                    'deflate.c',
                    'infback.c',
                    'inffast.c',
                    'inflate.c',
                    'inftrees.c',
                    'trees.c',
                    'zutil.c',
                    'compress.c',
                    'uncompr.c',
                    'gzclose.c',
                    'gzlib.c',
                    'gzread.c',
                    'gzwrite.c'
                ],
        deps = [
                ],
        extra_cppflags = [
                    '-D_LARGEFILE64_SOURCE=1',
                     '-DHAVE_HIDDEN',
                     '-O3'
                ],
        warning = 'no'
)

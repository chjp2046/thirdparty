cc_library(
        name = "libpng15",
        srcs = [
                    'png.c',
                    'pngerror.c',
                    'pngget.c',
                    'pngmem.c',
                    'pngpread.c',
                    'pngread.c',
                    'pngrio.c',
                    'pngrtran.c',
                    'pngrutil.c',
                    'pngset.c',
                    'pngtrans.c',
                    'pngwio.c',
                    'pngwrite.c',
                    'pngwtran.c',
                    'pngwutil.c',
                ],
        deps = [
                    "//thirdparty/zlib-1.2.8:zlib"
                ],
        extra_cppflags = [
                     '-DPNG_CONFIGURE_LIBPNG',
                     '-DHAVE_CONFIG_H',
                     '-fPIC',
                     '-DPIC'
                ],
        warning = 'no'
)

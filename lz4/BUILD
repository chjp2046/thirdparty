cc_library(
    name = "lz4",
    srcs = [
        "lz4.c",
        "lz4hc.c"
    ],
    deps = [
    ],
	extra_cppflags = [
		'-O3',
		'-std=c99',
		'-Wall',
		'-Wextra',
		'-Wundef',
		'-Wshadow',
		'-Wcast-align',
		'-Wstrict-prototypes',
		'-DLZ4_VERSION=\"r124\"'
	],
	# -O3 -std=c99 -Wall -Wextra -Wundef -Wshadow -Wcast-align -Wstrict-prototypes -DLZ4_VERSION=\"r124\"
)
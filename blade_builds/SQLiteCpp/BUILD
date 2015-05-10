cc_library(
    name = "sqlite_cpp",
    srcs = [
        'src/Column.cpp',
		'src/Database.cpp',
		'src/Statement.cpp',
		'src/Transaction.cpp',
		'sqlite3/sqlite3.c'
    ],
    deps = [
		"//thirdparty/zlib:zlib",
		"#m"
    ],
    incs = [
		'include',
		'sqlite3'
    ],
    extra_cppflags = [
         '-DSQLITE_ENABLE_COLUMN_METADATA'
    ],
    warning = 'no'
)
#./configure --prefix=/***/glog --enable-static CPPFLAGS="-fPIC -DPIC -I/***/gflags/include" LDFLAGS="-L/***/gflags/lib"

cc_library(
    name = "glog",
    srcs = [
        "demangle.cc",
        "logging.cc",
        "raw_logging.cc",
        "signalhandler.cc",
        "symbolize.cc",
        "utilities.cc",
        "vlog_is_on.cc",
    ],
    incs = '.',
    deps = [
        '#pthread',
        '//thirdparty/gflags:gflags'
    ],
    warning = 'no'
)

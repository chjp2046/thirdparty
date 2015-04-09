cc_library(
    name = "test",
    srcs = [
        "binaries.cc",
        "cmdline.cc",
        "core.cc",
        "framework.cc",
        "is_local.cc",
        "killpid.cc",
        "libtool.cc",
        "memcached.cc",
        "port.cc",
        "runner.cc",
        "server.cc",
        "server_container.cc",
        "signal.cc",
        "socket.cc",
        "strerror.cc",
        "test.cc",
        "unittest.cc",
    ],
    defs = [
        'LIBTEST_TEMP=\\"tmp_chroot\\"',
        "GEARMAND_BLOBSLAP_WORKER=0",
    ]
)

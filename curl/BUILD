package(default_visibility = ["//visibility:public"])

cc_library(
    name = 'curl',
    deps = [
        "//thirdparty/curl-7.38.0/lib:curl"
    ],
	hdrs = [":headers"]
)


cc_binary(
    name = 'https',
    srcs = 'https.c',
    deps = ':curl'
)

filegroup(
    name = "headers",
    srcs = glob([
        "*.h"
    ]),
)



#./configure --enable-http --disable-ftp --disable-file --disable-ldap --disable-ldaps --disable-rtsp --enable-        proxy --disable-dict --disable-telnet --disable-tftp --enable-pop3 --enable-imap --enable-smtp --disable-gopher --    disable-manual --disable-libcurl-option --enable-ipv6 --enable-verbose --disable-sspi --enable-crypto-auth --disable- ntlm-wb --disable-tls-srp --enable-cookies --disable-soname-bump --with-ssl=/usr/local/cftlib/openssl --without-      gnutls --without-polarssl --without-cyassl --without-nss --without-axtls --without-ca-bundle --without-libssh2 --     without-librtmp --without-libidn --without-nghttp2


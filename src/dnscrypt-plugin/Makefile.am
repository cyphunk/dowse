ACLOCAL_AMFLAGS = -I m4

pkglib_LTLIBRARIES = dnscrypt_dowse.la

dnscrypt_dowse_la_LIBTOOLFLAGS = --tag=disable-static

dnscrypt_dowse_la_SOURCES = dnscrypt-dowse.c domainlist.c hashmap.c

dnscrypt_dowse_la_LIBADD = @LDNS_LIBS@ -lhiredis -ljemalloc

dnscrypt_dowse_la_CFLAGS = -Os -Wall -I../dnscrypt-proxy/src/include -I..

dnscrypt_dowse_la_LDFLAGS = $(AM_LDFLAGS) \
-avoid-version \
-export-dynamic \
-module \
-no-undefined

dnscrypt_dowse_la_CPPFLAGS = $(LTDLINCL) -I../../include

SUBDIRS = .

BINDLIBDIR = @BINDDIR@/lib

AM_CPPFLAGS = $(ATF_CFLAGS) -DUNIT_TEST -I$(top_srcdir)/includes
AM_CPPFLAGS += -I@BINDDIR@/include -I$(top_srcdir)
AM_CPPFLAGS += -DLOCALSTATEDIR='"."'
AM_CPPFLAGS += -DCLIENT_PATH='"."'

EXTRA_DIST = Atffile duid0_test.txt duid1_test.txt duid2_test.txt duid3_test.txt

# for autotools debugging only
info:
	@echo "ATF_CFLAGS=$(ATF_CFLAGS)"
	@echo "ATF_LDFLAGS=$(ATF_LDFLAGS)"
	@echo "ATF_LIBS=$(ATF_LIBS)"

DHCPSRC = ../clparse.c ../dhc6.c ../dhclient.c

DHCPLIBS = $(top_builddir)/common/libdhcp.a $(top_builddir)/omapip/libomapi.a    \
          $(top_builddir)/dhcpctl/libdhcpctl.a $(BINDLIBDIR)/libirs.a \
	  $(BINDLIBDIR)/libdns.a $(BINDLIBDIR)/libisccfg.a \
	  $(BINDLIBDIR)/libisc.a

ATF_TESTS =
if HAVE_ATF

ATF_TESTS += duid_unittests 

duid_unittests_SOURCES = $(DHCPSRC) 
duid_unittests_SOURCES += duid_unittest.c

duid_unittests_LDADD = $(ATF_LDFLAGS)
duid_unittests_LDADD += $(DHCPLIBS)

check: $(ATF_TESTS)
	-cp -n $(top_srcdir)/client/tests/Atffile Atffile
	-cp -n $(top_srcdir)/client/tests/duid0_test.txt duid0_test.txt
	-cp -n $(top_srcdir)/client/tests/duid1_test.txt duid1_test.txt
	-cp -n $(top_srcdir)/client/tests/duid2_test.txt duid2_test.txt
	-cp -n $(top_srcdir)/client/tests/duid3_test.txt duid3_test.txt
	sh ${top_builddir}/tests/unittest.sh

distclean-local:
	@if test $(top_srcdir) != ${top_builddir}; then \
		rm -f Atffile duid0_test.txt duid1_test.txt; \
		rm -f duid2_test.txt duid3_test.txt; \
	fi

endif

check_PROGRAMS = $(ATF_TESTS)

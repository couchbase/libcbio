#
#     Copyright 2012 Couchbase, Inc.
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.
#

ACLOCAL_AMFLAGS = -I m4 --force
lib_LTLIBRARIES = libcbio.la

pkginclude_HEADERS = \
                     include/libcbio/cbio.h \
                     include/libcbio/types.h \
                     include/libcbio/visibility.h

libcbio_la_CPPFLAGS = $(AM_CPPFLAGS) -DLIBCBIO_INTERNAL=1
libcbio_la_SOURCES = src/document.c src/error.c src/instance.c src/internal.h
libcbio_la_LDFLAGS = $(AM_LDFLAGS) -lcouchstore $(AM_PROFILE_SOLDFLAGS) \
                     -version-info $(LIBCBIO_API_CURRENT):$(LIBCBIO_API_REVISION):$(LIBCBIO_API_AGE) \
                     -no-undefined

check_PROGRAMS =

if HAVE_GOOGLETEST
check_PROGRAMS += tests/cbio_unit_tests
endif

TESTS=${check_PROGRAMS}

tests_cbio_unit_tests_SOURCES = tests/cbio_unit_tests.cc \
                                tests/document_unit_tests.cc \
                                tests/strerror_unit_tests.cc \
                                tests/instance_unit_tests.cc
tests_cbio_unit_tests_DEPENDENCIES = libcbio.la
tests_cbio_unit_tests_LDADD = -lgtest libcbio.la

LINTFLAGS=-Iinclude -b -c -errchk=%all \
          -erroff=E_INCL_NUSD,E_CAST_INT_TO_SMALL_INT,E_PTRDIFF_OVERFLOW  \
          -errtags=yes -errhdr=%user \
          -errsecurity=extended -fd -Ncheck=%all -Nlevel=4 -n -Xc99=none
lint:
	$(LINT.c) $(libcbio_la_SOURCES)

VALGRIND=valgrind
VALGRIND_OPTIONS=--tool=Memcheck --num-callers=50 \
                 --error-limit=yes --track-origins=yes --malloc-fill=55 \
                 --free-fill=aa --dsymutil=yes -q

VALGRIND_TEST=tests/.libs/cbio_unit_tests

valgrind: ${check_PROGRAMS}
	@for f in $(VALGRIND_TEST); \
        do \
           LD_LIBRARY_PATH=`pwd`/.libs \
           DYLD_LIBRARY_PATH=`pwd`/.libs \
           echo Running Valgrind on $$f; \
           $(VALGRIND) $(VALGRIND_OPTIONS) --log-file=`basename $$f`.log $$f; \
        done

reformat:
	astyle --mode=c \
               --quiet \
               --style=1tbs \
               --indent=spaces=4 \
               --indent-namespaces \
               --indent-col1-comments \
               --max-instatement-indent=78 \
               --pad-oper \
               --pad-header \
               --add-brackets \
               --unpad-paren \
               --align-pointer=name \
               --align-reference=name \
               $(top_srcdir)/include/libcbio/*.[ch] \
               $(top_srcdir)/src/*.[ch] \
               $(top_srcdir)/tests/*.[ch][ch]


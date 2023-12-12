#-------------------------------------------------------------------------
#
# Makefile--
#    Makefile for access/heap
#
# IDENTIFICATION
#    contrib/heapy/Makefile
#
#-------------------------------------------------------------------------

subdir = contrib/heapy
top_builddir = ../../
include $(top_builddir)/src/Makefile.global

OBJS = src/heapy/heapam.o src/heapy/heapam_handler.o  src/heapy/heapyam_handler.o \
	src/heapy/heapam_visibility.o src/heapy/hio.o src/heapy/pruneheap.o src/heapy/rewriteheap.o \
	src/heapy/syncscan.o src/heapy/tuptoaster.o src/heapy/vacuumlazy.o src/heapy/visibilitymap.o \
	ysmgr/md.o \
	ysmgr/smgr.o \
	src/virt_tablespace.o

include $(top_srcdir)/src/backend/common.mk

PG_CPPFLAGS +=  -fPIC -I./include -Iinclude -Ilib -I$(libpq_srcdir) -I$(libpq_srcdir)/postgresql/server/utils

PG_CXXFLAGS +=  -fPIC -I./include -Iinclude -Ilib -I$(libpq_srcdir) -I$(libpq_srcdir)/postgresql/server/utils

PG_CFLAGS += -fPIC
PG_CFLAGS += -I./ysmgr

PG_CFLAGS += -I./$(top_srcdir)/src/include -I./include -Iinclude -Ilib -I$(libpq_srcdir) -I$(libpq_srcdir)/postgresql/server/utils  -I$(libpq_srcdir)/postgresql/server

MODULE_big = heapy

EXTENSION = heapy
DATA = heapy--1.0.sql
PGFILEDESC = "heapy - yeneid help functions"

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/heapy
top_builddir = ../..
top_srcdir = ../..
# include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif




cleanall:
	@-$(MAKE) clean # incase PGXS not included
	rm -f *.o *.so *.a
	rm -f *.gcov src/*.gcov src/*.gcda src/*.gcno
	rm -f src/*.o src/*.d


apply_fmt:
	clang-format -i ./src/*.cpp ./include/*.h ./*.c

format:
	@-[ -n "`command -v dos2unix`" ] && dos2unix -k -q src/*.cpp bin/gpcheckcloud/*.cpp test/*.cpp include/*.h
	@-[ -n "`command -v clang-format`" ] && clang-format -style="{BasedOnStyle: Google, IndentWidth: 4, ColumnLimit: 100, AllowShortFunctionsOnASingleLine: None}" -i src/*.cpp bin/gpcheckcloud/*.cpp test/*.cpp include/*.h

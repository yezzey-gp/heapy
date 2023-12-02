#-------------------------------------------------------------------------
#
# Makefile--
#    Makefile for access/heap
#
# IDENTIFICATION
#    src/backend/access/heap/Makefile
#
#-------------------------------------------------------------------------

subdir = src/backend/access/heap
top_builddir = ../../
include $(top_builddir)/src/Makefile.global

OBJS = heapam.o heapam_handler.o heapam_visibility.o hio.o pruneheap.o rewriteheap.o \
	syncscan.o tuptoaster.o vacuumlazy.o visibilitymap.o

include $(top_srcdir)/src/backend/common.mk

# PG_CPPFLAGS +=  -fPIC -I./include -Iinclude -Ilib -I$(libpq_srcdir) -I$(libpq_srcdir)/postgresql/server/utils

# PG_CXXFLAGS +=  -fPIC -I./include -Iinclude -Ilib -I$(libpq_srcdir) -I$(libpq_srcdir)/postgresql/server/utils

PG_CFLAGS += -fPIC


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

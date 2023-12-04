#ifndef HEAPY_VIRTUAL_TABLESPACE
#define HEAPY_VIRTUAL_TABLESPACE

#include "pg.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

EXTERNC void HeapyATExecSetTableSpace(Relation aorel, Oid reloid,
                                       Oid desttablespace_oid);


EXTERNC void HeapyDefineOffloadPolicy(Oid reloid);

#endif /* HEAPY_VIRTUAL_TABLESPACE */
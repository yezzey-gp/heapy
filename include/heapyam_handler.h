#ifndef HEAPY_HEAPYAM_HANDLER_TABLESPACE
#define HEAPY_HEAPYAM_HANDLER_TABLESPACE

#include "pg.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif


#ifdef __cplusplus
extern "C" {
#endif

#include "heapyam.h"

#ifdef __cplusplus
}
#endif


EXTERNC void
heapyam_tuple_insert_internal(Relation relation, TupleTableSlot *slot, CommandId cid,
					int options, BulkInsertState bistate);

#endif /* HEAPY_HEAPYAM_HANDLER_TABLESPACE */
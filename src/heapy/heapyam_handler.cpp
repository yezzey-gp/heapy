

#include "pg.h"

#include "heapyam_handler.h"

/* ----------------------------------------------------------------------------
 *  Functions for manipulations of physical tuples for heap AM.
 * ----------------------------------------------------------------------------
 */

void
heapyam_tuple_insert_internal(Relation relation, TupleTableSlot *slot, CommandId cid,
					int options, BulkInsertState bistate)
{
	bool		shouldFree = true;
	auto	tuple = ExecFetchSlotHeapTuple(slot, true, &shouldFree);
	auto xid = GetCurrentTransactionId();

	/* Update the tuple with table oid */
	slot->tts_tableOid = RelationGetRelid(relation);
	tuple->t_tableOid = slot->tts_tableOid;

	/* Perform the insertion, and copy the resulting ItemPointer */
	heapy_insert(relation, tuple, cid, options, bistate, xid);
	ItemPointerCopy(&tuple->t_self, &slot->tts_tid);

	/* update metadata fork */

	auto oldSmgr = RelationGetSmgr(relation);
	
	RelationGetSmgr(relation) = ;

	if (shouldFree)
		pfree(tuple);
}
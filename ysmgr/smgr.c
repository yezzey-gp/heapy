
#include "postgres.h"


#include "access/aomd.h"
#include "access/xact.h"
#include "access/xlogutils.h"
#include "catalog/catalog.h"
#include "catalog/indexing.h"
#include "commands/tablespace.h"
#include "postmaster/postmaster.h"
#include "lib/ilist.h"
#include "storage/bufmgr.h"
#include "storage/ipc.h"
#include "storage/md.h"
#include "storage/smgr.h"
#include "utils/faultinjector.h"
#include "utils/hsearch.h"
#include "utils/inval.h"

#include "catalog/pg_tablespace.h"

#include "ysmgr/md.h"

static const f_smgr smgrsw[] = {
	/* magnetic disk */
	{
		.smgr_init = mdinit,
		.smgr_shutdown = NULL,
		.smgr_close = mdclose,
		.smgr_create = mdcreate,
		.smgr_exists = mdexists,
		.smgr_unlink = mdunlink,
		.smgr_extend = mdextend,
		.smgr_prefetch = mdprefetch,
		.smgr_read = mdread,
		.smgr_write = mdwrite,
		.smgr_writeback = mdwriteback,
		.smgr_nblocks = mdnblocks,
		.smgr_truncate = mdtruncate,
		.smgr_immedsync = mdimmedsync,
	},
	/*
	 * Relation files that are different from heap, characterised by:
	 *     1. variable blocksize
	 *     2. block numbers are not consecutive
	 *     3. shared buffers are not used
	 * Append-optimized relation files currently fall in this category.
	 */
	{
		.smgr_init = NULL,
		.smgr_shutdown = NULL,
		.smgr_close = mdclose,
		.smgr_create = mdcreate,
		.smgr_exists = mdexists,
		.smgr_unlink = mdunlink_ao,
		.smgr_extend = mdextend,
		.smgr_prefetch = mdprefetch,
		.smgr_read = mdread,
		.smgr_write = mdwrite,
		.smgr_writeback = mdwriteback,
		.smgr_nblocks = mdnblocks,
		.smgr_truncate = mdtruncate,
		.smgr_immedsync = mdimmedsync,
	},
    	/* magnetic disk */
	{
		.smgr_init = ymdinit,
		.smgr_shutdown = NULL,
		.smgr_close = ymdclose,
		.smgr_create = ymdcreate,
		.smgr_exists = ymdexists,
		.smgr_unlink = ymdunlink,
		.smgr_extend = ymdextend,
		.smgr_prefetch = ymdprefetch,
		.smgr_read = ymdread,
		.smgr_write = ymdwrite,
		.smgr_writeback = ymdwriteback,
		.smgr_nblocks = ymdnblocks,
		.smgr_truncate = ymdtruncate,
		.smgr_immedsync = ymdimmedsync,
	},
};


#define HEAPY_SMGR_ID 2
#define NSmgr 2

void smgr_init_heapy(void) {
	int i;
	for (i = 0; i < NSmgr; i++)
	{
		if (smgrsw[i].smgr_init)
			smgrsw[i].smgr_init();
	}

	ymdinit();
}


const f_smgr *
smgr_heapy(BackendId backend, RelFileNode rnode, SMgrImpl which)
{
    if (rnode.spcNode == HEAPYTABLESPACE_OID
    ) {
        return  &smgrsw[HEAPY_SMGR_ID];
    }
	// for md.c 
	return &smgrsw[which];
}


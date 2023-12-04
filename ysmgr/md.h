/*-------------------------------------------------------------------------
 *
 * md.h
 *	  magnetic disk storage manager public interface declarations.
 *
 *
 * Portions Copyright (c) 1996-2019, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/storage/md.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef YMD_H
#define YMD_H

#include "storage/block.h"
#include "storage/relfilenode.h"
#include "storage/smgr.h"
#include "storage/sync.h"

/* md storage manager functionality */
extern void ymdinit(void);
extern void ymdclose(SMgrRelation reln, ForkNumber forknum);
extern void ymdcreate(SMgrRelation reln, ForkNumber forknum, bool isRedo);
extern void ymdcreate_ao(RelFileNodeBackend rnode, int32 segmentFileNum, bool isRedo);
extern bool ymdexists(SMgrRelation reln, ForkNumber forknum);
extern void ymdunlink(RelFileNodeBackend rnode, ForkNumber forknum, bool isRedo);
extern void ymdextend(SMgrRelation reln, ForkNumber forknum,
					 BlockNumber blocknum, char *buffer, bool skipFsync);
extern void ymdprefetch(SMgrRelation reln, ForkNumber forknum,
					   BlockNumber blocknum);
extern void ymdread(SMgrRelation reln, ForkNumber forknum, BlockNumber blocknum,
				   char *buffer);
extern void ymdwrite(SMgrRelation reln, ForkNumber forknum,
					BlockNumber blocknum, char *buffer, bool skipFsync);
extern void ymdwriteback(SMgrRelation reln, ForkNumber forknum,
						BlockNumber blocknum, BlockNumber nblocks);
extern BlockNumber ymdnblocks(SMgrRelation reln, ForkNumber forknum);
extern void ymdtruncate(SMgrRelation reln, ForkNumber forknum,
					   BlockNumber nblocks);
extern void ymdimmedsync(SMgrRelation reln, ForkNumber forknum);

/* md sync callbacks */
extern int	ymdsyncfiletag(const FileTag *ftag, char *path);
extern int	ymdunlinkfiletag(const FileTag *ftag, char *path);
extern bool ymdfiletagmatches(const FileTag *ftag, const FileTag *candidate);
#endif							/* YMD_H */

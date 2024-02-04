

#ifndef HEAPY_META_H
#define HEAPY_META_H


/*
 * RelationOpenSmgr
 *		Open the relation at the smgr level, if not already done.
 */
#define RelationGetSmgr(relation) (relation)->rd_smgr


#endif /* HEAPY_META_H */
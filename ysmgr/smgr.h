#ifndef HEAPY_SMGR_H
#define HEAPY_SMGR_H

#include "storage/smgr.h"

const f_smgr *
smgr_heapy(BackendId backend, RelFileNode rnode, SMgrImpl which);

void smgr_init_heapy(void);


#endif HEAPY_SMGR_H
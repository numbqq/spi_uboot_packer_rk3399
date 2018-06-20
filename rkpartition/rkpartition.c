/*********************************************************************
(C) Copyright 2005-2016 Fuzhou Rockchip Electronics Co.Ltd
This program is the unpublished property and trade secret of Rockchip.
It is to be utilized solely under license from Rockchip and it is   to
be maintained on a confidential basis for internal company use only.
The security and protection of the program is paramount to maintenance
of the trade secret status.  It is to  be  protected  from  disclosure
to unauthorized parties, both within the Licensee company and outside,
in a manner  not less stringent than  that utilized for Licensee's own
proprietary internal information.  No  copies of  the source or Object
Code are to leave the premises of Licensee's business except in strict
accordance with the license agreement signed by Licensee with Rockchip.
*********************************************************************/
#include "config.h"

#ifdef _LOAD_KERNEL_
STRUCT_PART_INFO g_partition;  //size 2KB
#define RK_PARTITION_TAG 0x50464B52
uint32 rk_partition_init(void)
{
	//PRINT_E("rk_partition_init %d\n",RkldTimerGetTick());
	if(StorageReadLba(0, &g_partition, 4) == FTL_OK) {
		//rknand_print_hex("part:", &g_partition, 4, 512);
		if (g_partition.hdr.uiFwTag == RK_PARTITION_TAG) {
			return 0;
		}
	}
	return -1;
}

uint32 get_part_offset(ENUM_PARTITION_TYPE emPartType)
{
	uint32 i;

	if (g_partition.hdr.uiFwTag == RK_PARTITION_TAG) {
		for (i = 0; i < g_partition.hdr.uiPartEntryCount; i++) {
			if(g_partition.part[i].emPartType == emPartType) {
				return g_partition.part[i].uiPartOffset;
			}
		}		
	}

	return -1;
}

#endif

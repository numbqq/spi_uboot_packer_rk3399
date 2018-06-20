#ifndef _RK_PARTITION_
#define _RK_PARTITION_

typedef enum {
	PART_VENDOR = 1 << 0,
	PART_IDBLOCK = 1 << 1,
	PART_KERNEL = 1 << 2,
	PART_BOOT = 1 << 3,
	PART_TRUST = 1 << 4,
	PART_UBOOT = 1 << 5,
	PART_USER = 1 << 31
}ENUM_PARTITION_TYPE;

typedef struct {
	uint16	year;
	uint8	month;
	uint8	day;
	uint8	hour;
	uint8	min;
	uint8	sec;
	uint8	reserve;
}STRUCT_DATETIME,*PSTRUCT_DATETIME;

typedef struct {
	uint32	uiFwTag; //"RKFP"
	STRUCT_DATETIME	dtReleaseDataTime;
	uint32	uiFwVer;
	uint32	uiSize;//size of sturct,unit of uint8
	uint32	uiPartEntryOffset;//unit of sector
	uint32	uiBackupPartEntryOffset;
	uint32	uiPartEntrySize;//unit of uint8
	uint32	uiPartEntryCount;
	uint32	uiFwSize;//unit of uint8
	uint8	reserved[464];
	uint32	uiPartEntryCrc;
	uint32	uiHeaderCrc;
}STRUCT_FW_HEADER,*PSTRUCT_FW_HEADER;

typedef struct {
	uint8	szName[32];
	ENUM_PARTITION_TYPE emPartType;
	uint32	uiPartOffset;//unit of sector
	uint32	uiPartSize;//unit of sector
	uint32	uiDataLength;//unit of uint8
	uint32	uiPartProperty;
	uint8	reserved[76];
}STRUCT_PART_ENTRY,*PSTRUCT_PART_ENTRY;

typedef struct {
	STRUCT_FW_HEADER hdr;     //0.5KB
	STRUCT_PART_ENTRY part[12]; //1.5KB
}STRUCT_PART_INFO,*PSTRUCT_PART_INFO;

extern STRUCT_PART_INFO g_partition;
extern uint32 rk_partition_init(void);
extern uint32 get_kernel_part_offset(void);

#endif

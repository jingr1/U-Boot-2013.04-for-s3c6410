/*
 * OK6410 SD Boot
 */

#include <common.h>
#include <asm/io.h>

#ifdef CONFIG_MMC_CHANNEL
#define MMC_CHANNEL CONFIG_MMC_CHANNEL
#else
#define MMC_CHANNEL 0
#endif

#define ELFIN_HSMMC_BASE 	(0x7c200000 + MMC_CHANNEL*0x100000)
#define HM_CONTROL4      	(ELFIN_HSMMC_BASE + 0x8C)
#define globalBlockSizeHide 	*((volatile unsigned int *)(0x0c004000-0x04))
#define globalSDHCInfo      	*((volatile unsigned int *)(0x0c004000-0x08))

#define LAST_BLKPOS	   	(globalBlockSizeHide - 2)	
#define BLK_SIZE	    	512
#define BL1_SIZE	    	(1024*8)
#define BL2_SIZE	    	(1024*300)

#if 0
#define ENV_SIZE		CONFIG_ENV_SIZE
#else
#define ENV_SIZE		(1024*16)
#endif

#define BL1_BLKCNT		(BL1_SIZE/BLK_SIZE)
#define BL2_BLKCNT		(BL2_SIZE/BLK_SIZE)
#define ENV_BLKCNT		(ENV_SIZE/BLK_SIZE)
#define STARTBLKADDR		(LAST_BLKPOS-BL1_BLKCNT-BL2_BLKCNT-ENV_BLKCNT)
#define DESTADDR		(CONFIG_SYS_PHY_UBOOT_BASE)

#define CopyMMCtoMem(a,b,c,d,e)	(((int(*)(int,uint,ushort,uint *, int))(*((uint *)(0x0C004000+0x8))))(a,b,c,d,e))

int BootCopyMMCtoMem()
{
  writel(readl(HM_CONTROL4)|(0x3<<16),HM_CONTROL4);
  return CopyMMCtoMem(MMC_CHANNEL,STARTBLKADDR,BL2_BLKCNT,(uint *)DESTADDR,0);
}



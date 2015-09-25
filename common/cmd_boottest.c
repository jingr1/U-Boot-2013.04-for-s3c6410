/*
 * Build a simple command for test
 * Author:jingri
*/

#include <common.h>
#include <command.h>

static int do_boottest(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
        int i;

        for (i = 0; i < argc; i++) 
		printf("argv[%d] = %s\n", i, argv[i]);

        return 0;
}

U_BOOT_CMD(
        boottest,   CONFIG_SYS_MAXARGS,     1,      do_boottest,
        "just for test\n",
        "[args..]\n"
        "    - boottest command---\n"
	"	-- build a simple command"
);

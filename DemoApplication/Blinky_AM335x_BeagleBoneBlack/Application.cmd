/*
 * Linker script.
 *
 * $LastChangedRevision: 903 $
 * $LastChangedDate:: 2016-03-10 14:44:32 +0100#$
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */

-stack  0x2000                             /* SOFTWARE STACK SIZE           */
-heap   0x2000                             /* HEAP AREA SIZE                */
-e Entry
/* Since we used 'Entry' as the entry-point symbol the compiler issues a    */
/* warning (#10063-D: entry-point symbol other than "_c_int00" specified:   */
/* "Entry"). The CCS Version (5.1.0.08000) stops building from command      */
/* line when there is a warning. So this warning is suppressed with the     */
/* below flag. */
--diag_suppress=10063

MEMORY
{
	DDR_MEM: origin = 0x80000000, length = 0x20000000
}


SECTIONS
{
	/*.text:Entry : load > 0x402F0400*/
	.text:Entry : load > 0x80000000

    .text		>  DDR_MEM
    .stack      >  DDR_MEM
    .bss        >  DDR_MEM
                    RUN_START(bss_start)
                    RUN_END(bss_end)
    .const      >  DDR_MEM
    .cinit 		> DDR_MEM
    .data 		> DDR_MEM
}

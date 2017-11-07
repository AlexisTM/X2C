/*
 * Linker script.
 *
 * $LastChangedRevision: 541 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
MEMORY
{
/* program memory */
PAGE 0:
	FLASH : origin = 0x300000, length = 0x3FF80
	BEGIN : origin = 0x33FFF6, length = 0x2
/* data memory */
PAGE 1:
	RAM : origin = 0x8000, length = 0x8000
}

SECTIONS
{
    .cinit				> FLASH PAGE 0
    .text				> FLASH PAGE 0
    .econst				> FLASH PAGE 0

    .ebss				> RAM PAGE 1
    .bss    			> RAM PAGE 1
    .esysmem 			> RAM PAGE 1
    .sysmem 			> RAM PAGE 1
    .stack  			> RAM PAGE 1

	.begin				> BEGIN PAGE 0
    .reset              > RAM, PAGE = 1, TYPE = DSECT

    ramfuncs:			LOAD = FLASH, PAGE = 0,
    					RUN = RAM, PAGE = 1,
    					LOAD_START(_RamfuncsLoadStart),
                        LOAD_END(_RamfuncsLoadEnd),
                        RUN_START(_RamfuncsRunStart)
}

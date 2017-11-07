;*
;* Places a branch to 'c_int00' function at flash start address.
;*
;* $LastChangedRevision: 480 $
;*
;* Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
;* All rights reserved.
;*
	.ref _c_int00
	.sect ".begin"
	LB _c_int00

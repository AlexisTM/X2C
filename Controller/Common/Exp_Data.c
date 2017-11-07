/*
 * Exponential function lookup table.
 * -1..0..1 ~ exp(-1)..exp(1)
 *
 * Caution: input > 0 leads to output = 1!
 *
 * $LastChangedRevision: 632 $
 *
 * Copyright (c) 2013, Linz Center of Mechatronics GmbH (LCM) http://www.lcm.at/
 * All rights reserved.
 */
#include "Exp_Data.h"

/* Exponential function data in 8 bit format */
#ifndef __NO_EXP_TABLE8__
const int8 Exp_Table8[257] = {
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
    127,  127,  127,  127,  127,  127,  127,  127,
     47,   47,   48,   48,   49,   49,   49,   50,
     50,   51,   51,   51,   52,   52,   53,   53,
     53,   54,   54,   55,   55,   55,   56,   56,
     57,   57,   58,   58,   59,   59,   60,   60,
     60,   61,   61,   62,   62,   63,   63,   64,
     64,   65,   65,   66,   66,   67,   67,   68,
     69,   69,   70,   70,   71,   71,   72,   72,
     73,   74,   74,   75,   75,   76,   76,   77,
     78,   78,   79,   79,   80,   81,   81,   82,
     83,   83,   84,   85,   85,   86,   87,   87,
     88,   89,   89,   90,   91,   91,   92,   93,
     94,   94,   95,   96,   97,   97,   98,   99,
    100,  100,  101,  102,  103,  104,  104,  105,
    106,  107,  108,  109,  109,  110,  111,  112,
    113,  114,  115,  116,  117,  117,  118,  119,
    120,  121,  122,  123,  124,  125,  126,  127,
    127};
#endif

/* Exponential function data in 16 bit format */
#ifndef __NO_EXP_TABLE16__
const int16 Exp_Table16[257] = {
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    32767,  32767,  32767,  32767,  32767,  32767,  32767,  32767,
    12055,  12149,  12245,  12341,  12437,  12535,  12633,  12732,
    12832,  12933,  13034,  13136,  13239,  13343,  13448,  13553,
    13660,  13767,  13875,  13984,  14093,  14204,  14315,  14428,
    14541,  14655,  14770,  14886,  15002,  15120,  15239,  15358,
    15479,  15600,  15722,  15846,  15970,  16095,  16221,  16349,
    16477,  16606,  16736,  16868,  17000,  17133,  17268,  17403,
    17539,  17677,  17816,  17955,  18096,  18238,  18381,  18525,
    18671,  18817,  18965,  19113,  19263,  19414,  19567,  19720,
    19875,  20031,  20188,  20346,  20506,  20667,  20829,  20992,
    21157,  21323,  21490,  21658,  21828,  21999,  22172,  22346,
    22521,  22698,  22876,  23055,  23236,  23418,  23602,  23787,
    23974,  24162,  24351,  24542,  24735,  24929,  25124,  25321,
    25520,  25720,  25922,  26125,  26330,  26536,  26744,  26954,
    27166,  27379,  27593,  27810,  28028,  28248,  28469,  28693,
    28918,  29144,  29373,  29603,  29836,  30070,  30305,  30543,
    30783,  31024,  31267,  31513,  31760,  32009,  32260,  32513,
    32767};
#endif
	
/* Exponential function data in 32 bit format */
#ifndef __NO_EXP_TABLE32__
const int32 Exp_Table32[257] = {
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
    2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,  2147483647,
     790015084,   796211249,   802456012,   808749752,   815092855,   821485708,   827928700,   834422225,
     840966680,   847562463,   854209978,   860909630,   867661828,   874466984,   881325513,   888237835,
     895204371,   902225546,   909301788,   916433531,   923621208,   930865259,   938166125,   945524254,
     952940092,   960414094,   967946715,   975538415,   983189658,   990900910,   998672642,  1006505329,
    1014399448,  1022355481,  1030373915,  1038455238,  1046599943,  1054808528,  1063081494,  1071419345,
    1079822591,  1088291745,  1096827323,  1105429846,  1114099840,  1122837833,  1131644360,  1140519956,
    1149465165,  1158480532,  1167566608,  1176723946,  1185953106,  1195254652,  1204629150,  1214077174,
    1223599299,  1233196107,  1242868184,  1252616120,  1262440510,  1272341954,  1282321055,  1292378424,
    1302514674,  1312730423,  1323026295,  1333402919,  1343860928,  1354400960,  1365023658,  1375729671,
    1386519653,  1397394261,  1408354160,  1419400019,  1430532511,  1441752317,  1453060120,  1464456612,
    1475942488,  1487518448,  1499185200,  1510943455,  1522793931,  1534737352,  1546774447,  1558905949,
    1571132600,  1583455145,  1595874338,  1608390936,  1621005702,  1633719407,  1646532828,  1659446745,
    1672461947,  1685579228,  1698799390,  1712123239,  1725551588,  1739085257,  1752725071,  1766471864,
    1780326475,  1794289749,  1808362538,  1822545701,  1836840104,  1851246619,  1865766126,  1880399512,
    1895147668,  1910011495,  1924991901,  1940089800,  1955306112,  1970641768,  1986097703,  2001674861,
    2017374191,  2033196653,  2049143212,  2065214841,  2081412522,  2097737243,  2114190000,  2130771798,
    2147483647};
#endif

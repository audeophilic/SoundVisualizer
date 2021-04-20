#pragma once
#pragma once
// A fixed array of colors that can be indexed into of the form 0xAARRGGBB where
// A = alpha channel, R = red channel, G = green channel, B = blue channel.
// The ColorCycle forms a gradient from black/transparent to blue, to green, to red.
static const size_t ColorCycle[] =
{
0x00000000,
0x01000001,
0x02000002,
0x04000004,
0x05000005,
0x06000006,
0x07000007,
0x08000008,
0x09000009,
0x0a00000a,
0x0b00000b,
0x0c00000c,
0x0d00000d,
0x0e00000e,
0x0f00000f,
0x10000010,
0x11000011,
0x12000012,
0x13000013,
0x14000014,
0x15000015,
0x16000016,
0x17000017,
0x18000018,
0x19000019,
0x1a00001a,
0x1b00001b,
0x1c00001c,
0x1d00001d,
0x1e00001e,
0x1f00001f,
0x20000020,
0x21000021,
0x22000022,
0x23000023,
0x24000024,
0x25000025,
0x26000026,
0x27000027,
0x28000028,
0x29000029,
0x2a00002a,
0x2b00002b,
0x2c00002c,
0x2d00002d,
0x2e00002e,
0x2f00002f,
0x30000030,
0x31000031,
0x32000032,
0x33000033,
0x34000034,
0x35000035,
0x36000036,
0x37000037,
0x38000038,
0x39000039,
0x3a00003a,
0x3b00003b,
0x3c00003c,
0x3d00003d,
0x3e00003e,
0x3f00003f,
0x40000040,
0x41000041,
0x42000042,
0x43000043,
0x44000044,
0x45000045,
0x46000046,
0x47000047,
0x48000048,
0x49000049,
0x4a00004a,
0x4b00004b,
0x4c00004c,
0x4d00004d,
0x4e00004e,
0x4f00004f,
0x50000050,
0x51000051,
0x52000052,
0x53000053,
0x54000054,
0x55000055,
0x56000056,
0x57000057,
0x58000058,
0x59000059,
0x5a00005a,
0x5b00005b,
0x5c00005c,
0x5d00005d,
0x5e00005e,
0x5f00005f,
0x60000060,
0x61000061,
0x62000062,
0x63000063,
0x64000064,
0x65000065,
0x66000066,
0x67000067,
0x68000068,
0x69000069,
0x6a00006a,
0x6b00006b,
0x6c00006c,
0x6d00006d,
0x6e00006e,
0x6f00006f,
0x70000070,
0x71000071,
0x72000072,
0x73000073,
0x74000074,
0x75000075,
0x76000076,
0x77000077,
0x78000078,
0x79000079,
0x7a00007a,
0x7b00007b,
0x7c00007c,
0x7d00007d,
0x7e00007e,
0x7f00007f,
0x80000080,
0x81000081,
0x82000082,
0x83000083,
0x84000084,
0x85000085,
0x86000086,
0x87000087,
0x88000088,
0x89000089,
0x8a00008a,
0x8b00008b,
0x8c00008c,
0x8d00008d,
0x8e00008e,
0x8f00008f,
0x90000090,
0x91000091,
0x92000092,
0x93000093,
0x94000094,
0x95000095,
0x96000096,
0x97000097,
0x98000098,
0x99000099,
0x9a00009a,
0x9b00009b,
0x9c00009c,
0x9d00009d,
0x9e00009e,
0x9f00009f,
0xa00000a0,
0xa10000a1,
0xa20000a2,
0xa30000a3,
0xa40000a4,
0xa50000a5,
0xa60000a6,
0xa70000a7,
0xa80000a8,
0xa90000a9,
0xaa0000aa,
0xab0000ab,
0xac0000ac,
0xad0000ad,
0xae0000ae,
0xaf0000af,
0xb00000b0,
0xb10000b1,
0xb20000b2,
0xb30000b3,
0xb40000b4,
0xb50000b5,
0xb60000b6,
0xb70000b7,
0xb80000b8,
0xb90000b9,
0xba0000ba,
0xbb0000bb,
0xbc0000bc,
0xbd0000bd,
0xbe0000be,
0xbf0000bf,
0xc00000c0,
0xc10000c1,
0xc20000c2,
0xc30000c3,
0xc40000c4,
0xc50000c5,
0xc60000c6,
0xc70000c7,
0xc80000c8,
0xc90000c9,
0xca0000ca,
0xcb0000cb,
0xcc0000cc,
0xcd0000cd,
0xce0000ce,
0xcf0000cf,
0xd00000d0,
0xd10000d1,
0xd20000d2,
0xd30000d3,
0xd40000d4,
0xd50000d5,
0xd60000d6,
0xd70000d7,
0xd80000d8,
0xd90000d9,
0xda0000da,
0xdb0000db,
0xdc0000dc,
0xdd0000dd,
0xde0000de,
0xdf0000df,
0xe00000e0,
0xe10000e1,
0xe20000e2,
0xe30000e3,
0xe40000e4,
0xe50000e5,
0xe60000e6,
0xe70000e7,
0xe80000e8,
0xe90000e9,
0xea0000ea,
0xeb0000eb,
0xec0000ec,
0xed0000ed,
0xee0000ee,
0xef0000ef,
0xf00000f0,
0xf10000f1,
0xf20000f2,
0xf30000f3,
0xf40000f4,
0xf50000f5,
0xf60000f6,
0xf70000f7,
0xf80000f8,
0xf90000f9,
0xfa0000fa,
0xfb0000fb,
0xfc0000fc,
0xfd0000fd,
0xfe0000fe,
0xff0000ff,
0xff0001fe,
0xff0002fd,
0xff0003fc,
0xff0004fb,
0xff0005fa,
0xff0006f9,
0xff0007f8,
0xff0008f7,
0xff0009f6,
0xff000af5,
0xff000bf4,
0xff000cf3,
0xff000df2,
0xff000ef1,
0xff000ff0,
0xff0010ef,
0xff0011ee,
0xff0012ed,
0xff0013ec,
0xff0014eb,
0xff0015ea,
0xff0016e9,
0xff0017e8,
0xff0018e7,
0xff0019e6,
0xff001ae5,
0xff001be4,
0xff001ce3,
0xff001de2,
0xff001ee1,
0xff001fe0,
0xff0020df,
0xff0021de,
0xff0022dd,
0xff0023dc,
0xff0024db,
0xff0025da,
0xff0026d9,
0xff0027d8,
0xff0028d7,
0xff0029d6,
0xff002ad5,
0xff002bd4,
0xff002cd3,
0xff002dd2,
0xff002ed1,
0xff002fd0,
0xff0030cf,
0xff0031ce,
0xff0032cd,
0xff0033cc,
0xff0034cb,
0xff0035ca,
0xff0036c9,
0xff0037c8,
0xff0038c7,
0xff0039c6,
0xff003ac5,
0xff003bc4,
0xff003cc3,
0xff003dc2,
0xff003ec1,
0xff003fc0,
0xff0040bf,
0xff0041be,
0xff0042bd,
0xff0043bc,
0xff0044bb,
0xff0045ba,
0xff0046b9,
0xff0047b8,
0xff0048b7,
0xff0049b6,
0xff004ab5,
0xff004bb4,
0xff004cb3,
0xff004db2,
0xff004eb1,
0xff004fb0,
0xff0050af,
0xff0051ae,
0xff0052ad,
0xff0053ac,
0xff0054ab,
0xff0055aa,
0xff0056a9,
0xff0057a8,
0xff0058a7,
0xff0059a6,
0xff005aa5,
0xff005ba4,
0xff005ca3,
0xff005da2,
0xff005ea1,
0xff005fa0,
0xff00609f,
0xff00619e,
0xff00629d,
0xff00639c,
0xff00649b,
0xff00659a,
0xff006699,
0xff006798,
0xff006897,
0xff006996,
0xff006a95,
0xff006b94,
0xff006c93,
0xff006d92,
0xff006e91,
0xff006f90,
0xff00708f,
0xff00718e,
0xff00728d,
0xff00738c,
0xff00748b,
0xff00758a,
0xff007689,
0xff007788,
0xff007887,
0xff007986,
0xff007a85,
0xff007b84,
0xff007c83,
0xff007d82,
0xff007e81,
0xff007f80,
0xff00807f,
0xff00817e,
0xff00827d,
0xff00837c,
0xff00847b,
0xff00857a,
0xff008679,
0xff008778,
0xff008877,
0xff008976,
0xff008a75,
0xff008b74,
0xff008c73,
0xff008d72,
0xff008e71,
0xff008f70,
0xff00906f,
0xff00916e,
0xff00926d,
0xff00936c,
0xff00946b,
0xff00956a,
0xff009669,
0xff009768,
0xff009867,
0xff009966,
0xff009a65,
0xff009b64,
0xff009c63,
0xff009d62,
0xff009e61,
0xff009f60,
0xff00a05f,
0xff00a15e,
0xff00a25d,
0xff00a35c,
0xff00a45b,
0xff00a55a,
0xff00a659,
0xff00a758,
0xff00a857,
0xff00a956,
0xff00aa55,
0xff00ab54,
0xff00ac53,
0xff00ad52,
0xff00ae51,
0xff00af50,
0xff00b04f,
0xff00b14e,
0xff00b24d,
0xff00b34c,
0xff00b44b,
0xff00b54a,
0xff00b649,
0xff00b748,
0xff00b847,
0xff00b946,
0xff00ba45,
0xff00bb44,
0xff00bc43,
0xff00bd42,
0xff00be41,
0xff00bf40,
0xff00c03f,
0xff00c13e,
0xff00c23d,
0xff00c33c,
0xff00c43b,
0xff00c53a,
0xff00c639,
0xff00c738,
0xff00c837,
0xff00c936,
0xff00ca35,
0xff00cb34,
0xff00cc33,
0xff00cd32,
0xff00ce31,
0xff00cf30,
0xff00d02f,
0xff00d12e,
0xff00d22d,
0xff00d32c,
0xff00d42b,
0xff00d52a,
0xff00d629,
0xff00d728,
0xff00d827,
0xff00d926,
0xff00da25,
0xff00db24,
0xff00dc23,
0xff00dd22,
0xff00de21,
0xff00df20,
0xff00e01f,
0xff00e11e,
0xff00e21d,
0xff00e31c,
0xff00e41b,
0xff00e51a,
0xff00e619,
0xff00e718,
0xff00e817,
0xff00e916,
0xff00ea15,
0xff00eb14,
0xff00ec13,
0xff00ed12,
0xff00ee11,
0xff00ef10,
0xff00f00f,
0xff00f10e,
0xff00f20d,
0xff00f30c,
0xff00f40b,
0xff00f50a,
0xff00f609,
0xff00f708,
0xff00f807,
0xff00f906,
0xff00fa05,
0xff00fb04,
0xff00fc03,
0xff00fd02,
0xff00fe01,
0xff00ff00,
0xff01fe00,
0xff02fd00,
0xff03fc00,
0xff04fb00,
0xff05fa00,
0xff06f900,
0xff07f800,
0xff08f700,
0xff09f600,
0xff0af500,
0xff0bf400,
0xff0cf300,
0xff0df200,
0xff0ef100,
0xff0ff000,
0xff10ef00,
0xff11ee00,
0xff12ed00,
0xff13ec00,
0xff14eb00,
0xff15ea00,
0xff16e900,
0xff17e800,
0xff18e700,
0xff19e600,
0xff1ae500,
0xff1be400,
0xff1ce300,
0xff1de200,
0xff1ee100,
0xff1fe000,
0xff20df00,
0xff21de00,
0xff22dd00,
0xff23dc00,
0xff24db00,
0xff25da00,
0xff26d900,
0xff27d800,
0xff28d700,
0xff29d600,
0xff2ad500,
0xff2bd400,
0xff2cd300,
0xff2dd200,
0xff2ed100,
0xff2fd000,
0xff30cf00,
0xff31ce00,
0xff32cd00,
0xff33cc00,
0xff34cb00,
0xff35ca00,
0xff36c900,
0xff37c800,
0xff38c700,
0xff39c600,
0xff3ac500,
0xff3bc400,
0xff3cc300,
0xff3dc200,
0xff3ec100,
0xff3fc000,
0xff40bf00,
0xff41be00,
0xff42bd00,
0xff43bc00,
0xff44bb00,
0xff45ba00,
0xff46b900,
0xff47b800,
0xff48b700,
0xff49b600,
0xff4ab500,
0xff4bb400,
0xff4cb300,
0xff4db200,
0xff4eb100,
0xff4fb000,
0xff50af00,
0xff51ae00,
0xff52ad00,
0xff53ac00,
0xff54ab00,
0xff55aa00,
0xff56a900,
0xff57a800,
0xff58a700,
0xff59a600,
0xff5aa500,
0xff5ba400,
0xff5ca300,
0xff5da200,
0xff5ea100,
0xff5fa000,
0xff609f00,
0xff619e00,
0xff629d00,
0xff639c00,
0xff649b00,
0xff659a00,
0xff669900,
0xff679800,
0xff689700,
0xff699600,
0xff6a9500,
0xff6b9400,
0xff6c9300,
0xff6d9200,
0xff6e9100,
0xff6f9000,
0xff708f00,
0xff718e00,
0xff728d00,
0xff738c00,
0xff748b00,
0xff758a00,
0xff768900,
0xff778800,
0xff788700,
0xff798600,
0xff7a8500,
0xff7b8400,
0xff7c8300,
0xff7d8200,
0xff7e8100,
0xff7f8000,
0xff807f00,
0xff817e00,
0xff827d00,
0xff837c00,
0xff847b00,
0xff857a00,
0xff867900,
0xff877800,
0xff887700,
0xff897600,
0xff8a7500,
0xff8b7400,
0xff8c7300,
0xff8d7200,
0xff8e7100,
0xff8f7000,
0xff906f00,
0xff916e00,
0xff926d00,
0xff936c00,
0xff946b00,
0xff956a00,
0xff966900,
0xff976800,
0xff986700,
0xff996600,
0xff9a6500,
0xff9b6400,
0xff9c6300,
0xff9d6200,
0xff9e6100,
0xff9f6000,
0xffa05f00,
0xffa15e00,
0xffa25d00,
0xffa35c00,
0xffa45b00,
0xffa55a00,
0xffa65900,
0xffa75800,
0xffa85700,
0xffa95600,
0xffaa5500,
0xffab5400,
0xffac5300,
0xffad5200,
0xffae5100,
0xffaf5000,
0xffb04f00,
0xffb14e00,
0xffb24d00,
0xffb34c00,
0xffb44b00,
0xffb54a00,
0xffb64900,
0xffb74800,
0xffb84700,
0xffb94600,
0xffba4500,
0xffbb4400,
0xffbc4300,
0xffbd4200,
0xffbe4100,
0xffbf4000,
0xffc03f00,
0xffc13e00,
0xffc23d00,
0xffc33c00,
0xffc43b00,
0xffc53a00,
0xffc63900,
0xffc73800,
0xffc83700,
0xffc93600,
0xffca3500,
0xffcb3400,
0xffcc3300,
0xffcd3200,
0xffce3100,
0xffcf3000,
0xffd02f00,
0xffd12e00,
0xffd22d00,
0xffd32c00,
0xffd42b00,
0xffd52a00,
0xffd62900,
0xffd72800,
0xffd82700,
0xffd92600,
0xffda2500,
0xffdb2400,
0xffdc2300,
0xffdd2200,
0xffde2100,
0xffdf2000,
0xffe01f00,
0xffe11e00,
0xffe21d00,
0xffe31c00,
0xffe41b00,
0xffe51a00,
0xffe61900,
0xffe71800,
0xffe81700,
0xffe91600,
0xffea1500,
0xffeb1400,
0xffec1300,
0xffed1200,
0xffee1100,
0xffef1000,
0xfff00f00,
0xfff10e00,
0xfff20d00,
0xfff30c00,
0xfff40b00,
0xfff50a00,
0xfff60900,
0xfff70800,
0xfff80700,
0xfff90600,
0xfffa0500,
0xfffb0400,
0xfffc0300,
0xfffd0200,
0xfffe0100,
0xffff0000
};
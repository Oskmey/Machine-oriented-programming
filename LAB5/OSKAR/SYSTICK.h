#pragma once

typedef volatile struct{
	union{
		unsigned int STK_CTRL;
		struct{
			unsigned int ENABLE:1;
			unsigned int TICKINT:1;
			unsigned int CLKSOURCE:1;
			unsigned int :12;
			unsigned int COUNTFLAG:1;
			unsigned int :16;
		};
	};
	unsigned int LOAD:24;
	unsigned int :0;
	unsigned int VAL:24;
	unsigned int :0;
	unsigned int CALIB:24;
	unsigned int :6;
	unsigned int CALIB_UNKNOWN:2; //VET EJ LOL
}SYSTICK;
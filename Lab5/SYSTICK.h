#pragma once

#define SYSTICK_ADR (*((volatile SYSTICK*) 0xE000E010))

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
	unsigned int :8;
	unsigned int VAL:24;
	unsigned int :8;
	unsigned int CALIB:24;
	unsigned int :6;
	unsigned int CALIB_UNKNOWN:2; //VET EJ LOL
}SYSTICK;
#pragma once

#define SCB_VTOR (*((volatile unsigned int*) 0xE000ED08))//Put 0x2001C000 here, or choose a custom adress for SCB_ADRESSES
#define SCB_ADRESSES (*((volatile SCB*) 0x2001C004))


typedef volatile struct{
			void (*AIRCR)(void);
			void(*SCR)(void);
			void(*CCR)(void);
			void(*SPHR1)(void);
			void(*SPHR2)(void);
			void(*SHCCR)(void);
			void(*CFSR)(void);
			void(*HFSR)(void);
			int :32;
			void(*MMAR)(void);
			void(*BFAR)(void);
			void(*AFSR)(void);
}SCB;
	


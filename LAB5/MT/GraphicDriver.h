#pragma once
#define B_E 		0x40 	// Enable
#define B_RST 		0x20 	// Reset
#define B_CS2 		0x10 	// Controller Select 2
#define B_CS1 		8 		// Controller Select 1
#define B_SELECT 	4 		// ASCII or Graphics select
#define B_RW 		2 		// Read/Write
#define B_DI 		1 		// Data or Instruction : 1 data, 0 Instr

#define LCD_ON 			0x3F // Display på
#define LCD_OFF 		0x3E // Av
#define LCD_SET_ADD 	0x40 // Set X adress (0 – 63)
#define LCD_SET_PAGE 	0xB8 // Set Y adress (0 – 7)
#define LCD_DISP_START	0xC0 // Start adress i display minne
#define LCD_BUSY 		0x80 // läsa ut busy status. R/W skall vara hög


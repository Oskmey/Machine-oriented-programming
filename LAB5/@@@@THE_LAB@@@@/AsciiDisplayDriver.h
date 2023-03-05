#pragma once

#define B_E 0x40
#define B_SELECT 4
#define B_RW 2
#define B_RS 1
void ascii_text_generator(void);
void ascii_init(void);
void ascii_write_cmd(unsigned char cmd);
void ascii_write_data(unsigned char data);
char ascii_read_controller( void );
void ascii_write_controller( unsigned char c );
char ascii_read_status( void );
char ascii_read_data( void );
void ascii_ctrl_bit_set( unsigned char x );
void ascii_ctrl_bit_clear( char x );
void clear_display(void);
void ascii_write_char(unsigned char data);
void ascii_gotoxy( int x, int y);
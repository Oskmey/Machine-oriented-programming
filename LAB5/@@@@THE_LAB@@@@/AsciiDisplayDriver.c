

#include "AsciiDisplayDriver.h"
#include "GPIO.h"


void ascii_init(void){
	delay_milli(1);
	ascii_write_cmd(0x38);
	delay_milli(1);
	ascii_write_cmd(0xe);
	delay_milli(1);
	clear_display();
	delay_milli(2);
	ascii_write_cmd(6);
	delay_milli(2);
}


void ascii_write_cmd(unsigned char cmd){
	ascii_ctrl_bit_clear( B_RS );
	ascii_ctrl_bit_clear( B_RW );
	ascii_write_controller(cmd);

}


void ascii_write_data(unsigned char data){
	ascii_ctrl_bit_set(B_RS);
	ascii_ctrl_bit_clear(B_RW);
	ascii_write_controller(data);
}



char ascii_read_controller( void ){
	PORT_E.MODER = 0x00005555;
	char c;
	ascii_ctrl_bit_set( B_E );
	delay_250ns();
	delay_250ns();
	c = PORT_E.IDRHIGH;
	ascii_ctrl_bit_clear( B_E );
	PORT_E.MODER  = 0x55555555;
	return c;
}

void ascii_write_controller( unsigned char c ){
	delay_milli(1);
	ascii_ctrl_bit_set( B_E );
	PORT_E.ODRHIGH = c; 
	delay_250ns();
	ascii_ctrl_bit_clear( B_E );
	delay_250ns();
}

char ascii_read_status( void ){
	char c;
	PORT_E.MODER = 0x00005555;
	ascii_ctrl_bit_set( B_RW );
	ascii_ctrl_bit_clear( B_RS );
	c = ascii_read_controller();
	PORT_E.MODER = 0x55555555;
	return c;
}

char ascii_read_data( void ){
	char c;
	PORT_E.MODER = 0x00005555;
	ascii_ctrl_bit_set( B_RW );
	ascii_ctrl_bit_set( B_RS );
	c = ascii_read_controller();
	PORT_E.MODER = 0x55555555;
	return c;
}

void ascii_ctrl_bit_set( unsigned char x ){ /* x: bitmask bits are 1 to set */
	char c;
	c = PORT_E.ODRLOW;
	PORT_E.ODRLOW = B_SELECT | x | c;
}

void ascii_ctrl_bit_clear( char x ){ /* x: bitmask bits are 1 to clear */
	char c;
	c = PORT_E.ODRLOW;
	c = c & ~x;
	PORT_E.ODRLOW = B_SELECT | c;
}

void clear_display(){
	while((ascii_read_status() & 0x80)== 0x80 );
	delay_micro(8);
	ascii_write_cmd(1);
	delay_milli(2);
}

void ascii_write_char(unsigned char data){
	while ( (ascii_read_status() & 0x80) == 0x80);
		delay_micro(8);
		ascii_write_data(data);
		delay_micro(43);
}

void ascii_gotoxy( int x, int y){
	int address;
	address = x - 1;
	if(y == 2){
		address = address + 0x40;
	}
	ascii_write_cmd(0x80 | address);
}

#pragma once
typedef volatile struct{     
	unsigned int MODER;         //In-out
	unsigned short OTYPER;	   //Push-open
	unsigned int :0;   //next address 
	unsigned int OSPEEDR;	   
	unsigned int PUPDR;
	union {				//Address of the input registers 
		unsigned short IDR;		//All of IDR
		struct{
			unsigned char IDRLOW;
			unsigned char IDRHIGH;
			unsigned short reserved; 
		};
	};
	union {				//Address of the output registers 
		unsigned short ODR;		//All of ODR
		struct{
			unsigned char ODRLOW;	
			unsigned char ODRHIGH;
			unsigned short reserved2;
		};
	};
	unsigned int BSRR;
	unsigned int LCKR :17; //only uses 17 bits 
	unsigned int :0;		
	unsigned int AFRL;
	unsigned int AFRH;
	
}GPIO;
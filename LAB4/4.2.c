/*
 * 	********INFO*********
 * 	Vi tilldelar PIN E3 till EXTI3, vilket innebär att om det kommer ström till pin 3 så tolkar processorn det som ett avbrott. 
 * 	FlipFlop skickar alltid en IRQ-signal till PIN 3, oavsett vilket IRQ som sker på enheten.   
 * 	I EXTI3_handler funktionen går vi igenom våra pins för att se vilket avbrott som har inträffat och försöker sedan "hantera" det.
 * 	
 *
 */
__attribute__((naked)) __attribute__((section (".start_section")) )
void startup ( void )
{
__asm__ volatile(" LDR R0,=0x2001C000\n");		/* set stack */
__asm__ volatile(" MOV SP,R0\n");
__asm__ volatile(" BL main\n");					/* call main */
__asm__ volatile(".L1: B .L1\n");				/* never return */
}
//_____________________________________________________________________________________________
#define SYSCFG ((volatile unsigned int*)(0x40013800))
#define SYSCFG_EXTICR1 ((volatile unsigned int*)(0x40013808))

#define EXTI_IMR ((volatile unsigned int*)(0x40013C00)) //ska datorn ta emot 
#define EXTI_FTSR ((volatile unsigned int*)(0x40013C0C)) //NEG flanktriggad
#define EXTI_RTSR ((volatile unsigned int*)(0x40013C08)) //POS flanktriggad
#define EXTI_PR ((volatile unsigned int*)(0x40013C14)) //PÅ-AV





//___VECTOR_TABLE_______________________________________________________________________________
#define SCB_VTOR ((volatile unsigned int*)(0xE000ED08))




//___INTERRPUT_SET-ENABLE_BIT___________________________________________________________________
#define NVIC_ISER0 ((volatile unsigned int*)(0xE000E100))




//___PORT_E_____________________________________________________________________________________
#define GPIO_E ((volatile unsigned int*)(0x40021000))
#define GPIO_IDRLOW_E ((volatile unsigned int*)(0x40021010))
#define GPIO_ODRLOW_E ((volatile unsigned int*)(0x40021014))




//___PORT_D_____________________________________________________________________________________
#define GPIO_D ((volatile unsigned int*)(0x40020C00))
#define GPIO_ODRLOW_D ((volatile unsigned char *)(0x40020C14))
#define GPIO_ODRHIGH_D ((volatile unsigned char *)(0x40020C15))



//______________________________________________________________________________________________
#define EXTI3_IRQ_BPOS (1<<3)
#define IRQ0 1
#define IRQ1 (1<<1)
#define IRQ2 (1<<2)
#define RTS_IRQ0 (1<<4)
#define RTS_IRQ1 (1<<5)
#define RTS_IRQ2 (1<<6)
#define ANY_DIODRAMP_VALUE 0xFF







volatile unsigned char count;

void EXTI3_handler(void){
	if(*EXTI_PR == EXTI3_IRQ_BPOS) //om EXIT3 är aktiv 
		*EXTI_PR |=~EXTI3_IRQ_BPOS; //Stäng av flag
		if(*GPIO_IDRLOW_E & IRQ0){
			*GPIO_ODRLOW_E |=RTS_IRQ0; //Skickar 1 till RTS 
			*GPIO_ODRLOW_E &=~RTS_IRQ0; //Stänger av RTS vi är alltså avbrottet är hanterat 
			count++;
		}
		if(*GPIO_IDRLOW_E & IRQ1){
			*GPIO_ODRLOW_E |=RTS_IRQ1;
			*GPIO_ODRLOW_E &=~RTS_IRQ1;
			count = 0;
		}
		if(*GPIO_IDRLOW_E & IRQ2){
			*GPIO_ODRLOW_E |=RTS_IRQ2;
			*GPIO_ODRLOW_E &=~RTS_IRQ2;
			if(*GPIO_ODRHIGH_D & ANY_DIODRAMP_VALUE){
				*GPIO_ODRHIGH_D = 0;
			}
			else{
				*GPIO_ODRHIGH_D = 0xFF;
			}
		}
	
}





void init_app(void){
	/* starta klockor port D och E */
	*((unsigned long*) 0x40023830) = 0x18;
/* starta klockor för SYSCFG */
	*((unsigned long*)0x40023844) |= 0x4000;
	
	*SCB_VTOR = 0x2001C000; //Vector Table 
	*((void(**)(void)) 0x2001C064) = EXTI3_handler;
	
	*SYSCFG_EXTICR1 &=~0xF000; // Vi nolställer EXTICR1 och har kvar resten 
	*SYSCFG_EXTICR1 |=0x4000; //PIN 3 på port D blir nu till lina
	
	*EXTI_IMR |= EXTI3_IRQ_BPOS; //Vi kan ta emot EXTI3 
	*EXTI_RTSR |= EXTI3_IRQ_BPOS;
	*EXTI_FTSR &=~ EXTI3_IRQ_BPOS;
	
	*NVIC_ISER0 |= (1<<9); //processon kan hantera EXTI3 
	
	*GPIO_E =0x55555500; // pin 0-3 är in pin 4-15 är out så att vi kan skicka RTS signaler till Flip
	*GPIO_D =0x55555555;	
	
}








void main(void){
	init_app();
	while(1){
		char c = count;
		*GPIO_ODRLOW_D = count;
	}
}


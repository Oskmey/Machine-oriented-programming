/*
 * 	********INFO*********
 * 	Vi tilldelar PIN E2 E1 E0 till EXTI2,EXTI1 och EXTI0, vilket innebär att om det kommer ström till någon pin så tolkar processorn det som ett avbrott. 
 * 	Det kan uppstå problem med simulatorn om det finns ett pågående avbrott innan init_app() har genomförts.
 * 	
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

#define EXTI2_IRQ_BPOS (1<<2)
#define EXTI1_IRQ_BPOS (1<<1)
#define EXTI0_IRQ_BPOS (1<<0)
#define EXTIX_IRQ_BPOS 0x7

#define EXTI_IMR ((volatile unsigned int*)(0x40013C00)) //ska datorn ta emot 
#define EXTI_FTSR ((volatile unsigned int*)(0x40013C0C)) //NEG flanktriggad
#define EXTI_RTSR ((volatile unsigned int*)(0x40013C08)) //POS flanktriggad
#define EXTI_PR ((volatile unsigned int*)(0x40013C14)) //PÅ-AV





//___VECTOR_TABLE_______________________________________________________________________________
#define SCB_VTOR ((volatile unsigned int*)(0xE000ED08))



//___INTERRPUT_SET-ENABLE_BIT___________________________________________________________________
#define NVIC_ISER0 ((volatile unsigned int*)(0xE000E100))
#define NVIC_EXTI2_IRQ_BPOS (1<<8)
#define NVIC_EXTI1_IRQ_BPOS (1<<7)
#define NVIC_EXTI0_IRQ_BPOS (1<<6)
#define NVIC_EXTIX_IRQ_BPOS 0x1C0

//___PORT_E_____________________________________________________________________________________
#define GPIO_E ((volatile unsigned int*)(0x40021000))
#define GPIO_IDRLOW_E ((volatile unsigned int*)(0x40021010))
#define GPIO_ODRLOW_E ((volatile unsigned int*)(0x40021014))




//___PORT_D_____________________________________________________________________________________
#define GPIO_D ((volatile unsigned int*)(0x40020C00))
#define GPIO_ODRLOW_D ((volatile unsigned char *)(0x40020C14))
#define GPIO_ODRHIGH_D ((volatile unsigned char *)(0x40020C15))



//______________________________________________________________________________________________
#define IRQ0 1
#define IRQ1 (1<<1)
#define IRQ2 (1<<2)
#define RTS_IRQ0 (1<<4)
#define RTS_IRQ1 (1<<5)
#define RTS_IRQ2 (1<<6)
#define ANY_DIODRAMP_VALUE 0xFF







volatile unsigned char count;

void EXTI2_IRQ_handler(void){
	if(*EXTI_PR == EXTI2_IRQ_BPOS) //om EXIT0 är aktiv 
		*EXTI_PR |=~EXTI2_IRQ_BPOS; //Stäng av flag
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
void EXTI1_IRQ_handler(void){
	if(*EXTI_PR == EXTI1_IRQ_BPOS) //om EXIT1 är aktiv 
		*EXTI_PR |=~EXTI1_IRQ_BPOS; //Stäng av flag
		if(*GPIO_IDRLOW_E & IRQ1){
			*GPIO_ODRLOW_E |=RTS_IRQ1;
			*GPIO_ODRLOW_E &=~RTS_IRQ1;
			count = 0;
		}
}
void EXTI0_IRQ_handler(void){
		if(*EXTI_PR == EXTI0_IRQ_BPOS) //om EXIT2 är aktiv 
		*EXTI_PR |=~EXTI0_IRQ_BPOS; //Stäng av flag
		if(*GPIO_IDRLOW_E & IRQ0){
			*GPIO_ODRLOW_E |=RTS_IRQ0; //Skickar 1 till RTS 
			*GPIO_ODRLOW_E &=~RTS_IRQ0; //Stänger av RTS 
			count++;
		}
}

void EXTI2_config(void){
	*((void(**)(void)) 0x2001C060) = EXTI2_IRQ_handler;
	
}


void EXTI1_config(void){
	*((void(**)(void)) 0x2001C05C) = EXTI1_IRQ_handler;
}


void EXTI0_config(void){
	*((void(**)(void)) 0x2001C058) = EXTI0_IRQ_handler;
}


void init_app(void){
	*((unsigned long*) 0x40023830) = 0x18; 	/* starta klockor port D och E */
	*((unsigned long*)0x40023844) |= 0x4000;/* starta klockor för SYSCFG */
	*SCB_VTOR = 0x2001C000; //Vector Table 
	EXTI2_config();
	EXTI1_config();
	EXTI0_config();
	
	
	*SYSCFG_EXTICR1 &=~0xFFFF; 
	*SYSCFG_EXTICR1 |=0x4444; 
	
	*EXTI_IMR |= EXTIX_IRQ_BPOS  ;
	*EXTI_RTSR |= EXTIX_IRQ_BPOS;
	*EXTI_FTSR &=~ EXTIX_IRQ_BPOS;
	
	*NVIC_ISER0 |= NVIC_EXTIX_IRQ_BPOS; //processon kan hantera EXTI2 EXTI1 EXTI0
	
	*GPIO_E =0x55555500; // pin 0-3 är in pin 4-15 är out så att vi kan skicka RTS signaler till Flip
	*GPIO_D =0x55555555;	
	
}

void main(void){
	init_app();
	while(1){
		*GPIO_ODRLOW_D = count;
	}
}

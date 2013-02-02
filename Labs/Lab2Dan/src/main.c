#include "LPC17xx.h"
#define LED0 (1<<19)
#define LED1 (1<<20)
#define LED2 (1<<21)

//Button P0.2 has priority 0
//Butotn P0.3 has priority 1
int i=0;
int n=0;
int flag = 0;

void EINT1_IRQHandler(void)
{
	LPC_GPIO1 ->FIOPIN = LED0 | ~LED0; // turn off all leds
	while(1){

		LPC_GPIO1 -> FIOPIN ^= LED1;
		for(n=0;n<900000;n++);

		//blink LED1
	}

}

void EINT3_IRQHandler(void) //Need to change to interrupt 3
{
	LPC_GPIO1 ->FIOPIN = LED0 | ~LED0; // turn off all leds
	while(1){


		LPC_GPIO1 -> FIOPIN ^= LED2;
		for(n=0;n<900000;n++);
		//blink LED2
	}
	LPC_GPIOINT -> IO0IntClr |= (1<<2);
}

int main(void) {
	//initialize everything

	NVIC_SetPriority(EINT3_IRQn,0);
	NVIC_SetPriority(EINT1_IRQn,1);
	LPC_GPIOINT -> IO0IntEnR |= (1<<2);
	LPC_GPIO1 -> FIODIR |= LED0;
	LPC_GPIO1 -> FIODIR |= LED1;
	LPC_GPIO1 -> FIODIR |= LED2;
	NVIC_EnableIRQ(EINT1_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);
	LPC_GPIO1 -> FIOPIN = ~LED0;

	while(1){

		flag = ((~LPC_GPIO0 -> FIOPIN) & (1<<3)) == (1<<3);
		// Blink LED0
		LPC_GPIO1 -> FIOPIN ^= LED0;
		for(n=0;n<900000;n++);

		if(flag == 1) NVIC_SetPendingIRQ(EINT1_IRQn);


	}

	return 0;
}

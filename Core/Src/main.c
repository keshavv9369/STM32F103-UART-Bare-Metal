#include "stm32f103xb.h"
#include "m3_cmsis_serial.h"
#include<main.h>

char hello[] = {'H', 'E', 'L', 'L', 'O', '\r', '\n'};
volatile uint32_t mstick = 0;

void delay_ms(uint32_t ms);

int main(){

		systick_Init();
		/// serial_usart1_Init();
		USART_Init();

	while(1){

		for(int i = 0; i < 7; i++)
		{
		    while(!(USART1->SR & USART_SR_TXE));  // Wait until transmit register empty
		    USART1->DR = hello[i];
		}
		delay_ms(1000);

	}
}

void delay_ms(uint32_t ms){
	uint32_t now =mstick;
	while((mstick-now) < ms);
}

void systick_Init(void){
	SysTick->LOAD =7999;
	SysTick->VAL =0;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | // Use processor clock
	                SysTick_CTRL_TICKINT_Msk   | // Enable interrupt
	                SysTick_CTRL_ENABLE_Msk;     // Enable counter

}

void USART_Init(void)
{
    /* Enable clocks */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    /* PA9 = TX : Alternate Function Push-Pull, 50 MHz */
    GPIOA->CRH &= ~(0xF << 4);
    GPIOA->CRH |=  (0xB << 4);

    /* PA10 = RX : Floating input */
    GPIOA->CRH &= ~(0xF << 8);
    GPIOA->CRH |=  (0x4 << 8);

    /* Reset USART configuration */
    USART1->CR1 = 0;
    USART1->CR2 = 0;
    USART1->CR3 = 0;

    /* Baud rate = 9600 at 8 MHz */
    USART1->BRR = 0x0341;

    /* Enable transmitter */
    USART1->CR1 |= USART_CR1_TE;

    /* Optional: Enable receiver too */
    USART1->CR1 |= USART_CR1_RE;

    /* Enable USART */
    USART1->CR1 |= USART_CR1_UE;
}

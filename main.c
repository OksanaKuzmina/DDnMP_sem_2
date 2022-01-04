
#include "main.h"

#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */


/*Определение прототипов функциий*/

void change_led_state_IT_exemple_3(void);
void init_IT_for_exemple_3(void);
int tumbler (void);
void delay (uint32_t ticks);

uint32_t pin_state = 0;
uint32_t ves = 0;
uint32_t i;
int main(void)
{
		/*Включение тактирования для порта А и C*/
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN_Msk | RCC_APB2ENR_IOPCEN_Msk;
    
    /* Включение на вход(считывание с тумблера) Включение порта С пины 0,1,2,3,15,14,7,12  */
    /* Установка регистра CRL битов MODE6[1:0] на тип входа pull-down(подключение ножки тумблера) */
    GPIOC->CRL = (GPIOC->CRL) & (  ~(GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1 | GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1 | GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1| GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1));
	
	/* Установка регистра CRL битов CNF6[1:0]  на тип входа pull-down(подключение ножки тумблера) */
	GPIOC->CRL = (GPIOC->CRL) & ( ~( GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0 | GPIO_CRL_CNF3_0 | GPIO_CRL_CNF2_0 | GPIO_CRL_CNF7_0));
    
	GPIOC->CRL = (GPIOC->CRL) | ( GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 | GPIO_CRL_CNF3_1 | GPIO_CRL_CNF2_1 | GPIO_CRL_CNF7_1);
    

    GPIOC->CRH = (GPIOC->CRH) & (  ~(GPIO_CRH_MODE12_0 | GPIO_CRH_MODE12_1 | GPIO_CRH_MODE14_0 | GPIO_CRH_MODE14_1 | GPIO_CRH_MODE15_0 | GPIO_CRH_MODE15_1));
	
	/* Установка регистра CRL битов CNF6[1:0]  на тип входа pull-down(подключение ножки тумблера) */
	GPIOC->CRH = (GPIOC->CRH) & ( ~( GPIO_CRH_CNF12_0 | GPIO_CRH_CNF14_0 | GPIO_CRH_CNF15_0));
    
	GPIOC->CRH = (GPIOC->CRH) | ( GPIO_CRH_CNF12_1 | GPIO_CRH_CNF14_1 | GPIO_CRH_CNF15_1);
    
    
    
     /* Включение на выход(считывание с тумблера) Включение порта A пины 0,1,4,6,7,9,8,10 */
    GPIOA->CRL = (GPIOA->CRL) & (  ~(GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1 | GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1 | GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1 | GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1| GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1));
	
	/* Установка регистра CRL битов CNF6[1:0]  на тип входа pull-down(подключение ножки тумблера) */
	GPIOA->CRL = (GPIOA->CRL) & ( ~( GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0 | GPIO_CRL_CNF2_0 | GPIO_CRL_CNF3_0 | GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0 | GPIO_CRL_CNF6_0 | GPIO_CRL_CNF7_0));
    
	GPIOA->CRL = (GPIOA->CRL) | ( GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 | GPIO_CRL_CNF2_1 | GPIO_CRL_CNF3_1 | GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1 | GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1);
    
    GPIOA->CRH = (GPIOA->CRH) & (  ~(GPIO_CRH_MODE8_0 | GPIO_CRH_MODE8_1 | GPIO_CRH_MODE9_0 | GPIO_CRH_MODE9_1 | GPIO_CRH_MODE10_0 | GPIO_CRH_MODE10_1));
	
	// Установка регистра CRL битов CNF6[1:0]  на тип входа pull-down(подключение ножки тумблера) /
	GPIOA->CRH = (GPIOA->CRH) & ( ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0 | GPIO_CRH_CNF10_0));
    
	GPIOA->CRH = (GPIOA->CRH) | (  GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1 |GPIO_CRH_CNF10_1);
    
    /* Подключение кнопки*/
	GPIOC->CRH = (GPIOC->CRH) & ( ~( GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1));
	/* Установка регистра CRL битов CNF13[1:0] на тип входа pull-up */
    GPIOC->CRH = ((GPIOC->CRH) | ( GPIO_CRH_CNF13_0 | GPIO_CRH_MODE13_1));
	GPIOC->ODR = ((GPIOC->ODR) | ( GPIO_PIN_13));
	
	
	/*Инициализация прерываний для*/
	init_IT_for_exemple_3();
  while (1)
  {
            i = 255; //начальное значение счетчика
            change_led_state_IT_exemple_3();
  }
}

int tumbler (void)     /*Пожпрограмма считывания значений с тумблера*/ 
{
    ves = 0;
	ves |= GPIOC->IDR & GPIO_PIN_0;
    ves |= GPIOC->IDR & GPIO_PIN_1;
	ves |= GPIOC->IDR & GPIO_PIN_2;
    ves |= GPIOC->IDR & GPIO_PIN_3;
    ves |= GPIOC->IDR & GPIO_PIN_7 >> 3;
    ves |= GPIOC->IDR & GPIO_PIN_12 >> 7;
    ves |= GPIOC->IDR & GPIO_PIN_14 >> 8;
    ves |= GPIOC->IDR & GPIO_PIN_15 >> 8;
    return(ves);
}
void change_led_state_IT_exemple_3(void)
{
    //цикл инкреминирующего счетчика
		for (; i > 1; i--)
    {
    
        GPIOA->BSRR = i;
         delay (100000);
         GPIOA->BRR = i;
        
    }   
        
}

void init_IT_for_exemple_3(void)
{
	/****************************************************************/
	/*Включение прерываний от пина 13*/
	/****************************************************************/
	//Включение тактирования на блок альтернативных функций
	RCC->APB2ENR = RCC->APB2ENR | RCC_APB2ENR_AFIOEN;
	//Разрешить прерывание 13 пина порта С
	AFIO->EXTICR[3] = 0x0020;
	//Разрешить прерывание 13 линии
	EXTI->IMR|=(EXTI_IMR_MR13);
	EXTI->EMR|=(EXTI_EMR_MR13);
	
	//Прерывание 13 линии по спадающему фронту фронту
	EXTI->RTSR|=(EXTI_RTSR_TR13);
	
	/* Разрешение прерываний */
	NVIC->ISER[(((uint32_t)EXTI15_10_IRQn) >> 5UL)] = (uint32_t)(1UL << (((uint32_t)EXTI15_10_IRQn) & 0x1FUL));
}

void delay (uint32_t ticks)
{
	for (uint32_t i = 0; i < ticks; i++)
	{
	}
}

/*Обработчик прерывания по линии EXTI15_10*/

void EXTI15_10_IRQHandler (void)
{
		EXTI->PR |= GPIO_PIN_13;
		if (pin_state == 0)
		{
			ves = tumbler();
            pin_state = 1;
		}
		if (pin_state == 1)
		{
			i = 0;
            pin_state = 2;
		}
        if (pin_state == 2)
		{
           GPIOA->BRR =  0 ;
            pin_state = 3;
		}
        if (pin_state == 3)
		{
           i = ves ;
            pin_state = 0;
		}
}

void HardFault_Handler (void)
{
	while(1)
	{}
}


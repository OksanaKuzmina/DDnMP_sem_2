
#include "stm32f10x.h"
#include <stdio.h>		
#include <stdint.h>		
#include <string.h>

#define GPIO_PIN_0                 ((uint16_t)0x0001)  
#define GPIO_PIN_1                 ((uint16_t)0x0002)  
#define GPIO_PIN_2                 ((uint16_t)0x0004)  
#define GPIO_PIN_3                 ((uint16_t)0x0008)  
#define GPIO_PIN_4                 ((uint16_t)0x0010)  
#define GPIO_PIN_5                 ((uint16_t)0x0020)  
#define GPIO_PIN_6                 ((uint16_t)0x0040) 
#define GPIO_PIN_7                 ((uint16_t)0x0080) 
#define GPIO_PIN_8                 ((uint16_t)0x0100)  
#define GPIO_PIN_9                 ((uint16_t)0x0200)  
/*Определение прототипов функциий*/
void init_usart(void);
void change_led_state_IT_exemple_3(void);
void delay (uint32_t ticks);
uint32_t N, i, state, p;  
    // функция включения прерываний
void interrupt_USAT1(void);
int main(void)              
{   
    p = 0;
    char data[16] = "";                           // массив для записи значений принятых по средством USART 
    char data2[] = "";                          // массив для записи значения N
    char data3[] = "Взвод ВЦ18-01АСУ, Кузьмина О.Н., Разработка декрементирующего двоичного счетчика(N->0) с управлением по интерфейсу UART , команды START, STOP, RESET, HELP, FREQUENCY = CODE";    
    /*Включение тактирования для порта С */
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    interrupt_USAT1();//Включение прерывания по USART
     /* Включение порта C пины 0-7 для светодидодов на выход push-pull*/
    GPIOC->CRL = (GPIOC->CRL) | (GPIO_CRL_MODE0_0 | GPIO_CRL_MODE0_1 | GPIO_CRL_MODE1_0 | GPIO_CRL_MODE1_1 | GPIO_CRL_MODE2_0 | GPIO_CRL_MODE2_1 | GPIO_CRL_MODE3_0 | GPIO_CRL_MODE3_1 | GPIO_CRL_MODE4_0 | GPIO_CRL_MODE4_1 | GPIO_CRL_MODE5_0 | GPIO_CRL_MODE5_1 | GPIO_CRL_MODE6_0 | GPIO_CRL_MODE6_1| GPIO_CRL_MODE7_0 | GPIO_CRL_MODE7_1);	
	GPIOC->CRL = (GPIOC->CRL) & ( ~( GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0 | GPIO_CRL_CNF2_0 | GPIO_CRL_CNF3_0 | GPIO_CRL_CNF4_0 | GPIO_CRL_CNF5_0 | GPIO_CRL_CNF6_0 | GPIO_CRL_CNF7_0 | GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1 | GPIO_CRL_CNF2_1 | GPIO_CRL_CNF3_1 | GPIO_CRL_CNF4_1 | GPIO_CRL_CNF5_1 | GPIO_CRL_CNF6_1 | GPIO_CRL_CNF7_1));   

    init_usart();                               //функция настройки USART              
	              N = 255; //начальное значение счетчика		
                  i = N; //начальное значение счетчика
                  state = 37;  //пока ничего не передали просто считать тики
    while (1)
          {
              while ((USART1->SR & USART_SR_RXNE) == 0)  {}     //условие считывания данных через USART    (стоповый бит)  
              //     USART1->SR &= ~USART_SR_RXNE;       
                 data[0] = USART1->DR;                     //запись значения переданого через USART
                   data[1] = USART1->DR;
                   data[2] = USART1->DR;
                 int16_t rr=USART1->SR;
                 if (data[0] == 'A')  
                     state = 0;
                 if (data[0] == 'O')
                     state = 2;
                 if (data[0] == 'S')
                     state = 3;
                 if (data[0] == 'E')
                     state = 1;
                 if (data[0] == 'L')
                     state = 4;
    
              switch(state)                        // в зависимости от нажатия кнопки выполняются разные case
                {case 0:                                          
                    change_led_state_IT_exemple_3();            //декреминирующий счетчик
                 break;                             
                case 1: //1 нажатие считывание значения счетчика                             
                    data2[0] = data[12];                            //запись переданного значения
                    N = atoi(data);                               //изменение типа строки в тип числа
                    i = N;
                    state = 0;
                 break;                                      
                 case 2: //2 нажатие остановка счетчика, просто считает тики                                
                    delay(100000);                                         
                 break;                                    
                 case 3: //3 нажатие  сброс счетчика
                     GPIOA->ODR = 0;                                //выключает все светодиоды
                 delay(100000);
                 break; 
                 case 4:  
                 while ((USART1->SR & USART_SR_TXE) == 0)       //условие считывания данных через UASRT передача при help                    
                     {   
                         p++;                                            //счетчик чтоб передавть буковки
                        USART1->DR = data3[p];                       //передача символов через USART
                     } 
              p = 0;
                   state = 2;  
                 break;    
          }
                  
}
}

void change_led_state_IT_exemple_3(void)    //Функция обрабатывает значение счетчика и выводит его значение на светодиоды
{
    //цикл инкреминирующего счетчика
		for (; i > 1; i--)
    {
         GPIOC->ODR = i; 
         delay (1000000);    
    }   
      i = N;  
}

void init_usart(void) //Функция настройки USART(PA9(TX) и PA10(RX))  
{
    // настройка вывода PA9 (TX1) на режим альтернативной функции с активным выходом
    GPIOA->CRH &= (~GPIO_CRH_CNF9_0);                      //установка 0 в регистре CRH в бите CNF9_0(для передачи)
    GPIOA->CRH |= (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9);      //установка 1 в регистре CRH в биты MODE9 и  CNF9_1

    // настройка вывода PA10 (RX1) на режим входа с подтягивающим резистором
    GPIOA->CRH &= (~GPIO_CRH_CNF10_0);                      //установка 0 в регистре CRH в бите CNF10_0(для приема)
    GPIOA->CRH |= GPIO_CRH_CNF10_1;                         //установка 1 в регистре CRH в бите CNF10_1

    // конфигурация UART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // включаем тактирование UART1  
    USART1->CR1 = USART_CR1_UE; // разрешаем использовать(включаем) USART1, сбрасываем остальные биты
    USART1->BRR = 7500; // скорость передачи, с которой можем отправлять 9600 бод
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE ; // разрешаем приемник и передатчик
}
/************Функция задержки************/
void delay (uint32_t ticks)
{
	for (uint32_t i = 0; i < ticks; i++)
	{
	}
}
void interrupt_USAT1(void)
{
/* разрешаем прерывание по приему */
USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE; 
/*разрешение прерывания USART2 в контроллере прерываний*/
NVIC_EnableIRQ (USART1_IRQn);
}

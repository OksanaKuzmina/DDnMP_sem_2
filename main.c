#include <stdio.h>		/* Заголовочный файл объявляет несколько целочисленных типов и макросов */
#include <stdint.h>		/* Заголовочный файл объявляет несколько целочисленных типов и макросов */
/*
ЗАДАНИЕ:
Сформировать массив из 10-ти двухбайтных чисел. Переписать во второй массив все отрицательные числа. Их количество поместить в регистр R5. 
*/
// Инициализируем первичный массив с числами
int16_t array_original [] = {1,-2,0,-6,7,8,-9,43,-7,9};
int funcwrite (int d);
int funcminus (int b);
//Экспортируем функцию	из main.s написанную на ассемблере.
extern int array_treatment_asm (int16_t* array_ptr, size_t array_size, int16_t* new_array_ptr );	
	
// Объявляем пустой массив для передачи его адреса в функцию array_treatment_asm
int16_t new_array [sizeof(array_original)/sizeof(int32_t)]= {0};

int main (void){
int16_t a;
    
	/*Вызываем функцию array_treatment_asm, тело которой описано в файле main_1.s. 
	Так как, в языке ассемблера не функций malloc() и вообще нет механизма выделения данных из кучи, 
	то мы заранее выделяем место в оперативной памяти для обработанного массива, 
	поэтому нам необходимо передать адрес нового массива в функцию. 
	Размерность массива такая же как у оригинального массива.*/
	

	a = array_treatment_asm(array_original, sizeof(array_original)/sizeof(int16_t), new_array);
    a=0;
	
    
        for(int i=0; i<9; i++ ){
        a = funcminus(array_original[i]);
            
	}

     return(a);   
}

int funcminus (int b)
    {
int c;        
        if( b <0)
       c = funcwrite(c);
        
      return (c);   
    }
int funcwrite (int d)
{                   
      d=d++;
	return (d);
}
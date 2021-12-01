Stack_Size EQU 0x400
        AREA STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem SPACE Stack_Size
__initial_sp

; <h> Heap Configuration
; <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
Heap_Size EQU 0x200
                AREA HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem SPACE Heap_Size
__heap_limit
                PRESERVE8
                THUMB
; Vector Table Mapped to Address 0 at Reset
                AREA RESET, DATA, READONLY
                            DCD __initial_sp ; Top of Stack
                            DCD Reset_Handler ; Reset Handler
                AREA |.text|, CODE, READONLY
                    
; Reset handler
Reset_Handler PROC
        IMPORT __main
                LDR R0, =__main
                BX R0
; B main_asm
                ENDP
                IMPORT __use_two_region_memory
                EXPORT __user_initial_stackheap
                    
__user_initial_stackheap
                LDR R0, = Heap_Mem
                LDR R1, =(Stack_Mem + Stack_Size)
                LDR R2, = (Heap_Mem + Heap_Size)
                LDR R3, = Stack_Mem
                BX LR
                
                ALIGN
                    
                END
            ; Запись адреса переменной "result" в регистр "R2"
            LDR R2, =result
            ; Запись значения регистра R1 в память по адресу записанного в регистре R2
            STRB R1, [R2] ; result = a
            ENDP ; Конец функции main
            END ; Конец файла
				


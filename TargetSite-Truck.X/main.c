#include "mcc_generated_files/mcc.h"
#include <stdbool.h>

bool flag;
void send(unsigned char data);
void recieve_ang(uint8_t data, uint8_t *ch, uint8_t *ang);


void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    
    ANSELA = 0x0;    
    ANSELB = 0x0;
    
    //USART setting
    //TX on
    TXSTA = 0x02;
    //RC on
    RCSTA = 0x90;
    //BAUDCON 16bit
    BAUDCON = 0x08;
    //BRGH = 0, BRG16 = 1 9600bit mode
    SPBRG = 51;
    
    //interrupt setting
    //interrupt flg clear
    PIR1bits.RCIF = 0;
    
    //USART recive interrupt enable
    PIE1bits.RCIE = 1;
    PEIE = 1;
    GIE = 1;

    while (1)
    {
        // Add your application code
    }
}


/**
 * send data
 * @param data
 */
void send(unsigned char data){
    while(!TXSTAbits.TRMT);
    TXREG = data;
}


/**
 * interrupt func
 */
void __interrupt() isr(void){
    if(PIR1bits.RCIF){
        //flg clear
        PIR1bits.RCIF = 0;
        //error
        if((RCSTAbits.OERR) || (RCSTAbits.FERR)){
            RCSTA = 0;
            RCSTA = 0x90;
        }else{
        //not error
            if(flag){
                LATA = 0x01;
                flag = false;
            }else{
                LATA = 0x0;
                flag = true;
            }
            
            uint8_t data = RCREG;
            send(data);                                     
        }
    }
}
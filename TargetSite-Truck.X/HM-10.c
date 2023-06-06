/*
 * File:   HM-10.c
 * Author: george
 *
 * Created on June 6, 2023, 8:33 PM
 */


#include <xc.h>
#include "./HM-10.h"

/**
 * HM-10を初期化
 * ピンの設定
 * 割り込みの許可
 */
void initialize_hm10(){
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
}
/*
 * File:   Led.c
 * Author: george
 *
 * Created on June 6, 2023, 8:50 PM
 */


#include <xc.h>
#include "./Led.h"

#define _XTAL_FREQ 8000000

void initialize_led(Led *p){
    TRISB &= ~p->activate_pin;
    TRISB &= ~p->status_pin;
    
    low_activate_led(p);
    low_status_led(p);
}

/**
 * 起動用LEDを光らす
 * @param p
 */
void high_activate_led(Led *p){   
    LATB |= p->activate_pin;
}
/**
 * 起動用LEDを消す
 * @param p
 */
void low_activate_led(Led *p){
    LATB &= ~p->activate_pin;
}
/**
 * 起動用LEDを点滅させる
 * @param p
 * @param interval 点滅の間隔
 */
void blink_activate_led(Led *p){
    for(uint8_t i = 0; i < BLINK_COUNT; i++){
        high_activate_led(p);        
        __delay_ms(BLINK_INTERVAL_MS);
        low_activate_led(p);
        __delay_ms(BLINK_INTERVAL_MS);
    }
}
/**
 * ステータスLEDを光らす
 * @param p
 */
void high_status_led(Led *p){
    LATB |= p->status_pin;
}
/**
 * ステータスLEDを消す
 * @param p
 */
void low_status_led(Led *p){
    LATB &= ~p->status_pin;
}
/**
 * ステータスLEDを点灯させる
 * @param p
 * @param interval 点灯の間隔
 */
void blink_status_led(Led *p){
    for(uint8_t i = 0; i < BLINK_COUNT; i++){
        high_status_led(p);        
        __delay_ms(BLINK_INTERVAL_MS);
        low_status_led(p);
        __delay_ms(BLINK_INTERVAL_MS);
    }
}
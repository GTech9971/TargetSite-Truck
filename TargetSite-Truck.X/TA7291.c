#include "TA7291P.h"

static void set_input1_pin_low(TA7291P *p){
    LATA &= ~p->input1_pin;
}
static void set_input1_pin_high(TA7291P *p){
    LATA |= p->input1_pin;
}

static void set_input2_pin_low(TA7291P *p){
    LATA &= ~p->input2_pin;
}
static void set_input2_pin_high(TA7291P *p){
    LATA |= p->input2_pin;
}

/**
 * ピンのANSEL,TRISの設定
 * @param p
 */
void initialize(TA7291P *p){    
    //input1_pin
    //input2_pin
    //vref_pin
    //出力設定(input:1, output:0)
    TRISA &= ~p->input1_pin;
    TRISA &= ~p->input2_pin;
    TRISA &= ~p->vref_pin;
    
    //vrefピンのアナログ設定(analog:1, digital:0)
    ANSELA |= p->vref_pin;
    
    //PWM初期化
    // CCP3M PWM; DC3B 3; 
	CCP3CON = 0x3C;    
	// CCPR3L 127; 
	CCPR3L = 0x7F;    
	// CCPR3H 0; 
	CCPR3H = 0x00;    
	// Selecting Timer 2
	CCPTMRS0bits.C3TSEL = 0x0;
    
    //Timer2 初期化
    // PR2 255; 
    PR2 = 0xFF;
    // TMR2 0; 
    TMR2 = 0x00;
    // Clearing IF flag.
    PIR1bits.TMR2IF = 0;
    // T2CKPS 1:1; T2OUTPS 1:1; TMR2ON on; 
    T2CON = 0x04;
    
}

/**
 * モーターのスピードを設定する
 * @param p
 * @param speed
 */
void set_speed(TA7291P *p, uint16_t speed){
    p->speed = speed;
    pwm_load_duty_value(p->speed);    
}

/**
 * pwmのデューティー比を変更する
 * @param duty_value 0~1023
 */
static void pwm_load_duty_value(uint16_t duty_value){
    // Writing to 8 MSBs of pwm duty cycle in CCPRL register
    CCPR3L = ((duty_value & 0x03FC)>>2);
    
   // Writing to 2 LSBs of pwm duty cycle in CCPCON register
    CCP3CON = ((uint8_t)(CCP3CON & 0xCF) | ((duty_value & 0x0003)<<4));
}

/**
 * モーター停止
 * @param p
 */
void stop(TA7291P *p){
    set_input1_pin_low(p);
    set_input2_pin_low(p);
    
    set_speed(p, 0);
}

/**
 * モーター直進
 * @param p
 * @param value
 */
void forward(TA7291P *p, uint16_t value){
    set_input1_pin_high(p);
    set_input2_pin_low(p);
    
    set_speed(p, value);
}

/**
 * モーター後退
 * @param p
 * @param value
 */
void back(TA7291P *p, uint16_t value){    
    set_input1_pin_low(p);
    set_input2_pin_high(p);
    
    set_speed(p, value);
}

/**
 * モーターブレーキ
 * @param p
 */
void brake(TA7291P *p){
    set_input1_pin_high(p);
    set_input2_pin_high(p);
}
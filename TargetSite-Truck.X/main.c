#include "mcc_generated_files/mcc.h"
#include <stdbool.h>
#include "./HM-10.h"
#include "./Led.h"
#include "TruckCommand.h"
#include "Truck.h"

Truck truck;
bool status_led_flag = false;

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    ANSELA = 0x0;    
    ANSELB = 0x0;
        
    Led led = {0x80, 0x40};
    initialize_led(&led);
    //起動用LED点灯
    blink_activate_led(&led);
    
    //ステータス用LED点灯
    blink_status_led(&led);
    
    initialize_hm10();
    
    /** input1, input2, vrefpin, speed */
    TA7291P driver = {0x01, 0x02, 0x08, 0x00};
    initialize(&driver);
    
    //トラック初期化
    truck.driver = &driver;
    truck.led = &led;
   
    while (1)
    {
        // DEBUG
//        if(status_led_flag == false){
//            high_status_led(truck.led);
//            status_led_flag = true;
//        }else{
//            low_status_led(truck.led);
//            status_led_flag = false;
//        }
//        uint8_t data = 0x00;
//        TruckCommand truck_cmd = {STOP, NONE, 0};
//        create_command(data, &truck_cmd);
//            
//        execute_command(&truck, &truck_cmd);
    }
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
            if(status_led_flag == false){
                high_status_led(truck.led);
                status_led_flag = true;
            }else{
                low_status_led(truck.led);
                status_led_flag = false;
            }
            uint8_t data = RCREG;
            TruckCommand truck_cmd = {STOP, NONE, 0};
            create_command(data, &truck_cmd);
            
            execute_command(&truck, &truck_cmd);
        }
    }
}
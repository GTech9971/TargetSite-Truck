#include "mcc_generated_files/mcc.h"
#include <stdbool.h>
#include "./HM-10.h"
#include "./Led.h"
#include "TruckCommand.h"
#include "Truck.h"

Truck truck;

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    ANSELA = 0x0;    
    ANSELB = 0x0;
        
    Led led = {0x80, 0x40};
    initialize_led(&led);
    //起動用LED点灯
    blink_activate_led(&led, 100);
    
    initialize_hm10();
    
    /** input1, input2, vrefpin, speed */
    TA7291P driver = {0x01, 0x00, 0x03, 0x00};
    //トラック初期化
    truck = {&driver, &led};
   
    while (1)
    {
        // Add your application code
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
            uint8_t data = RCREG;
            TruckCommand truck_cmd = {Command.STOP, SpeedMode.NONE, 0};
            create_command(data, &truck_cmd);
        }
    }
}
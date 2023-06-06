#include "mcc_generated_files/mcc.h"
#include <stdbool.h>
#include "./HM-10.h"
#include "./Led.h"
#include "TruckCommand.h"


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
            TruckCommand truck_cmd = create_command(data);
            execute_command(&truck_cmd);
        }
    }
}
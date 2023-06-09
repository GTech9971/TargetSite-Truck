/*
 * File:   Truck.c
 * Author: george
 *
 * Created on June 7, 2023, 7:48 PM
 */


#include <xc.h>
#include "Truck.h"
#include "TA7291P.h"


/**
 * コマンドを実行する
 * @param p
 */
void execute_command(Truck *p, const TruckCommand *command){
    uint16_t speed = calc_speed(command->speed);
    
    switch(command->cmd){
        case STOP:{
            stop(p->driver);
            break;
        }case FORWARD:{
            forward(p->driver, speed);
            break;
        }case BACK:{
            back(p->driver, speed);
            break;
        }case BRAKE:{
            brake(p->driver);
            break;
        }default:{
            stop(p->driver);
            break;
        }
    }
}

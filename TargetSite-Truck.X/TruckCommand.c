/*
 * File:   TruckCommand.c
 * Author: george
 *
 * Created on June 7, 2023, 8:19 PM
 */


#include <xc.h>
#include "TruckCommand.h"

/**
 * コマンドのスピード(0~10)から0~1023の値に変換する
 * @param p
 * @return 
 */
uint16_t calc_speed(const uint8_t input) {
    if(input == 0){return 0;}
    if(input >= 10){return 1023;}
    uint16_t value = (input * 1023) / 10;
    return value;
}

/**
 * 受信データからコマンドを生成する
 * @param data 受信データ
 * @return コマンド
 */
void create_command(const uint8_t data, TruckCommand *command){
    //cmd
    uint8_t cmd_data = data >> 6;
    if(cmd_data & 0x00){
        command->cmd = STOP;
    }else if(cmd_data & 0x02){
        command->cmd = FORWARD;
    }else if(cmd_data & 0x01){
        command->cmd = BACK;
    }else if(cmd_data & 0x03){
        command->cmd = BRAKE;
    }else{
        //不正データ
        command->cmd = STOP;
    }
    
    //INC/DEC/NONE
    //TODO
    command->speedMode = NONE;

    //Speed    
    command->speed = data & 0x0F;
}
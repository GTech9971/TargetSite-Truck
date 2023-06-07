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
    // 入力値の範囲を0〜1に正規化
    float normalizedInput = (float)(input - 0) / (float)(10 - 0);
  
    // 0〜1の範囲をoutputMin〜outputMaxの範囲に変換
    uint16_t mappedValue = (uint16_t)(normalizedInput * (1023 - 0) + 0);
  
    return mappedValue;
}

/**
 * 受信データからコマンドを生成する
 * @param data 受信データ
 * @return コマンド
 */
void create_command(const uint8_t data, TruckCommand *command){
    //cmd
    const uint8_t cmd_data = data >> 6;
    if(cmd_data & 0x00){
        command->cmd = Command.STOP;
    }else if(cmd_data & 0x02){
        command->cmd = Command.FORWARD;
    }else if(cmd_data & 0x01){
        command->cmd = Command.BACK;
    }else if(cmd_data & 0x03){
        command->cmd = Command.BRAKE;
    }else{
        //不正データ
        command->cmd = Command.STOP;
    }
    
    //INC/DEC/NONE
    //TODO
    command->speedMode = SpeedMode.NONE;

    //Speed    
    command->speed = data & 0x0F;
}
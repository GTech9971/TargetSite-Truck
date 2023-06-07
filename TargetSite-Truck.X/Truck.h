#pragma once

#include "TruckCommand.h"
#include "TA7291P.h"
#include "Led.h"

typedef struct{
    TA7291P *driver;
    Led *led;
} Truck;

/**
 * コマンドを実行する
 * @param p
 */
void execute_command(Truck *p, const TruckCommand *cmd);
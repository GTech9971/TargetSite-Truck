#pragma once

#define BLINK_COUNT 10

/**
 * LEDのピン情報
 * 今回はRBに対してのピン情報
 */
typedef struct{
    /** 起動確認用LEDのピン */
   uint8_t activate_pin;
   /** ステータス確認用LEDのピン */
   uint8_t status_pin;
} Led;

void initialize_led(Led *p);

/**
 * 起動用LEDを光らす
 * @param p
 */
void high_activate_led(Led *p);
/**
 * 起動用LEDを消す
 * @param p
 */
void low_activate_led(Led *p);
/**
 * 起動用LEDを点滅させる
 * @param p
 * @param interval 点滅の間隔
 */
void blink_activate_led(Led *p, uint8_t interval);

/**
 * ステータスLEDを光らす
 * @param p
 */
void high_status_led(Led *p);
/**
 * ステータスLEDを消す
 * @param p
 */
void low_status_led(Led *p);
/**
 * ステータスLEDを点灯させる
 * @param p
 * @param interval 点灯の間隔
 */
void blink_status_led(Led *p, uint8_t interval);
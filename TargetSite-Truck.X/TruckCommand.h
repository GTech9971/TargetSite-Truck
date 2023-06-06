#include <xc.h>

/**
 * モーターへのコマンド
 */
enum command{
    /** 停止 */
    STOP,
    /** 前進 */
    FORWARD,
    /** 後退 */
    BACK,
    /** ブレーキ */
    BRAKE,
};

/**
 * スピードの調整モード
 */
enum speed_mode{
    /** 徐々に増加 */
    INC,
    /** 徐々に減少 */
    DEC,
    /** 固定値 */
    NONE,
};

/**
 * トラックへのコマンド
 */
typedef struct{
    /** コマンド */
    command cmd;
    /** スピードの調整 */
    speed_mode speed_mode;
    /** スピード(0~10) */
    uint8_t speed;
} TruckCommand;

/**
 * コマンドのスピード(0~10)から0~1023の値に変換する
 * @param p
 * @return 
 */
static uint16_t calc_speed(uint8_t input) {
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
TruckCommand create_command(uint8_t data);

/**
 * コマンドを実行する
 * @param p
 */
void execute_command(TruckCommand *p);
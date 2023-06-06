# TargetSite-Truck

 ionic/react iosからBlueooth経由でデータを受信し、モータを操作することでラジコンを動かす

## マイコン PIC16F1827

[datasheet](datasheet/pic16f1827.pdf)

## HM-10

BLE規格のモジュール

| サービスUUID | キャラUUID |
| ------------ | ---------- |
| FFE0         | FFE1       |

[datasheet](datasheet/DSD%20TECH%20HM-10%20datasheet.pdf)

### USART

RX = RB1
TX = RB2

ピンを全てデジタルに設定

```
ANSELA = 0x00;
ANSELB = 0x00;
```

RXピンを入力モードに設定

```
TRISA = 0x00;
TRISB = 0x02;
```

RX,TXを有効化

```
TXSTA = 0x20;
RCSTA = 0x90;
```

通信設定

```
//16bit
BAUDCON = 0x08;

//9600bit mode
SPBGR = 51;
```

データ送信

```
void send(unsigned char data){
    while(!TXSTAbits.TRMT);
    TXREG = data;
}

```

### 割り込み

割り込み有効化

```
//interrupt flg clear
PIR1bits.RCIF = 0;
    
//USART recive interrupt enable
PIE1bits.RCIE = 1;
//peripheral enable
PEIE = 1;
//global enable
GIE = 1;
```

割り込み関数

```
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
            //RCREGが受信データ
            send(RCREG);
        }
    }
}
```

## TA7291P

モータードライバー
[datasheet](datasheet/ta7291.pdf)

### ファンクション

| IN1 | IN2 | モード   |
| --- | --- | -------- |
| 0   | 0   | ストップ |
| 1   | 0   | 前進     |
| 0   | 1   | 後退     |
| 1   | 1   | ブレーキ |

### CCP(PWMモード)

PWM有効化 CCP3

```
//pwm initialize
// CCP3M PWM; DC3B 3; 
CCP3CON = 0x3C;    
// CCPR3L 127; 
CCPR3L = 0x7F;    
// CCPR3H 0; 
CCPR3H = 0x00;    
// Selecting Timer 2
CCPTMRS0bits.C3TSEL = 0x0;
    
//timer2 initialize
// PR2 255; 
PR2 = 0xFF;
// TMR2 0; 
TMR2 = 0x00;
// Clearing IF flag.
PIR1bits.TMR2IF = 0;
// T2CKPS 1:1; T2OUTPS 1:1; TMR2ON on; 
T2CON = 0x04;
```

## データ仕様

| bit7 | bit6 | bit5 |  bit4   | bit3 | bit2 | bit1 | bit0 |
| :--: | :--: | :--: | :-----: | :--: | :--: | :--: | :--: |
|  >   | CMD  |  >   | INC/DEC |  >   | SPD  |      |      |

### CMD

トラックへの命令
| bit7 | bit6 |  モード  |
| :--: | :--: | :------: |
|  0   |  0   |   停止   |
|  1   |  0   |   前進   |
|  0   |  1   |   後退   |
|  1   |  1   | ブレーキ |

### INC/DEC

- INC

    現在のスピードからSPDの値に増加していく

- DEC
    現在のスピードから徐々に減少していく

| bit5 | bit4 | モード |
| :--: | :--: | :----: |
|  0   |  0   |  通常  |
|  0   |  1   |  INC   |
|  1   |  0   |  DEC   |

### SPD

モーターのスピードを設定する(10進数で0~10までの値)
| bit3 | bit2 | bit1 | bit0 |
| ---- | ---- | ---- | ---- |

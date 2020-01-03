// CAN受信のサンプル
// 
// 受信したCAN信号をシリアルで送信する
 
#include <mcp_can.h>
#include <SPI.h>
 
//設定値
#define CS_PIN  (10) // CSを10ピンとする（変更可能）
#define INT_PIN (9)  // INTを9ピンとする（変更可能）

// 8pin  to mcp2515
// 9pin  to 88A8JGM
// 10pin to mcp
// 11pin to mcp
// 12pin to sd
// 13pin to mcp


 
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

unsigned char temp[8] = {2, 1, 0x0c, 0, 0, 0, 0, 0};    // temp  0x05
 
MCP_CAN CAN0(CS_PIN);      
 
void setup()
{
  Serial.begin(115200);
  CAN0.begin(CAN_500KBPS); // CANの通信速度を500kbpsにする 
  pinMode(INT_PIN, INPUT); // 割り込みのためのピンを設定
  Serial.println("MCP2515 Library Receive Example...");

}
 
void loop()
{

  CAN0.sendMsgBuf(0x7df, 0, 8, temp);  //ECUにデータ送信要求
  
    if(!digitalRead(INT_PIN))   // 受信割り込みが発生したら、CANデータをReadする
    {
      CAN0.readMsgBuf(&len, rxBuf);              
      rxId = CAN0.getCanId();                    
if (rxId==0x7e8){
      Serial.print("ID: ");
      Serial.print(rxId, HEX);
      Serial.print("  Data: ");
      for(int i = 0; i<len; i++)                
      {
        if(rxBuf[i] < 0x10)
        {
          Serial.print("0");
        }
        Serial.print(rxBuf[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
    }
delay(100);
}

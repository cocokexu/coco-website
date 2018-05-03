 #include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN           8   //灯带信号引脚

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      25 //这里是灯带中的灯的个数，我这边有25个，所以就设置25，具体你看你那边的灯带有多少个，自己改

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 50; // delay for half a second
int touch=3;//定义触摸传感器的接口
int slider1=A1;//定义slider的接口
int slider2=A2;
int slider3=A3;
int val1=10;
int val2=100;
int val3=220;
#define NTD0 -1
#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556
#define NTD8 622

#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278

#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112
//根據中部列出D的音節

int tune[] =
{
  NTD5, NTD3, NTD0, NTD0, NTD3, NTD2,
  NTD1, NTD2, NTD3, NTD5, NTD3, NTD5,
  NTD6, NTD3, NTD0, NTD0, NTD3, NTD2,
  NTD1, NTD2, NTD3, NTD5, NTD3, NTD5,
  NTD6, NTD4, NTD0, NTD0, NTD4, NTD3,
  NTD2, NTD3, NTD4, NTD6, NTD8, NTD6,
  NTD7, NTD6, NTD6, NTD5,
  NTD5, NTD4, NTD3, NTD2,
};
float durt[] =
{
  0.5, 0.5, 1, 1, 0.5, 0.5,
  0.5, 0.5, 0.5, 1, 0.5, 1,
  0.5, 0.5, 1, 1, 0.5, 0.5,
  0.5, 0.5, 0.5, 1, 0.5, 1,
  0.5, 0.5, 1, 1, 0.5, 0.5,
  0.5, 0.5, 0.5, 1, 0.5, 1,
  1 + 0.5, 0.5, 0.5, 1,
  1 + 0.5, 0.5, 1 + 1,
  0.5, 1 + 0.5, 1, 1,
};

//根據右邊的簡譜寫出音調和節奏 
int length;
int tonepin = 6; //蜂鸣器信号引脚


void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
pinMode(9,INPUT_PULLUP);
  pixels.begin(); // This initializes the NeoPixel library.
pinMode(touch,INPUT);
Serial.begin(9600);
 pinMode(tonepin, OUTPUT);
  length = sizeof(tune) / sizeof(tune[0]);
}

void loop() {

 val1 = analogRead(slider1);  //读取电阻值
 val2 = analogRead(slider2);  //读取电阻值
 val3 = analogRead(slider3);  //读取电阻值
val1=map(val1,0,1023,0,255);//将slider中的值从1023份映射到0到255，因为灯带的使用值为0到255
val2=map(val2,0,1023,0,255);
val3=map(val3,0,1023,0,255);
while (Serial.available())
 {
    int inByte =Serial.read( );
    switch (inByte)
    {
     case 65:  //串口輸入為A時
        Serial.println("I'm not singing");  //回送I'm not singing
        digitalWrite(13, LOW);  //滅燈
  for(int i=0;i<25;i++)
  {
    pixels.setPixelColor(i, 0,0,0); 
  }
     // pixels.setPixelColor(10, 100,200,55); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.


 break;
  case 66:  //串口輸入為B時
  
 Serial.println("I'm singing");  //回送I'm singing
        digitalWrite(13, HIGH); //亮燈
     
       for (int x = 0; x < length; x++)
      {
          tone(tonepin, tune[x]*1.19);
        delay(500 * durt[x]);
        noTone(tonepin);
        // 演奏 *1.19使D調變成F調
        }
        
           for(int i=0;i<25;i++)//灯带中25个灯循环反应
 {
    pixels.setPixelColor(0, val1,val2,val3); // val1,val2,val3分别对应灯带的R，G,B
}
   pixels.show();
   delay(1000);//灯光每一次变化的时间为1秒
 Serial.print("val1=");
  Serial.println(val1); //   串口输出
   Serial.print("val2=");
  Serial.println(val2); //   串口输出
   Serial.print("val3=");
 Serial.println(val3); //   串口输出
 delay(1000);
  break;
}
 }  
 }

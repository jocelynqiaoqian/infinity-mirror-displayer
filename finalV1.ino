#include <FastLED.h>
#define NUM_LEDS 8

CRGB leds[NUM_LEDS];
void rpm_cal();
void printLetter(char ch);
void normal_print(int times);
void printLetter(char ch, long interval);
void printLetter_new(char ch, int interval,long color);
void show_frame(int content, int total_number,long color) ;
void show_sigleunit(long color,byte b, int width_color, int width_black ) ;
void show_singleline(long color, byte b);

  void led_test1();
void clean_buffer();
int str_len = 0;
int black_len = 0;
volatile int  count =0;
volatile int refresh = 0;
int rows= 8;      
const int charHeight = 8;
const int charWidth = 5;
long time_his = 0;
long time_his2 = 0;

long timeinterval =0;

float rpm =0;
int half_revolutions = 0;
long lastmillis = 0;

int k = 0;
String btdata = "String";

int test2pass = 0;
String trash = "";

bool speedtest = 0;
int print_index = 1;

bool time_start = 0;
int hour = 0;
int mini= 0;
int second = 0;
String H = "0";
String M = "0";
String S = "0";
bool hour_change = 0;
bool mini_change = 0;
String temp = "";

bool time_update = 0;


   const unsigned char font[95][5] = {
         {0x00,0x00,0x00,0x00,0x00},   //   0x20 32
         {0x00,0x00,0x6f,0x00,0x00},   // ! 0x21 33
         {0x00,0x07,0x00,0x07,0x00},   // " 0x22 34
         {0x14,0x7f,0x14,0x7f,0x14},   // # 0x23 35
         {0x00,0x07,0x04,0x1e,0x00},   // $ 0x24 36
         {0x23,0x13,0x08,0x64,0x62},   // % 0x25 37
         {0x36,0x49,0x56,0x20,0x50},   // & 0x26 38
         {0x00,0x00,0x07,0x00,0x00},   // ' 0x27 39
         {0x00,0x1c,0x22,0x41,0x00},   // ( 0x28 40
         {0x00,0x41,0x22,0x1c,0x00},   // ) 0x29 41
         {0x14,0x08,0x3e,0x08,0x14},   // * 0x2a 42
         {0x08,0x08,0x3e,0x08,0x08},   // + 0x2b 43
         {0x00,0x50,0x30,0x00,0x00},   // , 0x2c 44
         {0x08,0x08,0x08,0x08,0x08},   // - 0x2d 45
         {0x00,0x60,0x60,0x00,0x00},   // . 0x2e 46
         {0x20,0x10,0x08,0x04,0x02},   // / 0x2f 47
         {0x3e,0x51,0x49,0x45,0x3e},   // 0 0x30 48
         {0x00,0x42,0x7f,0x40,0x00},   // 1 0x31 49
         {0x42,0x61,0x51,0x49,0x46},   // 2 0x32 50
         {0x21,0x41,0x45,0x4b,0x31},   // 3 0x33 51
         {0x18,0x14,0x12,0x7f,0x10},   // 4 0x34 52
         {0x27,0x45,0x45,0x45,0x39},   // 5 0x35 53
         {0x3c,0x4a,0x49,0x49,0x30},   // 6 0x36 54
         {0x01,0x71,0x09,0x05,0x03},   // 7 0x37 55
         {0x36,0x49,0x49,0x49,0x36},   // 8 0x38 56
         {0x06,0x49,0x49,0x29,0x1e},   // 9 0x39 57
         {0x00,0x36,0x36,0x00,0x00},   // : 0x3a 58
         {0x00,0x56,0x36,0x00,0x00},   // ; 0x3b 59
         {0x08,0x14,0x22,0x41,0x00},   // < 0x3c 60
         {0x14,0x14,0x14,0x14,0x14},   // = 0x3d 61
         {0x00,0x41,0x22,0x14,0x08},   // > 0x3e 62
         {0x02,0x01,0x51,0x09,0x06},   // ? 0x3f 63
         {0x3e,0x41,0x5d,0x49,0x4e},   // @ 0x40 64
         {0x7e,0x09,0x09,0x09,0x7e},   // A 0x41 65
         {0x7f,0x49,0x49,0x49,0x36},   // B 0x42 66
         {0x3e,0x41,0x41,0x41,0x22},   // C 0x43 67
         {0x7f,0x41,0x41,0x41,0x3e},   // D 0x44 68
         {0x7f,0x49,0x49,0x49,0x41},   // E 0x45 69
         {0x7f,0x09,0x09,0x09,0x01},   // F 0x46 70
         {0x3e,0x41,0x49,0x49,0x7a},   // G 0x47 71
         {0x7f,0x08,0x08,0x08,0x7f},   // H 0x48 72
         {0x00,0x41,0x7f,0x41,0x00},   // I 0x49 73
         {0x20,0x40,0x41,0x3f,0x01},   // J 0x4a 74
         {0x7f,0x08,0x14,0x22,0x41},   // K 0x4b 75
         {0x7f,0x40,0x40,0x40,0x40},   // L 0x4c 76
         {0x7f,0x02,0x0c,0x02,0x7f},   // M 0x4d 77
         {0x7f,0x04,0x08,0x10,0x7f},   // N 0x4e 78
         {0x3e,0x41,0x41,0x41,0x3e},   // O 0x4f 79
         {0x7f,0x09,0x09,0x09,0x06},   // P 0x50 80
         {0x3e,0x41,0x51,0x21,0x5e},   // Q 0x51 81
         {0x7f,0x09,0x19,0x29,0x46},   // R 0x52 82
         {0x46,0x49,0x49,0x49,0x31},   // S 0x53 83
         {0x01,0x01,0x7f,0x01,0x01},   // T 0x54 84
         {0x3f,0x40,0x40,0x40,0x3f},   // U 0x55 85
         {0x0f,0x30,0x40,0x30,0x0f},   // V 0x56 86
         {0x3f,0x40,0x30,0x40,0x3f},   // W 0x57 87
         {0x63,0x14,0x08,0x14,0x63},   // X 0x58 88
         {0x07,0x08,0x70,0x08,0x07},   // Y 0x59 89
         {0x61,0x51,0x49,0x45,0x43},   // Z 0x5a 90
         {0x3c,0x4a,0x49,0x29,0x1e},   // [ 0x5b 91
         {0x02,0x04,0x08,0x10,0x20},   // \ 0x5c 92
         {0x00,0x41,0x7f,0x00,0x00},   // ] 0x5d 93
         {0x04,0x02,0x01,0x02,0x04},   // ^ 0x5e 94
         {0x40,0x40,0x40,0x40,0x40},   // _ 0x5f 95
         {0x00,0x00,0x03,0x04,0x00},   // ` 0x60 96
         {0x20,0x54,0x54,0x54,0x78},   // a 0x61 97
         {0x7f,0x48,0x44,0x44,0x38},   // b 0x62 98
         {0x38,0x44,0x44,0x44,0x20},   // c 0x63 99
         {0x38,0x44,0x44,0x48,0x7f},   // d 0x64 100
         {0x38,0x54,0x54,0x54,0x18},   // e 0x65 101
         {0x08,0x7e,0x09,0x01,0x02},   // f 0x66 102
         {0x0c,0x52,0x52,0x52,0x3e},   // g 0x67 103
         {0x7f,0x08,0x04,0x04,0x78},   // h 0x68 104
         {0x00,0x44,0x7d,0x40,0x00},   // i 0x69 105
         {0x20,0x40,0x44,0x3d,0x00},   // j 0x6a 106
         {0x00,0x7f,0x10,0x28,0x44},   // k 0x6b 107
         {0x00,0x41,0x7f,0x40,0x00},   // l 0x6c 108
         {0x7c,0x04,0x18,0x04,0x78},   // m 0x6d 109
         {0x7c,0x08,0x04,0x04,0x78},   // n 0x6e 110
         {0x38,0x44,0x44,0x44,0x38},   // o 0x6f 111
         {0x7c,0x14,0x14,0x14,0x08},   // p 0x70 112
         {0x08,0x14,0x14,0x18,0x7c},   // q 0x71 113
         {0x7c,0x08,0x04,0x04,0x08},   // r 0x72 114
         {0x48,0x54,0x54,0x54,0x20},   // s 0x73 115
         {0x04,0x3f,0x44,0x40,0x20},   // t 0x74 116
         {0x3c,0x40,0x40,0x20,0x7c},   // u 0x75 117
         {0x1c,0x20,0x40,0x20,0x1c},   // v 0x76 118
         {0x3c,0x40,0x30,0x40,0x3c},   // w 0x77 119
         {0x44,0x28,0x10,0x28,0x44},   // x 0x78 120
         {0x0c,0x50,0x50,0x50,0x3c},   // y 0x79 121
         {0x44,0x64,0x54,0x4c,0x44},   // z 0x7a 122
         {0x00,0x08,0x36,0x41,0x41},   // { 0x7b 123
         {0x00,0x00,0x7f,0x00,0x00},   // | 0x7c 124
         {0x41,0x41,0x36,0x08,0x00},   // } 0x7d 125
         {0x04,0x02,0x04,0x08,0x04},   // ~ 0x7e 126
     };

String text_String = "ECE5725";

void setup() {
  FastLED.addLeds<APA102>(leds, NUM_LEDS);  // setup the led strip using fast-led lib
  Serial.begin(57600);                      // set the serial baud rate 57600 is the download rate of arduino. So we can wirelessly upload.
  attachInterrupt(digitalPinToInterrupt(2), rpm_cal, FALLING);  // setup the external interrupt
//  pinMode(LED_BUILTIN, OUTPUT);                               // jsut some debug led setup

// now it is the start mode code sectoin in arduino

clean_buffer(); // clean the buffer 
 
 while (Serial.available() == 0) {  //wait until there are some information come in 
 }

 
  delay(100);                    // wait to receive the whole data
  btdata = Serial.readString();  //read the data and store the data in btdata
  if(btdata == "1")            //actually there will not be orther command here is just to show it can receive the right data. So actually it is a debug point
    led_test1();                 //execute the led test program
  Serial.println("test1");     //   
   
    


}

void loop() {
  
//  time_his = micros();
  // put your main code here, to run repeatedly:
//Serial.println(timeinterval);
if(refresh == 1 )
{
//  detachInterrupt(0);
  refresh = 0;
  

  
  
    
  
// for(k = text_String.length()-2; k>-1; k--) {
////  delay(2);
//// if(refresh == 1 )
//// {k = sizeof(textString);
//// refresh = 0;}
//  
//    printLetter(text_String.indexOf(k),28*1000); 
// }

//  for(k = text_String.length(); k>-1; k--) {
////  delay(2);
//// if(refresh == 1 )
//// {k = sizeof(textString);
//// refresh = 0;}
////detachInterrupt(0);
//    normal_print(min(68,round(1000/rpm*1.682)));
//        normal_print(88);

     show_frame(1, 100, 0xFF0000); //try
////    attachInterrupt(0, rpm_cal, FALLING);
//    
//    printLetter(text_String.charAt(k),28*1000); 
// }

// Serial.print("FINISH");
// attachInterrupt(0,rpm_fan, FALLING);

  

if (millis() - lastmillis >= 1000 &&speedtest == 0){ //update the rpm and trasmit the signal to raspberry pi 
 detachInterrupt(0);//Disable interrupt when calculating
 rpm = float(half_revolutions); // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
 if(rpm == 23 && speedtest == 0) {
 Serial.println("test2"); // print the rpm value.
 speedtest = 1;
 }
 half_revolutions = 0; // Restart the RPM counter
 lastmillis = millis(); // Uptade lasmillis
 attachInterrupt(0, rpm_cal, FALLING); //enable interrupt

// if(print_index == 1)
// print_index = 2;
// else
// print_index = 1;
 }
  

  if (Serial.available()) {

  btdata = Serial.read();     //read String is very slow so we should use read byte
//  print_index = 2;
  if(btdata == "50") {
    print_index = 2;
  }
  
  else if(btdata == "51" ) {
    if (time_start == 0) {
    hour = ((Serial.read()-48)*10 + Serial.read()-48);
    mini = ((Serial.read()-48)*10 + Serial.read()-48);
    second = ((Serial.read()-48)*10 + Serial.read()-48);
    time_converter(hour,mini,second);
   

//    hour = 12;
//    mini = 12;
//    second = 12;
    
    print_index = 3;  
    time_start = 1;
    }
    else{
    print_index = 3;  
    time_update = 1;
    }
  }
  
  else {
    print_index = 4;
    }
    
}

parse_print();

}
}


void rpm_cal() {
//time_his = micros();

half_revolutions ++;
//
count ++;
if(count ==1) {
refresh = 1;
count = 0;
}

//refresh = 1;
//goto loopstart;
//
//  timeinterval = millis() - time_his;
////  if(timeinterval > 35000 || timeinterval < 28000)
////  timeinterval == 30000;
//  time_his = millis();
// // Serial.println(timeinterval);
////  delay(10);
////  temp = timeinterval;
// for(int k = sizeof(textString); k>-1; k--)
//  printLetter(textString[k],30000); 
  
 }


void normal_print(int times){

   for (int i = 0 ; i< times ; i++) {
//      if(refresh == 1){
//        
//        break;
//        }
      for (int j = 0; j < 8; j ++) {
//       if(refresh == 1){
//        
//        break;
//        }
        leds[j] = CRGB::Red;
      }
//            if(refresh == 1){
//        
//        break;
//        }
      FastLED.show();
//            if(refresh == 1){
//        
//        break;
//        }
       for (int j = 0; j < 8; j ++) {
//              if(refresh == 1){
//        
//        break;
//        }
        leds[j] = CRGB::Black;
      }
//            if(refresh == 1){
//        
//        break;
//        }
      FastLED.show();
//            if(refresh == 1){
//        
//        break;
//        }
//       for (int j = 0; j < 8; j ++) {
////              if(refresh == 1){
////        
////        break;
////        }
//        leds[j] = CRGB::Black;
//      }
////            if(refresh == 1){
////        
////        break;
////        }
//      FastLED.show();
////            if(refresh == 1){
////        
////        break;
////        }
      
   }
}


 

void printLetter(char ch, long interval)
  {    
    if (ch < 32 || ch > 126){
      ch = 32;
      }
    ch -= 32;
    for (int i=charWidth-1; i>-1; i--) {
//      if(refresh == 1 ){
//        refresh = 0;
//      break;}
      byte b = font[ch][i];
      for (int j=0; j<charHeight; j++) {
//        if(refresh == 1){
//          refresh = 0;
//        break;
//        }
        if (bitRead(b,j)){
          leds[j] = CRGB::Blue;
          }
        }
        
        FastLED.show();

//  delayMicroseconds(interval/360*1);
  
//        delayMicroseconds(200);
//  if(interval>35000) interval = 30000;
//
//        
//        time_his2 = micros();
////        timeinterval = 30000;
//  // 
//  Serial.println(interval);
//  
//  while((micros() - time_his2) <= interval/360*10 );


        for (int j=0; j<charHeight; j++) {                
                  leds[j] = CRGB::Black;                  
                }
//         if(i == 0)
        FastLED.show();
        
     
        if (i != 0){
//
////        time_his2 = micros();
////        while((micros() - time_his2) <= interval/360*0);
//        }
//
//        
//        delayMicroseconds(interval/360*0.1);
        }
        
        else if(~k) {
//
//        {time_his2 = micros();
//        while((micros() - time_his2) <= interval/360*10);
//        }
//      else
        delayMicroseconds(interval/360*10); 
           
        }
    } 
  }  





void printLetter_new(char ch, int interval,long color,int interval_unit)
  {    
    if (ch < 32 || ch > 126){
      ch = 32;
      }
    ch -= 32;
    for (int i=charWidth-1; i>-1; i--) {
      byte b = font[ch][i];
      if(i != 0)
      show_sigleunit(color,b,1,interval_unit);
      else if( i == 0 && k != 0)
      show_sigleunit(color,b,1,interval_unit+interval);
      else if( i == 0 && k == 0)
      show_sigleunit(color,b,1,interval_unit);
    }
  }

        






  

  void led_test1() {
     for (int i=0; i<8; i++) {                
         leds[i] = CRGB::Blue;
         }
         FastLED.show();
      delay(1000);
      
     for (int i=0; i<8; i++) {                
         leds[i] = CRGB::Green;
     }
     FastLED.show();
     delay(1000);
     
     for (int i=0; i<8; i++) {                
         leds[i] = CRGB::Red;
     }
     FastLED.show();
     delay(1000);

     for (int i=0; i<8; i++) {                
         leds[i] = CRGB::Black;
     }
     FastLED.show();
     
  }

//  void print_rps(number) {
//    if number < 10 
//    Serial.print()
//  }


//void clean_buffer() {  //serial.flush?  may be it will be faster
//  if (Serial.available()) {
//  trash = Serial.readString();
//  trash = "";
//}
//}


void clean_buffer() {  //second version which is faster
  while (Serial.available()) {
  trash = Serial.read();
}
}

void show_frame(int content, int total_number,long color) {
  if(content == 1) //show text
    str_len = text_String.length();
    black_len = (total_number - str_len*5 - (str_len-1)*3)/2;
    show_sigleunit(0x00000,0xFF,black_len,0);
    for(k = text_String.length(); k>-1; k--)
    printLetter_new(text_String.charAt(k),1,color,1);
    
    
    
    
    
    
  
}

void show_sigleunit(long color,byte b, int width_color, int width_black ) {
  for (int i = 0 ; i<width_color ; i++)
  show_singleline(color,b);
  for (int i = 0 ; i<width_black ; i++)
  show_singleline(0x000000,0xFF);
}


void show_singleline(long color, byte b){
//  long led_color = color << 16;
       for (int i=0; i<8; i++) {
         if (bitRead(b,i))               
         leds[i] = color;
         else
         leds[i] = 0x000000;
     }
     FastLED.show();
  
}


void time_converter(int hour, int mini, int second)
{
  if (hour<10) {
    H = hour;
    H = "0" + H;}
    else 
    H = hour;
    
    if (mini < 10) {
    M = mini;
    M = "0" + M;}
    else 
    M = mini;
    
    if (second < 10) {
    S = second;
    S = "0" + S;}
    else 
    S = second;
    text_String = H + ":" + M + ":" + S ;
}

void parse_print() {
    if(print_index == 1)
    text_String = "ECE5725";

  
  else if (print_index == 2)
    text_String = "INFINITE";
    
  else if (print_index == 3) {
   
    if (time_update == 1) {
      time_update = 0;
      second = second + 1;
    
    if (second >= 60) {
      mini = mini + 1;
      second = 0;
    }
     if (mini >= 60 ) {
      hour = hour + 1;
      mini = 0;
     }
     
      if (hour == 24){
      hour = 1;
  }

  
 time_converter(hour,mini,second);
  }
}

  else 
  text_String = btdata;

}


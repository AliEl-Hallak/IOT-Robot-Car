#include <LedControl.h> //Kütüphanemizi dahil edelim 

#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 
char auth [] = "WjtcUgF9NZvRA6X9ymODQWtGET9x_NqW";  
char ssid [] = "Ali";  // Bağlantı yapacağınız Wi‐Fi adı 
char pass [] = "22224444"; // Wi‐Fi şifreniz
#define CLK 10 
#define CS 3 
#define DIN 1
#define MaxSayisi 1  //Bağlı olan dot matrix sayısı 

const long delay_suresi = 750; //Kodda kullanacağımız delay süresi 

LedControl led = LedControl(DIN, CLK, CS, MaxSayisi); 

//Kullanacağımız ifadeler için byte tipinde bir dizi tanımlıyoruz
byte images[][8] =
 {{
  
     B00111100,  //gulen ifade
     B01000010,
     B10010101,
     B10100001,
     B10100001,
     B10010101,
     B01000010,
     B00111100
   }

   
 };

 void MatrixeYazdir(byte* ch)
 {
   for (int i = 0; i < 8; i++)
   {
     led.setRow(0, i, ch[i]);
   }
 }


#define buzzer D8
#define in1 D3
#define in2 D4
#define in3 D5
#define in4 D6
#define ena D2
#define enb D7
bool  sag=0;
bool  sol=0;
bool  elleri=0;
bool  geriy=0;
bool  korna=0;
int hiz;


void setup()
{


  Blynk.begin(auth, ssid, pass); 
         led.setIntensity(0, 15);  //Parlaklık ayarı
   led.shutdown(0, false);   //Led matrixi aktif hale getirme
   led.clearDisplay(0 );
        MatrixeYazdir(images[0]);
  
 
  Serial.begin(115200); 
  pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(ena,OUTPUT);
pinMode(enb,OUTPUT);
  // Debug console
  
}
BLYNK_WRITE(V0){
  sag = param.asInt();
  
}

BLYNK_WRITE(V1){
  sol = param.asInt();
    
}

BLYNK_WRITE(V0){
  elleri = param.asInt();
  
}

BLYNK_WRITE(V1){
  geriy = param.asInt();
   
}
BLYNK_WRITE(V4){
  hiz = param.asInt();
}
BLYNK_WRITE(V5){
  korna = param.asInt();
}
void  cont()
{
   if(korna==1){
   kornases();
    }
 else if(korna==0){
   noTone(buzzer);
    }
   if(elleri==1){
  
    elleric();
    }

    else if(geriy==1){
   
   greayc();
    }
     else if(sag==1){
     
   sagc();
    }
    
     else if(sol==1){
       
   solc();
    }

    
      else if(sol==0 && elleri==0 && geriy==0 && sag==0){
  
   hic();
    }
}

void loop()
{
  Blynk.run();
cont();

}
void elleric()
{
 
analogWrite(ena,hiz);
analogWrite(enb,hiz);
digitalWrite(in1,1);
digitalWrite(in2,0);
digitalWrite(in3,0);
digitalWrite(in4,1);


  }
void kornases()
{
tone(buzzer,400);
delay(200);


noTone(buzzer);
delay(200);
tone(buzzer,400);
delay(500);



  }
 

  void greayc()
{
 
analogWrite(ena,hiz);
analogWrite(enb,hiz);
digitalWrite(in1,0);
digitalWrite(in2,1);
digitalWrite(in3,1);
digitalWrite(in4,0);

  }
    void sagc()
{
    
analogWrite(ena,hiz);
analogWrite(enb,hiz);
digitalWrite(in1,1);
digitalWrite(in2,0);
digitalWrite(in3,1);
digitalWrite(in4,0);

  }
    void solc()
{
   
analogWrite(ena,hiz);
analogWrite(enb,hiz);
digitalWrite(in1,0);
digitalWrite(in2,1);
digitalWrite(in3,0);
digitalWrite(in4,1);
  }
      void hic()
{
 
digitalWrite(in1,0);
digitalWrite(in2,0);
digitalWrite(in3,0);
digitalWrite(in4,0);
  }

#include <SoftwareSerial.h>
SoftwareSerial SIM800L(2, 3); // RX | TX
#define BUZZ 12
#define SLED 11

int pin1 = 8;
int pin2 = 7;
int Pos = 0; 
int State;
int LastState;  
int blits;
int counter ;
void setup() {
   //menggunakan baut komunikasi 9600 pada serial monitor
    Serial.begin(9600);
    SIM800L.begin(9600);  
     pinMode (pin1 ,INPUT);
     pinMode (pin2 ,INPUT);
    pinMode(BUZZ, OUTPUT);
    pinMode(SLED, OUTPUT);
    digitalWrite(SLED,HIGH);
}
 
void loop() {
  while(Pos < 40){
  State = digitalRead(pin1);
  blits = abs((-1)+State);
   if (State != LastState){     
     if (blits != State) { 
       Pos ++;
     }    
     else {
       Pos --;
     }
   } 
  Serial.println(Pos); 
  delay(100);
  LastState = State;
    }
  while(1){
  emergency();
    digitalWrite(BUZZ,HIGH); 
    delay(80);
    digitalWrite(BUZZ,LOW); 
    delay(80);   
    digitalWrite(BUZZ,HIGH); 
    delay(80);
    digitalWrite(BUZZ,LOW); 
    delay(80);
    kirimSMS();
  }
}
void emergency(){
  for(int i=0;i<5;i++){
    digitalWrite(BUZZ,HIGH); 
    delay(500);
    digitalWrite(BUZZ,LOW); 
    delay(500);
   } 
  }
void kirimSMS(){
   while(!Serial);
   Serial.println("Arduino with Module GSM is ready");
 
    //menggunakan baut komunikasi 9600 antara module gsm dengan arduino
    Serial.println("Module dimulai pada serial komunikasi 9600");
    delay(1000);//waktu jeda 1 detik
    Serial.println("SIM800L SIAP DIGUNAKAN!");
   
  Serial.println("Set format SMS ke ASCII"); //menset format SMS
  SIM800L.write("AT+CMGF=1\r\n"); //Prosedur penulisan oleh module sim800l
  delay(1000); //waktu jeda 1 detik
 
  Serial.println("SIM800 Set SMS ke Nomor Tujuan");
  //silahkan ganti no hp nya menjadi no hp ANDA
  SIM800L.write("AT+CMGS=\"081217161711\"\r\n");
  delay(1000);
   
  Serial.println("Module mengirimkan SMS ke no tujuan");
  //isi SMS yang ditujukan ke no hp diatas
  SIM800L.write("TERJADI PERGESERAN TANAH"); 
  delay(1000);
  Serial.println("SMS Selesai Dikirim!");
  Serial.println("Ketik pada keyboard Ctrl+Z atau ESC > keluar menu ini");
  SIM800L.write((char)26);
  delay(1000);
  }

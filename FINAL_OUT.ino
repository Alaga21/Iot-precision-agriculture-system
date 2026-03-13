#define BLYNK_TEMPLATE_ID "TMPL3Y8nr5f9_"
#define BLYNK_TEMPLATE_NAME "Distance Meter"
#define BLYNK_AUTH_TOKEN "_ZrZ-QPd1AyqHfP8MNItaC9v9vV5MMfN"

//#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Servo.h>

Servo s1;  // create servo object to control a servo
Servo s2;

//blynk authentication// 
char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "akash";
char pass[] = "akz123456"; 

#define mot1 19
#define mot3 21
#define mot2 22
#define mot4 23

#define echoPin 18
#define trigPin 14

const int stepPin =32; // Step pin connection
const int dirPin = 33; // Direction pin connection

bool mode1,mode2,mode3,st; 
int count1=0,count2=0,count3=0,flag=0,i,a1,a2;
float duration,distance;
BLYNK_WRITE(V0)
{      
 mode1= param.asInt();
}
BLYNK_WRITE(V1){
 mode2 = param.asInt();
  
}
BLYNK_WRITE(V2){
 mode3= param.asInt();
}
BLYNK_WRITE(V3){
 st = param.asInt();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(mot1,OUTPUT);
  pinMode(mot2,OUTPUT);
  pinMode(mot3,OUTPUT);
  pinMode(mot4,OUTPUT);

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  s1.attach(13);  // attaches the servo on pin 9 to the servo object
  s2.attach(27); 
  s1.write(90);  
  s2.write(180);
   Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  // put your main code here, to run repeatedly:
 Blynk.run();
 object_detection();
  if((st==0)&&(mode1==1)&&(mode2==0)&&(mode3==0)&&(flag==0)){
    //mode1 motion
    if(count1<=3){
     Forward();
     count1++;
     Serial.println("mode1");
    }
    else{
      Stop();
      count1=0;
      delay(1000);
      stepper(100);
     }
      }
  else if((st==0)&&(mode1==0)&&(mode2==1)&&(mode3==0)&&(flag==0)){
    //mode2 motion
 Serial.println("mode2");
 if(count2<=10){
     Forward();
     count2++;
     Serial.println("mode2");
    }
    else{
      count2=0;
      Stop();
      delay(1000);
      stepper(300);
     }
  
   }
  else if((st==0)&&(mode1==0)&&(mode2==0)&&(mode3==1)&&(flag==0)){
    //mode3 motion
    Serial.println("mode3");
  if(count3<=13){
     Forward();
     count3++;
     Serial.println("mode3");
    }
    else{
      count3=0;
      Stop();
      delay(1000);
      stepper(500);
     }
   }
  else if((st==1)||((st==0)&&(mode1==0)&&(mode2==0)&&(mode3==0))||(flag==1)){
    Stop();
  }
     delay(500);
}
void Forward(){
  digitalWrite(mot1,LOW);
  digitalWrite(mot2,HIGH);
  digitalWrite(mot3,LOW);
  digitalWrite(mot4,HIGH);
}
void Stop(){
  digitalWrite(mot1,LOW);
  digitalWrite(mot2,LOW);
  digitalWrite(mot3,LOW);
  digitalWrite(mot4,LOW);
}
////////////////////////////obstacle detection/////////////////////////////
void object_detection(){
    
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance= duration*0.017;

Serial.print("Distance measured: ");
Serial.println(distance);
if(distance<=17){
 Stop();
 Serial.println("object deteected");
 flag=1;
  
}
else{
  Serial.println("no object");
  flag=0;
}
}
void stepper(int height){
  digitalWrite(dirPin, HIGH);
      for (i=0;i<=height;i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
        Serial.println("up");
        Serial.println(i);
      }
      delay(1000);
      digitalWrite(dirPin, LOW);
      for (i=height;i>=0;i--) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(1000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(1000);
         Serial.println("down");
        Serial.println(i);
      }
      delay(2000);
      for(a1=90;a1>=0;a1--){
        s1.write(a1);
        delay(5);
      }
      delay(500);
       for(a1=0;a1<=90;a1++){
        s1.write(a1);
        delay(5);
      }
            delay(500);
      for(a2=180;a2>=90;a2--){
        s2.write(a2);
        delay(5);
      }
      delay(500);
       for(a2=90;a2<=180;a2++){
        s2.write(a2);
        delay(5);
      }
}

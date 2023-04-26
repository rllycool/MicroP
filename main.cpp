#include "mbed.h"

DigitalOut myled(LED1);
//declare all our LEDs
DigitalOut redLED1(p11);
DigitalOut redLED2(p12);
DigitalOut redLED3(p13);
DigitalOut greenLED1(p30);
DigitalOut greenLED2(p29);
DigitalOut greenLED3(p28);

//declare our switches
DigitalIn redSwitch(p17,PullUp); //One of the red LEDs
// that is off should be turned on. 
DigitalIn greenSwitch(p18,PullUp); //one of the 
//green LEDs that is off should be turned on.
DigitalIn bothSwitch(p23,PullDown); //turn off one of both LEDS


int main() {
    //declare our counters to keep track of LEDS
    int redcount=0;
    int greencount=0;

    //declare LED default states
    redLED1 =0;
    redLED2 =0;
    redLED3 =0;
    greenLED1 =1;
    greenLED2 =1;
    greenLED3 =1;
    
  while(1) {
    
    //wait to deal with switch bounce
    wait(0.18);
   
    //switch1 pressed
    if(redSwitch.read() == 0){
        
        if(redcount==2){
            redLED3=1; //turn on LED
            redcount++; //increase count
        }
        if(redcount==1){
            redLED2 = 1;
            redcount++;
        }
        else{
            redLED1=1;
            redcount++;
        }
    }
    
    //switch2 pressed
    if(greenSwitch.read() == 0){
        if(greencount==2){
            greenLED3=0;
            greencount++;
        }
        if(greencount==1){
            greenLED2 = 0;
            greencount++;
        }
        else{
            greenLED1=0;
            greencount++;
        }
    }

    //when Switch 3 is pressed
    if(bothSwitch.read()==1){
        //all checks for REDcount to turn off REDLEDS
        if(redcount==0){
            redLED1=0;
        }
        if(redcount==1){
            redLED2=0;
            redcount--;
        }
        if(redcount>=2){
            redLED3 =0;
            redcount =1;
        }
        wait(.1);
        //all checks for greencount to turn off greenLEDS
        if(greencount==0){
            greenLED1 =1;
        }
         if(greencount==1){
            greenLED2 =1;
            greencount--;
        }
        if(greencount>=2){
            greenLED3 =1;
            greencount=1;
        }
    }
  }
}

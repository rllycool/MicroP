#include "mbed.h"
#include <stdlib.h>  

SPI spi(p11,p12,p13); //stub
DigitalOut cs1(p14),cs2(p15,1);

int main() {
    int data;
    int randNum;
    int success;
    int time;
    int currtime;
    Timer timer;
    spi.frequency(1000000);

    time = 1;
  while(1) {
        //generate a rand num 1 2 3
        randNum= rand() % 3;
        timer.reset();

        //letter a
        if(randNum == 0){
            success=0;

            spi.format(8,0);
            cs1=0; //ready to write
            spi.write(0xFA); //display a
            cs1=1; //close

            while (success != 1){
                timer.start();
                currtime = timer.read();
                spi.format(8,2);
                cs2=1;
                data = spi.write(0);
                cs2=0;
                
                if(data == 0b00000001){
                    timer.stop();
                    success=1;
                    break;
                }
                if((data =! 0b00000001) || (currtime > time)){
                    spi.format(8,0);
                    cs1=0; 
                    spi.write(0b00011100); //display L
                    cs1=1;
                    while(1){
                        wait(0.2);
                    }
                }

            }
        }

        //letter b
        if(randNum == 1){
            success=0;
            spi.format(8,0);
            cs1=0; 
            spi.write(0x3e); //display b
            cs1=1;

            while (success != 1){
                timer.start();
                currtime = timer.read();
                spi.format(8,2);
                cs2=1; //ready to write
                data = spi.write(0);
                cs2=0; //sleepy
               
                if(data == 0b00000010){
                    timer.stop();
                    success=1;
                    break;
                }
                if((data =! 0b00000010) || (currtime > time)){
                    spi.format(8,0);
                    cs1=0; 
                    spi.write(0b00011100); //display L
                    cs1=1;
                    while(1){
                        wait(0.2);
                    }
                    
                }
            
            }
        }

        //letter c
        if(randNum == 2){
            success=0;
            spi.format(8,0);
            cs1=0; //ready to write
            spi.write(0b10011100); //display c
            cs1=1; //close


            while (success != 1){
                timer.start();
                currtime = timer.read();
                spi.format(8,2);
                cs2=1;
                data = spi.write(0);
                cs2=0;
            
                if(data == 0b000000100){
                    timer.stop();
                    success=1;
                    break;
                }
                if((data =! 0b00000010) || (currtime > time)){
                    spi.format(8,0);
                    cs1=0; 
                    spi.write(0b00011100); //display L
                    cs1=1;
                    while(1){
                        wait(0.2);
                    }
                }

            }
        }

        time = time * 0.8;
        spi.format(8,0);
        cs1=0; 
        spi.write(0b00000000); //display ???
        cs1=1;
        wait(1);
                    
  }
}

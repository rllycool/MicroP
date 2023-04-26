#include "mbed.h"


DigitalOut myled(LED1);
DigitalIn mode(p21);

BusOut display(p5,p6,p7,p8,p9,p10,p11,p12);
Serial pc(USBTX, USBRX); // tx, rx
AnalogIn tempIn(p19);

//this is the method for our busout to operate depending on vals.
int SegConvert(int digit)
{
    switch (digit) {
        case 0: return 0b00111111;  // 0
        case 1: return 0b00000110;  // 1
        case 2: return 0b01011011;  // 2
        case 3: return 0b01001111;  // 3
        case 4: return 0b01100110;  // 4
        case 5: return 0b01101101;  // 5
        case 6: return 0b01111101;  // 6
        case 7: return 0b00000111;  // 7
        case 8: return 0b01111111;  // 8
        case 9: return 0b01101111;  // 9
        case 'C': return 0b00111001;    // Celsisus C
        case 'F': return 0b01110001;    // Farenheit F
        case '-': return 0b01000000;    // negative symbol
        case 'NULL': return 0b00000000; // blank the display
    }
    return 0; 
}

int main() {
    //set baudrate
    pc.baud(9600);

    float tempC,tempF;
    float v,f,sum;
    int tempInt;

  while(1) {
    sum=0;
    //mean average voltage
    for(int i = 0;i<1000;i++){
        f =tempIn;
        sum = sum+f;
    }
    f = sum/1000; 
    v= f*3.3;

    //Calculate Temp in C and F
    tempC = (v-0.4)/(0.0195);
    tempF = (tempC * 9/5) +32;

    //Decide which to use based on p21
    if(mode==0){
        tempInt= (int)tempC;
    }
    if(mode==1){
         tempInt = (int)tempF;
    }

    //print temp to terminal for debugging purposes
    pc.printf("Temp: %i \n\r",tempInt);

    //handle all positive double digit temps 
    if(tempInt>0){
        for(int i=0;i<2;i++){
            if(i==0){
                int digit = tempInt/10;

                display = SegConvert(digit);
                wait(0.5);
                display= SegConvert('NULL');
            }
            if(i==1){
                int digit = tempInt % 10;

                display = SegConvert(digit);
                wait(0.5);
                display= SegConvert('NULL');
            }
            wait(0.1);
        }
    }

    //not needed by product description, but accounts for pos, single val temps
    if(tempInt >0 && tempInt<9){
        display = SegConvert(tempInt);
        wait(0.5);
        display= SegConvert('NULL');
        wait(0.1);
    }

    //handle negative double digit temps
    if(tempInt <0 && abs(tempInt)>9){
        display = SegConvert('-');
        wait(0.5);
        display= SegConvert('NULL');
        wait(0.1);

        int digit = abs(tempInt/10);

        display = SegConvert(digit);
        wait(0.5);
        display= SegConvert('NULL');
        wait(0.1);

        digit = tempInt % 10;

        display = SegConvert(digit);
        wait(0.5);
        display= SegConvert('NULL');
        wait(0.1);
    }

    //handle negative and single digit temps
    if(tempInt <0 && abs(tempInt)<9){
        display = SegConvert('-');
        wait(0.5);
        display= SegConvert('NULL');
        wait(0.1);

      
        display = SegConvert(abs(tempInt));
        wait(0.5);
        display= SegConvert('NULL');
        wait(0.1);
    }

    //display F or C depending on mode
    if(mode == 1){
        display= SegConvert('F');
        wait(0.5);
    }
    if(mode == 0){
        display= SegConvert('C');
        wait(0.5);
    }
    display= SegConvert('NULL');


    wait(1);
  }
}

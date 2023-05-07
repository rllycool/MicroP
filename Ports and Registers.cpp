//NO MBED.H

// Registers for port 0
#define FIO0DIR (*(volatile unsigned int *)0x2009c000)
#define FIO0PIN (*(volatile unsigned int *)0x2009c014)

// Registers for port 1
#define FIO1DIR (*(volatile unsigned int *)0x2009c020)
#define FIO1PIN (*(volatile unsigned int *)0x2009c034)

// Registers for port 2
#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)

#define PINMODE0 (*(volatile unsigned int *)0x4002c040)
#define PINMODE1 (*(volatile unsigned int *)0x4002c044)

void wait(float sec)
{
  volatile int count = sec*21.33e6;
  while (count>0) count--;
}
void intpins(){
    FIO1DIR |= (1<<18); // LED 1: Output
     FIO1DIR |= (1<<20); // LED 2: Output
     FIO1DIR |= (1<<21); // LED 3: Output
     FIO1DIR |= (1<<23); // Led 4: Output
  
    //REDLEDS
     FIO0DIR |= (1<<16);//pin 14 output
     FIO0DIR |= (1<<25);//pin 17 output

     //GREENLEDS
     FIO2DIR |= (1<<2); //pin24 output
     FIO2DIR |= (1<<5); //pin 21 output

     //input
     //red button p11
     FIO0DIR &= ~(1u<<18);
     //green button p28
     FIO0DIR &= ~(1u<<10);

     PINMODE0 |= (1u<<20) | (1u<<21);
     PINMODE1  |= (1u<<4) | (1u<<5);
}
int buttonPush (int bit){
    return FIO0PIN >> bit & 1;
}

void write (int bit[]){

    if(bit[0]==1){
        FIO0PIN |= (1<<25);
    }
    else{
        FIO0PIN &= ~(1<<25);
    }
    if(bit[1]==1){
        FIO0PIN |= (1<<16);
    }
    else{
         FIO0PIN &= ~(1<<16);
    }
    if(bit[2]==1){
         FIO1PIN |= (1<<18);
    }
    else{
         FIO1PIN &= ~(1<<18);
    }
    if(bit[3]==1){
         FIO1PIN |= (1<<20);
    }
    else{
        FIO1PIN &= ~(1<<20);
    }
    if(bit[4]==1){
        FIO1PIN |= (1<<21);
    }
    else{
        FIO1PIN &= ~(1<<21);
    }
    if(bit[5]==1){
        FIO1PIN |= (1<<23);
    }
    else{
        FIO1PIN &= ~(1<<23);
    }
    if(bit[6]==1){
        FIO2PIN |= (1<<2);
    }
    else{
        FIO2PIN &= ~(1<<2);
    }
    if(bit[7]==1){
        FIO2PIN |= (1<<5);
    }
    else{
        FIO2PIN &= ~(1<<5);
    }

    /*
    if(bit ==0){
        FIO0PIN |= (1<<25);
    }
    
    if(bit==1){
        FIO0PIN |= (1<<16);
    }
    
    if(bit==2){
        FIO1PIN |= (1<<18);
    }
    

    if(bit==3){
        FIO1PIN |= (1<<20);
    }
    
    if(bit==4){
         FIO1PIN |= (1<<21);
    }
    
    if(bit==5){
         FIO1PIN |= (1<<23); // Led 4: Output
    }
   
    if(bit==6){
        FIO2PIN |= (1<<2);
    }
    
    if(bit==7){
        FIO2PIN |= (1<<5);
    }     
    */
}


void reverse(int arr[], int start, int end) {
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        ++start;
        --end;
    }
}

void rotateRight(int arr[], int n, int k) {
    // normalize k to be within the range [0, n)
    k %= n;
    if (k < 0) {
        k += n;
    }

    // reverse the first n-k elements
    reverse(arr, 0, n-k-1);

    // reverse the remaining k elements
    reverse(arr, n-k, n-1);

    // reverse the entire array
    reverse(arr, 0, n-1);
}

void rotateLeft(int arr[], int n, int d) {
    for (int i = 0; i < d; i++) {
        int temp = arr[0];
        for (int j = 0; j < n - 1; j++) {
            arr[j] = arr[j + 1];
        }
        arr[n - 1] = temp;
    }
}

int main() {
    intpins();
    int score[8] = {0,0,0,1,1,0,0,0};
    write(score);
/*
    for(int i =0; i < sizeof(score); i++){
        if(score[i]==1){
            write(i);
        }
    }
*/
    while(1){
        
        if(score[0] == 1 && score[1]==1) {
            while(1){
                wait(1);
            }

        }
        if(score[6] == 1 && score[7] ==1){
            while(1){
                wait(1);
            }
        }

        
        if(buttonPush(10)){

            int n = sizeof(score) / sizeof(score[0]);
            int k = 1; // rotate by 1 positions to the right

            rotateRight(score, n, k);
            write(score);
            wait(0.2);
        }
        
       if(buttonPush(18)){
            int n = sizeof(score) / sizeof(score[0]);
            int d = 1; // number of positions to rotate left

            rotateLeft(score, n, d);
            write(score);
            wait(0.2);
       }

       //wait(0.2);
    }
return 0;


}


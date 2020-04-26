#include "TELAIO.h"
// Include display library
#include <TM1637Display.h>
#include <string>
#include <ctime>


// keep in mind that D0 and D4 are already used by board LEDs
#define TM1637_CLK D1    // chip clock
#define TM1637_DIO D2    // chip digital I/O

// setup the 4-Digit Display
TM1637Display display(TM1637_CLK, TM1637_DIO);

void setup() {
  initSetup();//inizializza wifi lcd time
  
}

void loop() {
  int i, j, k;
  display.setBrightness(0x02);// imposta luminosita' basso
  time_t now = time(nullptr);
  tm *ltm = localtime(&now);
  //Serial.println((String)ctime(&now));
  //Serial.println(ltm->tm_hour);//ora
  //Serial.println(ltm->tm_min);//minuti

  //convert to number 4 digit
  int timenumber = (int)ltm->tm_hour*100+(int)ltm->tm_min;
  //display.showNumberDecEx(timenumber, 0b11100000, false, 4, 0);

    /*
    display.showNumberDecEx(0, (0x80 >> 0), true);
    delay(1000);
    display.showNumberDecEx(1, (0x80 >> 1), true);
    delay(1000);
    
    for(i=0; i <= 23; i++) {
      for(j=0; j<=59; j++){
        display.showNumberDecEx(i*100+j, (0x80 >> 1), true);
        delay(50);
      }
    }*/
   
    for(k=0; k <= 1; k++) {
    display.showNumberDecEx(timenumber, (0x80 >> k), true);
    delay(500);
    }
    
  
     
    
    


}

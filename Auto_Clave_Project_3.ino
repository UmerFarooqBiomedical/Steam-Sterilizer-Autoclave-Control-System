#include <doxygen.h>
#include <NexButton.h>
#include <NexCheckbox.h>
#include <NexConfig.h>
#include <NexCrop.h>
#include <NexDualStateButton.h>
#include <NexGauge.h>
#include <NexGpio.h>
#include <NexHardware.h>
#include <NexHotspot.h>
#include <NexNumber.h>
#include <NexObject.h>
#include <NexPage.h>
#include <NexPicture.h>
#include <NexProgressBar.h>
#include <NexRadio.h>
#include <NexRtc.h>
#include <NexScrolltext.h>
#include <NexSlider.h>
#include <NexText.h>
#include <NexTimer.h>
#include "Nextion.h"
#include <NexTouch.h>
#include <NexUpload.h>
#include <NexVariable.h>
#include <NexWaveform.h>





NexPage page0    = NexPage(0, 0, "page0");
NexPage page1    = NexPage(1, 0, "page1");
NexPage page2    = NexPage(2, 0, "page2");
NexPage page3    = NexPage(3, 0, "page3");
NexPage page5    = NexPage(4, 0, "page5");

NexText t5 = NexText(1, 6, "t5"); // Declare a text object [page id:0,component id:2, component name: "textNumber"].
NexText startText = NexText(0, 3, "startText"); // Declare a text object [page id:0,component id:2, component name: "textNumber"].

NexButton startButton = NexButton(0, 2, "startButton");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton checkButton = NexButton(0, 4, "checkButton");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].

NexButton b0 = NexButton(2, 3, "b0");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton b1 = NexButton(2, 4, "b1");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton b2 = NexButton(2, 5, "b2");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton b3 = NexButton(2, 6, "b3");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton b6 = NexButton(2, 7, "b6");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton b7 = NexButton(2, 8, "b7");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton b8 = NexButton(2, 9, "b8");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton b9 = NexButton(2, 10, "b9");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton b10 = NexButton(2, 11, "b10");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton doButton = NexButton(4, 2, "doButton");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton duButton = NexButton(0, 6, "duButton");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton do1Button = NexButton(0, 7, "do1Button");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton homeButton = NexButton(4, 14, "homeButton");// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].

NexNumber n1 = NexNumber(1, 4, "n1");
NexProgressBar j0  = NexProgressBar(1, 7, "j0");


#include "max6675.h"
float starttime = millis();
float endtime = starttime;
int ktcSO = 8;
int ktcCS = 9;
int ktcCLK = 10;


MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

int dcs = 27; // DOOR CLOSE SWITCH
int ts = A0; // Temperature sensor
int dlock =37; // Door Seal Exhaust Valve RELAY 1
int vv = 45; // Vaccum Valve RELAY 2
int wv = 47; // Water Valve RELAY 3
int vp = 49; // Vaccum Pump RELAY 4
float tsx = 0;

int stcv = 51; // RELAY 5
int ev = 53; // Exhaust Valve RELAY 6
int atm = 35; // ATM RELAY 7
int re = 39; // RELAY 8
int pswitch = 31; // pressure switch
//const int sb = 27; // START BUTTON
int dcsx = digitalRead(dcs);
//int tsx = map(analogRead(ts), 0,1024,0,150);
int ps = digitalRead(pswitch);
//int s= digitalRead(sb); // s = start



bool secondpulse = false;
bool thirdpulse = false;
bool fourthpulse = false;
bool fifthpulse = false;
bool sixthpulse = false;
bool first = false;

/*
   Register object textNumber, buttonPlus, buttonMinus, to the touch event list.
*/
NexTouch *nex_listen_list[] =
{
  &page0,
  &page1,
  &page2,
  &page3,
  &page5,
  &t5,
  &startText,
  &startButton,

  &checkButton,
  &doButton,
  &duButton,
  &do1Button,
  &homeButton,
  &b0,
  &b1,
  &b2,
  &b3,
  &b6,
  &b7,
  &b8,
  &b9,
  &b10,
  &n1,
  NULL
};
/*
   Button0 component pop callback function.
   In this example,the value of the text component will plus one every time when button0 is released.
*/




void startButtonPopCallback(void *ptr)
{
  dbSerialPrintln("startButton");
  MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

  tsx = ktc.readCelsius();


  for (;;)
  {

    uint32_t number = 0;
    j0.getValue(&number);
    j0.setValue(number);
    //int tsx = map(analogRead(ts), 0,1024,0,150);
    tsx = ktc.readCelsius();
    MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

    // tsx = ktc.readCelsius();

    int dcsx = digitalRead(dcs);
    int ps = digitalRead(pswitch);
    n1.setValue(tsx);
    /////////////////////////////////////////////////////////
    ///////////////////Algorithm////////////////////////////
    ///////////////////////////////////////////////////////






    if (secondpulse == false)
    {

      n1.setValue(tsx);
      if (secondpulse == false && dcsx == HIGH)
      {
        //tsx = ktc.readCelsius();
        page1.show();

        n1.setValue(tsx);
        float endtime4 = millis() + 180000;
        for (; millis() <= endtime4;)

        {
          number = 0;
          tsx = ktc.readCelsius();
          delay(200);
          j0.setValue(number);
          t5.setText("Vaccum Phase");
          digitalWrite(dlock, LOW);
          digitalWrite(vv, LOW);
          digitalWrite(ev, HIGH);
          digitalWrite(wv, LOW);
          digitalWrite(vp, LOW);
          n1.setValue(tsx);
          dbSerialPrintln("Vaccum Phase");
        }
        // delay(5000);
        n1.setValue(tsx);
        secondpulse = true;
        n1.setValue(tsx);
      }
      n1.setValue(tsx);
    }
    n1.setValue(tsx);
    if (secondpulse == true && dcsx == HIGH && thirdpulse == false && fourthpulse == false && fifthpulse == false && sixthpulse == false)
    {
      for (; tsx <= 134;)
      {
        tsx = ktc.readCelsius();
        n1.setValue(tsx);
        digitalWrite(vv, HIGH);
        digitalWrite(wv, HIGH);
        digitalWrite(vp, HIGH);

        n1.setValue(tsx);
        n1.setValue(tsx);
        t5.setText("Heating to Sterilization");
        dbSerialPrintln("Heating to Sterilization");

        number = 20;
        j0.setValue(number);
        n1.setValue(tsx);
        digitalWrite(dlock, LOW);
        digitalWrite(stcv, LOW);
        thirdpulse = true;
        n1.setValue(tsx);
      }
    }

    if (dcsx == HIGH && tsx >= 134 && thirdpulse == true && fourthpulse == false && fifthpulse == false && sixthpulse == false)
    {
      //tsx = ktc.readCelsius();
      float endtime3 = millis() + 300000;
      for (; millis() <= endtime3;)

      {
        t5.setText("Sterilization");
        tsx = ktc.readCelsius();
        delay(200);

        n1.setValue(tsx);
        // tsx = map(analogRead(ts), 0,1024,0,150);

        if (dcsx == HIGH && tsx <= 132 && thirdpulse == true && fourthpulse == false && fifthpulse == false && sixthpulse == false)
        {

          digitalWrite(dlock, LOW);
          digitalWrite(stcv, LOW);


        }
        else if (dcsx == HIGH && tsx >= 136 && thirdpulse == true && fourthpulse == false && fifthpulse == false && sixthpulse == false)
        {

          digitalWrite(stcv, HIGH);



        }
      }



      delay(200);
      n1.setValue(tsx);
      fourthpulse = true;
    }



    if (secondpulse == true && dcsx == HIGH && digitalRead(pswitch) == HIGH && thirdpulse == true && fourthpulse == true && fifthpulse == false && sixthpulse == false)
    {
      for (; digitalRead(pswitch) == HIGH;)
      {

        tsx = ktc.readCelsius();
        delay(200);
        n1.setValue(tsx);
        number = 40;
        j0.setValue(number);
        digitalWrite(stcv, HIGH);
        digitalWrite(dlock, LOW);
        digitalWrite(ev, LOW);
        t5.setText("Exhaust");

      }
    }
    if (secondpulse == true && dcsx == HIGH && ps == LOW && thirdpulse == true && fourthpulse == true && fifthpulse == false && sixthpulse == false)
    {
      tsx = ktc.readCelsius();
      delay(200);
      n1.setValue(tsx);
      digitalWrite(ev, HIGH);
      fifthpulse = true;
    }



    if (secondpulse == true && dcsx == HIGH && thirdpulse == true && fourthpulse == true && fifthpulse == true && sixthpulse == false)
    {

      float endtime7 = millis() + 360000;
      for (; millis() <= endtime7;)
      {
        tsx = ktc.readCelsius();
        delay(200);
        n1.setValue(tsx);
        number = 60;
        j0.setValue(number);


        digitalWrite(dlock, LOW);
        digitalWrite(vv, LOW);
        digitalWrite(wv, LOW);
        digitalWrite(vp, LOW);
        t5.setText("Drying");

        n1.setValue(tsx);

      }
      delay(200);
      n1.setValue(tsx);
      digitalWrite(vv, HIGH);
      digitalWrite(wv, HIGH);
      digitalWrite(vp, HIGH);

      number = 80;
      j0.setValue(number);

      float endtime2 = millis() + 180000;
      for (; millis() <= endtime2;)
      {

        tsx = ktc.readCelsius();
        delay(200);
        n1.setValue(tsx);
        t5.setText("Fresh Air");
        digitalWrite(atm, LOW);
        
      }
      n1.setValue(tsx);
      digitalWrite(atm, HIGH);
       number = 90;
      t5.setText("Door Exhaust");
      j0.setValue(number);

      float endtime5 = millis() + 60000;
      for (; millis() <= endtime5;)
      {
        tsx = ktc.readCelsius();
        delay(200);
        n1.setValue(tsx);
        digitalWrite(re, LOW);
        digitalWrite(wv, LOW);
        digitalWrite(vp, LOW);
        
      }
      digitalWrite(re, HIGH);
      digitalWrite(wv, HIGH);
      digitalWrite(vp, HIGH);
      delay(200);
      n1.setValue(tsx);

      number = 100;
      t5.setText("Cycle Ended");
      j0.setValue(number);
      delay(5000);
      page5.show();
      sixthpulse = true;
      return 0;
    }

    if (dcsx == LOW)
    {
      page0.show();
      startText.setText("Warning: Door Switch Opened");

      dbSerialPrintln("Warning: Close Door");
      digitalWrite(dlock, HIGH);
      digitalWrite(vv, HIGH);
      digitalWrite(wv, HIGH);
      digitalWrite(vp, HIGH);
      digitalWrite(stcv, HIGH);
      digitalWrite(ev, LOW);
      digitalWrite(atm, HIGH);
      digitalWrite(re, HIGH);
      return 0;
    }
  }
}



void checkButtonPopCallback(void *ptr)
{
  dbSerialPrintln("checkButton");
  page2.show();


}
void b0PushCallback(void *ptr)
{
  digitalWrite(dlock, LOW);
}
void b0PopCallback(void *ptr)
{
  digitalWrite(dlock, HIGH);
}

void b1PushCallback(void *ptr)
{
  digitalWrite(vp, LOW);
}
void b1PopCallback(void *ptr)
{
  digitalWrite(vp, HIGH);
}

void b6PushCallback(void *ptr)
{
  digitalWrite(vv, LOW);
}
void b6PopCallback(void *ptr)
{
  digitalWrite(vv, HIGH);
}

void b2PushCallback(void *ptr)
{
  digitalWrite(wv, LOW);
}
void b2PopCallback(void *ptr)
{
  digitalWrite(wv, HIGH);
}
void b7PushCallback(void *ptr)
{
  digitalWrite(stcv, LOW);
}
void b7PopCallback(void *ptr)
{
  digitalWrite(stcv, HIGH);
}
void b3PushCallback(void *ptr)
{
  digitalWrite(ev, LOW);
}
void b3PopCallback(void *ptr)
{
  digitalWrite(ev, HIGH);
}
void b8PushCallback(void *ptr)
{
  digitalWrite(atm, LOW);
}
void b8PopCallback(void *ptr)
{
  digitalWrite(atm, HIGH);
}

void b9PushCallback(void *ptr)
{
  digitalWrite(re, LOW);
}
void b9PopCallback(void *ptr)
{
  digitalWrite(re, HIGH);
}
void b10PopCallback(void *ptr)
{
  dbSerialPrintln("b10");
  page0.show();
}


void do1ButtonPopCallback(void *ptr)
{
  dbSerialPrintln("do1Button");
  for (;;)
  {
    int dcsx = digitalRead(dcs);
    loop();
    if (dcsx == HIGH)
    {
      digitalWrite(dlock, LOW);
      startText.setText("Door Locked, Press Start Button");

    }
    else if (dcsx == LOW)
    {
      digitalWrite(dlock, HIGH);
      startText.setText("Close the door");

    }
    return 0;
  }
}

void duButtonPopCallback(void *ptr)
{
  dbSerialPrintln("duButton");
  digitalWrite(dlock, HIGH);
  startText.setText("Door Unlocked");
}

void doButtonPushCallback(void *ptr)
{
  dbSerialPrintln("doButton");
  digitalWrite(dlock, HIGH);
}


void homeButtonPushCallback(void *ptr)
{
  dbSerialPrintln("homeButton");
  page0.show();
  secondpulse = false;
  thirdpulse = false;
  fourthpulse = false;
  fifthpulse = false;
  sixthpulse = false;

}


void setup(void)
{
  //INPUT & OUTPUT DECLARATION
  //pinMode(sb, INPUT);
  pinMode(dcs, INPUT);

  pinMode(dlock, OUTPUT);
  pinMode(vv, OUTPUT);
  pinMode(wv, OUTPUT);
  pinMode(vp, OUTPUT);
  pinMode(stcv, OUTPUT);
  pinMode(ts, INPUT);
  pinMode(ev, OUTPUT);
  pinMode(atm, OUTPUT);
  pinMode(pswitch, INPUT);
  pinMode(re, OUTPUT);




  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  nexInit();

  Serial.begin(115200);

  /* Register the pop event callback function of the current button0 component. */
  startButton.attachPop(startButtonPopCallback);

  checkButton.attachPop(checkButtonPopCallback);


  doButton.attachPush(doButtonPushCallback);
  duButton.attachPop(duButtonPopCallback);
  do1Button.attachPop(do1ButtonPopCallback);
  homeButton.attachPush(homeButtonPushCallback);
  b0.attachPop(b0PopCallback);
  b0.attachPush(b0PushCallback);
  b1.attachPop(b1PopCallback);
  b1.attachPush(b1PushCallback);
  b2.attachPop(b2PopCallback);
  b2.attachPush(b2PushCallback);
  b3.attachPop(b3PopCallback);
  b3.attachPush(b3PushCallback);
  b6.attachPop(b6PopCallback);
  b6.attachPush(b6PushCallback);
  b7.attachPop(b7PopCallback);
  b7.attachPush(b7PushCallback);
  b8.attachPop(b8PopCallback);
  b8.attachPush(b8PushCallback);
  b9.attachPop(b9PopCallback);
  b9.attachPush(b9PushCallback);
  b10.attachPop(b10PopCallback);



  dbSerialPrintln("Setup done");
}

void loop(void)
{

  if (first == false)
  {

    digitalWrite(dlock, HIGH);
    digitalWrite(vv, HIGH);
    digitalWrite(wv, HIGH);
    digitalWrite(vp, HIGH);
    digitalWrite(stcv, HIGH);
    digitalWrite(ev, LOW);
    digitalWrite(atm, HIGH);
    digitalWrite(re, HIGH);
    page3.show();

    delay(10000);
    page0.show();

    first = true;
  }






  nexLoop(nex_listen_list);

}



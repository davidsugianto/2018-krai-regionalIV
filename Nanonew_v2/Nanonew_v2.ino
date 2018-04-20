#include <PS2X_lib.h>
PS2X ps2x;
int ir64, error = 0;
byte type = 0, vibrate = 0;
int LY, LX, RY, RX, LYold, LXold, RYold, RXold;
int control = 'A';
uint8_t tombol2=0, tombol=0, tombol3=0, tombol4=0, tombol5=0;

///////////////////////////////Swicth/////////////////////////////
#define limitkanan  4
//#define limitkiri   3
#define limitstick  A5
#define limitslider 9
///////////////////////////////Motor//////////////////////////////
#define kanan   A2    //
#define kiri    A3    //
#define pwm1    5    //
#define maju    A0    //
#define mundur  A1    //
#define pwm2    6    //
///////////////////////////////encoder//////////////////////////////
#define atasA   2
#define atasB   3

float
atas = 0,
jariroda = 2.2, pulsa = 134,
kll = 2 * PI * jariroda,
cm = pulsa / kll, jarak = 0;

void setup() {
  pinMode(kanan, OUTPUT);
  pinMode(kiri, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(maju, OUTPUT);
  pinMode(mundur, OUTPUT);
  pinMode(pwm2, OUTPUT);
  pinMode(limitkanan, INPUT_PULLUP);
  pinMode(limitstick, INPUT_PULLUP);
  pinMode(limitslider, INPUT_PULLUP);
  //pinMode(limitkiri, INPUT_PULLUP);
  pinMode(atasB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(atasA), counteratas, RISING);
  digitalWrite(kanan, HIGH);
  digitalWrite(kiri, HIGH);
  digitalWrite(pwm1, HIGH);
  digitalWrite(maju, HIGH);
  digitalWrite(mundur, HIGH);
  digitalWrite(pwm2, HIGH);

  // latas = atas;
  // timer = millis();

  Serial.begin(9600);
  error = ps2x.config_gamepad(13, 11, 10, 12, false, false);
  if (error == 0) {
  }
}

void loop() {
  //jarak = kll * (atas / pulsa);
//  Serial.println(atas);
   //prints();
   if (Serial.available() > 0) {
     ir64 = Serial.read();
   }
   if (digitalRead(limitkanan) == LOW)
   {
     Serial.println("limitkanan");
     digitalWrite(maju, LOW);
     digitalWrite(mundur, HIGH);
     analogWrite(pwm2, 0);
     delay(60);
     digitalWrite(maju, HIGH);
     digitalWrite(mundur, HIGH);
     analogWrite(pwm2, 255);
   }
   if (ir64 == 't')
   {
     digitalWrite(maju, LOW);
     digitalWrite(mundur, HIGH);
     analogWrite(pwm2, 0);
   }
   if (digitalRead(limitslider) == LOW)
    {
    digitalWrite(maju, HIGH);
    digitalWrite(mundur, LOW);
    analogWrite(pwm2, 0);
    delay(100);
    digitalWrite(maju, HIGH);
    digitalWrite(mundur, HIGH);
    analogWrite(pwm2, 255);
    }
    if (ir64 == 'u')
    {
      digitalWrite(maju, HIGH);
      digitalWrite(mundur, HIGH);
      analogWrite(pwm2, 255);
    }
    if (ir64 == 'b')
    {
      digitalWrite(maju, LOW);
      digitalWrite(mundur, HIGH);
      analogWrite(pwm2, 0);
      delay(100);
      digitalWrite(maju, HIGH);
      digitalWrite(mundur, HIGH);
      analogWrite(pwm2, 255);
    }
    if (ir64 == 'a')
    {
      digitalWrite(maju, LOW);
      digitalWrite(mundur, HIGH);
      analogWrite(pwm2, 0);
      if (digitalRead(limitslider) == LOW)
       {
       digitalWrite(maju, HIGH);
       digitalWrite(mundur, LOW);
       analogWrite(pwm2, 0);
       delay(200);//100
       digitalWrite(maju, HIGH);
       digitalWrite(mundur, HIGH);
       analogWrite(pwm2, 255);
       Serial.print("q");
       ir64 = 'z';
       }
    }
    if (ir64 == 'b')
    {
      digitalWrite(maju, HIGH);
      digitalWrite(mundur, LOW);
      analogWrite(pwm2, 0);
      if (digitalRead(limitslider) == LOW)
       {
       digitalWrite(maju, LOW);
       digitalWrite(mundur, HIGH);
       analogWrite(pwm2, 0);
       delay(100);
       digitalWrite(maju, HIGH);
       digitalWrite(mundur, HIGH);
       analogWrite(pwm2, 255);
       //Serial.print("w");
       ir64 = 'c';
       }
    }
    if (ir64 == 'd')
    {
      digitalWrite(maju, LOW);
      digitalWrite(mundur, HIGH);
      analogWrite(pwm2, 0);
      if (digitalRead(limitslider) == LOW)
       {
       digitalWrite(maju, HIGH);
       digitalWrite(mundur, LOW);
       analogWrite(pwm2, 0);
       delay(90);
       digitalWrite(maju, HIGH);
       digitalWrite(mundur, HIGH);
       analogWrite(pwm2, 255);
       Serial.print("w");
       ir64 = 'c';
       }
    }

   ps2x.read_gamepad(false, vibrate);

   if (ps2x.ButtonPressed(PSB_PAD_UP))
   { Serial.print("A"); }

   if (ps2x.ButtonReleased(PSB_PAD_UP))
   { Serial.print("Z"); }

   if (ps2x.ButtonPressed(PSB_PAD_DOWN))
   { Serial.print("B"); }

   if (ps2x.ButtonReleased(PSB_PAD_DOWN))
   { Serial.print("Z"); }

   if (ps2x.ButtonPressed(PSB_PAD_LEFT))
   { Serial.print("C"); }

   if (ps2x.ButtonReleased(PSB_PAD_LEFT))
   { Serial.print("Z"); }

   if (ps2x.ButtonPressed(PSB_PAD_RIGHT))
   { Serial.print("D"); }

   if (ps2x.ButtonReleased(PSB_PAD_RIGHT))
   { Serial.print("Z"); }

   if (ps2x.ButtonPressed(PSB_START))
   {
     tombol4++;
     if (tombol4>1)
       {
         tombol4=0;
       }
     if (tombol4 == 0)
       {
         Serial.print("F");
       }
     else if (tombol4 == 1)
       {
         Serial.print("K");
       }
   }

   if (ps2x.ButtonReleased(PSB_START))
   {
     Serial.print("1");
   }

   if (ps2x.ButtonPressed(PSB_SELECT))
   {
     Serial.print("H");
   }

   if (ps2x.ButtonReleased(PSB_SELECT))
   {
   }

   if (ps2x.ButtonPressed(PSB_TRIANGLE))
   {
         Serial.print("G");
         digitalWrite(maju, LOW);
         digitalWrite(mundur, HIGH);
         analogWrite(pwm2, 0);
   }

   if (ps2x.ButtonReleased(PSB_TRIANGLE))
   {  }

   if (ps2x.ButtonPressed(PSB_CIRCLE)) //lingkaran
   {
     Serial.print("I");
   }

   if (ps2x.ButtonReleased(PSB_CIRCLE))
   {
     Serial.print("1");
   }

   if (ps2x.ButtonPressed(PSB_SQUARE)) //kotak
   {
     Serial.print("Y");
     digitalWrite(maju, LOW);
     digitalWrite(mundur, HIGH);
     analogWrite(pwm2, 0);
     // Serial.print("E");
   }

   if (ps2x.ButtonReleased(PSB_SQUARE))
   { //Serial.print("Z");
   }

   if (ps2x.ButtonPressed(PSB_CROSS))
   {
     Serial.print("J");
     digitalWrite(maju, LOW);
     digitalWrite(mundur, HIGH);
     analogWrite(pwm2, 0);
     delay(500);
     digitalWrite(maju, HIGH);
     digitalWrite(mundur, HIGH);
     analogWrite(pwm2, 255);
   }

   if (ps2x.ButtonReleased(PSB_CROSS))
   { }

   if (ps2x.ButtonPressed(PSB_L2))
   {
     Serial.print("S");
   }

   if (ps2x.ButtonReleased(PSB_L2))
   {
     //Serial.print("2");
     //putar(kanan, kiri, 255, HIGH, HIGH);
     Serial.print("1");
   }

   if (ps2x.ButtonPressed(PSB_R1))
   { Serial.print("L"); }

   if (ps2x.ButtonReleased(PSB_R1))
   { Serial.print("Z"); }

   if (ps2x.ButtonPressed(PSB_L1))
   { Serial.print("M"); }

   if (ps2x.ButtonReleased(PSB_L1))
   { Serial.print("Z"); }

   if (ps2x.ButtonPressed(PSB_R2))
   {
     Serial.print("X");
   }

   if (ps2x.ButtonReleased(PSB_R2))
   {
     Serial.print("1");
     //putar(kanan, kiri, 255, HIGH, HIGH);

   }

   if (ps2x.ButtonPressed(PSB_L3))
   {
     Serial.print("O");
   }

   if (ps2x.ButtonReleased(PSB_L3))
   {
     Serial.print("1");
   }

   if (ps2x.ButtonPressed(PSB_R3))
   {
     Serial.print("P");
   }

   if (ps2x.ButtonReleased(PSB_R3))
   {
     Serial.print("1");
   }

   LY = (int) ps2x.Analog(PSS_LY);
   LX = (int) ps2x.Analog(PSS_LX);
   RY = (int) ps2x.Analog(PSS_RY);
   RX = (int) ps2x.Analog(PSS_RX);

   if (LX != LXold || LY != LYold)
   {
     if (LY == 0 && LX == 123) //majupelan
     {
      // Serial.print("aa");
     }

     if (LY == 255 && LX == 123) //mundurpelan
     {
      // Serial.print("bb");
     }

     if (LY == 123 && LX == 0) //kiripelan
     { //Serial.print("cc");
        putar(kanan, kiri, 195, HIGH, LOW);
     }

     if (LY == 123 && LX == 255) //kananpelan
     { //Serial.print("dd");
        putar(kanan, kiri, 195, LOW, HIGH);
     }

     if (LY == 123 && LX == 123) //stopotor
     {
       // slider(maju, mundur, 255, HIGH, HIGH);
       putar(kanan, kiri, 255, HIGH, HIGH);
       //Serial.println("stop");
     }
  // Serial.print(LX);
  // Serial.print(", ");
  // Serial.println(LY);
   }

   if (RX != RXold || RY != RYold)
   {
     if (RY == 0 && RX == 123) //majupelan
     {
       //Serial.print("ff");
       slider(maju, mundur, 0, LOW, HIGH);
     }

     if (RY == 255 && RX == 123) //mundurpelan
     {
       //Serial.print("gg");
      slider(maju, mundur, 0, HIGH, LOW);
     }

     if (RY == 123 && RX == 0) //kiripelan
     {
       //Serial.print("hh");
     }

     if (RY == 123 && RX == 255) //kananpelan
     { //Serial.print("jj");
     }

     if (RY == 132 && RX == 123) //stopotor
     {
       // slider(maju, mundur, 255, HIGH, HIGH);
       slider(maju, mundur, 255, HIGH, HIGH);
       //Serial.println("stop");
     }
  // Serial.print(RX);
  // Serial.print(", ");
  // Serial.println(RY);
   }
   LYold = LY;
   LXold = LX;
   RYold = RY;
   RXold = RX;
   delay(20);
}

void slider2()
{
  digitalWrite(maju, LOW);
  digitalWrite(mundur, HIGH);
  analogWrite(pwm2, 0);
  if (digitalRead(limitslider) == LOW)
   {
   digitalWrite(maju, HIGH);
   digitalWrite(mundur, LOW);
   analogWrite(pwm2, 0);
   delay(100);
   digitalWrite(maju, HIGH);
   digitalWrite(mundur, HIGH);
   analogWrite(pwm2, 255);
   }
}

void putar(int a, int b, int c, int d, int e)
{
  digitalWrite(a, d);
  digitalWrite(b, e);
  analogWrite(pwm1, c);
}

void slider(int a, int b, int c, int d, int e)
{
  digitalWrite(a, d);
  digitalWrite(b, e);
  analogWrite(pwm2, c);
}

// void prints()
// {
//   jarak = kll * (atas / pulsa);
//   Serial.print("jarak: ");
//   Serial.print(jarak);
//   Serial.print(" ");
//   Serial.print("atas: ");
//   Serial.println(atas);
// }

void TZ1()
{
    //Serial.print("mulai");
    while (1) {
    jarak = kll * (atas / pulsa);
    // putar(kanan, kiri, 195, LOW, HIGH);
    if (jarak <= 10 )
    {
      //putar(kanan, kiri, 255, HIGH, HIGH);
      putar(kanan, kiri, 215, LOW, HIGH);
      //Serial.println("putark ke kanan ");
    }
    else
    {
      putar(kanan, kiri, 255, HIGH, HIGH);
      //Serial.println("berhenti");
      break;
    }
  }
}

void trial1()
{
    while (1) {
    jarak = kll * (atas / pulsa);
    //putar(kanan, kiri, 195, LOW, HIGH);
    if (jarak >= 9.8 )
    {
      putar(kanan, kiri, 215, HIGH, LOW);
      Serial.println("putark ke kiri ");
      //putar(kanan, kiri, 195, HIGH, LOW);
    }
    else
    {
      Serial.println("berhenti emas");
      putar(kanan, kiri, 255, HIGH, HIGH);
      break;
    }
  }
}

void trial2()
{
    while (1) {
    jarak = kll * (atas / pulsa);
    //putar(kanan, kiri, 195, LOW, HIGH);
    if (jarak >= 6.7 )
    {
      putar(kanan, kiri, 215, HIGH, LOW);
      Serial.println("putark ke kiri ");
      //putar(kanan, kiri, 195, HIGH, LOW);
    }
    else
    {
      Serial.println("berhenti emas");
      putar(kanan, kiri, 255, HIGH, HIGH);
      break;
    }
  }
}

void trial3()
{
    while (1) {
    jarak = kll * (atas / pulsa);
    //putar(kanan, kiri, 195, LOW, HIGH);
    if (jarak >= 3 )
    {
      putar(kanan, kiri, 215, HIGH, LOW);
      Serial.println("putark ke kiri ");
      //putar(kanan, kiri, 195, HIGH, LOW);
    }
    else
    {
      Serial.println("berhenti emas");
      putar(kanan, kiri, 255, HIGH, HIGH);
      break;
    }
  }
}

void trial4()
{
    while (1) {
    jarak = kll * (atas / pulsa);
    if (jarak <= 10 )
    {
      putar(kanan, kiri, 215, LOW, HIGH);
    }
    else
    {
      putar(kanan, kiri, 255, HIGH, HIGH);
      break;
    }
  }
}

void trial5()
{
    while (1) {
    jarak = kll * (atas / pulsa);
    if (jarak <= 8 )
    {
      putar(kanan, kiri, 215, LOW, HIGH);
    }
    else
    {
      putar(kanan, kiri, 255, HIGH, HIGH);
      break;
    }
  }
}

void trial6()
{
    while (1) {
    jarak = kll * (atas / pulsa);
    if (jarak <= 5 )
    {
      putar(kanan, kiri, 215, LOW, HIGH);
    }
    else
    {
      putar(kanan, kiri, 255, HIGH, HIGH);
      break;
    }
  }
}

void trial7()
{
    while (1) {
    jarak = kll * (atas / pulsa);
    if (jarak <= 3 )
    {
      putar(kanan, kiri, 215, LOW, HIGH);
    }
    else
    {
      putar(kanan, kiri, 255, HIGH, HIGH);
      break;
    }
  }
}

void ambilemas()
{
    while (1) {
    jarak = kll * (atas / pulsa);
    //putar(kanan, kiri, 195, LOW, HIGH);
    if (jarak >= 0 )
    {
      putar(kanan, kiri, 215, HIGH, LOW);
      Serial.println("putark ke kiri ");
      //putar(kanan, kiri, 195, HIGH, LOW);
    }
    else
    {
      Serial.println("berhenti emas");
      putar(kanan, kiri, 255, HIGH, HIGH);
      break;
    }
  }
}

void counteratas() {
  if(digitalRead(atasA) && !digitalRead(atasB)) {
    atas += 1;
  }
  if(digitalRead(atasA) && digitalRead(atasB)) {
    atas -= 1;
  }
}

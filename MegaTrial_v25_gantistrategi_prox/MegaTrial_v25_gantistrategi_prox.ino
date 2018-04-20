//Mega trial fix v21 tz3dipercepat fix siap tanding
int control = 0, a ='0', dinding;
const int pingpin = A0;
#define proximity 25
#define proximity1 23
int data = 0, data1 = 0;

///////////////////////Motor/////////////////////////
#define kandep1   8    //R
#define kandep2   9    //L
#define kirdep1   6    //R
#define kirdep2   7    //L
#define kanbel1   12    //R
#define kanbel2   13    //L
#define kirbel1   10    //R
#define kirbel2   11    //L
#define maju      1
#define mundur    2
#define berhenti  3

float
pwmkandep = 0, pwmkirdep = 0,
pwmkanbel = 0, pwmkirbel = 0;

//////////////////////////Encoder/////////////////////////////
#define depankananA       3
#define depankananB       26
#define depankiriA        21
#define depankiriB        24
#define belakangkananA    19
#define belakangkananB    28
#define belakangkiriA     18
#define belakangkiriB     30
#define tengahA           2
#define tengahB           22

float
depkan = 0, depkir = 0, kanan = 0,
belkan = 0, belkir = 0, tengah = 0, tengah1 = 0,
enckandep = 0, enckirdep = 0,
enckanbel = 0, enckirbel = 0,
piddepkan, piddepkir, pidbelkan, pidbelkir;

volatile long int
ldepkan = 0, ldepkir = 0,
lbelkan = 0, lbelkir = 0, ltengah = 0,
ddepkan = 0, ddepkir = 0,
dbelkan = 0, dbelkir = 0, dtengah = 0;

int
rpskandep = 0, rpskirdep = 0,
rpskanbel = 0, rpskirbel = 0,
vrps = -80, vrps1 = -82, vrps2 = -80, vrps3 = -82, vrps4 = -80, vrps5 = -82,
v = 190, v1 = 15, v2 = 150, v3 = 107, vrpsa = 0, vrpsb = 0, v4 = 150, v5 = 107;
//v =173
float
jariroda = 7.85, pulsa = 134,
jari = 2.4, pulse = 400,
kll = 2 * PI * jariroda,
keliling = 2 * PI * jari,
cm = pulsa / kll, jarak = 0, jarak1 = 0;

/////////////////////////Pneumatic//////////////////////////
#define matic1A 32 //buka capit
#define matic1B 34 //tutup capit
#define matic2B 36  //tutup capit
#define matic2A 38  //buka capit
#define matic3B 40   //tutup capit
#define matic3A 42   //buka capit
#define matic4A 44  // buka capit
#define matic4B 46  //tutup capit
#define matic5A 51
#define matic5B 53

long ltime, ltime1, ltime2, ltime3, ltime4, timer, timer1, timer2, timer3, timer4, timer5, timer6;

void setup() {
  pinMode(kandep1, OUTPUT);
  pinMode(kandep2, OUTPUT);
  pinMode(kirdep1, OUTPUT);
  pinMode(kirdep2, OUTPUT);
  pinMode(kanbel1, OUTPUT);
  pinMode(kanbel2, OUTPUT);
  pinMode(kirbel1, OUTPUT);
  pinMode(kirbel2, OUTPUT);
  pinMode(matic1A, OUTPUT);
  pinMode(matic1B, OUTPUT);
  pinMode(matic2A, OUTPUT);
  pinMode(matic2B, OUTPUT);
  pinMode(matic3A, OUTPUT);
  pinMode(matic3B, OUTPUT);
  pinMode(matic4A, OUTPUT);
  pinMode(matic4B, OUTPUT);
  pinMode(matic5A, OUTPUT);
  pinMode(matic5B, OUTPUT);
  pinMode(proximity, INPUT_PULLUP);
  pinMode(proximity1, INPUT_PULLUP);

  digitalWrite(kandep1, LOW);
  digitalWrite(kandep2, LOW);
  digitalWrite(kanbel1, LOW);
  digitalWrite(kanbel2, LOW);
  digitalWrite(kirdep1, LOW);
  digitalWrite(kirdep2, LOW);
  digitalWrite(kirbel1, LOW);
  digitalWrite(kirbel2, LOW);
  digitalWrite(matic1A, LOW);
  digitalWrite(matic1B, LOW);
  digitalWrite(matic2A, LOW);
  digitalWrite(matic2B, LOW);
  digitalWrite(matic3A, LOW);
  digitalWrite(matic3B, LOW);
  digitalWrite(matic4A, LOW);
  digitalWrite(matic4B, LOW);
  digitalWrite(matic5A, LOW);
  digitalWrite(matic5B, LOW);

  Serial.begin(115200);
  Serial2.begin(9600);

  pinMode(depankananB, INPUT_PULLUP);
  pinMode(depankiriB, INPUT_PULLUP);
  pinMode(belakangkananB, INPUT_PULLUP);
  pinMode(belakangkiriB, INPUT_PULLUP);
  pinMode(tengahA, INPUT_PULLUP);
  pinMode(tengahB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(depankananA), counterkandep, RISING);
  attachInterrupt(digitalPinToInterrupt(depankiriA), counterkirdep, RISING);
  attachInterrupt(digitalPinToInterrupt(belakangkananA), counterkanbel, RISING);
  attachInterrupt(digitalPinToInterrupt(belakangkiriA), counterkirbel, RISING);
  attachInterrupt(digitalPinToInterrupt(tengahA), countertengah, RISING);

  ldepkan = depkan, ldepkir = depkir,
  lbelkan = belkan, lbelkir = belkir, ltengah = tengah;
  ltime1 = millis(); ltime2 = millis(); ltime3 = millis(); ltime4 = millis();
  timer = millis(); timer1 = millis(); timer2 = millis(); timer3 = millis();
  timer4 = millis(); timer5 = millis(), timer6 = millis();
  delay(10);
  stoptor(0);
}

void loop() {
  if (Serial2.available() > 0) {
    a = Serial2.read();
  }
  if (a == 'A') //up
  {
    ngiri();
  }
  if (a == 'B')//down
  {
    nganan();
  }
  else if (a == 'C') //kiri
  {
    downFast();
  }
  else if (a == 'D') //kanan
  {
    up();
  }
  else if (a == 'L') //R1
  {
    putarkiri();
  }
  else if (a == 'M') //L1
  {
    putarkanan();
  }
  else if (a == 'J')  //PSB_CROSS
  {
    mulai();
  }
  else if (a == 'G') //PSB_TRIANGLE
  {
    goEmas();
  }
  else if (a == 'Y') //PSB_TRIANGLE
  {
    goEmasTrial();
  }

  else if (a == 'I')
  {
    bukakok(matic5A);
    delay(300);
    downFast();
    delay(10);
    control = 1;
    while (control == 1)
    {
      control = 0;
    }
  }

  else if (a == 'S')
  {
    bukakok(matic1A);
  }

  else if (a == 'X')
  {
    bukakok(matic3A);
  }

  else if (a == 'q')
  {
    //SerialUSB.println("bukaTZ1");
    a = 0;
    //bukakok(matic3A);
    bukaTZ1();
  }

  // else if (a == 'w')
  // {
  //   SerialUSB.println("bukaTZ2");
  //   a = 0;
  //   bukaTZ2();
  // }

  else if (a == 'O')
  {
    bukakok(matic2A);
  }

  else if (a == 'P')
  {
    bukakok(matic4A);
    delay(300);
    downFast();
    delay(10);
    control = 1;
    while (control == 1)
    {
      control = 0;
    }
  }

  else if (a == 'F')
  {
    ambilkok();
  }

  else if (a == 'K')
  {
    bukakok2();
  }

  else if (a == 'H')
  {
    gotrial3();
  }

  else if (a == 'E')
  {
    goTZ2();
  }

  else if (a == 'Z')
  {
    stopmotor();
  }
}

void bukaTZ1()
{
  bukakok(matic3A);
  delay(100);
  Serial2.println("b");
}

void bukaTZ2()
{
  bukakok(matic4A);
  delay(200);
  down();
  delay(1000);
  stoptor(0);
  stopmotor();
}

void proximity_sensorbel()
{
  data1 = digitalRead(proximity1);
  if (data1 == 1)
  {
    RPSkandep(-15, 0.2, 0, 0.01);  RPSkirbel(-15, 0.2, 0, 0.01);
    RPSkirdep(-15, 0.2, 0, 0.01);  RPSkanbel(-15, 0.2, 0, 0.01);
    //SerialUSB.println("0");
  }
  else
  {
    //SerialUSB.println("1");
    stoptor(0);
    stopmotor();
    delay(350);
    ambilkok();
    mati();
    stoptor(0);
    stopmotor();
    control = 'C';
    while (control == 'C')
    {
      goTZ1();
      // a = 1;
      // control = 0;
      // break;
    }
  }
}

void proximity_sensorbel1()
{
  data = digitalRead(proximity);
  if (data == 1)
  {
    RPSkandep(-20, 0.2, 0, 0.01);  RPSkirbel(-20, 0.2, 0, 0.01);//15
    RPSkirdep(-20, 0.2, 0, 0.01);  RPSkanbel(-30, 0.2, 0, 0.01);
    //SerialUSB.println("0");
  }
  else
  {
    //SerialUSB.println("1");
    stoptor(0);
    stopmotor();
    delay(500);
    ambilkok();
    mati();
    stoptor(0);
    stopmotor();
    control = 'F';
    while (control == 'F')
    {
      goTZ3();
    }
    //control = 1;
  }
  while (control == 1)
  {
    control = 0;
  }
}

void mulai()
{
  jarak = keliling * (tengah / pulse);
  if (jarak > -145)//80
  {
    RPSkirdep(vrps1, 0.2, 0, 0.02);   RPSkirbel(vrps1, 0.2, 0, 0.02);
    RPSkandep(vrps, 0.2, 0, 0.02);    RPSkanbel(vrps, 0.2, 0, 0.02);
    softbrake(-20);
  }
  else
  {
    stoptor(0);
    delay(10);
    proximity_sensorbel();
  }
}

void goTZ1()
{
  //while (1) {
  jarak = keliling * (tengah / pulse);
  if (jarak < -138)
  {
    RPSkandep(50, 0.15, 0, 0.01);  RPSkirbel(50, 0.15, 0, 0.01);
    RPSkirdep(59, 0.2, 0, 0.01);  RPSkanbel(52, 0.15, 0, 0.01); //kirdep 55 p 0.15
  }
  else if (jarak >= -138 && jarak < 150)//157 // 211 300
  {
    RPSkandep(v, 0.2, 5, 0.01);  RPSkirbel(v, 0.2, 0, 0.01);
    RPSkirdep(v1, 0.25, 0, 0.01);  RPSkanbel(v1, 0.25, 0, 0.01);
    brake(175);//200
  }
  else if (jarak >= 150 && jarak < 330)
  {
    RPSkandep(85, 0.25, 0, 0.01);  RPSkirbel(41, 0.2, 0, 0.01);//kandep 59
    RPSkirdep(27, 0.2, 0, 0.01);  RPSkanbel(40, 0.2, 0, 0.01);
  }
  else if (jarak >= 330 && jarak < 452)
  {
    RPSkandep(35, 0.5, 0, 0.01);  RPSkirbel(35, 0.5, 0, 0.01);
    RPSkirdep(35, 0.5, 0, 0.01);  RPSkanbel(35, 0.5, 0, 0.01);
  }
  else if (jarak > 452 && jarak < 455)
  {
     // stoptor(0);
     // stopmotor();
     // Serial2.print("a");
     // break;
     stoptor(0);
     stopmotor();
     delay(500);
     control = 1;
   }
   while (control == 1)
   {
     control = 0;
   }
  //}
}

void goTZ2()
{
  //while (1) {
  jarak = keliling * (tengah / pulse);
  if (jarak < 530)
  {
    stoptor(0);
    delay(10);
    RPSkandep(20, 0.2, 0, 0.01);  RPSkirbel(20, 0.2, 0, 0.01);
    RPSkirdep(20, 0.2, 0, 0.01);  RPSkanbel(20, 0.2, 0, 0.01);
  }
  else if (jarak >= 520)
  {
    stoptor(0);
    stopmotor();
    delay(500);
    control = 1;
    //Serial2.print("d");
    //break;
  }
  while (control == 1)
  {
    control = 0;
  }
 //}
}

void gotrial2()
{
  jarak = keliling * (tengah / pulse);
  if (jarak > -515)
  {
    RPSkandep(-61, 0.3, 0, 0.01);  RPSkirbel(-61, 0.3, 0, 0.01);
    RPSkirdep(60, 0.3, 0, 0.01);  RPSkanbel(60, 0.3, 0, 0.01);
  }
  else if (jarak <= -516)
  {
    stopmotor();
    delay(200);
    control = 1;
  }
  while (control == 1)
  {
    control = 0;
  }
}

void goEmas()
{
  jarak = keliling * (tengah / pulse);
  if (jarak >= -225)//220
  {
    RPSkirdep(vrps3, 0.2, 0, 0.02);   RPSkirbel(vrps3, 0.2, 0, 0.02);
    RPSkandep(vrps2, 0.2, 0, 0.02);   RPSkanbel(vrps2, 0.2, 0, 0.02);
    softbrake3(55);//120 //55
    if (jarak <= -190 && jarak >= -200)
    {
      bukakok2();
    }
    control = 1;
  }
  else
  {
    // bukakok2();
    stoptor(0);
    delay(10);
    proximity_sensorbel1();
  }
  while (control == 1)
  {
    control = 0;
  }
}

void goEmasTrial()
{
  jarak = keliling * (tengah / pulse);
  if (jarak >= -220)//220
  {
    RPSkirdep(vrps5, 0.2, 0, 0.02);   RPSkirbel(vrps5, 0.2, 0, 0.02);
    RPSkandep(vrps4, 0.2, 0, 0.02);   RPSkanbel(vrps4, 0.2, 0, 0.02);
    softbrake4(94);//100
    if (jarak <= -190 && jarak >= -200)
    {
      bukakok2();
    }
    control = 1;
  }
  else
  {
    stoptor(0);
    delay(10);
    proximity_sensorbel1();
  }
  while (control == 1)
  {
    control = 0;
  }
}

void goTZ3()
{
  //while (1) {
  jarak = keliling * (tengah / pulse);
  if (jarak < 0)
  {
    RPSkandep(40, 0.2, 0, 0.02);  RPSkirbel(78, 0.2, 0, 0.02);
    RPSkirdep(190, 0.3, 0, 0.02);  RPSkanbel(118, 0.3, 0, 0.02);
  }
  else if (jarak > 0 && jarak < 120)
  {
  RPSkandep(70, 0.2, 0, 0.02);  RPSkirbel(88, 0.2, 0, 0.02);
  RPSkirdep(170, 0.3, 0, 0.02);  RPSkanbel(128, 0.3, 0, 0.02);
    //control = 2;
  }
  else if (jarak >= 120 && jarak < 600)//675
  {
    stoptor(0);
    delay(1);
    RPSkandep(v2, 0.2, 0, 0.02);  RPSkirbel(v2, 0.2, 0, 0.02);
    RPSkirdep(v3, 0.2, 0, 0.02);  RPSkanbel(v3, 0.2, 0, 0.02);
    softstart2(15);
    //control = 2;
  }
  else if (jarak > 600 && jarak < 605)
  {
    stoptor(0);
    stopmotor();
    //break;
    delay(500);
    control = 2;
  }
//}
  while (control == 2)
  {
    control = 0;
  }
}

void gotrial3()
{
  jarak = keliling * (tengah / pulse);
  if (jarak < 0)
  {
    RPSkandep(40, 0.2, 0, 0.02);  RPSkirbel(78, 0.2, 0, 0.02);
    RPSkirdep(190, 0.3, 0, 0.02);  RPSkanbel(118, 0.3, 0, 0.02);
  }
  else if (jarak > 0 && jarak < 120)
  {
  RPSkandep(70, 0.2, 0, 0.02);  RPSkirbel(88, 0.2, 0, 0.02);
  RPSkirdep(170, 0.3, 0, 0.02);  RPSkanbel(128, 0.3, 0, 0.02);
    //control = 2;
  }
  else if (jarak >= 120 && jarak < 600)//675
  {
    stoptor(0);
    delay(1);
    RPSkandep(v4, 0.2, 0, 0.02);  RPSkirbel(v4, 0.2, 0, 0.02);
    RPSkirdep(v5, 0.2, 0, 0.02);  RPSkanbel(v5, 0.2, 0, 0.02);
    softstart3(5);
    //control = 2;
  }
  else if (jarak > 600 && jarak < 605)
  {
    stoptor(0);
    stopmotor();
    //break;
    delay(500);
    control = 2;
  }
//}
  while (control == 2)
  {
    control = 0;
  }
}

void ambilkok()
{
  digitalWrite(matic1B, HIGH);
  digitalWrite(matic2B, HIGH);
  digitalWrite(matic3B, HIGH);
  digitalWrite(matic4B, HIGH);
  digitalWrite(matic5B, HIGH);
  delay(50);
  digitalWrite(matic1B, LOW);
  digitalWrite(matic2B, LOW);
  digitalWrite(matic3B, LOW);
  digitalWrite(matic4B, LOW);
  digitalWrite(matic5B, LOW);
}

void bukakok2()
{
  digitalWrite(matic1A, HIGH);
  digitalWrite(matic2A, HIGH);
  digitalWrite(matic3A, HIGH);
  digitalWrite(matic4A, HIGH);
  digitalWrite(matic5A, HIGH);
  delay(50);
  digitalWrite(matic1A, LOW);
  digitalWrite(matic2A, LOW);
  digitalWrite(matic3A, LOW);
  digitalWrite(matic4A, LOW);
  digitalWrite(matic5A, LOW);
}


void mati()
{
  digitalWrite(matic1A, LOW);
  digitalWrite(matic1A, LOW);
  digitalWrite(matic2A, LOW);
  digitalWrite(matic2A, LOW);
  digitalWrite(matic3A, LOW);
  digitalWrite(matic3A, LOW);
  digitalWrite(matic4A, LOW);
  digitalWrite(matic4A, LOW);
}

void bukakok(int a)
{
  digitalWrite(a, HIGH); delay(70); digitalWrite(a, LOW);
}

void stoptor( float a)
{
  RPSkandep(0, a, 0, 0);  RPSkanbel(0, a, 0, 0);
  RPSkirdep(0, a, 0, 0);  RPSkirbel(0, a, 0, 0);
}

void softbrake(float t)
{
  if ((millis() - timer) > 100 && jarak < t)
  {
    timer = millis();
    vrps += 20;
    vrps1 += 20;
    if (vrps > -7) {
      vrps = -7;
    }
    if (vrps1 > -7) {
      vrps1 = -7;
    }
  }
}

void brake(float t)
{
  if ((millis() - timer1) > 100 && jarak > t)
  {
    timer1 = millis();
    v -= 20;
    v1 -= 5;
    if (v < 10) {
      v = 10;
    }
    if (v1 < 10) {
      v1 = 10;
    }
  }
}

void softstart2(float t)
{
  if ((millis() - timer2) > 100 && jarak < t)
  {
    timer2 = millis();
    v2 -= 20;
    v3 -= 20;
    if (v2 < 10) {
      v2 = 10;
    }
    if (v3 < 10) {
      v3 = 10;
    }
  }
}

void softstart3(float t)
{
  if ((millis() - timer6) > 100 && jarak < t)
  {
    timer6 = millis();
    v4 -= 20;
    v5 -= 20;
    if (v4 < 10) {
      v4 = 10;
    }
    if (v5 < 10) {
      v5 = 10;
    }
  }
}

void softbrake2(int t)
{
  if ((millis() - timer3) > 100 && jarak < t)
  {
    timer3 = millis();
    vrpsa += 68;
    vrpsb += 68;
    if (vrpsa > -5) {
      vrpsa = -5;
    }
    if (vrpsb > - 5) {
      vrpsb = -5;
    }
  }
}

void softbrake3(float t)
{
  if ((millis() - timer4) > 100 && jarak < t)
  {
    timer4 = millis();
    vrps2 += 15;
    vrps3 += 15;
    if (vrps2 > -7) {
      vrps2 = -7;
    }
    if (vrps3 > -7) {
      vrps3 = -7;
    }
  }
}

void softbrake4(float t)
{
  if ((millis() - timer5) > 100 && jarak < t)
  {
    timer5 = millis();
    vrps4 += 15;
    vrps5 += 15;
    if (vrps4 > -7) {
      vrps4 = -7;
    }
    if (vrps5 > -7) {
      vrps5 = -7;
    }
  }
}

void prints()
{
  jarak = keliling * (tengah / pulse);
  Serial.print("jarak: ");
  Serial.print(jarak);
  Serial.print("  ");
  Serial.print("depkan: ");
  Serial.print(depkan);
  Serial.print("  ");
  Serial.print("depkir: ");
  Serial.print(depkir);
  Serial.print("  ");
  Serial.print("belkan: ");
  Serial.print(belkan);
  Serial.print("  ");
  Serial.print("belkir: ");
  Serial.print(belkir);
  Serial.print("  ");
  Serial.print("tengah: ");
  Serial.println(tengah);
}

void mundurr()
{
  RPSkandep(-50, 0.1, 0, 0.01);  RPSkanbel(-50, 0.1, 0, 0.01);
  RPSkirdep(-50, 0.1, 0, 0.01);  RPSkirbel(-50, 0.1, 0, 0.01);
}

void RPSkandep(float rps, float kp, float ki, float kd)
{
  float
  Kp = kp, Ki = ki, Kd = kd,
  pid, TS = 1, P, I, D,
       error, lError = 0;
  int cRPS;
  rpskandep = rps;
  if ((millis() - ltime1) > 100)
  {
    cRPS = abs(depkan) - abs(ldepkan);
    if (rpskandep > 0) {
      motor1(maju);
    }
    else if (rpskandep < 0) {
      motor1(mundur);
    }
    else if (rpskandep == 0)
    {
      motor1(berhenti);
      pwmkandep = 0;
    }

    error = abs(rpskandep) - abs(cRPS);
    P = Kp * error;
    D = (Kd / TS) * (error - lError);
    piddepkan = P + D;
    pwmkandep = pwmkandep + piddepkan;
    ltime1 = millis(); lError = error; ldepkan = depkan;

    if (pwmkandep > 255) pwmkandep = 255;
    else if (pwmkandep < 0) pwmkandep = 0;
  }
}

void RPSkirdep(float rps, float kp, float ki, float kd)
{
  float
  Kp = kp, Ki = ki, Kd = kd,
  pid, TS = 1, P, I, D,
       error, lError = 0;
  int cRPS;
  rpskirdep = rps;
  if ((millis() - ltime2) > 100)
  {
    cRPS = abs(depkir) - abs(ldepkir);
    if (rpskirdep > 0) {
      motor3(maju);
    }
    else if (rpskirdep < 0) {
      motor3(mundur);
    }
    else if (rpskirdep == 0)
    {
      motor3(berhenti);
      pwmkirdep = 0;
    }

    error = abs(rpskirdep) - abs(cRPS);
    P = Kp * error;
    D = (Kd / TS) * (error - lError);
    piddepkir = P + D;
    pwmkirdep = pwmkirdep + piddepkir;
    ltime2 = millis(); lError = error; ldepkir = depkir;

    if (pwmkirdep > 255) pwmkirdep = 255;
    else if (pwmkirdep < 0) pwmkirdep = 0;
  }
}

void RPSkanbel(float rps, float kp, float ki, float kd)
{
  float
  Kp = kp, Ki = ki, Kd = kd,
  pid, TS = 1, P, I, D,
       error, lError = 0;
  int cRPS;
  rpskanbel = rps;
  if ((millis() - ltime3) > 100)
  {
    cRPS = abs(belkan) - abs(lbelkan);
    if (rpskanbel > 0) {
      motor2(maju);
    }
    else if (rpskanbel < 0) {
      motor2(mundur);
    }
    else if (rpskanbel == 0)
    {
      motor2(berhenti);
      pwmkanbel = 0;
    }

    error = abs(rpskanbel) - abs(cRPS);

    P = Kp * error;
    D = (Kd / TS) * (error - lError);
    pidbelkan = P + D;
    pwmkanbel = pwmkanbel + pidbelkan;
    ltime3 = millis(); lError = error; lbelkan = belkan;

    if (pwmkanbel > 255) pwmkanbel = 255;
    else if (pwmkanbel < 0) pwmkanbel = 0;
  }
}

void RPSkirbel(float rps, float kp, float ki, float kd)
{
  float
  Kp = kp, Ki = ki, Kd = kd,
  pid, TS = 1, P, I, D,
       error, lError = 0;
  int cRPS;
  rpskirbel = rps;
  if ((millis() - ltime4) > 100)
  {
    cRPS = abs(belkir) - abs(lbelkir);
    if (rpskirbel > 0) {
      motor4(maju);
    }
    else if (rpskirbel < 0) {
      motor4(mundur);
    }
    else if (rpskirbel == 0)
    {
      motor4(berhenti);
      pwmkirbel = 0;
    }

    error = abs(rpskirbel) - abs(cRPS);

    P = Kp * error;
    D = (Kd / TS) * (error - lError);
    pidbelkir = P + D;
    pwmkirbel = pwmkirbel + pidbelkir;
    ltime4 = millis(); lError = error; lbelkir = belkir;

    if (pwmkirbel > 255) pwmkirbel = 255;
    else if (pwmkirbel < 0) pwmkirbel = 0;
  }
}

void serong()
{
  analogWrite(kirdep1, LOW);
  analogWrite(kirdep2, LOW);
  analogWrite(kanbel1, LOW);
  analogWrite(kanbel2, LOW);
}

void serong1()
{
  analogWrite(kandep1, LOW);
  analogWrite(kandep2, LOW);
  analogWrite(kirbel1, LOW);
  analogWrite(kirbel2, LOW);
}

void up()
{
  analogWrite(kirdep1, 60);
  analogWrite(kirdep2, LOW);
  analogWrite(kanbel1, 50);
  analogWrite(kanbel2, LOW);
  analogWrite(kandep1, 50);
  analogWrite(kandep2, LOW);
  analogWrite(kirbel1, 50);
  analogWrite(kirbel2, LOW);
}

void upLow()
{
  analogWrite(kirdep1, 20);
  analogWrite(kirdep2, LOW);
  analogWrite(kanbel1, 20);
  analogWrite(kanbel2, LOW);
  analogWrite(kandep1, 20);
  analogWrite(kandep2, LOW);
  analogWrite(kirbel1, 20);
  analogWrite(kirbel2, LOW);
}

void down()
{
  analogWrite(kirdep1, LOW);
  analogWrite(kirdep2, 70);
  analogWrite(kanbel1, LOW);
  analogWrite(kanbel2, 70);
  analogWrite(kandep1, LOW);
  analogWrite(kandep2, 70);
  analogWrite(kirbel1, LOW);
  analogWrite(kirbel2, 70);
}

void downLow()
{
  analogWrite(kirdep1, LOW);
  analogWrite(kirdep2, 30);
  analogWrite(kanbel1, LOW);
  analogWrite(kanbel2, 30);
  analogWrite(kandep1, LOW);
  analogWrite(kandep2, 30);
  analogWrite(kirbel1, LOW);
  analogWrite(kirbel2, 30);
}

void downFast()
{
  analogWrite(kirdep1, LOW);
  analogWrite(kirdep2, 150);
  analogWrite(kanbel1, LOW);
  analogWrite(kanbel2, 150);
  analogWrite(kandep1, LOW);
  analogWrite(kandep2, 150);
  analogWrite(kirbel1, LOW);
  analogWrite(kirbel2, 150);
}

void ngiri()
{
  analogWrite(kirdep1, LOW);
  analogWrite(kirdep2, 45);
  analogWrite(kanbel1, LOW);
  analogWrite(kanbel2, 45);
  analogWrite(kandep1, 40);
  analogWrite(kandep2, LOW);
  analogWrite(kirbel1, 40);
  analogWrite(kirbel2, LOW);
}

void ngiricepat()
{
  analogWrite(kirdep1, LOW);
  analogWrite(kirdep2, 180);
  analogWrite(kanbel1, LOW);
  analogWrite(kanbel2, 170);
  analogWrite(kandep1, 110);
  analogWrite(kandep2, LOW);
  analogWrite(kirbel1, 110);
  analogWrite(kirbel2, LOW);
}

void nganan()
{
  analogWrite(kirdep1, 95);
  analogWrite(kirdep2, LOW);
  analogWrite(kanbel1, 93);
  analogWrite(kanbel2, LOW);
  analogWrite(kandep1, LOW);
  analogWrite(kandep2, 90);
  analogWrite(kirbel1, LOW);
  analogWrite(kirbel2, 90);
}

void putarkanan()
{
  analogWrite(kirdep1, LOW);
  analogWrite(kirdep2, 30);
  analogWrite(kanbel1, 30);
  analogWrite(kanbel2, LOW);
  analogWrite(kandep1, 30);
  analogWrite(kandep2, LOW);
  analogWrite(kirbel1, LOW);
  analogWrite(kirbel2, 30);
}

void putarkiri()
{
  analogWrite(kirdep1, 30);
  analogWrite(kirdep2, LOW);
  analogWrite(kanbel1, LOW);
  analogWrite(kanbel2, 30);
  analogWrite(kandep1, LOW);
  analogWrite(kandep2, 30);
  analogWrite(kirbel1, 30);
  analogWrite(kirbel2, LOW);
}

void stopmotor()
{
  analogWrite(kirdep1, LOW);
  analogWrite(kirdep2, LOW);
  analogWrite(kanbel1, LOW);
  analogWrite(kanbel2, LOW);
  analogWrite(kandep1, LOW);
  analogWrite(kandep2, LOW);
  analogWrite(kirbel1, LOW);
  analogWrite(kirbel2, LOW);
}
void motor1(int dir)
{
  switch (dir)
  {
    case maju:
      analogWrite(kandep1, pwmkandep);
      digitalWrite(kandep2, LOW);
      break;
    case mundur:
      digitalWrite(kandep1, LOW);
      analogWrite(kandep2, pwmkandep);
      break;
    case berhenti:
      digitalWrite(kandep1, HIGH);
      digitalWrite(kandep2, HIGH);
      break;
  }
}

void motor2(int dir)
{
  switch (dir)
  {
    case maju:
      analogWrite(kanbel1, pwmkanbel);
      digitalWrite(kanbel2, LOW);
      break;
    case mundur:
      digitalWrite(kanbel1, LOW);
      analogWrite(kanbel2, pwmkanbel);
      break;
    case berhenti:
      digitalWrite(kanbel1, HIGH);
      digitalWrite(kanbel2, HIGH);
      break;
  }
}

void motor3(int dir)
{
  switch (dir)
  {
    case maju:
      analogWrite(kirdep1, pwmkirdep);
      digitalWrite(kirdep2, LOW);
      break;
    case mundur:
      digitalWrite(kirdep1, LOW);
      analogWrite(kirdep2, pwmkirdep);
      break;
    case berhenti:
      digitalWrite(kirdep1, HIGH);
      digitalWrite(kirdep2, HIGH);
      break;
  }
}

void motor4(int dir)
{
  switch (dir)
  {
    case maju:
      analogWrite(kirbel1, pwmkirbel);
      digitalWrite(kirbel2, LOW);
      break;
    case mundur:
      digitalWrite(kirbel1, LOW);
      analogWrite(kirbel2, pwmkirbel);
      break;
    case berhenti:
      digitalWrite(kirbel1, HIGH);
      digitalWrite(kirbel2, HIGH);
      break;
  }
}

void counterkandep() {
  if (digitalRead(depankananA) && !digitalRead(depankananB)) {
    depkan += 1;
  }
  if (digitalRead(depankananA) && digitalRead(depankananB)) {
    depkan -= 1;
  }
}

void counterkanbel() {
  if (digitalRead(belakangkananA) && !digitalRead(belakangkananB)) {
    belkan += 1;
    // kanan += 1;
  }
  if (digitalRead(belakangkananA) && digitalRead(belakangkananB)) {
    belkan -= 1;
    // kanan -= 1;
  }
}

void counterkirdep() {
  if (digitalRead(depankiriA) && !digitalRead(depankiriB)) {
    depkir -= 1;
  }
  if (digitalRead(depankiriA) && digitalRead(depankiriB)) {
    depkir += 1;
  }
}

void counterkirbel() {
  if (digitalRead(belakangkiriA) && !digitalRead(belakangkiriB)) {
    belkir -= 1;
  }
  if (digitalRead(belakangkiriA) && digitalRead(belakangkiriB)) {
    belkir += 1;
  }
}

void countertengah() {
  if (digitalRead(tengahA) && !digitalRead(tengahB)) {
    tengah += 1;
  }
  if (digitalRead(tengahA) && digitalRead(tengahB)) {
    tengah -= 1;
  }
}

void bacaping()
{
  dinding = Ping();
  if (dinding > 45)
  {
    up();
  }
  else
  {
    stopmotor();
    control = 0;
  }
}

int Ping()
{
  long duration, inches, cm;
  pinMode(pingpin, OUTPUT);
  digitalWrite(pingpin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingpin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingpin, LOW);
  pinMode(pingpin, INPUT);
  duration = pulseIn(pingpin, HIGH, 250000);
  return cm = microsecondsToCentimeters(duration);
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

int control = 0, a='0', dinding;
const int pingpin = A0;

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
vrps = -31, vrps1 = -31,
v = 0, v1 = 0, v2 = 0, v3 = 0, vrpsa = -30, vrpsb = -30;
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

long ltime, ltime1, ltime2, ltime3, ltime4, timer, timer1;

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
  ltime1 = millis(); ltime2 = millis(); timer = millis(); timer1 = millis();
  ltime3 = millis(); ltime4 = millis(); ltime = millis();
  delay(10);
  bukakok(matic1A);
  bukakok(matic2A);
  bukakok(matic3A);
  bukakok(matic4A);
}

void loop() {
  prints();
  if (Serial2.available()) {
    a = Serial2.read();
  }
  if (a == 'A') //up
  {
    up();
  }
  else if (a == 'B')//down
  {
    down();
  }
  else if (a == 'C') //kiri
  {
    ngiri();
  }
  else if (a == 'D') //kanan
  {
    nganan();
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
  // else if (a == 'H')
  // {
  //   bacaping();
  // }

  else if (a == 'G') //PSB_TRIANGLE
  {
    goEmas();
  }

  else if (a == 'I')
  {
    gotrial3();
  }

  else if (a == 'S')
  {
    bukakok(matic1A);
    delay(300);
    down();
    delay(10);
    control= 1;
    while (control == 1)
    {
      control = 0;
    }
  }

  else if (a == 'X')
  {
    bukakok(matic3A);
    delay(300);
    down();
    delay(10);
    control= 1;
    while (control == 1)
    {
      control = 0;
    }
  }

  else if (a == 'O')
  {
    bukakok(matic2A);
    delay(300);
    down();
    delay(10);
    control= 1;
    while (control == 1)
    {
      control = 0;
    }
  }

  else if (a == 'P')
  {
    bukakok(matic4A);
    delay(300);
    down();
    delay(10);
    control= 1;
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
    bukakok(matic1A);
    bukakok(matic2A);
    bukakok(matic3A);
    bukakok(matic4A);
  }

  else if (a == 'H')
  {
    goTZ3();
  }

  else if (a == 'E')
  {
    gotrial2();
  }

  else if (a == 'Z')
  {
    stopmotor();
  }
}

void mulai()
{
  //SerialUSB.println("mulai ambil kok");
  jarak = keliling * (tengah / pulse);
  if(jarak < 250)
  {
    RPSkandep(56, 0.2, 0, 0.01);  RPSkanbel(-64, 0.2, 0, 0.01);
    RPSkirdep(-61, 0.2, 0, 0.01);  RPSkirbel(50, 0.2, 0, 0.01);
  }
  else if (jarak >= 251)
  {
    stopmotor();
    control='C';
  }
  while (control=='C')
  {
    jarak = keliling * (tengah / pulse);
    stopmotor();
    delay(100);
    ambilkok();
    control='D';
    while (control=='D')
    {
      jarak = keliling * (tengah / pulse);
      mati();
      goTZ1();
    }
  }
}

void goTZ1()
{
  jarak = keliling * (tengah / pulse);
  if (jarak > -467)
  {
    RPSkandep(-94, 0.3,0, 0.01);  RPSkirbel(-94, 0.3, 0, 0.01);
    RPSkirdep(90, 0.3, 0, 0.01);  RPSkanbel(90, 0.3, 0, 0.01);

  }
  else if (jarak <= -468)
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

void gotrial2()
{
  jarak = keliling * (tengah / pulse);
  if (jarak > -515)
  {
    RPSkandep(-61, 0.3,0, 0.01);  RPSkirbel(-61, 0.3, 0, 0.01);
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
  if (jarak < 60)
  {
    RPSkandep(57, 0.2, 0, 0.01);  RPSkanbel(-75, 0.2, 0, 0.01);
    RPSkirdep(-72, 0.2, 0, 0.01);  RPSkirbel(52, 0.2, 0, 0.01);

    if (jarak >= 10 && jarak <= 20)
    {
      RPSkandep(34, 0.2, 0, 0.01);  RPSkanbel(-52, 0.2, 0, 0.01);
      RPSkirdep(-39, 0.2, 0, 0.01);  RPSkirbel(33, 0.2, 0, 0.01);
    }
    control = 1;
  }
  else if (jarak >= 30 && jarak <= 240)
  {
    RPSkandep(34, 0.3, 0, 0.01);  RPSkanbel(-52, 0.3, 0, 0.01);
    RPSkirdep(-39, 0.3, 0, 0.01);  RPSkirbel(33, 0.3, 0, 0.01);
    if (jarak >= 237 && jarak <= 240)
    {
      bukakok(matic1A);
      bukakok(matic2A);
      bukakok(matic3A);
      bukakok(matic4A);
    }
    control = 1;
  }
  else if (jarak >= 241)
  {
    stopmotor();
    control='E';
  }
  while (control=='E')
  {
    jarak = keliling * (tengah / pulse);
    stopmotor();
    delay(70);
    ambilkok2();
    control='F';
    while (control=='F')
    {
      jarak = keliling * (tengah / pulse);
      mati();
      goTZ3();
    }
  }
  while (control == 1)
  {
    control = 0;
  }
}

void goTZ3()
{
  jarak = keliling * (tengah / pulse);
  if (jarak > -530)
  {
    RPSkandep(-116, 0.3,0, 0.01);  RPSkanbel(110, 0.3, 0, 0.01);
    RPSkirdep(110, 0.3, 0, 0.01);  RPSkirbel(-116, 0.3, 0, 0.01);
  }
  else if (jarak <= -530 && jarak >= -724 )
  {
    RPSkandep(-41, 0.3,0, 0.01);  RPSkanbel(40, 0.3, 0, 0.01);
    RPSkirdep(40, 0.3, 0, 0.01);  RPSkirbel(-41, 0.3, 0, 0.01);
  }
  else if (jarak <= -725)
  {
    stopmotor();
    delay(200);
    control = 2;
  }

  while (control == 2)
  {
    control = 0;
  }
}

void gotrial3()
{
  jarak = keliling * (tengah / pulse);
  if (jarak < 265)
  {
    RPSkandep(46, 0.2, 0, 0.01);  RPSkanbel(-54, 0.2, 0, 0.01);
    RPSkirdep(-51, 0.2, 0, 0.01);  RPSkirbel(40, 0.2, 0, 0.01);
  }
  else if (jarak >= 265)
  {
    stopmotor();
    control='C';
  }
  while (control=='C')
  {
    jarak = keliling * (tengah / pulse);
    stopmotor();
    delay(100);
    ambilkok();
    control='D';
    while (control=='D')
    {
      jarak = keliling * (tengah / pulse);
      mati();
      goTZ3();
    }
  }
}

void ambilkok()
{
  digitalWrite(matic1B, HIGH); delay(70); digitalWrite(matic1B, LOW);
  digitalWrite(matic2B, HIGH); delay(70); digitalWrite(matic2B, LOW);
  digitalWrite(matic3B, HIGH); delay(70); digitalWrite(matic3B, LOW);
  digitalWrite(matic4B, HIGH); delay(70); digitalWrite(matic4B, LOW);
}

void ambilkok2()
{
  digitalWrite(matic1B, HIGH); delay(70); digitalWrite(matic1B, LOW);
  digitalWrite(matic2B, HIGH); delay(70); digitalWrite(matic2B, LOW);
  digitalWrite(matic3B, HIGH); delay(70); digitalWrite(matic3B, LOW);
  digitalWrite(matic4B, HIGH); delay(70); digitalWrite(matic4B, LOW);
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
  RPSkandep(0,a,0,0.1);  RPSkanbel(0,a,0,0.1);
  RPSkirdep(0,a,0,0.1);  RPSkirbel(0,a,0,0.1);
}

void softbrake(float t)
{
  if ((millis() - timer) > 100 && jarak < t)
  {
    timer = millis();
    vrps += 10;
    vrps1 += 10;
    if (vrps >- 5) {
      vrps = -5;
    }
    if (vrps1 >- 5) {
      vrps1 = -5;
    }
  }
}

void softstart(float t)
{
  if ((millis() - timer) > 100 && jarak > t)
  {
    timer = millis();
    v -= 10;
    v1 -= 10;
    if (v < 5) {
      v = 5;
    }
    if (v1 < 5) {
      v1 = 5;
    }
  }
}

void softstart2(float t)
{
  if ((millis() - timer) > 100 && jarak < t)
  {
    timer = millis();
    v2 += 10;
    v3 += 10;
    if (v2 >- 5) {
      v2 = 5;
    }
    if (v3 >- 5) {
      v3 = 5;
    }
  }
}

void softbrake2(int t)
{
  if ((millis() - timer) > 100 && jarak < t)
  {
    timer = millis();
    vrpsa += 68;
    vrpsb += 68;
    if (vrpsa >-5) {
      vrpsa = -5;
    }
    if (vrpsb >- 5) {
       vrpsb = -5;
    }
  }
}

void prints()
{
  jarak = keliling * (tengah / pulse);
  SerialUSB.print("jarak: ");
  SerialUSB.print(jarak);
  SerialUSB.print("  ");
  SerialUSB.print("depkan: ");
  SerialUSB.print(depkan);
  SerialUSB.print("  ");
  SerialUSB.print("depkir: ");
  SerialUSB.print(depkir);
  SerialUSB.print("  ");
  SerialUSB.print("belkan: ");
  SerialUSB.print(belkan);
  SerialUSB.print("  ");
  SerialUSB.print("belkir: ");
  SerialUSB.print(belkir);
  SerialUSB.print("  ");
  SerialUSB.print("tengah: ");
  SerialUSB.println(tengah);
}

void mundurr()
{
  RPSkandep(-50,0.1,0,0.01);  RPSkanbel(-50,0.1,0,0.01);
  RPSkirdep(-50,0.1,0,0.01);  RPSkirbel(-50,0.1,0,0.01);
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
    if (rpskandep > 0) { motor1(maju); }
    else if (rpskandep < 0) { motor1(mundur); }
    else if (rpskandep == 0)
    { motor1(berhenti); pwmkandep = 0;}

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
    if (rpskirdep > 0) { motor3(maju); }
    else if (rpskirdep < 0) { motor3(mundur); }
    else if (rpskirdep == 0)
    { motor3(berhenti); pwmkirdep = 0;}

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
    if (rpskanbel > 0) { motor2(maju); }
    else if (rpskanbel < 0) { motor2(mundur); }
    else if (rpskanbel == 0)
    { motor2(berhenti); pwmkanbel = 0;}

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
    if (rpskirbel > 0) { motor4(maju); }
    else if (rpskirbel < 0) { motor4(mundur); }
    else if (rpskirbel == 0)
    {  motor4(berhenti); pwmkirbel = 0; }

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

void ngiri()
{
  analogWrite(kirdep1, LOW);
  analogWrite(kirdep2, 75);
  analogWrite(kanbel1, LOW);
  analogWrite(kanbel2, 75);
  analogWrite(kandep1, 70);
  analogWrite(kandep2, LOW);
  analogWrite(kirbel1, 70);
  analogWrite(kirbel2, LOW);
}

void nganan()
{
  analogWrite(kirdep1, 75);
  analogWrite(kirdep2, LOW);
  analogWrite(kanbel1, 73);
  analogWrite(kanbel2, LOW);
  analogWrite(kandep1, LOW);
  analogWrite(kandep2, 70);
  analogWrite(kirbel1, LOW);
  analogWrite(kirbel2, 70);
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
  if(digitalRead(depankananA) && !digitalRead(depankananB)) {
    depkan += 1;
  }
  if(digitalRead(depankananA) && digitalRead(depankananB)) {
    depkan -= 1;
  }
}

void counterkanbel() {
  if(digitalRead(belakangkananA) && !digitalRead(belakangkananB)) {
    belkan += 1;
    kanan += 1;
  }
  if(digitalRead(belakangkananA) && digitalRead(belakangkananB)) {
    belkan -= 1;
    kanan -= 1;
  }
}

void counterkirdep() {
  if(digitalRead(depankiriA) && !digitalRead(depankiriB)) {
    depkir += 1;
  }
  if(digitalRead(depankiriA) && digitalRead(depankiriB)) {
    depkir -= 1;
  }
}

void counterkirbel() {
  if(digitalRead(belakangkiriA) && !digitalRead(belakangkiriB)) {
    belkir += 1;
  }
  if(digitalRead(belakangkiriA) && digitalRead(belakangkiriB)) {
    belkir -= 1;
  }
}

void countertengah() {
  if(digitalRead(tengahA) && !digitalRead(tengahB)) {
    tengah += 1;
  }
  if(digitalRead(tengahA) && digitalRead(tengahB)) {
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

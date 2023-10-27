///Libraries
  #include <Servo.h>
///Pins
  // Define DC Motor Pins
  #define enA 10
  #define in1 9
  #define in2 8

  // Define UltraSonic sensor pins
  #define trigL 14
  #define echoL 15
  #define trigC 16
  #define echoC 17
  #define trigR 18
  #define echoR 19

  //Define Servo pins
  #define sPin 5

///Intitializing Variables
  //Ultrasonic Sensor Variables
    int durL; //duration the left sensor took to recieve the sound wave
    int distL; // distance away from the wall from the left sensor
    int durC ;
    int distC;
    int durR;
    int distR;

  //Turn() Variables
    float diff; //distance to the right - distance to the left
    int tilt; //number that decides the angle of the

///Functions
  void US() {  //To get a reading from the ultrasonic sensors

    //Left sensor

    digitalWrite(trigL, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigL, LOW); //Sends out an ultrasonic wave

    durL = pulseIn(echoL, HIGH); //recieves it back and measures the time it took

    distL = 0.01715 * durL; //calculates the distance in cm

    //Right sensor

    digitalWrite(trigR, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigR, LOW);

    durR = pulseIn(echoR, HIGH);

    distR = 0.01715 * durR;

    diff = distR - distL;  //Defining the difference between the distance to the left and right. //if the distance on the right is greater, 'diff' is positive and vice versa.
  }

  void Stop() {  ///For stopping completely
    myservo.write(90);
    analogWrite(enA, 0);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(10);
  }

  void Forward() {  //For going forward
    analogWrite(enA, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    delay(10);
  }

  void Turn() {  //For centering and turning left or right automatically depending on robot's position

    US(); //first takes a reading from the ultrasonic sensors

    if (diff > 150 ) {tilt = 1;} //decides the tilt value
    else if (diff > 60 ) {tilt = 2;}
    else if (diff > 15) {tilt = 3;}
    else if ((abs(diff)) < 15) {tilt = 0;}
    else if (diff < -15) {tilt = 4;}
    else if (diff < -60) {tilt = 5;}
    else if (diff < -150) {tilt = 6;}




    switch (tilt){ //turns accordingly
        case 0: //Center
          myservo.write(90);
          break;
        case 1: //High Left
          myservo.write(50);
          break;
        case 2: //Mid Left
          myservo.write(65);
          break;
        case 3: //Low Left
          myservo.write(80);
          break;
        case 4: //Low Right
        myservo.write(100);
          break;
        case 5: //Mid Right
        myservo.write(115);
          break;
        case 6: //High Right
        myservo.write(140);
          break;
      }
  }

void setup() {
  Serial.begin(115200);

  //H bridge DC Motor pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Servo pins
  myservo.attach(sPin);

  //Ultrasonic Sensor pins
  pinMode(trigL, OUTPUT);
  pinMode(echoL, INPUT);
  pinMode(trigC, OUTPUT);
  pinMode(echoC, INPUT);
  pinMode(trigR, OUTPUT);
  pinMode(echoR, INPUT);

  //Automatic centering at startup
  myservo.write(90);
  delay(10);
}

void loop() {
  US();
  Forward();
  Turn();
}
//-Declarations and libraries
  int Quar = 0; //records the quarter in memory.
  int Stop = 0;
  int EmptySlot; // is the index of the first empty slot in the PathList string.

  unsigned long StartTime = 0; //for measuring duration since blue line reading.
  
  float t;
  
  String PathList= "0000"; //my workaround for making a dynamic list in C++.

  #include "HUSKYLENS.h"

  HUSKYLENS huskylens;

  int area;
  String color;
  int AreaG = 0;
  int AreaR = 0;
  int LineB = 0;

void setup() { 
  Serial.begin(115200);
  Wire.begin();
  while (!huskylens.begin(Wire)) {}
 }

void loop() {
  AreaFinder();
  ColorDetect();
  delay(1000);

 /*while (Stop == 0){
    PathMaker();
    Run();
    StopFunc();
}*/
}

//-Void functions
  void Turn() {
    Serial.println("..............TURN..............");
    Quar += 1;
  }
  void PathMaker(){
    if (Quar <= 3) {
    Turn();
    //ReadCamera(); replace with areafinder later
    ColorDetect();
    }
  }

  void PathStore(int Num) {
    if (PathList[3] == 48) {
      EmptySlot = PathList.indexOf(48);
      PathList[EmptySlot] = Num;
    }
  }

  void RunPath(int Quarter) {
    Quarter = Quarter%4;
    switch (PathList[Quarter]) {
      case 53: //which equals 5 in ascii.
        GreenRed();
        break;
      case 52: //4.
        RedGreen();
        break;
      case 51: //3.
        Green();
        break;
      case 50: //2.
        Red();
        break;
      case 49: //1.
        None();
        break;
      }
  }

  void Run(){ // Executes the second and third lap
    if ((Quar > 3) && (PathList.indexOf(48) == -1 )) {
      for (int i = 1; i < 8; i++){
        Turn();
        RunPath(i);
      }
    }
  }

  void ColorDetect() {
    if (AreaR>AreaG){ //there is more red.
      if(AreaG>0){ //is there any green?
        //PathStore(52); //4
        RedGreen();
      }
      else{
        //PathStore(50); //2
        Red();
      }
    }

    else if (AreaG>AreaR) { //there is more green.
      if(AreaR>0){ //is there any red?
        //PathStore(53); //5
        GreenRed();
      }
      else{
        //PathStore(51); //3
        Green();
      }
    }

    else{
      //PathStore(49); //1
      None();

    }
  }

  void StopFunc() {
      if (Quar == 11){
        Stop()
        Stop = 1;
      }
  }

  void Stop() {
    Serial.print()
  }

  ///ColorDecide Functions
    void RedGreen(){Serial.println("RIGHT, LEFT");}
    void GreenRed(){Serial.println("LEFT, RIGHT");}
    void Red(){Serial.println("RIGHT");}
    void Green(){Serial.println("LEFT");}
    void None(){Serial.println("CENTER");}

  ///HuskeyLens Functions

    void AreaFinder() {
      AreaR = 0;
      AreaG = 0;
      LineB = 0;

      if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
      else if(!huskylens.available()) Serial.println(F("No block appears on the screen!"));
      else
      {
        Serial.println(F("###########"));
        while (huskylens.available())
        {
          HUSKYLENSResult result = huskylens.read();
          printResult(result);
        }    
      }

      Serial.println(String() + F("areaR=") + AreaR + F("|areaG=") + AreaG + F("|LineB=") + LineB + F("|Qaur=") + Quar + F("|StartTime=") + (StartTime) +F("|Duration=") + (millis()-StartTime));

      delay(1000);
    }

    void printResult(HUSKYLENSResult result){
      area = result.width * result.height;
      LineB = 0;

      switch (result.ID) {
      case 1:
        color = "Red  "; //just for naming
        AreaR = area; //to decide whether the area is the area of the red or green traffic sign.
      break;

      case 2:
        color = "Green";
        AreaG = area;
      break;

      case 3:
        if ((millis() - StartTime) >= 2500) {
        color = "Blue Line";
        LineB = 1;
        Quar += 1;
        StartTime = millis();
        }
        else{ Serial.println("**************************"); }

      default:
        color = "Unknown";
        break;
      }
    }
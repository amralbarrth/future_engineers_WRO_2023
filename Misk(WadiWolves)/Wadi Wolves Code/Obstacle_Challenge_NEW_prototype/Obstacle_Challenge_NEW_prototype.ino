//-Declare
  int Lap; //records the lap in memory.
  int Quar; //records the quarter in memory.
  int LapRes; //what is returned when the current Lap is called through Lap().
  int Stop = 0;
  int EmptySlot; // is the index of the first empty slot in the PathList string.
  float AreaG = 4;
  float AreaR= 2;
  float t;
  String PathList= "0000"; //my workaround for making a dynamic list in C++.

void setup() {
Serial.begin(9600);
}
void loop() {
 while (Stop == 0){
    PathMaker();
    Run();
    StopFunc();
}
}

//-Void functions
 void Turn() {
  Serial.println("..............TURN..............");
  Quar += 1;
 }
  void PathMaker(){
   if (Quar <= 3) {
    Turn();
    ReadCamera();
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
        PathStore(52); //4
      }
      else{
        PathStore(50); //2
      }
    }

    else if (AreaG>AreaR) { //there is more green.
      if(AreaR>0){ //is there any red?
        PathStore(53); //5
      }
      else{
        PathStore(51); //3
      }
      }

    else{
      PathStore(49); //1
    }
  }
  
  void StopFunc() {
      if (Quar == 11){
        Stop = 1;
      }
  }

  void ReadCamera(){
    Serial.println("read");
    AreaR +=2;
    AreaG +=1;
  }

///ColorDecide Functions
  void RedGreen(){Serial.println("RIGHT, LEFT");}
  void GreenRed(){Serial.println("LEFT, RIGHT");}
  void Red(){Serial.println("RIGHT");}
  void Green(){Serial.println("LEFT");}
  void None(){Serial.println("CENTER");}

//-Counters and calculators

  /*  int LapCalc(int Quarter) { //returns the current lap by the current quarter.
      LapRes = floor(Quarter/4);
      return LapRes; //as in lap result.
    }
  */
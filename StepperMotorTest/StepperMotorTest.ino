// defines pins numbers
int maxSteps = 0;
const int stepPin = 9; 
const int dirPin = 8; 
const int enablePin = 2;//enable 
int stepDir = 1; //the direction of the stepper
int microA,microB,dirBtnA,dirBtnB; //pin 4 tot 7
int state = 0; //0 is calibration
bool isCalibrated = false;
bool leftEnable,rightEnable;
//unsigned long maxStep = 10;
//unsigned long thisStep = 0;
// add schematic and thoughts


void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(enablePin,OUTPUT);
  pinMode(4,INPUT); //gruen //killswitch
  pinMode(5,INPUT); //blouw //killswitch
  pinMode(6,INPUT); //gruen //button
  pinMode(7,INPUT); //blouw  //button
  Serial.begin(9600);
  digitalWrite(enablePin,HIGH);//disable
  state = 1;
  leftEnable= true;
  rightEnable = true;
}

void loop() 
{
  if(!isCalibrated) doCalibration();
  //first read the button and switch inputs
  microA = digitalRead(4);
  microB = digitalRead(5);
  dirBtnA = digitalRead(6);
  dirBtnB = digitalRead(7);

//  Serial.print(microA);
//  Serial.print(":");
//  Serial.println(microB);
  switch (state) 
  {
    case 0:
      doCalibration();
      break;
    case 1:
      // statements use buttons to manualy drive stepper
      if(dirBtnA == dirBtnB)
      { 
        digitalWrite(enablePin,HIGH);//disable
        return;
      }
      else if(dirBtnA == true)
      {
        //check direction with killswitch maybe inverse
        doStep(0,microA,100);
      }
      else
      {
        doStep(1,microB,100);
      }
      break;
      
    default:

      break;
  }
  digitalWrite(enablePin,HIGH);//enable
}

void doCalibration()
{
  digitalWrite(enablePin,LOW);
  // calibration go backwards till microswitch, then one step back
  // then go foreward till microswitch and one step back, the counted steps are the maximum and this is equals to 1
  // then go to 0.5 as initial state which should be the half steps back
  // statements
  // when done set state to 1
  isCalibrated = true;
  state = 1;
}

void doStep(int dir,int microPin,int stepTime)
{
  stepDir = dir;
  digitalWrite(enablePin,LOW);//enable
  digitalWrite(dirPin,stepDir);
  delayMicroseconds(stepTime); 
  for(int x = 0; x < 100; x++) {//200
      if(digitalRead(microPin) == true) return;
      digitalWrite(stepPin,HIGH); 
      delayMicroseconds(stepTime); 
      digitalWrite(stepPin,LOW); 
      delayMicroseconds(stepTime); 
  }
}

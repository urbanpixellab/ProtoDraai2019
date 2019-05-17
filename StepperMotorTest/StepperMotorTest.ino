// defines pins numbers
const int stepPin = 9; 
const int dirPin = 8; 
int stepDir = 0; //the direction of the stepper
int microA,microB,dirBtnA,dirBtnB; //pin 4 tot 7
int state = 0; //0 is calibration
bool isCalibrated = false;
//unsigned long maxStep = 10;
//unsigned long thisStep = 0;
// add schematic and thoughts


void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(4,INPUT); //gruen
  pinMode(5,INPUT); //blouw
  pinMode(6,INPUT); //gruen
  pinMode(7,INPUT); //blouw
  state = 0;
}

void loop() 
{
  if(!isCalibrated) doCalibration();
  
  //first read the button and switch inputs
  microA = digitalRead(4);
  microB = digitalRead(5);
  dirBtnA = digitalRead(6);
  dirBtnB = digitalRead(7);

  switch (state) 
  {
    case 0:
      doCalibration();
      break;
    case 1:
      // statements
      if(dirBtnA == dirBtnB) return;
      else
      {
        if(dirBtnA == 0 && dirBtnB == 1)
        {
          if(stepDir != 0)
          {
            stepDir = 0;
            digitalWrite(dirPin,stepDir);
          }
        }
        else if(dirBtnA == 1 && dirBtnB == 0)
        {
          if(stepDir != 1)
          {
            stepDir = 1;
            digitalWrite(dirPin,stepDir);
          }
        }
      }
      doStep();
      break;
    default:
      // statements
      break;
  }
}

void doCalibration()
{
  // calibration go backwards till microswitch, then one step back
  // then go foreward till microswitch and one step back, the counted steps are the maximum and this is equals to 1
  // then go to 0.5 as initial state which should be the half steps back
  // statements
  // when done set state to 1
  isCalibrated = true;
  state = 1;
}

void doStep()
{
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(70); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(70); 
  }
}


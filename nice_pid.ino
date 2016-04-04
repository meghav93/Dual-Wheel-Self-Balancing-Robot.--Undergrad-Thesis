 //#include <Pendulum_Robot.h>

 
#define gyroX A5
#define accX A0
#define accY A4
#define EncoderX 2
#define EncoderY 3
#define error_size 20
//-----------PID CONSTANTS---------


float p =2;
float i =2.9;
float d =0.005;

int pulses_left=0;
float desired_pwm,new_pwm;

//------------MOTOR PINS------------

int loopCounter=0;
long int wheelPosition=0,wheelVelocity=0,lastWheelPosition=0,targetPosition=0;

int right_pwm=6;
int right_dir1=8;
int right_dir2=9;
int left_pwm=5;
int left_dir1=11;
int left_dir2=10;


double loopStartTime;
double lastLoopUsefulTime=0;
double lastLoopTime=0;
int STD_LOOP_TIME = 10;
//int pid_loop_time_seconds = pid_loop_time/1000;
double accXval,accYval,accX_in,accY_in,acc_in,gyro_in,gangle;
double rate;
//double time,time1;
double acc_angle,kangle,acc_angle1,acc_angle2,current_error,prev_error=0,integral,difference,correction;
double pwm;
double diff;

float x_angle = 0;
float x_angleC = 0;
float x_angleRG = 0;
float x_angleRA = 0;
float x_angle2C = 0;
float prev;
double sum = 0;
double error[10]={ 0 };
double zeroValues[3] = {0};



void setup()
{

  Serial.begin(9600);
  attachInterrupt(0,doEncoderX,RISING); // pin 2
  attachInterrupt(1,doEncoderY,RISING); // pin 3
  pinMode(13,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);

  

  digitalWrite(13,1);

  /*--------- initial values ---------*/

  /*--------- average of 100 gyro data ---------*/
     
  

  /*--------- initial accelerometer angle ---------*/
  
  acc_in=pitch();//44.10;             // 90 degree reading
  Serial.print("acc=");
  Serial.println(acc_in);
  delay(300);
  /*--------- Initialize start time ---------*/
    loopStartTime=millis();
 
  digitalWrite(13,0);
}
void loop()
{
//  Serial.println(pulses_left);
   

  /*--------- accelerometer angle stuff ---------*/
  //acc_angle=pitch();
  acc_angle=(pitch()-acc_in);
  if(acc_angle>=50)
  {
    acc_angle1=90-acc_angle;
    acc_angle2=180-acc_angle;
    acc_angle1=-acc_angle1;
    acc_angle2=-acc_angle2;
    if(acc_angle1>-50)
    {
      acc_angle=acc_angle1;
    }
    else if(acc_angle2>-50)
    {
      acc_angle=acc_angle2;
    }     
  }
  else if(acc_angle<-50)
  {
    acc_angle1=90+acc_angle;
    acc_angle2=180+acc_angle;

    if(acc_angle1<-50)
    {
      acc_angle=acc_angle1;
    }

    else if(acc_angle2<-50)
    {
      acc_angle=acc_angle2;
    }     
  }
  acc_angle=acc_angle*15;

//  Serial.print(acc_angle);
  

  /*--------- Gyro stuff ---------*/
  rate=gyro_rate();

  /*--------- Kalman Angle ---------*/
  kangle=kalmanCalculate(acc_angle,rate,lastLoopTime);
//  Serial.print("      ");
//  Serial.println(kangle);
  loopCounter++;
  if (loopCounter == 10) {
    loopCounter = 0; // Reset loop counter
    wheelPosition = pulses_left;
    wheelVelocity = wheelPosition - lastWheelPosition;
    lastWheelPosition = wheelPosition;
//    Serial.print(wheelVelocity);
//    Serial.print("    ");
//    Serial.print(wheelPosition);
//    Serial.print("    ");
//    Serial.println(lastWheelPosition);
    if (abs(wheelVelocity) <= 10 ) { // Set new targetPosition if braking
      targetPosition = wheelPosition;

    }
  }
   
  /*--------- PID ---------*/
  Pid(kangle,targetPosition,wheelPosition);     
        
       
        



  /*--------- loop timing control ---------*/
  lastLoopUsefulTime = millis()-loopStartTime;
  if(lastLoopUsefulTime<STD_LOOP_TIME)
    delay(STD_LOOP_TIME-lastLoopUsefulTime);
   
  lastLoopTime = millis() - loopStartTime;
  loopStartTime = millis();
}



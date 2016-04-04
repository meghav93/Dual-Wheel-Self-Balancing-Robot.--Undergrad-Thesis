double restAngle;
void Pid(float kangle,long int target,long wheelPosition)
{
   long positionError = wheelPosition - target;
    if (abs(positionError) > 1000) // Inside zone A
      restAngle -= positionError/100;
   else if (abs(positionError) > 500) // Inside zone B
      restAngle -= (double)positionError/1000;
    //else // Inside zone C
      //restAngle -= (double)positionError/1500;   
    //restAngle -= (double)wheelVelocity;
    if (restAngle < 160) // Limit rest Angle
      restAngle = 160;
    else if (restAngle > 200)
      restAngle = 200;  
      Serial.print(positionError);
      Serial.print("      ");
      Serial.println(restAngle);
      Serial.print("      ");
  /*--------- current error ----------*/
        current_error=restAngle-kangle; 
//        Serial.print(current_error);
        /*--------- error array shifting circle ---------*/
        for(int i=error_size;i>0;i--)
          error[i]=error[i-1];
      
        /*--------- Current error ---------*/
        error[0]=current_error;
    
        sum =0;
        /*--------- Error Summation ---------*/
        for(int j=0; j<error_size;j++)
          sum+=error[j];
      
        /*--------- Difference of Error ---------*/
        difference=error[0]-error[1];
      
        /*--------- PID MAGIC ---------*/

        correction = p*current_error +                 
                     i*sum*0.01 + 
                    (d*difference)/0.01;
        
       
        new_pwm =constrain(correction,-255,255);
//        Serial.print("    ");
//        Serial.println(new_pwm);
//       if(new_pwm>0)
//             forward(abs(new_pwm));
//       else if(new_pwm<0)
//             reverse(abs(new_pwm));
//       else {stopper();
//             for(int h=0;h<error_size;h++)   error[h]=0;}
}

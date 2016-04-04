void doEncoderX()
{ 
  if (digitalRead(EncoderX) == HIGH) 
  { 

    if (digitalRead(EncoderY) == LOW) 
    {  
      pulses_left =pulses_left + 1;              // CW
    } 
    else 
    {
      pulses_left =pulses_left - 1;              // CCW
    }
  }

}




void doEncoderY()
{ 

  if (digitalRead(EncoderY) == HIGH) 
  {   

    if (digitalRead(EncoderX) == HIGH) 
    {  
      pulses_left =pulses_left + 1;             // CW
    } 
    else 
    {
      pulses_left =pulses_left - 1;             // CCW
    }
  }


} 
//
//void leftEncoder() { 
//  if(PIND & _BV(PIND4)) // read pin 4
//    leftCounter--;
//  else
//    leftCounter++;    
//}
//void rightEncoder() {
//  if(PIND & _BV(PIND5)) // read pin 5
//    rightCounter--;
//  else
//    rightCounter++;  
//}


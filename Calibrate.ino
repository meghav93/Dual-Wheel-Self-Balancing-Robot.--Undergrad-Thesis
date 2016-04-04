void calibrateSensors() 
{
  for (uint8_t i = 0; i < 100; i++) { // Take the average of 100 readings
    zeroValues[0] += analogRead(gyroX);
    zeroValues[1] += analogRead(accX);
    zeroValues[2] += analogRead(accY);
    delay(10);
  }
  zeroValues[0] /= 100; // Gyro X-axis
  zeroValues[1] /= 100; // Accelerometer Y-axis
  zeroValues[2] /= 100; // Accelerometer Z-axis

//  if(zeroValues[1] > 500) { // Check which side is lying down - 1g is equal to 0.33V or 102.3 quids (0.33/3.3*1023=102.3)
//    zeroValues[1] -= 102.3; // +1g when lying at one of the sides
//    kalman.setAngle(90); // It starts at 90 degress and 270 when facing the other way
//    gyroAngle = 90;
//  } else {
//    zeroValues[1] += 102.3; // -1g when lying at the other side
//    kalman.setAngle(270);
//    gyroAngle = 270;
//  }
//
//  digitalWrite(buzzer,HIGH);
//  delay(100);  
//  digitalWrite(buzzer,LOW);
}

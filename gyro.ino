double gyro_rate()
{
  double gyroRate = -((double)((double)analogRead(gyroX) - zeroValues[0]) / 1.2288276); //0.681318 //1.0323
  return gyroRate;
}

//1.86186

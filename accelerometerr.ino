float pitch()
{
  accXval = ((double)analogRead(accX) - zeroValues[1]);  
  accYval = ((double)analogRead(accY) - zeroValues[2]);
  // Convert to 360 degrees resolution
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // We are then convert it to 0 to 2π and then from radians to degrees
  return (atan2(-accXval,-accYval)+PI)*RAD_TO_DEG;
}

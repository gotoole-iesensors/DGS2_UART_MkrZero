#define Timed_Initial_Zero  
#define Timed_Initial_Zero_Period 3600   //Zero set after 3600s

void setup() 
{
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(3000);

  Serial.println("\r\r\r\r\r\r\r\r");
  Serial.println("**********************************************************************************************************");
  Serial.println("Enter return to perform single read");
  Serial.println("Enter 'L' to toggle/untoggle legacy DGS output");
  Serial.println("Enter 'e' to read EEPROM");
  Serial.println("Enter 'C' to toggle/untoggle continuous output");
//  Serial.println("Enter '!' to toggle/untoggle synchronous ADC operation");
  Serial.println("Enter 'A' to enter running average(1-180 samples), SPS(1-256), interval between measurements(1, 5, 10, 15)");
  Serial.println("Enter 'M' to enter module barcode");
  Serial.println("Enter 'B' to enter sensor barcode");
  Serial.println("Enter 'O' to set open circuit measurement");
  Serial.println("Enter 'Z' to set zero circuit measurement");
  Serial.println("Enter 'P' to st AD5941 potentiostat settings");
  Serial.println("Enter 'S' to set sensor sensitivity in pA/PPM");
  Serial.println("Enter 'G' to perform a gas span at a set PPB value");
  Serial.println("Enter 'T' to set temperature reading offset");
  Serial.println("Enter 'H' to set humidity reading offset");
  Serial.println("Enter 'N' to set temperature compensation factor");
//  Serial.println("Enter 'I' to set I2C address (0x30 to 0x5F)");
  Serial.println("Enter 'E' to lock/unlock EEPROM");
  Serial.println("Enter 'r' to reset MCU \r\n");
  Serial.println("**********************************************************************************************************");
  Serial.println("Legacy output:");
  Serial.println("Serial, PPB, T, H, ADC_Raw, T_Raw, H_Raw, D, H, M, S \r\n");
  Serial.println("Standard output:");
  Serial.println("Serial, PPB, Tx100, Hx100, ADC_Raw, T_Raw, H_Raw");      
}

void loop() 
{
  unsigned long int LastMillis;
  bool Zero_Timer_Triggered = false;

  LastMillis = millis();
  while(1)
  {
    while (Serial1.available() > 0) 
    {
      Serial.write(Serial1.read());
      yield();
    }
    while (Serial.available() > 0) 
    {
      Serial1.write(Serial.read());
      yield();
    }

#ifdef Timed_Initial_Zero
    if((millis() > (Timed_Initial_Zero_Period * 1000)) && (!Zero_Timer_Triggered))
    {
      Zero_Timer_Triggered = true;
      Serial1.write("Z"); //adjust Zero_Timer for a scheduled initial Zero
    }
#endif
  }
}
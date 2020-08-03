#include "Energia.h"

/* Defines pin configuration of robot */
#include "RSLK_MAX_Pins.h"

#include <Wire.h>

/* Define a generic I2C sensor class */ 
#define I2C_VOBJ       0x00
#define I2C_TDIE       0x01
#define I2C_CONFIG     0x02
#define I2C_TOBJ       0x03
#define I2C_STATUS     0x04
#define I2C_STATMASK   0x05

#define I2C_CFG_RESET    0x8000
#define I2C_CFG_MODEON   0x1000
#define I2C_CFG_1SAMPLE  0x0000
#define I2C_CFG_2SAMPLE  0x0200
#define I2C_CFG_4SAMPLE  0x0400
#define I2C_CFG_8SAMPLE  0x0600
#define I2C_CFG_16SAMPLE 0x0800
#define I2C_CFG_ALERTEN  0x0100
#define I2C_CFG_ALERTF   0x0080
#define I2C_CFG_TRANSC   0x0040

#define I2C_STAT_ALERTEN 0x8000
#define I2C_STAT_CRTEN   0x4000

#define I2C_I2CADDR 0x44
#define I2C_DEVID 0x1F



class I2C_SENSOR  {
 public:
  I2C_SENSOR(uint8_t addr = I2C_I2CADDR);
  boolean begin(uint16_t samplerate = I2C_CFG_16SAMPLE);  // by default go highres

  int16_t readRawDieTemperature(void);
  int16_t readRawVoltage(void);
  double readObjTempC(void);
  double readDieTempC(void);
  void write16(uint8_t addr, uint16_t data);

 private:
  uint8_t _addr;
  uint16_t read16(uint8_t addr);
};

I2C_SENSOR::I2C_SENSOR(uint8_t i2caddr) {
  _addr = i2caddr;
}


boolean I2C_SENSOR::begin(uint16_t samplerate) {
  Wire.begin();
  write16(I2C_CONFIG, I2C_CFG_MODEON | I2C_CFG_ALERTEN | 
    I2C_CFG_TRANSC | samplerate);
  write16(I2C_STATMASK, I2C_STAT_ALERTEN | I2C_STAT_CRTEN);
  // enable conversion ready alert

  uint16_t did;
  did = read16(I2C_DEVID);
  Serial.print("did = 0x"); Serial.println(did, HEX);
  if (did != 0x78) return false;
  return true;
}


double I2C_SENSOR::readDieTempC(void) {
   double Tdie = readRawDieTemperature();
   Tdie *= 0.03125; // convert to celsius
   Serial.print("Tdie = "); Serial.print(Tdie); Serial.println(" C");
   return Tdie;
}

double I2C_SENSOR::readObjTempC(void) {
  int16_t raw = read16(I2C_TOBJ);
  // invalid
  if (raw & 0x1) return NAN;
  raw >>=2;

  double Tobj = raw;
  Tobj *= 0.03125; // convert to celsius

  Serial.print("Tobj = "); Serial.print(Tobj); Serial.println(" C");

  return Tobj;
}

int16_t I2C_SENSOR::readRawDieTemperature(void) {
  int16_t raw = read16(I2C_TDIE);

#ifdef TESTDIE
  raw = TESTDIE;
#endif

  Serial.print("Raw Tambient: 0x"); Serial.print (raw, HEX);
  float v = raw/4;
  v *= 0.03125;
  Serial.print(" ("); Serial.print(v); Serial.println(" *C)");
  raw >>= 2;
  return raw;
}

int16_t I2C_SENSOR::readRawVoltage(void) {
  int16_t raw;

  raw = read16(I2C_VOBJ);

#ifdef TESTVOLT
  raw = TESTVOLT;
#endif

  Serial.print("Raw voltage: 0x"); Serial.print (raw, HEX);
  float v = raw;
  v *= 156.25;
  v /= 1000;
  Serial.print(" ("); Serial.print(v); Serial.println(" uV)");
  
  return raw; 
}


uint16_t I2C_SENSOR::read16(uint8_t a) {
  uint16_t ret;

  Wire.beginTransmission(_addr); // start transmission to device 
  Wire.write(a); // sends register address to read from
  Wire.endTransmission(); // end transmission
  
  Wire.requestFrom(_addr, (uint8_t)2);// send data n-bytes read
  ret = Wire.read(); // receive DATA
  ret <<= 8;
  ret |= Wire.read(); // receive DATA

  return ret;
}

void I2C_SENSOR::write16(uint8_t a, uint16_t d) {
  Wire.beginTransmission(_addr); // start transmission to device 
  Wire.write(a); // sends register address to read from
  Wire.write(d>>8);  // write data
  Wire.write(d);  // write data
  Wire.endTransmission(); // end transmission
}

/* Define a specific OPT3001 class */

class OPT3001
{
  public:
  void begin();
  uint32_t readResult();
  uint16_t readManufacturerId();
  uint16_t readDeviceId();
  uint16_t readConfigReg();
  uint16_t readLowLimitReg();
  uint16_t readHighLimitReg();
  uint16_t readRegister(uint8_t registerName);
  uint8_t  interruptPin();
  private:
  
};

#define OPT3001_I2CADDR 0x44
#define OPT3001_INTERRUPT_PIN 8
#define RESULT_REG 0x00
#define CONFIG_REG 0x01
#define LOWLIMIT_REG 0x02
#define HIGHLIMIT_REG 0x03
#define OPT3001_MANUFACTUREID_REG 0x7E
#define OPT3001_DEVICEID_REG 0x7F

#define DEFAULT_CONFIG     0b1100110000010000 // 800ms
#define DEFAULT_CONFIG_100 0b1100010000010000 // 100ms
/*   CONFIG REGISTER BITS: RN3 RN2 RN1 RN0 CT M1 M0 OVF CRF FH FL L Pol ME FC1 FC0
  RN3 to RN0 = Range select:
          1100 by default, enables auto-range 
  CT = Conversion time bit
          0 = 100ms conversion time
          1 = 800ms conversion time (default)
  M1 to M0 = Mode bits
          00 = Shutdown mode
          01 = Single shot mode
          10 = Continuous conversion (default)
          11 = Continuous conversion
  OVF (Bit 8) –   Overflow flag. When set the conversion result is overflown.
  CRF (Bit 7) – Conversion ready flag. Sets at end of conversion. Clears by read or write of the Configuration register.
  FH (Bit 6)  –   Flag high bit. Read only. Sets when result is higher that TH register. Clears when Config register is 
          read or when Latch bit is ‘0’ and the result goes bellow TH register.
  FL (Bit 5)  –   Flag low bit. Read only. Sets when result is lower that TL register. Clears when Config register is read 
          or when Latch bit is ‘0’ and the result goes above TL register.
  L (Bit 4)   – Latch bit. Read/write bit. Default ‘1’, Controls Latch/transparent functionality of FH and FL bits. When 
          L = 1 the Alert pin works in window comparator mode with Latched functionality When L = 0 the Alert pin 
          works in transparent mode and the two limit registers provide the hysteresis.
  Pol (Bit 3) – Polarity. Read/write bit. Default ‘0’, Controls the active state of the Alert pin. Pol = 0 means Alert 
          active low.
  ME (Bit 2)  – Exponent mask. In fixed range modes masks the exponent bits in the result register to “0000”.
  FC1 to FC0  - Fault count bits. Read/write bits. Default “00” - the first fault will trigger the alert pin.
*/

void OPT3001::begin()
{
  uint16_t writeByte = DEFAULT_CONFIG_100;
  // Initialize Wire
  // Use I2C module 1 (I2C1SDA & I2C1SCL per BoosterPack standard) and begin
  Wire.begin();
  
    /* Begin Tranmission at address of device on bus */
  Wire.beginTransmission(OPT3001_I2CADDR);
  /* Send Pointer Register Byte */
  
  Wire.write(CONFIG_REG);

  /* Read*/
  Wire.write((unsigned char)(writeByte>>8));
  Wire.write((unsigned char)(writeByte&0x00FF));

  /* Sends Stop */
  Serial.println("before ending transmission");
  Wire.endTransmission();
  Serial.println("return to life");
  return;
}

uint16_t OPT3001::readRegister(uint8_t registerName)
{
  int8_t lsb;
  int8_t msb;
  int16_t result;


  // Initialize Wire
  Wire.begin();

  /* Begin Transmission at address of device on bus */
  Wire.beginTransmission(OPT3001_I2CADDR);

  /* Send Pointer to register you want to read */
  Wire.write(registerName);

  /* Sends Stop */
  Wire.endTransmission(true);

  /* Requests 2 bytes from Slave */
  Wire.requestFrom(OPT3001_I2CADDR, 2);

  /* Wait Until 2 Bytes are Ready*/
  while(Wire.available() < 2) {}

  /* Read*/
  msb = Wire.read();
  lsb = Wire.read();
  result = (msb << 8) | lsb;

  return result;
}


uint16_t OPT3001::readManufacturerId()
{

  return readRegister(OPT3001_MANUFACTUREID_REG);
  
}

uint16_t OPT3001::readDeviceId()
{
  return readRegister(OPT3001_DEVICEID_REG);
    
}

uint16_t OPT3001::readConfigReg()
{
  return readRegister(CONFIG_REG);
}

uint16_t OPT3001::readLowLimitReg()
{
  return readRegister(LOWLIMIT_REG);
  
  
}

uint16_t OPT3001::readHighLimitReg()
{
  return readRegister(HIGHLIMIT_REG);
}


uint32_t OPT3001::readResult()
{
  uint16_t exponent = 0;
  uint32_t result = 0;
  int16_t raw;
  raw = readRegister(RESULT_REG);
  
  /*Convert to LUX*/
  //extract result & exponent data from raw readings
  result = raw&0x0FFF;
  exponent = (raw>>12)&0x000F;

  //convert raw readings to LUX
  switch(exponent){
    case 0: //*0.015625
      result = result>>6;
      break;
    case 1: //*0.03125
      result = result>>5;
      break;
    case 2: //*0.0625
      result = result>>4;
      break;
    case 3: //*0.125
      result = result>>3;
      break;
    case 4: //*0.25
      result = result>>2;
      break;
    case 5: //*0.5
      result = result>>1;
      break;
    case 6:
      result = result;
      break;
    case 7: //*2
      result = result<<1;
      break;
    case 8: //*4
      result = result<<2;
      break;
    case 9: //*8
      result = result<<3;
      break;
    case 10: //*16
      result = result<<4;
      break;
    case 11: //*32
      result = result<<5;
      break;
  }

  return result;
  
}

uint8_t OPT3001::interruptPin()
{
  return (digitalRead(OPT3001_INTERRUPT_PIN)==0?1:0);
}

//I2C_SENSOR OPT3001(0x41);  // start with a diferent i2c address!
OPT3001 opt3001;
#define USE_USCI_B1

void setup() {
  unsigned int readings = 0;
  
  Serial.begin(115200);
  delay(1000);
  
  opt3001.begin(); 
  
  Serial.println("OPT3001 Initialized----------------------------------");
  
  // get manufacturer ID from OPT3001. Default = 0101010001001001
  readings = opt3001.readManufacturerId();  
  Serial.print("Manufacturer ID: "); 
  Serial.println(readings, BIN);

  // get device ID from OPT3001. Default = 0011000000000001
  readings = opt3001.readDeviceId();  
  Serial.print("Device ID: "); 
  Serial.println(readings, BIN);
  
  // read config register from OPT3001. Default = 1100110000010000
  readings = opt3001.readConfigReg();  
  Serial.print("Configuration Register: "); 
  Serial.println(readings, BIN);

  // read Low Limit register from OPT3001. Default = 0000000000000000
  readings = opt3001.readLowLimitReg();  
  Serial.print("Low Limit Register: "); 
  Serial.println(readings, BIN);
  
  // read High Limit register from OPT3001. Default = 1011111111111111
  readings = opt3001.readHighLimitReg();  
  Serial.print("High Limit Register: "); 
  Serial.println(readings, BIN);    
  
  Serial.println("\nOPT3001 READINGS-------------------------------------");
}

void loop() {
   // Variables
  uint32_t readings;
     
  // Read OPT3001
  readings = opt3001.readResult();  
  
  Serial.print("LUX Readings = ");
  Serial.println(readings, DEC);
 
  delay(800);
}

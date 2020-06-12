
//Tutorials:
//MMA8451:
//MLX90641:
//LSM9DS1: https://learn.adafruit.com/adafruit-lsm9ds1-accelerometer-plus-gyro-plus-magnetometer-9-dof-breakout/overview
//         https://github.com/kriswiner/LSM9DS1/blob/master/LSM9DS1_MS5611_BasicAHRS_t3.ino

//Version Notes:
//Attempt to convert from Arduino to Particle

//Loading libraries
#include <Particle.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_BNO055.h>

//i2c
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_MMA8451 mma = Adafruit_MMA8451();
Adafruit_BNO055 bno = Adafruit_BNO055();

void setup(void) {

  // Intialize connection with serial port
  // Will pause until serial console opens
  Serial.begin(9600);
  while(!Serial.isConnected());

  Serial.println("Serial succcessfully connected");
  Serial.println("Initializing program");
  Serial.println();

  //State whether connected to WiFi
  if (WiFi.ready()) {
    Serial.println("Wifi successfully connected");
  }
  else
  {
    Serial.println("Wifi connection failed");
  }
  Serial.println();

  //Greeting message sent over serial
  Serial.println("Adafruit MMA8451, MLX90614, BNO055 Fitbit");
  Serial.println("Fitbit_Code Version 2.3");
  Serial.println("Rev Date 01/17/2019");
  Serial.println();

  //Initialise sensors, set parameters, and print results
  //Warn if boards cannot be detected

  //MMA8451 ----------------------------------------------------
  if (! mma.begin()) {
    Serial.println("Unable to initialize MMA8451");
    while (1);
  }
  Serial.println("MMA8451 found");

  //Set the accelerometer range
  mma.setRange(MMA8451_RANGE_2_G);
  //mma.setRange(MMA8451_RANGE_4_G);
  //mma.setRange(MMA8451_RANGE_8_G);

  //MLX90641 ---------------------------------------------------
  if (!mlx.begin()) {
    Serial.println("Unable to initialize LSM9DS1");
    while (1);
  }
  Serial.println("MLX90641 found");

  //BNO055 -----------------------------------------------------
  if (!bno.begin()) {
    Serial.println("Unable to initialize BNO055");
    while (1);
  }
  Serial.println("BNO055 found");

  //Example includes this, says to use for better accuracy?
  bno.setExtCrystalUse(true);

  Serial.println();

  /*Program waits after intialization for signal to begin reporting data*/
  /*Signal program to begin loop by sending any command*/
  Serial.println("Setup complete");
  Serial.println("Send signal to start");
  Serial.println("------------------------------------");

  while(Serial.available() == 0){}
}

void loop() {

  //MMA8451 ----------------------------------------------------
  Serial.println("MMA8451");

  /*Read the 'raw' data in 14-bit counts
  mma.read();
  Serial.print("X:\t"); Serial.print(mma.x);
  Serial.print("\tY:\t"); Serial.print(mma.y);
  Serial.print("\tZ:\t"); Serial.print(mma.z);
  Serial.println(); */

  /* Get a new sensor event */
  sensors_event_t event;
  mma.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2)
  Serial.print("X: \t"); Serial.print(event.acceleration.x); Serial.print("\t");
  Serial.print("Y: \t"); Serial.print(event.acceleration.y); Serial.print("\t");
  Serial.print("Z: \t"); Serial.print(event.acceleration.z); Serial.print("\t");
  Serial.println("m/s^2 "); */

  /* Calculate and display the acceleration vector from components */
  float mmaaccelvector = sqrt(sq(event.acceleration.x) + sq(event.acceleration.y) + sq(event.acceleration.z)) - 9.81;

  Serial.print("Acceleration: ");
  Serial.print(mmaaccelvector);
  Serial.println(" m/s^2");

  /* Get the orientation of the sensor
  uint8_t o = mma.getOrientation();

  switch (o) {
    case MMA8451_PL_PUF:
      Serial.println("Portrait Up Front");
      break;
    case MMA8451_PL_PUB:
      Serial.println("Portrait Up Back");
      break;
    case MMA8451_PL_PDF:
      Serial.println("Portrait Down Front");
      break;
    case MMA8451_PL_PDB:
      Serial.println("Portrait Down Back");
      break;
    case MMA8451_PL_LRF:
      Serial.println("Landscape Right Front");
      break;
    case MMA8451_PL_LRB:
      Serial.println("Landscape Right Back");
      break;
    case MMA8451_PL_LLF:
      Serial.println("Landscape Left Front");
      break;
    case MMA8451_PL_LLB:
      Serial.println("Landscape Left Back");
      break;
    }
  Serial.println(); */

  //MLX90614 ----------------------------------------------------
  Serial.println("MLX90614");

  /* Display temperature reading in Celcius */
  Serial.print("Ambient = ");
  Serial.print(mlx.readAmbientTempC());
  Serial.println(" C");
  Serial.print("Object = ");
  Serial.print(mlx.readObjectTempC());
  Serial.println(" C");

  /* Display temperature reading in Farenheit
  Serial.print("Ambient = ");
  Serial.print(mlx.readAmbientTempF());
  Serial.println(" F");
  Serial.print("Object = ");
  Serial.print(mlx.readObjectTempF());
  Serial.println(" F");
  Serial.println(); */

  //BNO055 ------------------------------------------------------
  Serial.println("BNO055");

  /* Get a new sensor event */
  bno.getEvent(&event);

  /* Board layout:
         +----------+
         |         *| RST   PITCH  ROLL  HEADING
     ADR |*        *| SCL
     INT |*        *| SDA     ^            /->
     PS1 |*        *| GND     |            |
     PS0 |*        *| 3VO     Y    Z-->    \-X
         |         *| VIN
         +----------+
  */

  /* The processing sketch expects data as roll, pitch, heading */
  Serial.print(F("Orientation: "));
  Serial.print((float)event.orientation.x);
  Serial.print(F(" "));
  Serial.print((float)event.orientation.y);
  Serial.print(F(" "));
  Serial.print((float)event.orientation.z);
  Serial.println(F(""));

  /* Get accelerometer vector */
  imu::Vector<3> accelerometer = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);

  /* Display the floating point data
  Serial.print("X: ");
  Serial.print(accelerometer.x());
  Serial.print(" Y: ");
  Serial.print(accelerometer.y());
  Serial.print(" Z: ");
  Serial.print(accelerometer.z());
  Serial.print("\t\t"); */

  /* Calculate and display the acceleration vector from components */
  float bnoaccelvector = sqrt(sq(accelerometer.x()) + sq(accelerometer.y()) + sq(accelerometer.z())) - 9.81;

  Serial.print("Acceleration: ");
  Serial.print(bnoaccelvector);
  Serial.print(" m/s^2");
  Serial.println();

  Serial.println("------------------------------------");
  delay(100);
}
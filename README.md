# salamander

Fitbit style sensor package created with Particle Argon and Adafruit sensors.

### Hardware

Particle Argon WiFi Development Board https://store.particle.io/products/argon  
Adafruit BNO055 Absolute Orientation Sensor https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor  
Melexis MLX90614 Contact-less Infrared Sensor https://www.adafruit.com/product/1747  
Adafruit MMA8451 Triple-Axis Accelerometer https://www.adafruit.com/product/2019  

### File Structure

#### ```/src``` folder:  
This is the source folder that contains the firmware file.

If your application contains multiple files, they shou
ld all be included in the `src` folder. If your firmware depends on Particle libraries, those dependencies are specified in the `project.properties` file referenced below.

#### ```salamander.ino``` file:
This file is the firmware that will run as the primary application on the Particle. It contains a `setup()` and `loop()` function written in C++. This pulls data from the three boards and prints the output to serial.

#### ```/lib``` folder:  
This is the file that contains the libraries for the three boards.

### Compiling

When you're ready to compile the application, make sure you have the correct Particle device target selected and run `particle compile <platform>` in the CLI or click the Compile button in the Desktop IDE. The following files in your project folder will be sent to the compile service:

- Everything in the `/src` folder, including the `salamander.ino` application file
- The `project.properties` file for your project
- Any libraries stored under `lib/<libraryname>/src`

/**
 * Header       SHT31Sensor.h
 * Author       2021-10-22 Charles Geiser (https://www.dodeka.ch)
 * 
 * Purpose      Declaration of the class SHT31Sensor
 *              Inherits from Adafruit_SHT31 class
 * 
 * Constructor
 * arguments    i2cAddress    Address of the I2C-Interface of the SHT31 sensor
 */
#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_SHT31.h>

#ifndef _SHT31SENSOR_H_
#define _SHT31SENSOR_H_

class SHT31SensorData
{
    public:
        float tCelsius    = 20.0;   // sensor reading
        float relHumidity = 40.0;   // sensor reading
        float dewPoint    =  6.0;   // calculated dewpoint for temperature=20°C and humidity=40.0%
};

class SHT31Sensor : public Adafruit_SHT31
{
    protected:
        uint8_t         _i2cAddress;
        SHT31SensorData _sensorData;

    public:
        SHT31Sensor(uint8_t i2cAddress) : Adafruit_SHT31(), _i2cAddress(i2cAddress) {}
        bool begin();       // to be called in setup of main program
        void readSensor();  // updates measurements into SHT31SensorData
        void getSensorData(SHT31SensorData &data);  // copy measurements into the variable data
        void printSensorData();                      // print measurements to the monitor

    private:
        float   _calculateDewPoint();
};
#endif
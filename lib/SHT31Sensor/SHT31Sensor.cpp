/**
 * Class        SHT31Sensor.cpp
 * Author       2021-10-22 Charles Geiser (https://www.dodeka.ch)
 *
 * Purpose      Implements a class for the SHT31 temperature and humidity sensor.
 *              It also calculates the dewpoint.
 *              The sensor readings are stored in the SHT31SensorData data structure. 
 *              They can be copied to a variable of the same type in the main program 
 *              using the getSensorData() method. 
 * 
 * Methods      bool begin();       // to be called in setup of main program
 *              void readSensor();  // updates measurements into SHT31SensorData
 *              void getSensorData(SHT31SensorData &data);  // copy measurements into the variable data
 *              void printSensorData();                     // print measurements to the monitor
 * 
 * 
 * Board        Arduino UNO
 * 
 * Remarks      
 * 
 * References    
 */
#include "SHT31Sensor.h"

/**
 * Calculate dewpoint from given temperature and rel. humidity
 */
float SHT31Sensor::_calculateDewPoint() 
{
    float k;
    k = log(_sensorData.relHumidity/100) + (17.62 * _sensorData.tCelsius) / (243.12 + _sensorData.tCelsius);
    return 243.12 * k / (17.62 - k);
}

void SHT31Sensor::readSensor()
{
    _sensorData.tCelsius    = readTemperature();
    _sensorData.relHumidity = readHumidity();
    _sensorData.dewPoint    = _calculateDewPoint();      
}

/**
 * Initialize the sensor and read available data
 */
bool SHT31Sensor::begin()
{
    char buf[64];
    if (! Adafruit_SHT31::begin(_i2cAddress))
    {
        snprintf(buf, sizeof(buf), R"(===> SHT31Sensor not found on i2c address %u / 0x%x)", _i2cAddress, _i2cAddress);
        Serial.println(buf);
        return false;
    }
    else
    {
        readSensor();
        return true;
    }    
}

/**
 * Print measured sensor data
 */
void SHT31Sensor::printSensorData()
{
    char buf[88];

    snprintf(buf, sizeof(buf), R"(
    Temperature   %6.1f °C
    Humidity      %6.1f %%rF
    Dewpoint      %6.1f °C)", 
        (double)_sensorData.tCelsius,
        (double)_sensorData.relHumidity,
        (double)_sensorData.dewPoint);
    Serial.println(buf);
}

/**
 * Copy sensor readings into the variable data
 */
void SHT31Sensor::getSensorData(SHT31SensorData &data)
{
    data = _sensorData;
}
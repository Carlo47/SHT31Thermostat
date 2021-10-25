/**
 * Class        SHT31Thermostat.cpp
 * Author       2021-10-22 Charles Geiser (https://www.dodeka.ch)
 *
 * Purpose      Implements a class SHT31Thermostat.
 *              Inherits from class SHT31Sensor. 
 * 
 * Methods      loop()                   To be called in your main loop
 *              setRefreshInterval       Sets the time between two measurements
 *              setLimitLow              Sets the lower temperature limit
 *              setLimitHigh             Sets the upper temperature limit
 *              setTempDelta             Sets the allowed temperature range
 *              addOnLowTempReachedCB    Adds a callback to be called when the temperature drops below the lower limit
 *              addOnHighTempReachedCB   Adds a callback to be called when the temperature goes beyond than the upper limit
 *              addOnDataReadyCB
 *              printThermostatData
 *                           
 * Board        Arduino UNO
 * 
 * Remarks      
 * 
 * References    
 */
#include "SHT31Thermostat.h"

void SHT31Thermostat::setRefreshInterval(uint32_t msRefresh)
{
    _data.msRefresh = msRefresh;
}

void SHT31Thermostat::setLimitLow(float tLow)
{
    _data.tLimitLow = tLow;
    _data.tLimitHigh = _data.tLimitLow + _data.tDelta;
}

void SHT31Thermostat::setLimitHigh(float tHigh)
{
    _data.tLimitHigh = tHigh;
    _data.tLimitLow = _data.tLimitHigh - _data.tDelta;
}

void SHT31Thermostat::setTempDelta(float delta)
{
    _data.tDelta = delta;
    _data.tLimitLow = _data.tLimitHigh - _data.tDelta;
}

void SHT31Thermostat::loop()
{
    if (millis() > _data.msPrevious + _data.msRefresh )
    {
        readSensor();
        _onDataReady();
        if (_sensorData.tCelsius >= _data.tLimitHigh) _onHighTempReached();
        if (_sensorData.tCelsius < _data.tLimitLow)  _onLowTempReached();
        _data.msPrevious = millis();
    }
}

void SHT31Thermostat::addOnLowTempReachedCB(CallbackFunction cb)
{
    _onLowTempReached = cb;
}

void SHT31Thermostat::addOnHighTempReachedCB(CallbackFunction cb)
{
    _onHighTempReached = cb;
}

void SHT31Thermostat::addOnDataReadyCB(CallbackFunction cb)
{
    _onDataReady = cb;
}

void SHT31Thermostat::printThermostatData()
{
    char buf[120];

    snprintf(buf, sizeof(buf), R"(
    Lower limit   %6.1f °C
    Upper limit   %6.1f °C
    Delta T       %6.1f °C
    Refresh interval %5d)",
        (double)_data.tLimitLow,
        (double)_data.tLimitHigh,
        (double)_data.tDelta,
        (int)_data.msRefresh);
    Serial.println(buf);
}

void SHT31Thermostat::getThermostatData(SHT31ThermostatData &data)
{
    data = _data;
}
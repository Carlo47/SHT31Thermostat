/**
 * Header       SHT31Sensor.h
 * Author       2021-10-22 Charles Geiser (https://www.dodeka.ch)
 * 
 * Purpose      Declaration of the class SHT31Thermostat
 *              Inherits from SHT31Sensor class
 * 
 * Constructor
 * arguments    i2cAddress    Address of the I2C-Interface of the SHT31 sensor
 */
#include "SHT31Sensor.h"

#ifndef _SHT31THERMOSTAT_H
#define _SHT31THERMOSTAT_H

typedef void(*CallbackFunction)();

class SHT31ThermostatData
{
    public:
        uint32_t msPrevious = 0;
        uint32_t msRefresh  = 10000;
        float    tLimitHigh = 20.0;    // user defined upper temperature limit
        float    tLimitLow  = 19.0;    // user defined lower temperature limit (or calculated when max deviation is set)
        float    tDelta     =  1.0;    // user defined max deviation from upper temperature (or calculated when lower temperature is set)
};

class SHT31Thermostat : public SHT31Sensor
{
    private:
        static void _nop(){};
        SHT31ThermostatData  _data;
        CallbackFunction _onLowTempReached  = _nop;
        CallbackFunction _onHighTempReached = _nop;
        CallbackFunction _onDataReady       = _nop;

    public:
        SHT31Thermostat(uint8_t i2cAddress) : SHT31Sensor(i2cAddress) {}

        void setRefreshInterval(uint32_t msRefresh);
        void setLimitHigh(float tHigh);
        void setLimitLow(float tLow);
        void setTempDelta(float delta);
        void getThermostatData(SHT31ThermostatData &data);
        void loop();
        void addOnLowTempReachedCB(CallbackFunction cb);
        void addOnHighTempReachedCB(CallbackFunction cb);
        void addOnDataReadyCB(CallbackFunction cb);
        void printThermostatData();
};
#endif
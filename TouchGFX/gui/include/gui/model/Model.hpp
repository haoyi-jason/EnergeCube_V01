#ifndef MODEL_HPP
#define MODEL_HPP

#include <stdint.h>

class ModelListener;

class Model
{
public:
    struct EnergyData {
        float    voltage_V;       // Battery/bus voltage (V)
        float    current_A;       // Load/charge current (A)
        float    power_W;         // Instantaneous power (W)
        uint8_t  soc_pct;         // State of Charge (%)
        int8_t   temperature_C;   // Temperature (°C)
        uint16_t faultFlags;      // Bitmask of fault codes
        bool     chargeEnabled;   // Charge relay state
        bool     isOnline;        // System online/comms alive
    };

    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    // Getters
    const EnergyData& getEnergyData() const { return energyData; }
    float getVoltage() const { return energyData.voltage_V; }
    float getCurrent() const { return energyData.current_A; }
    float getPower() const { return energyData.power_W; }
    uint8_t getSoC() const { return energyData.soc_pct; }
    int8_t getTemperature() const { return energyData.temperature_C; }
    uint16_t getFaultFlags() const { return energyData.faultFlags; }
    bool isChargeEnabled() const { return energyData.chargeEnabled; }
    bool isOnline() const { return energyData.isOnline; }

    // Setters
    void setVoltage(float v) { energyData.voltage_V = v; }
    void setCurrent(float a) { energyData.current_A = a; }
    void setPower(float w) { energyData.power_W = w; }
    void setSoC(uint8_t pct) { energyData.soc_pct = pct; }
    void setTemperature(int8_t c) { energyData.temperature_C = c; }
    void setFaultFlags(uint16_t flags) { energyData.faultFlags = flags; }
    void setChargeEnabled(bool en) { energyData.chargeEnabled = en; }
    void setOnline(bool online) { energyData.isOnline = online; }

protected:
    ModelListener* modelListener;

private:
    EnergyData energyData;
    uint32_t   tickCounter;
};

#endif // MODEL_HPP

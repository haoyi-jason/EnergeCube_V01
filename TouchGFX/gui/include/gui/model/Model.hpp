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

    struct MainScreenData {
        // Panel A – AC Input
        float ac_in_voltage;
        float ac_in_current;
        // Panel B – DC Input
        float dc_in_voltage;
        float dc_in_current;
        // Panel C – MPPT
        float mppt_voltage;
        float mppt_current;
        // Panel D – Battery
        float   bat_voltage;
        float   bat_current;
        uint8_t soc_pct;
        bool    alarm_active;
        // Panel E – AC Output
        float ac_out_voltage;
        float ac_out_current;
        float ac_out_power;
        // Panel F – Fan / Temperature
        int8_t temp_box;
        int8_t temp_other;
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

    const MainScreenData& getMainScreenData() const { return mainData; }
    void setMainScreenData(const MainScreenData& d);

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
    EnergyData     energyData;
    MainScreenData mainData;
    uint32_t       tickCounter;
};

#endif // MODEL_HPP

#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0), tickCounter(0)
{
    energyData.voltage_V     = 48.0f;
    energyData.current_A     = 0.0f;
    energyData.power_W       = 0.0f;
    energyData.soc_pct       = 0;
    energyData.temperature_C = 25;
    energyData.faultFlags    = 0;
    energyData.chargeEnabled = true;
    energyData.isOnline      = true;

    mainData.ac_in_voltage  = 0.0f;
    mainData.ac_in_current  = 0.0f;
    mainData.dc_in_voltage  = 0.0f;
    mainData.dc_in_current  = 0.0f;
    mainData.mppt_voltage   = 0.0f;
    mainData.mppt_current   = 0.0f;
    mainData.bat_voltage    = 0.0f;
    mainData.bat_current    = 0.0f;
    mainData.soc_pct        = 0;
    mainData.alarm_active   = false;
    mainData.ac_out_voltage = 0.0f;
    mainData.ac_out_current = 0.0f;
    mainData.ac_out_power   = 0.0f;
    mainData.temp_box       = 0;
    mainData.temp_other     = 0;
}

void Model::tick()
{
    tickCounter++;

    /* Simulate voltage cycling 48.0 -> 54.0 V over ~600 ticks */
    energyData.voltage_V = 48.0f + 6.0f * ((tickCounter % 601) / 600.0f);

    /* Simulate current oscillating between -10 A and +10 A */
    float phase = (tickCounter % 200) / 200.0f; // 0..1
    if (phase < 0.5f)
        energyData.current_A = -10.0f + 40.0f * phase;        // -10 -> +10
    else
        energyData.current_A = 30.0f - 40.0f * phase;         // +10 -> -10

    /* Instantaneous power */
    energyData.power_W = energyData.voltage_V * energyData.current_A;

    /* SoC counts 0->100 over 1000 ticks, then resets */
    energyData.soc_pct = (uint8_t)((tickCounter % 1000) / 10);

    /* Temperature stays at 25 °C in simulation */
    energyData.temperature_C = 25;

    /* Notify listener */
    if (modelListener != 0)
    {
        modelListener->energyDataUpdated(energyData);
    }

    /* Populate mainData from energyData for simulation */
    mainData.ac_in_voltage  = 220.0f;
    mainData.ac_in_current  = 5.0f;
    mainData.dc_in_voltage  = 24.0f;
    mainData.dc_in_current  = 3.5f;
    mainData.mppt_voltage   = 36.0f;
    mainData.mppt_current   = 4.0f;
    mainData.bat_voltage    = energyData.voltage_V;
    mainData.bat_current    = energyData.current_A;
    mainData.soc_pct        = energyData.soc_pct;
    mainData.alarm_active   = (energyData.faultFlags != 0);
    mainData.ac_out_voltage = 220.0f;
    mainData.ac_out_current = 2.5f;
    mainData.ac_out_power   = 220.0f * 2.5f;
    mainData.temp_box       = energyData.temperature_C;
    mainData.temp_other     = energyData.temperature_C + 5;

    if (modelListener != 0)
    {
        modelListener->mainDataUpdated(mainData);
    }
}

void Model::setMainScreenData(const MainScreenData& d)
{
    mainData = d;
    if (modelListener != 0)
        modelListener->mainDataUpdated(mainData);
}

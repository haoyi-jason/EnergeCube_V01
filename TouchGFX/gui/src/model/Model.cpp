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
}

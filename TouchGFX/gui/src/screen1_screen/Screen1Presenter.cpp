#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{
    model->bind(this);
}

void Screen1Presenter::deactivate()
{
    model->bind(0);
}

void Screen1Presenter::notifyScreenSetup()
{
    /* Forward current model data to the view immediately after setup */
    energyDataUpdated(model->getEnergyData());
}

void Screen1Presenter::energyDataUpdated(const Model::EnergyData& data)
{
    view.updateEnergyDisplay(data.voltage_V, data.current_A, data.power_W,
                             data.soc_pct, data.temperature_C, data.isOnline);
}

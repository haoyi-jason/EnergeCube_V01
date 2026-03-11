#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

Screen2Presenter::Screen2Presenter(Screen2View& v)
    : view(v)
{

}

void Screen2Presenter::activate()
{
    model->bind(this);
}

void Screen2Presenter::deactivate()
{
    model->bind(0);
}

void Screen2Presenter::energyDataUpdated(const Model::EnergyData& data)
{
    view.updateFaultStatus(data.faultFlags, data.chargeEnabled);
}

#include <gui/screen3_screen/Screen3View.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

Screen3Presenter::Screen3Presenter(Screen3View& v)
    : view(v)
{

}

void Screen3Presenter::activate()
{
    model->bind(this);
}

void Screen3Presenter::deactivate()
{
    model->bind(0);
}

void Screen3Presenter::energyDataUpdated(const Model::EnergyData& data)
{
    view.updateChargeState(data.chargeEnabled);
}

void Screen3Presenter::toggleChargeEnable()
{
    model->setChargeEnabled(!model->isChargeEnabled());
}

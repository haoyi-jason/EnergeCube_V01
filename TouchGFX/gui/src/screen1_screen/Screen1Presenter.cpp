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
    mainDataUpdated(model->getMainScreenData());
}

void Screen1Presenter::energyDataUpdated(const Model::EnergyData& data)
{
    (void)data;
    /* EnergyData is still available for legacy use or future extension */
}

void Screen1Presenter::mainDataUpdated(const Model::MainScreenData& data)
{
    view.updateMainDisplay(data);
}

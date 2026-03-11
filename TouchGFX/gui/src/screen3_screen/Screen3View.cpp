#include <gui/screen3_screen/Screen3View.hpp>

Screen3View::Screen3View()
{

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();

    /* Display firmware version */
    touchgfx::Unicode::snprintf(versionBuf, TEXT_BUF_SIZE, "v1.0.0");
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

void Screen3View::updateChargeState(bool chargeEnabled)
{
    touchgfx::Unicode::snprintf(chargeBuf, TEXT_BUF_SIZE,
                                chargeEnabled ? "CHG: ENABLED" : "CHG: DISABLED");
}

void Screen3View::toggleChargeEnable()
{
    presenter->toggleChargeEnable();
}

#include <gui/screen2_screen/Screen2View.hpp>

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::updateFaultStatus(uint16_t faultFlags, bool chargeEnabled)
{
    if (faultFlags == 0)
    {
        touchgfx::Unicode::snprintf(faultBuf, TEXT_BUF_SIZE, "OK");
    }
    else
    {
        touchgfx::Unicode::snprintf(faultBuf, TEXT_BUF_SIZE, "FAULT:0x%04X", (unsigned)faultFlags);
    }

    touchgfx::Unicode::snprintf(chargeBuf, TEXT_BUF_SIZE,
                                chargeEnabled ? "CHG:ON" : "CHG:OFF");
}

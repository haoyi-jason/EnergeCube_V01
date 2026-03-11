#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
    presenter->notifyScreenSetup();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateEnergyDisplay(float voltage, float current, float power,
                                      uint8_t soc, int8_t temp, bool online)
{
    (void)online;

    touchgfx::Unicode::snprintf(voltageBuf, TEXT_BUF_SIZE, "%d.%01dV",
                                (int)voltage,
                                (int)((voltage - (int)voltage) * 10));

    if (current < 0.0f)
    {
        float absCurrent = -current;
        touchgfx::Unicode::snprintf(currentBuf, TEXT_BUF_SIZE, "-%d.%01dA",
                                    (int)absCurrent,
                                    (int)((absCurrent - (int)absCurrent) * 10));
    }
    else
    {
        touchgfx::Unicode::snprintf(currentBuf, TEXT_BUF_SIZE, "%d.%01dA",
                                    (int)current,
                                    (int)((current - (int)current) * 10));
    }

    if (power < 0.0f)
    {
        touchgfx::Unicode::snprintf(powerBuf, TEXT_BUF_SIZE, "-%dW", (int)(-power));
    }
    else
    {
        touchgfx::Unicode::snprintf(powerBuf, TEXT_BUF_SIZE, "%dW", (int)power);
    }

    touchgfx::Unicode::snprintf(socBuf, TEXT_BUF_SIZE, "%d%%", (int)soc);

    touchgfx::Unicode::snprintf(tempBuf, TEXT_BUF_SIZE, "%d C", (int)temp);
}

#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Color.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();

    // Attach wildcard buffers to every text widget
    // T_WILDCARD must exist in the TouchGFX texts system

    textA2.setWildcard(bufA2);
    textA3.setWildcard(bufA3);

    textB2.setWildcard(bufB2);
    textB3.setWildcard(bufB3);

    textC2.setWildcard(bufC2);
    textC3.setWildcard(bufC3);

    textD_vc.setWildcard(bufD_vc);
    textD_soc.setWildcard(bufD_soc);
    textD_alarm.setWildcard(bufD_alarm);

    textE2.setWildcard(bufE2);
    textE3.setWildcard(bufE3);

    textF2.setWildcard(bufF2);
    textF3.setWildcard(bufF3);

    presenter->notifyScreenSetup();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::updateSocBar(uint8_t soc_pct)
{
    /* Clamp to 0-100 */
    if (soc_pct > 100)
    {
        soc_pct = 100;
    }

    int fillWidth = (socBarBg.getWidth() * soc_pct) / 100;
    socBarFill.setWidth(fillWidth);
    socBarFill.invalidate();
}

void Screen1View::updateMainDisplay(const Model::MainScreenData& d)
{
    /* Panel A – AC Input */
    touchgfx::Unicode::snprintf(bufA2, TEXT_BUF_SIZE, "%d.%01dV",
                                (int)d.ac_in_voltage,
                                (int)((d.ac_in_voltage - (int)d.ac_in_voltage) * 10));
    touchgfx::Unicode::snprintf(bufA3, TEXT_BUF_SIZE, "%d.%01dA",
                                (int)d.ac_in_current,
                                (int)((d.ac_in_current - (int)d.ac_in_current) * 10));
    textA2.invalidate();
    textA3.invalidate();

    /* Panel B – DC Input */
    touchgfx::Unicode::snprintf(bufB2, TEXT_BUF_SIZE, "%d.%01dV",
                                (int)d.dc_in_voltage,
                                (int)((d.dc_in_voltage - (int)d.dc_in_voltage) * 10));
    touchgfx::Unicode::snprintf(bufB3, TEXT_BUF_SIZE, "%d.%01dA",
                                (int)d.dc_in_current,
                                (int)((d.dc_in_current - (int)d.dc_in_current) * 10));
    textB2.invalidate();
    textB3.invalidate();

    /* Panel C – MPPT */
    touchgfx::Unicode::snprintf(bufC2, TEXT_BUF_SIZE, "%d.%01dV",
                                (int)d.mppt_voltage,
                                (int)((d.mppt_voltage - (int)d.mppt_voltage) * 10));
    touchgfx::Unicode::snprintf(bufC3, TEXT_BUF_SIZE, "%d.%01dA",
                                (int)d.mppt_current,
                                (int)((d.mppt_current - (int)d.mppt_current) * 10));
    textC2.invalidate();
    textC3.invalidate();

    /* Panel D – Battery */
    touchgfx::Unicode::snprintf(bufD_vc, TEXT_BUF_SIZE, "%d.%01dV %d.%01dA",
                                (int)d.bat_voltage,
                                (int)((d.bat_voltage - (int)d.bat_voltage) * 10),
                                (int)d.bat_current,
                                (int)((d.bat_current - (int)d.bat_current) * 10));
    textD_vc.invalidate();

    touchgfx::Unicode::snprintf(bufD_soc, TEXT_BUF_SIZE, "%d%%", (int)d.soc_pct);
    textD_soc.invalidate();

    updateSocBar(d.soc_pct);

    if (d.alarm_active)
    {
        touchgfx::Unicode::snprintf(bufD_alarm, TEXT_BUF_SIZE, "ALARM!");
        textD_alarm.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    }
    else
    {
        touchgfx::Unicode::snprintf(bufD_alarm, TEXT_BUF_SIZE, "OK");
        textD_alarm.setColor(touchgfx::Color::getColorFromRGB(0, 255, 0));
    }
    textD_alarm.invalidate();

    /* Panel E – AC Output */
    touchgfx::Unicode::snprintf(bufE2, TEXT_BUF_SIZE, "%d.%01dV %d.%01dA",
                                (int)d.ac_out_voltage,
                                (int)((d.ac_out_voltage - (int)d.ac_out_voltage) * 10),
                                (int)d.ac_out_current,
                                (int)((d.ac_out_current - (int)d.ac_out_current) * 10));
    touchgfx::Unicode::snprintf(bufE3, TEXT_BUF_SIZE, "%dW", (int)d.ac_out_power);
    textE2.invalidate();
    textE3.invalidate();

    /* Panel F – Fan/Temperature */
    touchgfx::Unicode::snprintf(bufF2, TEXT_BUF_SIZE, "Box:%dC", (int)d.temp_box);
    touchgfx::Unicode::snprintf(bufF3, TEXT_BUF_SIZE, "Other:%dC", (int)d.temp_other);
    textF2.invalidate();
    textF3.invalidate();
}

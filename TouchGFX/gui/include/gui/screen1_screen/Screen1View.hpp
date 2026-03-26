#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/Unicode.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateMainDisplay(const Model::MainScreenData& d);

protected:
    static const uint8_t TEXT_BUF_SIZE = 32;

    /* Panel A – AC Input */
    touchgfx::Unicode::UnicodeChar bufA2[TEXT_BUF_SIZE];   // Voltage
    touchgfx::Unicode::UnicodeChar bufA3[TEXT_BUF_SIZE];   // Current

    /* Panel B – DC Input */
    touchgfx::Unicode::UnicodeChar bufB2[TEXT_BUF_SIZE];   // Voltage
    touchgfx::Unicode::UnicodeChar bufB3[TEXT_BUF_SIZE];   // Current

    /* Panel C – MPPT */
    touchgfx::Unicode::UnicodeChar bufC2[TEXT_BUF_SIZE];   // Voltage
    touchgfx::Unicode::UnicodeChar bufC3[TEXT_BUF_SIZE];   // Current

    /* Panel D – Battery */
    touchgfx::Unicode::UnicodeChar bufD_vc[TEXT_BUF_SIZE];    // Voltage/Current
    touchgfx::Unicode::UnicodeChar bufD_soc[TEXT_BUF_SIZE];   // SOC %
    touchgfx::Unicode::UnicodeChar bufD_alarm[TEXT_BUF_SIZE]; // Alarm status

    /* Panel E – AC Output */
    touchgfx::Unicode::UnicodeChar bufE2[TEXT_BUF_SIZE];   // Voltage/Current
    touchgfx::Unicode::UnicodeChar bufE3[TEXT_BUF_SIZE];   // Power

    /* Panel F – Fan/Temperature */
    touchgfx::Unicode::UnicodeChar bufF2[TEXT_BUF_SIZE];   // Box temperature
    touchgfx::Unicode::UnicodeChar bufF3[TEXT_BUF_SIZE];   // Other temperature

private:
    void updateSocBar(uint8_t soc_pct);
};

#endif // SCREEN1VIEW_HPP

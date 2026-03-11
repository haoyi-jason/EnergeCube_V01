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

    void updateEnergyDisplay(float voltage, float current, float power,
                             uint8_t soc, int8_t temp, bool online);

protected:
    static const uint8_t TEXT_BUF_SIZE = 32;
    touchgfx::Unicode::UnicodeChar voltageBuf[TEXT_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar currentBuf[TEXT_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar powerBuf[TEXT_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar socBuf[TEXT_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar tempBuf[TEXT_BUF_SIZE];
};

#endif // SCREEN1VIEW_HPP

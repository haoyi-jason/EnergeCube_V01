#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <touchgfx/Unicode.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateFaultStatus(uint16_t faultFlags, bool chargeEnabled);

protected:
    static const uint8_t TEXT_BUF_SIZE = 48;
    touchgfx::Unicode::UnicodeChar faultBuf[TEXT_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar chargeBuf[TEXT_BUF_SIZE];
};

#endif // SCREEN2VIEW_HPP

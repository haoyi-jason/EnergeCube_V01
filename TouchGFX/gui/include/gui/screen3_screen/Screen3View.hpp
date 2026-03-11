#ifndef SCREEN3VIEW_HPP
#define SCREEN3VIEW_HPP

#include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>
#include <touchgfx/Unicode.hpp>

class Screen3View : public Screen3ViewBase
{
public:
    Screen3View();
    virtual ~Screen3View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void updateChargeState(bool chargeEnabled);
    void toggleChargeEnable();

protected:
    static const uint8_t TEXT_BUF_SIZE = 32;
    touchgfx::Unicode::UnicodeChar chargeBuf[TEXT_BUF_SIZE];
    touchgfx::Unicode::UnicodeChar versionBuf[TEXT_BUF_SIZE];
};

#endif // SCREEN3VIEW_HPP

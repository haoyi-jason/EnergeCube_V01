#ifndef SCREEN1VIEW_HPP
#define SCREEN1VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/Bitmap.hpp>

class Screen1View : public Screen1ViewBase
{
public:
    // Button identifiers for the 6 function buttons on Screen 1
    enum ButtonId
    {
        BTN_A = 0,
        BTN_B,
        BTN_C,
        BTN_E,
        BTN_F,
        BTN_G
    };

    Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Button click handlers
    void onButtonAClicked();
    void onButtonBClicked();
    void onButtonCClicked();
    void onButtonEClicked();
    void onButtonFClicked();
    void onButtonGClicked();

    // Button icon setters (64x64 bitmap)
    void setButtonAIcon(const touchgfx::BitmapId icon);
    void setButtonBIcon(const touchgfx::BitmapId icon);
    void setButtonCIcon(const touchgfx::BitmapId icon);
    void setButtonEIcon(const touchgfx::BitmapId icon);
    void setButtonFIcon(const touchgfx::BitmapId icon);
    void setButtonGIcon(const touchgfx::BitmapId icon);

    // Button text line A setters
    void setButtonATextA(const char* text);
    void setButtonBTextA(const char* text);
    void setButtonCTextA(const char* text);
    void setButtonETextA(const char* text);
    void setButtonFTextA(const char* text);
    void setButtonGTextA(const char* text);

    // Button text line B setters
    void setButtonATextB(const char* text);
    void setButtonBTextB(const char* text);
    void setButtonCTextB(const char* text);
    void setButtonETextB(const char* text);
    void setButtonFTextB(const char* text);
    void setButtonGTextB(const char* text);

    // Area D API
    void setAreaDTextA(const char* text);
    void setAreaDTextB(const char* text);
    void setAreaDTextC(const char* text);
    void setAreaDIcon(const touchgfx::BitmapId icon);

    // Navigation
    void gotoScreen2();

protected:
};

#endif // SCREEN1VIEW_HPP

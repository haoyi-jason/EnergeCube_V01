#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

// Button click handlers

void Screen1View::onButtonAClicked()
{
    /* TODO: implement button A action */
}

void Screen1View::onButtonBClicked()
{
    /* TODO: implement button B action */
}

void Screen1View::onButtonCClicked()
{
    /* TODO: implement button C action */
}

void Screen1View::onButtonEClicked()
{
    /* TODO: implement button E action */
}

void Screen1View::onButtonFClicked()
{
    /* TODO: implement button F action */
}

void Screen1View::onButtonGClicked()
{
    gotoScreen2();
}

// Button icon setters (64x64 bitmap)

void Screen1View::setButtonAIcon(const touchgfx::BitmapId icon)
{
    /* TODO: wire to TouchGFX widget for button A */
    (void)icon;
}

void Screen1View::setButtonBIcon(const touchgfx::BitmapId icon)
{
    /* TODO: wire to TouchGFX widget for button B */
    (void)icon;
}

void Screen1View::setButtonCIcon(const touchgfx::BitmapId icon)
{
    /* TODO: wire to TouchGFX widget for button C */
    (void)icon;
}

void Screen1View::setButtonEIcon(const touchgfx::BitmapId icon)
{
    /* TODO: wire to TouchGFX widget for button E */
    (void)icon;
}

void Screen1View::setButtonFIcon(const touchgfx::BitmapId icon)
{
    /* TODO: wire to TouchGFX widget for button F */
    (void)icon;
}

void Screen1View::setButtonGIcon(const touchgfx::BitmapId icon)
{
    /* TODO: wire to TouchGFX widget for button G */
    (void)icon;
}

// Button text line A setters

void Screen1View::setButtonATextA(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button A, line A */
    (void)text;
}

void Screen1View::setButtonBTextA(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button B, line A */
    (void)text;
}

void Screen1View::setButtonCTextA(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button C, line A */
    (void)text;
}

void Screen1View::setButtonETextA(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button E, line A */
    (void)text;
}

void Screen1View::setButtonFTextA(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button F, line A */
    (void)text;
}

void Screen1View::setButtonGTextA(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button G, line A */
    (void)text;
}

// Button text line B setters

void Screen1View::setButtonATextB(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button A, line B */
    (void)text;
}

void Screen1View::setButtonBTextB(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button B, line B */
    (void)text;
}

void Screen1View::setButtonCTextB(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button C, line B */
    (void)text;
}

void Screen1View::setButtonETextB(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button E, line B */
    (void)text;
}

void Screen1View::setButtonFTextB(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button F, line B */
    (void)text;
}

void Screen1View::setButtonGTextB(const char* text)
{
    /* TODO: wire to TouchGFX label widget for button G, line B */
    (void)text;
}

// Area D API

void Screen1View::setAreaDTextA(const char* text)
{
    /* TODO: wire to TouchGFX label widget for Area D, line A */
    (void)text;
}

void Screen1View::setAreaDTextB(const char* text)
{
    /* TODO: wire to TouchGFX label widget for Area D, line B */
    (void)text;
}

void Screen1View::setAreaDTextC(const char* text)
{
    /* TODO: wire to TouchGFX label widget for Area D, line C */
    (void)text;
}

void Screen1View::setAreaDIcon(const touchgfx::BitmapId icon)
{
    /* TODO: wire to TouchGFX image widget for Area D */
    (void)icon;
}

// Navigation

void Screen1View::gotoScreen2()
{
    application().gotoScreen2ScreenCoverTransitionEast();
}


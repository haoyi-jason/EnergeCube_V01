#ifndef SCREEN3VIEW_HPP
#define SCREEN3VIEW_HPP

#ifdef __has_include
#  if __has_include(<gui_generated/screen3_screen/Screen3ViewBase.hpp>)
#    include <gui_generated/screen3_screen/Screen3ViewBase.hpp>
#    define SCREEN3_HAS_GENERATED_BASE 1
#  endif
#endif

#ifndef SCREEN3_HAS_GENERATED_BASE
/* Screen3ViewBase has not been generated yet by TouchGFX Designer.
 * Provide a forward-compatible minimal base so this header can be
 * compiled while the designer project is still being set up. */
#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>
class Screen3ViewBase : public touchgfx::View<Screen3Presenter>
{
public:
    Screen3ViewBase() {}
    virtual ~Screen3ViewBase() {}
    virtual void setupScreen() {}
    virtual void tearDownScreen() {}
protected:
    FrontendApplication& application()
    {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }
};
#endif // SCREEN3_HAS_GENERATED_BASE

#include <stdint.h>

// DF_ parameter table entry (user-defined, expandable)
struct DF_Param
{
    char    name[32];
    int32_t value;
};

// LD_ parameter table entry (user-defined, expandable)
struct LD_Param
{
    char  name[32];
    float value;
};

class Screen3View : public Screen3ViewBase
{
public:
    Screen3View();
    virtual ~Screen3View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // DF_ parameter table API
    static const uint8_t DF_PARAM_COUNT = 8;
    DF_Param dfParams[DF_PARAM_COUNT];
    void    setDF_Param(uint8_t index, const char* name, int32_t value);
    int32_t getDF_Param(uint8_t index) const;

    // LD_ parameter table API
    static const uint8_t LD_PARAM_COUNT = 8;
    LD_Param ldParams[LD_PARAM_COUNT];
    void  setLD_Param(uint8_t index, const char* name, float value);
    float getLD_Param(uint8_t index) const;

    // System reset
    void systemReset();

    // Time calibration
    // @param weekday  RTC_WEEKDAY_* constant (1=Monday .. 7=Sunday); defaults to Monday (1)
    void calibrateTime(uint16_t year, uint8_t month, uint8_t day,
                       uint8_t hour, uint8_t minute, uint8_t second,
                       uint8_t weekday = 1u);

    // Navigation
    void gotoScreen1();

protected:
};

#endif // SCREEN3VIEW_HPP

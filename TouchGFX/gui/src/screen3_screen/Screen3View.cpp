#include <gui/screen3_screen/Screen3View.hpp>
#include <string.h>
#include <stdio.h>
#include "stm32h7xx_hal.h"

extern RTC_HandleTypeDef hrtc;

Screen3View::Screen3View()
{
    // Initialise DF_ parameter table with default names and zero values
    for (uint8_t i = 0; i < DF_PARAM_COUNT; i++)
    {
        snprintf(dfParams[i].name, sizeof(dfParams[i].name), "DF_%02u", i);
        dfParams[i].value = 0;
    }

    // Initialise LD_ parameter table with default names and zero values
    for (uint8_t i = 0; i < LD_PARAM_COUNT; i++)
    {
        snprintf(ldParams[i].name, sizeof(ldParams[i].name), "LD_%02u", i);
        ldParams[i].value = 0.0f;
    }
}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

// DF_ parameter table API

void Screen3View::setDF_Param(uint8_t index, const char* name, int32_t value)
{
    if (index >= DF_PARAM_COUNT)
    {
        return;
    }
    strncpy(dfParams[index].name, name, sizeof(dfParams[index].name) - 1);
    dfParams[index].name[sizeof(dfParams[index].name) - 1] = '\0';
    dfParams[index].value = value;
}

int32_t Screen3View::getDF_Param(uint8_t index) const
{
    if (index >= DF_PARAM_COUNT)
    {
        return 0;
    }
    return dfParams[index].value;
}

// LD_ parameter table API

void Screen3View::setLD_Param(uint8_t index, const char* name, float value)
{
    if (index >= LD_PARAM_COUNT)
    {
        return;
    }
    strncpy(ldParams[index].name, name, sizeof(ldParams[index].name) - 1);
    ldParams[index].name[sizeof(ldParams[index].name) - 1] = '\0';
    ldParams[index].value = value;
}

float Screen3View::getLD_Param(uint8_t index) const
{
    if (index >= LD_PARAM_COUNT)
    {
        return 0.0f;
    }
    return ldParams[index].value;
}

// System reset — triggers an immediate MCU software reset via NVIC

void Screen3View::systemReset()
{
    NVIC_SystemReset();
}

// Time calibration — programmes the STM32 RTC via HAL

void Screen3View::calibrateTime(uint16_t year, uint8_t month, uint8_t day,
                                uint8_t hour, uint8_t minute, uint8_t second,
                                uint8_t weekday)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    sTime.Hours   = hour;
    sTime.Minutes = minute;
    sTime.Seconds = second;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

    sDate.Year  = (year >= 2000u) ? (uint8_t)(year - 2000u) : 0u; // HAL expects 2-digit offset from 2000
    sDate.Month = month;
    sDate.Date  = day;
    sDate.WeekDay = weekday;    // Use RTC_WEEKDAY_* constants (1=Monday .. 7=Sunday)
    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

// Navigation

void Screen3View::gotoScreen1()
{
    application().gotoScreen1ScreenCoverTransitionWest();
}

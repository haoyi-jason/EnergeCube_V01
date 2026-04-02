#include <gui/screen2_screen/Screen2View.hpp>
#include <string.h>
#include "ff.h"

Screen2View::Screen2View()
    : logCount(0)
{
    memset(logBuffer, 0, sizeof(logBuffer));
}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::addLogEntry(const char* timestamp, const char* message)
{
    if (logCount < LOG_CAPACITY)
    {
        strncpy(logBuffer[logCount].timestamp, timestamp, sizeof(logBuffer[logCount].timestamp) - 1);
        logBuffer[logCount].timestamp[sizeof(logBuffer[logCount].timestamp) - 1] = '\0';
        strncpy(logBuffer[logCount].message, message, sizeof(logBuffer[logCount].message) - 1);
        logBuffer[logCount].message[sizeof(logBuffer[logCount].message) - 1] = '\0';
        logCount++;
    }
    else
    {
        // Circular buffer: shift all entries left by one to drop the oldest,
        // then store the newest entry at the end.
        memmove(&logBuffer[0], &logBuffer[1], sizeof(LogEntry) * (LOG_CAPACITY - 1));
        strncpy(logBuffer[LOG_CAPACITY - 1].timestamp, timestamp, sizeof(logBuffer[0].timestamp) - 1);
        logBuffer[LOG_CAPACITY - 1].timestamp[sizeof(logBuffer[0].timestamp) - 1] = '\0';
        strncpy(logBuffer[LOG_CAPACITY - 1].message, message, sizeof(logBuffer[0].message) - 1);
        logBuffer[LOG_CAPACITY - 1].message[sizeof(logBuffer[0].message) - 1] = '\0';
    }

    // Append the new entry to the persistent log file on eMMC
    FIL fil;
    FRESULT res = f_open(&fil, "/EMMC/system_log.csv", FA_OPEN_APPEND | FA_WRITE);
    if (res == FR_OK)
    {
        char line[160];
        snprintf(line, sizeof(line), "%s,%s\n", timestamp, message);
        UINT bw;
        f_write(&fil, line, strlen(line), &bw);
        f_close(&fil);
    }

    refreshLogTable();
}

void Screen2View::clearLog()
{
    logCount = 0;
    memset(logBuffer, 0, sizeof(logBuffer));
    f_unlink("/EMMC/system_log.csv");
    refreshLogTable();
}

void Screen2View::exportLogToSD()
{
    FIL fil;
    FRESULT res = f_open(&fil, "/SD/system_log_export.csv", FA_CREATE_ALWAYS | FA_WRITE);
    if (res == FR_OK)
    {
        const char* header = "timestamp,message\n";
        UINT bw;
        f_write(&fil, header, strlen(header), &bw);

        char line[160];
        for (uint16_t i = 0; i < logCount; i++)
        {
            snprintf(line, sizeof(line), "%s,%s\n",
                     logBuffer[i].timestamp,
                     logBuffer[i].message);
            f_write(&fil, line, strlen(line), &bw);
        }
        f_close(&fil);
    }
}

void Screen2View::gotoScreen1()
{
    application().gotoScreen1ScreenCoverTransitionWest();
}

void Screen2View::refreshLogTable()
{
    /* TODO: refresh the scrollable log table widget when TouchGFX designer
     * wiring is complete. This stub triggers a screen invalidation so the
     * UI redraws on the next frame. */
    invalidate();
}


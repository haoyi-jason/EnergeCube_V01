#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>
#include <stdint.h>

class Screen2View : public Screen2ViewBase
{
public:
    // Maximum number of log entries held in memory
    static const uint16_t LOG_CAPACITY = 1000;

    // A single system log record
    struct LogEntry
    {
        char timestamp[20];  // "YYYY-MM-DD HH:MM:SS"
        char message[128];
    };

    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    // Log management
    void addLogEntry(const char* timestamp, const char* message);
    void clearLog();
    void exportLogToSD();

    // Navigation
    void gotoScreen1();

    // UI refresh
    void refreshLogTable();

protected:
    LogEntry logBuffer[LOG_CAPACITY];
    uint16_t logCount;
};

#endif // SCREEN2VIEW_HPP

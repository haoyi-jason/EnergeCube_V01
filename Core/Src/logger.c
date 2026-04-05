#include "logger.h"
#include <string.h>

void logger_add_entry(const char* timestamp, const char* message)
{
    /* TODO: forward to Screen2View::addLogEntry() via model bridge or FreeRTOS queue */
    (void)timestamp;
    (void)message;
}

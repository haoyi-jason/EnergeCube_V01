#include "app_task.h"

/* C-callable wrapper called by AppTask every 100 ms.
 * The TouchGFX GUI thread drives Model::tick() via
 * FrontendApplication::handleTickEvent() on every display frame.
 * This stub exists as an extension point for external callers
 * (e.g. AppTask) and can be extended to inject hardware readings
 * into the model in future revisions.
 */

/* --------------------------------------------------------------------------
 * Logger integration extension point
 * --------------------------------------------------------------------------
 * When the FreeRTOS-based logger (Core/Src/logger.c) is ready to forward
 * log entries to the GUI, wire it here:
 *
 *   1. Declare a FreeRTOS queue handle in logger.c (e.g. xLogQueue).
 *   2. In model_tick_from_c() below, drain the queue and call a new
 *      Model method (e.g. Model::pushLogEntry()) which the Screen2Presenter
 *      will relay to Screen2View::addLogEntry().
 *
 * Example sketch:
 *
 *   extern QueueHandle_t xLogQueue;
 *   LogEntry_t entry;
 *   while (xQueueReceive(xLogQueue, &entry, 0) == pdTRUE)
 *   {
 *       // model.pushLogEntry(entry.timestamp, entry.message);
 *   }
 * --------------------------------------------------------------------------
 */
extern "C" void model_tick_from_c(void)
{
    /* Intentionally empty: model updates are currently driven by the
     * GUI thread in FrontendApplication::handleTickEvent(). */
}


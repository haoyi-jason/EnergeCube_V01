#include "app_task.h"

/* C-callable wrapper called by AppTask every 100 ms.
 * The TouchGFX GUI thread drives Model::tick() via
 * FrontendApplication::handleTickEvent() on every display frame.
 * This stub exists as an extension point for external callers
 * (e.g. AppTask) and can be extended to inject hardware readings
 * into the model in future revisions.
 */
extern "C" void model_tick_from_c(void)
{
    /* Intentionally empty: model updates are currently driven by the
     * GUI thread in FrontendApplication::handleTickEvent(). */
}

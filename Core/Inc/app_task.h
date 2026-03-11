#ifndef APP_TASK_H
#define APP_TASK_H

#ifdef __cplusplus
extern "C" {
#endif

void AppTask(void *argument);
void model_tick_from_c(void);   /* C-callable wrapper for Model::tick() */

#ifdef __cplusplus
}
#endif

#endif /* APP_TASK_H */

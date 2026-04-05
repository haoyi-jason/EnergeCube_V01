#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Add a log entry from C code (e.g. RTOS tasks, ISR-safe via queue).
 * @param timestamp  ISO-8601 string "YYYY-MM-DD HH:MM:SS"
 * @param message    Log message string (max 127 chars)
 */
void logger_add_entry(const char* timestamp, const char* message);

#ifdef __cplusplus
}
#endif

#endif /* LOGGER_H */

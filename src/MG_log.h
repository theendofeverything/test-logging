#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
////////////
// INTERNALS
////////////
uint32_t _MG_log_count = 0;

typedef enum
{
    _MG_LOG_INFO,
    _MG_LOG_UI,
    _MG_LOG_SDL,
    _MG_LOG_ERROR,
} _MG_log_category;

const char*  _MG_log_categories[] = {
    "INFO",
    "UI",
    "SDL",
    "ERROR",
};

bool _MG_log_config[] = {
    true,
    true,
    true,
    true,
};

int
_MG_log(
        _MG_log_category log_category,
        uint32_t log_count,
        const char* FILE,
        int LINE,
        const char* formatted_str,
        ...)
{
    int done;
    va_list arg;

    switch(log_category)
    {
        case _MG_LOG_INFO: case _MG_LOG_UI: case _MG_LOG_SDL:
            { // Print to stdout
                printf("LOG-%04d: %-8s %s:%d:\n\t", log_count, _MG_log_categories[log_category], FILE, LINE);

                va_start (arg, formatted_str);
                done = vfprintf(stdout, formatted_str, arg);
                va_end(arg);

                printf("\n");
                break;
            }
        case _MG_LOG_ERROR:
            { // Print to stderr
                fprintf(stderr, "LOG-%04d: %-8s %s:%d:\n\t", log_count, _MG_log_categories[log_category], FILE, LINE);

                va_start (arg, formatted_str);
                done = vfprintf(stderr, formatted_str, arg);
                va_end(arg);

                fprintf(stderr, "\n");
                break;
            }
    }
    return done;
}

#define LOG(category, str, ...) do\
    {\
        if (_MG_log_config[category])\
        {\
            _MG_log_count++;\
            _MG_log(category, _MG_log_count, __FILE__, __LINE__, str, __VA_ARGS__);\
        }\
    } while(0)

//////////////
// LOGGING API
//////////////
/** Use LOG_CATEGORY() instead of printf()
 *
 * LOG_INFO()
 * LOG_UI()
 * LOG_SDL()
 * LOG_ERROR()
 *
 * Example:
 *
 * ```c
 * int main(void) {
 *     LOG_INFO("2+2 = %d", 2+2);
 * }
 * ```
 *
 * The above prints the following to stdout:
 * LOG-0001: INFO     src/main.c:7:
 *      2+2 = 4
 */
#define LOG_INFO(str, ...) LOG(_MG_LOG_INFO, str, __VA_ARGS__)
#define LOG_UI(str, ...)   LOG(_MG_LOG_UI, str, __VA_ARGS__)
#define LOG_SDL(str, ...)  LOG(_MG_LOG_SDL, str, __VA_ARGS__)
#define LOG_ERROR(str, ...) LOG(_MG_LOG_ERROR, str, __VA_ARGS__)

/** Turn any logging category on/off at any point in the application.
 */
#define LOG_INFO_ON  _MG_log_config[_MG_LOG_INFO] = true
#define LOG_INFO_OFF _MG_log_config[_MG_LOG_INFO] = false
#define LOG_UI_ON  _MG_log_config[_MG_LOG_UI] = true
#define LOG_UI_OFF _MG_log_config[_MG_LOG_UI] = false
#define LOG_SDL_ON  _MG_log_config[_MG_LOG_SDL] = true
#define LOG_SDL_OFF _MG_log_config[_MG_LOG_SDL] = false
#define LOG_ERROR_ON  _MG_log_config[_MG_LOG_ERROR] = true
#define LOG_ERROR_OFF _MG_log_config[_MG_LOG_ERROR] = false



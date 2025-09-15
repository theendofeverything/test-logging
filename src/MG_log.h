#pragma once
/** TODO:
 * Replace log level string with an enum.
 * If log level is ERROR, print to stderr instead of stdout.
 * Make this a log category instead of a log level.
 * Add logic to turn categories on/off
 * (replaces me editing `-D` values in the Makefile)
 */
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
////////////
// INTERNALS
////////////
uint32_t _MG_log_count = 0;

int
_MG_log(
        const char* LOG_LEVEL,
        uint32_t log_count,
        const char* FILE,
        int LINE,
        const char* formatted_str,
        ...)
{
    printf("LOG-%04d: %-8s %s:%d:\n\t", log_count, LOG_LEVEL, FILE, LINE);

    va_list arg;
    int done;

    va_start (arg, formatted_str);
    done = vfprintf(stdout, formatted_str, arg);
    va_end(arg);

    return done;
}

//////////////
// LOGGING API
//////////////
/** Use LOG() instead of printf()
 *
 * Example:
 *
 * ```c
 * int main(void) {
 *     LOG("INFO", "2+2 = %d", 2+2);
 * }
 * ```
 *
 * The above prints the following to stdout:
 * LOG-0001: INFO     src/main.c:7:
 *      2+2 = 4
 */
#define LOG(LEVEL, str, ...) do\
    {\
        _MG_log_count++;\
        _MG_log(LEVEL, _MG_log_count, __FILE__, __LINE__, str, __VA_ARGS__);\
    } while(0)


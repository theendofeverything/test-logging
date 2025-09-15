# About

A simple C logging macro for better `printf` debugging.

Note: SDL already has a logging library. See `SDL_LogMessage()` in `SDL_log.h`.

# Example

Debug 2+2:

```c
#include <stdlib.h>
#include "MG_log.h"
int main(void) {
    LOG("INFO", "2+2 = %d", 2+2);
    return EXIT_SUCCESS;
}
```

The above macro `LOG(...)` expands to:

```c
do {
        _MG_log_count++;
        _MG_log("INFO", _MG_log_count, "src/main.c", 7, "2+2 = %d", 2+2);
    } while(0);
```

And outputs:

```
LOG-0001: INFO     src/main.c:7:
        2+2 = 4
```

# Internals

Private function `_MG_log(...)` is just a copy of the code for `printf` that calls `vfprintf`:

```c
    int
    __printf (const char *format, ...)
    {
      va_list arg;
      int done;

      va_start (arg, format);
      done = vfprintf (stdout, format, arg);
      va_end (arg);

      return done;
    }
```

My logging function just adds a bunch of parameters before `format` that I use
in an initial `printf`. Then I just copy/paste the function body from `printf`
to handle the usual `printf` variable-length parameter list:

```c
int _MG_log(
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
```

The `_MG_log_count` is just to give each logged message a sense of time-ordering.

# Goal

The goal is two-fold:

- Logging categories:
    - Provide categories of logging, e.g., "INFO", "ERROR", "UI", "SDL", etc.,
      to easily turn on/off groups of print statements
- Standard log message formatting:
    - Message prefix:
        - log number, category, file, and line number
    - Message is indented
        - Message indentation is defined in one place


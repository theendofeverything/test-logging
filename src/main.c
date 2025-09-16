#include <stdlib.h>
#include "MG_log.h"


int
main(void)
{
    LOG_INFO("Info");
    LOG_UI("UI thing");
    LOG_SDL("SDL stuff");
    LOG_ERROR("Error");

    LOG_INFO_OFF;
    LOG_UI_OFF;
    LOG_SDL_OFF;
    LOG_ERROR_OFF;
    LOG_INFO("2+2 = %d", 2+2);
    LOG_UI("2+2 = %d", 2+2);
    LOG_SDL("2+2 = %d", 2+2);
    LOG_ERROR("2+2 = %d", 2+2);

    LOG_INFO_ON;
    LOG_UI_ON;
    LOG_SDL_ON;
    LOG_ERROR_ON;
    LOG_INFO("3+3 = %d", 3+3);
    LOG_UI("3+3 = %d", 3+3);
    LOG_SDL("3+3 = %d", 3+3);
    LOG_ERROR("3+3 = %d", 3+3);
    return EXIT_SUCCESS;
}

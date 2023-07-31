#include "core.h"

int main()
{
    /* start rush */
    int status = rush_loop();

    if (status == -1)
        return EXIT_SUCCESS;

    return status;
}

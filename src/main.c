#include <stdio.h>

#include "log.h"

void printing(char *data, uint32_t len)
{
     printf("%s",data);
}

int main(int argc, char const *argv[])
{
    LOG_INIT(printing,LOG_LEVEL_INFO);
    LOG_PRINT(LOG_LEVEL_ERROR, "Starting Logging\r\n");
    LOG_PRINT(LOG_LEVEL_CRITICAL, "Starting Logging\r\n");
    LOG_PRINT(LOG_LEVEL_INFO, "Starting Logging\r\n");
    LOG_PRINT(LOG_LEVEL_WARNING, "Starting Logging\r\n");

    return 0;
}

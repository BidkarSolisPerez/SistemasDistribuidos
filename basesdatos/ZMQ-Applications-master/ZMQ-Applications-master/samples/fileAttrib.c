#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

int main ( int argc, char *argv[])
{
    struct stat FileAttrib;

    if(argc <= 1)
    {
        printf("Argument missing!\n");
        exit(10);
    }

    if (stat(argv[(argc - 1)], &FileAttrib) < 0)
        printf("File Error Message = %s\n", strerror(errno));
    else
        printf( "Mod time: %d\n", FileAttrib.st_mtime );

    return 0;
}

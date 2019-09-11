// hwserver.c
// Hello World server
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client, replies with "World" 
//
#include <zhelpers.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

static void list_dir(const char *path)
{
    struct dirent *entry;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        

        char filename[256];
        struct tm *foo;
        struct stat attrib;


	    sprintf (filename, "%s", entry->d_name);

        if((!strcmp(filename,".")) || (!strcmp(filename,".."))){
            continue;
        }else
        {
            /* code */
            printf("File name: %s\n",filename);
            char directory[256] = "C:\\SistemasDistribuidos\\";

            struct stat attr;
            stat(strcat(directory,filename), &attr);
            printf("Last modified time: %s", ctime(&attr.st_mtime));

            /*
            struct stat t_stat;
            stat(filename, &t_stat);
            struct tm * timeinfo = localtime(&t_stat.st_ctime); // or gmtime() depending on what you want
            printf("File time and date: %s\n", asctime(timeinfo));*/
        }

    }

    closedir(dir);
}

int main(int argc, char *argv[]){

    printf("Hello %s!!\n",argv[1]);
    printf("Hello %s!!\n",argv[2]);


    list_dir("C:\\SistemasDistribuidos");



    getchar();

    return 0;
}
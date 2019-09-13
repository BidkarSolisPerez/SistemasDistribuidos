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

    FILE *fp;
    fp = fopen ( "archivos.txt", "w" );

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

            char directory[256] = "D:\\SistemasDistribuidos\\";
            struct stat attr;
            stat(strcat(directory,filename), &attr);
            printf("Last modified time: %s\n", ctime(&attr.st_mtime));

            
            if(!S_ISDIR(attr.st_mode)){
                printf("Es un archivo\n");
                printf("Preparando para escribir en archivo\n");
	            
                fp = fopen ( "archivos.txt", "a" );        
            
	            if (fp==NULL) {
                    printf("Error al crear o leer el archivo\n");
                }else{
                    printf("Escribiendo...\n\n");
                    fputs(strcat(filename, "\t"),fp);
                    fputs("\n",fp);
                }
            }

            /*
            struct stat t_stat;
            stat(filename, &t_stat);
            struct tm * timeinfo = localtime(&t_stat.st_ctime); // or gmtime() depending on what you want
            printf("File time and date: %s\n", asctime(timeinfo));*/
        }
        fclose ( fp );
    }

    closedir(dir);
}

int main(int argc, char *argv[]){

    printf("Hello %s!!\n",argv[1]);
    printf("Hello %s!!\n",argv[2]);


    list_dir("D:\\SistemasDistribuidos");



    getchar();

    return 0;
}
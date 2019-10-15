#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include "zhelpers.h"

int callback(void *, int, char **, char **);

int main(void)
{

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("profesor.db", &db);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    FILE *prof;

    prof = fopen("prof.json", "w");

    //printf("Escribiendo en archivo\n");
    fprintf(prof, "{\"title\":\"Listado de Profesores\",\"professors\":[");
    fclose(prof);

    char *sql = "SELECT * FROM profesor";
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);
    prof = fopen("prof.json", "a");
    int charsToDelete = 1;
    fseeko(prof, -charsToDelete, SEEK_END);
    int position = ftello(prof);
    ftruncate(fileno(prof), position);
    fprintf(prof, "]}");
    fclose(prof);
    return 0;
}

int callback(void *NotUsed, int argc, char **argv,
             char **azColName)
{
    FILE *prof;
    prof = fopen("prof.json", "a");
    fprintf(prof, "{");
    NotUsed = 0;
    for (int i = 0; i < argc; i++)
    {

        // convert 123 to string [buf]

        if (atoi(argv[i]))
        {
            printf("Is integer\n");
            fprintf(prof, "\"");
            fprintf(prof, azColName[i]);
            fprintf(prof, "\":");
            fprintf(prof, argv[i]);
            fprintf(prof, ",");
        }
        else
        {
            printf("Is string\n");
            fprintf(prof, "\"");
            fprintf(prof, azColName[i]);
            fprintf(prof, "\":");
            fprintf(prof, "\"");
            fprintf(prof, argv[i]);
            fprintf(prof, "\"");
            fprintf(prof, ",");
        }

        printf("%s = %s\n", azColName[i],
               argv[i] ? argv[i] : "NULL");
    }
    int charsToDelete = 1;
    fseeko(prof, -charsToDelete, SEEK_END);
    int position = ftello(prof);
    ftruncate(fileno(prof), position);
    fprintf(prof, "},");
    fclose(prof);
    printf("\n");
    return 0;
}
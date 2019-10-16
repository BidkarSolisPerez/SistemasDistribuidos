<<<<<<< HEAD
#include <sqlite3.h>
#include <stdio.h>
#include <nxjson.h>

char* concatenar(char* str1, char* str2);

int main(void) {

  sqlite3 * db;
  char * err_msg = 0;
  int rc = sqlite3_open("professorsDB.db", & db);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  char* sql;

  FILE * f = fopen("modificar.json", "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET); /* same as rewind(f); */

  char * input = malloc(fsize + 1);
  fread(input, 1, fsize, f);
  fclose(f);

  input[fsize] = 0;

  const nx_json * json = nx_json_parse_utf8(input);
  const nx_json * professors = nx_json_get(json, "professors");  
  nx_json * prof = professors -> child;

  
  for (prof = professors -> child; prof; prof = prof -> next) {
    nx_json * field = prof -> child;
    
    char valor[200]; 
    char* where = " where id=";
    sql = "update Professors set ";

    for (field = prof -> child; field; field = field -> next) {
      if (field -> type == NX_JSON_STRING) {
        
        if (strcmp(field -> key, "name") == 0 || strcmp(field -> key, "email") == 0 || strcmp(field -> key, "degree") == 0) {
          sql = concatenar(sql, (char*)field -> key);
          sql = concatenar(sql, "='");
          sql = concatenar(sql, (char *)field->text_value);
          sql = concatenar(sql, "',");
        }      

      } else if (field -> type == NX_JSON_INTEGER) {
         sprintf(valor, "%d", field->int_value); // Entero -> Char[200]
     
        if (strcmp(field -> key, "phone") != 0) {
          where = concatenar(where, (char *)valor);
        } else {       
          sql = concatenar(sql, (char*)field -> key);
          sql = concatenar(sql, "=");
          sql = concatenar(sql, (char *)valor);
        }
      } else if (field -> type == NX_JSON_DOUBLE) {
         sprintf(valor, "%f", field->dbl_value); // Doble -> Char[200]
         sql = concatenar(sql, (char*)field -> key);
         sql = concatenar(sql, "=");
         sql = concatenar(sql, (char *)valor);
      }

    }
    sql = concatenar(sql, where);

    rc = sqlite3_exec(db, sql, 0, 0, & err_msg);
    if (rc != SQLITE_OK) {
      printf("%s\n\n", stderr);
      printf("%s\n\n", err_msg);
      fprintf(stderr, "SQL error: %s\n", err_msg);
      sqlite3_free(err_msg);
      sqlite3_close(db);
      return 1;
    }  
  }

  sqlite3_close(db);

  printf("------Datos actualizados ---- \n");
  getchar();

  return 0;
}

char* concatenar(char* str1, char* str2)
{
    char* str3 = (char*) malloc(1 + strlen(str1)+ strlen(str2) );
    strcpy(str3, str1);
    strcat(str3, str2);
	return str3;
=======
#include <stdio.h>
#include <stdlib.h>
#include "zhelpers.h"
#include <sqlite3.h>
#include <nxjson.h>

int main()
{
    FILE *f = fopen("data.json", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET); /* same as rewind(f); */

    char *input = malloc(fsize + 1);
    fread(input, 1, fsize, f);
    fclose(f);

    input[fsize] = 0;

    const nx_json *json = nx_json_parse_utf8(input);

    const nx_json *professors = nx_json_get(json, "professors");

    nx_json *prof = professors->child;
    for (prof = professors->child; prof; prof = prof->next)
    {
        nx_json *field = prof->child;
        char statement[100] = "UPDATE profesor Set";
        char *value;
        char id[10];
        for (field = prof->child; field; field = field->next)
        {
            char isID[10];
            sprintf(isID, "%s", field->key);
            if (isID == "id")
            {
                printf("Es el id\n");
                itoa(field->int_value, id, 10);
                continue;
            }
            else
            {
                printf("No es el ID\n");
                if (field->type == NX_JSON_STRING)
                {
                    printf("Es un string\n");
                    printf("%s => %s\n", field->key, field->text_value);
                    sprintf(value, "%s", field->text_value);
                    printf("Value: %s\n", value);
                    strcat(statement, field->key);
                    strcat(statement, "=");
                    strcat(statement, "'");
                    strcat(statement, value);
                    strcat(statement, "'");
                    printf("Statement: %s\n", statement);
                    if (field->next)
                    {
                        strcat(statement, ",");
                    }
                }
                else if (field->type == NX_JSON_INTEGER)
                {
                    printf("Es un int\n");
                    printf("%s => %d\n", field->key, field->int_value);
                    sprintf(value, "%d", field->int_value);
                    printf("Value: %s\n", value);
                    strcat(statement, field->key);
                    strcat(statement, "=");
                    strcat(statement, value);
                    if (field->next)
                    {
                        strcat(statement, ",");
                    }
                }
                else if (field->type == NX_JSON_DOUBLE)
                {
                    printf("Es un double\n");
                    printf("%s => %f\n", field->key, field->dbl_value);
                    sprintf(value, "%f", field->dbl_value);
                    printf("Value: %f\n", value);
                    strcat(statement, field->key);
                    strcat(statement, "=");
                    strcat(statement, value);
                    if (field->next)
                    {
                        strcat(statement, ",");
                    }
                }
            }
        }
        strcat(statement, " where id = ");
        strcat(statement, id);
        strcat(statement, ";");
        printf("%s\n", statement);
        printf("\n");

        //Database
        sqlite3 *db;
        char *err_msg = 0;

        int rc = sqlite3_open("profesor.db", &db);

        rc = sqlite3_exec(db, statement, 0, 0, &err_msg);

        if (rc != SQLITE_OK)
        {
            fprintf(stderr, "SQL error: %s\n", err_msg);
            sqlite3_free(err_msg);
            sqlite3_close(db);
            return 1;
        }

        sqlite3_close(db);
    }

    return 0;
>>>>>>> ede1116a19d470d5048e72fdaa33f169f051b788
}
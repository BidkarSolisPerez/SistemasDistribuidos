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
    char statement[100] = "INSERT INTO profesor VALUES(";
    char *value;
    for (field = prof->child; field; field = field->next)
    {
      if (field->type == NX_JSON_STRING)
      {
        printf("Es un string\n");
        printf("%s => %s\n", field->key, field->text_value);
        sprintf(value, "%s", field->text_value);
        printf("Value: %s\n", value);
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
        strcat(statement, value);
        if (field->next)
        {
          strcat(statement, ",");
        }
      }
    }
    strcat(statement, ");");
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
}
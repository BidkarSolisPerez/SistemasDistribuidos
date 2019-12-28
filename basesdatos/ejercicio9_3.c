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
}
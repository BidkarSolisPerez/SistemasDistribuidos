// wuclient.c
// Weather update client
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds avg temp in zipcode
//
#include <zhelpers.h>
#include <unistd.h>
#include <sqlite3.h>
#include <stdio.h>

int callback(void *, int, char **, char **);

int main(int argc, char *argv[])
{
    void *context = zmq_ctx_new();

    //  Socket to talk to server
    printf("Collecting updates from weather server...\n");

    void *subscriber = zmq_socket(context, ZMQ_SUB);
    int rc = zmq_connect(subscriber, "tcp://localhost:5556");
    //assert (rc == 0);

    char *filter = (argc > 1) ? argv[1] : "";
    rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));

    //Para base de datos
    sqlite3 *db;
    char *err_msg = 0;

    printf("Servidor en espera de la inforamcion para procesar la consulta a la base de datos");
    //  Process 100 updates
    while (1)
    {
        char *string = s_recv(subscriber);

        printf("Valor recibido desde el coordinador: %s\n", string);

        char *requestType = strtok(string, ",");
        printf("Request type: %s\n", requestType);

        char *values = strtok(NULL, ",");
        printf("Valores del query: %s\n", values);

        char *id = strtok(NULL, ",");
        printf("Valor de id: %s\n", id);		

        if (strcmp(requestType, "GET") == 0)
        {
            if (id != NULL)
            {
                printf("Es de tipo get\n");
                int rcdb = sqlite3_open("Test.db", &db);

                printf("Valor rc: %d\n", rcdb);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Cannot open database: %s\n",
                            sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 1;
                }

                char sql[100] = "SELECT * FROM ";
                printf("SQL: %s\n", sql);

                strcat(sql, values);
                strcat(sql, " where id = ");
                strcat(sql, id);

                printf("Statement: %s\n", sql);
                rcdb = sqlite3_exec(db, sql, callback, 0, &err_msg);

                if (rcdb != SQLITE_OK)
                {
                    fprintf(stderr, "Failed to select data\n");
                    fprintf(stderr, "SQL error: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 1;
                }

                sqlite3_close(db);
            }
            else
            {
                printf("Es de tipo get\n");
                int rcdb = sqlite3_open("Test.db", &db);

                printf("Valor rc: %d\n", rcdb);
                if (rc != SQLITE_OK)
                {
                    fprintf(stderr, "Cannot open database: %s\n",
                            sqlite3_errmsg(db));
                    sqlite3_close(db);
                    return 1;
                }

                char sql[100] = "SELECT * FROM ";
                printf("SQL: %s\n", sql);

                strcat(sql, values);

                printf("Statement: %s\n", sql);				
                rcdb = sqlite3_exec(db, sql, callback, 0, &err_msg);

                if (rcdb != SQLITE_OK)
                {
                    fprintf(stderr, "Failed to select data\n");
                    fprintf(stderr, "SQL error: %s\n", err_msg);
                    sqlite3_free(err_msg);
                    sqlite3_close(db);
                    return 1;
                }

                sqlite3_close(db);
            }
        }
        else if (strcmp(requestType, "POST") == 0)
        {
            printf("Es de tipo post\n");			
            int rcdb = sqlite3_open("Test.db", &db);

            printf("Valor rc: %d\n", rcdb);
            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Cannot open database: %s\n",
                        sqlite3_errmsg(db));
                sqlite3_close(db);
                return 1;
            }

            printf("Values: %s\n", values);
            printf("ID: %s\n", id);
            
			char sql[200] = "insert into "; 
			strcat(sql, values);
			strcat(sql, " values (");
            printf("SQL: %s\n", sql);
			/* get the first token */
			if(strcmp(values, "profesor") == 0 || strcmp(values, "escuela") == 0){
				printf("Entre en escuela profesor\n");
				char *end_str;
				char *token = strtok_r(id, "&", &end_str);
				int counterP = 0;
				while (token != NULL)
				{
					char *end_token;
					printf("a = %s %d\n", token, counterP);
					char *token2 = strtok_r(token, "=", &end_token);
					int counterV = 0;
					while (token2 != NULL)
					{
						if (counterV == 1){
							printf("Values = %s\n", token2);						
							if(counterP == 0)
								strcat(sql, token2);
							else{
								token2 += 3;			
								int length = strlen(token2);//Get length of string
								token2[length - 1] = '\0';
								token2[length - 2] = '\0';
								token2[length - 3] = '\0';							
								printf("Values new = %s\n", token2);	
								strcat(sql, ",'");	
								strcat(sql, token2);
								strcat(sql, "'");							
							}
						}
						token2 = strtok_r(NULL, "=", &end_token);
						counterV = counterV == 1 ? 0 : counterV + 1;
					}
					token = strtok_r(NULL, "&", &end_str);
					counterP = counterP +1; 
					free(end_token);
				}
				free(end_str);
				free(token);
			}
			else if(strcmp(values, "estudiante") == 0){
				printf("Entre en estudiante\n");
				char *end_str;
				char *token = strtok_r(id, "&", &end_str);
				int counterP = 0;
				while (token != NULL)
				{
					char *end_token;
					printf("a = %s %d\n", token, counterP);
					char *token2 = strtok_r(token, "=", &end_token);
					int counterV = 0;
					while (token2 != NULL)
					{
						if (counterV == 1){
							printf("Values = %s\n", token2);						
							if(counterP == 0 || counterP == 2 )
								if (counterP == 0) 
									strcat(sql, token2);
								else {
									strcat(sql, ",");
									strcat(sql, token2);									
								}
							else{
								token2 += 3;			
								int length = strlen(token2);//Get length of string
								token2[length - 1] = '\0';
								token2[length - 2] = '\0';
								token2[length - 3] = '\0';							
								printf("Values new = %s\n", token2);	
								strcat(sql, ",'");	
								strcat(sql, token2);
								strcat(sql, "'");							
							}
						}
						token2 = strtok_r(NULL, "=", &end_token);
						counterV = counterV == 1 ? 0 : counterV + 1;
					}
					token = strtok_r(NULL, "&", &end_str);
					counterP = counterP +1; 
					free(end_token);
				}
				free(end_str);
				free(token);
			}
			else if(strcmp(values, "curso") == 0){
				printf("Entre en curso\n");
				char *end_str;
				char *token = strtok_r(id, "&", &end_str);
				int counterP = 0;
				while (token != NULL)
				{
					char *end_token;
					printf("a = %s %d\n", token, counterP);
					char *token2 = strtok_r(token, "=", &end_token);
					int counterV = 0;
					while (token2 != NULL)
					{
						if (counterV == 1){
							printf("Values = %s\n", token2);						
							if(counterP == 0 || counterP == 3 || counterP == 4){
								if (counterP == 0) 
									strcat(sql, token2);
								else {
									strcat(sql, ",");
									strcat(sql, token2);									
								}
									
							}
							else{
								token2 += 3;			
								int length = strlen(token2);//Get length of string
								token2[length - 1] = '\0';
								token2[length - 2] = '\0';
								token2[length - 3] = '\0';							
								printf("Values new = %s\n", token2);	
								strcat(sql, ",'");	
								strcat(sql, token2);
								strcat(sql, "'");							
							}
						}
						token2 = strtok_r(NULL, "=", &end_token);
						counterV = counterV == 1 ? 0 : counterV + 1;
					}
					token = strtok_r(NULL, "&", &end_str);
					counterP = counterP +1; 
					free(end_token);
				}
				free(end_str);
				free(token);
			}
			
			 
			strcat(sql, ")");           
            printf("Statement: %s\n", sql);
            rcdb = sqlite3_exec(db, sql, 0, 0, &err_msg);

            if (rcdb != SQLITE_OK)
            {
                fprintf(stderr, "Failed to select data\n");
                fprintf(stderr, "SQL error: %s\n", err_msg);
				getchar();
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 1;
            }

            printf("Registro insertado\n");
            sqlite3_close(db);
        }
        else if (strcmp(requestType, "PUT") == 0)
        {
            printf("Es de tipo put\n");			
            int rcdb = sqlite3_open("Test.db", &db);

            printf("Valor rc: %d\n", rcdb);
            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Cannot open database: %s\n",
                        sqlite3_errmsg(db));
                sqlite3_close(db);
                return 1;
            }

            printf("Values: %s\n", values);
            printf("ID: %s\n", id);

            char sql[200] = "update "; 
			strcat(sql, values);
			strcat(sql, " set ");
            printf("SQL: %s\n", sql);
			char * whereID = "";
			/* get the first token */
			if(strcmp(values, "profesor") == 0 || strcmp(values, "escuela") == 0){		
				printf("Entre en profesor escuela\n");
				char *end_str;
				char *token = strtok_r(id, "&", &end_str);
				int counterP = 0;
				while (token != NULL)
				{
					char *end_token;
					printf("a = %s %d\n", token, counterP);
					char *token2 = strtok_r(token, "=", &end_token);
					int counterV = 0;
					while (token2 != NULL)
					{
						if (counterV == 1){
							printf("Values = %s\n", token2);						
							if(counterP == 0)								
								whereID = token2;
							else{
								token2 += 3;			
								int length = strlen(token2);//Get length of string
								token2[length - 1] = '\0';
								token2[length - 2] = '\0';
								token2[length - 3] = '\0';							
								printf("Values new = %s\n", token2);	
								strcat(sql, "'");
								strcat(sql, token2);
								strcat(sql, "'");
								if (strcmp(values, "profesor") == 0 )
									if(counterP != 4)
										strcat(sql, ",");
								if (strcmp(values, "escuela") == 0 )
									if(counterP != 3)
										strcat(sql, ",");
							}
						}
						else{
							if(counterP != 0){
								strcat(sql, token2);
								strcat(sql, "=");
							}
						}				
						token2 = strtok_r(NULL, "=", &end_token);
						counterV = counterV == 1 ? 0 : counterV + 1;
					}
					token = strtok_r(NULL, "&", &end_str);
					counterP = counterP +1; 
					free(end_token);
				}
				free(end_str);
				free(token);
			}
			else if(strcmp(values, "estudiante") == 0){
				printf("Entre en estudiante\n");
				char *end_str;
				char *token = strtok_r(id, "&", &end_str);
				int counterP = 0;
				while (token != NULL)
				{
					char *end_token;
					printf("a = %s %d\n", token, counterP);
					char *token2 = strtok_r(token, "=", &end_token);
					int counterV = 0;
					while (token2 != NULL)
					{
						if (counterV == 1){
							printf("Values = %s\n", token2);						
							if(counterP == 0 || counterP == 2 )
								if (counterP == 0) 
									whereID = token2;
								else {									
									strcat(sql, token2);									
									strcat(sql, ",");
								}
							else{
								token2 += 3;			
								int length = strlen(token2);//Get length of string
								token2[length - 1] = '\0';
								token2[length - 2] = '\0';
								token2[length - 3] = '\0';							
								printf("Values new = %s\n", token2);	
								strcat(sql, "'");	
								strcat(sql, token2);
								strcat(sql, "'");
								if(counterP != 4)strcat(sql, ",");							
							}
						}
						else{
							if(counterP != 0){
								strcat(sql, token2);
								strcat(sql, "=");
							}
						}	
						token2 = strtok_r(NULL, "=", &end_token);
						counterV = counterV == 1 ? 0 : counterV + 1;
					}
					token = strtok_r(NULL, "&", &end_str);
					counterP = counterP +1; 
					free(end_token);
				}
				free(end_str);
				free(token);
			}
			else if(strcmp(values, "curso") == 0){
				printf("Entre en curso\n");
				char *end_str;
				char *token = strtok_r(id, "&", &end_str);
				int counterP = 0;
				while (token != NULL)
				{
					char *end_token;
					printf("a = %s %d\n", token, counterP);
					char *token2 = strtok_r(token, "=", &end_token);
					int counterV = 0;
					while (token2 != NULL)
					{
						if (counterV == 1){
							printf("Values = %s\n", token2);						
							if(counterP == 0 || counterP == 3 || counterP == 4){
								if (counterP == 0) 
									whereID = token2;
								else {									
									strcat(sql, token2);									
									if(counterP != 4)strcat(sql, ",");
								}
									
							}
							else{
								token2 += 3;			
								int length = strlen(token2);//Get length of string
								token2[length - 1] = '\0';
								token2[length - 2] = '\0';
								token2[length - 3] = '\0';							
								printf("Values new = %s\n", token2);	
								strcat(sql, "'");	
								strcat(sql, token2);
								strcat(sql, "'");
								if(counterP != 4)strcat(sql, ",");							
							}
						}
						else{
							if(counterP != 0){
								strcat(sql, token2);
								strcat(sql, "=");
							}
						}	
						token2 = strtok_r(NULL, "=", &end_token);
						counterV = counterV == 1 ? 0 : counterV + 1;
					}
					token = strtok_r(NULL, "&", &end_str);
					counterP = counterP +1; 
					free(end_token);
				}
				free(end_str);
				free(token);
			}
			
			 
			if (strcmp(values, "profesor") == 0) 
				strcat(sql, " where id = ");
			else if (strcmp(values, "curso") == 0) 
				strcat(sql, " where id_curso = ");
			else if (strcmp(values, "escuela") == 0) 
				strcat(sql, " where id_escuela = ");
			else if (strcmp(values, "estudiante") == 0) 
				strcat(sql, " where id_estudiante = ");
			strcat(sql, whereID);
            printf("Statement: %s\n", sql);
            rcdb = sqlite3_exec(db, sql, 0, 0, &err_msg);

            if (rcdb != SQLITE_OK)
            {
                fprintf(stderr, "Failed to select data\n");
                fprintf(stderr, "SQL error: %s\n", err_msg);
				getchar();
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 1;
            }

            printf("Registro actualizado\n");
            sqlite3_close(db);
        }
        else if (strcmp(requestType, "DELETE") == 0)
        {
            printf("Es de tipo delete\n");
            int rcdb = sqlite3_open("Test.db", &db);

            printf("Valor rc: %d\n", rcdb);
            if (rc != SQLITE_OK)
            {
                fprintf(stderr, "Cannot open database: %s\n",
                        sqlite3_errmsg(db));
                sqlite3_close(db);
                return 1;
            }

            printf("Values: %s\n", values);
            printf("ID: %s\n", id);

            char sql[100] = "DELETE FROM ";
            printf("SQL: %s\n", sql);

            strcat(sql, values);

            printf("SQL: %s\n", sql);

            strcat(sql, " where id = ");

            printf("SQL: %s\n", sql);

            strcat(sql, id);

            printf("SQL: %s\n", sql);
            printf("Statement: %s\n", sql);
            rcdb = sqlite3_exec(db, sql, 0, 0, &err_msg);

            if (rcdb != SQLITE_OK)
            {
                fprintf(stderr, "Failed to select data\n");
                fprintf(stderr, "SQL error: %s\n", err_msg);
                sqlite3_free(err_msg);
                sqlite3_close(db);
                return 1;
            }

            printf("Registro eliminado\n");
            sqlite3_close(db);
        }
        else
        {
            printf("Request desconocido\n");
        }

        free(string);
    }
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    getchar();
    return 0;
}

int callback(void *NotUsed, int argc, char **argv,
             char **azColName)
{
    printf("Ingreso al callback\n");
    NotUsed = 0;
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i],
               argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}
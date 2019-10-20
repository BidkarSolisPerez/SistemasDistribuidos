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
                int rcdb = sqlite3_open("Test2.db", &db);

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
                int rcdb = sqlite3_open("Test2.db", &db);

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
        }
        else if (strcmp(requestType, "PUT") == 0)
        {
            printf("Es de tipo put\n");
        }
        else if (strcmp(requestType, "DELETE") == 0)
        {
            printf("Es de tipo delete\n");
            int rcdb = sqlite3_open("Test2.db", &db);

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
#include <string.h>
#include <stdio.h>

int main(void)
{
    char str[] = "a;b;c;d;e\nf;g;h;i;j\n1;2;3;4;5\n";
    char *end_str;
    char *token = strtok_r(str, "\n", &end_str);

    while (token != NULL)
    {
        char *end_token;
        printf("a = %s\n", token);
        char *token2 = strtok_r(token, ";", &end_token);
        while (token2 != NULL)
        {
            printf("b = %s\n", token2);
            token2 = strtok_r(NULL, ";", &end_token);
        }
        token = strtok_r(NULL, "\n", &end_str);
    }
	getchar();
    return 0;
}
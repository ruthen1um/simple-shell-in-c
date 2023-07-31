#include "core.h"
#include "builtin.h"

#define LEN(x) (sizeof(x) / sizeof(*x))

#define MAXINPUTBUFFER 1024
#define MAXTOKENBUFFER 256

int rush_loop()
{
    char *input_buffer;
    char **token_buffer;

    /*
    * There are three possible cases of the status variable:
    *
    *  status == -1: shell must terminate with successful exit code
    *  status == 0: shell loop must continue
    *  status in range 1 - 256: shell must terminate with specified exit code
    *
    */

    int status = 0;

    do
    {
        input_buffer = (char *)malloc(sizeof(char) * MAXINPUTBUFFER);
        token_buffer = (char **)malloc(sizeof(char *) * MAXTOKENBUFFER);

        if ((input_buffer == NULL) || (token_buffer == NULL))
        {
            fprintf(stderr, "%s at line %d: couldn't allocate memory", __FILE__, __LINE__);
            return EXIT_FAILURE;
        }

        print_prompt();
        read_input(input_buffer, MAXINPUTBUFFER);
        tokenize(input_buffer, token_buffer, MAXTOKENBUFFER);
        status = parse(token_buffer);

        free(input_buffer);
        free(token_buffer);

        if (status == -1)
            return 0;

        if (status < -1 && status > 255)
        {
            fprintf(stderr, "%s at line %d: bad status code", __FILE__, __LINE__);
            return 1;
        }

    } while (!status);

    return 0;
}

void print_prompt()
{
    fputs("> ", stdout);
}

void read_input(char *buffer, int size)
{
    /* fgets() reads (size - 1) characters and adds '\0' character at the end of the string */
    fgets(buffer, size, stdin);
}

void tokenize(char *buffer, char *token_buffer[], int size)
{
    int p = 0;
    char delims[] = " \t\n\v\f\r";

    token_buffer[p] = strtok(buffer, delims);

    while (token_buffer[p] != NULL)
    {
        token_buffer[++p] = strtok(NULL, delims);

        /* add NULL at the end if there are more tokens than (size) */
        if (p >= size)
        {
            token_buffer[p - 1] = NULL;
            return;
        }
    }

    token_buffer[p] = NULL;
}

int parse(char *token_buffer[])
{
    if (token_buffer[0] == NULL)
        return 0;

    for (int i = 0; i < LEN(token_buffer); i++)
    {
        if ((strcmp(token_buffer[0], rush_builtins[i].name)) == 0)
            return rush_builtins[i].func(token_buffer + 1);
    }

    fprintf(stderr, "%s: command not found\n", token_buffer[0]);
    return 0;
}

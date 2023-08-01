#include "core.h"
#include "builtin.h"

#define LEN(x) (sizeof(x) / sizeof(*x))

#define MAXLINEBUFFER 1024
#define MAXTOKENBUFFER 256
#define TOKENDELIM " \t"

void rush_prompt()
{
    fputs("> ", stdout);
}

char *rush_read_line()
{
    char *line_buffer = malloc(sizeof(char) * MAXLINEBUFFER);

    if (line_buffer == NULL)
    {
        fprintf(stderr, "%s at line %d: couldn't allocate line_buffer", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }


    fgets(line_buffer, MAXLINEBUFFER, stdin);

    char c;

    /*
        *) if there is no '\n' character in line_buffer, it means that more characters than MAXLINEBUFFER were entered,
        so we need to erase characters left after fgets()

        *) if there is a '\n' character, we do not want to include it in line_buffer
    */

    if (strchr(line_buffer, '\n') == NULL)
        while ((c = getc(stdin)) != '\n' && c != EOF);
    else
        line_buffer[strcspn(line_buffer, "\n")] = 0;

    return line_buffer;
}

char **rush_tokenize(char *line)
{
    char **token_buffer = malloc(sizeof(char *) * MAXTOKENBUFFER);

    if (token_buffer == NULL)
    {
        fprintf(stderr, "%s at line %d: couldn't allocate token_buffer", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }

    int p = 0;

    token_buffer[p] = strtok(line, TOKENDELIM);

    if (token_buffer[p] == NULL)
        return token_buffer;

    p++;

    char *token;

    while (1)
    {
        token = strtok(NULL, TOKENDELIM);

        if (token == NULL && p < MAXTOKENBUFFER)
        {
            token_buffer[p] = token;
            break;
        }

        if (p == MAXTOKENBUFFER)
        {
            token_buffer[MAXTOKENBUFFER - 1] = NULL;
            break;
        }

        token_buffer[p++] = token;
    }

    return token_buffer;
}

int rush_execute(char **tokens)
{
    if (tokens[0] == NULL)
        return 0;

    for (int i = 0; i < LEN(tokens); i++)
    {
        if ((strcmp(tokens[0], rush_builtins[i].name)) == 0)
            return rush_builtins[i].func(tokens + 1);
    }

    fprintf(stderr, "rush: %s: command not found\n", tokens[0]);

    return 0;
}

void rush_loop()
{
    char *line;
    char **tokens;

    int status;

    /* keep executing loop while status = 0 */
    do {
        rush_prompt();
        line = rush_read_line();
        tokens = rush_tokenize(line);
        status = rush_execute(tokens);

        free(line);
        free(tokens);

    } while (!status);
}

#include <stdio.h>

typedef enum
{
    ERROR_NOFILE = 10,
    ERROR_FILE_INVALID_OR_NOT_FOUND
} CAT_ERRORS;

int main(int argc, char const *argv[])
{
    if (argc <= 1)
    {
        fprintf(stderr, "No input file specified!\n");
        return ERROR_NOFILE;
    }

    FILE *f = NULL;
    for (size_t i = 0; i < argc; i++)
    {
        f = fopen(argv[i], "r");

        if (!f)
        {
            fprintf(stderr, "Could not open file: %s\n", argv[i]);
            return ERROR_FILE_INVALID_OR_NOT_FOUND;
        }

        fprintf(stdout, "-- %s --\n", argv[i]);

        char c;
        while ((c = fgetc(f)) != EOF)
        {
            fprintf(stdout, "%c", c);
        }

        fprintf(stdout, "\n");
    }

    return 0;
}

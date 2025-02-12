#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc <= 1)
        fprintf(stderr, "Not enough arguments specified!\nUse -h for help!\n");

    if (argv[1][0] == '-')
    {

        char command[64];
        size_t i = 0;
        while (argv[1][i] == '-')
        {
            i++;
        }

        sprintf(command, "%s", argv[1] + i);

        if (strncmp(command, "h", 1) == 0)
        {
            printf("-h | Display help\n-ws <file> <string> |  overwrites contents and writes string to file\n");
            return 0;
        }
        else if (strncmp(command, "ws", 1) == 0)
        {
            if (argc < 3)
            {
                fprintf(stderr, "No string given to write to file!\n");
                return -1;
            }

            FILE *f = fopen(argv[2], "w");
            if (!f)
            {
                fprintf(stderr, "Could not create \"%s\"!\n", argv[2]);
                return -1;
            }

            fwrite(argv[3], strlen(argv[3]), 1, f);
            fclose(f);
            return 0;
        }
    }

    FILE *f = fopen(argv[1], "w");
    if (!f)
    {
        fprintf(stderr, "Could not create \"%s\"!\n", argv[1]);
        return -1;
    }
    fclose(f);
    return 0;
}

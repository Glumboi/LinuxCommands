#include <stdio.h>

int main(int argc, char const *argv[])
{
    if (argc <= 1)
    {
        fprintf(stderr, "No file/s for removal specified!\n");
        return -1;
    }

    for (size_t i = 1; i < argc; i++)
    {
        if (remove(argv[i]) == 0)
        {
            fprintf(stdout, "Deleted file: %s\n", argv[i]);
            continue;
        }

        fprintf(stderr, "Failed to delete file: %s\n", argv[i]);
    }

    return 0;
}

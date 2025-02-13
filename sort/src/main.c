#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LINE_BUFFER 10 // default amounts of lines
#define DEFAULT_LINE_LEN 64    // default buffer size for a line in a file

typedef struct
{
    char **arr;
    size_t len;
} __sortInfo;

int compareStrings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

__sortInfo sortContents(char *file)
{
    if (!file)
    {
        fprintf(stderr, "File null pointer\n");
        return (__sortInfo){0};
    }

    __sortInfo result = {0};

    FILE *f = fopen(file, "r");
    if (!f)
    {
        fprintf(stderr, "Failed to open file: %s\n", file);
        return result;
    }

    char line[DEFAULT_LINE_LEN];
    char **lines = malloc(DEFAULT_LINE_BUFFER * sizeof(char *));
    if (!lines)
    {
        fclose(f);
        return result;
    }

    size_t lineCount = 0;
    size_t bufferSize = DEFAULT_LINE_BUFFER;

    while (fgets(line, DEFAULT_LINE_LEN, f))
    {
        if (lineCount >= bufferSize)
        {
            size_t newSize = bufferSize + DEFAULT_LINE_BUFFER;
            char **tempLines = realloc(lines, newSize * sizeof(char *));
            if (!tempLines)
            {
                fclose(f);
                free(lines);
                return result;
            }
            lines = tempLines;
            bufferSize = newSize;
        }

        lines[lineCount] = malloc(strlen(line) + 1); // Allocate memory for each line
        if (!lines[lineCount])
        {
            fclose(f);
            for (size_t i = 0; i < lineCount; i++)
                free(lines[i]);
            free(lines);
            return result;
        }

        strcpy(lines[lineCount], line);
        lineCount++;
    }

    fclose(f);

    result.len = lineCount;
    result.arr = lines;
    qsort(result.arr, result.len, sizeof(char *), compareStrings);
    return result;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        fprintf(stderr, "No file/s for sorting specified!\n");
        return -1;
    }

    for (size_t i = 1; i < argc; i++)
    {
        __sortInfo inf = sortContents(argv[i]);

        if (inf.len == 0)
        {
            fprintf(stderr, "Error processing file!\n");
            return -1;
        }

        for (size_t i = 0; i < inf.len; i++)
        {
            fprintf(stdout, "%s", inf.arr[i]);
        }

        free(inf.arr);
        inf.arr = NULL;
        inf.len = 0;
    }

    return 0;
}

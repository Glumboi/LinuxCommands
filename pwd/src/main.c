#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    char dir[260];
    sprintf(dir, "%s", argv[0] + 9);
    dir[0] = toupper(dir[1]); 
    dir[1] = ':'; 
    dir[2] = '/'; 
    printf("%s\n", dir);
    
    return 0;
}

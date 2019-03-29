#include <string.h>
#include "../any_modules.c"

// biteral

int main(void) {
    char* no = "anyName() : void - /anyAddr";

    if (strcmp(getDataStream(no, Part_2), "нет") != 0)
        printf("%s\n", "1 \"not\" failed");


    no = "anyName(void) : void - /anyAddr";
    if (strcmp(getDataStream(no, Part_2), "нет") != 0)
        printf("%s\n", "2 \"not\" failed");


    no = "anyName( void) : void - /anyAddr";
    if (strcmp(getDataStream(no, Part_2), "нет") != 0)
        printf("%s\n", "3 \"not\" failed");


    no = "anyName(void ) : void - /anyAddr";
    if (strcmp(getDataStream(no, Part_2), "нет") != 0)
        printf("%s\n", "4 \"not\" failed");


    no = "anyName( void ) : void - /anyAddr";
    if (strcmp(getDataStream(no, Part_2), "нет") != 0)
        printf("%s\n", "5 \"not\" failed");


    return 0;
}

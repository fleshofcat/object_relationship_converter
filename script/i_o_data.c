#ifndef I_O_DATA_C
#define I_O_DATA_C

#include<stdio.h>
#include<string.h>

#include"global_data.h"

char* getDataFromFile(char*);

char * formattingSheet();
int putInFile(char* in, char* fileName);


char* getDataFromFile(char* fileName) {
    FILE *iFile = fopen(fileName,"r"); // "config_c_tst";

    if (iFile == NULL) {
        printf("%s", "Error: File not opened.\n");
        return NULL;
    }

    fseek(iFile, 0, SEEK_END);
    int size = ftell(iFile);
    rewind(iFile);

    char* buffOut = (char*)malloc(size);
    fread(buffOut, 1, size, iFile);
    fclose(iFile);
    return strdup(buffOut);
}

char * formattingSheet() { //  оптимизировать
    char * test = malloc((LINES*COLUMNS*sizeof(int)) + (LINES*COLUMNS*2));
    for (int l = 0; l < LINES; l++) {
        for (int c = 0; c < COLUMNS; c++) {
            strcat(test, "\"");
            strcat(test, readySheet[l][c]);
            strcat(test, "\"");
            strcat(test, ",");
        }
    strcat(test, "\n");
    }
    return strdup(test);
}



int putInFile(char* in, char* fileName) {
    FILE *oFile = fopen(fileName,"w");

    if (oFile == NULL) {
        printf("%s", "Error: File not opened.\n");
        return -1;
    }

    fwrite(in, 1, strlen(in), oFile);
    fclose(oFile);
    return 0;
}



#endif // I_O_DATA_C

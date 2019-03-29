#ifndef HANDLING_C
#define HANDLING_C

/*
 * handling - функциональная группа
 */

#include <string.h>
#include "global_data.h"
#include "i_o_data.c"
#include "any_modules.c"

char * handleFile_out(char* allData);
char * handleModule_out(char*);
char * handleParts_out(char*, int);
char * handleString_out(char*, int);


char * handleFile_out(char* fileName) { // file
    char* fileData = getDataFromFile(fileName);
    strcat(fileData, "\n"); // FIXME - без "\n" в конце документа все крешится (invalid pointer:..)
    /* ... */

    char* modData = strdup(fileData);    // ... equal Data module
    handleModule_out(modData);
    putInFile(formattingSheet(), "outSheet.csv");
    return "";
}


                // здесь определяется вывод ----
char * handleModule_out(char* in) { // module
    char* part_1 = strdup(in);  // Contains a list of modules that call this module
    char* part_2;               // Contains a list of modules that this module calls

    HANDLE_MODULE_TYPE = handleString_out(in, GET_TYPE);
    HANDLE_MODULE_NAME = handleString_out(in, GET_NAME);

/*
 * part_2 is determined by "\n"+"HANDLE_MODULE_NAME"
 *
 * If you look for "HANDLE_MODULE_NAME" will respond to substrings
 */
    char buff[500] = "\n";                                              // seek second entrance HANDLE_MODULE_NAME
    if (strlen(HANDLE_MODULE_NAME) >= sizeof(buff)) {
        printf("%s\n\n", "HANDLE_MODULE_NAME more than 100 chars");
        return NULL;
    }

    part_2 = strstr(part_1 + 1, strcat(buff, HANDLE_MODULE_NAME));      // part_1 & part_2 use the common space
    if (part_2 != NULL) {
//        part_2[-1] = '\0';
        *part_2++ = '\0';
    } else {
        printf("%s\n\n", "wrong defined first funcName");
        return NULL;
    }


    handleParts_out(structuringPartData(part_1), Part_1);
    handleParts_out(structuringPartData(part_2), Part_2);
    return "";
}


char * handleParts_out(char* dataPart, int numPart) { // parts
    char* block = strdup(dataPart);
    char* oneString = strtok(block, "\n");

    int c = 0;
    int dataStreamFlag;
    if (numPart == Part_1) {
        c = 2;
        dataStreamFlag = GET_DATA_STREAM;
    } else if (numPart == Part_2) {
        c = 8;
        dataStreamFlag = -GET_DATA_STREAM; // GET_DATA_STREAM * (-1)
    } else {
        printf("%s\n", "Err: incorrect Part_* number");
        return "Err: incorrect part_* number";
    }

    oneString = strtok(NULL, "\n");

    for (int l = 0 ; oneString != NULL; l++) {
        readySheet[l][c] = handleString_out(oneString, GET_TYPE);
        readySheet[l][c+1] = handleString_out(oneString, GET_NAME);
        readySheet[l][c+2] = handleString_out(oneString, GET_ADDR);
        readySheet[l][c+3] = handleString_out(oneString, dataStreamFlag);
        readySheet[l][c+4] = handleString_out(oneString, GET_CONTROL_STREAM);
//        printf("%s\n", readySheet[l][c+2]);

        if (oneString[strlen(oneString) + 1] == '\n') oneString = "\n"; // костыль
        else  oneString = strtok(NULL, "\n");

        if (l > LINES) return "Err: Overflow lines in handleParts_out()\n";
    }



    return "handleString() end";
}





char * handleString_out(char* str, int api) { // strings
    switch (api) {

    case GET_TYPE:
    return strdup(getType(str));
        break;

    case GET_NAME:
        return strdup(getName(str));
        break;

    case GET_ADDR:
        return strdup(getAddr(str));
        break;

    case GET_DATA_STREAM:
        return strdup(getDataStream(str, Part_1));
        break;

    case -GET_DATA_STREAM:
        return strdup(getDataStream(str, Part_2));
        break;

    case GET_CONTROL_STREAM:
        return strdup(getControlStream(str));
        break;

    default:
        return "default in handleString_out";
        break;
    }

    return str;
}




#endif // HANDLING_C




















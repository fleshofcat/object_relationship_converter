#include "main.h"
#include "i_o_data.c"
#include "handling.c"

#include <string.h>

void printSheet();

int main(int argc, char* argv[]) {

    for (int l = 0; l < LINES; l++)
        for (int c = 0; c < COLUMNS; c++)
            readySheet[l][c] = "";

    argv[1] = "config_c_tst";

//    printf("%s\n", handleFile_out(argv[1]/*"config_c_tst"*/, atoi(argv[2]))); // Data distribution between table variables
    handleFile_out(argv[1]);


    return 0;
}

void printSheet() {
        for (int l = 0; l < LINES; l++) { // print readySheet
            for (int c = 0; c < COLUMNS; c++) {
                printf("%s\t",  readySheet[l][c]);
            }
            printf("%s\n", "");
        }
}

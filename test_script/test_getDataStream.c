#include <stdio.h>
#include <string.h>
#include "../script/global_data.h"

int test_getDataStream_uni(char* type, char* param, char* tst_word, int partN);


int test_getDataStream() {
//    char* tst_word;
int res = 0;
    res += test_getDataStream_uni("void", "void", "нет", Part_2);
    res += test_getDataStream_uni("void", "int", "прямой", Part_2);
    res += test_getDataStream_uni("int", "void", "обратный", Part_2);
    res += test_getDataStream_uni("int", "int", "двусторонний", Part_2);
    return res;
}


int test_getDataStream_uni(char* type, char* param, char* tst_word, int partN) {
#define P_ONE "anyName("
#define P_SECONG ") : "
#define P_THIRD " - /anyAddr"

    char str[1000] = P_ONE;

    strcat(str, param);
    strcat(str, P_SECONG);
    strcat(str, type);
    strcat(str, P_THIRD);

    if (strcmp(getDataStream(str, partN), tst_word) != 0){
        printf("%s%s%s\n", "1 \"", tst_word, "\" failed");
        return -1;
    }
    return 0;

#undef P_ONE
#undef P_SECONG
#undef P_THIRD
}



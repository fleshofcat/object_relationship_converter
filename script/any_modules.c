#ifndef ANY_MODULES_C
#define ANY_MODULES_C

#include "any_modules.h"

char * structuringPartData(char*);
char * getString(char*);
char * getType(char*);
char * getName(char*);
char * getAddr(char*);
char * getDataStream(char*, int);
char * getControlStream(char*);
char * getFixedParam(char*);
int determineKind(char*);



char * structuringPartData(char* partDat) { // FIXME
    int sizeInput = strlen(partDat);
    char* listFunc = (char*)malloc(strlen(partDat));
    listFunc[0] = '\0';
    char* listData = (char*)malloc(strlen(partDat));
    listData[0] = '\0';

    for (int i = 0; i < sizeInput; i += (strlen(getString(partDat + i)))) {
        int checkResult = determineKind(getString(partDat + i));

        switch (checkResult) {
        case Kind_func:
            strcat(listFunc, getString(partDat + i));
            break;

        case Kind_data:
            strcat(listData, getString(partDat + i));
            break;

        default:    // "while" ended
            goto out;
            break;
        }
    }
out:
    strcat(listFunc, "\n\n");
    strcat(listFunc, listData);
    return strdup(listFunc);
}


char * getString(char* in) {
    int inSize = strlen(in);
    char* out = strdup(in);
    for (int i = 1; i < inSize; i++) {
        if (in[i] == '\n') {
            out[i+1] = '\0';
            return strdup(out);
        }
    }
    return strdup(out);
}

/*
 * take string
 * return type from handling string
 *  Not from function !!!
 */
char * getType_p(char* in) {
    int inSize = strlen(in);

    for (int i = 0; i < inSize; i++) {
        if (in[i] == ' ' && in[i+1] == ':') {
            char* out = strdup(in + (i+=3));
            inSize -= i;
            for (int q = 0; q <= inSize; q++) {
                if ((out[q] == ' ' && out[q+1] == '-') || strchr("\n(", out[q])) {
                    if (out[q-1] == ' ') q--;
                    out[q] = '\0';
                    return strdup(out);
                }
            }
        }
        if (in[i] == '\n') break;
    }
    return "";
}

char * getType(char* in) {
    char* out = strdup(in);
    out += 3;

    while (!(out[-3] == ' ' && out[-2] == ':') ) {
        if (*out == '\0' || *out-3 == '\0') return "";
        out++;
    }

    char* tail = out;
    while (!(tail[0] == ' ' && tail[1] == '-') && !(strchr("\n(", tail[0])))
        tail++;
    tail[0] = '\0';
    return out;
}





char * getAddr(char* in) {
    char* out = strdup(in);
    out += 3;
    while (!(out[-3] == ' ' && out[-2] == '-')) {
        if (*out == '\0' || *out-3 == '\0') return "";
        out++;
    }

    char* tail = out;
    while (!(strchr(" ", tail[0])) || (tail[-1] == '\\' && tail[0] == ' ')) tail++;
    tail[0] = '\0';
    return strdup(out);
}


char * getName(char* str) {
    char* out = strdup(str);
    while (strchr(" \t", *out)) out++; // out = first symbol of string
    char* tail = out;

    for (int i = strlen(str); i > 0; i--) {
        while ( !( *tail == ' ' && (strchr(":-(", tail[1])) )  &&  !strchr("\n", *tail))
            tail++;
        tail[0] = '\0';
        return strdup(out);
    }
    return "";
}

/*
 * take string & part number
 * return rus designation
 */
char * getDataStream(char* in, int partNum) {
    char* loc_tst = in;
    while (strchr(" \t\n", *loc_tst)) {
        if (*loc_tst == '\0')
            return "";
        loc_tst++;
    }

    if (strcmp(in, "") == 0)
        return "";

    char* param;
    char* type;
    if (partNum == Part_1) { // спросить, что делать, если функцию вызывают данные(как данные)
        param = getFixedParam(HANDLE_MODULE_NAME);
        type = strdup(HANDLE_MODULE_TYPE);
    } else {
        if (determineKind(in) == Kind_data) // Weed out the data strings
            return "двусторонний";

//        char* str = strdup(in);
        param = getFixedParam(getName(in));
        type = getType(in);
    }

    if ((strcmp(type, "void") == 0) && (strcmp(param, "void") == 0))
        return "нет";

    if ((strcmp(type, "void") == 0) && !(strcmp(param, "void") == 0))
        return "прямой";

    if (!(strcmp(type, "void") == 0) && (strcmp(param, "void") == 0))
        return "обратный";

    if (!(strcmp(type, "void") == 0) && !(strcmp(param, "void") == 0))
        return "двусторонний";

    printf("%s\n\n", "Err: Attain the end in getDataStream()");
    return "";
}


char * getControlStream(char* in) {
    while (strchr(" \t\n", *in) && (*in != '\0')) in++;
//        if (*in == '\0')
//            return "";

    int check = determineKind(in);
    if (check == Kind_func)
        return "+";
    else if (check == Kind_data)
        return "-";
    else
        return "";

}


int determineKind(char* test) {
    while ((strchr(" \t\n", *test)) && (*test  != '\0')) test++;

    while(*test++) {
        if ((test[0] != ' ') && (test[1] == '(')) return Kind_func; // заглушка
        if ((test[0] == '\n') || (test[0] == '\0') || (test[0] == ' '  && strchr(":-", test[1])))  return Kind_data;
    }
    return Kind_check_failed;
}

/*
 * this func take funcName() and
 * return him arg...
 */
char * getFixedParam(char* in) {
    if (strcmp(in, "") == 0)
        return "";
    char* str = strdup(in);
    while (*str++ != '(') ;
    str[strlen(str) - 1] = '\0';
    while (strchr(" \t\n", *str) && *str != '\0')     str++;
    char* tail = str;
    tail += strlen(str)-1;
    while ((tail > str) && (strchr(" \t\n", *tail)))
        *tail-- = '\0';
    if (strcmp(str, "") == 0)
        return "void";

    return strdup(str);
}

//char * strtok(char *s, const char *delim)
//{
//    static char *lasts;
//    register int ch;

//    if (s == 0)
//    s = lasts;
//    do {
//    if ((ch = *s++) == '\0')
//        return 0;
//    } while (strchr(delim, ch));
//    --s;
//    lasts = s + strcspn(s, delim);
//    if (*lasts != 0)
//    *lasts++ = 0;
//    return s;
//}







#endif // ANY_MODULES_C

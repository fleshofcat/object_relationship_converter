#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#define LINES   1024
#define COLUMNS 14


char* readySheet[LINES][COLUMNS];

#define HANDLE_MODULE_TYPE readySheet[0][0]
#define HANDLE_MODULE_NAME readySheet[0][1]


enum {
    Part_1,
    Part_2,

    Kind_func,
    Kind_data,
    Kind_check_failed,

    GET_FUNC_NAME,
    GET_TYPE_FUNC,
    GET_NAME,
    GET_TYPE,
    GET_ADDR,
    GET_DATA_STREAM,
    GET_CONTROL_STREAM
};



struct writeDataG {
    char *typeFuncG, *funcNameG,      // Table variables
    *typeOfCallingFuncG, *callingFuncG, *callingFuncModuleG, *dataStreamG, *cntrlFlowG, *dataFormG,
    *typeOfCallingFunc2G, *callingFunc2G, *callingFuncModule2G, *dataStream2G, *cntrlFlow2G, *dataForm2G;
} writeDataG ;


#endif // GLOBAL_DATA_H

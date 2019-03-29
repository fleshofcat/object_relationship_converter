#include <stdio.h>
#include <string.h>
#include "../script/global_data.h"
#include "../script/any_modules.c"

void test_getType();

void test_getType() {
    char* str = "\tdo_blb_create(mproc *, mpart *, message_data *, message_data *) : int - /sandbox/rtos/trunk/os-core/src/module/apm/blb.c";
    char* tst = getType(str);

    if (strcmp(tst, "int") != 0) {
        printf("%s\n\n", "Trouble getType()");
    }
}

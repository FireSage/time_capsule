#include <iostream>
#include <windows.h>
#include <fstream>
#include <oleacc.h>
#include <combaseapi.h>

#include "Window.h"

// using namespace std;

HWINEVENTHOOK g_hook;


void CALLBACK HandleWindowChangeEvent(HWINEVENTHOOK hook, 
                            DWORD event, 
                            HWND hwnd, 
                            LONG idObject, 
                            LONG idChild, 
                            DWORD dwEventThread, 
                            DWORD dwmsEventTime){
    Window win = Window(hwnd);
    // if(IsWindow(hwnd)){
        // std::cout<<"Window change\n";
    // }
    // HWND window = GetForegroundWindow();
    // int length = GetWindowTextLength(window);
    // char* buffer = new char[length + 1];
    // GetWindowText(window, buffer, length + 1);
    // std::string windowTitle(buffer);
    // std::cout << windowTitle << std::endl;
}

void subscribeToWindowChangeEvent(){
    // CoInitialize(NULL);

    g_hook = SetWinEventHook(
        EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND,  // Range of events (4 to 5).
        NULL,                                          // Handle to DLL.
        HandleWindowChangeEvent,                                // The callback.
        0, 0,              // Process and thread IDs of interest (0 = all)
        WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS // Flags.
    );
    std::cout<<"Listening for window switch ... "<<std::endl;
} 


void logActiveApp(string app){
    std::ofstream fileWriter;
    std::ifstream fileReader;

    fileWriter.open("time_capsule_log", std::ios_base::out | std::ios::trunc);
    if(fileWriter.is_open()){
        
    }
}
int main(){
    // HWND window = GetForegroundWindow();
    // int length = GetWindowTextLength(window);
    // char* buffer = new char[length + 1];
    // GetWindowText(window, buffer, length + 1);
    // std::string windowTitle(buffer);
    // std::cout << windowTitle;
    subscribeToWindowChangeEvent();
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        std::cout<<".";
    }
    return 0;
}
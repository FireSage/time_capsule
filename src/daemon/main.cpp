#include <iostream>
#include <windows.h>
#include <fstream>
#include <oleacc.h>
#include <combaseapi.h>
#include <ctime>
#include <chrono>
#include <sys/time.h>
#include "window.h"
#include <unordered_map>

// using namespace std;
std::unordered_map<string, Window*> windows;
Session session;

HWINEVENTHOOK g_hook;
using std::cout; using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam){

    return TRUE;
}
void CALLBACK HandleWindowChangeEvent(HWINEVENTHOOK hook, 
                            DWORD event, 
                            HWND hwnd, 
                            LONG idObject, 
                            LONG idChild, 
                            DWORD dwEventThread, 
                            DWORD dwmsEventTime){
    auto nowTime = duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::time_t time_t_time = duration_cast<seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    std::cout << "now Time: " << nowTime << "   time_t: " << time_t_time << std::endl;
    Window* win = new Window(hwnd);
    //Use process_id and filename as key  
    string key = std::to_string(win->getProcessId()) + "-"+ win->getFileName();
    if(windows.find(key) != windows.end()){
        delete windows[key];
    }
    windows[key] = win;
    // TODO:: change session to only inlcude relevant infor and not entire window object
    session.add(nowTime, win);
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
    // int integ = 0;
    // std::cout<<"Int size: "<< sizeof integ << std::endl;
    session = Session();
    EnumWindows(EnumWindowsProc, 0);
    subscribeToWindowChangeEvent();
    // TODO:: listen for process end : GetProcessTimes()
    // TODO:: use EVENT_OBJECT_NAMECHANGE to listen for tab changes in chrome etc 
    // TODO:: Track open windows
    // TODO:: Don not recreate object for window already being tracked. Map by process id
    // TODO:: Deal with memory leaks 
    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        std::cout<<".";
    }
    return 0;
}


/*
* get current active window    |
* write it to datatbase        |
* listen for inactive periods  | ---- loop
* listen for window switch     |
* 
*
*
*/
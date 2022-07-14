#include <iostream>
#include <string>
#include <windows.h>
#include <oleacc.h>
#include <combaseapi.h>
#include <psapi.h>
#include <tchar.h>

using std::string;

class Window{
    HWND hwnd {};
    string title {};
    string name {};
    string filename;
    DWORD process_id {};
    public:
    Window(HWND window);
    string findProcessTitle(HWND window);
    string findProcessFileName(HWND window);
};

Window::Window(HWND window){
    this->findProcessTitle(window);
    this->findProcessFileName(window);
}

string Window::findProcessTitle(HWND window){
    int length = GetWindowTextLength(window);
    
    char* buffer = new char[length + 1];
    if (GetWindowText(window, buffer, length + 1) > 0){
        this->title = string(buffer);
        // std::cout << this->title << std::endl;
    }
     return this->title;
}

string Window::findProcessFileName(HWND window){
    DWORD processBuffer;
    GetWindowThreadProcessId(window, &processBuffer);
    this->process_id = processBuffer;

    HANDLE processHandle = OpenProcess(
                  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                  FALSE,
                  processBuffer
                );
    if (processHandle){
        DWORD len = MAX_PATH;
        char* filenameBuffer =  new char[1000];
        if (GetProcessImageFileNameA(processHandle, filenameBuffer, 1000)){
            this->filename = string(filenameBuffer);
            // std::cout<<"Path: " << string(filenameBuffer)<<std::endl;
    //         // At this point, buffer contains the full path to the executable
        }
        CloseHandle(processHandle);
    }
    return this->filename;
}
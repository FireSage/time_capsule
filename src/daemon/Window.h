#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <iostream>
#include <string>
#include <windows.h>
#include <oleacc.h>
#include <combaseapi.h>
#include <psapi.h>
#include <tchar.h>
#include <filesystem>

using std::string;

class Window{
    HWND m_hwnd {};
    string title {};
    string M_application_name {};
    std::filesystem::path filepath;
    DWORD process_id {};
    
    public:
        Window(HWND window);
        string findProcessTitle(HWND window);
        string findProcessFileName(HWND window);
        std::filesystem::path getFilePath() const;
        std::string getFileName() const;
        DWORD getProcessId() const; 
};

class Session{
    private:
        struct session_data {
            int64_t start_time;
            int stop_time;
            Window* window;
        };
             
        typedef struct session_node{
            session_data* data;

            //next and previous elements
            session_node* next;
            session_node* previous;

        }* session_nodePtr;

        session_nodePtr head;
        session_nodePtr tail;
        session_nodePtr temp;

    public:
        Session();
        void add(int64_t startTime, Window* wind);
        void remove(Window* wind);
};



/*
Window::Window(HWND window){
    this->findProcessTitle(window);
    this->findProcessFileName(window);
}
string Window::findProcessTitle(HWND window){
    int length = GetWindowTextLength(window);
    
    char* buffer = new char[length + 1];
    if (GetWindowText(window, buffer, length + 1) > 0){
        this->title = string(buffer);
        std::cout << this->title << std::endl;
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
            this->filepath = string(filenameBuffer);
            std::cout<<"Path: " << this->filepath.filename() << std::endl;
            // std::cout<<"Path: " << string(filenameBuffer)<<std::endl;
    //         // At this point, buffer contains the full path to the executable
        }
        CloseHandle(processHandle);
    }
    return this->filepath.filename().string();
}
*/
#endif
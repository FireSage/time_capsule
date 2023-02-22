#include <iostream>
#include <string>
#include <filesystem>
#include <windows.h>
#include <oleacc.h>
#include <combaseapi.h>
#include <psapi.h>
#include <tchar.h>

#include "window.h"

Window::Window(HWND window) : m_hwnd(window){
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
    if (processHandle != nullptr){
        DWORD len = MAX_PATH;
        // char* filenameBuffer =  new char[1000];
        char filenameBuffer[MAX_PATH];
        // if (GetModuleFileNameEx(processHandle, nullptr, buffer, MAX_PATH))
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

DWORD Window::getProcessId() const{
    return this->process_id;
}

std::filesystem::path Window::getFilePath() const{
    return this->filepath;
}

string Window::getFileName() const{
    return this->filepath.filename().string();
}

// -----------------SESSION IMPLEMENTATION---------------------

Session::Session(){
    head = NULL;
    tail = NULL;
    temp = NULL;
}
void Session::add(int64_t startTime, Window *wind){
    session_nodePtr node = new session_node;
    node->next = NULL;
    //set data
    session_data* dat = new session_data;
    dat->start_time = startTime;
    dat->window = wind;
    node->data = dat;

    if(head == NULL){
        head = node;
        tail = node;
    }else{
        tail->next = node;
        node->previous = tail;
        tail = node; 
    }
}
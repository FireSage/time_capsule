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
    this->findProcessTitle();
    this->findProcessFileName();
}


string Window::findProcessTitle(){
    int length = GetWindowTextLength(this->m_hwnd);
    
    char* buffer = new char[length + 1];
    if (GetWindowText(this->m_hwnd, buffer, length + 1) > 0){
        this->title = string(buffer);
        // std::cout << this->title << std::endl;
    }
    return this->title;
}

string Window::findProcessFileName(){
    DWORD processBuffer;
    GetWindowThreadProcessId(this->m_hwnd, &processBuffer);
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
            // std::cout<<"Path: " << this->filepath.filename() << std::endl;
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

string Window::getTitle() const{
    return this->title;
}

// -----------------SESSION IMPLEMENTATION---------------------

Session::Session(){
    WriteQueue = {};
    // head = NULL;
    // tail = NULL;
    // temp = NULL;
}

void Session::add(int64_t startTime, Window *wind){
    session_data* dat = new session_data;
    dat->start_time = startTime;
    dat->window = wind;
    this->WriteQueue.push_back(dat);
}
// void Session::add(int64_t startTime, Window *wind){
//     session_nodePtr node = new session_node;
//     node->next = NULL;
//     //set data
//     session_data* dat = new session_data;
//     dat->start_time = startTime;
//     dat->window = wind;
//     node->data = dat;

//     if(head == NULL){
//         head = node;
//         tail = node;
//     }else{
//         tail->next = node;
//         node->previous = tail;
//         tail = node; 
//     }
// }
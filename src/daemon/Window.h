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
#include <deque>
using std::string;

class Window{
    HWND m_hwnd {};
    string title {};
    string M_application_name {};
    std::filesystem::path filepath;
    DWORD process_id {};
    
    public:
        Window(HWND window);
        string findProcessTitle();
        string findProcessFileName();
        std::filesystem::path getFilePath() const;
        std::string getFileName() const;
        std::string getTitle() const;
        DWORD getProcessId() const;
};

class Session{
    private:
        struct session_data {
            int64_t start_time;
            int stop_time;
            Window* window;
        };

        std::deque<session_data*> WriteQueue;

    public:
        Session();
        void add(int64_t startTime, Window* wind);
        void remove(Window* wind);
};



#endif
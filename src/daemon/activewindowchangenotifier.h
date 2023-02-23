#ifndef ACTIVE_WINDOW_CHANGE_CLASS_H
#define ACTIVE_WINDOW_CHANGE_CLASS_H

#include <windows.h>
#include <functional>
#include <vector>
// #include <window.h>

class ActiveWindowChangeNotifier{
    HWINEVENTHOOK m_hook;
    static std::vector<std::function<void(HWND)>> m_listeners;

    static void CALLBACK HandleWindowChangeEvent(HWINEVENTHOOK hook, 
                            DWORD event, 
                            HWND hwnd, 
                            LONG idObject, 
                            LONG idChild, 
                            DWORD dwEventThread, 
                            DWORD dwmsEventTime){
        for(const std::function<void(HWND)>& listener: m_listeners) {
            listener(hwnd);
        }
    }
    public:
    ActiveWindowChangeNotifier(){
        m_hook = SetWinEventHook(
            EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND,  // Range of events (4 to 5).
            NULL,                                          // Handle to DLL.
            &ActiveWindowChangeNotifier::HandleWindowChangeEvent,                                // The callback.
            0, 0,              // Process and thread IDs of interest (0 = all)
            WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS // Flags.
        );
    }

    ~ActiveWindowChangeNotifier(){
        UnhookWinEvent(m_hook);
    }

    void addListener(const std::function<void(HWND)>& listener){
        std::cout<<"Listening for window switch ... "<<std::endl;
        m_listeners.push_back(listener);
    }

};

std::vector<std::function<void(HWND)>> ActiveWindowChangeNotifier::m_listeners;


#endif
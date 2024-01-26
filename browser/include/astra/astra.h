#pragma once

#include <astra/base.h>

namespace Astra {

    class Application
    {
    public:
        Application();
        ~Application();

        void Run();
        void Close();

        WideString GetAppDataDirectory();
        WideString GetBrowserDataDirectory();
        WideString GetUserDataDirectory();

        WideString GetFullPathFor(LPCWSTR relativePath);

        static Application& Get();

    private:

        void Init();
        void Resize();

        static LRESULT CALLBACK ProcessMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        HINSTANCE m_InstanceHandle;
        HWND m_Window;

        Ref<WebViewEnvironment> m_ContentEnvironment;
        Ref<WebViewController> m_ContentController;
        Ref<WebView> m_ContentWebView;

        Ref<WebViewEnvironment> m_ToolbarEnvironment;
        Ref<WebViewController> m_ToolbarController;
        Ref<WebView> m_ToolbarWebView;

        EventRegistrationToken m_ToolbarZoomToken = {};

        bool m_Running;

    private:
        static TCHAR g_WindowClass[];
        static Application* s_Instance;
    };
}
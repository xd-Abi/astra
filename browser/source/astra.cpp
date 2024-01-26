#include <astra/astra.h>

namespace Astra {

    TCHAR Application::g_WindowClass[] = TEXT("AstraWindow");
    Application* Application::s_Instance;

    Application::Application()
    {
        /**
         * Check if there is already an instance exists.
         */
        if (s_Instance)
        {
            MessageBoxA(nullptr, TEXT("Application already exists!"), TEXT("Error"), MB_OK | MB_ICONERROR);
            return;
        }
        s_Instance = this;

        Init();
    }

    Application::~Application()
    {
        UnregisterClass(g_WindowClass, m_InstanceHandle);
    }


    void Application::Init()
    {
        m_InstanceHandle = GetModuleHandleA(nullptr);

        /**
         * Register window class
         */
        WNDCLASS wc = { sizeof(WNDCLASS) };
        wc.lpfnWndProc = Application::ProcessMessage;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = m_InstanceHandle;
        wc.hIcon = nullptr;
        wc.hCursor = LoadCursor(m_InstanceHandle, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName = nullptr;
        wc.lpszClassName = g_WindowClass;

        if (!RegisterClass(&wc))
        {
            MessageBoxA(nullptr, TEXT("Window Class Registration Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
            return;
        }

        /**
         * Window creation
         */
        m_Window = CreateWindow(
                g_WindowClass,
                TEXT("Astra"),
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                nullptr,
                nullptr,
                m_InstanceHandle,
                nullptr
        );

        if (m_Window == nullptr)
        {
            MessageBoxA(nullptr, TEXT("Window Creation Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
            return;
        }

        ShowWindow(m_Window, SW_SHOWNORMAL);
        UpdateWindow(m_Window);

        /**
         * Create WebView environment for web content requested by the user.
         */
        HRESULT hr = CreateCoreWebView2EnvironmentWithOptions(nullptr, GetUserDataDirectory().c_str(), nullptr,
            Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
                [this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT
                {
                    RETURN_IF_FAILED(result);
                    m_ContentEnvironment = env;
                    return S_OK;
                }
            ).Get()
        );

        if (!SUCCEEDED(hr))
        {
            MessageBoxA(nullptr, TEXT("Content WebView Creation Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
            return;
        }

        hr = m_ContentEnvironment->CreateCoreWebView2Controller(m_Window,
            Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                [this](HRESULT result, WebViewController* controller) -> HRESULT
                {
                    if (!SUCCEEDED(result))
                    {
                        return result;
                    }

                    m_ContentController = controller;
                    m_ContentController->get_CoreWebView2(&m_ContentWebView);

                    Ref<ICoreWebView2Settings> settings;
                    m_ContentWebView->get_Settings(&settings);

                    settings->put_IsScriptEnabled(true);
                    settings->put_AreDevToolsEnabled(false);

                    Resize();
                    m_ContentWebView->Navigate(L"localhost:3000");

                    return S_OK;
                }
            ).Get()
        );

        if (!SUCCEEDED(hr))
        {
            MessageBoxA(nullptr, TEXT("Content WebView Creation Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
            return;
        }

        /**
         * Create WebView environment for toolbar.
         */
        hr = CreateCoreWebView2EnvironmentWithOptions(nullptr, GetBrowserDataDirectory().c_str(), nullptr,
            Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
                [this](HRESULT result, ICoreWebView2Environment* env) -> HRESULT
                {
                    RETURN_IF_FAILED(result);
                    m_ToolbarEnvironment = env;
                    return S_OK;
                }
            ).Get()
        );

        if (!SUCCEEDED(hr))
        {
            MessageBoxA(nullptr, TEXT("Toolbar WebView Creation Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
            return;
        }
        
        hr = m_ToolbarEnvironment->CreateCoreWebView2Controller(m_Window,
            Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                [this](HRESULT result, WebViewController* controller) -> HRESULT
                {
                    if (!SUCCEEDED(result))
                    {
                        return result;
                    }

                    m_ToolbarController = controller;
                    m_ToolbarController->get_CoreWebView2(&m_ToolbarWebView);
                    m_ToolbarController->add_ZoomFactorChanged(Microsoft::WRL::Callback<ICoreWebView2ZoomFactorChangedEventHandler>(
                            [](ICoreWebView2Controller* host, IUnknown* args) -> HRESULT
                            {
                                host->put_ZoomFactor(1.0);
                                return S_OK;
                            }
                    ).Get(), &m_ToolbarZoomToken);

                    Ref<ICoreWebView2Settings> settings;
                    m_ToolbarWebView->get_Settings(&settings);

                    settings->put_IsScriptEnabled(true);
                    settings->put_AreDevToolsEnabled(false);

                    Resize();
                    WideString toolbarHTMLContentPath = GetFullPathFor(L"toolbar\\index.html");
                    m_ToolbarWebView->Navigate(toolbarHTMLContentPath.c_str());

                    return S_OK;
                }
            ).Get()
        );

        if (!SUCCEEDED(hr))
        {
            MessageBoxA(nullptr, TEXT("Toolbar WebView Creation Failed!"), TEXT("Error"), MB_OK | MB_ICONERROR);
            return;
        }

        m_Running = true;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            MSG msg;

            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }

    void Application::Resize()
    {
        RECT clientArea;
        GetClientRect(m_Window, &clientArea);

        if (m_ContentController != nullptr)
        {
            clientArea.top = 53;
            m_ContentController->put_Bounds(clientArea);
        }

        if (m_ToolbarController != nullptr)
        {
            clientArea.top = 0;
            clientArea.bottom = 53;
            m_ToolbarController->put_Bounds(clientArea);
        }
    }

    WideString Application::GetAppDataDirectory()
    {
        TCHAR path[MAX_PATH];
        WideString dataDirectory;
        HRESULT hr = SHGetFolderPath(nullptr, CSIDL_APPDATA, NULL, 0, path);

        if (SUCCEEDED(hr))
        {
            dataDirectory = WideString(dataDirectory);
            dataDirectory.append(L".\\Astra\\");

            return dataDirectory;
        }
        else
        {
            /**
             * Fallback to the current directory if AppData retrieval fails
             */
            return L".\\Astra";
        }
    }
        
    WideString Application::GetBrowserDataDirectory()
    {
        auto directory = GetAppDataDirectory();
        directory.append(L"\\Browser Data");

        return directory;
    }

    WideString Application::GetUserDataDirectory()
    {
        auto directory = GetAppDataDirectory();
        directory.append(L"\\User Data");

        return directory;
    }

    WideString Application::GetFullPathFor(LPCWSTR relativePath)
    {
        WCHAR path[MAX_PATH];
        GetModuleFileNameW(m_InstanceHandle, path, MAX_PATH);
        WideString pathName(path);

        size index = pathName.find_last_of(L"\\") + 1;
        pathName.replace(index, pathName.length(), relativePath);

        return pathName;
    }

    Application& Application::Get()
    {
        return *s_Instance;
    }

    LRESULT CALLBACK Application::ProcessMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        static int CAPTION_THICKNESS = 53;
        static RECT BORDER_THICKNESS = { 4, 4, 4, 4 };

        switch (message)
        {
            case WM_GETMINMAXINFO:
            {
                MINMAXINFO* pInfo = (MINMAXINFO*)lParam;
                pInfo->ptMinTrackSize.x = 900;
                pInfo->ptMinTrackSize.y = 600;
            }
            break;
            case WM_SIZE:
            {
                auto& app = Application::Get();
                app.Resize();
            }
            break;
            case WM_NCCALCSIZE:
            {
                int resizeBorderX = GetSystemMetrics(SM_CXFRAME);
                int resizeBorderY = GetSystemMetrics(SM_CYFRAME);

                auto* params = (NCCALCSIZE_PARAMS*)lParam;
                RECT* requestedClientRect = params->rgrc;

                requestedClientRect->right -= resizeBorderX;
                requestedClientRect->left += resizeBorderX;
                requestedClientRect->bottom -= resizeBorderY;

                /**
                 * NOTE: Top borders are to be handled differently.
                 * Contracting by 1 on Windows 11 seems to give a small area
                 * for resizing whilst not showing a white border.
                 */
                requestedClientRect->top += 0;

                return 0;
            }
            case WM_NCHITTEST:
            {
                POINT point = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
                ScreenToClient(hwnd, &point);

                if (!IsZoomed(hwnd))
                {
                    RECT rect;
                    GetClientRect(hwnd, &rect);

                    const int verticalBorderSize = GetSystemMetrics(SM_CYFRAME);
                    enum {
                        left = 1,
                        top = 2,
                        right = 4,
                        bottom = 8
                    };

                    int hit = 0;
                    if (point.x <= BORDER_THICKNESS.left)
                    {
                        hit |= left;
                    }
                    if (point.x >= rect.right - BORDER_THICKNESS.right)
                    {
                        hit |= right;
                    }
                    if (point.y <= BORDER_THICKNESS.top || point.y < verticalBorderSize)
                    {
                        hit |= top;
                    }
                    if (point.y >= rect.bottom - BORDER_THICKNESS.bottom)
                    {
                        hit |= bottom;
                    }

                    if (hit & top && hit & left)        return HTTOPLEFT;
                    if (hit & top && hit & right)       return HTTOPRIGHT;
                    if (hit & bottom && hit & left)     return HTBOTTOMLEFT;
                    if (hit & bottom && hit & right)    return HTBOTTOMRIGHT;
                    if (hit & left)                     return HTLEFT;
                    if (hit & top)                      return HTTOP;
                    if (hit & right)                    return HTRIGHT;
                    if (hit & bottom)                   return HTBOTTOM;
                }

                if (point.y <= CAPTION_THICKNESS)
                {
                    return HTCAPTION;
                }

                return HTCLIENT;
            }
        }

        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}
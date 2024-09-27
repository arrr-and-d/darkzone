// DARKZONE - An optimized screen dimmer 

#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

bool isDragging = false;
bool isRightDragging = false;
POINT dragStart;

// Initial opacity value
BYTE currentOpacity = 100;

// Initial window size
int currentWidth = 800;
int currentHeight = 600;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Window class
    const wchar_t CLASS_NAME[] = L"TransparentBlackWindow";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create handle to a window
    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
        CLASS_NAME,
        L"Transparent Window",
        WS_POPUP | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, currentWidth, currentHeight,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    // Set the initial window's layered attributes for transparency
    SetLayeredWindowAttributes(hwnd, RGB(255, 0, 0), currentOpacity, LWA_ALPHA);

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Create a solid black brush
        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));
        // Fill the window with the selected color
        FillRect(hdc, &ps.rcPaint, hBrush);
        DeleteObject(hBrush);

        EndPaint(hwnd, &ps);
    }
    return 0;

    case WM_LBUTTONDOWN:
        isDragging = true;
        dragStart.x = LOWORD(lParam);
        dragStart.y = HIWORD(lParam);
        SetCapture(hwnd);
        return 0;

    case WM_LBUTTONUP:
        isDragging = false;
        ReleaseCapture();
        return 0;

    case WM_RBUTTONDOWN:
        isRightDragging = true;
        dragStart.x = LOWORD(lParam);
        dragStart.y = HIWORD(lParam);
        SetCapture(hwnd);
        return 0;

    case WM_RBUTTONUP:
        isRightDragging = false;
        ReleaseCapture();
        return 0;

    case WM_MOUSEMOVE:
        if (isDragging)
        {
            POINT p;
            p.x = LOWORD(lParam);
            p.y = HIWORD(lParam);
            RECT rc;
            GetWindowRect(hwnd, &rc);
            SetWindowPos(hwnd, NULL, rc.left + (p.x - dragStart.x), rc.top + (p.y - dragStart.y), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }
        else if (isRightDragging)
        {
            POINT p;
            p.x = LOWORD(lParam);
            p.y = HIWORD(lParam);
            RECT rc;
            GetWindowRect(hwnd, &rc);
            SetWindowPos(hwnd, NULL, rc.left + (p.x - dragStart.x), rc.top + (p.y - dragStart.y), currentWidth, currentHeight, SWP_NOZORDER);
        }
        return 0;

    case WM_KEYDOWN:
        if (GetForegroundWindow() == hwnd) // Only process if the window is selected
        {
            switch (wParam)
            {
            case 'P': // Increase opacity
                if (currentOpacity < 255)
                {
                    currentOpacity++;
                    SetLayeredWindowAttributes(hwnd, RGB(255, 0, 0), currentOpacity, LWA_ALPHA);
                }
                break;

            case 'O': // Decrease opacity
                if (currentOpacity > 0)
                {
                    currentOpacity--;
                    SetLayeredWindowAttributes(hwnd, RGB(255, 0, 0), currentOpacity, LWA_ALPHA);
                }
                break;

            case VK_LEFT: // Decrease width
                currentWidth = max(100, currentWidth - 10);
                SetWindowPos(hwnd, NULL, 0, 0, currentWidth, currentHeight, SWP_NOMOVE | SWP_NOZORDER);
                break;

            case VK_RIGHT: // Increase width
                currentWidth += 10;
                SetWindowPos(hwnd, NULL, 0, 0, currentWidth, currentHeight, SWP_NOMOVE | SWP_NOZORDER);
                break;

            case VK_DOWN: // Increase height
                currentHeight += 10;
                SetWindowPos(hwnd, NULL, 0, 0, currentWidth, currentHeight, SWP_NOMOVE | SWP_NOZORDER);
                break;

            case VK_UP: // Decrease height
                currentHeight = max(100, currentHeight - 10);
                SetWindowPos(hwnd, NULL, 0, 0, currentWidth, currentHeight, SWP_NOMOVE | SWP_NOZORDER);
                break;
            }
        }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

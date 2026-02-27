#include <windows.h>
#include <string>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void PerformCalculation(HWND hwnd, char operation);

HWND hEdit1, hEdit2;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Calculator";
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 0)); // Red background
    
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("Calculator", "My Calculator", WS_OVERLAPPED | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);
    
    ShowWindow(hwnd, nCmdShow);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD,
            20, 10, 200, 20, hwnd, NULL, NULL, NULL);
        
        hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 40, 200, 20, hwnd, NULL, NULL, NULL);
        hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
            20, 70, 200, 20, hwnd, NULL, NULL, NULL);
        
        CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD,
            20, 100, 40, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD,
            70, 100, 40, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD,
            120, 100, 40, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD,
            170, 100, 40, 30, hwnd, (HMENU)4, NULL, NULL);
        break;
    
    case WM_COMMAND:
        if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {
            PerformCalculation(hwnd, (LOWORD(wParam) == 1 ? '+' :
                                      LOWORD(wParam) == 2 ? '-' :
                                      LOWORD(wParam) == 3 ? '*' : '/'));
        }
        break;
        
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

void PerformCalculation(HWND hwnd, char operation) {
    char buffer1[256], buffer2[256];
    GetWindowText(hEdit1, buffer1, 256);
    GetWindowText(hEdit2, buffer2, 256);
    
    double num1 = atof(buffer1);
    double num2 = atof(buffer2);
    double result = 0;
    
    if (operation == '/' && num2 == 0) {
        MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
        return;
    }
    
    switch (operation) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = num1 / num2; break;
    }
    
    char resultText[256];
    sprintf(resultText, "Result: %.2f", result);

    MessageBox(hwnd, resultText, "Result", MB_OK | MB_ICONINFORMATION);
}

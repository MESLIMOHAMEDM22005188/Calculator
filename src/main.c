#include <windows.h>
#include <stdio.h>
#include <math.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

// Global Variables
char inputBuffer[256] = "";
double currentNumber = 0;
char operation = '\0';
HWND hDisplay;

void calculate() {
    double result = 0;

    if (operation == '+') result = currentNumber + atof(inputBuffer);
    else if (operation == '-') result = currentNumber - atof(inputBuffer);
    else if (operation == '*') result = currentNumber * atof(inputBuffer);
    else if (operation == '/') {
        if (atof(inputBuffer) != 0)
            result = currentNumber / atof(inputBuffer);
        else
            MessageBox(NULL, "Error: Division by zero!", "Error", MB_OK);
    } else if (operation == '^') result = pow(currentNumber, atof(inputBuffer));

    // Display result
    sprintf(inputBuffer, "%.2f", result);
    SetWindowText(hDisplay, inputBuffer);

    // Reset
    currentNumber = 0;
    operation = '\0';
}

void performUnaryOperation(char op) {
    double value = atof(inputBuffer);
    double result = 0;

    switch (op) {
        case 's': result = sin(value); break;
        case 'c': result = cos(value); break;
        case 't': result = tan(value); break;
        case 'S': result = asin(value); break;
        case 'C': result = acos(value); break;
        case 'T': result = atan(value); break;
        case '2': result = pow(value, 2); break;
        case '3': result = pow(value, 3); break;
    }

    sprintf(inputBuffer, "%.2f", result);
    SetWindowText(hDisplay, inputBuffer);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG messages;
    WNDCLASS wincl = {0};

    // Define window class
    wincl.hInstance = hInstance;
    wincl.lpszClassName = "CalculatorApp";
    wincl.lpfnWndProc = WindowProcedure;
    wincl.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);

    // Register the class
    if (!RegisterClass(&wincl)) return 0;

    // Create the main window
    HWND hwnd = CreateWindow(
        "CalculatorApp", "Advanced Calculator",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 600,
        HWND_DESKTOP, NULL, hInstance, NULL
    );

    // Run the message loop
    while (GetMessage(&messages, NULL, 0, 0)) {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            // Create display
            hDisplay = CreateWindow("EDIT", "",
                                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
                                    20, 20, 340, 40, hwnd, NULL, NULL, NULL);

            // Create buttons
            const char* buttons[] = {
                "7", "8", "9", "/", "sin", "cos", "tan",
                "4", "5", "6", "*", "asin", "acos", "atan",
                "1", "2", "3", "-", "x^2", "x^3", "π",
                "0", "C", "=", "+", "φ", "sqrt", "log"
            };
            for (int i = 0; i < 28; i++) {
                CreateWindow("BUTTON", buttons[i],
                             WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                             20 + (i % 7) * 50, 80 + (i / 7) * 60, 45, 45,
                             hwnd, (HMENU)(i + 1), NULL, NULL);
            }
            break;
        }
        case WM_COMMAND: {
            int id = LOWORD(wParam);
            char buttonText[10];
            GetWindowText((HWND)lParam, buttonText, 10);

            if (id >= 1 && id <= 28) {
                if (isdigit(buttonText[0])) { // Numbers
                    strcat(inputBuffer, buttonText);
                    SetWindowText(hDisplay, inputBuffer);
                } else if (strcmp(buttonText, "C") == 0) { // Clear
                    inputBuffer[0] = '\0';
                    currentNumber = 0;
                    operation = '\0';
                    SetWindowText(hDisplay, inputBuffer);
                } else if (strcmp(buttonText, "=") == 0) { // Equals
                    calculate();
                } else if (strcmp(buttonText, "π") == 0) { // Pi
                    sprintf(inputBuffer, "%.15f", M_PI);
                    SetWindowText(hDisplay, inputBuffer);
                } else if (strcmp(buttonText, "φ") == 0) { // Golden Ratio
                    sprintf(inputBuffer, "%.15f", 1.61803398875);
                    SetWindowText(hDisplay, inputBuffer);
                } else if (strcmp(buttonText, "x^2") == 0) { // Square
                    performUnaryOperation('2');
                } else if (strcmp(buttonText, "x^3") == 0) { // Cube
                    performUnaryOperation('3');
                } else if (strcmp(buttonText, "sin") == 0) {
                    performUnaryOperation('s');
                } else if (strcmp(buttonText, "cos") == 0) {
                    performUnaryOperation('c');
                } else if (strcmp(buttonText, "tan") == 0) {
                    performUnaryOperation('t');
                } else if (strcmp(buttonText, "asin") == 0) {
                    performUnaryOperation('S');
                } else if (strcmp(buttonText, "acos") == 0) {
                    performUnaryOperation('C');
                } else if (strcmp(buttonText, "atan") == 0) {
                    performUnaryOperation('T');
                } else { // Binary Operations
                    currentNumber = atof(inputBuffer);
                    operation = buttonText[0];
                    inputBuffer[0] = '\0';
                }
            }
            break;
        }
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


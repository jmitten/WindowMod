#include <unistd.h>
#include <stdio.h>

#define _WIN32_WINNT 0x0500

#include <windows.h>

void showInfo(char *);

void showTitle();

void CaptureWindow(char[], char[], int, int, int);

void DisableCloseButton(HWND);

void EnableCloseButton(HWND);

int main(int argc, char *argv[]) {
    showTitle();
    int c, windowFlag = 0, renameFlag = 0, enableFlag = 0, hideFlag = 0, timeout = 60;
    opterr = 0;
    char windowTitle[256], newWindowName[256];
    while ((c = getopt(argc, argv, "hfew:t:r:")) != -1) {
        switch (c) {
            case 'h':
                showInfo(argv[0]);
                exit(1);
            case 'w':
                lstrcpyA(windowTitle, optarg);
                windowFlag = 1;
                break;
            case 't':
                timeout = atoi(optarg);
                break;
            case 'r':
                lstrcpyA(newWindowName, optarg);
                renameFlag = 1;
                break;
            case 'e':
                enableFlag = 1;
                break;
            case 'f':
                hideFlag = 1;
                break;
            case '?':
                if (optopt == 'w') {

                    fprintf(stderr, "Option -%c requires an argument: %s\n", optopt, "Window Title");
                } else if (optopt == 'r') {
                    fprintf(stderr, "Option -%c requires an argument: %s\n", optopt, "New Window Title");
                } else if (optopt == 't') {
                    fprintf(stderr, "Option -%c requires an argument: %s\n", optopt, "Timeout Value(Seconds)");
                } else {
                    fprintf(stderr, "Unknown option character \'%c\'.\n", optopt);
                }
                exit(1);
                break;
            default:
                abort();
        }
    }
    if (argc == 1) {
        fprintf(stdout, "No arguments were specified\n");
        fprintf(stdout, "Use %s -h for help.\n", argv[0]);
        exit(1);
    }
    if (hideFlag) {
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    }
    if (!windowFlag) {
        fprintf(stdout, "You must specify a window title.\n");
        exit(1);
    }
    if (timeout <= 0) {
        fprintf(stdout, "Invalid timeout value. Defaulting to 60 seconds.\n");
        timeout = 60;
    }
    if (!renameFlag) {
        lstrcpy(newWindowName, windowTitle);
    }


    fprintf(stdout, "Window Title: %s\n", windowTitle);
    fprintf(stdout, "Renaming Window To: %s\n", newWindowName);
    fprintf(stdout, "Program Timeout: %d seconds\n", timeout);
    if (enableFlag) {
        fprintf(stdout, "Mode: Enable close button\n");
    } else {
        fprintf(stdout, "Mode: Disable close button\n");
    }
    CaptureWindow(windowTitle, newWindowName, timeout, enableFlag, hideFlag);
    return 0;
}

void showInfo(char *s) {
    fprintf(stdout, "Usage:   %s [-option] [argument]\n", s);
    fprintf(stdout, "option:  -e  Enable close button\n");
    fprintf(stdout, "         -f  Force the console window to stay hidden\n");
    fprintf(stdout, "         -h  show help information\n");
    fprintf(stdout, "         -w <Window Title(REQUIRED)>\n");
    fprintf(stdout, "         -t  <Timeout Value (Seconds)>\n");
    fprintf(stdout, "         -r  <New Window Title>\n");
}

void CaptureWindow(char title[], char newTitle[], int timeOut, int enableFlag, int hideFlag) {
    HWND hWnd = NULL;
    for (int i = -1; i < timeOut * 2; i++) {
        hWnd = FindWindow(NULL, title);
        if (hWnd == 0) {
            Sleep(500);
        }
        else {
            i = timeOut * 2;
        }
    }
    if (hWnd == 0) {
        if (hideFlag) {
            char message[255];
            sprintf(message, "The window \'%s\' was not found.\nThe operation timed out.", title);
            MessageBox(NULL, message, TEXT("Error: Window not found"), MB_OK | MB_ICONERROR);
        } else {
            fprintf(stderr, "The window \'%s\' was not found.\nThe operation timed out.", title);
        }
        exit(1);
    } else {
        if (enableFlag) {
            EnableCloseButton(hWnd);
        } else {
            DisableCloseButton(hWnd);
        }
        SetWindowText(hWnd, newTitle);
    }
}

void DisableCloseButton(HWND hwnd) {
    DeleteMenu(GetSystemMenu(hwnd, FALSE), SC_CLOSE, MF_DISABLED);
}

void EnableCloseButton(HWND hwnd) {
    GetSystemMenu(hwnd, TRUE);
    DrawMenuBar(hwnd);
}

void showTitle() {
    fprintf(stdout, " ______________________\n");
    fprintf(stdout, "|                      |\n");
    fprintf(stdout, "|    WindowMod v0.1    |\n");
    fprintf(stdout, "|  Created by jmitten  |\n");
    fprintf(stdout, "|______________________|\n");
}
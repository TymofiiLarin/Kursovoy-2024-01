


#include <windows.h>
#include <stdio.h>

static WCHAR GetUserInput();


WCHAR ShowMainMenu()
{
    wprintf(L"\n\nMain Menu\n");
    wprintf(L"---------\n");
    wprintf(L"A) Get/Set user quotas\n");
    wprintf(L"B) Add/Delete a user for which to keep track of disk quotas\n");
    wprintf(L"C) Exit \n");
    wprintf(L"Please enter your selection: ");

    return (GetUserInput());
}

WCHAR ShowUserManagerMenu()
{
    wprintf(L"\n\nUser Manager Menu\n");
    wprintf(L"-----------------\n");
    wprintf(L"A) Add a user for which to keep track of quotas\n");
    wprintf(L"B) Delete a user for which you no longer which to track quotas\n");
    wprintf(L"C) Enumerate users for which quotas are tracked\n");
    wprintf(L"D) Exit back to main menu\n");
    wprintf(L"Please enter your selection: ");

    return (GetUserInput());
}


WCHAR ShowQuotaManagerMenu()
{
    wprintf(L"\n\nQuota Manager Menu\n");
    wprintf(L"------------------\n");
    wprintf(L"A) Get the quota information for all users\n");
    wprintf(L"B) Set the quota hard limit for a user\n");
    wprintf(L"C) Set the quota threshold for a user\n");
    wprintf(L"D) Exit back to main menu\n");
    wprintf(L"Please enter your selection: ");

    return (GetUserInput());
}


WCHAR GetUserInput()
{
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD sInputRecord;
    DWORD        dwInputEvents;

    ReadConsoleInput(hStdIn,&sInputRecord,1 ,&dwInputEvents);
    while (!((sInputRecord.EventType == KEY_EVENT) && (sInputRecord.Event.KeyEvent.bKeyDown)))
    {
        FlushConsoleInputBuffer(hStdIn);
        ReadConsoleInput(hStdIn,&sInputRecord,1 ,&dwInputEvents);
    }

    return sInputRecord.Event.KeyEvent.uChar.UnicodeChar;
}

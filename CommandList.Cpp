
#include <windows.h>
#include <stdio.h>
#include <dskquota.h>
#include "CommandList.h"

static void WaitForKeyPress();

BOOL SetUserHardLimit(IDiskQuotaControl* lpDiskQuotaControl)
{
    HRESULT  hr;
    IDiskQuotaUser* lpDiskQuotaUser;
    WCHAR    szUser[MAX_PATH] = {0};
    WCHAR    szLimit[MAX_PATH] = {0};
    DWORD    dwCharsRead;
    LONGLONG llLimit = 0;
    HANDLE   hStdIn  = GetStdHandle(STD_INPUT_HANDLE);

    wprintf(L"\n\nEnter the logon name of the user ");
    wprintf(L"(ie. DOMAIN\\USERNAME): ");

    ReadConsole(hStdIn, szUser, MAX_PATH, &dwCharsRead, NULL);
    szUser[MAX_PATH-1] = L'\0';

    LfcrToNull(szUser);

    hr = lpDiskQuotaControl->FindUserName((LPCWSTR)szUser, &lpDiskQuotaUser);

    if (SUCCEEDED(hr))
    {
        wprintf(L"\nEnter the new hard limit in bytes (-1 == No Limit): ");

        ReadConsole(hStdIn, szLimit, MAX_PATH, &dwCharsRead, NULL);
        LfcrToNull(szLimit);
        llLimit = _wtoi64(szLimit);

        if (llLimit >= -1)
        {
            hr = lpDiskQuotaUser->SetQuotaLimit(llLimit, TRUE);

            if (FAILED(hr))
            {
                wprintf(L"\nCould not set the quota limit for ");
                wprintf(L"%s to %i64 bytes\n", szUser, llLimit);
            }
        }
        else
        {
            wprintf(L"\nInvalid limit!");
        }

        lpDiskQuotaUser->Release();
    }
    else
    {
        wprintf(L"\nCould not find quota data for %s\n", szUser);
    }

    return SUCCEEDED(hr);
}

BOOL SetUserThreshold(IDiskQuotaControl* lpDiskQuotaControl)
{
    HRESULT  hr;
    IDiskQuotaUser* lpDiskQuotaUser;
    WCHAR    szUser[MAX_PATH] = { 0 };
    DWORD    dwCharsRead;
    LONGLONG llLimit = 0;
    HANDLE   hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    wprintf(L"\n\nEnter the logon name of the user ");
    wprintf(L"(ie. DOMAIN\\USERNAME): ");

    ReadConsole(hStdIn, szUser, MAX_PATH, &dwCharsRead, NULL);

    szUser[MAX_PATH - 1] = L'\0';

    LfcrToNull(szUser);

    hr = lpDiskQuotaControl->FindUserName((LPCWSTR)szUser, &lpDiskQuotaUser);

    if (SUCCEEDED(hr))
    {
        WCHAR    szLimit[MAX_PATH] = { 0 };
        wprintf(L"\nEnter the new threshold in bytes (-1 == No Limit): ");

        ReadConsole(hStdIn, szLimit, MAX_PATH, &dwCharsRead, NULL);
        LfcrToNull(szLimit);
        llLimit = _wtoi64(szLimit);

        if (llLimit >= -1)
        {
            hr = lpDiskQuotaUser->SetQuotaThreshold(llLimit, TRUE);

            if (FAILED(hr))
            {
                wprintf(L"\nCould not set the quota limit for %s", szUser);
                wprintf(L"to %i64 bytes\n", llLimit);
            }
        }
        else
        {
            wprintf(L"\nInvalid limit!");
        }
        lpDiskQuotaUser->Release();
    }
    else
    {
        ShowError(hr);
    }

    return SUCCEEDED(hr);
}



BOOL AddUser(IDiskQuotaControl* lpDiskQuotaControl)
{
    HRESULT  hr;
    IDiskQuotaUser* lpDiskQuotaUser;
    WCHAR    szUser[MAX_PATH] = {0};
    DWORD    dwCharsRead;
    HANDLE   hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    wprintf(L"\n\nEnter the logon name of the user (ie. DOMAIN\\USERNAME): ");

    ReadConsole(hStdIn, szUser, MAX_PATH, &dwCharsRead, NULL);
    LfcrToNull(szUser);

    hr = lpDiskQuotaControl->AddUserName(szUser,
                                DISKQUOTA_USERNAME_RESOLVE_SYNC,
                                &lpDiskQuotaUser);

    if (FAILED(hr))
    {
        ShowError(hr);
        return FALSE;
    }
    lpDiskQuotaUser->Release();

    return TRUE;
}


BOOL DeleteUser(IDiskQuotaControl* lpDiskQuotaControl)
{
    HRESULT         hr;
    IDiskQuotaUser* lpDiskQuotaUser;
    WCHAR           szUser[MAX_PATH] = {0};
    DWORD           dwCharsRead;
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    wprintf(L"\n\nEnter the logon name of the user (ie. DOMAIN\\USERNAME): ");

    ReadConsole(hStdIn, szUser, MAX_PATH, &dwCharsRead, NULL);
    LfcrToNull(szUser);

    hr = lpDiskQuotaControl->FindUserName((LPCWSTR)szUser, &lpDiskQuotaUser);

    if (SUCCEEDED(hr))
    {
        hr = lpDiskQuotaControl->DeleteUser(lpDiskQuotaUser);

        if (FAILED(hr))
        {
            wprintf(L"\nCould not delete the user.");
        }

        lpDiskQuotaUser->Release();
    }
    else
    {
        ShowError(hr);
    }

    return SUCCEEDED(hr);
}

BOOL EnumerateUsers(IDiskQuotaControl* lpDiskQuotaControl)
{
    HRESULT              hr;
    IEnumDiskQuotaUsers* lpEnumDiskQuotaUsers;
    IDiskQuotaUser*      lpDiskQuotaUser;
    DWORD                dwUsersFetched;

    hr = lpDiskQuotaControl->CreateEnumUsers(NULL, 0,
                                             DISKQUOTA_USERNAME_RESOLVE_SYNC,
                                             &lpEnumDiskQuotaUsers);
    if (SUCCEEDED(hr))
    {
        WCHAR szLogonName[MAX_PATH];

        wprintf(L"\n\nLogon name\n");
        wprintf(L"----------\n");

        while(SUCCEEDED(hr) &&
              S_OK == lpEnumDiskQuotaUsers->
                      Next(1, &lpDiskQuotaUser, &dwUsersFetched))
        {
            if (SUCCEEDED(hr = lpDiskQuotaUser->GetName(NULL, 0, szLogonName,
                                                        MAX_PATH, NULL, 0)))
            { 
                szLogonName[MAX_PATH-1] = L'\0';
                wprintf(L"%s\n", szLogonName);
                lpDiskQuotaUser->Release();
            }
        }
        lpEnumDiskQuotaUsers->Release();
    }

    if (FAILED(hr)) ShowError(hr);
    WaitForKeyPress();

    return SUCCEEDED(hr);
}

BOOL EnumerateUserQuotas(IDiskQuotaControl* lpDiskQuotaControl)
{
    HRESULT              hr;
    IEnumDiskQuotaUsers* lpEnumDiskQuotaUsers;

    hr = lpDiskQuotaControl->CreateEnumUsers(NULL, 0,
                                             DISKQUOTA_USERNAME_RESOLVE_SYNC,
                                             &lpEnumDiskQuotaUsers);
    if (SUCCEEDED(hr))
    {
        IDiskQuotaUser*      lpDiskQuotaUser;
        DWORD                dwUsersFetched;
        WCHAR                szLogonName[MAX_PATH];
        WCHAR                szQuotaUsedText[MAX_PATH];
        WCHAR                szQuotaLimitText[MAX_PATH];
        WCHAR                szQuotaThresholdText[MAX_PATH];
        DISKQUOTA_USER_INFORMATION dqUserInfo;

        wprintf(L"\n\nStatus               Logon Name  ");
        wprintf(L"Amount Used        Limit    Threshold\n");
        wprintf(L"------               ----------  ");
        wprintf(L"-----------        -----    ---------\n");

        while(SUCCEEDED(hr) &&
              S_OK == lpEnumDiskQuotaUsers->
                        Next(1, &lpDiskQuotaUser, &dwUsersFetched))
        {
            if (SUCCEEDED(hr = lpDiskQuotaUser->
                    GetName(NULL, 0, szLogonName, MAX_PATH, NULL, 0))      &&
                SUCCEEDED(hr = lpDiskQuotaUser->
                    GetQuotaThresholdText(szQuotaThresholdText, MAX_PATH)) &&
                SUCCEEDED(hr = lpDiskQuotaUser->
                    GetQuotaLimitText(szQuotaLimitText, MAX_PATH))         &&
                SUCCEEDED(hr = lpDiskQuotaUser->
                    GetQuotaUsedText(szQuotaUsedText, MAX_PATH))           &&
                SUCCEEDED(hr = lpDiskQuotaUser->
                    GetQuotaInformation((LPVOID)&dqUserInfo,
                        sizeof(DISKQUOTA_USER_INFORMATION))))
            {
                szLogonName[MAX_PATH - 1] = L'\0';
                szQuotaUsedText[MAX_PATH - 1] = L'\0';
                szQuotaLimitText[MAX_PATH - 1] = L'\0';
                szQuotaThresholdText[MAX_PATH - 1] = L'\0';

                if ((dqUserInfo.QuotaUsed > dqUserInfo.QuotaThreshold) &&
                    (dqUserInfo.QuotaThreshold >= 0))
                {
                    wprintf(L"Warning ");
                }
                else
                {
                    wprintf(L"OK      ");
                }

                wprintf(L"%23s", szLogonName);
                wprintf(L"   %10s", szQuotaUsedText);
                wprintf(L"   %10s", szQuotaLimitText);
                wprintf(L"   %10s", szQuotaThresholdText);
                wprintf(L"\n");
            }
            else
            {
                szLogonName[MAX_PATH - 1] = L'\0';

                wprintf(L"Could not retrieve %s's quota information\n",
                         szLogonName);
            }
            lpDiskQuotaUser->Release();
        }
        lpEnumDiskQuotaUsers->Release();
    }
    else
    {
        ShowError(hr);
    }

    WaitForKeyPress();

    return SUCCEEDED(hr);
}

void ShowError(HRESULT hr)
{
    LPVOID lpMsgBuf;
    
    if (!FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
                  FORMAT_MESSAGE_FROM_SYSTEM     |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  hr,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPWSTR) &lpMsgBuf,
                  0,
                  NULL ))
    {
        wprintf(L"Unknown error occured\n");
        return;
    }

    wprintf(L"\n%s", (LPCWSTR)lpMsgBuf);

    LocalFree( lpMsgBuf );

    WaitForKeyPress();
}

void LfcrToNull(LPWSTR szString)
{
    WCHAR* szLfcr;

    szLfcr = wcsstr(szString, L"\r\n");

    if (szLfcr) *szLfcr = '\0';
}

void WaitForKeyPress()
{
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD sInputRecord;
    DWORD        dwInputEvents;

    wprintf(L"\nPress any key to continue: ");
    ReadConsoleInput(hStdIn,&sInputRecord,1 ,&dwInputEvents);
    while (!((sInputRecord.EventType == KEY_EVENT) &&             (sInputRecord.Event.KeyEvent.bKeyDown)))
    {
        FlushConsoleInputBuffer(hStdIn);

        ReadConsoleInput(hStdIn,&sInputRecord,1 ,&dwInputEvents);
    }
}
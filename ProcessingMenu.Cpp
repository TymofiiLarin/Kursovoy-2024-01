

#include <stdio.h>
#include <windows.h>
#include <dskquota.h>
#include <clocale>
#include <cwctype>
#include <string>

#include "ProcessingMenu.h"
#include "ShowMenu.h"
#include "CommandList.h"


BOOL ProcessingMainMenu(WCHAR wcMenuChoice, IDiskQuotaControl* lpDiskQuotaControl)
{
    switch (std::towlower(wcMenuChoice))
    {

    case 'a':
        while (ProcessingQuotaManagerMenu(ShowQuotaManagerMenu(),
                                       lpDiskQuotaControl));
        break;
    case 'b':
        while (ProcessingUserManagerMenu(ShowUserManagerMenu(),
                                      lpDiskQuotaControl));
        break;
    case 'c':
        return FALSE;
        break;
    default:
        wprintf(L"\n\nInvalid selection.\n");
        break;
    }

    return TRUE;
}


BOOL ProcessingUserManagerMenu(WCHAR wcMenuChoice,
                            IDiskQuotaControl* lpDiskQuotaControl)
{
    DWORD dwQuotaLogFlags = 0;
    lpDiskQuotaControl->GetQuotaLogFlags(&dwQuotaLogFlags);

    switch (std::towlower(wcMenuChoice))
    {
    case 'a':
        AddUser(lpDiskQuotaControl);
        break;
    case 'b':
        DeleteUser(lpDiskQuotaControl);
        break;
    case 'c':
        EnumerateUsers(lpDiskQuotaControl);
        break;
    case 'd':
        return FALSE;
        break;
    default:
        wprintf(L"\n\nInvalid selection.\n");
        break;
    }

    return TRUE;
}


BOOL ProcessingQuotaManagerMenu(WCHAR wcMenuChoice,
                             IDiskQuotaControl* lpDiskQuotaControl)
{
    switch(wcMenuChoice)
    {

    case 'a':
        EnumerateUserQuotas(lpDiskQuotaControl);
        break;
    case 'b':
        SetUserHardLimit(lpDiskQuotaControl);
        break;
    case 'c':
        SetUserThreshold(lpDiskQuotaControl);
        break;
    case 'd':
        return FALSE;
        break;
    default:
        wprintf(L"\n\nInvalid selection.\n");
        break;
    }

    return TRUE;
}

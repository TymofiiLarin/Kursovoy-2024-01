
#include <windows.h>
#include <stdio.h>
#define INITGUIDS
#include <dskquota.h>
#include "ProcessingMenu.h"
#include "ShowMenu.h"
#include "CommandList.h"

extern "C"
int wmain(int argc, WCHAR* argv[])
{
    HRESULT hr;

    if (argc != 2)
        {
        wprintf(L"\nUsage: %s <Path of Root Directory>\n", argv[0]);
        return 0;
    }

    hr = CoInitialize(NULL);

    if (SUCCEEDED(hr))
    {
        IDiskQuotaControl* lpDiskQuotaControl;

        hr = CoCreateInstance(CLSID_DiskQuotaControl,
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              IID_IDiskQuotaControl,
                              (LPVOID*)&lpDiskQuotaControl);
        if (SUCCEEDED(hr))
        {
            hr = lpDiskQuotaControl->Initialize(argv[1], TRUE);

            if (SUCCEEDED(hr))
            {
                while (ProcessingMainMenu(ShowMainMenu(), lpDiskQuotaControl));
            }

            lpDiskQuotaControl->Release();
        }
        CoUninitialize();
    }

    if (FAILED(hr)) ShowError(hr);

    return SUCCEEDED(hr) ? 1 : 0;
}

/*----------------------------------------------------------------------------
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.

Copyright (C) 1999 - 2000.  Microsoft Corporation.  All rights reserved.


ProcessingMenu.h

Description:
Prototypes for functions used to process menu selections
----------------------------------------------------------------------------*/

#if !defined (_PROCESS_MENU_H_)
#define _PROCESS_MENU_H_

BOOL ProcessingMainMenu(WCHAR wcMenuChoice, IDiskQuotaControl* lpDiskQuotaControl);

BOOL ProcessingUserManagerMenu(WCHAR wcMenuChoice, IDiskQuotaControl* lpDiskQuotaControl);
BOOL ProcessingQuotaManagerMenu(WCHAR wcMenuChoice, IDiskQuotaControl* lpDiskQuotaControl);

#endif 
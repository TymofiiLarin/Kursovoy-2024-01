
#if !defined (_COMMANDS_H_)
#define _COMMANDS_H_

BOOL GetDefaultHardLimit(IDiskQuotaControl* lpDiskQuotaControl);
BOOL SetDefaultHardLimit(IDiskQuotaControl* lpDiskQuotaControl);
BOOL SetUserHardLimit(IDiskQuotaControl* lpDiskQuotaControl);
BOOL GetUserQuotaInfo(IDiskQuotaControl* lpDiskQuotaControl);
BOOL AddUser(IDiskQuotaControl* lpDiskQuotaControl);
BOOL DeleteUser(IDiskQuotaControl* lpDiskQuotaControl);
BOOL EnumerateUsers(IDiskQuotaControl* lpDiskQuotaControl);
BOOL EnumerateUserQuotas(IDiskQuotaControl* lpDiskQuotaControl);
BOOL SetUserThreshold(IDiskQuotaControl* lpDiskQuotaControl);

void ShowError(HRESULT hr);
void LfcrToNull(LPWSTR szString);

#endif 
#include <Windows.h>
#include <wchar.h>

VOID ShowError(DWORD errId)
{
	DWORD flags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS;

	LPWSTR errMsg;

	if (!FormatMessageW(flags, 0, errId, 0, (LPWSTR)&errMsg, 0, NULL))
	{
		fwprintf(stderr, L"\nCould not show error message, code: %lu", GetLastError());

	}

	wprintf(L"%s", errMsg);
	LocalFree(errMsg);
}

int wmain(int argc, WCHAR * argv[])
{
	//GetVolumeInformationW
	BOOL volInfor;
	LPCWSTR rootPath = L"D:\\";
	WCHAR volName[MAX_PATH+1];
	DWORD volumeNameSize = MAX_PATH + 1;
	DWORD volSerialNumber;
	WCHAR fileSystem[MAX_PATH+1];
	DWORD fileSystemSize = MAX_PATH + 1;

	//GetVolumeNameForVolumeMountPoint
	BOOL volumeName;
	WCHAR volumeGuid[50];
	DWORD sizeOfGuid = 50;

	if (argc != 2)
	{
		fwprintf(stderr, L"\nUsage: %s [DriveLetter]\n", argv[0]);
		return FALSE;
	}

	volumeName = GetVolumeNameForVolumeMountPointW(argv[1], volumeGuid, sizeOfGuid);

	if (!volumeName)
	{
		fwprintf(stderr, L"\nError getting volume GUID, code: ");
		ShowError(GetLastError());
		return FALSE;
	}
	
	//Here we get all the volume info, except for volume GUID path
	volInfor = GetVolumeInformationW(argv[1], volName, volumeNameSize, &volSerialNumber, NULL, NULL, fileSystem, fileSystemSize);

	if (!volInfor)
	{
		fwprintf(stderr, L"\nError getting volume info, code: ");
		ShowError(GetLastError());
		return FALSE;
	}

	wprintf(L"\nVolume GUID path: %s\n", volumeGuid);
	wprintf(L"\nVolume label: %s\n", volName);
	wprintf(L"\nFile system: %s\n", fileSystem);
	wprintf(L"\nSerial number: %lu\n", volSerialNumber);

	return 0;
}
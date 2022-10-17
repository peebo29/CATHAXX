#include "lib/Helpers.hpp"
#include "resource.h"

#include <Windows.h>
#include <ctime>
#include <filesystem>
#include <fstream>

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR cmdLine, int showCmd)
{
	wchar_t tempPath[MAX_PATH];
	std::size_t charCount = GetTempPath(MAX_PATH, tempPath);

	for (const auto &entry : std::filesystem::directory_iterator(tempPath))
	{
		if (entry.is_regular_file() && !Helpers::fileInUse(entry.path()) && entry.path().filename().wstring().ends_with(L"-MEOWENGINE-tmp.dll"))
			std::filesystem::remove(entry.path());
	}

	const auto csgoPid = Helpers::findPid(L"csgo.exe");
	if (!csgoPid)
		MessageBoxA(0, "Failed to load MEOWENGINE.\nYou need to run CS:GO before running the loader.", "MEOWENGINE", MB_OK | MB_ICONERROR);
	else
	{
		auto csgoProcess = OpenProcess(PROCESS_ALL_ACCESS, false, csgoPid);
		if (!csgoProcess)
			MessageBoxA(0, "Failed to load MEOWENGINE.\nFailed to open CS:GO process. Try running MEOWENGINE INSTALLER with administrator privileges.", "MEOWENGINE", MB_OK | MB_ICONERROR);
		else
		{
			if (!Helpers::bypassCsgoInject(csgoProcess))
				MessageBoxA(0, "Failed to load MEOWENGINE.\nFailed to bypass CS:GO library inject protection.", "MEOWENGINE", MB_OK | MB_ICONERROR);
			else
			{
				wchar_t tempFilePath[MAX_PATH];
				std::srand(static_cast<int>(std::time(nullptr)));
				std::swprintf(tempFilePath, MAX_PATH, L"%ls\\%i-MEOWENGINE-tmp.dll", tempPath, std::rand());

				std::ofstream tempFile{tempFilePath, std::ios::binary | std::ios::out};
				if (tempFile.is_open())
				{
					std::size_t size;
					const auto resource = Helpers::loadFromResource(&size);
					const void *dllData = LockResource(resource);

					tempFile.write(reinterpret_cast<const char *>(dllData), size);
					tempFile.close();

					std::uintptr_t dllModuleHandle = 0;
					if (!Helpers::loadLibreryRemote(csgoProcess, tempFilePath, &dllModuleHandle))
						MessageBoxA(0, "Failed to load MEOWENGINE.\nUnknown error has occured while loading library.", "MEOWENGINE", MB_OK | MB_ICONERROR);
					else
					{
						if (!dllModuleHandle)
							MessageBoxA(0, "Failed to load MEOWENGINE.\nDllMain returned false or load library failed.", "MEOWENGINE", MB_OK | MB_ICONERROR);
						else
							MessageBoxA(0, "INJECTED -- WELCOME TO V3.16", "MEOWENGINE", MB_OK | MB_ICONINFORMATION);
					}
		
					FreeResource(resource);
				} else
					MessageBoxA(0, "Failed to load MEOWENGINE.\nFailed to create temporary file.", "MEOWENGINE", MB_OK | MB_ICONERROR);
			}

			CloseHandle(csgoProcess);
		}
	}

	return TRUE;
}

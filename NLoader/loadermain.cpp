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
		if (entry.is_regular_file() && !Helpers::fileInUse(entry.path()) && entry.path().filename().wstring().ends_with(L"-MeowEngine-tmp.dll"))
			std::filesystem::remove(entry.path());
	}

	const auto csgoPid = Helpers::findPid(L"csgo.exe");
	if (!csgoPid)
		MessageBoxA(0, "Failed to load MeowEngine.\nYou need to run CS:GO before running the loader.", "MeowEngine", MB_OK | MB_ICONERROR);
	else
	{
		auto csgoProcess = OpenProcess(PROCESS_ALL_ACCESS, false, csgoPid);
		if (!csgoProcess)
			MessageBoxA(0, "Failed to load MeowEngine.\nFailed to open CS:GO process. Try running MeowEngineLoader with administrator privileges.", "MeowEngine", MB_OK | MB_ICONERROR);
		else
		{
			if (!Helpers::bypassCsgoInject(csgoProcess))
				MessageBoxA(0, "Failed to load MeowEngine.\nFailed to bypass CS:GO library inject protection.", "MeowEngine", MB_OK | MB_ICONERROR);
			else
			{
				wchar_t tempFilePath[MAX_PATH];
				std::srand(static_cast<int>(std::time(nullptr)));
				std::swprintf(tempFilePath, MAX_PATH, L"%ls\\%i-MeowEngine-tmp.dll", tempPath, std::rand());

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
						MessageBoxA(0, "Failed to load MeowEngine.\nUnknown error has occured while loading library.", "MeowEngine", MB_OK | MB_ICONERROR);
					else
					{
						if (!dllModuleHandle)
							MessageBoxA(0, "Failed to load MeowEngine.\nDllMain returned false or load library failed.", "MeowEngine", MB_OK | MB_ICONERROR);
						else
							MessageBoxA(0, "Success! MeowEngine is now loaded.", "MeowEngine", MB_OK | MB_ICONINFORMATION);
					}
		
					FreeResource(resource);
				} else
					MessageBoxA(0, "Failed to load MeowEngine.\nFailed to create temporary file.", "MeowEngine", MB_OK | MB_ICONERROR);
			}

			CloseHandle(csgoProcess);
		}
	}

	return TRUE;
}

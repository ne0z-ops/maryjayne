#include <Windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
//#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <Shlobj.h>
#include <KnownFolders.h>

#include "Backend/Render/render.h"
#include "Frontend/Console/console.hpp"

#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "Ntdll.lib")
#pragma comment(lib, "Shell32.lib")

//using json = nlohmann::json;

void CameraCache()
{
	for (;;)
	{
		auto camera = cmd::ReadChain<uintptr_t>(cmd::vrtxrr22, { 0xbedd6a8, 0xB8, 0x30, 0x10 });
		pointers->Matrix = cmd::read<Matrix4x4>(camera + 0x30C);
		pointers->CameraPos = cmd::read<Vector3>(camera + 0x454);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main()
{
	Monitor::Width = GetSystemMetrics(SM_CXSCREEN);
	Monitor::Height = GetSystemMetrics(SM_CYSCREEN);

	console->WriteString("Please open Rust!");
	while (values::hwnd == NULL)
	{
		values::hwnd = FindWindowA(0, ("Rust"));
	}
	console->WriteString("Found Rust Process");

	if (!cmd::AutoFind())
	{
		printf("Driver Not Found\n");
	}
	else
	{
		console->WriteString("Found driver handle");
	}

	std::string dll = "ntdll.dll";
	LPCTSTR combatproc = L"RustClient.exe";

	cmd::process_id = cmd::FProcess(combatproc);
	cmd::cache_cr3();
	cmd::vrtxrr2 = cmd::SimpleBase();
	cmd::vrtxrr22 = cmd::get_module(L"GameAssembly.dll");

	console->WriteString("Initializing Rzctl");
	if (!rzctl::init)
	{
		printf("Failed to init razer!");
	}
	console->WriteString("Finished");

	console->WriteString("Starting Camera Thread");
	std::thread(CameraCache).detach();

	if (MessageBoxW(NULL, L"Press ok once your in a server", L"Nigger.lol", MB_OKCANCEL) == IDOK)
	{
		console->WriteString("Initializing Setup");
		overlay->Init();
		data->Init();
		console->WriteString("Initializing Overlay");
		render->Init();
	}
}
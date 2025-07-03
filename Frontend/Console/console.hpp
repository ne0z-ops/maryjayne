#pragma once

#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

class console_class
{
public:
	void WriteString(std::string text);
	void BlankLine();
	void Sleep(DWORD Milliseconds);
	void SleepSeconds(DWORD Seconds);
	void BeepMJ(DWORD dwFreq, DWORD dwDuration);
	void ClearScreen();
}; inline console_class* console = new console_class();
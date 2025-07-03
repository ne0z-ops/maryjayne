#include "console.hpp"
#include "colors/color_console.h"

void console_class::WriteString(std::string text)
{
	std::cout << rang::fg::white << "[" << rang::fg::reset;
	std::cout << rang::fgB::magenta << "Rust" << rang::fg::reset;
	std::cout << rang::fg::white << "] " << rang::fg::reset;

	std::cout << text << std::endl;
}

void console_class::BlankLine()
{
	std::cout << "" << std::endl;
}

void console_class::BeepMJ(DWORD dwFreq, DWORD dwDuration)
{
	Beep(dwFreq, dwDuration);
}

void console_class::Sleep(DWORD Milliseconds)
{
	Sleep(Milliseconds);
}

void console_class::SleepSeconds(DWORD Seconds)
{
	std::this_thread::sleep_for(std::chrono::seconds(Seconds));
}

void console_class::ClearScreen()
{
	system("cls");
}
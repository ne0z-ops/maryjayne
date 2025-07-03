#include "../Cache/cache.h"
#include <string>
#include <cmath>
#include <chrono>
#include <thread>
#include <cstdlib>

#include "razer/razer/rzctl.h"

struct Functions
{
	auto FovChanger(float fov) -> void
	{
		uintptr_t kl = cmd::read<uintptr_t>(cmd::vrtxrr22 + 0xE46F558); // graphics:
		uintptr_t field = cmd::read<uintptr_t>(kl + 0xB8);

		std::uint32_t current_fov = cmd::read<std::uint32_t>(field + 0x1C0); // Read current FOV

		std::uint32_t fl_uint;
		memcpy(&fl_uint, &fov, sizeof(fl_uint));
		uintptr_t v7 = (((fl_uint ^ 0xE08DC626) - 0x3EE53B83) ^ 0x70311D82) + 0x6F409E3A;
	}
}; static Functions* functions = new Functions();

inline static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}

static const char* keyNames[] =
{

	"Keybind",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

int aimbot_key = VK_RBUTTON;
int trigger_key = VK_RBUTTON;
inline static int keystatus = 0;
inline static int realkey = 0;

inline static int keystatus1 = 0;
inline static int realkey1 = 0;

inline bool GetKey1(int key)
{
	realkey1 = key;
	return true;
}
inline void ChangeKey1(void* blank)
{
	keystatus1 = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				trigger_key = i;
				keystatus1 = 0;
				return;
			}
		}
	}

}

inline bool GetKey(int key)
{
	realkey = key;
	return true;
}
inline void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetAsyncKeyState(i) & 0x8000)
			{
				aimbot_key = i;
				keystatus = 0;
				return;
			}
		}
	}

}


inline void HotkeyButton1(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);
	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = (("Select Key"));
	else
		aimkeys = preview_value;

	if (status == 1)
	{

		aimkeys = (("Press the Key"));
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(150, 40)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}

}
inline void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);
	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = (("Select Key"));
	else
		aimkeys = preview_value;

	if (status == 1)
	{

		aimkeys = (("Press the Key"));
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(150, 40)))
	{
		if (status == 0)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

// Perlin noise function for smooth randomness
float PerlinNoise(float value) {
	return (std::sin(value * 12.9898f) * 43758.5453f) - std::floor(std::sin(value * 12.9898f) * 43758.5453f);
}



auto autoMouseMove(float x, float y) {
	static Vector3 last_target(0, 0, 0);  // Add this to track last position
	Vector3 center(Monitor::Width / 2, Monitor::Height / 2, 0);
	Vector3 target(0, 0, 0);

	if (x != 0 || y != 0) {
		const float tolerance = 1.0f;

		if (x != 0) {
			float deltaX = x - center.x;
			if (std::abs(deltaX) > tolerance) {
				// Add lerp between last position and new position
				float smoothedX = deltaX / values::aimbot::smoothing_x;
				target.x = last_target.x + (smoothedX - last_target.x) * 0.5f;  // 0.5f is lerp factor, adjust as needed

				if (target.x + center.x > Monitor::Width)
					target.x = Monitor::Width - center.x;
				if (target.x + center.x < 0)
					target.x = -center.x;
			}
		}

		if (y != 0) {
			float deltaY = y - center.y;
			if (std::abs(deltaY) > tolerance) {
				// Add lerp between last position and new position
				float smoothedY = deltaY / values::aimbot::smoothing_y;
				target.y = last_target.y + (smoothedY - last_target.y) * 0.5f;  // 0.5f is lerp factor, adjust as needed

				if (target.y + center.y > Monitor::Height)
					target.y = Monitor::Height - center.y;
				if (target.y + center.y < 0)
					target.y = -center.y;
			}
		}
	}

	last_target = target;  // Store current target for next frame
	rzctl::mouse_move(target.x, target.y);
}
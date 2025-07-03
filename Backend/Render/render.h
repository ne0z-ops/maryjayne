#include "../../Frontend/Overlay/overlay.h"
#include "../../Frontend/Framework/imgui/imgui_impl_dx9.h"
#include "../../Frontend/Framework/imgui/imgui_impl_win32.h"
#include "../../Frontend/Framework/imgui/imgui_internal.h"
#include "../../Frontend/Framework/imgui/MenuFonts.h"
#include "../../Frontend/Framework/imgui/MenuControls.h"
#include "../../Frontend/Framework/imgui/MenuBackground.h"
#include "../../Frontend/Framework/imgui/icon_font.h"


LPDIRECT3DTEXTURE9 menuBg;

//ImFont* ico_0;
ImFont* ico_1;
ImFont* ubu_1;
ImFont* ubu_0;
//ImFont* ubu_2;
//ImFont* ubu_child;
DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;


std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%m/%d/%y %H:%M", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}

static int tab = 0;
static bool keybinds_visible = true;
static ImVec2 keybinds_pos(100, 100); // Initial position for keybinds

void ColorPicker(const char* name, float* color, bool alpha) {

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	ImGuiStyle* style = &ImGui::GetStyle();

	auto alphaSliderFlag = alpha ? ImGuiColorEditFlags_AlphaBar : ImGuiColorEditFlags_NoAlpha;

	ImGui::SameLine(219.f);
	ImGui::ColorEdit4(std::string{ "##" }.append(name).append(("Picker")).c_str(), color, alphaSliderFlag | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoTooltip);
}


static char inputText[256] = "";


const char* Fovtype[] = { "1", };
const char* Hitboxes[] = { "Head", "Neck", "Chest", "Pelvis"};
const char* aimtype[] = { "Mouse", };


void Aimbot() {
	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {
		InsertGroupBoxLeft("Aimbot", 400.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);
			style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0); // No border color
			const char* Fovtype[] = { "1", };
			const char* Hitboxes[] = { "Head", "Neck", "Chest", "Pelvis" };
			const char* aimtype[] = { "Mouse", }; // removed the other options cause shit was gay.

			InsertCheckbox("Enable", values::aimbot::enable);
			InsertCombo("Aimbot Type", values::aimbot::aim_type, aimtype);
			InsertCheckbox("Draw Fov", values::aimbot::drawfov);
			InsertCheckbox("Fov Outline", values::aimbot::outlined_fov);
			InsertCheckbox("Fov Automatic", values::aimbot::automatic_fov);
			InsertCombo("Fov Type", values::aimbot::fov_type, Fovtype);
			InsertCheckbox("Skip Downed", values::aimbot::ignored_downed);
			InsertCombo("Hitbox", values::aimbot::target_hitbox, Hitboxes);
			InsertSlider("Field of view", values::aimbot::aim_fov, 0.f, 500, "%1.f%");
			InsertCheckbox("Display Target", values::aimbot::display_target);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Aimbot Cover", "Aimbot");
	}

	ImGui::NextColumn(); {
		InsertGroupBoxRight("Aimbot Settings", 400.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);


			InsertCheckbox("Hitchance", values::aimbot::hitchance);
			InsertSlider("Hitchance Value", values::aimbot::hit_chance, 0.f, 100, "%1.f%");
			InsertSlider("Smoothing X", values::aimbot::smoothing_x, 5.f, 50, "%1.f%");
			InsertSlider("Smoothing Y", values::aimbot::smoothing_y, 5.f, 50, "%1.f%");
			InsertSlider("Max Distance", values::aimbot::max_distance, 0.f, 300, "%1.f%");

			ImGui::Spacing();
			ImGui::SetCursorPosX(40);
			HotkeyButton(aimbot_key, ChangeKey, keystatus);

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Aimbot Settings Cover", "Aimbot Settings");
	}
}


int weapon_tab = 0;
int test_tab = 0;

void Visuals() {
	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Player ESP", 400.f); {

			const char* BoxType[] = { "None", "2D", "Corner", "Filled" };
			const char* LineType[] = { "Bottom", "Middle", "Top" };

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);
			style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);

			InsertCombo("Box Type", values::visuals::box_type, BoxType);
			InsertCheckbox("Skeleton", values::visuals::skeleton);
			InsertCheckbox("Name", values::visuals::username);
			InsertCheckbox("Distance", values::visuals::distance);
			InsertCheckbox("Held Item", values::visuals::weapon);
			InsertCheckbox("Wounded Esp", values::visuals::show_wounded);

			InsertCheckbox("Show Scientists", values::visuals::show_scientists);
			InsertCheckbox("Show Sleepers", values::visuals::show_sleepers);
			InsertSlider("Visuals Distance ", values::visuals::maxplayerdistance, 150.f, 500.f, "%1.f%");





			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Player ESP Cover", "Player ESP");
	}
}

void Misc() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Colors", 400.f); {
			style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);

			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			ImGui::PushFont(menuFont);
			ImGui::SetCursorPosX(10);
			ImGui::SetCursorPos(ImVec2(20, 20));
			ImGui::Text(("Box Color"));
			InsertColorPicker("Box Color", values::colors::BoxVisible, true);
			ImGui::SetCursorPosX(10);
			ImGui::SetCursorPos(ImVec2(20, 40));

			ImGui::SetCursorPos(ImVec2(20, 40));
			ImGui::Text(("Username Color"));
			InsertColorPicker("Username Color", values::colors::UsernameVisible, true);
			ImGui::SetCursorPosX(10);
			ImGui::SetCursorPos(ImVec2(20, 60));

			ImGui::SetCursorPos(ImVec2(20, 60));
			ImGui::Text(("Distance Color"));
			InsertColorPicker("Distance Color", values::colors::DistanceVisible, true);
			ImGui::SetCursorPosX(10);
			ImGui::SetCursorPos(ImVec2(20, 80));

			ImGui::SetCursorPos(ImVec2(20, 80));
			ImGui::Text(("HeldItem Color"));
			InsertColorPicker("HeldItem Color", values::colors::WeaponVisible, true);
			ImGui::SetCursorPosX(10);
			ImGui::SetCursorPos(ImVec2(20, 80));

			ImGui::SetCursorPos(ImVec2(20, 100));
			ImGui::Text(("Wounded Color"));
			InsertColorPicker("Wounded Color", values::colors::wounded, true);
			ImGui::SetCursorPosX(10);
			ImGui::SetCursorPos(ImVec2(20, 100));

			ImGui::SetCursorPos(ImVec2(20, 120));
			ImGui::Text(("Skeleton Color"));
			InsertColorPicker("Skeleton Color", values::colors::SkeletonColor, true);
			ImGui::SetCursorPosX(10);
			ImGui::SetCursorPos(ImVec2(20, 120));

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxLeft("Colors Cover", "Colors");

	}
	ImGui::NextColumn(); {

		InsertGroupBoxRight("Fonts", 150.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
			ImGui::CustomSpacing(9.f);
			const char* TextStyle[] = { "(style)", "[style]", "style" };
			const char* Fonts[] = {
				"Arial", "ArialBd", "Verdana", "VerdanaBold", "ComicSans", "ComicSansBold", "Bubble",
				"Pixel", "Future", "Melted", "Glitch", "SuperHero", "Cartoon", "Fortnite", "Cod",
				"Cs2", "Rust", "Gta", "Valorant", "Gotham", "Custom"
			};
			ImGui::CustomSpacing(9.f);
			InsertCheckbox("Watermark", values::visuals::water_mark);
			InsertCheckbox("Info Tab", values::visuals::info);
			InsertCombo("Fonts", values::visuals::Font_Type, Fonts)

			style->ItemSpacing = ImVec2(0, 0);
			style->WindowPadding = ImVec2(6, 6);

		} InsertEndGroupBoxRight("Fonts Cover", "Fonts");
	}
}

void Skins() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Configs", 150.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			style->Colors[ImGuiCol_Button] = ImColor(ImGuiCol_MenuTheme);

			//ImGui::SetCursorPos(ImVec2(30, 15));
			//if (ImGui::Button("Save Config", ImVec2(200, 30)))
			//{
			//	values::saveSettings("C:\\Nigger.lol\\cfg.config");
			//}
			//ImGui::SetCursorPos(ImVec2(30, 60));
			//if (ImGui::Button("Load Config", ImVec2(200, 30)))
			//{
			//	values::LoadSettings("C:\\Nigger.lol\\cfg.config");
			//}
			//style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);


		} InsertEndGroupBoxLeft("Config Cover", "Configs");
	}

}

void fun() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		InsertGroupBoxLeft("Configs", 150.f); {



		} InsertEndGroupBoxLeft("Config Cover", "Configs");
	}

}

void playerTab() {

	ImGuiStyle* style = &ImGui::GetStyle();
	InsertSpacer("Top Spacer");

	ImGui::Columns(2, NULL, false); {

		// Left side - World Esp
		InsertGroupBoxLeft("World Esp", 400.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);

			style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0); // No border color

			ImGui::Text("Pickups");
			InsertCheckbox("Enable", values::World::enable);
			InsertCheckbox("Dropped Items", values::World::dropped);
			InsertCheckbox("Large Storage", values::World::boxes);
			InsertCheckbox("Broken Box", values::World::brokenbox);
			InsertCheckbox("Battery", values::World::batterys);
			InsertCheckbox("Corpses", values::World::corpses);
			InsertCheckbox("Turrets", values::World::turrets);
			InsertCheckbox("Traps", values::World::traps);
			InsertCheckbox("Tcs", values::World::tcs);
			InsertCheckbox("Bags", values::World::bags);
			InsertCheckbox("Generators", values::World::generators);
			InsertCheckbox("Food Box", values::World::foodbox);
			InsertCheckbox("Stone", values::World::stone);
			InsertCheckbox("Sulfur", values::World::sulfur);
			InsertCheckbox("Metal", values::World::metal);
			InsertCheckbox("Wood Pile", values::World::woodpile);

		} InsertEndGroupBoxLeft("World Visuals Cover", "World Esp");

	}

	ImGui::NextColumn(); {

		// Right side - Cheat Info
		InsertGroupBoxRight("Pickups 2", 400.f); {
			style->ItemSpacing = ImVec2(4, 2);
			style->WindowPadding = ImVec2(4, 4);
			ImGui::CustomSpacing(9.f);
			ImGui::SetCursorPosX(20);

			ImGui::Text("Pickups 2");
			InsertCheckbox("EliteCrate", values::World::EliteCrate);
			InsertCheckbox("NormalCrate", values::World::NormalCrate);
			InsertCheckbox("MilitaryCrate", values::World::MilitaryCrateEsp);
			InsertCheckbox("LootBarrel", values::World::LootBarrelEsp);
			InsertCheckbox("Furnace", values::World::FurnaceEsp);
			InsertCheckbox("SamSites", values::World::SamSiteEsp);
			InsertCheckbox("MedKit", values::World::largemedkit);
			InsertCheckbox("Shelter", values::World::ShelterEsp);
			InsertCheckbox("Locked Crate", values::World::lockedcrate);
			InsertCheckbox("Supply Drop", values::World::supplydrop);
			InsertCheckbox("Wolf Animal", values::World::wolf);
			InsertCheckbox("Boar Animal", values::World::boar);
			InsertCheckbox("Diesel Collectable", values::World::diesel);
			InsertCheckbox("Dropped Item Image", values::visuals::droppeditemsimages);
			InsertSlider("World Distance ", values::visuals::MaxLootDistance, 150.f, 1000.f, "%1.f%");

		} InsertEndGroupBoxRight("Cheat Info Cover", "Cheat Info");

	}
}


bool is_open = true;
void RenderudMenu()
{
	ImGuiStyle* style = &ImGui::GetStyle();

	// Clean styling without rounding
	style->WindowPadding = ImVec2(6, 6);
	style->WindowRounding = 0.0f;
	style->ChildRounding = 0.0f;
	style->PopupRounding = 0.0f;
	style->FrameRounding = 0.0f;
	style->ScrollbarSize = 2.f;
	style->ScrollbarRounding = 0.f;
	style->GrabMinSize = 8.f;
	style->GrabRounding = 0.f;
	style->ItemSpacing = ImVec2(4, 2);
	style->ItemInnerSpacing = ImVec2(2, 2);
	style->FramePadding = ImVec2(4, 3);

	ImGui::PushFont(menuFont);
	ImGui::StyleColorsDark(style);

	const ImVec4 bgColor = ImVec4(18 / 255.f, 18 / 255.f, 18 / 255.f, 1.0f);
	const ImVec4 accentColor = ImVec4(34 / 255.f, 139 / 255.f, 34 / 255.f, 1.0f);
	const ImVec4 lightAccent = ImVec4(50 / 255.f, 205 / 255.f, 50 / 255.f, 1.0f);
	const ImVec4 darkAccent = ImVec4(0 / 255.f, 128 / 255.f, 0 / 255.f, 1.0f);
	const ImVec4 elementBg = ImVec4(24 / 255.f, 24 / 255.f, 24 / 255.f, 1.0f);
	const ImVec4 elementHovered = ImVec4(34 / 255.f, 139 / 255.f, 34 / 255.f, 0.5f);
	const ImVec4 elementActive = ImVec4(34 / 255.f, 139 / 255.f, 34 / 255.f, 1.0f);

	style->Colors[ImGuiCol_WindowBg] = bgColor;
	style->Colors[ImGuiCol_ChildBg] = bgColor;
	style->Colors[ImGuiCol_Border] = ImVec4(45 / 255.f, 45 / 255.f, 45 / 255.f, 1.0f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
	style->Colors[ImGuiCol_Button] = elementBg;
	style->Colors[ImGuiCol_ButtonHovered] = elementHovered;
	style->Colors[ImGuiCol_ButtonActive] = elementActive;
	style->Colors[ImGuiCol_FrameBg] = elementBg;
	style->Colors[ImGuiCol_FrameBgHovered] = elementHovered;
	style->Colors[ImGuiCol_FrameBgActive] = elementActive;
	style->Colors[ImGuiCol_CheckMark] = accentColor;
	style->Colors[ImGuiCol_SliderGrab] = accentColor;
	style->Colors[ImGuiCol_SliderGrabActive] = lightAccent;
	style->Colors[ImGuiCol_Header] = accentColor;
	style->Colors[ImGuiCol_HeaderHovered] = lightAccent;
	style->Colors[ImGuiCol_HeaderActive] = darkAccent;
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(accentColor.x, accentColor.y, accentColor.z, 0.4f);
	style->Colors[ImGuiCol_TitleBg] = bgColor;
	style->Colors[ImGuiCol_TitleBgActive] = bgColor;
	style->Colors[ImGuiCol_TitleBgCollapsed] = bgColor;

	if (values::menu::is_open)
	{
		ImGui::SetNextWindowSize(ImVec2(600.f, 500.f));
		ImGui::Begin("Nigger.lol", &is_open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		{
			ImGui::GetWindowDrawList()->AddRectFilled(
				ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y + 2),
				ImVec2(ImGui::GetWindowPos().x + ImGui::GetWindowWidth(), ImGui::GetWindowPos().y + 4),
				ImGui::ColorConvertFloat4ToU32(accentColor)
			);

			ImGui::BeginChild("##TabBar", ImVec2(ImGui::GetWindowWidth() - 16, 26), true);
			{
				float tabWidth = (ImGui::GetWindowWidth() - 25) / 6;
				ImGui::SetCursorPosY(4);
				ImGui::SetCursorPosX(4);

				auto DrawTab = [&](const char* label, int tabIndex) {
					if (tab == tabIndex) {
						ImGui::PushStyleColor(ImGuiCol_Button, accentColor);
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, lightAccent);
						ImGui::PushStyleColor(ImGuiCol_ButtonActive, darkAccent);
					}
					
					bool clicked = ImGui::Button(label, ImVec2(tabWidth, 18));
					
					if (tab == tabIndex)
						ImGui::PopStyleColor(3);
					
					if (clicked)
						tab = tabIndex;

					ImGui::SameLine();
				};

				DrawTab("Rage", 0);
				DrawTab("Visuals", 2);
				DrawTab("World Esp", 1);
				DrawTab("Settings", 3);
				DrawTab("Config", 4);
				DrawTab("Nothing", 5);
			}
			ImGui::EndChild();
			
			switch (tab) {
				case 0:
					Aimbot();
					break;
				case 1:
					playerTab();
					break;
				case 2:
					Visuals();
					break;
				case 3:
					Misc();
					break;
				case 4:
					Skins();
					break;
				case 5:
					fun();
					break;
			}
		}
		ImGui::End();
		
		ImVec2 mainPos = ImGui::GetWindowPos();
		ImVec2 mainSize = ImGui::GetWindowSize();
		
		if (keybinds_pos.x == 100 && keybinds_pos.y == 100) {
			keybinds_pos = ImVec2(mainPos.x + mainSize.x + 10, mainPos.y + 200);
		}
	}
	
	if (values::visuals::info)
	{
		if (keybinds_visible) {
			ImGui::SetNextWindowPos(keybinds_pos, ImGuiCond_FirstUseEver);
			ImGui::SetNextWindowSize(ImVec2(160, 120));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 6));

			ImGui::Begin("Keybinds", &keybinds_visible, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
			{
				keybinds_pos = ImGui::GetWindowPos();

				ImGui::TextColored(accentColor, "Keybinds");
				ImGui::Separator();
				ImGui::Spacing();

				if (values::visuals::username) {
					ImGui::Text("Name ESP: ON");
				}

				if (values::visuals::distance) {
					ImGui::Text("Distance ESP: ON");
				}

				if (values::aimbot::aim_type == 0 && values::aimbot::enable && GetAsyncKeyState(aimbot_key)) {
					ImGui::Text("Aimbot: ON");
				}
			}
			ImGui::End();
			ImGui::PopStyleVar();
		}
	}
	
	ImGui::PopFont();
}

void Shutdown() {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
}

void CreateStyle()
{
	auto& style = ImGui::GetStyle();
	auto& color = style.Colors;
	style.FrameRounding = 0;
	style.WindowBorderSize = 0;
	style.ScrollbarRounding = 0;
	style.ScrollbarSize = 5;
}

inline void DrawMenu() {
	if (GetAsyncKeyState(VK_INSERT)) {
		values::menu::is_open = !values::menu::is_open;
		Sleep(300);
	}

	RECT screen_rect;
	::GetWindowRect(::GetDesktopWindow(), &screen_rect);
	CreateStyle();
	RenderudMenu();
}

ImFont* Custom;

struct Render
{

	auto Init() -> void
	{
		DirectX();
		Loop();
	}

	auto DirectX() -> void
	{
		if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &DirectX9Interface::p_object)))
			//exit(3);

			ZeroMemory(&DirectX9Interface::p_params, sizeof(DirectX9Interface::p_params));
		DirectX9Interface::p_params.Windowed = TRUE;
		DirectX9Interface::p_params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		DirectX9Interface::p_params.hDeviceWindow = DirectX9Interface::hijacked_hwnd;
		DirectX9Interface::p_params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		DirectX9Interface::p_params.BackBufferFormat = D3DFMT_A8R8G8B8;
		DirectX9Interface::p_params.BackBufferWidth = Monitor::Width;
		DirectX9Interface::p_params.BackBufferHeight = Monitor::Height;
		DirectX9Interface::p_params.EnableAutoDepthStencil = FALSE;
		DirectX9Interface::p_params.BackBufferCount = 1;
		DirectX9Interface::p_params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		if (FAILED(DirectX9Interface::p_object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, DirectX9Interface::hijacked_hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &DirectX9Interface::p_params, 0, &DirectX9Interface::p_device)))
		{
			DirectX9Interface::p_object->Release();
			Sleep(1000);
			//exit(1);
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		if (menuBg == nullptr)
			D3DXCreateTextureFromFileInMemoryEx(DirectX9Interface::p_device, &menuBackground, sizeof(menuBackground), 1000, 1000, D3DUSAGE_DYNAMIC, 0, D3DFMT_X8B8G8R8, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &menuBg);






		ImGui_ImplWin32_Init(DirectX9Interface::hijacked_hwnd);
		ImGui_ImplDX9_Init(DirectX9Interface::p_device);
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.Fonts->AddFontFromFileTTF(("C:\\Windows\\Fonts\\Verdana.ttf"), 13, nullptr, io.Fonts->GetGlyphRangesDefault());
		MenuFont = io.Fonts->AddFontFromFileTTF(("C:\\Windows\\Fonts\\Verdana.ttf"), 13, nullptr, io.Fonts->GetGlyphRangesDefault());

		IconFont = io.Fonts->AddFontFromMemoryTTF(&PlatformFont, sizeof PlatformFont, 20, NULL, io.Fonts->GetGlyphRangesCyrillic());

		AllFont = io.Fonts->AddFontFromFileTTF(("C:\\Users\\Maryjayne\\AppData\\Roaming\\Nigger.lol\\Fonts\\Gotham-Black.ttf"), 20, nullptr, io.Fonts->GetGlyphRangesDefault());
		Custom = io.Fonts->AddFontFromFileTTF(("C:\\Rac\\custom.ttf"), 20, nullptr, io.Fonts->GetGlyphRangesDefault());
		if (!Custom)
		{
			Custom = io.Fonts->AddFontFromFileTTF(("C:\\Rac\\custom.otf"), 20, nullptr, io.Fonts->GetGlyphRangesDefault());

		}

		menuFont = io.Fonts->AddFontFromMemoryCompressedTTF(verdana_compressed_data, verdana_compressed_size, 12, NULL, io.Fonts->GetGlyphRangesCyrillic());
		tabFont = io.Fonts->AddFontFromMemoryCompressedTTF(cherryfont_compressed_data, cherryfont_compressed_size, 40, NULL, io.Fonts->GetGlyphRangesCyrillic());
		controlFont = io.Fonts->AddFontFromMemoryCompressedTTF(comboarrow_compressed_data, comboarrow_compressed_size, 12, NULL, io.Fonts->GetGlyphRangesCyrillic());
		boldMenuFont = io.Fonts->AddFontFromMemoryCompressedTTF(verdanab_compressed_data, verdanab_compressed_size, 11, NULL, io.Fonts->GetGlyphRangesCyrillic());
		legit_icons = io.Fonts->AddFontFromMemoryTTF(legittabiocns, sizeof(legittabiocns), 30, NULL, io.Fonts->GetGlyphRangesCyrillic());

		DirectX9Interface::p_object->Release();
	}

	auto Loop() -> void
	{
		static RECT old_rc;
		RtlSecureZeroMemory(&DirectX9Interface::message, sizeof(MSG));
		while (DirectX9Interface::message.message != WM_QUIT)
		{
			if (PeekMessageA(&DirectX9Interface::message, DirectX9Interface::hijacked_hwnd, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&DirectX9Interface::message);
				DispatchMessageA(&DirectX9Interface::message);
				continue;
			}

			RECT rc;
			POINT xy;
			RtlSecureZeroMemory(&rc, sizeof(RECT));
			RtlSecureZeroMemory(&xy, sizeof(POINT));
			GetClientRect(DirectX9Interface::game_wnd, &rc);
			ClientToScreen(DirectX9Interface::game_wnd, &xy);
			rc.left = xy.x;
			rc.top = xy.y;

			ImGuiIO& io = ImGui::GetIO();
			io.ImeWindowHandle = DirectX9Interface::game_wnd;
			Monitor::Width = io.DisplaySize.x;
			Monitor::Height = io.DisplaySize.y;
			Monitor::CenterX = io.DisplaySize.x / 2;
			Monitor::CenterY = io.DisplaySize.y / 2;

			POINT p;
			GetCursorPos(&p);
			long styleProc = GetWindowLongA(DirectX9Interface::hijacked_hwnd, GWL_EXSTYLE);
			io.MousePos.x = p.x - xy.x;
			io.MousePos.y = p.y - xy.y;
			if (values::menu::is_open)
			{

				styleProc &= ~WS_EX_LAYERED;
				SetWindowLongA(DirectX9Interface::hijacked_hwnd,
					GWL_EXSTYLE, styleProc);
				SetForegroundWindow(DirectX9Interface::hijacked_hwnd);
			}
			else
			{
				styleProc |= WS_EX_LAYERED;
				SetWindowLong(DirectX9Interface::hijacked_hwnd,
					GWL_EXSTYLE, styleProc);
			}
			if (GetAsyncKeyState(0x1))
			{
				io.MouseDown[0] = true;
				io.MouseClicked[0] = true;
				io.MouseClickedPos[0].x = io.MousePos.x;
				io.MouseClickedPos[0].x = io.MousePos.y;
			}
			else
			{
				io.MouseDown[0] = false;
			}
			if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
			{
				old_rc = rc;
				DirectX9Interface::p_params.BackBufferWidth = Monitor::Width;
				DirectX9Interface::p_params.BackBufferHeight = Monitor::Height;
				SetWindowPos(DirectX9Interface::hijacked_hwnd, (HWND)0, xy.x, xy.y, Monitor::Width, Monitor::Height, SWP_NOREDRAW);
				DirectX9Interface::p_device->Reset(&DirectX9Interface::p_params);
			}

			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ColorChange();

			DrawMenu();
			ImGui::PushFont(AllFont);

			loop->Loop();
			loop->World();

			ImDrawList* draw_list = ImGui::GetForegroundDrawList();

			if (values::visuals::water_mark)
			{
				static float lastTickCount = 0;
				static int fps = 0;
				static float lastFPS = 0;
				static int frameCount = 0;
				static int minFPS = INT_MAX;
				static int maxFPS = 0;
				static float resetTimer = 0;

				float currentTickCount = ImGui::GetTime();
				frameCount++;

				if (currentTickCount - lastFPS > 0.1f)
				{
					fps = static_cast<int>(frameCount / (currentTickCount - lastFPS));
					frameCount = 0;
					lastFPS = currentTickCount;

					minFPS = (fps < minFPS) ? fps : minFPS;
					maxFPS = (fps > maxFPS) ? fps : maxFPS;

					resetTimer += 0.1f;
					if (resetTimer >= 30.0f)
					{
						minFPS = INT_MAX;
						maxFPS = 0;
						resetTimer = 0;
					}
				}

				std::string watermarkText = "Nigger.lol | FPS: " + std::to_string(fps) + " | https://discord.gg/tqgXf7Dymb";
				RenderText(watermarkText, ImVec2(10, 10), 14.0f, 0xFFFFFFFF, false);
			}

			if (values::aimbot::drawfov)
			{
				if (values::aimbot::fov_type == 0)
				{
					if (values::aimbot::outlined_fov)
					{
						draw_list->AddCircle(ImVec2(Monitor::CenterX, Monitor::CenterY), values::aimbot::aim_fov, ImColor(0, 0, 0), 50, 3.0f);

					}
					draw_list->AddCircle(ImVec2(Monitor::CenterX, Monitor::CenterY), values::aimbot::aim_fov, ImColor(ImVec4(values::colors::fovcolor[0], values::colors::fovcolor[1], values::colors::fovcolor[2], 1.0f)), 50, 1);
				}
			}

			ImGui::PopFont();
			ImGui::EndFrame();

			DirectX9Interface::p_device->SetRenderState(D3DRS_ZENABLE, false);
			DirectX9Interface::p_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			DirectX9Interface::p_device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
			DirectX9Interface::p_device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

			if (DirectX9Interface::p_device->BeginScene() >= 0)
			{
				ImGui::Render();
				ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
				DirectX9Interface::p_device->EndScene();
			}
			HRESULT result = DirectX9Interface::p_device->Present(NULL, NULL, NULL, NULL);
			if (result == D3DERR_DEVICELOST && DirectX9Interface::p_device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			{
				ImGui_ImplDX9_InvalidateDeviceObjects();
				DirectX9Interface::p_device->Reset(&DirectX9Interface::p_params);
				ImGui_ImplDX9_CreateDeviceObjects();
			}



		}
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		if (DirectX9Interface::p_device != NULL)
		{
			DirectX9Interface::p_device->EndScene();
			DirectX9Interface::p_device->Release();
		}
		if (DirectX9Interface::p_object != NULL)
		{
			DirectX9Interface::p_object->Release();
		}
		DestroyWindow(DirectX9Interface::hijacked_hwnd);
	}

}; static Render* render;
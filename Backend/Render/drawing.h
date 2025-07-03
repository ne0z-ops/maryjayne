#include <WinNls.h>
#include <string>
#include <stdio.h>
#include "../../Frontend/Framework/imgui/imgui.h" // for working.
#include <iosfwd>
#include <map>
#include <fstream>
#include <ostream>
#include <filesystem>
#include <sysinfoapi.h>
#include <Windows.h>

float color_red = 1.;
float color_green = 0;
float color_blue = 0;
float color_random = 0.0;
float color_speed = 2.0;

void ColorChange()
{
	static float Color[3];
	static DWORD Tickcount = 0;
	static DWORD Tickcheck = 0;
	ImGui::ColorConvertRGBtoHSV(color_red, color_green, color_blue, Color[0], Color[1], Color[2]);
	if (GetTickCount() - Tickcount >= 1)
	{
		if (Tickcheck != Tickcount)
		{
			Color[0] += 0.001f * color_speed;
			Tickcheck = Tickcount;
		}
		Tickcount = GetTickCount();
	}
	if (Color[0] < 0.0f) Color[0] += 1.0f;
	ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], color_red, color_green, color_blue);
}

namespace values
{

	HWND hwnd = 0;

	bool Worlddebug = 0;
	bool Playerdebug = 0;



	namespace visuals
	{
		bool enable = 1;
		bool itemlist = 0;
		bool reload_bar = 0;
		bool show_scientists = 1;
		bool show_sleepers = 0;
		bool radar = 0;
		bool droppeditemsimages = 0;
		bool show_wounded = 0;
		bool cratelocked = 0;


		bool teamate_color = 1;

		bool chams = 0;

		// HEAD
		bool head = 1;
		// SKELETON
		bool skeleton = 0;
		bool skeleton_outline = 1;
		float skeleton_thick = 2;
		float outline_skeleton_thick = 2.5f;
		// BOX
		bool box = 0;
		bool cornerbox = 0;
		bool filled_box = 0;
		int box_type = 0;
		float box_thick = 2;
		float box_outline_thick = 2.5f;
		bool box_outline = 1;
		// TEXT
		bool text_outline = 1;
		float text_size = 13;
		bool username = 1;
		bool distance = 0;
		bool platform = 0;
		bool rank = 0;
		bool icons = 0;
		bool colored_text = 0;
		bool weapon = 0;
		bool headline = 0;
		bool level = 0;
		bool kills = 0;
		bool team = 0;
		bool water_mark = 1;
		bool info = 0;
		bool stream_proof = 0;
		bool stream_proof_once = 0;
		bool old_style_top = 0;
		int text_style = 0;
		int rank_pos = 1;
		int username_pos = 1;
		int distance_pos = 0;
		float MaxLootDistance = 150.f;
		float maxplayerdistance = 300.f;
		int platform_pos = 1;
		int weapon_pos = 0;
		int level_pos = 3;
		int team_pos = 3;
		int kills_pos = 3;
		// LINES
		bool line_outline = 1;
		bool line = 0;
		int line_type = 0;
		float line_thick = 2;
		float outline_line_thick = 2.5f;
		//Aimbot visuals
		bool arrows = 0;
		bool arrows_danger = 0;
		bool arrows_safe = 0;
		bool danger_list = 0;
		bool sniper = 0;
		bool sword = 0;
		bool safe_list = 0;
		bool healing = 0;
		bool no_ammo = 0;
		std::vector<std::string> usernames = { "" };
		std::vector<std::string> roles = { "" };
		std::vector<std::string> distances = { "" };
		std::vector<std::string> usernames1 = { "" };
		std::vector<std::string> roles1 = { "" };
		std::vector<std::string> distances1 = { "" };
		// IMAGE
		bool image = 0;
		//Font
		int Font_Type = 0;


	}

	namespace World
	{
		bool enable = 0;
		bool dropped = 0;
		bool boxes = 0;
		bool batterys = 0;
		bool corpses = 0;

		bool turrets = 0;
		bool traps = 0;
		bool tcs = 0;
		bool bags = 0;
		bool generators = 0;
		bool stone = 0;
		bool sulfur = 0;
		bool brokenbox = 0;
		bool hemp = 0;
		bool metal = 0;
		bool EliteCrate = 0;
		bool NormalCrate = 0;
		bool MilitaryCrateEsp = 0;
		bool boxwooden = 0;
		bool LootBarrelEsp = 0;
		bool FurnaceEsp = 0;
		bool largemedkit = 0;
		bool LargeBoxEsp = 0;
		bool SmallBoxEsp = 0;
		bool ShelterEsp = 0;
		bool SamSiteEsp = 0;
		bool foodbox = 0;
		bool woodpile = 0;
		bool supplydrop = 0;
		bool lockedcrate = 0;
		bool diesel = 0;
		bool boar = 0;
		bool wolf = 0;

		//bool enable = 1;

		float MaxCacheDistance = 50.0f;


	}

	namespace aimbot
	{
		//aimbot
		bool enable = false;
		bool fov_changert = false;
		bool no_recoil = false;
		float norecoil_x = 5.0f;
		float norecoil_y = 5.0f;
		bool no_spread = false;
		bool no_aimcone = false;

		bool silent_aim = false;

		bool hitchance = false;

		bool visbile_check = false;
		bool display_target = false;
		bool check_flags = false;
		bool outlined_fov = false;
		inline bool automatic_fov = false;
		bool ignored_downed = false;
		bool ranadomization = false;

		int target_hitbox = 0;

		bool drawfov = true;
		bool prediction = false;
		bool weapon_configs = false;
		float aim_fov = 70;
		float fov_value = 70;

		float max_distance = 300;
		float hit_chance = 90.0f;

		float smoothing_x = 15.0f;
		float smoothing_y = 15.0f;
		int targeting_type = 0;
		int aim_type = 0;

		bool humanizationoptions[4] = { false, false, false, false };

		bool target_type[4] = { false, false, false, false };
		bool check_flags_type[2] = { false, false };

		int fov_type = 0;

	}


	namespace colors
	{
		// colors config

		float BoxVisible[4] = { 0, 1, 0.3, 1.0f };

		float UsernameVisible[4] = { 0, 1, 0.3, 1.0f };

		float DistanceVisible[4] = { 0, 1, 0.3, 1.0f };

		float WeaponVisible[4] = { 0, 1, 0.3, 1.0f };

		float woundedregular[4] = { 0, 1, 0.3, 1.0f };

		float wounded[4] = { 255, 0, 0, 1.0f }; // just draws red when there wounded

		float ScientistsVisible[4] = { 0, 1, 0.3, 1.0f };

		float SkeletonColor[4] = { 0, 1, 0.3, 1.0f };

		float fovcolor[4] = { 0, 0.8, 1, 1.0f };

		float color_speed = 2.0;

		bool rainbow = 0;

		float color_red = 1.;
		float color_green = 0;
		float color_blue = 0;



	}
	namespace radar // this is not in cheat but is in the works.
	{
		// radar  config
		bool enable = 1;
		bool minimap = 0;
		bool name = 1;
		bool distance = 1;
		float radar_position_x = 10.0f;
		float radar_position_y = 15.0f;
		float radar_size = 250.0f;
		float radar_distabce = 30;

	}

	namespace menu
	{
		bool is_open = 1;
	}
};

ImFont* IconFont;
ImFont* MenuFont;
ImFont* AllFont;

inline std::wstring MBytesToWString(const char* lpcszString)
{
	int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, NULL, 0);
	if (unicodeLen == 0) return L""; // Handle error

	std::wstring wString(unicodeLen, 0);
	MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, &wString[0], unicodeLen);

	return wString;
}


inline std::string WStringToUTF8(const std::wstring& wString)
{
	int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wString.c_str(), -1, NULL, 0, NULL, NULL);
	if (utf8Len == 0) return ""; // Handle error

	std::string utf8String(utf8Len, 0);
	WideCharToMultiByte(CP_UTF8, 0, wString.c_str(), -1, &utf8String[0], utf8Len, NULL, NULL);

	return utf8String;
}

#include <unordered_map>

namespace fs = std::filesystem;

// Add this line to define the texture cache
std::unordered_map<std::string, LPDIRECT3DTEXTURE9> textureCache;

std::string Path = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Rust\\Bundles\\items";

// Find PNG file
std::vector<uint8_t> FindPng(const std::string& ItemName) {
	fs::path filePath = fs::path(Path) / (ItemName + ".png");
	std::ifstream file(filePath, std::ios::binary | std::ios::ate);
	if (!file.is_open()) return {};

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<uint8_t> data(size);
	if (!file.read(reinterpret_cast<char*>(data.data()), size)) {
		return {}; // Read failed
	}
	return data;
}

// Add these helper functions at the top of the file
void SafeReleaseTexture(LPDIRECT3DTEXTURE9& texture) {
    if (texture) {
        texture->Release();
        texture = nullptr;
    }
}

bool IsTextureValid(LPDIRECT3DTEXTURE9 texture) {
    if (!texture) return false;
    D3DSURFACE_DESC desc;
    return SUCCEEDED(texture->GetLevelDesc(0, &desc));
}

// Main texture loading function
std::vector<LPDIRECT3DTEXTURE9> LoadTextures(LPDIRECT3DDEVICE9 pDevice, const std::vector<std::string>& itemNames) {
    std::vector<LPDIRECT3DTEXTURE9> textures;
    
    // Validate input parameters
    if (!pDevice || itemNames.empty()) {
        return textures;
    }

    textures.reserve(itemNames.size());

    for (const auto& itemName : itemNames) {
        // Skip empty names
        if (itemName.empty()) {
            textures.push_back(nullptr);
            continue;
        }

        // Check cache first
        auto it = textureCache.find(itemName);
        if (it != textureCache.end() && IsTextureValid(it->second)) {
            textures.push_back(it->second);
            continue;
        }

        // If texture wasn't in cache or was invalid, load it
        try {
            std::vector<uint8_t> imageData = FindPng(itemName);
            if (imageData.empty()) {
                textures.push_back(nullptr);
                continue;
            }

            LPDIRECT3DTEXTURE9 texture = nullptr;
            HRESULT hr = D3DXCreateTextureFromFileInMemory(
                pDevice,
                imageData.data(),
                imageData.size(),
                &texture
            );

            if (SUCCEEDED(hr) && texture) {
                // Remove old texture from cache if it exists
                if (it != textureCache.end()) {
                    SafeReleaseTexture(it->second);
                }
                
                // Store in cache and add to return vector
                textureCache[itemName] = texture;
                textures.push_back(texture);
            } else {
                textures.push_back(nullptr);
            }
        }
        catch (...) {
            // If anything goes wrong, push nullptr
            textures.push_back(nullptr);
        }
    }

    return textures;
}

// Add this cleanup function to be called when shutting down
void CleanupTextureCache() {
    for (auto& pair : textureCache) {
        SafeReleaseTexture(pair.second);
    }
    textureCache.clear();
}

// Single texture loading function
LPDIRECT3DTEXTURE9 LoadTexture(LPDIRECT3DDEVICE9 pDevice, const std::string& itemName) {
    if (!pDevice || itemName.empty()) {
        return nullptr;
    }

    // Check cache first
    auto it = textureCache.find(itemName);
    if (it != textureCache.end() && IsTextureValid(it->second)) {
        return it->second;
    }

    try {
        std::vector<uint8_t> imageData = FindPng(itemName);
        if (imageData.empty()) {
            return nullptr;
        }

        LPDIRECT3DTEXTURE9 texture = nullptr;
        HRESULT hr = D3DXCreateTextureFromFileInMemory(
            pDevice,
            imageData.data(),
            imageData.size(),
            &texture
        );

        if (SUCCEEDED(hr) && texture) {
            // Remove old texture if it exists
            if (it != textureCache.end()) {
                SafeReleaseTexture(it->second);
            }
            
            // Store in cache
            textureCache[itemName] = texture;
            return texture;
        }
    }
    catch (...) {
        // Silently fail and return nullptr
    }

    return nullptr;
}

// Draw inventory directly above player's head
void RenderInventoryAboveHead(const std::vector<LPDIRECT3DTEXTURE9>& textures, const Vector2& headPosition, float scale = 0.8f) {
	if (textures.empty()) return;

	// Use fixed dimensions for consistency
	const float boxSize = 24.0f;  // Fixed item size for above head
	const float padding = 2.0f;   // Fixed padding between items
	const float totalWidth = (textures.size() * (boxSize + padding)) - padding;

	// Calculate starting position (centered above head)
	float startX = headPosition.x - (totalWidth / 2.0f);
	float startY = headPosition.y - boxSize - 20.0f; // Fixed distance above head

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

	// Draw each item
	for (size_t i = 0; i < textures.size(); i++) {
		float itemX = startX + (i * (boxSize + padding));

		// Draw slot background with semi-transparent black
		drawList->AddRectFilled(
			ImVec2(itemX, startY),
			ImVec2(itemX + boxSize, startY + boxSize),
			IM_COL32(0, 0, 0, 150)  // More visible background
		);

		// Draw item border
		drawList->AddRect(
			ImVec2(itemX, startY),
			ImVec2(itemX + boxSize, startY + boxSize),
			IM_COL32(255, 255, 255, 100),  // White border
			0.0f,  // No rounding
			0,     // All corners
			1.0f   // Line thickness
		);

		// Draw item image if available
		if (textures[i]) {
			drawList->AddImage(
				textures[i],
				ImVec2(itemX, startY),
				ImVec2(itemX + boxSize, startY + boxSize)
			);
		}
	}
}

void RenderInventoryAboveHeadSecondary(const std::vector<LPDIRECT3DTEXTURE9>& textures, const Vector2& headPosition, float scale = 0.8f) {
	if (textures.empty()) return;

	// Use fixed dimensions for consistency
	const float boxSize = 24.0f;  // Fixed item size for above head
	const float padding = 2.0f;   // Fixed padding between items
	const float totalWidth = (textures.size() * (boxSize + padding)) - padding;

	// Calculate starting position (centered above head)
	// Position this row above the first inventory row
	float startX = headPosition.x - (totalWidth / 2.0f);
	float startY = headPosition.y - (boxSize * 2) - 24.0f; // Higher than the first row

	ImDrawList* drawList = ImGui::GetBackgroundDrawList();

	// Draw each item
	for (size_t i = 0; i < textures.size(); i++) {
		float itemX = startX + (i * (boxSize + padding));

		// Draw slot background with semi-transparent black
		drawList->AddRectFilled(
			ImVec2(itemX, startY),
			ImVec2(itemX + boxSize, startY + boxSize),
			IM_COL32(0, 0, 0, 150)  // More visible background
		);

		// Draw item border
		drawList->AddRect(
			ImVec2(itemX, startY),
			ImVec2(itemX + boxSize, startY + boxSize),
			IM_COL32(255, 255, 255, 100),  // White border
			0.0f,  // No rounding
			0,     // All corners
			1.0f   // Line thickness
		);

		// Draw item image if available
		if (textures[i]) {
			drawList->AddImage(
				textures[i],
				ImVec2(itemX, startY),
				ImVec2(itemX + boxSize, startY + boxSize)
			);
		}
	}
}

void RenderInventory(std::string Name, const std::vector<LPDIRECT3DTEXTURE9>& textures, int size, const std::string& playerName, float scale = 1.0f, bool useCustomPosition = false) {
	if (textures.empty() && !values::menu::is_open) return;

	float boxSize = 48.0f * scale;   // Item slot size
	float padding = 2.0f * scale;    // Space between items
	float spacingY = 1.5f * scale;   // Gap below black bar
	float barHeight = 12.0f * scale; // Name bar height
	float inventoryWidth = (size * (boxSize + padding)) - padding;
	float windowWidth = inventoryWidth - 2;
	float windowHeight = barHeight + spacingY + boxSize;

	// Only calculate center position if not using custom position
	if (!useCustomPosition) {
		// Calculate center position
		float centerX = Monitor::Width * 0.5f - windowWidth * 0.5f;
		float startY;

		// Set Y position based on inventory type
		if (Name == "Clothing Bar") {
			startY = 5.0f; // Top position for clothing bar
		}
		else {
			startY = 5.0f + windowHeight + 5.0f; // Position hotbar below clothing bar with small gap
		}

		ImGui::SetNextWindowPos(ImVec2(centerX, startY));
	}
	// If using custom position, the caller should have already set ImGui::SetNextWindowPos

	ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight));
	ImGui::Begin(Name.c_str(), nullptr,
		ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoMove);    // Add NoMove to prevent dragging

	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 cursorPos = ImGui::GetCursorScreenPos();
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	// Black bar background (only if player name is not empty)
	if (!playerName.empty()) {
		drawList->AddRectFilled(
			ImVec2(windowPos.x, windowPos.y),
			ImVec2(windowPos.x + windowWidth, windowPos.y + barHeight),
			IM_COL32(0, 0, 0, 255)
		);

		// Centered Player Name
		ImVec2 textSize = ImGui::CalcTextSize(playerName.c_str());
		ImGui::SetCursorPosX((windowWidth - textSize.x) * 0.5f);
		ImGui::SetCursorPosY((barHeight - textSize.y) * 0.5f);
		ImGui::Text("%s", playerName.c_str());
		ImGui::SetCursorPosY(barHeight + spacingY);
	}
	else {
		// Skip the title bar if no player name
		ImGui::SetCursorPosY(0);
	}

	ImGui::SetCursorPosX(0);

	// Draw item slots and images
	for (size_t i = 0; i < textures.size(); i++) {
		ImGui::PushID(i);

		ImVec2 boxPos = ImGui::GetCursorScreenPos();

		// Transparent white slot background
		drawList->AddRectFilled(
			ImVec2(boxPos.x, boxPos.y),
			ImVec2(boxPos.x + boxSize, boxPos.y + boxSize),
			IM_COL32(255, 255, 255, 50)
		);

		// Item Image
		if (textures[i]) {
			ImGui::Image((void*)textures[i], ImVec2(boxSize, boxSize));
		}

		if (i < textures.size() - 1)
			ImGui::SameLine();

		ImGui::PopID();
	}

	ImGui::End();
}

void DrawContainer(const std::string& title, const std::vector<std::string>& items, bool isLeftBox) {
	const float windowWidth = 245;
	const float windowHeight = 225;
	const float screenPadding = 5;
	const float windowSpacing = 5;  // Space between windows

	// Calculate positions for side by side windows
	float xPos = isLeftBox ? screenPadding : (screenPadding + windowWidth + windowSpacing);

	// Set fixed position for each window
	ImGui::SetNextWindowPos(ImVec2(xPos, 50), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_FirstUseEver);

	// Create window with no move, collapse, or resize
	ImGui::Begin(title.c_str(), nullptr,
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove);

	// Style the background
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
	ImGui::BeginChild("ItemList", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar);

	// Draw title
	ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("Inventory").x) * 0.5f);
	ImGui::Text("Content List");
	ImGui::Separator();

	// Draw items
	for (const auto& item : items) {
		if (item == "Empty") continue;

		ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize(item.c_str()).x) * 0.5f);
		ImGui::Text("%s", item.c_str());
	}

	ImGui::EndChild();
	ImGui::PopStyleColor();
	ImGui::End();
}

// Updated functions that use the common container function
void DrawBeltContents(const std::string& playerName, const std::vector<std::string>& beltItems) {
	std::string title = "Belt - " + playerName;
	DrawContainer(title, beltItems, true);  // true = left box
}

void DrawClothingContents(const std::string& playerName, const std::vector<std::string>& clothingItems) {
	std::string title = "Clothing - " + playerName;
	DrawContainer(title, clothingItems, false);  // false = right box
}

//FVector2D Lerp(const FVector2D& start, const FVector2D& end, float t) {
//	return FVector2D(start.X + t * (end.X - start.X), start.Y + t * (end.Y - start.Y));
//}
//
//// Quadratic Bézier interpolation function
//inline FVector2D QuadraticBezier(FVector2D p0, FVector2D p1, FVector2D p2, float t) {
//	float u = 1 - t;
//	return (u * u * p0) + (2 * u * t * p1) + (t * t * p2);
//}
//
//inline void BezierCurve(FVector2D ScreenPositionA, FVector2D ScreenPositionB, float Thickness, ImColor RenderColor, bool outline, int segments, float fov, float screenHeight, FVector worldPosA, FVector worldPosB) {
//	FVector2D midpoint = (ScreenPositionA + ScreenPositionB) * 0.5f;
//
//	// Calculate real-world distance between the two bones
//	FVector delta = worldPosA - worldPosB;
//	float distance = delta.length();
//
//	// Scale height dynamically using FOV & screen height
//	const float baseHeight = 9.0f;  // You can adjust this base value
//	float heightOffset = baseHeight * (screenHeight / (2.0f * distance * tanf(fov * (float)M_PI / 360.f)));
//
//	FVector2D controlPoint = midpoint + FVector2D(0, -heightOffset); // Moves control point upward
//
//	for (int i = 0; i < segments; ++i) {
//		float t1 = i / (float)segments;
//		float t2 = (i + 1) / (float)segments;
//
//		FVector2D point1 = QuadraticBezier(ScreenPositionA, controlPoint, ScreenPositionB, t1);
//		FVector2D point2 = QuadraticBezier(ScreenPositionA, controlPoint, ScreenPositionB, t2);
//
//		if (outline) {
//			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(point1.X, point1.Y), ImVec2(point2.X, point2.Y), ImColor(0, 0, 0, 255), Thickness + 1.5);
//		}
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(point1.X, point1.Y), ImVec2(point2.X, point2.Y), RenderColor, Thickness);
//	}
//}
//
//
//
//
//inline void SmoothLine(FVector2D ScreenPositionA, FVector2D ScreenPositionB, float Thickness, ImColor RenderColor, bool outline) {
//	
//
//		if (outline) {
//			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.X, ScreenPositionA.Y), ImVec2(ScreenPositionB.X, ScreenPositionB.Y), ImColor(0, 0, 0, 255), Thickness + 1.5);
//		}
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(ScreenPositionA.X, ScreenPositionA.Y), ImVec2(ScreenPositionB.X, ScreenPositionB.Y), RenderColor, Thickness);
//	
//}
//
//void Box(const ImVec2 Min, const ImVec2 Max, ImColor color, float thickness, bool outline)
//{
//	if (outline)
//	{
//		ImGui::GetBackgroundDrawList()->AddRect(Min, Max, ImColor(0, 0, 0), 0.0f, 0, thickness + 1.5f);
//
//	}
//	ImGui::GetBackgroundDrawList()->AddRect(Min, Max, color, 0.0f, 0, thickness);
//}
//
//void Fill(int x, int y, int w, int h, ImColor color) {
//	color.Value.w = 75.0f / 255.0f;
//
//	ImDrawList* Drawlist = ImGui::GetBackgroundDrawList();
//
//	Drawlist->AddRectFilled(
//		ImVec2(x, y),
//		ImVec2(x + w, y + h),
//		color
//	);
//}
//
//
//void Corner(int x, int y, int w, int h, ImColor color, float thickness, bool outline) {
//
//	if (outline)
//	{
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + (h / 3)), ImColor(0, 0, 0), thickness + 1.5f);
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + (w / 3), y), ImColor(0, 0, 0), thickness + 1.5f);
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y), ImVec2(x + w, y), ImColor(0, 0, 0), thickness + 1.5f);
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + (h / 3)), ImColor(0, 0, 0), thickness + 1.5f);
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h - (h / 3)), ImVec2(x, y + h), ImColor(0, 0, 0), thickness + 1.5f);
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + (w / 3), y + h), ImColor(0, 0, 0), thickness + 1.5f);
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y + h), ImVec2(x + w, y + h), ImColor(0, 0, 0), thickness + 1.5f);
//		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y + h - (h / 3)), ImVec2(x + w, y + h), ImColor(0, 0, 0), thickness + 1.5f);
//	}
//
//	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + (h / 3)), color, thickness);
//	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + (w / 3), y), color, thickness);
//	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y), ImVec2(x + w, y), color, thickness);
//	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + (h / 3)), color, thickness);
//	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h - (h / 3)), ImVec2(x, y + h), color, thickness);
//	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + (w / 3), y + h), color, thickness);
//	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - (w / 3), y + h), ImVec2(x + w, y + h), color, thickness);
//	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y + h - (h / 3)), ImVec2(x + w, y + h), color, thickness);
//}
//
//inline void Threed(const FVector& base, const FVector& head, float width, float height, float tick, ImU32 color) {
//	// Calculate the corner points
//	FVector halfWidthOffset = { width / 2, 0, 0 };
//	FVector halfHeightOffset = { 0, height / 2, 0 };
//
//	FVector bottom1 = { base.X - halfWidthOffset.X, base.Y - halfHeightOffset.Y, base.Z };
//	FVector bottom2 = { base.X + halfWidthOffset.X, base.Y - halfHeightOffset.Y, base.Z };
//	FVector bottom3 = { base.X + halfWidthOffset.X, base.Y + halfHeightOffset.Y, base.Z };
//	FVector bottom4 = { base.X - halfWidthOffset.X, base.Y + halfHeightOffset.Y, base.Z };
//
//	FVector top1 = { head.X - halfWidthOffset.X, head.Y - halfHeightOffset.Y, head.Z + 20 };
//	FVector top2 = { head.X + halfWidthOffset.X, head.Y - halfHeightOffset.Y, head.Z + 20 };
//	FVector top3 = { head.X + halfWidthOffset.X, head.Y + halfHeightOffset.Y, head.Z + 20 };
//	FVector top4 = { head.X - halfWidthOffset.X, head.Y + halfHeightOffset.Y, head.Z + 20 };
//
//	// Project the 3D world coordinates to 2D screen coordinates
//	FVector2D screenBottom1 = functions->ProjectWorldToScreen(bottom1);
//	FVector2D screenBottom2 = functions->ProjectWorldToScreen(bottom2);
//	FVector2D screenBottom3 = functions->ProjectWorldToScreen(bottom3);
//	FVector2D screenBottom4 = functions->ProjectWorldToScreen(bottom4);
//
//	FVector2D screenTop1 = functions->ProjectWorldToScreen(top1);
//	FVector2D screenTop2 = functions->ProjectWorldToScreen(top2);
//	FVector2D screenTop3 = functions->ProjectWorldToScreen(top3);
//	FVector2D screenTop4 = functions->ProjectWorldToScreen(top4);
//
//	// Draw the lines
//	auto draw_list = ImGui::GetBackgroundDrawList();
//	ImVec2 points[] = { ImVec2(screenBottom1.X, screenBottom1.Y), ImVec2(screenBottom2.X, screenBottom2.Y), ImVec2(screenBottom3.X, screenBottom3.Y), ImVec2(screenBottom4.X, screenBottom4.Y),
//						ImVec2(screenTop1.X, screenTop1.Y), ImVec2(screenTop2.X, screenTop2.Y), ImVec2(screenTop3.X, screenTop3.Y), ImVec2(screenTop4.X, screenTop4.Y) };
//
//	for (int i = 0; i < 4; i++) {
//		draw_list->AddLine(points[i], points[(i + 1) % 4], color, tick);
//		draw_list->AddLine(points[i + 4], points[(i + 1) % 4 + 4], color, tick);
//		draw_list->AddLine(points[i], points[i + 4], color, tick);
//	}
//}
//
//
//
//float RadarDistance = { 20.f };
//
//
//inline float custom_sinf(float _X) {
//	return _mm_cvtss_f32(_mm_sin_ps(_mm_set_ss(_X)));
//}
//
//inline float custom_cosf(float _X) {
//	return _mm_cvtss_f32(_mm_cos_ps(_mm_set_ss(_X)));
//}
//
//
//
//inline float custom_fabsf(float x) {
//	__m128 x_vec = _mm_set_ss(x);
//	x_vec = _mm_and_ps(x_vec, _mm_castsi128_ps(_mm_set1_epi32(0x7FFFFFFF)));
//	return _mm_cvtss_f32(x_vec);
//}
//
//
//void calc_range(float* x, float* y, float range) {
//	float AbsX = custom_fabsf(*x);
//	float AbsY = custom_fabsf(*y);
//
//	if (AbsX > range || AbsY > range) {
//		float ratio = AbsX > AbsY ? (range / AbsX) : (range / AbsY);
//
//		*x *= ratio * ((*x > 0) ? 1 : -1);
//		*y *= ratio * ((*y > 0) ? 1 : -1);
//	}
//}
//
//void CalcRadarPoint(FVector vOrigin, int& screenx, int& screeny) {
//	FVector Rotation = ViewPoint::Rotation;
//	float Yaw = Rotation.Y * static_cast<float>(M_PI) / 180.0f;
//	float DX = vOrigin.X - ViewPoint::Location.X;
//	float DY = vOrigin.Y - ViewPoint::Location.Y;
//
//	float SinYaw = custom_sinf(Yaw);
//	float MinusCosYaw = -custom_cosf(Yaw);
//
//	float x = DY * MinusCosYaw + DX * SinYaw;
//	x = -x;
//	float y = DX * MinusCosYaw - DY * SinYaw;
//
//	float Range = RadarDistance * 1000;
//
//	calc_range(&x, &y, Range);
//
//	ImVec2 DrawPos = ImVec2(values::radar::radar_position_x, values::radar::radar_position_y);
//	ImVec2 DrawSize = ImVec2(values::radar::radar_size, values::radar::radar_size);
//
//	int RadX = static_cast<int>(DrawPos.x);
//	int RadY = static_cast<int>(DrawPos.y);
//
//	float RadSizeX = DrawSize.x;
//	float RadSizeY = DrawSize.y;
//
//	int MaxX = static_cast<int>(RadSizeX + RadX - 5);
//	int MaxY = static_cast<int>(RadSizeY + RadY - 5);
//
//	screenx = RadX + static_cast<int>((RadSizeX / 2) + (x / Range * RadSizeX));
//	screeny = RadY + static_cast<int>((RadSizeY / 2) + (y / Range * RadSizeY));
//
//	screenx = std::clamp(screenx, RadX, MaxX);
//	screeny = std::clamp(screeny, RadY, MaxY);
//}
//inline float radar_circle_size = 3.0f;
//
//
//
//FVector2D RotatePoint(FVector2D radar_pos, FVector2D radar_size, FVector LocalLocation, FVector TargetLocation) {
//	float DX = TargetLocation.X - LocalLocation.X;
//	float DY = TargetLocation.Y - LocalLocation.Y;
//
//	float x = DY * -1;
//	x = -x;
//	float y = DX * -1;
//
//	float Range = 34 * 1000;
//
//	calc_range(&x, &y, Range);
//
//	int RadX = radar_pos.X;
//	int RadY = radar_pos.Y;
//
//	float RadSizeX = radar_size.X;
//	float RadSizeY = radar_size.Y;
//
//	int MaxX = RadSizeX + RadX - 5;
//	int MaxY = RadSizeY + RadY - 5;
//
//	FVector2D ReturnValue = FVector2D();
//
//	ReturnValue.X = RadX + (RadSizeX / 2) + (x / Range * RadSizeX);
//	ReturnValue.Y = RadY + (RadSizeY / 2) + (y / Range * RadSizeY);
//
//	ReturnValue.X = std::clamp(static_cast<int>(ReturnValue.X), RadX, MaxX);
//	ReturnValue.Y = std::clamp(static_cast<int>(ReturnValue.Y), RadY, MaxY);
//
//	return ReturnValue;
//}
//inline 	IDirect3DTexture9* menuBg;
//
//void CalcArrowPosition(FVector enemyPos, int& arrowX, int& arrowY, float& arrowAngle) {
//	FVector Rotation = ViewPoint::Rotation;
//	float Yaw = Rotation.Y * static_cast<float>(M_PI) / 180.0f;
//	float DX = enemyPos.X - ViewPoint::Location.X;
//	float DY = enemyPos.Y - ViewPoint::Location.Y;
//
//	float SinYaw = custom_sinf(Yaw);
//	float MinusCosYaw = -custom_cosf(Yaw);
//
//	float x = DY * MinusCosYaw + DX * SinYaw;
//	x = -x;
//	float y = DX * MinusCosYaw - DY * SinYaw;
//
//	float dist = std::sqrt(x * x + y * y);
//
//	// Center of screen
//	ImVec2 ScreenCenter = ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2);
//	float RadarRadius = values::aimbot::aim_fov * 1.1;  // Size of your FOV circle
//
//	if (dist > RadarRadius) {
//		// Normalize and scale to radar edge
//		float scale = RadarRadius / dist;
//		x *= scale;
//		y *= scale;
//	}
//
//	// Convert to screen coordinates
//	arrowX = static_cast<int>(ScreenCenter.x + x);
//	arrowY = static_cast<int>(ScreenCenter.y + y);
//
//	// Calculate angle for arrow direction
//	arrowAngle = std::atan2(y, x);
//}
//
//
//void add_to_minimap(FVector WorldLocation, FVector LocalLocation, ImColor Color, FVector2D RadarPos, FVector2D RadarSize, float Distance) {
//	FVector2D Screen = RotatePoint(RadarPos, RadarSize, LocalLocation, WorldLocation);
//
//
//	ImGui::GetBackgroundDrawList()->AddCircleFilled(ImVec2(Screen.X, Screen.Y), radar_circle_size, Color, 12);
//}
//
//
//
//void fortnite_radar(float x, float y, float size, bool rect = false)
//{
//	if (values::radar::enable && !values::radar::minimap)
//	{
//		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
//		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize, ImGuiCond_Once);
//		static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
//		ImGui::Begin(S("##radar"), nullptr, flags);
//
//		float render_size = 5;
//		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
//
//		drawList->AddRectFilled(ImVec2(x, y), ImVec2(x + size, y + size), ImColor(20, 20, 20, 180), 0.0f, 0);
//		drawList->AddRect(ImVec2(x, y), ImVec2(x + size, y + size), ImColor(0, 0, 0, 255), 0.0f, 0);
//
//		drawList->AddLine(ImVec2(values::radar::radar_position_x + (values::radar::radar_size / 2), values::radar::radar_position_y + (values::radar::radar_size / 2)), ImVec2(values::radar::radar_position_x, values::radar::radar_position_y), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 1.f);
//		drawList->AddLine(ImVec2(values::radar::radar_position_x + (values::radar::radar_size / 2), values::radar::radar_position_y + (values::radar::radar_size / 2)), ImVec2(values::radar::radar_position_x + values::radar::radar_size, values::radar::radar_position_y), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 1.f);
//		drawList->AddLine(ImVec2(values::radar::radar_position_x, values::radar::radar_position_y + (values::radar::radar_size / 2)), ImVec2(values::radar::radar_position_x + values::radar::radar_size, values::radar::radar_position_y + (values::radar::radar_size / 2)), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 1.f);
//		drawList->AddLine(ImVec2(values::radar::radar_position_x + (values::radar::radar_size / 2), values::radar::radar_position_y + (values::radar::radar_size / 2)), ImVec2(values::radar::radar_position_x + (values::radar::radar_size / 2), values::radar::radar_position_y), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 1.f);
//
//		drawList->AddLine(ImVec2(values::radar::radar_position_x + (values::radar::radar_size / 2), values::radar::radar_position_y + (values::radar::radar_size / 2)), ImVec2(values::radar::radar_position_x + (values::radar::radar_size / 2), values::radar::radar_position_y + values::radar::radar_size), ImGui::GetColorU32({ 0.f, 0.f, 0.f, 1.f }), 1.f);
//		drawList->AddCircleFilled(ImVec2(x + size / 2, y + size / 2), render_size / 2 * sqrt(2), ImGui::GetColorU32({ 1.0f, 1.0f, 1.0f, 1.0f }), 1000);
//
//		ImGui::End();
//	}
//}
//
//inline void StringText(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, std::string text, ...)
//{
//	if (bCenter)
//	{
//		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
//		x = x - textSize.x / 4;
//		y = y - textSize.y;
//	}
//	if (stroke)
//	{
//		ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//		ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//		ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//		ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//	}
//	ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x, y), ImColor(color), text.c_str());
//}
//
//inline void String(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
//{
//	va_list va_alist;
//	char buf[1024] = { 0 };
//	va_start(va_alist, pText);
//	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
//	va_end(va_alist);
//	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
//	if (bCenter)
//	{
//		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
//		x = x - textSize.x / 4;
//		y = y - textSize.y;
//	}
//	if (stroke)
//	{
//		ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//		ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//		ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//		ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//	}
//	ImGui::GetBackgroundDrawList()->AddText(AllFont, fontSize, ImVec2(x, y), ImColor(color), text.c_str());
//}
//
//
//void add_players_radar(AFortPawn* player,FVector WorldLocation, ImColor color)
//{
//	if (values::radar::enable && !values::radar::minimap)
//	{
//		static const auto flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground;
//		ImGui::Begin(S("##radar"), nullptr, flags);
//
//		int ScreenX, ScreenY = 0;
//		const auto& GetWindowDrawList = ImGui::GetBackgroundDrawList();
//		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
//
//
//
//
//		CalcRadarPoint(WorldLocation, ScreenX, ScreenY);
//
//
//
//		drawList->AddCircleFilled(ImVec2(ScreenX, ScreenY), 5, ImColor(color), 7);
//
//
//		if (values::radar::distance)
//		{
//			int dist = (int)(ViewPoint::Location.Distance(WorldLocation) / 100);
//			char distText[32];
//			snprintf(distText, sizeof(distText), S("(%dm)").d(), dist);
//
//			ImVec2 textSize = ImGui::CalcTextSize(distText);
//
//			String(values::visuals::text_size, ScreenX - textSize.x / 3, ScreenY + 6, ImColor(255, 255, 255), false, true, distText);
//		}
//
//		if (values::radar::name)
//		{
//			auto name = player->State()->Name(pointers->GameState);
//
//			ImVec2 textSize1 = ImGui::CalcTextSize(name.c_str());
//
//			String(values::visuals::text_size, ScreenX - textSize1.x / 3, ScreenY - 20, ImColor(255, 255, 255), false, true, name.c_str());
//		}
//
//
//		ImGui::End();
//	}
//}
//
//
//
//
//
//
//inline void Icon(float fontSize, int x, int y, ImColor color, bool bCenter, bool stroke, const char* pText, ...)
//{
//	va_list va_alist;
//	char buf[1024] = { 0 };
//	va_start(va_alist, pText);
//	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
//	va_end(va_alist);
//	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
//	if (bCenter)
//	{
//		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
//		x = x - textSize.x / 4;
//		y = y - textSize.y;
//	}
//	if (stroke)
//	{
//		ImGui::GetBackgroundDrawList()->AddText(IconFont, fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//		ImGui::GetBackgroundDrawList()->AddText(IconFont, fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//		ImGui::GetBackgroundDrawList()->AddText(IconFont, fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//		ImGui::GetBackgroundDrawList()->AddText(IconFont, fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
//	}
//	ImGui::GetBackgroundDrawList()->AddText(IconFont, fontSize, ImVec2(x, y), ImColor(color), text.c_str());
//}
//
//void Skeleton(Character* Mesh, int thick, ImColor color, bool outline)
//{
//	// Store world positions (FVector)
//	FVector Neck_World = Mesh->Bone(67);
//
//	FVector R_Shoulder_World = Mesh->Bone(9);
//	FVector L_Shoulder_World = Mesh->Bone(38);
//
//	FVector R_Bicep_World = Mesh->Bone(35);
//	FVector L_Bicep_World = Mesh->Bone(64);
//
//	FVector R_Elbow_World = Mesh->Bone(10);
//	FVector L_Elbow_World = Mesh->Bone(39);
//
//	FVector R_ForeArm_World = Mesh->Bone(34);
//	FVector L_ForeArm_World = Mesh->Bone(63);
//
//	FVector R_Wrist_World = Mesh->Bone(33);
//	FVector L_Wrist_World = Mesh->Bone(62);
//
//	FVector Mid_Chest_World = Mesh->Bone(7);
//	FVector Lower_Chest_World = Mesh->Bone(6);
//	FVector Bottom_Chest_World = Mesh->Bone(5);
//	FVector Over_Pelvis_World = Mesh->Bone(4);
//	FVector Right_Over_Pelvis_World = Mesh->Bone(3);
//
//	FVector Chest_World = Mesh->Bone(66);
//	FVector Pelvis_World = Mesh->Bone(2);
//	FVector R_Leg_World = Mesh->Bone(71);
//	FVector L_Leg_World = Mesh->Bone(78);
//
//	FVector R_Knee_World = Mesh->Bone(72);
//	FVector L_Knee_World = Mesh->Bone(79);
//
//	FVector R_Foot_World = Mesh->Bone(73);
//	FVector L_Foot_World = Mesh->Bone(80);
//
//	// Convert to screen positions (FVector2D)
//	FVector2D Neck = functions->ProjectWorldToScreen(Neck_World);
//
//	FVector2D R_Shoulder = functions->ProjectWorldToScreen(R_Shoulder_World);
//	FVector2D L_Shoulder = functions->ProjectWorldToScreen(L_Shoulder_World);
//
//	FVector2D R_Bicep = functions->ProjectWorldToScreen(R_Bicep_World);
//	FVector2D L_Bicep = functions->ProjectWorldToScreen(L_Bicep_World);
//
//	FVector2D R_Elbow = functions->ProjectWorldToScreen(R_Elbow_World);
//	FVector2D L_Elbow = functions->ProjectWorldToScreen(L_Elbow_World);
//
//	FVector2D R_ForeArm = functions->ProjectWorldToScreen(R_ForeArm_World);
//	FVector2D L_ForeArm = functions->ProjectWorldToScreen(L_ForeArm_World);
//
//	FVector2D R_Wrist = functions->ProjectWorldToScreen(R_Wrist_World);
//	FVector2D L_Wrist = functions->ProjectWorldToScreen(L_Wrist_World);
//
//	FVector2D Mid_Chest = functions->ProjectWorldToScreen(Mid_Chest_World);
//	FVector2D Lower_Chest = functions->ProjectWorldToScreen(Lower_Chest_World);
//	FVector2D Bottom_Chest = functions->ProjectWorldToScreen(Bottom_Chest_World);
//	FVector2D Over_Pelvis = functions->ProjectWorldToScreen(Over_Pelvis_World);
//	FVector2D Right_Over_Pelvis = functions->ProjectWorldToScreen(Right_Over_Pelvis_World);
//
//	FVector2D Chest = functions->ProjectWorldToScreen(Chest_World);
//	FVector2D Pelvis = functions->ProjectWorldToScreen(Pelvis_World);
//	FVector2D R_Leg = functions->ProjectWorldToScreen(R_Leg_World);
//	FVector2D L_Leg = functions->ProjectWorldToScreen(L_Leg_World);
//
//	FVector2D R_Knee = functions->ProjectWorldToScreen(R_Knee_World);
//	FVector2D L_Knee = functions->ProjectWorldToScreen(L_Knee_World);
//
//	FVector2D R_Foot = functions->ProjectWorldToScreen(R_Foot_World);
//	FVector2D L_Foot = functions->ProjectWorldToScreen(L_Foot_World);
//
//	// NECK
//	SmoothLine(Neck, Chest, thick, color, outline);
//	// SHOULDERS
//	SmoothLine(Chest, R_Shoulder, thick, color, outline);
//	SmoothLine(Chest, L_Shoulder, thick, color, outline);
//	// BICEPS
//	SmoothLine(R_Shoulder, R_Bicep, thick, color, outline);
//	SmoothLine(L_Shoulder, L_Bicep, thick, color, outline);
//	// ELBOWS
//	SmoothLine(R_Bicep, R_Elbow, thick, color, outline);
//	SmoothLine(L_Bicep, L_Elbow, thick, color, outline);
//	// FOREARM
//	SmoothLine(R_Elbow, R_ForeArm, thick, color, outline);
//	SmoothLine(L_Elbow, L_ForeArm, thick, color, outline);
//	// WRISTS
//	SmoothLine(R_ForeArm, R_Wrist, thick, color, outline);
//	SmoothLine(L_ForeArm, L_Wrist, thick, color, outline);
//	// CHEST
//	SmoothLine(Chest, Mid_Chest, thick, color, outline);
//	SmoothLine(Mid_Chest, Lower_Chest, thick, color, outline);
//	SmoothLine(Lower_Chest, Bottom_Chest, thick, color, outline);
//	SmoothLine(Bottom_Chest, Over_Pelvis, thick, color, outline);
//	SmoothLine(Over_Pelvis, Right_Over_Pelvis, thick, color, outline);
//	SmoothLine(Right_Over_Pelvis, Pelvis, thick, color, outline);
//	// PELVIS
//	SmoothLine(Pelvis, R_Leg, thick, color, outline);
//	SmoothLine(Pelvis, L_Leg, thick, color, outline);
//	// THIGHS
//	SmoothLine(R_Leg, R_Knee, thick, color, outline);
//	SmoothLine(L_Leg, L_Knee, thick, color, outline);
//	// FOOT
//	SmoothLine(R_Knee, R_Foot, thick, color, outline);
//	SmoothLine(L_Knee, L_Foot, thick, color, outline);
//}
//
//void RenderCustomWindow(const char* title, bool& show, const std::vector<std::string>& usernames, const std::vector<std::string>& roles, const std::vector<std::string>& distances) {
//	if (!show) return;
//
//	std::vector<std::string> validUsernames, validRoles, validDistances;
//	for (size_t i = 0; i < usernames.size(); i++) {
//		if (!usernames[i].empty()) {
//			validUsernames.push_back(usernames[i]);
//			validRoles.push_back(roles[i]);
//			validDistances.push_back(distances[i]);
//		}
//	}
//
//	int count = validUsernames.size();
//
//	float maxTextWidth = 0.0f;
//	for (int i = 0; i < count; i++) {
//		std::string combinedString = validUsernames[i] + " (" + validRoles[i] + ") (" + validDistances[i] + ")";
//		ImVec2 textSize = ImGui::CalcTextSize(combinedString.c_str());
//		maxTextWidth = max(maxTextWidth, textSize.x);
//	}
//
//	float windowWidth1 = max(maxTextWidth - 15, 235.0f); // Add padding, with a minimum width of 245
//	float windowWidth = max(maxTextWidth + 20, 245.0f); // Add padding, with a minimum width of 245
//	float windowHeight = count * 20 + 70;                   // Adjust height for title, bar, and spacing
//	ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_Always);
//
//	ImGui::Begin(title, &show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
//
//	ImVec2 windowSize = ImGui::GetWindowSize();
//
//	// Draw the background image first
//	ImGui::SetCursorPos(ImVec2(5, 5));
//	ImGui::Image(menuBg, ImVec2(windowSize.x - 10, windowSize.y - 11));
//
//	// Reset cursor position to ensure text is drawn on top
//	ImGui::SetCursorPos(ImVec2(10, 10));
//
//	// Centered window title
//	ImVec2 textSize = ImGui::CalcTextSize(title);
//	ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
//	ImGui::Text(title);
//
//	ImGui::BeginChild("BarContainer", ImVec2(ImGui::GetWindowWidth() - 10, 8), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
//
//	// Set cursor position and draw the bar
//	ImGui::SetCursorPos(ImVec2(5, 3)); // Adjust position to center the bar in the child
//	ImGui::ColorBar(S("Bar"), ImVec2(ImGui::GetWindowWidth() - 10, 2.0f)); // Use child width minus padding
//
//	// End the child window
//	ImGui::EndChild();
//
//	// Render each entry closer to the color bar
//	float textStartY = ImGui::GetCursorPosY() + 5; // Space below the bar
//	for (int i = 0; i < count; i++) {
//		std::string line = validUsernames[i] + " (" + validRoles[i] + ") (" + validDistances[i] + ")";
//		ImGui::SetCursorPos(ImVec2(10, textStartY + i * 20));
//		ImGui::Text("%s", line.c_str());
//	}
//
//	ImGui::End();
//}
//
//
//void DrawArrow(ImDrawList* drawList, ImVec2 position, float angle,
//	bool isHoldingHeal, bool isHoldingSniper, bool isHoldingSword,
//	bool arrowsDanger, bool arrowsSafe)
//{
//	// Default arrow size parameters
//	float baseArrowSize = 20; // Increased base size for better balance
//	float arrowWidth = baseArrowSize * 0.7f; // Adjusted to make the arrow more balanced
//	float arrowHeight = baseArrowSize * 1.4f; // Ensuring a balanced height for equilateral effect
//	ImColor arrowColor = ImColor(ImVec4(values::colors::accentColor[0], values::colors::accentColor[1], values::colors::accentColor[2], values::colors::accentColor[3]));
//
//	// If neither arrowsDanger nor arrowsSafe are true, render default arrow
//	if (!arrowsDanger && !arrowsSafe) {
//		ImVec2 p1 = ImVec2(position.x + arrowHeight * cos(angle), position.y + arrowHeight * sin(angle));
//		ImVec2 p2 = ImVec2(position.x + arrowWidth * cos(angle + 3.14f / 3), position.y + arrowWidth * sin(angle + 3.14f / 3));
//		ImVec2 p3 = ImVec2(position.x + arrowWidth * cos(angle - 3.14f / 3), position.y + arrowWidth * sin(angle - 3.14f / 3));
//
//		drawList->AddTriangleFilled(p1, p2, p3, arrowColor);
//		return; // Exit function early
//	}
//
//	// Select color based on player state **only if arrowsDanger or arrowsSafe are enabled**
//	if (isHoldingHeal) {
//		arrowColor = ImColor(0, 255, 0, 255);  // Green for healing
//	}
//	else if (isHoldingSniper) {
//		arrowColor = ImColor(0, 0, 255, 255);  // Blue for sniper
//	}
//	else if (isHoldingSword) {
//		arrowColor = ImColor(255, 255, 0, 255);  // Yellow for sword
//	}
//
//	
//
//	// Adjust arrow size based on text size if an icon exists
//	ImVec2 textSize = ImVec2(0, 0);
//	
//
//	// Calculate arrow points (equilateral shape)
//	ImVec2 p1 = ImVec2(position.x + arrowHeight * cos(angle), position.y + arrowHeight * sin(angle));
//	ImVec2 p2 = ImVec2(position.x + arrowWidth * cos(angle + 3.14f / 3), position.y + arrowWidth * sin(angle + 3.14f / 3));
//	ImVec2 p3 = ImVec2(position.x + arrowWidth * cos(angle - 3.14f / 3), position.y + arrowWidth * sin(angle - 3.14f / 3));
//
//	// Draw arrow
//	drawList->AddTriangleFilled(p1, p2, p3, arrowColor);
//
//}
//
//
//void DrawTargetHud(const char* title, bool show, const std::string& Username, int distance, const std::string& weapon,
//	const std::string& rank, const std::string& platform) {
//	if (!show) return;
//
//	float maxTextWidth = 0.0f;
//	std::vector<std::string> infoLines = {
//		"Username: " + Username,
//		"Distance: " + std::to_string(distance) + " meters",
//		"Weapon: " + weapon,
//		"Rank: " + rank,
//		"Platform: " + platform,
//	};
//
//	// Calculate max text width
//	for (const auto& line : infoLines) {
//		ImVec2 textSize = ImGui::CalcTextSize(line.c_str());
//		maxTextWidth = max(maxTextWidth, textSize.x);
//	}
//
//	float windowWidth = max(maxTextWidth + 25, 245.0f); // Add padding, minimum width 245
//	float windowHeight = infoLines.size() * 20 + 70;         // Adjust height for content
//	ImGui::SetNextWindowSize(ImVec2(windowWidth, windowHeight), ImGuiCond_Always);
//
//	ImGui::Begin(title, &show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
//
//	ImVec2 windowSize = ImGui::GetWindowSize();
//
//	// Draw the background image
//	ImGui::SetCursorPos(ImVec2(5, 5));
//	ImGui::Image(menuBg, ImVec2(windowSize.x - 10, windowSize.y - 11));
//
//	// Reset cursor position for text
//	ImGui::SetCursorPos(ImVec2(10, 10));
//
//	// Centered window title
//	ImVec2 textSize = ImGui::CalcTextSize(title);
//	ImGui::SetCursorPosX((windowSize.x - textSize.x) * 0.5f);
//	ImGui::Text(title);
//
//	ImGui::BeginChild("BarContainer", ImVec2(ImGui::GetWindowWidth() - 10, 8), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
//
//	// Draw the separator bar
//	ImGui::SetCursorPos(ImVec2(5, 3));
//	ImGui::ColorBar(S("Bar"), ImVec2(ImGui::GetWindowWidth() - 10, 2.0f));
//
//	ImGui::EndChild();
//
//	// Render the data entries
//	float textStartY = ImGui::GetCursorPosY() + 5; // Space below the bar
//	for (size_t i = 0; i < infoLines.size(); i++) {
//		ImGui::SetCursorPos(ImVec2(15, textStartY + i * 20));
//		ImGui::Text("%s", infoLines[i].c_str());
//	}
//
//	ImGui::End();
//}
//
//struct TextConfig {
//	std::string text;       // Text to display (ignored if isImage is true)
//	ImFont* font;           // Font for text rendering
//	float size;             // Font size for text
//	ImVec4 color;           // Text color
//	bool outline;           // Whether to draw an outline around text
//	ImVec4 outline_color;   // Outline color for text
//	bool isImage;           // Determines if this is an image instead of text
//	ImTextureID texture;    // Texture ID for image rendering
//	ImVec2 image_size;      // Size of the image
//	int position;           // 0 = below, 1 = above, 2 = left, 3 = right
//
//
//};
//
//void DrawTextWithConfig(ImDrawList* drawList, const ImVec2& box_top_left, const ImVec2& box_bottom_right, const std::vector<TextConfig>& texts, FVector2D head_pos, bool old_top_text) {
//	const float padding = 3.5f;
//	const float top_padding = 7.0f;
//	const float outline_thickness = 1.0f;
//
//	float box_width = box_bottom_right.x - box_top_left.x;
//	float box_height = box_bottom_right.y - box_top_left.y;
//
//	std::map<int, int> positionCounts = { {0, 0}, {1, 0}, {2, 0}, {3, 0} };
//
//	float max_text_height = 0.0f;
//	float total_top_text_width = 0.0f;
//	bool hasTopElements = false;
//
//	if (old_top_text) {
//		for (const auto& config : texts) {
//			if (config.position == 1) {
//				hasTopElements = true;
//				ImVec2 element_size = config.isImage ? config.image_size : config.font->CalcTextSizeA(config.size, FLT_MAX, 0.0f, config.text.c_str());
//				total_top_text_width += element_size.x + top_padding;
//				max_text_height = max(max_text_height, element_size.y);
//			}
//		}
//		if (hasTopElements) {
//			total_top_text_width -= top_padding;
//		}
//	}
//
//	float top_text_start_x = box_top_left.x + (box_width - total_top_text_width) * 0.5f;
//	float side_by_side_x_offset = 0.0f;
//
//	for (const auto& config : texts) {
//		ImVec2 element_size = config.isImage ? config.image_size : config.font->CalcTextSizeA(config.size, FLT_MAX, 0.0f, config.text.c_str());
//
//		int count = positionCounts[config.position]++;
//		float offset = count * (element_size.y + padding);
//
//		ImVec2 element_position;
//		switch (config.position) {
//		case 0:
//			element_position = ImVec2(
//				box_top_left.x + (box_width - element_size.x) * 0.5f,
//				box_bottom_right.y + padding + offset
//			);
//			break;
//		case 1:
//			if (old_top_text) {
//				element_position = ImVec2(
//					top_text_start_x + side_by_side_x_offset,
//					box_top_left.y - element_size.y - padding
//				);
//				side_by_side_x_offset += element_size.x + top_padding;
//			}
//			else {
//				element_position = ImVec2(
//					box_top_left.x + (box_width - element_size.x) * 0.5f,
//					box_top_left.y - element_size.y - padding - offset
//				);
//			}
//			break;
//		case 2:
//			element_position = ImVec2(
//				box_top_left.x - element_size.x - padding,
//				head_pos.Y + offset
//			);
//			break;
//		case 3:
//			element_position = ImVec2(
//				box_bottom_right.x + padding,
//				head_pos.Y + offset
//			);
//			break;
//		default:
//			continue;
//		}
//
//		if (config.isImage) {
//			element_position.y -= (element_size.y - max_text_height) * 0.5f;
//			drawList->AddImage(config.texture, element_position, ImVec2(element_position.x + element_size.x, element_position.y + element_size.y));
//		}
//		else {
//			if (config.outline) {
//				drawList->AddText(config.font, config.size, ImVec2(element_position.x - outline_thickness, element_position.y - outline_thickness), ImColor(config.outline_color), config.text.c_str());
//				drawList->AddText(config.font, config.size, ImVec2(element_position.x + outline_thickness, element_position.y - outline_thickness), ImColor(config.outline_color), config.text.c_str());
//				drawList->AddText(config.font, config.size, ImVec2(element_position.x - outline_thickness, element_position.y + outline_thickness), ImColor(config.outline_color), config.text.c_str());
//				drawList->AddText(config.font, config.size, ImVec2(element_position.x + outline_thickness, element_position.y + outline_thickness), ImColor(config.outline_color), config.text.c_str());
//			}
//			drawList->AddText(config.font, config.size, element_position, ImColor(config.color), config.text.c_str());
//		}
//	}
//}
//
//
//inline void DrawThreeDBoxText(const FVector& base, const FVector& head, float width, float height, float tick, ImU32 color, const char* text) {
//	// Calculate the corner points
//	FVector halfWidthOffset = { width / 2, 0, 0 };
//	FVector halfHeightOffset = { 0, height / 2, 0 };
//
//	FVector bottom1 = { base.X - halfWidthOffset.X, base.Y - halfHeightOffset.Y, base.Z };
//	FVector bottom2 = { base.X + halfWidthOffset.X, base.Y - halfHeightOffset.Y, base.Z };
//	FVector bottom3 = { base.X + halfWidthOffset.X, base.Y + halfHeightOffset.Y, base.Z };
//	FVector bottom4 = { base.X - halfWidthOffset.X, base.Y + halfHeightOffset.Y, base.Z };
//
//	FVector top1 = { head.X - halfWidthOffset.X, head.Y - halfHeightOffset.Y, head.Z + 20 };
//	FVector top2 = { head.X + halfWidthOffset.X, head.Y - halfHeightOffset.Y, head.Z + 20 };
//	FVector top3 = { head.X + halfWidthOffset.X, head.Y + halfHeightOffset.Y, head.Z + 20 };
//	FVector top4 = { head.X - halfWidthOffset.X, head.Y + halfHeightOffset.Y, head.Z + 20 };
//
//	// Project the 3D world coordinates to 2D screen coordinates
//	FVector2D screenBottom1 = functions->ProjectWorldToScreen(bottom1);
//	FVector2D screenBottom2 = functions->ProjectWorldToScreen(bottom2);
//	FVector2D screenBottom3 = functions->ProjectWorldToScreen(bottom3);
//	FVector2D screenBottom4 = functions->ProjectWorldToScreen(bottom4);
//
//	FVector2D screenTop1 = functions->ProjectWorldToScreen(top1);
//	FVector2D screenTop2 = functions->ProjectWorldToScreen(top2);
//	FVector2D screenTop3 = functions->ProjectWorldToScreen(top3);
//	FVector2D screenTop4 = functions->ProjectWorldToScreen(top4);
//
//	// Draw the lines
//	auto draw_list = ImGui::GetBackgroundDrawList();
//	ImVec2 points[] = { ImVec2(screenBottom1.X, screenBottom1.Y), ImVec2(screenBottom2.X, screenBottom2.Y), ImVec2(screenBottom3.X, screenBottom3.Y), ImVec2(screenBottom4.X, screenBottom4.Y),
//						ImVec2(screenTop1.X, screenTop1.Y), ImVec2(screenTop2.X, screenTop2.Y), ImVec2(screenTop3.X, screenTop3.Y), ImVec2(screenTop4.X, screenTop4.Y) };
//
//	FVector midBottom = {
//	  (bottom1.X + bottom2.X + bottom3.X + bottom4.X) / 4,
//	  (bottom1.Y + bottom2.Y + bottom3.Y + bottom4.Y) / 4,
//	  (bottom1.Z + bottom2.Z + bottom3.Z + bottom4.Z) / 4
//	};
//	FVector midTop = {
//		(top1.X + top2.X + top3.X + top4.X) / 4,
//		(top1.Y + top2.Y + top3.Y + top4.Y) / 4,
//		(top1.Z + top2.Z + top3.Z + top4.Z) / 4
//	};
//
//	// Project midpoints to screen coordinates
//	FVector2D screenMidBottom = functions->ProjectWorldToScreen(midBottom);
//	FVector2D screenMidTop = functions->ProjectWorldToScreen(midTop);
//
//
//	// Draw text on top of the box
//	float textVerticalOffset = -10.0f; // Adjust this value as needed
//
//	// Draw text on top of the box
//	ImVec2 textPosTop = ImVec2(screenMidTop.X, screenMidTop.Y + textVerticalOffset); // Adjust the y-coordinate
//	ImVec2 textSizeTop = ImGui::CalcTextSize(text);
//	textPosTop.x -= textSizeTop.x * 0.5f;
//	textPosTop.y -= textSizeTop.y * 0.5f;
//	//	draw_list->AddText(textPosTop, color, text);
//	String(values::visuals::text_size, textPosTop.x, textPosTop.y, color, false, values::visuals::text_outline, text);
//
//	for (int i = 0; i < 4; i++) {
//
//		if (values::visuals::box_outline)
//		{
//			draw_list->AddLine(points[i], points[(i + 1) % 4], ImColor(0, 0, 0), tick + values::visuals::box_outline_thick);
//			draw_list->AddLine(points[i + 4], points[(i + 1) % 4 + 4], ImColor(0, 0, 0), tick + values::visuals::box_outline_thick);
//			draw_list->AddLine(points[i], points[i + 4], ImColor(0, 0, 0), tick + values::visuals::box_outline_thick);
//		}
//
//		draw_list->AddLine(points[i], points[(i + 1) % 4], color, tick);
//		draw_list->AddLine(points[i + 4], points[(i + 1) % 4 + 4], color, tick);
//		draw_list->AddLine(points[i], points[i + 4], color, tick);
//	}
//
//
//
//
//}

//#include <nlohmann/json.hpp>

//// Helper function to save float[4] arrays to JSON
//void saveFloatArray(nlohmann::json& jsonSettings, const std::string& key, const float arr[4]) {
//	jsonSettings[key] = {
//		{"0", arr[0]},
//		{"1", arr[1]},
//		{"2", arr[2]},
//		{"3", arr[3]}
//	};
//}
//
//
//// Helper function to load float[4] arrays from JSON
//void loadFloatArray(const nlohmann::json& jsonSettings, const std::string& key, float arr[4]) {
//	arr[0] = jsonSettings[key]["0"];
//	arr[1] = jsonSettings[key]["1"];
//	arr[2] = jsonSettings[key]["2"];
//	arr[3] = jsonSettings[key]["3"];
//}
//
//
//
//namespace values {
//
//	// Function to save settings to a file
//	bool saveSettings(const std::string& filename) {
//		nlohmann::json jsonSettings;
//
//		// Save visuals settings
//		jsonSettings["visuals"] = {
//			{"enable", visuals::enable},
//			{"head", visuals::head},
//			{"skeleton", visuals::skeleton},
//			{"skeleton_outline", visuals::skeleton_outline},
//			{"skeleton_thick", visuals::skeleton_thick},
//			{"outline_skeleton_thick", visuals::outline_skeleton_thick},
//			{"box", visuals::box},
//			{"filled_box", visuals::filled_box},
//			{"box_type", visuals::box_type},
//			{"box_thick", visuals::box_thick},
//			{"box_outline_thick", visuals::box_outline_thick},
//			{"box_outline", visuals::box_outline},
//			{"text_outline", visuals::text_outline},
//			{"text_size", visuals::text_size},
//			{"username", visuals::username},
//			{"distance", visuals::distance},
//			{"platform", visuals::platform},
//			{"rank", visuals::rank},
//			{"icons", visuals::icons},
//			{"colored_text", visuals::colored_text},
//			{"droppeditemlogos", visuals::droppeditemsimages},
//			{"weapon", visuals::weapon},
//			{"level", visuals::level},
//			{"kills", visuals::kills},
//			{"team", visuals::team},
//			{"water_mark", visuals::water_mark},
//			{"stream_proof", visuals::stream_proof},
//			{"stream_proof_once", visuals::stream_proof_once},
//			{"old_style_top", visuals::old_style_top},
//			{"text_style", visuals::text_style},
//			{"rank_pos", visuals::rank_pos},
//			{"username_pos", visuals::username_pos},
//			{"distance_pos", visuals::distance_pos},
//			{"platform_pos", visuals::platform_pos},
//			{"weapon_pos", visuals::weapon_pos},
//			{"level_pos", visuals::level_pos},
//			{"team_pos", visuals::team_pos},
//			{"kills_pos", visuals::kills_pos},
//			{"line_outline", visuals::line_outline},
//			{"line", visuals::line},
//			{"line_type", visuals::line_type},
//			{"line_thick", visuals::line_thick},
//			{"outline_line_thick", visuals::outline_line_thick},
//			{"arrows", visuals::arrows},
//			{"arrows_danger", visuals::arrows_danger},
//			{"arrows_safe", visuals::arrows_safe},
//			{"danger_list", visuals::danger_list},
//			{"sniper", visuals::sniper},
//			{"sword", visuals::sword},
//			{"safe_list", visuals::safe_list},
//			{"healing", visuals::healing},
//			{"no_ammo", visuals::no_ammo},
//			{"image", visuals::image},
//			{"Font_Type", visuals::Font_Type}
//		};
//
//		// Save radar settings
//		jsonSettings["radar"] = {
//			{"enable", radar::enable},
//			{"minimap", radar::minimap},
//			{"name", radar::name},
//			{"distance", radar::distance},
//			{"radar_position_x", radar::radar_position_x},
//			{"radar_position_y", radar::radar_position_y},
//			{"radar_size", radar::radar_size},
//			{"radar_distabce", radar::radar_distabce}
//		};
//
//		// Save menu settings
//		jsonSettings["menu"] = {
//			{"is_open", menu::is_open}
//		};
//
//		// Save colors settings
//		// Save color settings
//		saveFloatArray(jsonSettings, "colors::BoxVisible", colors::BoxVisible);
//		saveFloatArray(jsonSettings, "colors::DistanceVisible", colors::DistanceVisible);
//		saveFloatArray(jsonSettings, "colors::WeaponVisible", colors::WeaponVisible);
//		saveFloatArray(jsonSettings, "colors::fovcolor", colors::fovcolor);
//
//		// Save other color settings
//		jsonSettings["colors"]["color_speed"] = colors::color_speed;
//		jsonSettings["colors"]["rainbow"] = colors::rainbow;
//		jsonSettings["colors"]["color_red"] = colors::color_red;
//		jsonSettings["colors"]["color_green"] = colors::color_green;
//		jsonSettings["colors"]["color_blue"] = colors::color_blue;
//
//
//		// Write to file
//		std::ofstream outFile(filename);
//		if (!outFile) {
//			std::cerr << "Error opening file for saving." << std::endl;
//			return false;
//		}
//
//		outFile << jsonSettings.dump(4); // Pretty print with indent
//		outFile.close();
//
//		return true;
//	}
//
//	bool LoadSettings(const std::string& filePath)
//	{
//		try {
//			std::ifstream file(filePath);
//			if (!file.is_open())
//			{
//				std::cerr << "Failed to open settings file for loading." << std::endl;
//				return false;
//			}
//
//			nlohmann::json jsonSettings;
//			file >> jsonSettings;
//			file.close();
//
//			// Helper function to safely get values with defaults
//			auto getValue = [](const nlohmann::json& j, const std::string& key, auto defaultValue) {
//				return j.contains(key) ? j[key].get<decltype(defaultValue)>() : defaultValue;
//			};
//
//			// Load visuals settings with validation
//			if (jsonSettings.contains("visuals")) {
//				const auto& visuals = jsonSettings["visuals"];
//				visuals::enable = getValue(visuals, "enable", true);
//				visuals::head = getValue(visuals, "head", true);
//				visuals::skeleton = getValue(visuals, "skeleton", false);
//				visuals::skeleton_outline = getValue(visuals, "skeleton_outline", true);
//				visuals::skeleton_thick = getValue(visuals, "skeleton_thick", 2.0f);
//				visuals::outline_skeleton_thick = getValue(visuals, "outline_skeleton_thick", 2.5f);
//				visuals::box = getValue(visuals, "box", false);
//				visuals::filled_box = getValue(visuals, "filled_box", false);
//				visuals::box_type = getValue(visuals, "box_type", 0);
//				visuals::box_thick = getValue(visuals, "box_thick", 2.0f);
//				visuals::box_outline_thick = getValue(visuals, "box_outline_thick", 2.5f);
//				visuals::box_outline = getValue(visuals, "box_outline", true);
//				visuals::text_outline = getValue(visuals, "text_outline", true);
//				visuals::text_size = getValue(visuals, "text_size", 13.0f);
//				visuals::username = getValue(visuals, "username", true);
//				visuals::distance = getValue(visuals, "distance", false);
//				visuals::platform = getValue(visuals, "platform", false);
//				visuals::rank = getValue(visuals, "rank", false);
//				visuals::icons = getValue(visuals, "icons", false);
//				visuals::colored_text = getValue(visuals, "colored_text", false);
//				visuals::weapon = getValue(visuals, "weapon", false);
//				visuals::level = getValue(visuals, "level", false);
//				visuals::kills = getValue(visuals, "kills", false);
//				visuals::team = getValue(visuals, "team", false);
//				visuals::water_mark = getValue(visuals, "water_mark", true);
//				visuals::stream_proof = getValue(visuals, "stream_proof", false);
//				visuals::stream_proof_once = getValue(visuals, "stream_proof_once", false);
//				visuals::old_style_top = getValue(visuals, "old_style_top", false);
//				visuals::text_style = getValue(visuals, "text_style", 0);
//				visuals::rank_pos = getValue(visuals, "rank_pos", 1);
//				visuals::username_pos = getValue(visuals, "username_pos", 1);
//				visuals::distance_pos = getValue(visuals, "distance_pos", 0);
//				visuals::platform_pos = getValue(visuals, "platform_pos", 1);
//				visuals::weapon_pos = getValue(visuals, "weapon_pos", 0);
//				visuals::level_pos = getValue(visuals, "level_pos", 3);
//				visuals::team_pos = getValue(visuals, "team_pos", 3);
//				visuals::kills_pos = getValue(visuals, "kills_pos", 3);
//				visuals::line_outline = getValue(visuals, "line_outline", true);
//				visuals::line = getValue(visuals, "line", false);
//				visuals::line_type = getValue(visuals, "line_type", 0);
//				visuals::line_thick = getValue(visuals, "line_thick", 2.0f);
//				visuals::outline_line_thick = getValue(visuals, "outline_line_thick", 2.5f);
//				visuals::arrows = getValue(visuals, "arrows", false);
//				visuals::arrows_danger = getValue(visuals, "arrows_danger", false);
//				visuals::arrows_safe = getValue(visuals, "arrows_safe", false);
//				visuals::danger_list = getValue(visuals, "danger_list", false);
//				visuals::sniper = getValue(visuals, "sniper", false);
//				visuals::sword = getValue(visuals, "sword", false);
//				visuals::safe_list = getValue(visuals, "safe_list", false);
//				visuals::healing = getValue(visuals, "healing", false);
//				visuals::no_ammo = getValue(visuals, "no_ammo", false);
//				visuals::image = getValue(visuals, "image", false);
//				visuals::Font_Type = getValue(visuals, "Font_Type", 0);
//			}
//
//			// Load aimbot settings with validation
//			if (jsonSettings.contains("aimbot")) {
//				const auto& aimbot = jsonSettings["aimbot"];
//				aimbot::enable = getValue(aimbot, "enable", false);
//				aimbot::visbile_check = getValue(aimbot, "visbile_check", false);
//				aimbot::display_target = getValue(aimbot, "display_target", false);
//				aimbot::check_flags = getValue(aimbot, "check_flags", false);
//				aimbot::outlined_fov = getValue(aimbot, "outlined_fov", false);
//				aimbot::ignored_downed = getValue(aimbot, "ignored_downed", false);
//				aimbot::ranadomization = getValue(aimbot, "ranadomization", false);
//				aimbot::target_hitbox = getValue(aimbot, "target_hitbox", 0);
//				aimbot::drawfov = getValue(aimbot, "drawfov", true);
//				aimbot::prediction = getValue(aimbot, "prediction", false);
//				aimbot::weapon_configs = getValue(aimbot, "weapon_configs", false);
//				aimbot::aim_fov = getValue(aimbot, "aim_fov", 70.0f);
//				aimbot::max_distance = getValue(aimbot, "max_distance", 300.0f);
//				aimbot::smoothing_x = getValue(aimbot, "smoothing_x", 15.0f);
//				aimbot::smoothing_y = getValue(aimbot, "smoothing_y", 15.0f);
//				aimbot::targeting_type = getValue(aimbot, "targeting_type", 0);
//				aimbot::fov_type = getValue(aimbot, "fov_type", 0);
//
//				// Load array values safely
//				for (int i = 0; i < 4; i++) {
//					aimbot::humanizationoptions[i] = getValue(aimbot, "humanizationoptions" + std::to_string(i), false);
//					aimbot::target_type[i] = getValue(aimbot, "target_type" + std::to_string(i), false);
//				}
//				for (int i = 0; i < 2; i++) {
//					aimbot::check_flags_type[i] = getValue(aimbot, "check_flags_type" + std::to_string(i), false);
//				}
//			}
//
//			// Load radar settings with validation
//			if (jsonSettings.contains("radar")) {
//				const auto& radar = jsonSettings["radar"];
//				radar::enable = getValue(radar, "enable", true);
//				radar::minimap = getValue(radar, "minimap", false);
//				radar::name = getValue(radar, "name", true);
//				radar::distance = getValue(radar, "distance", true);
//				radar::radar_position_x = getValue(radar, "radar_position_x", 10.0f);
//				radar::radar_position_y = getValue(radar, "radar_position_y", 15.0f);
//				radar::radar_size = getValue(radar, "radar_size", 250.0f);
//				radar::radar_distabce = getValue(radar, "radar_distabce", 30.0f);
//			}
//
//			// Load menu settings with validation
//			if (jsonSettings.contains("menu")) {
//				const auto& menu = jsonSettings["menu"];
//				menu::is_open = getValue(menu, "is_open", true);
//			}
//
//			// Load color settings with validation
//			if (jsonSettings.contains("colors")) {
//				const auto& colors = jsonSettings["colors"];
//				
//				// Load color arrays safely
//				if (colors.contains("BoxVisible")) {
//					const auto& boxVisible = colors["BoxVisible"];
//					colors::BoxVisible[0] = getValue(boxVisible, "0", 0.0f);
//					colors::BoxVisible[1] = getValue(boxVisible, "1", 1.0f);
//					colors::BoxVisible[2] = getValue(boxVisible, "2", 0.3f);
//					colors::BoxVisible[3] = getValue(boxVisible, "3", 1.0f);
//				}
//
//				if (colors.contains("UsernameVisible")) {
//					const auto& usernameVisible = colors["UsernameVisible"];
//					colors::UsernameVisible[0] = getValue(usernameVisible, "0", 0.0f);
//					colors::UsernameVisible[1] = getValue(usernameVisible, "1", 1.0f);
//					colors::UsernameVisible[2] = getValue(usernameVisible, "2", 0.3f);
//					colors::UsernameVisible[3] = getValue(usernameVisible, "3", 1.0f);
//				}
//
//				if (colors.contains("DistanceVisible")) {
//					const auto& distanceVisible = colors["DistanceVisible"];
//					colors::DistanceVisible[0] = getValue(distanceVisible, "0", 0.0f);
//					colors::DistanceVisible[1] = getValue(distanceVisible, "1", 1.0f);
//					colors::DistanceVisible[2] = getValue(distanceVisible, "2", 0.3f);
//					colors::DistanceVisible[3] = getValue(distanceVisible, "3", 1.0f);
//				}
//
//				if (colors.contains("WeaponVisible")) {
//					const auto& weaponVisible = colors["WeaponVisible"];
//					colors::WeaponVisible[0] = getValue(weaponVisible, "0", 0.0f);
//					colors::WeaponVisible[1] = getValue(weaponVisible, "1", 1.0f);
//					colors::WeaponVisible[2] = getValue(weaponVisible, "2", 0.3f);
//					colors::WeaponVisible[3] = getValue(weaponVisible, "3", 1.0f);
//				}
//
//				if (colors.contains("fovcolor")) {
//					const auto& fovcolor = colors["fovcolor"];
//					colors::fovcolor[0] = getValue(fovcolor, "0", 0.0f);
//					colors::fovcolor[1] = getValue(fovcolor, "1", 0.8f);
//					colors::fovcolor[2] = getValue(fovcolor, "2", 1.0f);
//					colors::fovcolor[3] = getValue(fovcolor, "3", 1.0f);
//				}
//
//				// Load other color settings
//				colors::color_speed = getValue(colors, "color_speed", 2.0f);
//				colors::rainbow = getValue(colors, "rainbow", false);
//				colors::color_red = getValue(colors, "color_red", 1.0f);
//				colors::color_green = getValue(colors, "color_green", 0.0f);
//				colors::color_blue = getValue(colors, "color_blue", 0.0f);
//			}
//
//			return true;
//		}
//		catch (const std::exception& e) {
//			std::cerr << "Error loading settings: " << e.what() << std::endl;
//			return false;
//		}
//	}
//
//	// ... existing code ...
//}
//
//void CleanupTexture(LPDIRECT3DTEXTURE9& texture) {
//    if (texture) {
//        texture->Release();
//        texture = nullptr;
//    }
//}
//
//// Add these helper functions before the Skins function
//std::vector<std::string> GetConfigFiles() {
//    std::vector<std::string> configs;
//    std::string configDir = "C:\\Nigger.lol\\Configs\\";
//    
//    // Create directory if it doesn't exist
//    std::filesystem::create_directories(configDir);
//    
//    // Get all .config files
//    for (const auto& entry : std::filesystem::directory_iterator(configDir)) {
//        if (entry.path().extension() == ".config") {
//            configs.push_back(entry.path().stem().string());
//        }
//    }
//    return configs;
//}
//
//void SaveConfigWithName(const std::string& name) {
//    std::string configDir = "C:\\Nigger.lol\\Configs\\";
//    std::string fullPath = configDir + name + ".config";
//    values::saveSettings(fullPath);
//}
//
//void LoadConfigByName(const std::string& name) {
//    std::string configDir = "C:\\Nigger.lol\\Configs\\";
//    std::string fullPath = configDir + name + ".config";
//    values::LoadSettings(fullPath);
//}
//
//void DeleteConfig(const std::string& name) {
//    std::string configDir = "C:\\Nigger.lol\\Configs\\";
//    std::string fullPath = configDir + name + ".config";
//    std::filesystem::remove(fullPath);
//}

// Add these UI helper functions before the Skins function
void InsertSpacer(const char* label) {
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
}

void InsertGroupBoxLeft(const char* label, float height) {
    ImGui::BeginChild(label, ImVec2(300, height), true);
    ImGui::Text(label);
    ImGui::Separator();
}

void InsertEndGroupBoxLeft(const char* label, const char* title) {
    ImGui::EndChild();
}
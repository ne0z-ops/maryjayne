#pragma once
#include "../../Frontend/Framework/imgui/imgui.h"
#include "../UnityEngine/functions.h"
#include <random>
#include <memory>
#include <iostream>
#include <string>
#include <atomic>
#include <unordered_map>
#include <mutex>
#include <array>

namespace ImGui {
	class ImDrawList;
}

// Add termination flag
static std::atomic<bool> g_running = true;

void DrawLine(const ImVec2& start, const ImVec2& end, ImU32 color, int width)
{
	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	if (draw_list) {
		draw_list->AddLine(start, end, color, width);
	}
}

void RenderText(const std::string& text, const ImVec2& pos, float size, uint32_t color, bool center)
{
	constexpr float fStrokeVal1 = 1.0f;
	uint32_t EdgeColor = 0xFF000000;

	float Edge_a = (EdgeColor >> 24) & 0xff;
	float Edge_r = (EdgeColor >> 16) & 0xff;
	float Edge_g = (EdgeColor >> 8) & 0xff;
	float Edge_b = (EdgeColor) & 0xff;

	std::stringstream steam;
	std::string line;

	steam << text;
	float y = 0.0f;
	int i = 0;

	while (std::getline(steam, line))
	{
		ImVec2 textSize = ImGui::GetFont()->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - textSize.x / 2.0f) - fStrokeVal1, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - textSize.x / 2.0f) + fStrokeVal1, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - textSize.x / 2.0f), (pos.y + textSize.y * i) - fStrokeVal1), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x - textSize.x / 2.0f), (pos.y + textSize.y * i) + fStrokeVal1), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), color, line.c_str());
		}
		else
		{
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x) - fStrokeVal1, (pos.y + textSize.y * i)), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x) + fStrokeVal1, (pos.y + textSize.y * i)), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x), (pos.y + textSize.y * i) - fStrokeVal1), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2((pos.x), (pos.y + textSize.y * i) + fStrokeVal1), ImGui::GetColorU32(ImVec4(Edge_r / 255, Edge_g / 255, Edge_b / 255, Edge_a / 255)), line.c_str());
			ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), size, ImVec2(pos.x, pos.y + textSize.y * i), color, line.c_str());
		}
		y = pos.y + textSize.y * (i + 1);
		i++;
	}
}

inline void draw_box(const ImVec2& position, float width, float height, ImColor box_color, float box_thickness, float box_outline_thickness) {

	/*if (visuals->filled_box) {
		ImGui::GetBackgroundDrawList()->AddRectFilled(position, ImVec2(position.x + width, position.y + height), ImColor(fillboxcolor[0], fillboxcolor[1], fillboxcolor[2], fillboxcolor[3]));
	}*/

	DrawLine(ImVec2(position.x, position.y), ImVec2(position.x + width, position.y), box_color, box_thickness); // top 
	DrawLine(ImVec2(position.x, position.y - 1.3f), ImVec2(position.x, position.y + height + box_thickness), box_color, box_thickness); // left
	DrawLine(ImVec2(position.x + width, position.y - 1.3f), ImVec2(position.x + width, position.y + height + box_thickness), box_color, box_thickness);  // right
	DrawLine(ImVec2(position.x, position.y + height), ImVec2(position.x + width, position.y + height), box_color, box_thickness);   // bottom 

	//if (true) {
	//	ImGui::GetBackgroundDrawList()->AddRect(position, ImVec2(position.x + width, position.y + height), ImColor(0, 0, 0), 0, 0, box_outline_thickness);
	//}

	//ImGui::GetBackgroundDrawList()->AddRect(position, ImVec2(position.x + width, position.y + height), box_color, 0, 0, box_thickness);
}

inline void draw_cornerbox(const ImVec2& position, float width, float height, ImColor box_color, float box_thickness, float box_outline_thickness) {
	// Cache the draw list pointer
	ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
	if (!draw_list) return;

	// Pre-calculate corner lengths
	float lineW = width / 3.0f;
	float lineH = height / 3.0f;

	// Pre-calculate corner positions to avoid repeated calculations
	ImVec2 topLeft(position.x, position.y);
	ImVec2 topRight(position.x + width, position.y);
	ImVec2 bottomLeft(position.x, position.y + height);
	ImVec2 bottomRight(position.x + width, position.y + height);

	// Draw corners in a single batch
	draw_list->AddLine(topLeft, ImVec2(topLeft.x, topLeft.y + lineH), box_color, box_thickness);
	draw_list->AddLine(topLeft, ImVec2(topLeft.x + lineW, topLeft.y), box_color, box_thickness);

	draw_list->AddLine(topRight, ImVec2(topRight.x, topRight.y + lineH), box_color, box_thickness);
	draw_list->AddLine(ImVec2(topRight.x - lineW, topRight.y), topRight, box_color, box_thickness);

	draw_list->AddLine(bottomLeft, ImVec2(bottomLeft.x, bottomLeft.y - lineH), box_color, box_thickness);
	draw_list->AddLine(bottomLeft, ImVec2(bottomLeft.x + lineW, bottomLeft.y), box_color, box_thickness);

	draw_list->AddLine(bottomRight, ImVec2(bottomRight.x, bottomRight.y - lineH), box_color, box_thickness);
	draw_list->AddLine(ImVec2(bottomRight.x - lineW, bottomRight.y), bottomRight, box_color, box_thickness);
}

void draw_outlined_text(ImFont* font, double fontSize, int x, int y, ImColor color, const char* text)
{
	ImVec4 outlineColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

	ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(x - 1, y - 1), IM_COL32(outlineColor.x * 255, outlineColor.y * 255, outlineColor.z * 255, outlineColor.w * 255), text);
	ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(x + 1, y - 1), IM_COL32(outlineColor.x * 255, outlineColor.y * 255, outlineColor.z * 255, outlineColor.w * 255), text);
	ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(x - 1, y + 1), IM_COL32(outlineColor.x * 255, outlineColor.y * 255, outlineColor.z * 255, outlineColor.w * 255), text);
	ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(x + 1, y + 1), IM_COL32(outlineColor.x * 255, outlineColor.y * 255, outlineColor.z * 255, outlineColor.w * 255), text);

	ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(x, y), ImColor(color), text);
}

void draw_outlined_text_2(ImFont* font, float fontSize, int x, int y, ImColor color1, ImColor color2, const char* text1, const char* text2)
{
	ImVec4 outlineColor = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	float lineHeight = fontSize + 2; // Adjust spacing between lines

	ImVec2 textSize1 = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text1);
	ImVec2 textSize2 = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text2);

	int text1_x = x + (textSize2.x - textSize1.x) / 2; // Center text1 over text2

	auto draw_text = [&](const char* text, int posX, int posY, ImColor textColor) {
		ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(posX - 1, posY - 1), IM_COL32(0, 0, 0, 255), text);
		ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(posX + 1, posY - 1), IM_COL32(0, 0, 0, 255), text);
		ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(posX - 1, posY + 1), IM_COL32(0, 0, 0, 255), text);
		ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(posX + 1, posY + 1), IM_COL32(0, 0, 0, 255), text);
		ImGui::GetBackgroundDrawList()->AddText(font, fontSize, ImVec2(posX, posY), textColor, text);
		};

	draw_text(text1, text1_x, y, color1);         // Distance (centered above name)
	draw_text(text2, x, y + lineHeight, color2);  // Name (bottom line)
}

#define M_PI 3.14159265358979323846f
#define M_RADPI	57.295779513082f
#define M_PI_F ((float)(M_PI))
#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI_F))




Vector3 Lerp(const Vector3& a, const Vector3& b, float t) {
	return Vector3(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	);
}

#define RAD2DEG(x) ((float)(x) * (float)(180.f / M_PI))
#define M_PI 3.14159265358979323846f
#define DBL_MAX 1.7976931348623158e+308

extern ImFont* AllFont;
extern int aimbot_key;

class TextureCache {
private:
	std::unordered_map<std::string, LPDIRECT3DTEXTURE9> cache;
	std::mutex cacheMutex;
	static const size_t MAX_CACHE_SIZE = 1000;

public:
	struct TextureResult {
		LPDIRECT3DTEXTURE9 texture;
		bool isNew;
	};

	TextureResult get_texture(LPDIRECT3DDEVICE9 device, const std::string& prefabName) {
		std::lock_guard<std::mutex> lock(cacheMutex);

		// Check cache first
		auto it = cache.find(prefabName);
		if (it != cache.end()) {
			return { it->second, false };
		}

		// If cache is too large, remove oldest entries
		if (cache.size() >= MAX_CACHE_SIZE) {
			cache.erase(cache.begin());
		}

		// Load new texture
		auto texture = LoadTexture(device, prefabName);
		if (texture) {
			cache[prefabName] = texture;
			return { texture, true };
		}

		return { nullptr, false };
	}

	void cleanup() {
		std::lock_guard<std::mutex> lock(cacheMutex);
		for (auto& pair : cache) {
			if (pair.second) {
				pair.second->Release();
			}
		}
		cache.clear();
	}

	~TextureCache() {
		cleanup();
	}
};

// Global instance
inline TextureCache g_texture_cache;

struct ActorLoop {
	std::mutex item_mutex; // Add mutex declaration here

	Vector2 CalculateAngle(const Vector3& player, const Vector3& target)
	{
		Vector3 direction = Vector3(player.x - target.x, player.y - target.y, player.z - target.z);
		return Vector2(RAD2DEG(asin(direction.y / direction.Length())), RAD2DEG(-atan2(direction.x, -direction.z)));
	}

	float value = 0.f;

	BaseEntity* last_target = nullptr;

	void silent_aim(BaseEntity* closest_player, double closest_distnace, BaseEntity* local_player, Matrix4x4 ViewMatrix) {
		if (closest_player == nullptr)
			return;

		if (closest_distnace > values::aimbot::max_distance)
			return;

		// Reset value when switching targets
		if (last_target != closest_player) {
			value = 0.f;
			last_target = closest_player;
		}

		// Rest of your existing code remains exactly the same...
		Vector3 target_position = Vector3();

		if (values::aimbot::target_hitbox == 0)
			target_position = camerashi->Get_Transformation(closest_player, BoneList::head)->Get_Position() + Vector3(0.0f, 0.20f, 0.0f);

		if (values::aimbot::target_hitbox == 1)
			target_position = camerashi->Get_Transformation(closest_player, BoneList::head)->Get_Position();

		if (values::aimbot::target_hitbox == 2)
			target_position = camerashi->Get_Transformation(closest_player, BoneList::neck)->Get_Position();
		if (values::aimbot::target_hitbox == 3)
			target_position = camerashi->Get_Transformation(closest_player, BoneList::spine1)->Get_Position();




		Vector3 local_player_position = camerashi->Get_Transformation(local_player, BoneList::head)->Get_Position();

		Vector2 Angle = CalculateAngle(local_player_position, target_position);
		Angle.Normalize();

		Vector2 target_loc;
		camerashi->WorldToScreen(target_position, &target_loc, ViewMatrix);

		if (values::aimbot::display_target) {


			ImGui::GetForegroundDrawList()->AddLine(ImVec2(Monitor::Width / 2, Monitor::Height / 2), ImVec2(target_loc.x, target_loc.y), ImColor(0, 0.8, 1), 1.5f);
		}

		if (values::aimbot::automatic_fov) {
			// Get target position
			target_position = camerashi->Get_Transformation(closest_player, BoneList::head)->Get_Position() + Vector3(0.0f, 0.20f, 0.0f);

			// Calculate distance to target
			float distance = pointers->CameraPos.Distance(target_position);

			// FOV adjustment parameters
			const float min_distance = 5.0f;   // When player is this close or closer, use max FOV
			const float max_distance = 200.0f;  // When player is this far or farther, use min FOV
			const float min_fov = 30.0f;       // Minimum FOV for far targets
			const float max_fov = 180.0f;      // Maximum FOV for close targets

			// Calculate new FOV based on distance
			float new_fov;
			if (distance <= min_distance) {
				new_fov = max_fov;
			}
			else if (distance >= max_distance) {
				new_fov = min_fov;
			}
			else {
				// Smoothly interpolate FOV based on distance
				float t = (distance - min_distance) / (max_distance - min_distance);
				new_fov = max_fov + t * (min_fov - max_fov);
			}

			// Smooth FOV transition
			const float smooth_speed = 0.1f;  // Adjust this value to control smoothing speed
			values::aimbot::aim_fov = values::aimbot::aim_fov + (new_fov - values::aimbot::aim_fov) * smooth_speed;
		}

		if (GetAsyncKeyState(aimbot_key)) {
			if (values::aimbot::hitchance) {

				value += 1.f;
				std::mt19937 rng(std::random_device{ }());
				std::uniform_int_distribution<int> dist(0, 100);
				int chance = dist(rng);

				if (value >= 100.f)
					value = 100.f;


				if (chance <= values::aimbot::hit_chance)
				{
					if (values::aimbot::aim_type == 2)
					{
						local_player->GetEyes()->SetBodyRotation(ToQuat(Vector3(Angle.x, Angle.y, 0.0f)));
					}
					else if (values::aimbot::aim_type == 1)
					{


						local_player->SetInputOffset(Vector3(Angle.x, Angle.y, 0.0f));
					}
					else if (values::aimbot::aim_type == 0)
					{
						autoMouseMove(target_loc.x, target_loc.y);

					}
				}
			}
			else {
				if (values::aimbot::aim_type == 2)
				{
					local_player->GetEyes()->SetBodyRotation(ToQuat(Vector3(Angle.x, Angle.y, 0.0f)));
				}
				else if (values::aimbot::aim_type == 1)
				{



					local_player->SetInputOffset(Vector3(Angle.x, Angle.y, 0.0f));
				}
				else if (values::aimbot::aim_type == 0)
				{
					autoMouseMove(target_loc.x, target_loc.y);
				}
			}
		}
	}

	void World()
	{
		if (!values::World::enable) return;

		// Cache commonly used values outside the loop
		const float max_distance = values::visuals::MaxLootDistance;
		const float text_size = values::visuals::text_size;
		const ImColor text_color(255, 255, 255);
		const ImColor distance_color(168, 92, 50);
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
		if (!draw_list) return;

		// Reusable lambda for drawing items
		auto DrawWorldItem = [&](const Vector2& pos, const std::string& display_name, int distance) {
			draw_outlined_text_2(AllFont, text_size, pos.x, pos.y,
				text_color, distance_color,
				(std::to_string(distance) + "m").c_str(),
				display_name.c_str());
		};

		for (const auto& itemEntity : ItemList) {
			// Early distance check
			int item_distance = pointers->CameraPos.Distance(itemEntity.location);
			if (item_distance > max_distance) continue;

			Vector2 item_pos;
			if (!camerashi->WorldToScreen(itemEntity.location, &item_pos, pointers->Matrix) ||
				!camerashi->InScreen(item_pos)) continue;

			// Handle world items
			if (itemEntity.name.find("(world)") != std::string::npos) {
				std::string name = itemEntity.name;
				size_t pos = name.find(" (world)");
				if (pos != std::string::npos) {
					name.erase(pos, 8);
					DrawWorldItem(item_pos, name, item_distance);
				}
				continue;
			}

			// Handle dropped items with images
			if (values::World::dropped && itemEntity.ClassName.find("DroppedItem") != std::string::npos) {
				if (values::visuals::droppeditemsimages) {
					std::string prefabName = itemEntity.items->get_short_name();
					if (!prefabName.empty() && prefabName != "Empty") {
						auto textureResult = g_texture_cache.get_texture(DirectX9Interface::p_device, prefabName);
						if (textureResult.texture) {
							draw_list->AddImage(
								reinterpret_cast<void*>(textureResult.texture),
								ImVec2(item_pos.x - 15, item_pos.y - 15),
								ImVec2(item_pos.x + 15, item_pos.y + 15),
								ImVec2(0, 0),
								ImVec2(1, 1)
							);
							continue;
						}
					}
				}

				std::string item_string = itemEntity.items->get_prefab();
				if (!item_string.empty() && item_string != "Empty") {
					DrawWorldItem(item_pos, item_string, item_distance);
				}
				continue;
			}

			// Handle all other item types using a switch-like approach
			const struct {
				const char* search_str;
				const char* display_name;
				bool* enabled;
			} items[] = {
				{"supply_drop", "Supply Drop", &values::World::supplydrop},
				{"wolf", "Wolf", &values::World::wolf},
				{"boar", "Boar", &values::World::boar},
				{"codelockedhackablecrate", "Locked Crate", &values::World::lockedcrate},
				{"diesel_collectable", "Diesel Collectable", &values::World::diesel},
				{"foodbox", "Food Box", &values::World::foodbox},
				{"box.wooden.large", "Large Storage Box", &values::World::boxes},
				{"coffinstorage", "Large Storage Box", &values::World::boxes},
				{"storage_barrel", "Large Storage Box", &values::World::boxes},
				{"generator.", "Generator", &values::World::generators},
				{"rechargable.battery", "Battery", &values::World::batterys},
				{"player_corpse", "Dead Body", &values::World::corpses},
				{"item_drop_backpack", "Dead Body", &values::World::corpses},
				{"autoturret", "Turret", &values::World::turrets},
				{"crate_elite", "Elite Crate", &values::World::EliteCrate},
				{"crate_normal_2", "Normal Crate", &values::World::NormalCrate},
				{"furnace", "Furnace", &values::World::FurnaceEsp},
				{"guntrap", "Shotgun Trap", &values::World::traps},
				{"hemp-collectable", "Hemp", &values::World::hemp},
				{"sleepingbag", "Bag/Bed", &values::World::bags},
				{"bed_deployed", "Bag/Bed", &values::World::bags},
				{"cupboard.tool", "TC", &values::World::tcs},
				{"stone-ore", "Stone", &values::World::stone},
				{"stone-collectable", "Stone", &values::World::stone},
				{"metal-ore", "Metal", &values::World::metal},
				{"metal-collectable", "Metal", &values::World::metal},
				{"sulfur-ore", "Sulfur", &values::World::sulfur},
				{"sulfur-collectable", "Sulfur", &values::World::sulfur},
				{"sam_static", "Sam Site", &values::World::SamSiteEsp}
			};

			for (const auto& item : items) {
				if (*item.enabled && itemEntity.name.find(item.search_str) != std::string::npos) {
					DrawWorldItem(item_pos, item.display_name, item_distance);
					break;
				}
			}
		}
	}

	BaseEntity* closest_player;
	float closest_distance = DBL_MAX;

	void Loop()
	{
		for (auto players : EntityList) {

			auto player = players.Player;

			auto pos = player->Position();
			auto Upper3d = camerashi->Get_Transformation(player, BoneList::head)->Get_Position() + Vector3(0.0f, 0.30f, 0.0f);
			auto Lower3d = pos - Vector3(0.0f, 0.30f, 0.0f);
			auto head3d = camerashi->Get_Transformation(player, BoneList::head)->Get_Position();

			// Store original colors
			ImColor BoxColor;
			ImColor NameColor;
			ImColor DistanceColor;
			ImColor HeldColor;
			ImColor StatusColor;

			// Check if player is wounded and update colors accordingly
			if (values::visuals::show_wounded && player->HasFlag(64)) {
				// Use wounded colors from the values array for this specific player
				BoxColor = ImColor(values::colors::wounded[0], values::colors::wounded[1], values::colors::wounded[2], values::colors::wounded[3]);
				NameColor = ImColor(values::colors::wounded[0], values::colors::wounded[1], values::colors::wounded[2], values::colors::wounded[3]);
				DistanceColor = ImColor(values::colors::wounded[0], values::colors::wounded[1], values::colors::wounded[2], values::colors::wounded[3]);
				HeldColor = ImColor(values::colors::wounded[0], values::colors::wounded[1], values::colors::wounded[2], values::colors::wounded[3]);
				StatusColor = ImColor(values::colors::wounded[0], values::colors::wounded[1], values::colors::wounded[2], values::colors::wounded[3]);
			}
			else {
				// Use default colors from the arrays
				BoxColor = ImColor(values::colors::BoxVisible[0], values::colors::BoxVisible[1], values::colors::BoxVisible[2], values::colors::BoxVisible[3]);
				NameColor = ImColor(values::colors::UsernameVisible[0], values::colors::UsernameVisible[1], values::colors::UsernameVisible[2], values::colors::UsernameVisible[3]);
				DistanceColor = ImColor(values::colors::DistanceVisible[0], values::colors::DistanceVisible[1], values::colors::DistanceVisible[2], values::colors::DistanceVisible[3]);
				HeldColor = ImColor(values::colors::WeaponVisible[0], values::colors::WeaponVisible[1], values::colors::WeaponVisible[2], values::colors::WeaponVisible[3]);
				StatusColor = ImColor(values::colors::woundedregular[0], values::colors::woundedregular[1], values::colors::woundedregular[2], values::colors::woundedregular[3]);
			}

			ImColor ScientistsColor = ImColor(values::colors::ScientistsVisible[0], values::colors::ScientistsVisible[1], values::colors::ScientistsVisible[2], values::colors::ScientistsVisible[3]);
			Vector2 Upper = Vector2();
			Vector2 Lower = Vector2();
			Vector2 Head = Vector2();

			auto test = cmd::read<bool>(player->Address() + 0x160);

			auto test1 = cmd::read<bool>(player->Address() + 0x162);

			if (!camerashi->WorldToScreen(Upper3d, &Upper, pointers->Matrix)) continue;
			if (!camerashi->WorldToScreen(Lower3d, &Lower, pointers->Matrix)) continue;
			if (!camerashi->WorldToScreen(head3d, &Head, pointers->Matrix)) continue;

			float FontSize = 13.f;
			float Entity_h = Upper.y - Lower.y;
			float w = Entity_h / 1;
			float Entity_x = Lower.x - w;
			float Entity_y = Lower.y;
			float Entity_w = Entity_h / 2.0;

			float boxWidth = (Lower.y - Upper.y) * 0.5f;
			float boxHeight = Lower.y - Upper.y;
			int top_offset = 15;
			int bottom_offset = 0;


			if (!camerashi->InScreen(Upper)) continue;

			if (values::aimbot::enable || values::visuals::itemlist)
			{
				float enemy_distance = pointers->CameraPos.Distance(player->Position());

				if (enemy_distance < closest_distance) {
					closest_player = player;
					closest_distance = enemy_distance;
				}

				auto CrosshairDistanceToPlayer = GetCrossDistance(Head.x, Head.y, Monitor::Width / 2, Monitor::Height / 2);
				if (!(CrosshairDistanceToPlayer <= values::aimbot::aim_fov)) {
					closest_player = nullptr;
					closest_distance = DBL_MAX;
				}

				//if (player->Position()->IsLocalPlayer()) { // this is team check i made but idek if works.
				//	closest_player = nullptr;
				//	F = DBL_MAX;
				//}

				//if (closest_player->TeamID() != 0 && closest_player->TeamID() == pointers->LocalPlayer->TeamID()) {
				//		closest_player = nullptr;
				//		closest_distance = DBL_MAX;
				//}

				if (!pos.IsValid()) {
					closest_player = nullptr;
					closest_distance = DBL_MAX;
				}

				if (values::aimbot::ignored_downed && closest_player->HasFlag(64)) {
					closest_player = nullptr;
					closest_distance = DBL_MAX;
				}

				if (closest_player->HasFlag(16)) {
					closest_player = nullptr;
					closest_distance = DBL_MAX;
				}

				Vector2 screenCoordinates;
				camerashi->WorldToScreen(closest_player->Position(), &screenCoordinates, pointers->Matrix);
				if (!(screenCoordinates.x >= 0 && screenCoordinates.x <= Monitor::Width && screenCoordinates.y >= 0 && screenCoordinates.y <= Monitor::Height)) {
					closest_player = nullptr;
					closest_distance = DBL_MAX;
				}
			}

			if (values::aimbot::enable)
			{
				auto weapon = pointers->LocalPlayer->Get_HeldItem();
				auto name = weapon->get_item_name();
				if (!name.empty() && pointers->LocalPlayer) silent_aim(closest_player, closest_distance, pointers->LocalPlayer, pointers->Matrix);
			}

			int playerdist = pointers->CameraPos.Distance(pos);

			if (playerdist < values::visuals::maxplayerdistance)
			{

				if (values::visuals::username)
				{
					std::string name = player->Name();

					ImVec2 TextSizeName = ImGui::CalcTextSize(name.c_str());


					float text_x = Upper.x;
					float text_y = Upper.y - top_offset;

					RenderText(name.c_str(), ImVec2(text_x, text_y), 13, NameColor, true);

					draw_player_status(
						ImVec2(text_x + TextSizeName.x + 2.0f, text_y),  // Reduced gap from 5.0f to 2.0f
						player,
						values::visuals::text_size
					);

					top_offset += 13;
				}

				if (values::visuals::box_type == 0)
				{

				}

				if (values::visuals::box_type == 1)
				{
					draw_box(ImVec2(Upper.x - boxWidth / 2, Upper.y), Lower.x + boxWidth / 2 - (Upper.x - boxWidth / 2), Lower.y - Upper.y, BoxColor, 1, 3);

				}

				else if (values::visuals::box_type == 2)
				{
					draw_cornerbox(ImVec2(Upper.x - boxWidth / 2, Upper.y), Lower.x + boxWidth / 2 - (Upper.x - boxWidth / 2), Lower.y - Upper.y, BoxColor, 1, 3);
				}

				else if (values::visuals::box_type == 3)
				{
					ImGui::GetBackgroundDrawList()->AddRectFilled(
						ImVec2(Upper.x - boxWidth / 2, Upper.y),
						ImVec2(Upper.x + boxWidth / 2, Upper.y + boxHeight),
						ImColor((int)(BoxColor.Value.x * 255), (int)(BoxColor.Value.y * 255), (int)(BoxColor.Value.z * 255), 85)
					);
				}

				if (values::visuals::weapon)
				{
					std::string heldweapon = player->Get_HeldItem()->get_item_name();
					if (heldweapon.empty())
					{
						heldweapon = ("No Held Item");
					}

					ImVec2 TextSizeName = ImGui::CalcTextSize(heldweapon.c_str());
					float text_x = Lower.x - (TextSizeName.x / 3);
					float text_y = Lower.y + bottom_offset;

					draw_outlined_text(AllFont, values::visuals::text_size, text_x, text_y, HeldColor, heldweapon.c_str());
					bottom_offset += 13;
				}

				if (values::visuals::distance)
				{
					std::string distancetxt = std::to_string(playerdist) + "m";

					ImVec2 TextSizeName = ImGui::CalcTextSize(distancetxt.c_str());
					float text_x = Lower.x - (TextSizeName.x / 3);
					float text_y = Lower.y + bottom_offset;

					draw_outlined_text(AllFont, values::visuals::text_size, text_x, text_y, DistanceColor, distancetxt.c_str());
					bottom_offset += 13;
				}

				if (values::visuals::skeleton)
				{
					// Cache the draw list
					ImDrawList* drawList = ImGui::GetBackgroundDrawList();

					// Define bone array
					std::array<BoneList, 15> Bones = {
						BoneList::l_foot, BoneList::l_knee, BoneList::l_hip,
						BoneList::r_foot, BoneList::r_knee, BoneList::r_hip,
						BoneList::neck, BoneList::spine3, BoneList::head,
						BoneList::l_upperarm, BoneList::l_forearm, BoneList::l_hand,
						BoneList::r_upperarm, BoneList::r_forearm, BoneList::r_hand
					};
					std::array<Vector2, Bones.size()> BonesPos;

					// Get all bone positions
					bool valid = true;
					for (int i = 0; i < Bones.size(); ++i) {
						auto bone3d = camerashi->Get_Transformation(player, Bones[i])->Get_Position();
						if (!camerashi->WorldToScreen(bone3d, &BonesPos[i], pointers->Matrix)) {
							valid = false;
							break;
						}
					}

					if (!valid) continue;

					// Set color based on wounded status
					ImColor skeletonColor;
					if (player->HasFlag(64)) {
						skeletonColor = ImColor(values::colors::wounded[0], values::colors::wounded[1], values::colors::wounded[2], values::colors::wounded[3]);
					}
					else {
						skeletonColor = ImColor(values::colors::SkeletonColor[0], values::colors::SkeletonColor[1], values::colors::SkeletonColor[2], values::colors::SkeletonColor[3]);
					}

					// Draw connected bones in groups of 3
					for (int j = 0; j < BonesPos.size(); j += 3) {
						drawList->AddLine(
							ImVec2(BonesPos[j].x, BonesPos[j].y),
							ImVec2(BonesPos[j + 1].x, BonesPos[j + 1].y),
							skeletonColor, 1.0f
						);
						drawList->AddLine(
							ImVec2(BonesPos[j + 1].x, BonesPos[j + 1].y),
							ImVec2(BonesPos[j + 2].x, BonesPos[j + 2].y),
							skeletonColor, 1.0f
						);
					}

					// Draw connecting lines between bone groups
					drawList->AddLine(ImVec2(BonesPos[2].x, BonesPos[2].y), ImVec2(BonesPos[6].x, BonesPos[6].y), skeletonColor, 1.0f);
					drawList->AddLine(ImVec2(BonesPos[5].x, BonesPos[5].y), ImVec2(BonesPos[6].x, BonesPos[6].y), skeletonColor, 1.0f);
					drawList->AddLine(ImVec2(BonesPos[9].x, BonesPos[9].y), ImVec2(BonesPos[7].x, BonesPos[7].y), skeletonColor, 1.0f);
					drawList->AddLine(ImVec2(BonesPos[12].x, BonesPos[12].y), ImVec2(BonesPos[7].x, BonesPos[7].y), skeletonColor, 1.0f);
				}
			}
		}
	}

	void Exploits()
	{

	}

	void draw_player_status(const ImVec2& name_pos, BaseEntity* player, float text_size) {
		const char* status_text = nullptr;
		ImColor status_color;
		float offset_x = 0.0f;

		if (values::visuals::show_wounded) {
			if (player->HasFlag(64)) {
				status_text = "[Wounded]";
				status_color = ImColor(values::colors::wounded[0], values::colors::wounded[1], values::colors::wounded[2], values::colors::wounded[3]);
			}
			else {
				status_text = "[Not Wounded]";
				status_color = ImColor(values::colors::UsernameVisible[0], values::colors::UsernameVisible[1], values::colors::UsernameVisible[2], values::colors::UsernameVisible[3]); // Grey color for not wounded
			}

			draw_outlined_text(
				AllFont,
				text_size,
				(int)(name_pos.x + offset_x),
				(int)name_pos.y,
				status_color,
				status_text
			);
		}
	}

	void Cleanup() {
		try {
			// Signal all threads to stop
			g_running.store(false, std::memory_order_release);

			// Clean up texture cache first
			try {
				g_texture_cache.cleanup();
			}
			catch (const std::exception& e) {
				// Just log and continue with cleanup
				std::cerr << "Error during texture cache cleanup: " << e.what() << std::endl;
			}

			// Allow time for threads to notice termination flag
			std::this_thread::sleep_for(std::chrono::milliseconds(150));

			// Collect all window handles first before attempting to close them
			std::vector<HWND> overlayWindows;

			// Try multiple window class names that might be used for the overlay
			const char* possibleClassNames[] = {
				"overlay_window_class",
				"Direct3DWindowClass",
				"ImGui Standalone",
				"SDL_app",
				nullptr  // Terminator
			};

			// Find windows by class name
			for (int i = 0; possibleClassNames[i] != nullptr; i++) {
				HWND overlayWindow = FindWindowA(possibleClassNames[i], nullptr);
				if (overlayWindow && IsWindow(overlayWindow)) {
					overlayWindows.push_back(overlayWindow);
				}
			}

			// Find windows by title
			EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
				if (!IsWindow(hwnd)) return TRUE;

				char windowTitle[256];
				GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

				// Check for common overlay window titles
				if (strstr(windowTitle, "Overlay") != nullptr ||
					strstr(windowTitle, "DirectX") != nullptr ||
					strstr(windowTitle, "D3D") != nullptr) {
					std::vector<HWND>* windows = reinterpret_cast<std::vector<HWND>*>(lParam);
					windows->push_back(hwnd);
				}
				return TRUE;
				}, reinterpret_cast<LPARAM>(&overlayWindows));

			// Now close all collected windows
			for (HWND hwnd : overlayWindows) {
				if (!IsWindow(hwnd)) continue;

				// Try graceful shutdown first with timeout
				DWORD_PTR result;
				if (SendMessageTimeoutA(hwnd, WM_CLOSE, 0, 0, SMTO_ABORTIFHUNG, 500, &result)) {
					// Message was processed, check if window is still open
					if (IsWindow(hwnd)) {
						// If still open, try more aggressive methods
						PostMessage(hwnd, WM_QUIT, 0, 0);
						PostMessage(hwnd, WM_DESTROY, 0, 0);

						// Small delay to allow messages to process
						std::this_thread::sleep_for(std::chrono::milliseconds(50));

						// If still open, force destroy
						if (IsWindow(hwnd)) {
							DestroyWindow(hwnd);
						}
					}
				}
				else {
					// Message timed out, force destroy
					DestroyWindow(hwnd);
				}
			}

			// Final delay to ensure windows are closed
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		catch (const std::exception& e) {
			std::cerr << "Exception during cleanup: " << e.what() << std::endl;
		}
		catch (...) {
			std::cerr << "Unknown exception during cleanup" << std::endl;
		}
	}

	void Init()
	{
		g_running.store(true, std::memory_order_release);  // Use atomic store with memory order
		std::thread([this]() {
			try {
				Exploits();
			}
			catch (const std::exception& e) {
				std::cerr << "Exception in Exploits thread: " << e.what() << std::endl;
			}
			}).detach();
	}

	~ActorLoop() {
		Cleanup();  // Ensure cleanup is called when ActorLoop is destroyed
	}
};

static ActorLoop* loop = new ActorLoop();

// Add function to trigger cleanup from external code
inline void ShutdownCheat() {
	try {
		if (loop) {
			// Set the running flag to false first to stop any ongoing operations
			g_running.store(false, std::memory_order_release);

			// Add a small delay to allow threads to notice the flag
			std::this_thread::sleep_for(std::chrono::milliseconds(50));

			loop->Cleanup();

			// Store pointer locally and null the global before delete
			ActorLoop* temp = loop;
			loop = nullptr;

			// Now delete the pointer
			delete temp;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception during ShutdownCheat: " << e.what() << std::endl;
		// Ensure loop is nulled even if there's an exception
		loop = nullptr;
	}
	catch (...) {
		std::cerr << "Unknown exception during ShutdownCheat" << std::endl;
		loop = nullptr;
	}
}

void shutdownoverlay() // keeping done nigger.
{
	if (system("Rust.exe") == 0) // call this out of the shutdowncheat func.
	{
		ShutdownCheat(); // should clean up cheat on close so when Nigger.lol == 0 indicating closed it will cleanup 
	}
}
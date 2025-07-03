#include <mutex>
#include <vector>
#include <unordered_map>
#include "../UnityEngine/sdk.h"
#include "../../Frontend/Offsets/offsets.h"
#include "../../Backend/Render/drawing.h"
#include "../../Frontend/Console/console.hpp"
#include "hid.h"

typedef          char   int8;
typedef   signed char   sint8;
typedef unsigned char   uint8;
typedef          short  int16;
typedef          int    int32;

#define LAST_IND(x,part_type)    (sizeof(x)/sizeof(part_type) - 1)
#if defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN
#define LOW_IND(x,part_type)   LAST_IND(x,part_type)
#define HIGH_IND(x,part_type)  0
#else
#define HIGH_IND(x,part_type)  LAST_IND(x,part_type)
#define LOW_IND(x,part_type)   0
#endif

#define _BYTE uint8_t
#define BYTEn(x, n)   (*((_BYTE*)&(x)+n))

#define HIBYTE(x) BYTEn(x,HIGH_IND(x,_BYTE))

#define WORDn(x, n)   (*((_WORD*)&(x)+n))
#define DWORDn(x, n)  (*((_DWORD*)&(x)+n))

#define LOBYTE(x)  BYTEn(x,LOW_IND(x,_BYTE))
#define LOWORD(x)  WORDn(x,LOW_IND(x,_WORD))
#define LODWORD(x) DWORDn(x,LOW_IND(x,_DWORD))


#define TEST_BITD(value, bit) (((value) & (1 << (bit))) != 0)
//typedef unsigned long _DWORD;

namespace decrypt
{
	uintptr_t Il2CppGetHandle(int32_t ObjectHandleID) {
		uint64_t rdi_1 = ObjectHandleID >> 3;
		uint64_t rcx_1 = (ObjectHandleID & 7) - 1;
		uint64_t baseAddr = cmd::vrtxrr22 + 0xBF45AD0 + rcx_1 * 0x28;
		uint32_t limit = cmd::read<uint32_t>(baseAddr + 0x10);
		if (rdi_1 < limit) {
			uintptr_t objAddr = cmd::read<uintptr_t>(baseAddr);
			uint32_t bitMask = cmd::read<uint32_t>(objAddr + ((rdi_1 >> 5) << 2));
			if (TEST_BITD(bitMask, rdi_1 & 0x1f)) {
				uintptr_t ObjectArray = cmd::read<uintptr_t>(baseAddr + 0x8) + (rdi_1 << 3);
				return  cmd::read<BYTE>(baseAddr + 0x14) > 1
					? cmd::read <uintptr_t>(ObjectArray)
					: ~cmd::read<uint32_t>(ObjectArray);
			}
		}
		return 0;
	}

	uint64_t networkable_key(uint64_t address) {
		__int64* a2;
		__int64 a3;
		__int64* v3; // rbx
		unsigned int v5; // ecx
		int v6; // eax
		bool v7; // zf
		__int64 v8; // rcx
		__int64 v9; // rax
		__int64 v10; // rcx
		__int64 v11; // rbp
		__int64 v12; // rbx
		__int64 v13; // rsi
		int v14; // eax
		__int64 v15; // rax
		signed __int64 v16; // rcx
		__int64 v17; // rbx
		unsigned int v18; // eax
		__int64 v20; // rax
		__int64 v21; // rbx
		__int64 v22; // rax
		__int64 v23; // rax
		__int64 v24; // [rsp+20h] [rbp-28h] BYREF
		signed __int64 v25; // [rsp+50h] [rbp+8h] BYREF

		a2 = &v24;
		v24 = cmd::read<uint64_t>(address + 24);
		LODWORD(a3) = 2;
		do
		{
			v5 = *(_DWORD*)a2;
			v6 = *(_DWORD*)a2;
			a2 = (__int64*)((char*)a2 + 4);
			*((_DWORD*)a2 - 1) = (((((v6 << 22) | (v5 >> 10)) + 656138671) << 11) | ((((v6 << 22) | (v5 >> 10)) + 656138671) >> 21))
				- 1352039990;
			v7 = (_DWORD)a3 == 1;
			a3 = (unsigned int)(a3 - 1);
		} while (!v7);
		v8 = v24;
		return Il2CppGetHandle(v24);
	}

	uint64_t networkable_key2(uint64_t pointer)  // update
	{
		__int64* a2;
		_int64 a3;
		__int64* v3; // rbx
		int v5; // eax
		unsigned int v6; // eax
		bool v7; // zf
		__int64 v8; // rcx
		__int64 v9; // rax
		__int64 v10; // rcx
		__int64 v11; // rbp
		__int64 v12; // rbx
		__int64 v13; // rsi
		int v14; // eax
		__int64 v15; // rax
		signed __int64 v16; // rcx
		__int64 v17; // rbx
		__int64 v19; // rax
		__int64 v20; // rbx
		__int64 v21; // rax
		__int64 v22; // rax
		__int64 v23; // [rsp+20h] [rbp-28h] BYREF
		signed __int64 v24; // [rsp+50h] [rbp+8h] BYREF
		a2 = &v23;
		v23 = cmd::read<uint64_t>(pointer + 24);
		LODWORD(a3) = 2;
		do
		{
			v5 = *(_DWORD*)a2;
			a2 = (__int64*)((char*)a2 + 4);
			v6 = (((v5 + 1408399105) << 28) | ((unsigned int)(v5 + 1408399105) >> 4)) + 1449545954;
			*((_DWORD*)a2 - 1) = (v6 << 21) | (v6 >> 11);
			v7 = (_DWORD)a3 == 1;
			a3 = (unsigned int)(a3 - 1);
		} while (!v7);
		v8 = v23;

		return Il2CppGetHandle(v23);
	}

	inline uint64_t DecryptPlayerInventory(uint64_t Address) {
		__int64* a2;
		__int64 a3;
		__int64* v3; // rbx
		unsigned int v5; // ecx
		unsigned int v6; // eax
		bool v7; // zf
		__int64 v8; // rcx
		__int64 v9; // rax
		__int64 v10; // rcx
		__int64 v11; // rbp
		__int64 v12; // rbx
		__int64 v13; // rsi
		int v14; // eax
		__int64 v15; // rax
		signed __int64 v16; // rcx
		__int64 v17; // rbx
		__int64 v19; // rax
		__int64 v20; // rbx
		__int64 v21; // rax
		__int64 v22; // rax
		__int64 v23; // [rsp+20h] [rbp-28h] BYREF

		signed __int64 v24; // [rsp+50h] [rbp+8h] BYREF
		a2 = &v23;
		v23 = cmd::read<uint64_t>(Address + 24);
		LODWORD(a3) = 2;
		do
		{
			v5 = *(_DWORD*)a2;
			v6 = *(_DWORD*)a2;
			a2 = (__int64*)((char*)a2 + 4);
			*((_DWORD*)a2 - 1) = ((((v6 << 23) | (v5 >> 9)) ^ 0x2D9DE272) + 1786976841) ^ 0x80042B5A;
			v7 = (_DWORD)a3 == 1;
			a3 = (unsigned int)(a3 - 1);
		} while (!v7);
		v8 = v23;

		return Il2CppGetHandle(v23);
	}

	uint64_t decrypt_eyes(uint64_t a1) {
		__int64* v3; // rbx
		int v5; // eax
		bool v6; // zf
		__int64 v7; // rcx
		__int64 v8; // rax
		__int64 v9; // rcx
		__int64 v10; // rbp
		__int64 v11; // rbx
		__int64 v12; // rsi
		int v13; // eax
		__int64 v14; // rax
		signed __int64 v15; // rcx
		__int64 v16; // rbx
		__int64 v18; // rax
		__int64 v19; // rbx
		__int64 v20; // rax
		__int64 v21; // rax
		__int64 v22; // [rsp+20h] [rbp-28h] BYREF
		signed __int64 v23; // [rsp+50h] [rbp+8h] BYREF

		__int64* a2;
		__int64 a3;

		a2 = &v22;
		v22 = cmd::read<uint64_t>(a1 + 24);
		LODWORD(a3) = 2;
		do
		{
			v5 = *(_DWORD*)a2;
			a2 = (__int64*)((char*)a2 + 4);
			*((_DWORD*)a2 - 1) = (((v5 + 657907416) << 7) | ((unsigned int)(v5 + 657907416) >> 25)) - 173559052;
			v6 = (_DWORD)a3 == 1;
			a3 = (unsigned int)(a3 - 1);
		} while (!v6);
		v7 = v22;

		return Il2CppGetHandle(v22);
	}

	auto decrypt_ClActiveItem(std::uint64_t a1) -> std::uint64_t {
		__int64 v2; // rdx
		long long* v3; // rdx
		int v4; // r8d
		unsigned int v5; // ecx
		unsigned int v6; // eax
		__int64 result; // rax
		__int64 v8; // rcx
		signed __int32 v9[8]; // [rsp+0h] [rbp-38h] BYREF
		long long v10; // [rsp+20h] [rbp-18h] BYREF
		v3 = &v10;
		v4 = 2;
		v10 = a1;
		do
		{
			v5 = *(_DWORD*)v3;
			v6 = *(_DWORD*)v3;
			v3 = (long long*)((char*)v3 + 4);
			*((_DWORD*)v3 - 1) = (((((v6 << 7) | (v5 >> 25)) - 2064472425) << 10) | ((((v6 << 7) | (v5 >> 25)) - 2064472425) >> 22))
				- 1699390350;
			--v4;
		} while (v4);
		return v10;
	}
}

class HeldItem {
public:

	std::uint64_t Address()
	{
		return (std::uint64_t)(this);
	}

	std::string get_prefab() {
		if (this == nullptr) {
			return " ";
		}

		uintptr_t unk = cmd::read<uintptr_t>((uintptr_t)this + Offsets::ItemDefinition);
		if (unk == 0) {
			return "Invalid ItemDefinition";
		}

		uintptr_t ItemDisplayName = cmd::read<uintptr_t>(unk + 0x38);
		if (ItemDisplayName == 0) {
			return "Invalid ItemDisplayName";
		}

		uintptr_t ItemDisplayEnglish = cmd::read<uintptr_t>(ItemDisplayName + 0x20);
		if (ItemDisplayEnglish == 0) {
			return "Invalid ItemDisplayEnglish";
		}

		return cmd::read_wstr(ItemDisplayEnglish + 0x14);
	}


	std::string get_item_name() {
		if (!(uintptr_t)this) return "Empty";
		uintptr_t unk = cmd::read<uintptr_t>((uintptr_t)this + Offsets::ItemDefinition); // item def (UPDATED)
		if (!cmd::Valid(unk)) return "Empty";;

		uintptr_t ItemDisplayName = cmd::read< uintptr_t>(unk + 0x38); // item display name (UPDATED)
		if (!cmd::Valid(ItemDisplayName)) return "Empty";

		uintptr_t ItemDisplayEnglish = cmd::read< uintptr_t>(ItemDisplayName + 0x20); // ItemDisplayEnglish (UPDATED)
		if (!cmd::Valid(ItemDisplayEnglish)) return "Empty";

		return cmd::read_wstr(ItemDisplayEnglish + 0x14);
	}

	std::string get_short_name() {
		if (!(uintptr_t)this) return "Empty";
		uintptr_t unk = cmd::read<uintptr_t>((uintptr_t)this + Offsets::ItemDefinition); // item def (UPDATED)
		if (!cmd::Valid(unk)) return "Empty";

		uintptr_t ItemDisplayName = cmd::read< uintptr_t>(unk + 0x20); // ITEM SHORTNAME (UPDATED)
		if (!cmd::Valid(ItemDisplayName)) return "Empty";

		return cmd::read_wstr(ItemDisplayName + 0x14);
	}

	bool is_weapon() {
		static const std::vector<std::string> weaponitems = {
			(std::string)("rifle"),
			(std::string)("pistol"),
			(std::string)("lmg"),
			(std::string)("shotgun"),
			(std::string)("smg")
		};
		auto ws = this->get_short_name();
		std::string ItemName(ws.begin(), ws.end());
		for (const auto& item : weaponitems) {
			if (ItemName.find(("eoka")) != std::string::npos) return false;
			if (ItemName.find(item) != std::string::npos) return true;
		}
		return false;
	}

	bool is_melee() {
		static const std::vector<std::string> meele_items = {
			(std::string)("rock"),
			(std::string)("hatchet"),
			(std::string)("stone.pickaxe"),
			(std::string)("stonehatchet"),
			(std::string)("pickaxe"),
			(std::string)("hammer.salvage"),
			(std::string)("icepick.salvag"),
			(std::string)("axe.salvaged"),
			(std::string)("pitchfork"),
			(std::string)("mace"),
			(std::string)("spear.stone"),
			(std::string)("spear.wooden"),
			(std::string)("machete"),
			(std::string)("bone.club"),
			(std::string)("paddle"),
			(std::string)("salvaged.sword"),
			(std::string)("salvaged.cleav"),
			(std::string)("knife.combat"),
			(std::string)("knife.butcher"),
			(std::string)("knife.bone"),
			(std::string)("hammer"),
			(std::string)("torch"),
			(std::string)("sickle")
		};

		std::string ItemName = this->get_short_name();
		for (const auto& item : meele_items) {
			if (ItemName.find(item) != std::string::npos) return true;
		}
		return false;
	}
};


enum class LifeState : unsigned int
{
	Alive = 0,
	Dead = 1
};


class PlayerEyes
{
private:
public:
	std::uint64_t Address()
	{
		return (std::uint64_t)(this);
	}

	Vector4 BodyRotation()
	{
		if (!cmd::Valid(this->Address()))return Vector4(-1, -1, -1, -1);
		return cmd::read<Vector4>(this->Address() + 0x50);
	}

	void SetViewOffset(Vector3 value)
	{
		cmd::write<Vector3>(this->Address() + Offsets::BPlayerEyes, value);
	}

	void SetBodyRotation(Vector4 Value)
	{
		if (!cmd::Valid(this->Address())) return;

		cmd::write<Vector4>(this->Address() + 0x50, Value);
	}
};

struct dynamic_array { uint64_t base; uint64_t mem_id; uint64_t sz; uint64_t cap; };

class BaseEntity
{
private:
public:

	std::uint64_t Address()
	{
		return (std::uint64_t)(this);
	}

	LifeState Lifestate()
	{
		return cmd::read<LifeState>(this->Address() + Offsets::lifestate); //lifestate  offset (UPDATED)
	}

	Vector3 Position()
	{
		auto model = cmd::read<uintptr_t>(this->Address() + Offsets::PlayerModel); // player model offset (UPDATED)
		if (!cmd::Valid(model))return Vector3(-1, -1, -1);

		auto pos = cmd::read<Vector3>(model + Offsets::PlayerPos); // position offset (UPDATED)
		return pos;
	}

	bool HasFlag(std::uint32_t Value)
	{
		return (cmd::read<std::uint32_t>(this->Address() + Offsets::playerFlags)) & Value; // playerFlags  offset (UPDATED)
	}

	bool HasEvent(std::uint32_t Value) // this is in testing #ud
	{
		return (cmd::read<std::uint32_t>(this->Address() + 0x8)) & Value; // Looking for a offset for crate events and shit.
	}

	std::string Name()
	{
		if (!cmd::Valid(this->Address()))return "";
		return cmd::ReadWString(this->Address() + Offsets::_displayName); //disply name offset (UPDATED)
	}

	unsigned long TeamID()
	{
		return cmd::read<unsigned long>(this->Address() + Offsets::clientTeam); //Current Team (UPDATED)
	}

	Vector3 GetInputOffset()
	{
		auto input = cmd::read<uintptr_t>(this->Address() + Offsets::PlayerInput); // playerInput offset (NOT UPDATED) 
		if (!cmd::Valid(input))return Vector3(-1, -1, -1);


		return cmd::read<Vector3>(input + 0x44);
	}

	void SetInputOffset(Vector3 value)
	{
		auto input = cmd::read<uintptr_t>(this->Address() + 0x320);
		if (!cmd::Valid(input))return;


		cmd::write<Vector3>(input + 0x44, value);
	}

	PlayerEyes* GetEyes()
	{

		auto PlayerEyes_encrypted = cmd::read<uint64_t>(this->Address() + Offsets::BPlayerEyes); // eyes  offset (UPDATED)
		if (!cmd::Valid(PlayerEyes_encrypted)) return nullptr;

		auto eyes = decrypt::DecryptPlayerInventory(PlayerEyes_encrypted);

		return (PlayerEyes*)eyes;
		std::cout << "Player Eyes ->" << eyes << std::endl; // for debugging purposes
	}

	HeldItem* Get_HeldItem() {
		HeldItem* item = nullptr;
		uint64_t active_item_id = cmd::read<uint64_t>((uintptr_t)this + Offsets::clActiveItem); //clactiveitem (UPDATED)
		int uiddecrypt = decrypt::decrypt_ClActiveItem(active_item_id);
		std::cout << "Active Item Pointer -> " << uiddecrypt << std::endl;
		uintptr_t player_inventory = decrypt::DecryptPlayerInventory(cmd::read<uint64_t>((uintptr_t)this + Offsets::Playerinventory)); //playerinventory (UPDATED)
		std::cout << "Player Inv Pointer -> " << player_inventory << std::endl;
		if (!cmd::Valid(player_inventory)) return nullptr;
		uint64_t inventory_belt = cmd::read<uint64_t>(player_inventory + Offsets::containerBelt); // Container belt (UPDATED)
		std::cout << "Inventory Belt Pointer -> " << inventory_belt << std::endl;
		if (!cmd::Valid(inventory_belt)) return nullptr;
		uint64_t belt_contents_list = cmd::read<uint64_t>(inventory_belt + Offsets::itemlist); // Item list / Content list (UPDATED)
		std::cout << "Belt Contents List Pointer -> " << belt_contents_list << std::endl;
		if (!cmd::Valid(belt_contents_list)) return nullptr;
		uint64_t belt_contents = cmd::read<uint64_t>(belt_contents_list + 0x60); // Item array (NOT UPDATED)
		std::cout << "Belt Contents Pointer -> " << belt_contents << std::endl;
		if (!cmd::Valid(belt_contents)) return nullptr;
		for (auto i = 0; i <= 6; i++) {
			if (belt_contents != 0) {
				uint64_t current_item = cmd::read<uint64_t>(belt_contents + (0x20 + (i * 8)));
				if (!cmd::Valid(current_item))continue;

				std::cout << "Current Item Pointer -> " << belt_contents << std::endl; 

				if (!current_item) continue;
				if (uiddecrypt == cmd::read<uint64_t>(current_item + Offsets::Itemuid)) {
					item = (HeldItem*)current_item;
					return item;
				}
			}
		}
		return item;
	}

	/*Math::Vector3 Position()
	{
		if (!validpointer(this->Address())) { Log("Invalid adress (Position)"); return{ }; }
		return ctx->read<Math::Vector3>(ctx->ReadChain<std::uint64_t>(this->Address(), { 0x10, 0x30,0x30,0x8,0x38 }) + 0x90);
	}

	SDK::Model* Model()
	{
		if (!validpointer(this->Address())) { Log("Invalid adress (Model)"); return{ }; }
		return ctx->read<SDK::Model*>(this->Address() + Offsets::BaseEntity::model);
	}*/
};




struct Camera
{
	Transformation* Get_Transformation(BaseEntity* entity, int bone) {
		uintptr_t player_model = cmd::read<uintptr_t>(entity->Address() + 0xC8); // BaseCombatEntity MODEL (NOT UPDATED)
		if (!cmd::Valid(player_model)) return nullptr;

		uintptr_t boneTransforms = cmd::read<uintptr_t>(player_model + 0x50);
		if (!cmd::Valid(boneTransforms)) return nullptr;

		Transformation* BoneValue = cmd::read<Transformation*>((boneTransforms + (0x20 + (bone * 0x8))));

		return BoneValue;
	}

	bool IsOnScreen(Vector2 Vec)
	{
		return Vec.x >= 0 && Vec.x <= Monitor::Width && Vec.y >= 0 && Vec.y <= Monitor::Height;
	}


	auto InScreen(Vector2 screen_position) -> bool {
		if (screen_position.x > 0 && screen_position.x < Monitor::Width && screen_position.y > 0 && screen_position.y < Monitor::Height)
			return true;
		else
			return false;
	}

	inline bool WorldToScreen(const Vector3& World, Vector2* ScreenOut, Matrix4x4 ViewMatrix)
	{
		Vector3 TransposeVector{ ViewMatrix._14, ViewMatrix._24, ViewMatrix._34 };
		Vector3 RightVector{ ViewMatrix._11, ViewMatrix._21, ViewMatrix._31 };
		Vector3 UpVector{ ViewMatrix._12, ViewMatrix._22, ViewMatrix._32 };

		// Getting Values
		float W = TransposeVector.Dot(World) + ViewMatrix._44;
		float X = RightVector.Dot(World) + ViewMatrix._41;
		float Y = UpVector.Dot(World) + ViewMatrix._42;

		// Setting Screen Position
		if (ScreenOut)
		{
			*ScreenOut = Vector2(Monitor::CenterX * (1.00f + X / W), Monitor::CenterY * (1 - Y / W));
		}
		else
		{
			return W > 0.098f;
		}

		// Validating Screen Position
		return ScreenOut->IsValid() && W > 0.098f;
		/*Vector3 trans_vec{ view_matrix._14, view_matrix._24, view_matrix._34 };
		Vector3 right_vec{ view_matrix._11, view_matrix._21, view_matrix._31 };
		Vector3 up_vec{ view_matrix._12, view_matrix._22, view_matrix._32 };

		float w = trans_vec.Dot(entity_position) + view_matrix._44;

		if (w < 0.1f) return Vector2();

		float y = up_vec.Dot(entity_position) + view_matrix._42;
		float x = right_vec.Dot(entity_position) + view_matrix._41;

		Vector2 Screen_position = Vector2((GetSystemMetrics(SM_CXSCREEN) / 2) * (1.f + x / w), (GetSystemMetrics(SM_CYSCREEN) / 2) * (1.f - y / w));
		return Screen_position;*/
	}
}; static Camera* camerashi = new Camera();

float GetDistance2D(const Vector2& a, const Vector2& b) {
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	return std::sqrt(dx * dx + dy * dy);
}

struct Public
{
	BaseEntity* LocalPlayer;
	uint64_t entity;
	uint64_t entity_array;
	uint32_t entity_size;
	HeldItem* item;
	uintptr_t BaseProjectile;
	Matrix4x4  Matrix;
	Vector3 CameraPos;

}; static Public* pointers = new Public();


class PlayerActors {
public:

	BaseEntity* Player;
};


class LootActors {
public:

};


typedef struct _LootEntity {
	Vector3 location;
	std::string name;
	HeldItem* items;
	std::string ClassName;
	uintptr_t Address() const { return reinterpret_cast<uintptr_t>(this); }

	bool HasEvent(std::uint32_t Value) const {
		return (cmd::read<std::uint32_t>(this->Address() + 0x8)) & Value;
	}
} LootEntity;

typedef struct _Entity
{
	BaseEntity* Player;
} Entity;

struct EntityData
{
	uintptr_t entity_loop;
	uintptr_t object;
	uintptr_t object_class;
	std::string buff;
};

std::vector<LootEntity> ItemList;
std::vector<Entity> EntityList;

std::vector<LootActors> Loot;
std::vector<LootActors> TempLoot;


float target_dist = FLT_MAX;
BaseEntity* AimbotPlayer;
std::vector<BaseEntity*> Players;
std::atomic<bool> running = true;
std::thread cacheThread;
std::vector<EntityData> entityCache;


auto CacheMainInfo() -> bool
{
	static uint64_t basenetworkable = cmd::read<uint64_t>(cmd::vrtxrr22 + Offsets::BaseNetworkable);
	if (!cmd::Valid(basenetworkable)) return false;

	static uint64_t static_fields = cmd::read<uint64_t>(basenetworkable + 0xB8);
	if (!cmd::Valid(static_fields)) return false;

	static uint64_t wrapper_class_ptr = cmd::read<uint64_t>(static_fields + 0x10);
	if (!cmd::Valid(wrapper_class_ptr)) return false;

	static uint64_t wrapper_class = decrypt::networkable_key(wrapper_class_ptr);
	if (!cmd::Valid(wrapper_class)) return false;

	static uint64_t parent_static_fields = cmd::read<uint64_t>(wrapper_class + 0x10);
	if (!cmd::Valid(parent_static_fields)) return false;

	static uint64_t parent_class = decrypt::networkable_key2(parent_static_fields);

	pointers->entity = cmd::read<uint64_t>(parent_class + 0x20);
	if (!cmd::Valid(pointers->entity)) return false;

	return true;
}

void CachePlayers(uint64_t entity_array, uint32_t entity_size)
{
	std::vector<Entity> tempList;

	for (const auto& test : entityCache)
	{
		if (values::Playerdebug == 1) {
			std::cout << test.buff << std::endl;
		}

		bool isScientist = (test.buff.find("scientistnpc") != std::string::npos) && values::visuals::show_scientists;
		bool isTunnelDweller = (test.buff.find("npc_tunneldweller") != std::string::npos) && values::visuals::show_scientists;
		bool isPlayerPrefab = test.buff.find("player.prefab") != std::string::npos;

		if (isPlayerPrefab || isScientist || isTunnelDweller)
		{
			BaseEntity* Player = cmd::read<BaseEntity*>(test.object + 0x28);

			if (Player->Lifestate() == LifeState::Dead) continue;
			if (Player->HasFlag(16) && !values::visuals::show_sleepers) continue;
			if (Player->HasFlag(64) && !values::visuals::show_wounded) continue;

			tempList.push_back({ Player });
		}
	}

	EntityList.clear();
	EntityList.swap(tempList);
}


void CacheWorldEntities(uint64_t entity_array, uint32_t entity_size) {
	std::vector<LootEntity> tmpItemList;

	for (auto test : entityCache)
	{
		if (values::Worlddebug == 1)
		{
			std::cout << test.buff << std::endl;
		}

		auto ukn01 = cmd::read<uintptr_t>(test.object + 0x28);

		auto ukn02 = cmd::read<uintptr_t>(ukn01);
		if (!ukn02)
			continue;
		std::string entityClass = cmd::read<monostr>(cmd::read<uintptr_t>(ukn02 + 0x10)).buffer;

		intptr_t objectPtr2 = cmd::read<uintptr_t>(test.object + 0x30);
		if (!objectPtr2)
		{
			continue;
		}

		uintptr_t objectPtr3 = cmd::read<uintptr_t>(objectPtr2 + 0x30);
		if (!objectPtr3)
		{
			continue;
		}

		uintptr_t objectPtr4 = cmd::read<uintptr_t>(objectPtr3 + 0x8);
		if (!objectPtr4)
		{
			continue;
		}

		uintptr_t objectPtr5 = cmd::read<uintptr_t>(objectPtr4 + 0x38);
		if (!objectPtr5)
		{
			continue;
		}

		Vector3 EntityPosition = cmd::read<Vector3>(objectPtr5 + 0x90);

		HeldItem* loot = nullptr;

		if (entityClass.find("DroppedItem") != std::string::npos) {
			loot = cmd::read<HeldItem*>(test.entity_loop + 0x1A8);
		}

		LootEntity itemObject{};
		itemObject.location = EntityPosition;
		if (test.buff.find("box.") != std::string::npos || test.buff.find("codelockedhackablecrate") != std::string::npos || test.buff.find("coffinstorage") != std::string::npos || test.buff.find("storage_barrel") != std::string::npos || test.buff.find("generator.") != std::string::npos || test.buff.find("rechargable.battery") != std::string::npos || test.buff.find("player_corpse") != std::string::npos || test.buff.find("autoturret") != std::string::npos || test.buff.find("guntrap") != std::string::npos || test.buff.find("hemp-collectable") != std::string::npos || test.buff.find("sleepingbag") != std::string::npos || test.buff.find("bed_deployed") != std::string::npos || test.buff.find("cupboard.tool") != std::string::npos || test.buff.find("stone-ore") != std::string::npos || test.buff.find("metal-ore") != std::string::npos || test.buff.find("sulfur-ore") != std::string::npos || test.buff.find("samsite") != std::string::npos || test.buff.find("item_drop_backpack") != std::string::npos || test.buff.find("item_drop") != std::string::npos || test.buff.find("foodbox") != std::string::npos || test.buff.find("wood-pile") != std::string::npos || test.buff.find("supply_drop") != std::string::npos)
		{
			itemObject.name = test.buff;
		}
		itemObject.items = loot;
		itemObject.ClassName = entityClass;

		tmpItemList.push_back(itemObject);
	}
	ItemList.clear();
	ItemList.swap(tmpItemList);
}

void GetComponentsInChildren(uintptr_t GameObject, std::vector<uintptr_t>& renderers)
{
	if (GameObject == 0) return;

	auto componentList = cmd::read<uint64_t>(GameObject + 0x30);
	int componentSize = cmd::read<int>(GameObject + 0x40);

	for (int j = 0; j < componentSize; ++j) {
		uintptr_t component = cmd::read<uint64_t>(componentList + (0x10 * j + 0x8));
		if (component == 0) continue;

		auto componentInst = cmd::read<uint64_t>(component + 0x28);
		if (componentInst == 0) continue;
		auto componentObject = cmd::read<uint64_t>(componentInst + 0x0);
		if (componentObject == 0) continue;
		auto componentName = cmd::read<uint64_t>(componentObject + 0x10);
		if (componentName == 0) continue;
		std::string Name = cmd::read_wstr(componentName);

		if (Name == "SkinnedMeshRenderer") {
			renderers.push_back(component);
		}
		if (Name == "Transform") {
			uintptr_t childList = cmd::read<uint64_t>(component + 0x70);
			int childSize = cmd::read<int>(component + 0x80);

			for (int i = 0; i < childSize; ++i) {
				uint64_t childTransform = cmd::read<uint64_t>(childList + (0x8 * i));
				if (childTransform == 0) continue;

				auto childGameObject = cmd::read<uint64_t>(childTransform + 0x30);
				if (childGameObject == 0) continue;
				auto childGameObjectName = cmd::read<uint64_t>(childGameObject + 0x60);
				if (childGameObject == 0) continue;
				std::string childName = cmd::read_wstr(childGameObjectName);

				GetComponentsInChildren(childGameObject, renderers);
			}
		}
	}
}

void Cache()
{
	while (running)
	{
		std::vector<EntityData> tmpEntityCache;

		if (CacheMainInfo())
		{
			pointers->entity_array = cmd::read<uint64_t>(pointers->entity + 0x18);
			pointers->entity_size = cmd::read<uint32_t>(pointers->entity + 0x10);

			pointers->LocalPlayer = cmd::read<BaseEntity*>(pointers->entity_array + 0x20);

			for (auto i = 0; i <= pointers->entity_size; i++) {
				uintptr_t entity_loop = cmd::read<uintptr_t>((uint64_t)pointers->entity_array + +(i * 0x8));
				if (!cmd::Valid(entity_loop)) continue;

				uintptr_t object = cmd::read<uintptr_t>(entity_loop + 0x10);
				if (!cmd::Valid(object)) continue;

				uintptr_t object_class = cmd::read<uintptr_t>(object + 0x30);
				if (!cmd::Valid(object_class)) continue;


				std::string buff = cmd::read<monostr>(cmd::read<uintptr_t>(object_class + 0x60)).buffer;
				if (buff.empty()) continue;

				tmpEntityCache.push_back({ entity_loop, object, object_class, buff });
			}
		}
		std::swap(entityCache, tmpEntityCache);
		std::move(tmpEntityCache);
		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
}

void PlayerCache()
{
	while (running)
	{
		CachePlayers(pointers->entity_array, pointers->entity_size);
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
	}
}


void WorldCache()
{
	while (running) {
		CacheWorldEntities(pointers->entity_array, pointers->entity_size);
		std::this_thread::sleep_for(std::chrono::microseconds(2));
	}

}


void RestartCache()
{
	running = false;
	if (cacheThread.joinable())
	{
		cacheThread.join();
	}

	running = true;
	cacheThread = std::thread(Cache);
}

struct Data
{	

	auto Init() -> void
	{
		RestartCache();

		console->WriteString("Starting Cache Thread");
		std::thread(Cache).detach();
		console->WriteString("Starting Player Thread");
		std::thread(PlayerCache).detach();
		console->WriteString("Starting World Thread");
		std::thread(WorldCache).detach();
		console->WriteString("Finished");
	}

}; static Data* data = new Data();
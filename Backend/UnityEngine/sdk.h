#include <cstdint>
#include <corecrt_math.h>
#include <corecrt_math_defines.h>
#include <d3d9types.h>
#include <d3d9.h>
#include <array>
#include "../Driver/driver.h"
#include "../includes/dxsdk/Include/d3dx9tex.h"

enum BoneList : int
{
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};

class Vector2
{
public:
	float x, y;

	Vector2() {};

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 operator+(const Vector2& Input)
	{
		return Vector2{ x + Input.x, y + Input.y };
	}

	Vector2 operator-(const Vector2& Input)
	{
		return Vector2{ x - Input.x, y - Input.y };
	}

	Vector2 operator*(const Vector2& Input)
	{
		return Vector2{ x * Input.x, y * Input.y };
	}

	Vector2 operator/(const float& Input)
	{
		return Vector2{ x / Input, y / Input };
	}


	Vector2 operator*(const float& Input)
	{
		return Vector2{ x * Input, y * Input };
	}

	bool IsValid()
	{
		return x && y;
	}

	float Length()
	{
		return std::sqrt((x * x) + (y * y));
	}

	float Distance(Vector2 To)
	{
		return std::sqrt(std::pow(To.x - x, 2.f) + std::pow(To.y - y, 2.f));
	}

	Vector2 Normalize()
	{
		if (y <= -180.f) y += 360.f;
		else if (y > 180.f) y -= 360.f;

		if (x > 90.f) x -= 180.f;
		else if (x <= -90.f) x += 180.f;

		return { x, y };
	}

	void Clamp()
	{
		x = std::clamp(x, -89.0f, 89.0f);
		y = std::clamp(y, -179.0f, 179.0f);
	}
};

class Vector3
{
public:
	float x, y, z;

	Vector3()
	{
		x = 0.f;
		y = 0.f;
		z = 0.f;
	}

	Vector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 operator+(const Vector3& Input)
	{
		return Vector3{ x + Input.x, y + Input.y, z + Input.z };
	}

	Vector3 operator-(const Vector3& Input)
	{
		return Vector3{ x - Input.x, y - Input.y, z - Input.z };
	}

	Vector3 operator/(float Input)
	{
		return Vector3{ x / Input, y / Input, z / Input };
	}

	Vector3 operator*(float Input)
	{
		return Vector3{ x * Input, y * Input, z * Input };
	}

	Vector3& operator+=(const Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	Vector3& operator-=(const Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	Vector3& operator/=(float Input)
	{
		x /= Input;
		y /= Input;
		z /= Input;

		return *this;
	}

	Vector3& operator*=(float Input)
	{
		x *= Input;
		y *= Input;
		z *= Input;

		return *this;
	}

	bool operator==(const Vector3& Input)
	{
		return x == Input.x && y == Input.y && z == Input.z;
	}

	void MakeAbsolute()
	{
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
	}

	float LengthSqr() const
	{
		return (x * x) + (y * y) + (z * z);
	}

	float Length() const
	{
		return (float)std::sqrt(LengthSqr());
	}

	float Length2D() const
	{
		return (float)sqrt((x * x) + (y * y));
	}

	float Magnitude() { return (float)sqrt(x * x + y * y + z * z); }
	float Magnitude2D() { return (float)sqrt(x * x + z * z); }

	Vector3 Normalize() const
	{
		Vector3 tis(this->x, this->y, this->z);
		float num = Vector3(this->x, this->y, this->z).Magnitude();
		if (num > 1E-05f)
		{
			tis.x /= num;
			tis.y /= num;
			tis.z /= num;
		}
		else
			tis = { 0, 0, 0 };


		return { tis.x, tis.y, tis.z };
	}


	Vector3 Cross(Vector3 rhs) const
	{
		return Vector3(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
	}

	float Dot(Vector3 Input) const
	{
		return (x * Input.x + y * Input.y + z * Input.z);
	}

	float Distance(Vector3 Input)
	{
		return (*this - Input).Length();
	}

	float DistanceSqr(Vector3 Input)
	{
		Vector3 Difference = { x - Input.x, y - Input.y, z - Input.z };
		return Difference.x * Difference.x + Difference.y * Difference.y + Difference.z * Difference.z;
	}

	float Distance2D(Vector3 Input)
	{
		return (*this - Input).Length2D();
	}

	void Clamp()
	{
		std::clamp(x, -89.f, 89.f);
		std::clamp(y, -180.f, 180.f);
		z = 0.f;
	}

	bool IsValid() const
	{
		return !(x == 0.f && y == 0.f && z == 0.f) || (x == -1.f && y == -1.f && z == -1.f);
	}
};


inline double GetCrossDistance(double x1, double y1, double x2, double y2) {
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

struct Vector4 {
	float x, y, z, w;
};

inline const double ToRad(double degree)
{
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}

inline Vector4 ToQuat(Vector3 Euler) {
	float c1 = cos(ToRad(Euler.x) / 2);
	float s1 = sin(ToRad(Euler.x) / 2);
	float c2 = cos(ToRad(Euler.y) / 2);
	float s2 = sin(ToRad(Euler.y) / 2);
	float c3 = cos(ToRad(Euler.z) / 2);
	float s3 = sin(ToRad(Euler.z) / 2);
	float c1c2 = c1 * c2;
	float s1s2 = s1 * s2;
	float c1s2 = c1 * s2;
	float s1c2 = s1 * c2;
	Vector4 Quat = {
		s1c2 * c3 + c1s2 * s3,
		c1s2 * c3 - s1c2 * s3,
		c1c2 * s3 - s1s2 * c3,
		c1c2 * c3 + s1s2 * s3
	};
	return Quat;
}
struct Matrix4x4
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
};

namespace DirectX9Interface
{
	IDirect3D9Ex* p_object = NULL;
	IDirect3DDevice9Ex* p_device = NULL;
	D3DPRESENT_PARAMETERS p_params = { NULL };
	MSG message = { NULL };
	HWND hijacked_hwnd = NULL;
	HWND game_wnd = NULL;
}

Vector2 cos_tan_horizontal(float angle, float range, float x, float y, int length) {
	float our_angle = (angle + 45.f);

	float yaw = our_angle * (3.14159265358979323846 / 180.0);

	float view_cosinus = cos(yaw);
	float view_sinus = sin(yaw);

	float x2 = range * (-view_cosinus) + range * view_sinus;
	float y2 = range * (-view_cosinus) - range * view_sinus;

	int screen_x = x + static_cast<int>(x2 / range * length);
	int screen_y = y + static_cast<int>(y2 / range * length);

	return Vector2(screen_x, screen_y);
}

class Transformation {
public:
	Vector3 Get_Position() {
		auto transform_internal = cmd::read<uint64_t>((uintptr_t)this + 0x10);
		if (!transform_internal) return Vector3(0, 0, 0);
		struct tempshit1 { uint64_t some_ptr; int32_t index; } temp;
		cmd::readphy((transform_internal + 0x38), &temp, sizeof(temp));
		if (!temp.some_ptr) return Vector3();
		struct tempshit2 { uint64_t relation_array; int64_t dependency_index_array; } temp2;
		cmd::readphy((temp.some_ptr + 0x18), &temp2, sizeof(temp2));
		if (!temp2.relation_array) return Vector3();
		if (!temp2.dependency_index_array) return Vector3();

		//__m128i temp_0;
		__m128 xmmword_1410D1340 = { -2.f, 2.f, -2.f, 0.f };
		__m128 xmmword_1410D1350 = { 2.f, -2.f, -2.f, 0.f };
		__m128 xmmword_1410D1360 = { -2.f, -2.f, 2.f, 0.f };
		//__m128 temp_1;
		//__m128 temp_2;
		auto temp_main = cmd::read<__m128>(temp2.relation_array + temp.index * 48);
		auto dependency_index = cmd::read<int32_t>(temp2.dependency_index_array + 4 * temp.index);

		while (dependency_index >= 0) {
			auto relation_index = 6 * dependency_index;
			struct tempshit3 { __m128 temp_2; __m128i temp_0; __m128 temp_1; } temp3;
			cmd::readphy((temp2.relation_array + 8 * relation_index), &temp3, sizeof(temp3));
			__m128 v10 = _mm_mul_ps(temp3.temp_1, temp_main);
			__m128 v11 = _mm_castsi128_ps(_mm_shuffle_epi32(temp3.temp_0, 0));
			__m128 v12 = _mm_castsi128_ps(_mm_shuffle_epi32(temp3.temp_0, 85));
			__m128 v13 = _mm_castsi128_ps(_mm_shuffle_epi32(temp3.temp_0, -114));
			__m128 v14 = _mm_castsi128_ps(_mm_shuffle_epi32(temp3.temp_0, -37));
			__m128 v15 = _mm_castsi128_ps(_mm_shuffle_epi32(temp3.temp_0, -86));
			__m128 v16 = _mm_castsi128_ps(_mm_shuffle_epi32(temp3.temp_0, 113));
			__m128 v17 = _mm_add_ps(
				_mm_add_ps(
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v11, xmmword_1410D1350), v13),
								_mm_mul_ps(_mm_mul_ps(v12, xmmword_1410D1360), v14)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), -86))),
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v15, xmmword_1410D1360), v14),
								_mm_mul_ps(_mm_mul_ps(v11, xmmword_1410D1340), v16)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 85)))),
					_mm_add_ps(
						_mm_mul_ps(
							_mm_sub_ps(
								_mm_mul_ps(_mm_mul_ps(v12, xmmword_1410D1340), v16),
								_mm_mul_ps(_mm_mul_ps(v15, xmmword_1410D1350), v13)),
							_mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(v10), 0))),
						v10)),
				temp3.temp_2);

			temp_main = v17;
			dependency_index = cmd::read<int32_t>(temp2.dependency_index_array + 4 * dependency_index);
		}

		return *reinterpret_cast<Vector3*>(&temp_main);
	}
};

struct monostr
{
	char buffer[128];
};

namespace Monitor
{
	int Width;
	int Height;
	int CenterX;
	int CenterY;

}

namespace Math
{
	inline double RadiansToDegrees(double dRadians)
	{
		return dRadians * (180.0 / M_PI);
	}
}
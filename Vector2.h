#pragma once
#include <iosfwd>

class Vector2
{
public:
	float x;
	float y;
	
	Vector2(float _x = 0, float _y = 0) {} // default para가 기본생성자 대신

	const Vector2 Normalize() const;	// normal vector 구하는 함수
	float Magnitude() const;	// 벡터 크기 구하는 함수(값은 스칼라)

	 // 두 점의 거리 & 내적 (객체 외부에서 사용하기 위해 static)
	static float DistTwoDot(const Vector2 &vec1, const Vector2 &vec2); 
	static float DotProduct(const Vector2 &vec1, const Vector2 &vec2);

	// 연산자 오버로딩
	const Vector2 operator*(float scalar) const; // ex. vector2 * 2
	const Vector2 operator+(const Vector2 &vec); // ex. vec1 + vec2
	Vector2 & operator*=(float scalar);	// ex. vector2 *= 3
	Vector2 & operator+=(const Vector2 &vec);  // ex. vec1 += vec2
};

const Vector2 operator*(float scalar, const Vector2 & vec);
std::istream & operator>>(std::istream & is, Vector2 & vec);
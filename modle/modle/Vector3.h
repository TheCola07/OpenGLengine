#ifndef VECTOR3_H_INCLUDED
#define VECTOR3_H_INCLUDED

class Vector3 {
public:
	Vector3();
	Vector3(float x, float y, float z);
	void operator=(Vector3 vec);
	void operator*=(float num);
	void operator+=(Vector3 vec);
	Vector3 Mutiply(Vector3 vec);
	Vector3 operator+(Vector3 vec);
	Vector3 operator*(float num);

	float x, y, z;
};

#endif
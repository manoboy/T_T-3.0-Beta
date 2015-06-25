#include "Math.h"
#include "MyWindow.h"
#include "Entity.h"
ViewMatrix vMatrix;
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
float Get3dDistance(Vector3D Pos1, Vector3D Pos2)
{
	return sqrt(pow((Pos2.x - Pos1.x), 2.0) + pow((Pos2.y - Pos1.y), 2.0) + pow((Pos2.z - Pos1.z), 2.0));
};

bool WorldToScreen(Vector3D PositionIn, Vector3D &PositionOut)
{
	float w = 0.0f;

	PositionOut.x = vMatrix.Matrix[0][0] * PositionIn.x + vMatrix.Matrix[0][1] * PositionIn.y + vMatrix.Matrix[0][2] * PositionIn.z + vMatrix.Matrix[0][3];
	PositionOut.y = vMatrix.Matrix[1][0] * PositionIn.x + vMatrix.Matrix[1][1] * PositionIn.y + vMatrix.Matrix[1][2] * PositionIn.z + vMatrix.Matrix[1][3];
	w = vMatrix.Matrix[3][0] * PositionIn.x + vMatrix.Matrix[3][1] * PositionIn.y + vMatrix.Matrix[3][2] * PositionIn.z + vMatrix.Matrix[3][3];

	if (w < 0.01f)
		return false;

	float InveseValue = 1.0f / w;
	PositionOut.x *= InveseValue;
	PositionOut.y *= InveseValue;

	float x = CMyWindow::Width / 2;
	float y = CMyWindow::Height / 2;

	x += 0.5 * PositionOut.x * CMyWindow::Width + 0.5;
	y -= 0.5 * PositionOut.y * CMyWindow::Height + 0.5;

	PositionOut.x = x;
	PositionOut.y = y;

	return true;

};
Vector3D VectorSubtract(Vector3D Vec1, Vector3D Vec2)
{
	return Vector3D(Vec1.x - Vec2.x, Vec1.y - Vec2.y, Vec1.z - Vec2.z);
};
void CalcAngle(Vector3D Source, Vector3D Destination, Vector3D &Angles)
{
	Vector3D forward = VectorSubtract(Destination, Source);
	float yaw, tmp, pitch;
	tmp = sqrt(forward.x*forward.x + forward.y*forward.y);
	yaw = (atan2(forward.y, forward.x) * 180 / M_PI);
	pitch = (atan2(-forward.z, tmp) * 180 / M_PI);

	Angles.x = pitch;
	Angles.y = yaw;
	Angles.z = 0;

}

/*
void CalcAngle(Vector3D src, Vector3D dst, Vector3D &angles)
{
	
	Vector3D delta = { (src.x - dst.x), (src.y - dst.y), (src.z - dst.z) };
	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);
	angles.x = (float)(asinf(delta.z / hyp) * 57.295779513082f);//asinf
	angles.y = (float)(atanf(delta.y / delta.x) * 57.295779513082f);
	angles.z = 0.0f;

	if (delta.x >= 0.0)
	{
		angles.y += 180.0f;
	}
	
}
*/

Vector3D AngleToDirection(Vector3D Angle)
{
	Angle.x = (Angle.x) * 3.14159265 / 180;
	Angle.y = (Angle.y) * 3.14159265 / 180;

	float sinYaw = sin(Angle.y);
	float cosYaw = cos(Angle.y);

	float sinPitch = sin(Angle.x);
	float cosPitch = cos(Angle.x);

	Vector3D Direction;
	Direction.x = cosPitch * cosYaw;
	Direction.y = cosPitch * sinYaw;
	Direction.z = -sinPitch;

	return Direction;
}
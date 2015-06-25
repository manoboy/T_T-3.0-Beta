#include "RayTrace.h"
#include "Entity.h"
CRayTrace* RayTrace = new CRayTrace;

CRayTrace::CRayTrace()
{

}


CRayTrace::~CRayTrace()
{
}

bool CRayTrace::Trace(Vector3D Direction, Vector3D LeftBottom, Vector3D RightTop)
{
	DirectionInverse.x = 1.0f / Direction.x;
	DirectionInverse.y = 1.0f / Direction.y;
	DirectionInverse.z = 1.0f / Direction.z;

	if (Direction.x == 0.0f && (LocalPlayer->EyePos.x < min(LeftBottom.x, RightTop.x) || LocalPlayer->EyePos.x > max(LeftBottom.x, RightTop.x)))
		return false;

	if (Direction.y == 0.0f && (LocalPlayer->EyePos.y < min(LeftBottom.y, RightTop.y) || LocalPlayer->EyePos.y > max(LeftBottom.y, RightTop.y)))
		return false;

	if (Direction.z == 0.0f && (LocalPlayer->EyePos.z < min(LeftBottom.z, RightTop.z) || LocalPlayer->EyePos.z > max(LeftBottom.z, RightTop.z)))
		return false;

	float t1 = (LeftBottom.x - LocalPlayer->EyePos.x) * DirectionInverse.x;
	float t2 = (RightTop.x - LocalPlayer->EyePos.x) * DirectionInverse.x;
	float t3 = (LeftBottom.y - LocalPlayer->EyePos.y) * DirectionInverse.y;
	float t4 = (RightTop.y - LocalPlayer->EyePos.y) * DirectionInverse.y;
	float t5 = (LeftBottom.z - LocalPlayer->EyePos.z) * DirectionInverse.z;
	float t6 = (RightTop.z - LocalPlayer->EyePos.z) * DirectionInverse.z;

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	if (tmax < 0) {
		return false;
	}

	if (tmin > tmax) {
		return false;
	}

	return true;

}

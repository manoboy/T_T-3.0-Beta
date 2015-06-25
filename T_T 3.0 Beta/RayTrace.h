#pragma once
#include "Math.h"
#include "Globals.h"

class CRayTrace
{
public:
	Vector3D Direction;
	Vector3D DirectionInverse;

	bool Trace(Vector3D Direction, Vector3D LeftBottom, Vector3D RightTop);

	CRayTrace();
	~CRayTrace();
};
extern CRayTrace* RayTrace;


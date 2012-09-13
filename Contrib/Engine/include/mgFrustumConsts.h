#ifndef _MGFRUSTUMCONSTS_H_
#define _MGFRUSTUMCONSTS_H_

#include "Render/RenderDevice.h"

static const float FIELD_OF_VIEW = 30.0f;
static const float Z_NEAR = 100.0f;
static const float Z_FAR = 10000.0f;
static const float Y_MAX = Z_NEAR * tanf(FIELD_OF_VIEW * 3.1415926f / 360);
static const float X_MAX = Y_MAX * 800.0f / 600.0f;//1.3335f;
//static const float TRANSLATE_Z = -300.0f * Z_NEAR / Y_MAX;

static const float TRANSLATE_Y = -10.0f;
static const float TRANSLATE_X_START = -230.0f;
static const float TRANSLATE_X_END = 12.0f;

inline void BeginFrustumMode()
{
	Render::device.SetCurrentMatrix(Render::PROJECTION);
	Render::device.PushMatrix();
	Render::device.SetViewFrustum(-X_MAX, X_MAX, -Y_MAX , Y_MAX , Z_NEAR, Z_FAR);
}

inline void EndFrustumMode()
{
	Render::device.SetCurrentMatrix(Render::PROJECTION);
	Render::device.PopMatrix();
}

#endif

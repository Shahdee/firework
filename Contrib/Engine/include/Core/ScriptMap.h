#include "types.h"
#include "Spline.h"
//////////////////////////////////////
typedef SplinePath<float> FSpline;
extern bool drawSplash;

// общесистемные биндинги к Lua
namespace LuaC
{
	void LoadResourceCallback(const string& filename);

	//void LoadParticlesCallback(const string& filename);

	void LoadEffectsCallback(const string& filename);
	void LoadEffectsGroupCallback(const string& filename, const std::string& group);
	void UnloadEffectsGroupCallback(const string& group);

	void CloseApplicationCallback();

	void StopApplicationCallback();

	void Spline_CalculateGradiendCallback(FSpline* spline, bool cycled);

	float FlerpCallback(float a, float b, float t);

	float FPeriodCallback(float t, float period);

	void ReleaseResourceGroupCallback(const string& group);

	void UploadResourceGroupCallback(const string& group);

	void ReleaseResourceCallback(const string& resId);

	void UploadResourceCallback(const string& resId);

	void LoadTextCallback(const string& file);
	void ClearTextsCallback();

	//string getGlobalStringCallBack(const string& id);

	void SetFullscreenModeCallback();

	void SetWindowedModeCallback();

	void SetCustomCursorCallback(bool mode);

	void ResetSplashCallback();
	
	void SetMaxFps(int fps);
	std::string GetLocalText(std::string& id);
}


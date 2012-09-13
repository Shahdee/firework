#ifndef _RENDERDEVICE_IPHONE_H_
#define _RENDERDEVICE_IPHONE_H_

#include <stack>
#include <vector>
#include <set>
#include "Assert.h"
#include "Utils/FPoint.h"
#include "Render/Texture.h"
//#import <QuartzCore/QuartzCore.h>

namespace Core
{
	class Window;
}

class VertexBuffer;
class TextureTextPrinter;

enum TextAlign
{
	LeftAlign,
	RightAlign,
	CenterAlign
};

enum DeviceMode
{
	DevFullscreen,
	DevWindowed
};

namespace Render
{
class Texture;
	
enum MatrixMode
{
	WORLD,
	MODELVIEW,
	PROJECTION,
	TEXTURE
};

enum BlendMode
{
	ALPHA,
	MULTIPLY,
	ADD
};

struct QuadVert
{
	QuadVert();
	QuadVert(float x_, float y_, float z_, DEVCOLOR color_, float u_, float v_);
	float x, y, z;
	DEVCOLOR color;
	float u, v;
};

class RenderDeviceImpl
{
	long memUsage;
	DeviceMode _currentDeviceMode;

	bool _windowBinded;

	void SetPresentParams(DeviceMode mode, int w=800, int h=600);

	MatrixMode _currentMatrix;
	DEVCOLOR _currentColor;
	DEVTEXTURE _currentTexture;

	/// Стек цвета. Все Draw... методы (кроме Direct... методов) пересчитывают цвет/альфу точек, относительно заданных ранее. То есть, если был задан цвет ARGB=0.5,0.3,1,1, то рисование точки с цветом 1,0.5,0.5,1 приведёт к реальному значению 0.5,0.15,0.5,1. При восстановлении из стека предыдущего значения, пересчёт прекращается. Смотри SetColor и ResetColor.
	std::stack<Color> _colorStack;
	/// стек чисел из интервала [0; 1]
	/// на вершине - <текущая альфа> / 255.0f.
	/// Стек используется функциями BeginAlphaMul и EndAlphaMul
	//std::stack<float> _alphaStack;

	/// текущая забинденая текстура
	Texture* bindedTexture;
	/// количество использованных каналов текстур, используется при выключении текстур
	int usedChannels;

	/// Правда ли, что устройство вывода поддерживает текстуры только со
	/// сторонами, являющимися степенями двойки.
	bool _isPower2Required;

	/// это размеры экрана в пикселях, используются при включении fullscreen
	int w_pix, h_pix; 
	/// текущие размеры окна
	int _current_width, _current_height;

	typedef std::set<Texture*> DynamicTexturesSet;
	/// список динамических текстур
	DynamicTexturesSet _dynamicTextures;

public:

	/// Рисовалка
	void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DEVCOLOR cv1, DEVCOLOR cv2, DEVCOLOR cv3, DEVCOLOR cv4, FRect uv=FRect(0.f, 1.f, 0.f, 1.f));
	/// Ещё рисовалка
	void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DEVCOLOR cv1, DEVCOLOR cv2, DEVCOLOR cv3, DEVCOLOR cv4, FPoint uv1, FPoint uv2, FPoint uv3, FPoint uv4);

	RenderDeviceImpl();
	~RenderDeviceImpl();
	
	void SetCamera(math::Vector3 lookFrom, math::Vector3 lookTo);

	/// context must be a EAGLContext, layer must be a CAEAGLLayer
	void BindWindowGL(void* context, void* layer);

	void Draw(VertexBuffer* vb);
	void DrawStrip(VertexBuffer* vb);
    void InitVertexBuffer(VertexBuffer* buffer, int numOfVertices);
	void Upload(VertexBuffer* buffer);

	void Upload(Texture* tex);
	void Reload(Texture *tex);
	void Bind(Texture* tex, int channel=0);
	void BindAlpha(Texture* tex);
	void Release(Texture* tex);
	void SetTexParams(Texture *tex);

	void SetViewFrustum(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetCurrentMatrix(MatrixMode mode);

	void ResetMatrix();
	void MatrixTranslate(math::Vector3 v);
	void MatrixTranslate(const math::Vector3* v);
	void MatrixRotate(math::Vector3 axis, float angle);
	void MatrixRotate(const math::Vector3* axis, float angle);
	void MatrixScale(float scale);
	void MatrixScale(float scaleX, float scaleY, float scaleZ);
	void PushMatrix();
	void PopMatrix();

	void GetDeviceMatrix();
	IPoint Project(math::Vector3 point);
	/// Включает или выключает текстурирование. При выключении обнуляются все использованные каналы текстур. При включении восстанавливается нулевой канал из последней текстуры.
	void SetTexturing(bool bEnable);
	void SetCulling(bool cullEnable);

	void SetBlendMode(BlendMode blendMode);
	void SetFog(bool isEnable);
	void SetBlend(bool isEnable);
	void SetLighting(bool isEnable);
	void SetAlpha(int alpha);
	void SetAlphaReference(int value);

	/// Прямое изменение текущего цвета.
	/// Рекомендуется использовать вместо этого метода метод SetColor.
	void SetCurrentColor(const Color& color = Color(0xff, 0xff, 0xff, 0xff));
	Color GetCurrentColor();

	void SetColor(DEVCOLOR col);
	DEVCOLOR GetColor();

	/// В этом методе _не_ пересчитывается альфа и цвет, так же _не_ пересчитываются координаты текстуры.
	/// Использовать не рекомендуется (но если очень хочется, то можно)
	void DirectDrawQuad(const QuadVert* quad);

	void Begin2DMode();
	void SetOrthoProjection(float width, float height);
	void Begin2DModeInViewport(int x, int y, int width, int height);
	void ResetViewport();
	void End2DMode();

	bool isLost();

	void BeginScene();
	void OutBlackScreen();
	void SetDepthTest(bool bEnable);
	void EndScene();

	void Release();
	void Reset();
	void Reset(DeviceMode mode);

	void WriteVendorInfo();

	unsigned int Width();
	unsigned int Height();
	/// Вызываются все _d3dDevice->SetRenderState,
	/// одинаковые для BindWindowGL, Reset() и Reset(mode)
	void SetDefaultRenderState();
	/// Правда ли, что устройство вывода поддерживает текстуры только со
	/// сторонами, являющимися степенями двойки.
	bool IsPower2Required();
	/// Сохранить текстуру в файл
	void StoreTextureToFile(Texture *tex, const std::string& file);
	/// Зарегистрировать динамическую текстуру. 
	/// Динамические текстуры уничтожаются при переинициализации RenderDeviceImpl. См. Texture::SetDynamic, Texture::Empty
	void RegisterDynamicTexture(Texture *tex);
	/// Отрегиестрировать динамическую текстуру.
	/// Динамические текстуры уничтожаются при переинициализации RenderDeviceImpl. См. Texture::SetDynamic, Texture::Empty
	void UnregisterDynamicTexture(Texture *tex);
	/// Возвращает использование видео памяти в Мб
	long GetVideoMemUsage();
	/// Пересчитывает UV координаты для текущей текстуры
	void TranslateUV(FRect& rect, FRect& uv);
};

extern RenderDeviceInterface& device;

}

#endif //_RENDERDEVICE_IPHONE_H_

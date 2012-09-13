#ifndef _RENDERDEVICE_GL_ES1_H_
#define _RENDERDEVICE_GL_ES1_H_

#include <stack>
#include <vector>
#include <set>
#include "Assert.h"
#include "Utils/FPoint.h"
#include "Render/Texture.h"
#include "ClippingMode.h"
#include "Render/RenderDeviceInterface.h"
#include "Render/VertexBuffer.h"
#include "Render/Target.h"
#include "SceneGraph/DeviceBuffer.h"
#include "SceneGraph/Material.h"
#include "SceneGraph/Light.h"

//#import <QuartzCore/QuartzCore.h>
#if defined(PROFILE_ES_CALLS)
#warning GL calls profile activated
#endif

#include "Render/ESProfiler.h"


namespace Core
{
	class Window;
}

class VertexBuffer;
class TextureTextPrinter;
 

namespace Render
{
class Texture;
class ShaderProgram;
class VolumeTexture;
class RenderDeviceGLES1
	: public RenderDeviceInterface
{
	long memUsage;
	DeviceMode _currentDeviceMode;

	bool _windowBinded;

	void SetPresentParams(DeviceMode mode, int w=800, int h=600);

	MatrixMode _currentMatrix;
	DEVCOLOR _currentColor;
	DEVTEXTURE _currentTexture;

	/// Стек цвета. Все Draw... методы (кроме Direct... методов) пересчитывают цвет/альфу точек, относительно заданных ранее. То есть, если был задан цвет ARGB=0.5,0.3,1,1, то рисование точки с цветом 1,0.5,0.5,1 приведёт к реальному значению 0.5,0.15,0.5,1. При восстановлении из стека предыдущего значения, пересчёт прекращается. Смотри SetColor и ResetColor.
	//std::stack<Color> _colorStack;
	/// стек чисел из интервала [0; 1]
	/// на вершине - <текущая альфа> / 255.0f.
	/// Стек используется функциями BeginAlphaMul и EndAlphaMul
	//std::stack<float> _alphaStack;

	/// текущая забинденая текстура
	Texture* bindedTexture;
	Target* bindedTarget;
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
	/// Количество текущих плоскостей отсечения
	int _nClipPlanes;
	std::stack<int> _clipPlanesStack;
    
    bool _isFogEnabled;
        // был ли включен ли туман 
    
	/// Проверка плоскости отсечения
	void CheckPlane(float plane[4], float x, float y, float z);
	
	QuadVert megaBuffer[6*40];
	int megaBufferIndex;
	void FlushBuffer();
	void PushToBuffer(QuadVert* quad);
	void SetStageOperation(int channel, unsigned int stageOperation);
	
	int MaxModelStack, MaxProjectionStack, MaxTextureStack, MaxTextureUnits;
	GLuint FBO;
	bool offscreenRendering;
	GLuint fogMode;
	GLfloat fogStart, fogEnd;
	Color fogColor;
public:

	virtual void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DEVCOLOR cv1, DEVCOLOR cv2, DEVCOLOR cv3, DEVCOLOR cv4, FRect uv=FRect(0.f, 1.f, 0.f, 1.f));
	virtual void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DEVCOLOR cv1, DEVCOLOR cv2, DEVCOLOR cv3, DEVCOLOR cv4, FPoint uv1, FPoint uv2, FPoint uv3, FPoint uv4);
	virtual void TrueDrawLine(const math::Vector3 &p1, const math::Vector3 &p2);
	RenderDeviceGLES1();
	~RenderDeviceGLES1();
	virtual void SetCamera(math::Vector3 lookFrom, math::Vector3 lookTo);
	virtual void BindWindowGL(void* layer);
	virtual void Draw(VertexBuffer* vb, int verticesCount = -1);
	virtual void DrawStrip(VertexBuffer* vb);
	virtual void DrawFan(VertexBuffer* vb);
	virtual void DrawIndexed(VertexBufferIndexed* buffer);
	virtual void InitVertexBuffer(VertexBuffer* buffer, int numOfVertices);
	virtual void InitIndexBuffer(VertexBufferIndexed* buffer, int numIndices);
	virtual void Upload(VertexBuffer* buffer, int verticesCount = -1);
	/// Рисует TRIANGLE_LIST
	virtual void DrawPrimitives(QuadVert *buf, int verticesCount);
	virtual void Lock(Texture *tex, DWORD *&frame);
	virtual void Unlock(Texture *tex);
	virtual void UploadIndexBuffer(VertexBufferIndexed* buffer);
	virtual void Release(VertexBuffer* buffer);
	virtual void ReleaseIndexBuffer(VertexBufferIndexed* buffer);
	virtual void Upload(Texture* tex);
	virtual void UploadRegion(Texture* tex, int x, int y, int width, int height, const char* data);
	virtual void Reload(Texture *tex);
	virtual void Bind(Texture* tex, int channel=0, unsigned int stageOperation = STAGE_DEFAULT);
	virtual void BindAlpha(Texture* tex);
	virtual void Release(Texture* tex);
	virtual void SetTexParams(Texture *tex);
	virtual Target* CreateRenderTarget(int width, int height, bool alpha = true);
	virtual void DeleteRenderTarget(Target*& tar);
	virtual void Bind(Target* tar, int channel=0, unsigned int stageOperation = STAGE_DEFAULT);
	virtual void BindAlpha(Target* tar);
	virtual void Release(Target* tar);
	virtual void BeginRenderTo(Target* tar, const Color color = Color::BLACK_TRANSPARENT);
	virtual void EndRenderTo();
	virtual void Upload(VolumeTexture* const texture);
	virtual void Bind(VolumeTexture* const texture, int channel = 0, unsigned int stageOperation = STAGE_DEFAULT);
	virtual void Release(VolumeTexture*);
	virtual SceneGraph::DeviceBuffer::HardPtr CreateVertexBuffer(DWORD /* FVF */, std::size_t /* stride */, std::size_t /* count */)
	{
		// заглушка
		assert(false);
		return SceneGraph::DeviceBuffer::HardPtr();
	}
	
	virtual SceneGraph::DeviceBuffer::HardPtr CreateIndexBuffer(IndexFormat /* indexFormat */, std::size_t /* count */) {
		// заглушка
		assert(false);
		return SceneGraph::DeviceBuffer::HardPtr();
	}
	
	virtual void DrawIndexedPrimitive(PrimitiveType /* type */, SceneGraph::DeviceBuffer::HardPtr /* vertices */, SceneGraph::DeviceBuffer::HardPtr /* indices */) {
		// заглушка
		assert(false);
	}
	
	virtual void SetMaterial(SceneGraph::Material::HardPtr /* material */) {
		// заглушка
		assert(false);
	}
	
	virtual void SetWorldMatrices(const std::vector<math::Matrix4>& /* matrices */) {
		// заглушка
		assert(false);
	}
	
	virtual void EnableIndexedVertexBlend(bool /* enable */) {
		// заглушка
		assert(false);
	}
	
	virtual void SetViewFrustum(float left, float right, float bottom, float top, float zNear, float zFar);
	virtual void SetCurrentMatrix(MatrixMode mode);
	virtual void ResetMatrix();
	virtual void MatrixTransform(const math::Matrix4& matrix);
	virtual void MatrixTranslate(const math::Vector3& v);
	virtual void MatrixRotate(const math::Vector3& axis, float angle);
	virtual void MatrixScale(float scale);
	virtual void MatrixScale(float scaleX, float scaleY, float scaleZ);
	virtual void PushMatrix();
	virtual void PopMatrix();

	virtual void GetDeviceMatrix();
	virtual IPoint Project(math::Vector3 point);
	virtual void SetTexturing(bool bEnable);
	virtual void SetCulling(bool cullEnable);
	virtual void SetBlendMode(BlendMode blendMode);
	virtual void SetFog(bool isEnable);
	virtual void SetFogSettings(float fogStart, float fogEnd, float density, FogMode fogMode, FogRenderState fogRenderState, Color color);
	virtual void SetBlend(bool isEnable);
	virtual void SetLighting(bool isEnable);
	virtual void SetAlpha(int alpha);
	virtual void SetAlphaReference(int value);
	virtual void SetCurrentColor(const Color& color = Color(0xff, 0xff, 0xff, 0xff));
	virtual Color GetCurrentColor();
	virtual void SetColor(DEVCOLOR col);
	virtual DEVCOLOR GetColor();
	virtual void DirectDrawQuad(const QuadVert* quad);
	virtual void DirectDrawQuad(const QuadVertT2* quad);
	virtual void DirectDrawQuad(const QuadVertT3* quad);
	virtual void Begin2DMode();
	virtual void SetOrthoProjection(float width, float height);
	virtual void Begin2DModeInViewport(int x, int y, int width, int height);
	virtual void ResetViewport();
	virtual void End2DMode();
	virtual bool isLost();
	virtual void BeginScene();
	virtual void OutBlackScreen();
	virtual void SetDepthTest(bool bEnable);
	virtual void EndScene();
	virtual void Release();
	virtual void Reset();
	virtual void Reset(DeviceMode mode, int, int);
	virtual void WriteVendorInfo();
	virtual int Width();
	virtual int Height();
	virtual void SetDefaultRenderState();
	virtual bool IsPower2Required();
	virtual void StoreTextureToFile(Texture *tex, const std::string& file);
	virtual void RegisterDynamicTexture(Texture *tex);
	virtual void UnregisterDynamicTexture(Texture *tex);
	virtual long GetVideoMemUsage();
	virtual void TranslateUV(FRect& rect, FRect& uv);
	virtual Texture* GetBindedTexture();
	virtual void BeginClipping(IRect window, ClippingMode clippingMode);
	virtual void EndClipping();
	virtual void CreateGLContext();
	virtual void DestroyGLContext();
	virtual void ClearBindedObject();
	virtual void UnbindAll();
	virtual bool CanUseGPUSkinning(int bonesCount);
	virtual math::Matrix4 GetViewProjectionMatrix();
	virtual void BeginPickPass() {assert(false);}
	virtual int EndPickPass(const IPoint &/*mouse_pos*/) {assert(false); return 0;}
	virtual bool IsPickPass() {assert(false); return false;}
	virtual void SetColorForMesh() {assert(false);}
	virtual ShaderProgram *GetBindedShader() {assert(false); return NULL;}
	virtual void AddLight(SceneGraph::Light::HardPtr /*light*/) {assert(false);}
	virtual bool GetLighting() {assert(false); return false;};
	virtual void DrawTriangle(FPoint p1, FPoint p2, FPoint p3);
	virtual BlendMode GetBlendMode() const;
	virtual void GLFinish() const ;
    virtual bool GetFog();
};

extern RenderDeviceInterface& device;


}

#endif //_RENDERDEVICE_GL_ES1_H_

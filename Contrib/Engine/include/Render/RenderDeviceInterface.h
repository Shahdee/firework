#pragma once
#include "SceneGraph.h"
#include "ClippingMode.h"
#include "Render/Target.h"
#include "Render/RenderTypes.h"

namespace Core
{
	class Window;
	class Application;
}

class VertexBuffer;
class VertexBufferIndexed;

namespace Render {

class Texture;
class Target;
class VolumeTexture;
class ShaderProgram;

//
// ����� ��� ���� �������� ��������� �������������
// ��� ���������� ������ ������ ���� 2 ��������:
//  1) �������� ��� ����� ��� ����� ����������� (= 0);
//  2) �������� ��� ����� � ���������� ����������� ������ � RenderDeviceInterface.cpp
//     (� ������������ �������������� assert(false)).
//
class RenderDeviceInterface {

public:

	// ����������� �� ���������
	RenderDeviceInterface();

	/// ������ viewport
	/// ���������� ����������, ������ ���������� ��������
	/// (dx only)
	virtual void SetViewport(int x, int y, int width, int height);

	/// (dx only)
	virtual IRect GetViewport();

	/// ������� ����� �� ��� ������� ������, � �.�. � �� ������ �� �����
	/// (dx only)
	virtual void SetFullscreenViewport();

	/// ���������� ������������� ������� �������������
	/// ������ � ������ ����������, �.�. ������������ �������� ������������
	virtual void SetOrthoProjection(float logicalWidth, float logicalHeight, float minZ, float maxZ);

	/// ���������
	virtual void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DEVCOLOR cv1, DEVCOLOR cv2, DEVCOLOR cv3, DEVCOLOR cv4, FRect uv=FRect(0.f, 1.f, 0.f, 1.f)) = 0;
	
	/// ����� ���������� ���������
	virtual void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DEVCOLOR cv1, DEVCOLOR cv2, DEVCOLOR cv3, DEVCOLOR cv4, FPoint uv1, FPoint uv2, FPoint uv3, FPoint uv4) = 0;

	/// ��������� �����
	virtual void TrueDrawLine(const math::Vector3& p1, const math::Vector3& p2) = 0;

	virtual ~RenderDeviceInterface();
	
	/// (dx only)
	virtual void SetGlobalCompress(bool allow);

	/// (dx only)
	virtual void SetCamera(math::Vector3 lookFrom, math::Vector3 lookTo) = 0;

	/// (dx only)
	virtual void BindWindowDX(Core::Window* wnd, int contextWidth, int contextHeight);

	/// layer must be a CAEAGLLayer
	/// (gl only)
	virtual void BindWindowGL(void* layer);

	/// (dx only)
	virtual void AddLight(SceneGraph::Light::HardPtr light) = 0;

	virtual void Draw(VertexBuffer* vb, int verticesCount = -1) = 0;

	virtual void DrawIndexed(VertexBufferIndexed *vb) = 0;

	virtual void DrawStrip(VertexBuffer* vb) = 0;

	virtual void DrawFan(VertexBuffer* vb) = 0;

	/// (dx only)
	virtual void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3,
					  float u1, float v1, float u2, float v2, float u3, float v3);

	/// (dx only)
	virtual void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3,
					  float u1, float v1, float u2, float v2, float u3, float v3,
					  float u21, float v21, float u22, float v22, float u23, float v23);

	/// (dx only)
	virtual void DrawTriangleWithColor(float x1, float y1, float x2, float y2, float x3, float y3,
							   float u1, float v1, float u2, float v2, float u3, float v3, 
							   DWORD c1, DWORD c2, DWORD c3);

	/// (gl only)
	virtual void DrawTriangle(FPoint p1, FPoint p2, FPoint p3);
	
	/// ���� � gl-������ ������ �� ������, ��� ��� �������������
	/// VBO ��� ������ �� ���� �������� �������
    virtual void InitVertexBuffer(VertexBuffer* buffer, int numOfVertices) = 0;

	/// ���� � gl-������ ������ �� ������, ��� ��� �������������
	/// VBO ��� ������ �� ���� �������� �������
	virtual void InitIndexBuffer(VertexBufferIndexed *buffer, int numOfIndices) = 0;

	virtual void Upload(VertexBuffer* buffer, int verticesCount = -1) = 0;

	virtual void UploadIndexBuffer(VertexBufferIndexed *buffer) = 0;

	virtual void Release(VertexBuffer* buffer) = 0;

	virtual void ReleaseIndexBuffer(VertexBufferIndexed *buffer) = 0;

	virtual void Upload(Texture* tex) = 0;
	
	virtual void UploadRegion(Texture* tex, int x, int y, int width, int height, const char* data);

	virtual void Reload(Texture *tex) = 0;

	/// (dx only)
	/// ToDo: ���� ������ �� �����, �������
	virtual void Lock(Texture *tex, DWORD *&frame) = 0;

	/// (dx only)
	/// ToDo: ���� ������ �� �����, �������
	virtual void Unlock(Texture *tex) = 0;

	virtual void Bind(Texture* tex, int channel=0, unsigned int stageOperation = STAGE_DEFAULT) = 0;

	virtual void Bind(Target* rt, int channel=0, unsigned int stageOperation = STAGE_DEFAULT) = 0;

	virtual void BindAlpha(Texture* tex) = 0;

	virtual void BindAlpha(Target* rt) = 0;

	virtual void Release(Texture* tex) = 0;

	// (dx only)
	virtual void Upload(VolumeTexture* tex) = 0;

	// (dx only)
	virtual void Release(VolumeTexture* tex) = 0;

	// (dx only)
	virtual void Bind(VolumeTexture* tex, int channel=0, unsigned int stageOperation = STAGE_DEFAULT) = 0;

	// (dx only)
	virtual void Upload(ShaderProgram* shader);

	// (dx only)
	virtual void Bind(ShaderProgram* shader);

	// (dx only)
	virtual void Release(ShaderProgram* shader);

	// (dx only)
	virtual ShaderProgram *GetBindedShader() = 0;

	// (dx only)
	virtual void SetPSParam(int baseReg, const float* fv, int size);

	// (dx only)
	virtual void SetVSParam(int baseReg, const float* fv, int size);
	
	// ������ ��� GPU Skinning
	// (������-�� ����� ���������� false!)
	// (dx only)
	virtual bool CanUseGPUSkinning(int bonesCount) = 0;
	
	virtual void SetViewFrustum(float left, float right, float bottom, float top, float zNear, float zFar) = 0;

	virtual void SetCurrentMatrix(MatrixMode mode) = 0;

	// (dx only)
	virtual MatrixMode GetCurrentMatrix();

	virtual void ResetMatrix() = 0;

	/// (dx only)
	virtual void MatrixMultiply(const math::Matrix4& matrix);

	virtual void MatrixTransform(const math::Matrix4& matrix) = 0;

	virtual void MatrixTranslate(const math::Vector3& v) = 0;

	virtual void MatrixRotate(const math::Vector3& axis, float angle) = 0;

	virtual void MatrixScale(float scale) = 0;

	virtual void MatrixScale(float scaleX, float scaleY, float scaleZ) = 0;

	/// (dx only)
	virtual void SetWorldMatrices(const std::vector<math::Matrix4>& matrices) = 0;

	virtual void PushMatrix() = 0;

	virtual void PopMatrix() = 0;

	/// ��������� ������� ��� �������� ������� ����� ������
	/// (dx only)
	virtual int GetStackSize(MatrixMode matrix);

	/// (dx only)
	virtual void GetDeviceMatrix() = 0;

	virtual math::Matrix4 GetModelMatrix();

	virtual math::Matrix4 GetViewProjectionMatrix() = 0;

	/// (dx only)
	virtual math::Matrix4 GetModelViewProjectionMatrix();

	virtual IPoint Project(math::Vector3 point) = 0;

	/// �������� ��� ��������� ���������������. ��� ���������� ���������� ��� �������������� ������ �������. ��� ��������� ����������������� ������� ����� �� ��������� ��������.
	virtual void SetTexturing(bool bEnable) = 0;

	virtual void SetCulling(bool cullEnable) = 0;

	virtual void SetBlendMode(BlendMode blendMode) = 0;

	virtual BlendMode GetBlendMode() const = 0;

	virtual void SetFog(bool isEnable) = 0;

	virtual bool GetFog();

	virtual void SetBlend(bool isEnable) = 0;

	/// (dx only)
	virtual void SetLighting(bool isEnable) = 0;

	/// (dx only)
	virtual bool GetLighting() = 0;

	/// ������-��, ����� �� ������������
	virtual void SetAlpha(int alpha) = 0;

	/// (dx only)
	/// �� iPad ����� ������������� ����� �������
	virtual void SetAlphaReference(int value) = 0;

	/// (dx only)
	/// �� iPad ����� ������������� ����� �������
	virtual int GetAlphaReference();

	/// ������ ��������� �������� �����.
	/// ������������� ������������ ������ ����� ������ ����� Render::BeginColor.
	virtual void SetCurrentColor(const Color& color = Color(0xff, 0xff, 0xff, 0xff)) = 0;

	virtual Color GetCurrentColor() = 0;

	/// ������ ��������� �������� �����.
	/// ������������� ������������ ������ ����� ������ ����� Render::BeginColor.
	virtual void SetColor(DEVCOLOR col) = 0;

	virtual DEVCOLOR GetColor() = 0;

	/// ������������ �� ������������� (�� ���� ����� �������, �� �����)
	virtual void DirectDrawQuad(const QuadVert* quad) = 0;

	virtual void DirectDrawQuad(const QuadVertT2* quad) = 0;

	virtual void DirectDrawQuad(const QuadVertT3* quad) = 0;
	
	/// ������ TRIANGLE_LIST
	virtual void DrawPrimitives(QuadVert *buf, int verticesCount) = 0;

	virtual void Begin2DMode() = 0;

	virtual void Begin2DModeInViewport(int x, int y, int width, int height) = 0;

	virtual void ResetViewport() = 0;

	virtual void End2DMode() = 0;

	virtual bool isLost() = 0;

	// ��������! ��� ��������������� ������� ������� ����� ������.
	virtual void BeginScene() = 0;

	/// (dx only)
	/// �������������� ������������ ������� �����
	virtual void OutBlackScreen() = 0;

	virtual void SetDepthTest(bool bEnable) = 0;

	/// (dx only)
	virtual void ClearDepthBuffer();

	// ��������! ��� ��������������� ������� ������� ����� ������.
	virtual void EndScene() = 0;

	/// (dx only)
	virtual void Present();

	virtual void Release() = 0;

	/// � GL 2 ��������� ��������� ������������
	virtual void Reset(DeviceMode mode, int contextWidth, int contextHeight) = 0;

	/// ���������� ��� _d3dDevice->SetRenderState,
	/// ���������� ��� BindWindow, Reset
	virtual void SetDefaultRenderState() = 0;

	/// ������ ��, ��� ���������� ������ ������������ �������� ������ ��
	/// ���������, ����������� ��������� ������.
	/// (� gl ������ ���������� true)
	virtual bool IsPower2Required() = 0;

	/// ��������� �������� � ����
	/// (dx only)
	virtual void StoreTextureToFile(Texture *tex, const std::string& file) = 0;

	/// ���������������� ������������ ��������. 
	/// ������������ �������� ������������ ��� ����������������� RenderDeviceImpl. ��. Texture::SetDynamic, Texture::Empty
	virtual void RegisterDynamicTexture(Texture *tex) = 0;

	/// ���������������� ������������ ��������.
	/// ������������ �������� ������������ ��� ����������������� RenderDeviceImpl. ��. Texture::SetDynamic, Texture::Empty
	virtual void UnregisterDynamicTexture(Texture *tex) = 0;

	/// ���������� ������������� ����� ������ � ��
	virtual long GetVideoMemUsage() = 0;

	/// ������������� UV ���������� ��� ������� ��������
	virtual void TranslateUV(FRect& rect, FRect& uv) = 0;

	/// (dx only)
	virtual void TranslateUV(FRect& uv);

	/// (dx only)
	virtual void TranslateUV(FPoint& uv1, FPoint& uv2);

	virtual void WriteVendorInfo() = 0;

	/// true ���� �������� ����������� ��� �������������� ������ �� "�������" ������
	/// (dx only)
	virtual bool LetterBoxScreen();

	/// true ���� �������� ����������� ��� �������������� ������ �� ������� ������
	/// (dx only)
	virtual bool PillarBoxScreen();

	/// ������� � ��������� ����������� �� ������ (����������)
	/// (dx only)
	virtual FRect ScreenPos();

	/// ������� � ��������� ����������� �� ������ (����������)
	/// (dx only)
	virtual FRect ScreenPosPhysical();

	virtual int Width() = 0;

	virtual int Height() = 0;

	/// (dx only)
	virtual int PhysicalWidth();

	/// (dx only)
	virtual int PhysicalHeight();

	/// �������� ����������� ������� ��� �������������� ������, ����������� �� ���������� ������
	/// (dx only)
	virtual IRect GetBestFSModeSizes(int origWidth, int origHeight);

	/// ���������� ��������� �� ������� ��������
	virtual Texture* GetBindedTexture() = 0;

	//
	// ������ ����� ��������� ������������� ����� window
	// ���������� ���� � ������� ������� ���������,
	// ������� ����� ���� ���������� � ��������.
	// ����� ���������� ����������� �������� ������ ������ ��� Z
	//
	// ����� ��������� �������, �������� �� �� ������ �� ������ ������.
	// �� ��������� - ���������� ��. �� ���������� ���������� ���������
	// ����� ����� ���������, ��������� �� ����� ���� ����� 6, �.�.
	// ���� ��� �������������� ������ �������������.
	//
	virtual void BeginClipping(IRect window, ClippingMode clippingMode = ClippingMode::ALL) = 0;

	//
	// ���������� �������, ��������� ��������� BeginClipping
	//
	virtual void EndClipping() = 0;

	//
	// ������� ���� ���������� � ������� ���������.
	// ���, ��� ������ ������ � ������� CreateRenderTarget _������_ 
	// ������� DeleteRenderTarget, ��� ������ �������� ���������� �� �����.
	// ��� ������ �� ���� ���������� ������� � ������ �������� �����������
	// �� ���������� � ����. ������� ����� ������� � ������������ ��������,
	// � ���� ������ Render::device ��� �����.
	// �������� alpha �������� ��� ��������� �����-����� � ����
	// ���� �� ��������� ������������ ����� �������������� � �� �����������, �� alpha ����� �������� ��� false
	// 
	virtual Target* CreateRenderTarget(int width, int height, bool alpha = true) = 0;

	//
	// ������� ������������ � ���������� ������
	//
	virtual void DeleteRenderTarget(Target*& renderTarget) = 0;

	//
	// ������ ��������� � ������-������
	// ��� ���� ������ ��������� ����� � ����� ������ ���� ����������� ��������.
	// ���� ���� ����� (0, 0, 0, 0), �� ���� ����������.
	// ���� ����� ������������ ���, �� ����� ����������� � ������ �������������
	// ��� �������� ������� �������.
	// ��������! ��� ��������������� ������� ������� ����� ������.
	//
	virtual void BeginRenderTo(Target* render, const Color color = Color::RED) = 0;

	//
	// ��������� ��������� � ������-������
	// ��������! ��� ��������������� ������� ������� ����� ������.
	//
	virtual void EndRenderTo() = 0;

	// ������ � ��������� ��������� ������ ������ ��������
	// � ����� ������ ���������� ������� � ����������� ��������� �����, ����� � 
	// ���������� ������, ����� ������ ������ ����� ��� ������
	// EndPickPass ���������� id �����, ������� ��� ��� ��������
	// ��-���������, ����� ��������� ����� ������, ������� ���� ��� �������� �� ���������
	// �������, �� ������� EndPickPass ����� �������� 0x00FFFFFF
	// (dx only)
	virtual void BeginPickPass() = 0;

	// (dx only)
	virtual int EndPickPass(const IPoint &mouse_pos) = 0;

	// (dx only)
	virtual bool IsPickPass() = 0;

	// (dx only)
	virtual Target* GetPickTarget() const;
	
	// (dx only)
	virtual void SetColorForMesh() = 0;	// ������������� ������� ���� ��� ������� ����, ���� � ���� �����������
							// �������� �����

	// ���������� ��������� ������
	// (dx only)
	virtual void SetFogSettings(float fogStart, float fogEnd, float density, FogMode fogMode, FogRenderState fogRenderState, Color color);

	/// ������ ����� ������
	// (dx only)
	virtual SceneGraph::DeviceBuffer::HardPtr CreateVertexBuffer(DWORD FVF, std::size_t stride, std::size_t count) = 0;
	
	/// ������ ����� ��������
	// (dx only)
	virtual SceneGraph::DeviceBuffer::HardPtr CreateIndexBuffer(IndexFormat indexFormat, std::size_t count) = 0;
	
	/// ������ ��������� � ������� ������ ������
	// (dx only)
	virtual void DrawPrimitive(PrimitiveType type, SceneGraph::DeviceBuffer::HardPtr vertices);
	
	/// ������ ��������� � ������� ������ ������ � ������ ��������
	// (dx only)
	virtual void DrawIndexedPrimitive(PrimitiveType type, SceneGraph::DeviceBuffer::HardPtr vertices, SceneGraph::DeviceBuffer::HardPtr indices) = 0;
	
	/// ������������� ������� �������� ��� �������������� � ����������
	// (dx only)
	virtual void SetMaterial(SceneGraph::Material::HardPtr material) = 0;
	
	/// ������������� ��� ������� ��������������� ���������� �������������� ������
	// (dx only)
	virtual void EnableIndexedVertexBlend(bool enable) = 0;

	// (dx only)
	virtual bool CopyTexture(Render::Target* from, Render::Texture* to);

	//
	// ������������� �������� � ������������ Application ��� ��� �����������.
	// ���������� _���������������_ ��� �������������������.
	// ��� �� ��������, ��� ����� �������������� ������ ��;
	// ���� �� �� �������������� �����������, �������� ��������� �������.
	//
	// ������������������� ����� ����� �������������� �������������.
	// ��� ���� (� directx) ������������ ������ ������� �� �������� ���������.
	//
	// (dx only)
	virtual void SetPreferredMultiSampleType(MultisampleType type);

	// 
	// ��������/��������� ������������ �������������.
	// ������ ������ �� ������������� �����, ��� ��������� ������� �������� ������������������.
	// ����� ����� �������� � ������������ Application (���  ������������ ������),
	// ��������� �������� ����������� ������ ��� ������ _d3dDevice->Reset().
	//
	// (dx only)
	virtual void SetVSyncState(bool enable);

	// ����������� ��������� ������������ ���� ��������
	// (dx only)
	virtual bool IsVertexShaderSupported(int majorVersion, int minorVersion);

	// (dx only)
	virtual bool IsPixelShaderSupported(int majorVersion, int minorVersion);

	/// ������� �������� OpenGL
	/// ������ ���������� � ������ ������� ������ (� �������� ����)
	/// ����� _�����������_ ����� �������� ������ ����� DestroyContext 
	/// (��� directx �� ������ ������)
	virtual void CreateGLContext() = 0;
	
	//
	// ������� �������� OpenGL
	// ����� �������� ����� CreateGLContext � ����� ������� ������
	// (��� directx �� ������ ������)
	//
	virtual void DestroyGLContext() = 0;
	
	/// (gl only)
	virtual void Release(Target* tar);
	
	/// (gl only)
	virtual void ClearBindedObject();
	
	// ��������� ��� ������� OpenGL (��������� ��� iOS, ���
	// ������������ ���������� ���������� ������)
	virtual void GLFinish() const;
	
/* ������������� ������ */
	
	// ���������� �� ������ � ������
	bool IsRenderingToTarget() const;

private:

	bool _isRenderingToTarget;
		// �������� �� � ���� (��������� ����� BeginRenderTo � EndRenderTo)

	bool _isRenderingToScreen;
		// �������� �� �� ����� (��������� ����� BeginScene � EndScene)

};

extern RenderDeviceInterface& device;
	
} // namespace Render

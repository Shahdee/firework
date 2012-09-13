#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <stack>
#include <vector>
#include <set>
#include "Assert.h"
#include "Utils/FPoint.h"
#include "Render/RenderDeviceInterface.h"
#include "Render/Texture.h"
#include "Render/VolumeTexture.h"
#include "Render/Target.h"
#include "ClippingMode.h"
#include "SceneGraph.h"

#include "getdxver.h"

#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

namespace Core
{
	class Window;
	class Application;
}

class VertexBuffer;
class VertexBufferIndexed;
class TextureTextPrinter;

namespace Render
{

class ShaderProgram;
class ShaderProgramDX9;

class RenderDeviceImpl
	: public RenderDeviceInterface
{
	LPDIRECT3D9 _d3d;
	LPDIRECT3DDEVICE9 _d3dDevice;
	D3DPRESENT_PARAMETERS _presentParam;

	// Поддерживается ли хардварная обработка вершин
	bool _hardwareVertexProcessing;

	// объявление формата вершин (взамен FVF-кодов)
	LPDIRECT3DVERTEXDECLARATION9 _vertexDeclaration;

	typedef std::vector<D3DDISPLAYMODE> SupportedDisplayModes;
	SupportedDisplayModes _fsModes;

	D3DDISPLAYMODE _currentDisplayMode;
	DeviceMode _currentDeviceMode;

	Core::Window *_bindedWnd;
	int _physWidth, _physHeight;

	/// использовать сжатие текстур в данный формат
	D3DFORMAT _textureConvert;
	/// разрешить сжатие всех текстур
	bool _allowGlobalCompress;
	/// кол-во свободной видеопамяти в момент запуска
	UINT memUsage;
	/// буфер для простого рендеринга
	IDirect3DVertexBuffer9* _tempBuffer;

	std::vector<D3DXMATRIX> _viewMatrixStack;
	std::vector<D3DXMATRIX> _textureMatrixStack;
	std::vector<D3DXMATRIX> _texture1MatrixStack;
	std::vector<D3DXMATRIX> _texture2MatrixStack;
	std::vector<D3DXMATRIX> _texture3MatrixStack;
	std::vector<D3DXMATRIX> _texture4MatrixStack;
	std::vector<D3DXMATRIX> _texture5MatrixStack;
	std::vector<D3DXMATRIX> _texture6MatrixStack;
	std::vector<D3DXMATRIX> _texture7MatrixStack;
	std::vector<D3DXMATRIX> _projectMatrixStack;
	std::vector<D3DXMATRIX>* _currentMatrixStack;

	D3DXMATRIX _projectMatrix;
	D3DXMATRIX _viewMatrix;
	D3DXMATRIX _worldMatrix;
	D3DVIEWPORT9 _viewport;

	MatrixMode _currentMatrix;
	DWORD _currentColor;
	LPDIRECT3DBASETEXTURE9 _currentTexture;

	/// текущая забинденая текстура
	Texture* bindedTexture;
	/// количество использованных каналов текстур, используется при выключении текстур
	int usedChannels;
	/// текущая забинденая 3d текстура
	VolumeTexture* bindedVolumeTexture;
	/// установленный вершинный шейдер
	ShaderProgramDX9* _shaderInUse;

	/// Правда ли, что устройство вывода поддерживает текстуры только со
	/// сторонами, являющимися степенями двойки.
	bool _isPower2Required;

	/// Максимально допустимое количество источников света
	unsigned int MaxActiveLights;
	unsigned int ActiveLights;

	typedef std::set<Texture*> DynamicTexturesSet;
	/// список динамических текстур
	DynamicTexturesSet _dynamicTextures;

	int _nClipPlanes;
		// текущее количество плоскостей отсечения (см. BeginClipping)

	static const int MAX_CLIP_PLANES = 6;
		// максимальное количество плоскостей отсечения (см. BeginClipping)

	std::stack<int> _clipPlanesStack;
		// Стек количества плоскостей отсечения - нужен, поскольку в
		// BeginClipping количество добавленных плоскостей может быть разным,
		// а EndClipping должен обеспечить реентерабельность.

	typedef std::list<Target*> Targets;
	Targets _targets;
		// список текстур-целей рендера

	Target *_pickBuffer;
		// Буфер выбора объектов
	bool _pickPass;
		// Проход рендера в буфер выбора объектов
	
	typedef std::set<ShaderProgramDX9*> Shaders;
	Shaders _shaders;
		// список шейдеров

	bool _isRenderingToTarget;
		// рендерим ли в цель (находимся между BeginRenderTo и EndRenderTo)

	bool _isRenderingToScreen;
		// рендерим ли на экран (находимся между BeginScene и EndScene)

	LPDIRECT3DSURFACE9 _depthsurf;
		// Z буфер (сохраняется тут, чтобы восстанавливать в EndRenderTo)

	Target* _bindedRenderTarget;
		// забенденный рендер-таргет

	MultisampleType _preferredMultiSampleType;
		// предпочитаемый тип мультисэмплирования

	UINT _presentInterval;
		// значение для _presentParam.FullScreen_PresentationInterval, управляет вертикальной синхронизацией

	BlendMode _currentBlendMode;
		// текущий режим блендинга

	int _currentAlphaRef;
		// текущее значение нижнего порога альфы, при котором пикселы еще выводятся
	int _savedAlphaRef;
		// для временного хранения _currentAlphaRef

	void SetPresentParams(DeviceMode mode);

	void LoadFullscreenModes();
	D3DDISPLAYMODE GetBestFSMode(int width, int height);

	//
	// Очистить Рендер-таргеты, предварительно инвалидировав их
	//
	void ClearRenderTargets();

	//
	// Пометить забинденный объект как незабинденный
	//
	void ClearBindedObject();

	//
	// Вернуть ближайший к предпочтительному тип мультисемплирования,
	// который поддерживается видеокартой.
	//
	D3DMULTISAMPLE_TYPE GetDeviceMultiSampleType(DeviceMode mode);

	void SetStageOperation(int channel, unsigned int stageOperation);
	// Отбиндить все текстуры. Полезно вызывать после мультитекстурирования.
	void UnbindAll();

public:
	/// установить ортогональную матрицу проецирования
	/// ширина и высота логические, т.е. определяются игровыми координатами
	void SetOrthoProjection(float logicalWidth, float logicalHeight, float minZ, float maxZ);

	/// задать viewport
	/// координаты логические, внутри произойдет пересчет
	void SetViewport(int x, int y, int width, int height);
	IRect GetViewport();

	/// сделать вывод на всю область экрана, в т.ч. и на полосы по бокам
	void SetFullscreenViewport();
	/// Рисовалка
	void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DWORD cv1, DWORD cv2, DWORD cv3, DWORD cv4, FRect uv=FRect(0.f, 1.f, 0.f, 1.f));
	/// Самая брутальная рисовалка
	void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DWORD cv1, DWORD cv2, DWORD cv3, DWORD cv4, FPoint uv1, FPoint uv2, FPoint uv3, FPoint uv4);
	/// Рисование линии
	void TrueDrawLine(const math::Vector3& p1, const math::Vector3& p2);

	RenderDeviceImpl();
	~RenderDeviceImpl();
	
	void SetGlobalCompress(bool allow);
	void SetCamera(math::Vector3 lookFrom, math::Vector3 lookTo);

	void BindWindowDX(Core::Window* wnd, int contextWidth, int contextHeight);

	void AddLight(SceneGraph::Light::HardPtr light);
	void Draw(VertexBuffer* vb, int verticesCount = -1);
	void DrawIndexed(VertexBufferIndexed *vb);
	void DrawStrip(VertexBuffer* vb);
	void DrawFan(VertexBuffer* vb);
	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3,
					  float u1, float v1, float u2, float v2, float u3, float v3);

	void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3,
					  float u1, float v1, float u2, float v2, float u3, float v3,
					  float u21, float v21, float u22, float v22, float u23, float v23);

	void DrawTriangleWithColor(float x1, float y1, float x2, float y2, float x3, float y3,
							   float u1, float v1, float u2, float v2, float u3, float v3, 
							   DWORD c1, DWORD c2, DWORD c3);
    void InitVertexBuffer(VertexBuffer* buffer, int numOfVertices);
	void InitIndexBuffer(VertexBufferIndexed *buffer, int numOfIndices);
	void Upload(VertexBuffer* buffer, int verticesCount = -1);
	void UploadIndexBuffer(VertexBufferIndexed *buffer);
	void Release(VertexBuffer* buffer);
	void ReleaseIndexBuffer(VertexBufferIndexed *buffer);
	/// Рисует TRIANGLE_LIST
	virtual void DrawPrimitives(QuadVert *buf, int verticesCount);

	void Upload(Texture* tex);
	void Reload(Texture *tex);
	void Lock(Texture *tex, DWORD *&frame);
	void Unlock(Texture *tex);
	void Bind(Texture* tex, int channel=0, unsigned int stageOperation = STAGE_DEFAULT);
	void Bind(Target* rt, int channel=0, unsigned int stageOperation = STAGE_DEFAULT);
	void BindAlpha(Texture* tex);
	void BindAlpha(Target* rt);
	virtual void Release(Texture* tex);
	void Upload(VolumeTexture* tex);
	void Release(VolumeTexture* tex);
	void Bind(VolumeTexture* tex, int channel=0, unsigned int stageOperation = STAGE_DEFAULT);
	
	void Upload(ShaderProgram* shader);
	void Bind(ShaderProgram* shader);
	void Release(ShaderProgram* shader);
	ShaderProgram *GetBindedShader();
	
	void SetPSParam(int baseReg, const float* fv, int size);
	void SetVSParam(int baseReg, const float* fv, int size);

	// методы для GPU Skinning
	bool CanUseGPUSkinning(int bonesCount);
	
	void SetViewFrustum(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetCurrentMatrix(MatrixMode mode);
	MatrixMode GetCurrentMatrix();

	void ResetMatrix();
	void MatrixMultiply(const math::Matrix4& matrix);
	void MatrixTransform(const math::Matrix4& matrix);
	void MatrixTranslate(const math::Vector3& v);
	void MatrixRotate(const math::Vector3& axis, float angle);
	void MatrixScale(float scale);
	void MatrixScale(float scaleX, float scaleY, float scaleZ);
	void SetWorldMatrices(const std::vector<math::Matrix4>& matrices);
	void PushMatrix();
	void PopMatrix();
	/// Служебная функция для проверки глубины стека матриц
	int GetStackSize(MatrixMode matrix);

	void GetDeviceMatrix();
	math::Matrix4 GetModelMatrix();
	math::Matrix4 GetViewProjectionMatrix();
	math::Matrix4 GetModelViewProjectionMatrix();
	IPoint Project(math::Vector3 point);

	/// Включает или выключает текстурирование. При выключении обнуляются все использованные каналы текстур. При включении восстанавливается нулевой канал из последней текстуры.
	virtual void SetTexturing(bool bEnable);
	void SetCulling(bool cullEnable);

	void SetBlendMode(BlendMode blendMode);
	BlendMode GetBlendMode() const;

	void SetAlphaBlendMode(AlphaBlendMode blendMode);

	void SetFog(bool isEnable);
	bool GetFog();
	void SetFogSettings(float fogStart, float fogEnd, float density, FogMode fogMode, FogRenderState fogRenderState, Color color);
	void SetBlend(bool isEnable);
	void SetLighting(bool isEnable);
	bool GetLighting();
	void SetAlpha(int alpha);
	void SetAlphaReference(int value);
	int GetAlphaReference();

	/// Прямое изменение текущего цвета.
	/// Рекомендуется использовать вместо этого метода метод Render::SetColor.
	void SetCurrentColor(const Color& color = Color(0xff, 0xff, 0xff, 0xff));
	Color GetCurrentColor();

	/// Прямое изменение текущего цвета.
	/// Рекомендуется использовать вместо этого метода метод Render::SetColor.
	void SetColor(DEVCOLOR col);
	DEVCOLOR GetColor();

	/// Использовать не рекомендуется (но если очень хочется, то можно)
	void DirectDrawQuad(const QuadVert* quad);
	void DirectDrawQuad(const QuadVertT2* quad);
	void DirectDrawQuad(const QuadVertT3* quad);

	void Begin2DMode();
	void Begin2DModeInViewport(int x, int y, int width, int height);
	void ResetViewport();
	void End2DMode();

	bool isLost();

	void BeginScene();
	void OutBlackScreen();
	void SetDepthTest(bool bEnable);
	void ClearDepthBuffer();
	void EndScene();

	void Present();

	void Release();
	void Reset(DeviceMode mode, int contextWidth, int contextHeight);

	/// Вызываются все _d3dDevice->SetRenderState,
	/// одинаковые для BindWindow, Reset
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
	void TranslateUV(FRect& uv);
	void TranslateUV(FPoint& uv1, FPoint& uv2);

	void WriteVendorInfo();

	/// true если включена компенсация для полноэкранного режима на "высоком" экране
	bool LetterBoxScreen();
	/// true если включена компенсация для полноэкранного режима на широком экране
	bool PillarBoxScreen();
	/// размеры и положение изображения на экране (логические)
	FRect ScreenPos();
	/// размеры и положение изображения на экране (физические)
	FRect ScreenPosPhysical();

	int Width();
	int Height();
	int PhysicalWidth();
	int PhysicalHeight();

	/// получить оптимальные размеры для полноэкранного режима, основываясь на переданных данных
	IRect GetBestFSModeSizes(int origWidth, int origHeight);

	/// Возвращает указатель на текущую текстуру
	Texture* GetBindedTexture();

	//
	// Начать режим отсечения прямоугольным окном window
	// Координаты окна в текущей системе координат,
	// которая может быть перемещена и повёрнута.
	// Перед отсечением разрешается вращение ТОЛЬКО вокруг оси Z
	//
	// Режим отсечения говорит, отсекать ли по каждой из четырёх сторон.
	// По умолчанию - отсекается всё. На количестве плоскостей отсечения
	// имеет смысл экономить, поскольку их может быть всего 6, т.е.
	// даже два прямоугольника отсечь проблематично.
	//
	void BeginClipping(IRect window, ClippingMode clippingMode = ClippingMode::ALL);

	//
	// Завершение участка, открытого последним BeginClipping
	//
	void EndClipping();

	//
	// Создать цель рендеринга с нужными размерами.
	// Тот, кто создаёт таргет с помощью CreateRenderTarget _обязан_ 
	// вызвать DeleteRenderTarget, как только текстура становится не нужна.
	// При выходе из игры количество висящих в памяти объектов проверяется
	// на равернство с нулём. Таргеты можно удалять в деструкторах виджетов,
	// в этот момент Render::device еще живой.
	// Параметр alpha включает или отключает альфа-канал у цели
	// Если не требуется использовать альфу отрендеренного в неё изображения, то alpha стоит передать как false
	// 
	Target* CreateRenderTarget(int width, int height, bool alpha = true);

	//
	// Удалить рендертаргет и освободить память
	//
	void DeleteRenderTarget(Target*& renderTarget);

	//
	// Начать рендерить в рендер-таргет
	// При этом начало координат будет в левом нижнем углу получающеся текстуры.
	// Цвет фона будет (0, 0, 0, 0), то есть прозрачный.
	// Если нужен непрозрачный фон, то можно отрендерить в таргет прямоугольник
	// без текстуры обычным образом.
	//
	void BeginRenderTo(Target* render, const Color color = Color::RED);

	//
	// Завершить рендерить в рендер-таргет
	//
	void EndRenderTo();

	// Происходит ли рендер в таргет
	inline bool IsRenderingToTarget() const { return _isRenderingToTarget; }

	//
	// Изменить пикселы рендер-таргета в указанном прямоугольнике.
	// region -- изменяемая область,
	// cmp_op_rgba -- операции для сравнения компонент цвета с эталонными значениями (в порядке RGBA),
	// cmp_ref_value -- эталонные значения компонент цвета,
	// value -- новые значения компонент цвета,
	// value_mask -- маски для каждой компоненты, определяют, какие биты надо менять
	bool UpdateRenderTargetContents(Target* target, const IRect& region,
									const CompareOp cmp_op_rgba[], const Color& cmp_ref_value, 
									const Color& value, const Color& value_mask);

	// Начать и закончить отрисовку буфера выбора объектов
	// В буфер должны рисоваться объекты с определённым значением цвета, чтобы в 
	// дальнейшем узнать, какой именно объект попал под курсор
	// EndPickPass возвращает id цвета, который был под курсором
	// По-умолчанию, буфер очищается белым цветом, поэтому если под курсором не оказалось
	// объекта, то функция EndPickPass вернёт значение 0x00FFFFFF
	void BeginPickPass();
	int EndPickPass(const IPoint &mouse_pos);
	bool IsPickPass();
	Target* GetPickTarget() const { return _pickBuffer; }
	//bool _savePickBuffer;
	
	void SetColorForMesh();	// Устанавливает текущий цвет для рендера меша, если у него отсутствует
							// цветовой канал

	/// Создаёт буфер вершин
	SceneGraph::DeviceBuffer::HardPtr CreateVertexBuffer(DWORD FVF, std::size_t stride, std::size_t count);
	
	/// Создаёт буфер индексов
	SceneGraph::DeviceBuffer::HardPtr CreateIndexBuffer(IndexFormat indexFormat, std::size_t count);
	
	/// Рисует примитивы с помощью буфера вершин
	void DrawPrimitive(PrimitiveType type, SceneGraph::DeviceBuffer::HardPtr vertices);
	
	/// Рисует примитивы с помощью буфера вершин и буфера индексов
	void DrawIndexedPrimitive(PrimitiveType type, SceneGraph::DeviceBuffer::HardPtr vertices, SceneGraph::DeviceBuffer::HardPtr indices);
	
	/// Устанавливает текущий материал для взаимодействия с освещением
	void SetMaterial(SceneGraph::Material::HardPtr material);
	
	/// Устанавливает или снимает индексированное смешивание преобразований вершин
	void EnableIndexedVertexBlend(bool enable);

	bool CopyTexture(Render::Target* from, Render::Texture* to);

	//
	// Рекомендуется вызывать в конструкторе Application или его наследников.
	// Установить _предпочтитаемый_ тип мультисэмплирования.
	// Это не означает, что будет использоваться именно он;
	// если он не поддерживается видеокартой, возьмётся ближайший меньший.
	//
	// Мультисэмплирование задаёт режим полноэкранного антиалиасинга.
	// при этом (в directx) сглаживаются только пиксели на границах полигонов.
	//
	void SetPreferredMultiSampleType(MultisampleType type);

	// 
	// Включить/выключить вертикальную синхронизацию.
	// Влияет только на полноэкранный режим, при включении немного страдает производительность.
	// Имеет смысл вызывать в конструкторе Application (или  производного класса),
	// поскольку параметр применяется только при вызове _d3dDevice->Reset().
	//
	void SetVSyncState(bool enable);

	// Получить из обычного цвета (a, r, g, b) цвет в формате premultiplied alpha (a, ar, ag, ab);
	// помещены в этот класс поскольку работают с внутренним представлением цвета
	static DEVCOLOR PremultiplyAlpha(const Color& color);
	static DEVCOLOR PremultiplyAlpha(const DEVCOLOR& color);

	// Определение поддержки определённого вида шейдеров
	bool IsVertexShaderSupported(int manorVersion, int minorVersion);
	bool IsPixelShaderSupported(int manorVersion, int minorVersion);

	void SetSeparateBlendMode(bool enable);

	// Пустые реализации CreateGLContext и DestroyContext
	virtual void CreateGLContext() {}
	virtual void DestroyGLContext() {}
};

extern RenderDeviceInterface& device;

} // namespace Render

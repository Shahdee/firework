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
// Общий для всех платформ интерфейс рендердевайса
// При добавлении нового метода есть 2 варианта:
//  1) объявить его здесь как чисто виртуальный (= 0);
//  2) объявить его здесь и определить тривиальную версию в RenderDeviceInterface.cpp
//     (с обязательным использованием assert(false)).
//
class RenderDeviceInterface {

public:

	// Конструктор по умолчанию
	RenderDeviceInterface();

	/// Задать viewport
	/// Координаты логические, внутри произойдет пересчет
	/// (dx only)
	virtual void SetViewport(int x, int y, int width, int height);

	/// (dx only)
	virtual IRect GetViewport();

	/// сделать вывод на всю область экрана, в т.ч. и на полосы по бокам
	/// (dx only)
	virtual void SetFullscreenViewport();

	/// установить ортогональную матрицу проецирования
	/// ширина и высота логические, т.е. определяются игровыми координатами
	virtual void SetOrthoProjection(float logicalWidth, float logicalHeight, float minZ, float maxZ);

	/// Рисовалка
	virtual void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DEVCOLOR cv1, DEVCOLOR cv2, DEVCOLOR cv3, DEVCOLOR cv4, FRect uv=FRect(0.f, 1.f, 0.f, 1.f)) = 0;
	
	/// Самая брутальная рисовалка
	virtual void TrueDraw(const math::Vector3& v1, const math::Vector3& v2, const math::Vector3& v3, const math::Vector3& v4, DEVCOLOR cv1, DEVCOLOR cv2, DEVCOLOR cv3, DEVCOLOR cv4, FPoint uv1, FPoint uv2, FPoint uv3, FPoint uv4) = 0;

	/// Рисование линии
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
	
	/// Пока в gl-версии ничего не делает, так как использование
	/// VBO под айфоно не дало никакого профита
    virtual void InitVertexBuffer(VertexBuffer* buffer, int numOfVertices) = 0;

	/// Пока в gl-версии ничего не делает, так как использование
	/// VBO под айфоно не дало никакого профита
	virtual void InitIndexBuffer(VertexBufferIndexed *buffer, int numOfIndices) = 0;

	virtual void Upload(VertexBuffer* buffer, int verticesCount = -1) = 0;

	virtual void UploadIndexBuffer(VertexBufferIndexed *buffer) = 0;

	virtual void Release(VertexBuffer* buffer) = 0;

	virtual void ReleaseIndexBuffer(VertexBufferIndexed *buffer) = 0;

	virtual void Upload(Texture* tex) = 0;
	
	virtual void UploadRegion(Texture* tex, int x, int y, int width, int height, const char* data);

	virtual void Reload(Texture *tex) = 0;

	/// (dx only)
	/// ToDo: если никому не нужен, удалить
	virtual void Lock(Texture *tex, DWORD *&frame) = 0;

	/// (dx only)
	/// ToDo: если никому не нужен, удалить
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
	
	// методы для GPU Skinning
	// (почему-то везде возвращает false!)
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

	/// Служебная функция для проверки глубины стека матриц
	/// (dx only)
	virtual int GetStackSize(MatrixMode matrix);

	/// (dx only)
	virtual void GetDeviceMatrix() = 0;

	virtual math::Matrix4 GetModelMatrix();

	virtual math::Matrix4 GetViewProjectionMatrix() = 0;

	/// (dx only)
	virtual math::Matrix4 GetModelViewProjectionMatrix();

	virtual IPoint Project(math::Vector3 point) = 0;

	/// Включает или выключает текстурирование. При выключении обнуляются все использованные каналы текстур. При включении восстанавливается нулевой канал из последней текстуры.
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

	/// Вообще-то, лучше не использовать
	virtual void SetAlpha(int alpha) = 0;

	/// (dx only)
	/// на iPad нужно реализовывать через шейдеры
	virtual void SetAlphaReference(int value) = 0;

	/// (dx only)
	/// на iPad нужно реализовывать через шейдеры
	virtual int GetAlphaReference();

	/// Прямое изменение текущего цвета.
	/// Рекомендуется использовать вместо этого метода метод Render::BeginColor.
	virtual void SetCurrentColor(const Color& color = Color(0xff, 0xff, 0xff, 0xff)) = 0;

	virtual Color GetCurrentColor() = 0;

	/// Прямое изменение текущего цвета.
	/// Рекомендуется использовать вместо этого метода метод Render::BeginColor.
	virtual void SetColor(DEVCOLOR col) = 0;

	virtual DEVCOLOR GetColor() = 0;

	/// Использовать не рекомендуется (но если очень хочется, то можно)
	virtual void DirectDrawQuad(const QuadVert* quad) = 0;

	virtual void DirectDrawQuad(const QuadVertT2* quad) = 0;

	virtual void DirectDrawQuad(const QuadVertT3* quad) = 0;
	
	/// Рисует TRIANGLE_LIST
	virtual void DrawPrimitives(QuadVert *buf, int verticesCount) = 0;

	virtual void Begin2DMode() = 0;

	virtual void Begin2DModeInViewport(int x, int y, int width, int height) = 0;

	virtual void ResetViewport() = 0;

	virtual void End2DMode() = 0;

	virtual bool isLost() = 0;

	// Внимание! При переопределении следует вызвать метод предка.
	virtual void BeginScene() = 0;

	/// (dx only)
	/// широкоэкранное закрашивание боковых полос
	virtual void OutBlackScreen() = 0;

	virtual void SetDepthTest(bool bEnable) = 0;

	/// (dx only)
	virtual void ClearDepthBuffer();

	// Внимание! При переопределении следует вызвать метод предка.
	virtual void EndScene() = 0;

	/// (dx only)
	virtual void Present();

	virtual void Release() = 0;

	/// В GL 2 последних параметра игнорируются
	virtual void Reset(DeviceMode mode, int contextWidth, int contextHeight) = 0;

	/// Вызываются все _d3dDevice->SetRenderState,
	/// одинаковые для BindWindow, Reset
	virtual void SetDefaultRenderState() = 0;

	/// Правда ли, что устройство вывода поддерживает текстуры только со
	/// сторонами, являющимися степенями двойки.
	/// (в gl всегда возвращает true)
	virtual bool IsPower2Required() = 0;

	/// Сохранить текстуру в файл
	/// (dx only)
	virtual void StoreTextureToFile(Texture *tex, const std::string& file) = 0;

	/// Зарегистрировать динамическую текстуру. 
	/// Динамические текстуры уничтожаются при переинициализации RenderDeviceImpl. См. Texture::SetDynamic, Texture::Empty
	virtual void RegisterDynamicTexture(Texture *tex) = 0;

	/// Отрегистрировать динамическую текстуру.
	/// Динамические текстуры уничтожаются при переинициализации RenderDeviceImpl. См. Texture::SetDynamic, Texture::Empty
	virtual void UnregisterDynamicTexture(Texture *tex) = 0;

	/// Возвращает использование видео памяти в Мб
	virtual long GetVideoMemUsage() = 0;

	/// Пересчитывает UV координаты для текущей текстуры
	virtual void TranslateUV(FRect& rect, FRect& uv) = 0;

	/// (dx only)
	virtual void TranslateUV(FRect& uv);

	/// (dx only)
	virtual void TranslateUV(FPoint& uv1, FPoint& uv2);

	virtual void WriteVendorInfo() = 0;

	/// true если включена компенсация для полноэкранного режима на "высоком" экране
	/// (dx only)
	virtual bool LetterBoxScreen();

	/// true если включена компенсация для полноэкранного режима на широком экране
	/// (dx only)
	virtual bool PillarBoxScreen();

	/// размеры и положение изображения на экране (логические)
	/// (dx only)
	virtual FRect ScreenPos();

	/// размеры и положение изображения на экране (физические)
	/// (dx only)
	virtual FRect ScreenPosPhysical();

	virtual int Width() = 0;

	virtual int Height() = 0;

	/// (dx only)
	virtual int PhysicalWidth();

	/// (dx only)
	virtual int PhysicalHeight();

	/// получить оптимальные размеры для полноэкранного режима, основываясь на переданных данных
	/// (dx only)
	virtual IRect GetBestFSModeSizes(int origWidth, int origHeight);

	/// Возвращает указатель на текущую текстуру
	virtual Texture* GetBindedTexture() = 0;

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
	virtual void BeginClipping(IRect window, ClippingMode clippingMode = ClippingMode::ALL) = 0;

	//
	// Завершение участка, открытого последним BeginClipping
	//
	virtual void EndClipping() = 0;

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
	virtual Target* CreateRenderTarget(int width, int height, bool alpha = true) = 0;

	//
	// Удалить рендертаргет и освободить память
	//
	virtual void DeleteRenderTarget(Target*& renderTarget) = 0;

	//
	// Начать рендерить в рендер-таргет
	// При этом начало координат будет в левом нижнем углу получающеся текстуры.
	// Цвет фона будет (0, 0, 0, 0), то есть прозрачный.
	// Если нужен непрозрачный фон, то можно отрендерить в таргет прямоугольник
	// без текстуры обычным образом.
	// Внимание! При переопределении следует вызвать метод предка.
	//
	virtual void BeginRenderTo(Target* render, const Color color = Color::RED) = 0;

	//
	// Завершить рендерить в рендер-таргет
	// Внимание! При переопределении следует вызвать метод предка.
	//
	virtual void EndRenderTo() = 0;

	// Начать и закончить отрисовку буфера выбора объектов
	// В буфер должны рисоваться объекты с определённым значением цвета, чтобы в 
	// дальнейшем узнать, какой именно объект попал под курсор
	// EndPickPass возвращает id цвета, который был под курсором
	// По-умолчанию, буфер очищается белым цветом, поэтому если под курсором не оказалось
	// объекта, то функция EndPickPass вернёт значение 0x00FFFFFF
	// (dx only)
	virtual void BeginPickPass() = 0;

	// (dx only)
	virtual int EndPickPass(const IPoint &mouse_pos) = 0;

	// (dx only)
	virtual bool IsPickPass() = 0;

	// (dx only)
	virtual Target* GetPickTarget() const;
	
	// (dx only)
	virtual void SetColorForMesh() = 0;	// Устанавливает текущий цвет для рендера меша, если у него отсутствует
							// цветовой канал

	// Установить параметры тумана
	// (dx only)
	virtual void SetFogSettings(float fogStart, float fogEnd, float density, FogMode fogMode, FogRenderState fogRenderState, Color color);

	/// Создаёт буфер вершин
	// (dx only)
	virtual SceneGraph::DeviceBuffer::HardPtr CreateVertexBuffer(DWORD FVF, std::size_t stride, std::size_t count) = 0;
	
	/// Создаёт буфер индексов
	// (dx only)
	virtual SceneGraph::DeviceBuffer::HardPtr CreateIndexBuffer(IndexFormat indexFormat, std::size_t count) = 0;
	
	/// Рисует примитивы с помощью буфера вершин
	// (dx only)
	virtual void DrawPrimitive(PrimitiveType type, SceneGraph::DeviceBuffer::HardPtr vertices);
	
	/// Рисует примитивы с помощью буфера вершин и буфера индексов
	// (dx only)
	virtual void DrawIndexedPrimitive(PrimitiveType type, SceneGraph::DeviceBuffer::HardPtr vertices, SceneGraph::DeviceBuffer::HardPtr indices) = 0;
	
	/// Устанавливает текущий материал для взаимодействия с освещением
	// (dx only)
	virtual void SetMaterial(SceneGraph::Material::HardPtr material) = 0;
	
	/// Устанавливает или снимает индексированное смешивание преобразований вершин
	// (dx only)
	virtual void EnableIndexedVertexBlend(bool enable) = 0;

	// (dx only)
	virtual bool CopyTexture(Render::Target* from, Render::Texture* to);

	//
	// Рекомендуется вызывать в конструкторе Application или его наследников.
	// Установить _предпочтитаемый_ тип мультисэмплирования.
	// Это не означает, что будет использоваться именно он;
	// если он не поддерживается видеокартой, возьмётся ближайший меньший.
	//
	// Мультисэмплирование задаёт режим полноэкранного антиалиасинга.
	// при этом (в directx) сглаживаются только пиксели на границах полигонов.
	//
	// (dx only)
	virtual void SetPreferredMultiSampleType(MultisampleType type);

	// 
	// Включить/выключить вертикальную синхронизацию.
	// Влияет только на полноэкранный режим, при включении немного страдает производительность.
	// Имеет смысл вызывать в конструкторе Application (или  производного класса),
	// поскольку параметр применяется только при вызове _d3dDevice->Reset().
	//
	// (dx only)
	virtual void SetVSyncState(bool enable);

	// Определение поддержки определённого вида шейдеров
	// (dx only)
	virtual bool IsVertexShaderSupported(int majorVersion, int minorVersion);

	// (dx only)
	virtual bool IsPixelShaderSupported(int majorVersion, int minorVersion);

	/// Создать контекст OpenGL
	/// Должна вызываться в начале каждого потока (и главного тоже)
	/// Также _обязательно_ нужно вызывать парный метод DestroyContext 
	/// (под directx не делает ничего)
	virtual void CreateGLContext() = 0;
	
	//
	// Удалить контекст OpenGL
	// Нужно вызывать парно CreateGLContext в конце каждого потока
	// (под directx не делает ничего)
	//
	virtual void DestroyGLContext() = 0;
	
	/// (gl only)
	virtual void Release(Target* tar);
	
	/// (gl only)
	virtual void ClearBindedObject();
	
	// Завершить все команды OpenGL (актуально для iOS, где
	// используется отложенное выполнение команд)
	virtual void GLFinish() const;
	
/* НЕВИРТУАЛЬНЫЕ МЕТОДЫ */
	
	// Происходит ли рендер в таргет
	bool IsRenderingToTarget() const;

private:

	bool _isRenderingToTarget;
		// рендерим ли в цель (находимся между BeginRenderTo и EndRenderTo)

	bool _isRenderingToScreen;
		// рендерим ли на экран (находимся между BeginScene и EndScene)

};

extern RenderDeviceInterface& device;
	
} // namespace Render

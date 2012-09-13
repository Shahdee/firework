#pragma once

#if defined(ENGINE_TARGET_WIN32_DX9)
#include "d3d9.h"
#elif defined(ENGINE_TARGET_WIN32_DX8)
#include "d3d8.h"
#endif
#include "Render/Texture.h"

namespace Render {

	enum CompareOp
	{
		CMP_EQ,
		CMP_NE,
		CMP_LT,
		CMP_LE,
		CMP_GT,
		CMP_GE,
		CMP_FALSE,
		CMP_TRUE
	};
//
// Объект, ведущий себя подобно текстуре,
// в который можно что-то рисовать.
//
// В public вынесены только те методы, которые будут полезны пользователю
// Все остальное, в том числе и конструктор, в private.
// Таким образом, создавать объекты и иметь полный доступ к ним может только
// экземпляр класса Render::RenderDeviceImpl.
//
// Особенности:
// 1) тот кто создал объект методом Render::RenderDeviceImpl::CreateRenderTarget,
//    обязан также удалить его методом Render::RenderDeviceImpl::DeleteRenderTarget;
// 2) при всех операциях в Render::Target нужно проверять, валиден ли он
//    функцией IsValid(); Таргет станет невалидным после изменения разрешения;
// 3) рендерить в текстуру можно только в Update, но не в Draw.
//
// Код, создающий RenderTarget должен выглядеть примерно так:
// 
// RenderTarget* _renderTarget;
// ...
// if (_renderTarget != NULL && !_renderTarget->IsValid()) {
//    Render::device.DeleteRenderTarget(_renderTarget);
//	  _renderTarget = NULL;
// }
// if (_renderTarget == NULL) {
//    _renderTarget = Render::device.CreateRenderTarget(_texture->getBitmapRect().width, _texture->getBitmapRect().height);
//    Render::device.BeginRenderTo(_renderTarget);
//    ... // Здесь рисуем что-нибудь
//    Render::device.EndRenderTo();
// }
//
// То есть мы _обязаны_ удалить объект после того, как он нам не нужен.
// Обратите внимание, что этот код должен быть в Update, но не в Draw.
//
class Target
{

public:

	bool needTranslate() const;
	
	void TranslateUV(FPoint& uv) const;
	
	void TranslateUV(FRect& rect, FRect& uv) const;
	
	IRect getRenderRect() const { return IRect(0, 0, _widthPow2, _heightPow2); }
	
	IRect getBitmapRect() const { return IRect(0, 0, _width, _height); }

	//
	// Установка текущей текстурой
	//
	void Bind(int cannel = 0, int stageOp = 0);

	//
	// Установка текущей текстурой для альфа-рисования
	//
	void BindAlpha();

	//
	// Рисование текстуры
	//
	void Draw(const FPoint& position);

	//
	// Валиден ли Таргет
	//
	bool IsValid();

	/// Пустой ли Таргет.
	/// Пустой таргет есть валидный таргет, но его содержимое было утеряно в результате сброса устройства
	bool Empty();

	//
	// Сохранить в формате BMP
	// Особенность: переворачивает текстуру по вертикали
	//
	void SaveAsBmp(const std::string & path);

	//
	// Сохранить в формате PNG
	// Особенность: переворачивает текстуру по вертикали
	//
	void SaveAsPng(const std::string & path);
	
	//
	// Сохранить в формате JPEG
	//
	void SaveAsJpeg(const std::string & path, int quality = 80);

	//
	// Деструктор
	//
	virtual ~Target();

	//
	// Проверка валидности объекта и пересоздание по необходимости (в этом случае возвращает false)
	// Полезно выполнять перед каждой операцией над объектом (см. п.2 в комментариях выше)
	// 
	static bool EnsureValidity(Target** t);

	//
	// Изменить пикселы рендер-таргета в указанном прямоугольнике.
	// region -- изменяемая область,
	// cmp_op_rgba -- операции для сравнения компонент цвета с эталонными значениями (в порядке RGBA),
	// cmp_ref_value -- эталонные значения компонент цвета,
	// value -- новые значения компонент цвета,
	// value_mask -- маски для каждой компоненты, определяют, какие биты надо менять
	//
	bool UpdateContents(const IRect& region, 
								const CompareOp cmp_op_rgba[], const Color& cmp_ref_value,
								const Color& value, const Color& value_mask);

	//
	// Установка фильтрации таргета
	//
	void setFilter(Texture::FilteringType filter);

	//
	// Установка адресации текстурных координат таргета
	//
	void setAdress(Texture::AdressType adress);

private:

	friend class RenderDeviceImpl;
	friend class RenderDeviceGLES1;
	friend class RenderDeviceGLES2;
		// чтобы только там можно было создавать объекты такого типа

	DEVTEXTURE _texture;	
		// текстура

#if defined(ENGINE_TARGET_WIN32_DX9)
	IDirect3DSurface9* _renderTargetSurface;
		// поверхность
	
	IDirect3DSurface9* _depthStencilSuface;
		// Z-буфер
#elif defined(ENGINE_TARGET_WIN32_DX8)
	IDirect3DSurface8* _renderTargetSurface;
		// поверхность
	
	IDirect3DSurface8* _depthStencilSuface;
		// Z-буфер
#endif
	
	bool _valid;
		// валидна ли цель рендеринга (становится невалидной, если устройство переинициализировалось)
	/// Пуста ли цель рендеринга
	bool _empty;

	bool _isBinded;
		// забиндена ли цель рендеринга

	int _width;
		// ширина текстуры

	int _height;
		// высота текстуры
	
	int _widthPow2;
		// ширина текстуры, округлённая до ближайшей большей степени двойки
	
	int _heightPow2;
		// высота текстуры, округлённая до ближайшей большей степени двойки

	int texWidth, texHeight; // размер памяти, выделенный под текстуру для таргета

	bool _alpha;
		// нужен ли альфа-канал цели?

	Texture::FilteringType _filter;
		// Тип фильтрации

	Texture::AdressType _adress;
		// Тип адресации текстурных координат

	//
	// Конструктор скрыт для всех кроме RenderDeviceImpl
	//
	Target(int width, int height);

	//
	// Очистить ресурсы, которыми владеет объект
	//
	void ReleaseResources();

	//
	// Зачищает все ресурсы и делает цель невалидной.
	//
	void SetInvalid();
	
#if defined(ENGINE_TARGET_WIN32_DX8) || defined(ENGINE_TARGET_WIN32_DX9)
	//
	// Сохраняет содержимое в Image::image_pool
	//
	bool CopyToImagePool();
#endif
};

} // namespace Render

#pragma once
#include "Render.h"
#include "Utils/random.hpp"
#include "Assert.h"
#include "Text.h"

/// Класс, отвечающий за плавную смену текстур.
/// При смене текстуры уровень альфа-канала старых текстур
/// постепенно уменьшается, новой текстуры - увеличивается.
class SmoothTextureChanger
{
private:

	struct Image
	{
		Image();
		~Image();
		Render::Texture* tex;
		Text *richText;
		IPoint textPos;
		string text;
		string font;
		float textScale;
		Color textColor;
		bool withText;
	};

	float alphaFactor;

	/// скорость изменения; 1.0f - изменение за 1 секунду
	float _speed;

	/// текущая (возможно, уходящая) текстура
	Image _currentImage;

	/// доля текущей текстуры (0; 1]
	float _currentImageShare;

	/// очередь следующих текстур
	/// первая в очереди плавно заменяет _currentImage,
	/// остальные ожидают своей очереди
	std::list<Image> _nextImages;

	/// прямой итератор по _nextTextures
	typedef std::list<Image>::iterator Iterator;

public:

	void setAlphaFactor(float a);

	Render::Texture* getCurrentTexture();

	/// Вывод на экран
	void Draw(const IPoint& pos = IPoint(0, 0));

	/// Прошло dt секунд
	void Update(float dt);

	/// Добавление новой текстуры в очередь
	void SetTexture(Render::Texture *newTexture);

	/// Добавление новой текстуры в очередь
	void SetTextureWithText(Render::Texture *newTexture, const std::string& text, const std::string& font,
		const IPoint& pos, float scale = 1.f, Color color = Color::WHITE);

	/// Добавление новой текстуры в очередь
	void SetTextureWithText(Render::Texture *newTexture, Text* text, const IPoint& pos);
	
	/// Заменить текстуру сразу, без плавного перехода
	void QuickReplaceTextureBy(Render::Texture *texture);

	/// Установить новую скорость смены текстур
	void SetSpeed(float value);

	/// Есть ли еще текстуры в очереди
	bool HasQueuedImages() const;

	/// Создание объекта с одной текстурой
	SmoothTextureChanger(Render::Texture *startTexture);
	SmoothTextureChanger(Render::Texture *startTexture, float speed);
	SmoothTextureChanger(Render::Texture *startTexture, const std::string& text, const std::string& font,
		const IPoint& pos, float scale = 1.f, Color color = Color::WHITE);
	SmoothTextureChanger(Render::Texture *startTexture, Text* text, const IPoint& pos);

	typedef boost::shared_ptr<SmoothTextureChanger> HardPtr;
};

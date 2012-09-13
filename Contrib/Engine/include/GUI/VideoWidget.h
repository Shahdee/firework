#pragma once

#include "GUI/Widget.h"
#include "Render/Texture.h"
#include "Render/Sprite.h"
#include "MM/MMPlayer.h"

namespace GUI {

	/// Видео из ogg/theora.

	/// Для создания экземпляра через Layer используется код подобный следующему:
	/// \code
	/// <VideoWidget name="video1" loop="false" frameDrop="true">
	/// 	<rectangle x="150" y="200" width="200" height="200"/>
	/// 	<file path="movies\clip1.ogg"/>
	/// </VideoWidget>
	/// \endcode
	/// Где rectangle - координаты прямоугольника, file - файл.
	/// После инициализации видео стоит на паузе. Запускать - message "Continue"
	/// Пауза - message "Pause"
	/// Запустить с начала - message "Play"
	/// Так же можно задавать позицию и размер через message "SetPosition" "x;y;width;height"

	class VideoWidget : public GUI::Widget
	{

	public:
		VideoWidget(const string& name_);
		VideoWidget(const string& name_, Xml::TiXmlElement* xmlElement);
		virtual ~VideoWidget();
		virtual void Draw();
		virtual void Update(float dt);
		virtual void AcceptMessage(const Message& message);

	private:
		MM::MMPlayer* player;
		Render::Sprite sprite;
		std::string file;
	};
}
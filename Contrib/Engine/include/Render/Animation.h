//****************************************************************************************
//	Класс Animation
//
//	Реализует спрайтовую анимацию. Карта анимации должна располагаться в 
//	файле BMP,GIF (не анимированный),TGA,JPG или PNG. Кадры в файле должны размещаться
//	начиная от левого верхнего угла текстуры (кадр 0) и далее слева направо построчно.
//	
//	Объекты описываются в xml-файле с помощью элемента <Animation id="Gobot" texture="#GobotTex">:
//	АТРИБУТЫ :
//	id			- идентификатор объекта;
//	texture		- идентификатор текстуры карты анимации (Текстура может быть также описана в ресурсах (элемент texture2D).
//				  размеры текстуры ДОЛЖНЫ БЫТЬ степенью 2)
//
//	Дочерние элеметы <Animation>
//
//	1. <frames width="73" height="81" count="6" first="1" last="5"/>
//			-	width	 - ширина одного кадра
//			-	height	 - высота одного кадра
//			-	count	 - количество кадров
//			-	first	 - номер первого проигрываемого кадра (при нереверсивном воспроизведении)
//			-	last	 - номер последнего проигрываемого кадра (при нереверсивном проигрывании)

//	2. <playback fps="5" play="1" loop="1" forward="0" pingpong="1"/> 
//			-	fps		 - скорость воспроизведения (кадров в секунду)
//			-	play	 - воспроизводить анимацию? 
//			-	loop	 - зациклить проигрывание?
//			-	forward  - воспроизводить, начиная с кадра 0 (вперед)?
//			-	pingpong - воспроизводить в стиле "пинг-понг"?
//****************************************************************************************
#ifndef _RENDER_ANIMATION_H_
#define _RENDER_ANIMATION_H_

#define ANIM_FWD				0
#define ANIM_REV				1
#define ANIM_PINGPONG			2
#define ANIM_NOPINGPONG			0
#define ANIM_LOOP				4
#define ANIM_NOLOOP				0

#include "Render/Texture.h"
#include "Render/sheet.h"
#include "Render/VertexBuffer.h"
#include "Render/RenderFunc.h"

namespace Render {

	/// Класс анимации. 

	/// Задаётся в описании ресурсов в виде кода подобного следующему:
	/// \code
	/// <animation id="GearAnimation" texture="#GearTexture">
	/// 	<frames width="32" height="32" count="8" first="0" last="7"/>
	/// 	<playback fps="24" play="1" loop="1" forward="0" pingpong="0"/> 
	/// </animation>
	/// \endcode
	/// Данное описание подходит для анимации сложенной в текстуре и упорядоченной по размеру.
	/// Для анимации в виде отдельных кадров задаётся путь к файлам кадров, сами кадры упорядочиваются по алфавиту.
	/// \code
	///	<animation id="FishMoveAnimation" path="animations\fish_move">
	///		<playback fps="24" play="1" loop="1" forward="1" pingpong="0"/> 
	///	</animation>
	/// \endcode
	class Animation
	{
	protected:
		
		/// Если используется одна текстура
		Render::Texture *_texMap;
		
		/// Если используется путь, содержащий множество текстур (каждый кадр отдельно)
		Render::Texture **_texArray;
		
		/// Если используются кадры запакованные в полотнище
		Render::Sheet *_sheet;
		
		/// Текущая текстура из полотнища
		Render::Texture *_sheet_texture, *_sheet_next_texture;
				
		IPoint position;

		int		_iFrameWidth;
		int		_iFrameHeight;
		int		_iFramesCount;
		int		_iCurrentFrame;	
		int		_iFirstPlayedFrame;
		int		_iLastPlayedFrame;
		bool	_bIsPlaying;
		
		/// устанавливается в true при пересечении границы анимации
		bool    _isFinished;

		float	_fSpeed;
		
		/// время, прошедшее с последней смены кадра
		float	_fSinceChangeTime;			
		
		/// координаты кадра в текстуре
		FRect uv, uvNext;
		
		/// доля одного кадра в текстуре (ширина и высота)
		float	_fXFramePerTex,_fYFramePerTex;

		/// направление воспроизведения
		int		_iDelta;
		
		/// режим воспроизведения
		int		_iMode;
		
		/// идентификатор анимации, считанный из xml
		std::string _id;

		/// группа для анимации
		std::string _group;
		
		/// рисовать горизонтально отражённую анимацию
		bool mirrored;
		
		int alphaBlend;

	public:
		typedef boost::shared_ptr<Animation> HardPtr;
		
		typedef boost::weak_ptr<Animation> WeakPtr;
		
		Animation();
		
		Animation(const Animation& anim);

		Animation(rapidxml::xml_node<>* elem);
		Animation(Xml::TiXmlElement* elem);

		static Animation* getFromXml(rapidxml::xml_node<>* elem);
		static Animation* getFromXml(Xml::TiXmlElement* elem);

		virtual ~Animation(void);
		
		Animation& operator=(const Animation& anim);
		
		virtual Animation* Clone() const;

		void	Upload(bool bCleanAfterUpload = true);
		
		void	Bind(int channel = 0, int stageOp = 0);
		
		void	setFilter(Render::Texture::FilteringType filter);
		
		void	Draw();
		
		void	Draw(const IPoint& position);
		
		void	Update(float dt);
		
		void	setCurrentFrame(int iFrame);
		
		void	setFirstPlayedFrame(int iFrame);
		
		void	setLastPlayedFrame(int iFrame);
		
		void	setMode(int iMode);
		
		void	setSpeed(float fFPS);
		
		void	setPlayback(bool bPlayback);
		
		void    setLoop(bool l);

		bool	IsPlaying() const {return _bIsPlaying;}
		
		bool    IsFinished() const {return !_bIsPlaying || _isFinished; }
		
		int		getMode() const {return _iMode;}
		
		float	getSpeed() const {return 1.0f/_fSpeed;}
		
		int		getCurrentFrame() const	{return _iCurrentFrame;}
		
		int		getFirstPlayedFrame() const {return _iFirstPlayedFrame;}
		
		int		getLastPlayedFrame() const {return _iLastPlayedFrame;}
		
		int		getFrameWidth() const {return _iFrameWidth;}
		
		int		getFrameHeight() const {return _iFrameHeight;}
		
		int		getFramesCount() const {return _iFramesCount;}
		
		FRect	getFrameUV() const;
		
		void    MoveTo(const IPoint& point);
		
		/// идентификатор анимации, считанный из xml
		std::string GetId() const;
		
		bool    GetMirrored() const;
		
		/// рисовать горизонтально отражённую анимацию
		/// влияет на Draw
		void    SetMirrored(bool m);
		
		virtual bool isPixelTransparent(int x, int y);
		
		virtual bool isPixelOpaque(int x, int y);
		
		virtual bool isPixelOpaque(const IPoint& p);
		
		/// Указывает нужно ли трансформировать текстурные координаты. Если да, то необходимо вызвать TranslateUV перед отрисовкой.
		virtual bool needTranslate();
		
		/// Трансформация текстурных координат. Вызывается в RenderDeviceImpl если needTranslate возвращает true.
		virtual void TranslateUV(FPoint &uv);
		
		/// Трансформация текстурных координат. Вызывается в RenderDeviceImpl если needTranslate возвращает true.
		virtual void TranslateUV(FRect &rect, FRect &uv);
	};
}

#endif

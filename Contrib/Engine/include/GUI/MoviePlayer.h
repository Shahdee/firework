#ifndef _GUI_MOVIEPLAYER_H_
#define _GUI_MOVIEPLAYER_H_

#include "GUI/Widget.h"
#include "GUI/MoviePlayerControl.h"

namespace GUI {

class MoviePlayerWidget : public GUI::Widget
{
private:

	float scale;
	Render::Texture* _ramka;
	//Text *_textSkip;
	IPoint _lastMousePos;
	float _trueTimer;
	//Text *_multText;

	Render::Texture* _fotka;
	bool _skipMult;
	float _skipTimer;
	bool _startText;
	SplinePath<FPoint> _movePhoto;
	SplinePath<float> _scalePhoto;
	SplinePath<float> _anglePhoto;

	int	                _currentScene;// Номер текущей сцены

	struct SceneInfo
	{
		string path;
		float speed;
	};

	std::vector<SceneInfo> _scenes;      // Вектор сцен
	string              _nameMovie;   // запомнить, то что будем играть
	float               _timer;       // 

	bool 
		// применять ли затемнение в начале и в конце сцены
		_applyFading,
		// ставить на паузу при завершении (а не останавливать с выгрузкой всех сцен) 
		_pauseOnFinish;

	struct Subtitle {
		std::string nameSound;
		bool startMusic;
		float startMusicTime;
		Text  *text;    // текст
		float startTime;// начало показывания
		float endTime;  // конец показывания
		IPoint pos;      // позиция вывода субтитров
		long sndId; // идентификатор проигрываемого звука
		Subtitle(Text *_text, float _sTime, float _eTime, const IPoint &p, std::string nameSount, float sMusicTime) 
			: text(_text)
			, startTime(_sTime)
			, endTime(_eTime)
			, pos(p) 
			, nameSound(nameSount)
			, startMusicTime(sMusicTime)
			, startMusic(false)
			, sndId(-1)
		{};

		void StopMusic();
	};
	std::list<Subtitle> _subtitle;    // субтитры

	struct FonSound
	{
		string nameSound;
		float time;
		float pause;
		bool start;

		void Init();
		void Update(float dt);
		void Stop();
	};
	std::vector< FonSound > _fonSound;
	typedef std::list<Subtitle>::iterator IterSubtitle;
	MoviePlayer::ResourceManager::HardPtr resources;
	std::vector< MoviePlayerControl *> vectorPlayer;
	MoviePlayerControl *player;    // Плеер

	enum { 
		Stopped,
		Playing, 
		Paused 
	} _playerState; // Состояние плеера

	static const float FADE_TIME; //время затенения экрана смены 
	float stop_time;              //время следующей остановки
	float _playerTimeScale;		
	//bool CheckTextInRect();

	void DrawSkipPanel();

public:
	MoviePlayerWidget(const string& name_, Xml::TiXmlElement* elem_);
	~MoviePlayerWidget();
	virtual void Draw();
	virtual void Update(float dt);
	virtual void AcceptMessage(const Message &message);
	virtual Message QueryState(const Message& message) const;
	//virtual bool MouseDown(const IPoint& mouse_pos);
	//virtual void MouseUp(const IPoint& mouse_pos);
	//virtual void MouseMove(const IPoint& mouse_pos);
	
	// Во всех PlayXXX() параметр looped назначает зацикленное проигрывание сцены мультфильма

	// Воспроизвести мультфильм, сцены которого расположены в файле filename;
	// если что-то уже проигрывается -- проигрывание продолжится
	void Play(std::string filename, bool looped = false);

	// Продолжить воспроизведение после паузы
	void Play(bool looped = false);                  

	// Остановить воспроизведение
	void Stop(bool skip = false);   

	// Приостановить воспроизведение
	void Pause();

	// Работает как пропуск всего мультфильма, отличие от Stop() -- кладёт в очередь другое сообщение
	void SkipScene();               

	// Собственно загрузка мультфильма из файла и запуск проигрывания
	void PlayMovie(std::string filename, bool looped = false);

	// Воспроизвести указанную сцену уже загруженного мультфильма
	void PlayScene(int scene, bool looped = false);

	// Включить/выключить режим затемнения в начале и в конце сцены
	void SetFading(bool value);

	// Приостанавливать в конце мультфильма или завершать с выгрузкой сцен
	void SetToPauseOnFinish(bool value);

	bool isPlaying() const { return _playerState == Playing; }
	bool isStopped() const { return _playerState == Stopped; }
	bool isPaused() const { return _playerState == Paused; }
};
};

#endif

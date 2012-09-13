#ifndef _GUI_MOVIEPLAYERCONTTROL_H_
#define _GUI_MOVIEPLAYERCONTTROL_H_

#include "MoviePlayerResMgr.h"
#include "MoviePlayerObjects.h"

class MoviePlayerControl
{
public:

	MoviePlayerControl(MoviePlayer::ResourceManager::HardPtr resources);

	~MoviePlayerControl();

	void Play(const std::string& filename);

	void Stop();

	bool IsStopped();

	bool IsEnd() { return _stop; };

	void Draw(int moveY = 0, float scale = 1.0f);

	void Update(float dt);

	void Pause() { _stop = true; };

	void Run() { _stop = false; };

	void SetLooped(bool value);

	bool IsLooped() const;

	float GetDuration();

	float GetProgress();

	void Rewind();

	FPoint GetObjPosition(const string& id);

	IPoint GetPosition() const;
	void SetPosition(const IPoint& p);

	static void LuaInit(lua_State **state);

private:

	typedef std::list<MoviePlayerObjectHardPtr> Objects;

	typedef Objects::iterator Iterator;

	typedef Objects::reverse_iterator ReverseIterator;

	enum { STATE_STOPPED = 0, STATE_PLAYING } _state;

	MoviePlayer::ResourceManager::HardPtr _resources;

	Objects _objects;

	float _duration;

	float _time;

	float _localTime;

	int _xPos, _yPos, _width, _height;

	int _frameCount;

	bool _stop;

	lua_State *_luaState;

	bool _error, _luaPresent;

	bool _looped;

	void LuaInit(const std::string& filename);

	void SmallUpdate(float dt);

	void RecalcTime(float dt);

	void PlayFile(const std::string& filename);

	void PlayXml(Xml::TiXmlElement *root);

	void Init();

	void Clear();
	
	void Purge();

	void LoadParams(Xml::TiXmlElement *root);

	void LoadObjects(Xml::TiXmlElement *objects);

	void ClearObjects();

};

#endif

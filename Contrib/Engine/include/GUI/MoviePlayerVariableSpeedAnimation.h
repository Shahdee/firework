#ifndef _GUI_MOVIEPLAYERVARIABLESPEEDANIMATION_H_
#define _GUI_MOVIEPLAYERVARIABLESPEEDANIMATION_H_

#include "MoviePlayerAnimation.h"

//
// Анимация с переменной скоростью
//
class MoviePlayerVariableSpeedAnimation
{
public:

	typedef boost::shared_ptr<MoviePlayerVariableSpeedAnimation> HardPtr;
		// тип указателя со счётчиком ссылок

private:

	int _currentFrame;

	int _firstFrame;

	int _lastFrame;

	float _speed;

	float _progress;

	bool _isPlaying;

	bool _isForwardPing;

	bool _isLoop;

	bool _isPingPong;

	MoviePlayerAnimationResource::WeakPtr _animation;

public:

	MoviePlayerVariableSpeedAnimation(MoviePlayerAnimationResource::WeakPtr animation, float startSpeed)
		: _animation(animation)
		, _isPlaying(true)
		, _progress(0.0f)
	{
		Assert(startSpeed > 0.0f);
		_speed = startSpeed;
		_firstFrame = 0;
		_lastFrame = _animation->size() - 1;
		_currentFrame = 0;
	}

	MoviePlayerVariableSpeedAnimation(MoviePlayerVariableSpeedAnimation::HardPtr copy) {
		this->_currentFrame = copy->_currentFrame;
		this->_firstFrame = copy->_firstFrame;
		this->_lastFrame = copy->_lastFrame;
		this->_speed = copy->_speed;
		this->_progress = copy->_progress;
		this->_isPlaying = copy->_isPlaying;
		this->_isForwardPing = copy->_isForwardPing;
		this->_isLoop = copy->_isLoop;
		this->_isPingPong = copy->_isPingPong;
		this->_animation = copy->_animation;
	}

	void Draw() {
		Assert(_animation != NULL);
		Assert(_animation->size() > 0);
		Assert(_animation->size() > _currentFrame);
		_animation->GetFrame(_currentFrame)->Bind();
		_animation->GetFrame(_currentFrame)->Draw(IPoint(0, 0));
	}

	void Update(float dt, float newFrameSpeed) {
		Assert(dt > 0);
		if (!_isPlaying) {
			return;
		}
		if (_firstFrame == _lastFrame) {
			return;
		}
		Assert(_firstFrame < _lastFrame);
		_progress += dt*(_speed + newFrameSpeed)/2.0f; // формула трапеций
		_speed = newFrameSpeed;
		while (_progress >= 1.0f && _isPlaying) {
			_progress -= 1.0f;
			if (_isPingPong) {
				if (_isForwardPing) {
					_currentFrame++;
					Assert(_currentFrame <= _lastFrame);
					if (_currentFrame == _lastFrame) {
						_isForwardPing = false;
					}
				} else {
					_currentFrame--;
					Assert(_currentFrame >= _firstFrame);
					if (_currentFrame == _firstFrame) {
						_isForwardPing = true;
						if (!_isLoop) {
							_isPlaying = false;
						}
					}
				}
			} else {
				if (_currentFrame < _lastFrame) {
					_currentFrame++;
					if (_currentFrame == _lastFrame && !_isLoop) {
						_isPlaying = false;
					}
				} else {
					_currentFrame = _firstFrame;
				}
			}
		}
	}

	void setMode(int mode) {
		if (mode == 0) {
			// fwd, no ping pong, no loop
			_isPingPong = false;
			_isLoop = false;
			_currentFrame = _firstFrame;
		} else if (mode == 2) {
			// fwd, ping pong, no loop
			_isPingPong = true;
			_isForwardPing = true;
			_isLoop = false;
			_currentFrame = _firstFrame;
		} else if (mode == 4) {
			// fwd, no ping pong, loop
			_isPingPong = false;
			_isLoop = true;
			_currentFrame = _firstFrame;
		} else if (mode == 6) {
			// fwd, ping pong, loop
			_isPingPong = true;
			_isForwardPing = true;
			_isLoop = true;
			_currentFrame = _firstFrame;
		} else {
			Assert(false);
		}
	}

	void setPlayback(bool isPlaying) {
		_isPlaying = isPlaying;
	}

	bool IsPlaying() {
		return _isPlaying;
	}

	int getFrameWidth() {
		return _animation->GetFrame(0)->getBitmapRect().width;
	}

	int getFrameHeight() {
		return _animation->GetFrame(0)->getBitmapRect().height;
	}

	int getFramesCount() {
		return _animation->size();
	}

	void Reset()
	{
		_isPlaying = true;
		_progress = 0.0f;
		_isForwardPing = true;
		_currentFrame = _firstFrame;
	}
};

#endif

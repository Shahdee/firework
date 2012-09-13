#pragma once

#include "GUI/Widget.h"

class IController
{
	std::string _name;

public:
	IController();

	IController(const std::string& name);

	virtual ~IController();

	float local_time;
	bool finished;
	bool paused;

	std::string getName();

	virtual void Update(float dt) = 0;
	virtual bool isFinish() = 0;
};

namespace Core
{

class ControllerManager 
{
	friend class ScreenImpl;

	std::list<IController*> _controllers;
	std::list<IController*> _addedControllers;
	typedef std::list<IController*>::iterator contr_iterator;

public:
	ControllerManager();
	~ControllerManager();

	bool isAdded;

	void Update(float dt);
	void KillControllers(const std::string& name);
	void PauseControllers(const std::string& name);
	void ContinueControllers(const std::string& name);
	void addController(IController* wManipulator);
	void addQueuedController();
	void UpdateAdded(float dt);
};

extern ControllerManager controllerKernel;

}

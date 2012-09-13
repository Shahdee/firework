#pragma once

#include "Core/MessageManager.h"
#include "Core/Screen.h"
#include "Core/Script.h"

class MessageFunc
{
	friend class Layer;

	Layer *_bindLayer;

public:
	MessageFunc();

	virtual ~MessageFunc();

    Layer* getThisLayer();

	virtual void AcceptMessage(const Message& message);

	static MessageFunc* Create(const std::string& className);
};

class LuaHandlerFunc : public MessageFunc
{
	std::string _functionName;

public:
	LuaHandlerFunc(const std::string& functionName);

	virtual void AcceptMessage(const Message& message);

};
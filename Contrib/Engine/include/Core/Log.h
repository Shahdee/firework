#pragma once

#include "BuildSettings.h"

#ifdef THREADED
	#include <boost/thread/recursive_mutex.hpp>
#endif

namespace Core
{
	class Log
	{
	private:

	#ifdef USE_LOG
		FILE *_fpLog;
		std::string _logFileName;
	#endif
	
#ifdef THREADED
	boost::recursive_mutex writeMutex;
#endif

		// Вернуть отформатированное время
		//static std::string GetTime();
		
		void WriteTime();

		void Write(const std::string& msg);

	public:

		Log();

		~Log();

		void Init(const std::string& fileName, bool reCreate);

		void WriteMessage(const std::string& msg, const std::string& msgColor);

		void WriteMessage(const std::string& msg);

		void WriteError(const std::string& errorName, const std::string& msg);

		void WriteError(const std::string& msg);

		void WriteLine(const std::string& msg);

		void WriteEvent(const std::string& eventName, const std::string& eventColor, const std::string& msg);

		// Вывести сообщение в консоль
		//static void Echo(const std::string& message);
	};

	extern Log log;

	void WriteError(const std::string& errorName, const std::string& msg);

	void WriteError(const std::string& msg);

	void WriteLine(const std::string& msg);

	void WriteMessage(const std::string& msg);

	void WriteDebugMessage(const std::string& msg);

	void Error(const std::string& errorName, const std::string& msg);

	void Error(const std::string& msg);

}


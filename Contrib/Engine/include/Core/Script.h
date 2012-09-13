#pragma once

struct lua_State;
struct lua_Debug;

// основные функции для работы с Lua
namespace Core
{
#ifdef THREADED
#include <boost/thread.hpp>
	extern boost::recursive_mutex luaMutex;
#define SCRIPT_THREAD_LOCK boost::recursive_mutex::scoped_lock lock(luaMutex);
#else
#define SCRIPT_THREAD_LOCK
#endif
	
	extern lua_State* luaState;
	extern lua_State* luaStateMain;

	void InitLua();

	void LuaDoFile(const std::string& filename);
	void LuaDoString(const std::string& str);

	int LuaErrorHandler(lua_State *L); ///< Вызывается при ошибках в Lua.
	int LuaError(lua_State *L, std::string message = "");

	std::string LuaToString(const luabind::object& obj); // Дамп переменной lua
	std::string LuaDumpLocals(lua_State * L, lua_Debug * d); // Дамп всех локальных переменных
	std::string LuaDumpStack(lua_State *L, bool dump_locals); // Возвращает call stack

	void LuaStackTrace(lua_State *L = luaState); ///< Печатает call stack в консоль и в лог.
	void LuaPrintStack(); ///< Вспомогательная функция для печати lua call stack.

	void LuaStartDebugging();
	void LuaStopDebugging();
	
	void LuaBreak();

	//------------------------------------------------------------------

	template <class TRet>
	inline TRet LuaCallFunction(const char* funcName)
	{
		try {
			return (TRet)luabind::call_function<TRet>(luaState, funcName);
		}
		catch (luabind::error &e) {
			LuaError(e.state(), std::string("LUA: Error in call ") + funcName +": "+ e.what());
		}
		return TRet();
	}

	template <class TRet, class A1>
	inline TRet LuaCallFunction(const char* funcName, const A1& arg1)
	{
		SCRIPT_THREAD_LOCK;
		try {
			return (TRet)luabind::call_function<TRet>(luaState, funcName, arg1);
		}
		catch (luabind::error &e) {
			LuaError(e.state(), std::string("LUA: Error in call ") + funcName +": "+ e.what());
		}
		return TRet();
	}

	inline void LuaCallVoidFunction(const char* funcName)
	{
		LuaCallFunction<void>(funcName);
	}
	
	template <class A1>
	inline void LuaCallVoidFunction(const char* funcName, const A1& arg1)
	{
		LuaCallFunction<void, A1>(funcName, arg1);
	}

	template<class TRet>
	inline TRet LuaCallFunction(const luabind::object& obj)
	{
		SCRIPT_THREAD_LOCK;
		try {
			if ( obj.interpreter() != luaState ) {
				return (TRet)luabind::call_function<TRet>(luabind::object(luaState, obj));
			} else {
				return (TRet)luabind::call_function<TRet>(obj);
			}
		}
		catch (luabind::error &e) {
			LuaError(e.state(), std::string("LUA: Error in call_function ") + utils::lexical_cast(obj) +": "+ e.what());
		}
		return TRet();
	}
	
	template<class TRet, class A1>
	inline TRet LuaCallFunction(const luabind::object& obj, const A1& arg1)
	{
		SCRIPT_THREAD_LOCK;
		try {
			if ( obj.interpreter() != luaState ) {
				return (TRet)luabind::call_function<TRet>(luabind::object(luaState, obj), arg1);
			} else {
				return (TRet)luabind::call_function<TRet>(obj, arg1);
			}
		}
		catch (luabind::error &e) {
			LuaError(e.state(), std::string("LUA: Error in call_function ") + utils::lexical_cast(obj) +": "+ e.what());
		}
		return TRet();
	}
	
	//------------------------------------------------------------------
	
	template<class T>
	inline T LuaCast(const luabind::object& obj) {
		try {
			return luabind::object_cast<T>(obj);
		} catch(luabind::cast_failed &e) {
			LuaError(e.state(), std::string("LUA: Cast error: ") + e.what());
		}
		return T();
	}
	
	//------------------------------------------------------------------
	
	// Вспомогательный класс, обеспечивающий замену luaState
	// на время текущей области видимости.
	class TmpLuaStateChanger {
		lua_State* tmp;
	private:
		TmpLuaStateChanger(const TmpLuaStateChanger&); // non-copyable!
		TmpLuaStateChanger& operator=(const TmpLuaStateChanger&);
	public:
		TmpLuaStateChanger(lua_State* s) { tmp = luaState; luaState = s; }
		~TmpLuaStateChanger() { luaState = tmp; }
	};

	//------------------------------------------------------------------
	
	template<typename TRet>
	inline TRet LuaResumeFunction(const char * funcName)
	{
		SCRIPT_THREAD_LOCK;
		try {
			luabind::object fun = luabind::globals(luaState)[funcName];
			return (TRet)luabind::resume_function<TRet>(fun);
		}
		catch (luabind::error &e) {
			LuaError(e.state(), std::string("LUA: Error in resume_function ") + funcName +": "+ e.what());
		}
		return TRet();
	}

	inline void LuaResumeVoidFunction(const char * funcName)
	{
		LuaResumeFunction<void>(funcName);
	}

	template<typename TRet, typename A1>
	inline TRet LuaResumeFunction(const char * funcName, const A1& arg1)
	{
		SCRIPT_THREAD_LOCK;
		try {
			luabind::object fun = luabind::globals(luaState)[funcName];
			return (TRet)luabind::resume_function<TRet>(fun, arg1);
		}
		catch (luabind::error &e) {
			LuaError(e.state(), std::string("LUA: Error in resume_function ") + funcName +": "+ e.what());
		}
		return TRet();
	}

	template<typename A1>
	inline void LuaResumeVoidFunction(const char * funcName, const A1& arg1)
	{
		LuaResumeFunction<void>(funcName, arg1);
	}
	
	template<typename TRet>
	inline TRet LuaResumeFunction(const luabind::object& func)
	{
		SCRIPT_THREAD_LOCK;
		try {
			if ( func.interpreter() != luaState ) {
				return (TRet)luabind::resume_function<TRet>(luabind::object(luaState, func));
			} else {
				return (TRet)luabind::resume_function<TRet>(func);
			}
		}
		catch (luabind::error &e) {
			LuaError(e.state(), std::string("LUA: Error in resume_function ") + utils::lexical_cast(func) +": "+ e.what());
		}
		return TRet();
	}
	
	template<typename TRet>
	inline TRet LuaResume()
	{
		SCRIPT_THREAD_LOCK;
		try {
			return (TRet)luabind::resume<TRet>(luaState);
		}
		catch (luabind::error &e) {
			LuaError(e.state(), std::string("LUA: Error in resume: ") + e.what());
		}
		return TRet();
	}

	inline void LuaResumeVoid() {
		LuaResume<void>();
	}

	template<typename TRet, typename A1>
	inline TRet LuaResume(const A1& arg1)
	{
		SCRIPT_THREAD_LOCK;
		try {
			return (TRet)luabind::resume<TRet>(luaState, arg1);
		}
		catch (luabind::error &e) {
			LuaError(e.state(), std::string("LUA: Error in resume: ") + e.what());
		}
		return TRet();
	}

	template<typename A1>
	inline void LuaResumeVoid(const A1& arg1) {
		LuaResume<void>(arg1);
	}

}


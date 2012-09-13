#undef assert
#undef Assert

#ifdef _DEBUG

#ifdef ENGINE_TARGET_WIN32
//Windows
#define assert(exp) do { if (!(exp)) _CrtDbgBreak(); } while(0)
#define halt(message) assert(false)
#endif // ENGINE_TARGET_WIN32

#ifdef ENGINE_TARGET_IPHONE
// iPhone
#define assert(exp) do { if(!(exp)) { AssertionFailed("assersion failed", #exp, __FILE__, __LINE__); }; } while(0)
#define halt(message) AssertionFailed(message, 0, __FILE__, __LINE__)

#ifdef __cplusplus
extern "C"
#endif
void AssertionFailed(const char* message, const char* expression, const char* file, int line);

#endif // ENGINE_TARGET_IPHONE

#endif // _DEBUG

// In release-mode assert do nothing
#ifndef assert

#ifdef ENGINE_TARGET_WIN32
#define assert(exp) (exp)
#define halt(message)
#endif

#ifdef ENGINE_TARGET_IPHONE
#define assert(exp) ((void)sizeof(exp))
#define halt(message)
#endif

#endif // !assert

#define Assert(exp) assert(exp)

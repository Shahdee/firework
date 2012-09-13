#pragma once
#if defined(PROFILE_ES_CALLS)
	
	void __esProf__bind(int i);
	void __esProf__draw(int i);
	void __esProf__matrix(int i);
	void __esProf__state(int i);
	void __esProf__info();
	void __esProf__begin();
	void __esProf__end();

	#define PROFILE_BIND(i) __esProf__bind(i);
	#define PROFILE_DRAW(i) __esProf__draw(i);
	#define PROFILE_MATRIX(i) __esProf__matrix(i);
	#define PROFILE_STATE(i) __esProf__state(i);

	#define PROFILE_INFO __esProf__info();

	#define PROFILE_FRAME_BEGIN __esProf__begin();
	#define PROFILE_FRAME_END __esProf__end();

#else

	#define PROFILE_BIND(i) 
	#define PROFILE_DRAW(i) 
	#define PROFILE_MATRIX(i) 
	#define PROFILE_STATE(i) 

	#define PROFILE_INFO 

	#define PROFILE_FRAME_BEGIN 
	#define PROFILE_FRAME_END 

#endif
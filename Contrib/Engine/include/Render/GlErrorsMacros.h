/*
 *  GlErrorsMacros.h
 *  Engine
 *
 *  Created by Slava on 18.06.10.
 *  Copyright 2010 Playrix Entertainment. All rights reserved.
 *
 */

#ifndef GL_ERROR_MACROS_INCLUDED
#define GL_ERROR_MACROS_INCLUDED

// Макрос проверки OpenGL на ошибки;
// вставляем его в конец каждой функции
// или куда угодно при отладке
#ifdef _DEBUG
#	define GL_ERRORS_CHECK GlErrorsCheck__(__FILE__, __LINE__)
#else
#	define GL_ERRORS_CHECK
#endif

// Макрос очистки очереди ошибок OpenGL
// Работает так же, как и GL_ERRORS_CHECK, отличие в том,
// что в любом случае очищает очередь ошибок
#ifdef _DEBUG
#	define GL_ERRORS_CLEAR GlErrorsClearDebug__(__FILE__, __LINE__)
#else
#	define GL_ERRORS_CLEAR GlErrorsClearRelease__()
#endif

#ifdef __cplusplus
extern "C" {
#endif]
	
// Проверяет, была ли ошибка при выполнении функций OpenGL;
// не вызывайте напрямую, пользуйтесь GL_ERRORS_CHECK;
void GlErrorsCheck__(const char *filename, int line);

// Очищает очередь сообщений об ошибках; предназначена для режима Release;
// не вызывайте напрямую, пользуйтесь GL_ERRORS_CLEAR;
void GlErrorsClearRelease__();

// Очищает очередь сообщений об ошибках; предназначена для режима Debug;
// не вызывайте напрямую, пользуйтесь GL_ERRORS_CLEAR;
void GlErrorsClearDebug__(const char *filename, int line);

#ifdef __cplusplus
}
#endif

#endif
#ifndef NSSTRINGUTF8_INCLUDED
#define NSSTRINGUTF8_INCLUDED

//
// Расширение NSString для более простой перегонки из NSString в const char* и обратно
// используя кодировку Utf8
//
@interface NSString(Utf8)

//
// Из C-строки в кодировке UTF8 получить NSString
// вызов выглядит так:
// 		NSString* s = [NSString fromUtf8String:cString];
// чем аналогичная констркция, которая работает "из коробки":
// 		NSString* s = [NSString stringWithCString:cString encoding:NSUTF8StringEncoding];
//
+ (NSString*) fromUtf8String:(const char*)cString;

//
// Из NSString получить C-строку в кодировке UTF8
// вызов выглядит так:
//		const char* s2 = [s toUtf8String];
// аналогичная конструкция, работающая "из коробки":
// 		const char* s2 = [s cStringUsingEncoding:NSUTF8StringEncoding];
//
// Внимание:
//  Возвращаемая строка авторелизная, поэтому если вам нужно ее хранить долго,
//  скопируйте ее куда-нибудь
//
- (const char*) toUtf8String;

#ifdef __cplusplus

#include <string>

// Аналог fromUtf8String: для стандартной строки
+ (NSString*) fromUtf8StdString:(std::string)stdString;

// Аналог toUtf8String для стандартной строки
// Здесь нет ограничения по хранению, как в toUtf8String
- (std::string) toUtf8StdString;

#endif // __cplusplus

@end // NSString(Utf8)

#endif // NSSTRINGUTF8_INCLUDED
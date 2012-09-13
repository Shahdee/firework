#ifndef ENGINE_WRAPPER_INCLUDED
#define ENGINE_WRAPPER_INCLUDED

// Класс, представляющий из себя Objective-C интерфейс к
// часто используемым функциям движка
// (нужно чтобы не смешивать Objective-C и C++ и чтобы волосы
// были шелковистее)
@interface EngineWrapper : NSObject {
	
}

//
// Вернуть текст из ресурс-менеджера
// Возвращает GetSource(), то есть немодифицированный текст
//
+(NSString*)getText:(const char*)idText;

@end

#endif

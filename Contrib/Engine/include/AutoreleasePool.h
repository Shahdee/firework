#ifndef AUTORELEASE_POOL_INCLUDED
#define AUTORELEASE_POOL_INCLUDED

//
// Класс, предоставляющий C++ интерфейс для NSAutoreleasePool (нужно в iOS):
// в конструкторе создает объект NSAutoreleasePool,
// в деструкторе освобождает его.
//
class AutoreleasePool
{
#ifdef ENGINE_TARGET_IPHONE

public:

	// Создаем объект типа NSAutoreleasePool*
	AutoreleasePool();
	
	// Освобождаем ресурсы, которыми владеет объект типа NSAutoreleasePool*
	~AutoreleasePool();
	
private:
	
	void* _pool;
		// тип void, а не NSAutoreleasePool, чтобы нормально скомпилировался чисто C++ код
	
#endif
};

#endif // AUTORELEASE_POOL_INCLUDED
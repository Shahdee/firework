#ifndef __SCENEGRAPH_UTILS_H__
#define __SCENEGRAPH_UTILS_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

namespace SceneGraph {

///
/// Безопасно освобождает интерфейс, унаследованный от IUnknown.
///
template<class T> UINT SafeRelease(T*& pT) {
	UINT cRef = 0;
	if (pT) {
		cRef = pT->Release();
		pT = NULL;
	}
	return cRef;
}

///
/// Безопасно удаляет указатель на объект в куче.
///
template<class T> void SafeDeletePtr(T*& pT) {
	if (pT) {
		delete pT;
		pT = NULL;
	}
}

///
/// Безопасно удаляет указатель на массив в куче.
///
template<class T> void SafeDeleteArray(T*& pT) {
	if (pT) {
		delete[] pT;
		pT = NULL;
	}
}

} // namespace SceneGraph

#endif // __UTILS_H__

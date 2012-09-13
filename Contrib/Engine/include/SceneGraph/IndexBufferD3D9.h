#ifndef __INDEXBUFFERD3D9_H__
#define __INDEXBUFFERD3D9_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include <d3d9.h>
#include "DeviceBuffer.h"

namespace SceneGraph {

///
/// Буфер индексов.
///
class IndexBufferD3D9 : public DeviceBuffer {
public:
	typedef boost::shared_ptr<IndexBufferD3D9> HardPtr;
	
	typedef boost::weak_ptr<IndexBufferD3D9> WeakPtr;
	
	IndexBufferD3D9(LPDIRECT3DINDEXBUFFER9 indices, std::size_t count, std::size_t stride);
	
	virtual ~IndexBufferD3D9();
	
	void* GetDeviceObject() const;
		/// Возвращает указатель на объект аппаратного буфера
	
	void* Lock();
		/// Блокирует весь буфер для доступа к его данным
	
	void Unlock();
		/// Разблокирует буфер.
		/// Должен быть вызван, если предшествующий вызов Lock был выполнен успешно.

protected:
	LPDIRECT3DINDEXBUFFER9 _indices;
		/// Буфер индексов
};

} // namespace SceneGraph

#endif // __INDEXBUFFERD3D9_H__

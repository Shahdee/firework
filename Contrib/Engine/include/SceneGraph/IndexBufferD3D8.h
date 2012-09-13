#ifndef __INDEXBUFFERD3D8_H__
#define __INDEXBUFFERD3D8_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include <d3d8.h>
#include "DeviceBuffer.h"

namespace SceneGraph {

///
/// Буфер индексов.
///
class IndexBufferD3D8 : public DeviceBuffer {
public:
	typedef boost::shared_ptr<IndexBufferD3D8> HardPtr;
	
	typedef boost::weak_ptr<IndexBufferD3D8> WeakPtr;
	
	IndexBufferD3D8(LPDIRECT3DINDEXBUFFER8 indices, std::size_t count, std::size_t stride);
	
	virtual ~IndexBufferD3D8();
	
	void* GetDeviceObject() const;
		/// Возвращает указатель на объект аппаратного буфера
	
	void* Lock();
		/// Блокирует весь буфер для доступа к его данным
	
	void Unlock();
		/// Разблокирует буфер.
		/// Должен быть вызван, если предшествующий вызов Lock был выполнен успешно.

protected:
	LPDIRECT3DINDEXBUFFER8 _indices;
		/// Буфер индексов
};

} // namespace SceneGraph

#endif // __INDEXBUFFERD3D8_H__

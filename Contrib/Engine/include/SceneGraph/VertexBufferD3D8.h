#ifndef __VERTEXBUFFERD3D8_H__
#define __VERTEXBUFFERD3D8_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include <d3d8.h>
#include "DeviceBuffer.h"

namespace SceneGraph {

///
/// Буфер вершин.
///
class VertexBufferD3D8 : public DeviceBuffer {
public:
	typedef boost::shared_ptr<VertexBufferD3D8> HardPtr;
	
	typedef boost::weak_ptr<VertexBufferD3D8> WeakPtr;
	
	VertexBufferD3D8(LPDIRECT3DVERTEXBUFFER8 vertices, DWORD FVF, std::size_t count, std::size_t stride);
	
	virtual ~VertexBufferD3D8();
	
	void* GetDeviceObject() const;
		/// Возвращает указатель на исходный буфер
	
	DWORD GetFVF() const;
		/// Возвращает формат вершин, хранящихся в буфере
	
	void* Lock();
		/// Блокирует весь буфер для доступа к его данным
	
	void Unlock();
		/// Разблокирует буфер.
		/// Должен быть вызван, если предшествующий вызов Lock был выполнен успешно.

protected:
	LPDIRECT3DVERTEXBUFFER8 _vertices;
		/// Буфер вершин
	
	DWORD _FVF;
		/// Формат вершины
};

} // namespace SceneGraph

#endif // __VERTEXBUFFERD3D8_H__

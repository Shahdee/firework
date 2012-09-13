#ifndef __VERTEXBUFFERD3D9_H__
#define __VERTEXBUFFERD3D9_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include <d3d9.h>
#include "DeviceBuffer.h"

namespace SceneGraph {

///
/// ����� ������.
///
class VertexBufferD3D9 : public DeviceBuffer {
public:
	typedef boost::shared_ptr<VertexBufferD3D9> HardPtr;
	
	typedef boost::weak_ptr<VertexBufferD3D9> WeakPtr;
	
	VertexBufferD3D9(LPDIRECT3DVERTEXBUFFER9 vertices, DWORD FVF, std::size_t count, std::size_t stride);
	
	virtual ~VertexBufferD3D9();
	
	void* GetDeviceObject() const;
		/// ���������� ��������� �� �������� �����
	
	DWORD GetFVF() const;
		/// ���������� ������ ������, ���������� � ������
	
	void* Lock();
		/// ��������� ���� ����� ��� ������� � ��� ������
	
	void Unlock();
		/// ������������ �����.
		/// ������ ���� ������, ���� �������������� ����� Lock ��� �������� �������.

protected:
	LPDIRECT3DVERTEXBUFFER9 _vertices;
		/// ����� ������
	
	DWORD _FVF;
		/// ������ �������
};

} // namespace SceneGraph

#endif // __VERTEXBUFFERD3D9_H__

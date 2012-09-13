#ifndef __DEVICEBUFFER_H__
#define __DEVICEBUFFER_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph.h"

namespace SceneGraph {

///
/// Базовый класс для буферов устройства.
///
class DeviceBuffer {
public:
	typedef boost::shared_ptr<DeviceBuffer> HardPtr;
	
	typedef boost::weak_ptr<DeviceBuffer> WeakPtr;
	
	DeviceBuffer(std::size_t count, std::size_t stride);
	
	virtual ~DeviceBuffer();
	
	std::size_t GetStride() const;
		/// Возвращает формат индексов в буфере
	
	std::size_t GetCount() const;
		/// Возвращает количество элементов в буфере
	
	std::size_t GetLengthBytes() const;
		/// Возвращает размер буфера в байтах
	
	virtual void* GetDeviceObject() const = 0;
		/// Возвращает указатель на объект аппаратного буфера
	
	virtual void* Lock() = 0;
		/// Блокирует весь буфер для доступа к его данным
	
	virtual void Unlock() = 0;
		/// Разблокирует буфер.
		/// Должен быть вызван, если предшествующий вызов Lock был выполнен успешно.
	
	template<class T> T* Lock() {
		assert(sizeof(T) == GetStride());
		return reinterpret_cast<T*>(Lock());
	}

private:
	std::size_t _count;
		/// Размер буфера в 'штуках'
	
	std::size_t _stride;
		/// Размер одной 'штуки'
};

} // namespace SceneGraph

#endif // __DEVICEBUFFER_H__

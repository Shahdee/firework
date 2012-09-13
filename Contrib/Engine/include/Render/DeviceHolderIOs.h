/*
 *  DeviceHolderIOs.h
 *  Engine
 *
 *  Created by Slava on 1/21/11.
 *  Copyright 2011 Playrix Entertainment. All rights reserved.
 *
 */

namespace Render {

class RenderDeviceInterface;
	
//
// Класс, ответственный за определение
// версии OpenGL ES, создание нужного девайса
// и удаления его.
// (iOs only)
//
// Экземпляр класса должен быть глобальной статической переменной,
// создающейся до Render::device.
//
class DeviceHolderIOs {

public:
	
	DeviceHolderIOs();
	
	~DeviceHolderIOs();
	
	// Возвращает ссылку на свежесозданный девайс
	// (этим нужно инициализировать Render::device)
	RenderDeviceInterface& GetDevice();

private:
	
	RenderDeviceInterface* _device;
		// собственно девайс, временем жизни которого и управляет класс
	
};

} // namespace Render
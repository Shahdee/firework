#ifndef _RENDER_SHADERPROGRAM_H_
#define _RENDER_SHADERPROGRAM_H_

#include "Utils/Vector4.h"
#include "Utils/Matrix4.h"

namespace Render {

/// Класс для управления вершинными и пиксельными шейдерами.
class ShaderProgram {
public:
	static ShaderProgram* getFromXml(rapidxml::xml_node<>* elem);
		
	virtual ~ShaderProgram() {};
	
	/// Создание пары шейдеров из файлов. Возможно задание пустой строки вместо одного из шейдеров.
	virtual bool Load(const std::string& filenameVS, const std::string& filenamePS) = 0;
	
	/// Загрузка шейдеров в устройство
	virtual void Upload() = 0;
	
	/// Выгрузка шейдеров из устройства
	virtual void Release() = 0;

	/// Связывание шейдеров с устройством
	virtual void Bind() = 0;
	
	/// Отвязывание шейдеров от устройства
	virtual void Unbind() = 0;
	
	/// Установка констант для вершинного шейдера
	virtual void setVSParam(const std::string& name, const float* fv, int size) = 0;

	/// Имеется ли данный параметр у вершинного шейдера
	virtual bool hasVSParam(const std::string& name) = 0;
	
	/// Установка констант для пиксельного шейдера
	virtual void setPSParam(const std::string& name, const float* fv, int size) = 0;

	/// Имеется ли данный параметр у пиксельного шейдера
	virtual bool hasPSParam(const std::string& name) = 0;
	
	void setVSParam(const std::string& name, const math::Vector4& v);
	
	void setVSParam(const std::string& name, const math::Matrix4& m);
	
	void setPSParam(const std::string& name, float f);
	
	void setPSParam(const std::string& name, const math::Vector4& v);
	
	void setPSParam(const std::string& name, const math::Matrix4& m);
};

inline void ShaderProgram::setVSParam(const std::string& name, const math::Vector4& v) {
	setVSParam(name, v.v, 4);
}

inline void ShaderProgram::setVSParam(const std::string& name, const math::Matrix4& m) {
	setVSParam(name, m.v, 16);
}

inline void ShaderProgram::setPSParam(const std::string& name, float f) {
	setPSParam(name, math::Vector4(f, 0, 0, 0).v, 4);
}

inline void ShaderProgram::setPSParam(const std::string& name, const math::Vector4& v) {
	setPSParam(name, v.v, 4);
}

inline void ShaderProgram::setPSParam(const std::string& name, const math::Matrix4& m) {
	setPSParam(name, m.v, 16);
}

} // namespace Render

#endif // _RENDER_SHADERPROGRAM_H_

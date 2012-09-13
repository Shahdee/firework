#pragma once

#include "Utils/Vector4.h"
#include "Utils/Matrix4.h"

#include <boost/smart_ptr.hpp>

#ifdef ENGINE_TARGET_WIN32_DX8
typedef DWORD DEVSHADER;
#else
typedef GLuint DEVSHADER;
#endif

namespace Render {

class RenderDeviceImpl;

/// Класс для управления вертексными и пиксельными шейдерами.
class ShaderProgram {
public:
	/// Создание пары шейдеров из файлов. Возможно задание пустой строки вместо одного из шейдеров.
	virtual bool LoadProgram(const std::string& vertexShader, const std::string& pixelShader) = 0;
	/// Создание из прекомпилированного кода. ИСПОЛЬЗОВАТЬ ТОЛЬКО ДЛЯ ОТЛАДКИ. Не поддерживается OpenGL.
	/// Допустимо задавать 0 вместо одного из шейдеров.
	virtual bool LoadProgram(const unsigned int* vertexFunc, const unsigned int* vertexDecl, const unsigned int* pixelFunc) = 0;
	virtual ~ShaderProgram() {}; 

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	/// Установка констант для шейдера. Параметр location определяет константу.
	virtual void setUniform(float, intconst std::string& location);
	virtual void setUniform(int , const std::string& location);
	virtual void setUniform(const math::Vector4&, const std::string& location);
	virtual void setUniform(const math::Vector3&, const std::string& location);
	virtual void setUniform(const math::Matrix4&, const std::string& location);
};


#ifdef ENGINE_TARGET_WIN32

class ShaderProgramDX :public ShaderProgram {
public:
	/// Тут задаются дополнительные возможности для DirectX. Их можно использовать ТОЛЬКО в RenderDevice.
};

///
/// Базовый класс всех шейдеров.
///
class Shader {
public:
	typedef boost::shared_ptr<Shader> HardPtr;
	
	typedef boost::weak_ptr<Shader> WeakPtr;

	virtual ~Shader() {}
	
	/// Загружает шейдер в графическое устройство
	virtual void Upload() = 0;
	
	/// Связывает шейдер с графическим устройством
	virtual void Bind() = 0;
	
	/// Устанавливает значение константы шейдера.
	/// Минимальный размер константы - float4, размер указывается в четырёхмерных векторах.
	virtual void SetConstant(int baseReg, void* value, int count) = 0;
	
	/// Отвязывает шейдер от графического устройства
	virtual void Unbind() = 0;
	
	/// Устанавливает Vector4 в качестве константы
	void SetVector4(int baseReg, const math::Vector4& v);
	
	/// Устанавливает Matrix4 в качестве константы
	void SetMatrix4(int baseReg, const math::Matrix4& m);

protected:
	Shader(const unsigned int* func) : _function(func) { }

protected:
	const unsigned int* _function;

private:
	Shader(const Shader&);
	Shader& operator = (const Shader&);
		// Конструктор копий и оператор присваивания не определены
};

inline void Shader::SetVector4(int baseReg, const math::Vector4& v) {
	SetConstant(baseReg, (void*)v.v, 1);
}

inline void Shader::SetMatrix4(int baseReg, const math::Matrix4& m) {
	SetConstant(baseReg, (void*)m.v, 4);
}


///
/// Пиксельный шейдер.
///
class PixelShader : public Shader {
public:
	typedef boost::shared_ptr<PixelShader> HardPtr;
	
	typedef boost::weak_ptr<PixelShader> WeakPtr;
	
	PixelShader(const unsigned int* func);
	
	~PixelShader();
	
	void Upload();
	
	void Bind();
	
	void SetConstant(int baseReg, void* value, int count);
	
	void Unbind();

private:
	friend class RenderDeviceImpl;
	
	DEVSHADER _handle;
};


///
/// Вершинный шейдер.
///
class VertexShader : public Shader {
public:
	typedef boost::shared_ptr<VertexShader> HardPtr;
	
	typedef boost::weak_ptr<VertexShader> WeakPtr;
	
	VertexShader(const unsigned int* func, const unsigned int* decl);
	
	~VertexShader();
	
	void Upload();
	
	void Bind();
	
	void SetConstant(int baseReg, void* value, int count);
	
	void Unbind();

protected:
	const unsigned int* _declaration;

private:
	friend class RenderDeviceImpl;
	
	DEVSHADER _handle;
};

#else

class ShaderProgramGL: public ShaderProgram {
public:
	/// Тут задаются дополнительные возможности OpenGL. Их можно использовать ТОЛЬКО в RenderDevice.
};

#endif


} // namespace Render

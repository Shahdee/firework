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

/// ����� ��� ���������� ����������� � ����������� ���������.
class ShaderProgram {
public:
	/// �������� ���� �������� �� ������. �������� ������� ������ ������ ������ ������ �� ��������.
	virtual bool LoadProgram(const std::string& vertexShader, const std::string& pixelShader) = 0;
	/// �������� �� ������������������� ����. ������������ ������ ��� �������. �� �������������� OpenGL.
	/// ��������� �������� 0 ������ ������ �� ��������.
	virtual bool LoadProgram(const unsigned int* vertexFunc, const unsigned int* vertexDecl, const unsigned int* pixelFunc) = 0;
	virtual ~ShaderProgram() {}; 

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	/// ��������� �������� ��� �������. �������� location ���������� ���������.
	virtual void setUniform(float, intconst std::string& location);
	virtual void setUniform(int , const std::string& location);
	virtual void setUniform(const math::Vector4&, const std::string& location);
	virtual void setUniform(const math::Vector3&, const std::string& location);
	virtual void setUniform(const math::Matrix4&, const std::string& location);
};


#ifdef ENGINE_TARGET_WIN32

class ShaderProgramDX :public ShaderProgram {
public:
	/// ��� �������� �������������� ����������� ��� DirectX. �� ����� ������������ ������ � RenderDevice.
};

///
/// ������� ����� ���� ��������.
///
class Shader {
public:
	typedef boost::shared_ptr<Shader> HardPtr;
	
	typedef boost::weak_ptr<Shader> WeakPtr;

	virtual ~Shader() {}
	
	/// ��������� ������ � ����������� ����������
	virtual void Upload() = 0;
	
	/// ��������� ������ � ����������� �����������
	virtual void Bind() = 0;
	
	/// ������������� �������� ��������� �������.
	/// ����������� ������ ��������� - float4, ������ ����������� � ������������ ��������.
	virtual void SetConstant(int baseReg, void* value, int count) = 0;
	
	/// ���������� ������ �� ������������ ����������
	virtual void Unbind() = 0;
	
	/// ������������� Vector4 � �������� ���������
	void SetVector4(int baseReg, const math::Vector4& v);
	
	/// ������������� Matrix4 � �������� ���������
	void SetMatrix4(int baseReg, const math::Matrix4& m);

protected:
	Shader(const unsigned int* func) : _function(func) { }

protected:
	const unsigned int* _function;

private:
	Shader(const Shader&);
	Shader& operator = (const Shader&);
		// ����������� ����� � �������� ������������ �� ����������
};

inline void Shader::SetVector4(int baseReg, const math::Vector4& v) {
	SetConstant(baseReg, (void*)v.v, 1);
}

inline void Shader::SetMatrix4(int baseReg, const math::Matrix4& m) {
	SetConstant(baseReg, (void*)m.v, 4);
}


///
/// ���������� ������.
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
/// ��������� ������.
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
	/// ��� �������� �������������� ����������� OpenGL. �� ����� ������������ ������ � RenderDevice.
};

#endif


} // namespace Render

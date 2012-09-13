#ifndef _RENDER_SHADERPROGRAMDX9_H_
#define _RENDER_SHADERPROGRAMDX9_H_

#include "ShaderProgram.h"
#include <d3d9.h>

namespace Render {

class RenderDeviceImpl;

/// ����� ��� ���������� ���������� � ����������� ���������.
class ShaderProgramDX9 : public ShaderProgram {
public:
	ShaderProgramDX9(rapidxml::xml_node<>* elem);
	
	~ShaderProgramDX9();
	
	/// �������� ���� �������� �� ������. �������� ������� ������ ������ ������ ������ �� ��������.
	bool Load(const std::string& filenameVS, const std::string& filenamePS);
	
	/// �������� �������� � ����������
	void Upload();
	
	/// �������� �������� �� ����������
	void Release();

	/// ���������� �������� � �����������
	void Bind();
	
	/// ����������� �������� �� ����������
	void Unbind();
	
	/// ��������� �������� ��� ���������� �������
	void setVSParam(const std::string& name, const float* fv, int size);

	/// ������� �� ������ �������� � ���������� �������
	virtual bool hasVSParam(const std::string& name);
	
	/// ��������� �������� ��� ����������� �������
	void setPSParam(const std::string& name, const float* fv, int size);

	/// ������� �� ������ �������� � ����������� �������
	virtual bool hasPSParam(const std::string& name);

private:
	friend class RenderDeviceImpl;
	
	IDirect3DVertexShader9* _vs;
	
	IDirect3DPixelShader9* _ps;
	
	std::vector<DWORD> _vsFunc;
	
	std::vector<DWORD> _psFunc;
	
	typedef std::map<std::string, int> RegisterMap;
	
	RegisterMap _vsRegisters;
	
	RegisterMap _psRegisters;
};

} // namespace Render

#endif // _RENDER_SHADERPROGRAMDX9_H_

#ifndef _RENDER_SHADERPROGRAMDX8_H_
#define _RENDER_SHADERPROGRAMDX8_H_

#include "ShaderProgram.h"

namespace Render {

class RenderDeviceImpl;

/// Класс для управления вершинными и пиксельными шейдерами.
class ShaderProgramDX8 : public ShaderProgram {
public:
	ShaderProgramDX8(rapidxml::xml_node<>* elem);
	
	~ShaderProgramDX8();
	
	/// Создание пары шейдеров из файлов. Возможно задание пустой строки вместо одного из шейдеров.
	bool Load(const std::string& filenameVS, const std::string& filenamePS);
	
	/// Загрузка шейдеров в устройство
	void Upload();
	
	/// Выгрузка шейдеров из устройства
	void Release();

	/// Связывание шейдеров с устройством
	void Bind();
	
	/// Отвязывание шейдеров от устройства
	void Unbind();
	
	/// Установка констант для вершинного шейдера
	void setVSParam(const std::string& name, const float* fv, int size);

	/// Имеется ли данный параметр у вершинного шейдера
	virtual bool hasVSParam(const std::string& name);
	
	/// Установка констант для пиксельного шейдера
	void setPSParam(const std::string& name, const float* fv, int size);

	/// Имеется ли данный параметр у пиксельного шейдера
	virtual bool hasPSParam(const std::string& name);

private:
	friend class RenderDeviceImpl;
	
	DWORD _vs;
	
	DWORD _ps;
	
	const DWORD* _vertexDecl;
	
	std::vector<DWORD> _vsFunc;
	
	std::vector<DWORD> _psFunc;
	
	typedef std::map<std::string, int> RegisterMap;
	
	RegisterMap _vsRegisters;
	
	RegisterMap _psRegisters;
};

} // namespace Render

#endif // _RENDER_SHADERPROGRAMDX8_H_

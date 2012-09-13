#pragma once

#include "Utils/IPoint.h"
#include "Render/VertexBuffer.h"
// Назначение: описывает поведение "искажающей сетки"

enum RefPoint
{
	REF_NODE,
	REF_CENTER,
	REF_TOPLEFT
};


class Distortion
{
	VertexBufferIndexed				_drawBuffer;

	// Размер сетки
	int								_nRows,_nCols;
	// Размер ячейки
	float							_cellw,_cellh;
	IRect							_rect;
	float							_uStart,_uEnd,_vStart,_vEnd;
	// аплоад каждый ход
	bool							_upload;

	Distortion();
public:
	Distortion(int cols, int rows, bool upload = true);
	Distortion(const Distortion& dist);
	Distortion(int cols, int rows, std::vector<int> &invis, bool upload = true);
	~Distortion();
	void							Upload();
	void							Draw();
	void							DrawGrid();
	void							SetRenderRect(const IRect& rect, float uStart = 0.0f, float uEnd = 1.0f, float vStart = 0.0f, float vEnd = 1.0f);
	void							SetRenderRect(const IRect& rect, const FRect &uv);
	const IRect&					GetRenderRect() const { return _rect; }
	FRect							GetTextureRect() const { return FRect(_uStart, _uEnd, _vStart, _vEnd); }
	void							SetDisplacement(int col, int row, float dx, float dy,RefPoint ref);
	void							SetColor(int col, int row, DWORD color);
	void							SetColor(DWORD color);
	void							Clear(DWORD color);	
	int								getColsCount() const {return _nCols;}
	int								getRowsCount() const {return _nRows;}
	void							SetTextureCoord(int col, int row, float u, float v);
	float getCellWidth() { return _cellw; }
	float getCellHeight() { return _cellh; }
};

#pragma once

#include "Render/Texture.h"

namespace Render {

	class Sheet;

	/// ������ �������� ����������� �� ������� ����� ������ ��������.

	/// ��� ��������������, ������� �� ������ � ���� �����������, � ������������ ����� ������������� Sheet'�. ��������� � ��������������� image � ���� ��� ����� �����������, ��� ������ ��� ���.
	/// ����� �������� �������� ���������������� ����� ��������, � ��� �� ����� ������������
	/// RenderDeviceImpl::TranslateUV.
	class PartialTexture: public Texture 
	{
		friend class Render::Sheet;

	protected:
		/// �������� � ������������
		Texture* texture;
		/// ���������� ����������� � ��������
		int baseX, baseY, width, height, innerX, innerY, frameWidth, frameHeight;
		/// ��������� ��� �������� ����� ������ �� Sheet::GetTexture.
		PartialTexture(Texture* _t, int _x, int _y, int _w, int _h, int _ix, int _iy, int _fw, int _fh);

	public:
		virtual ~PartialTexture();

		/// ��������� ����� �� ���������������� ���������� ����������. ���� ��, �� ���������� ������� TranslateUV ����� ����������.
		virtual bool needTranslate();
		/// ������������� ���������� ���������. ���������� � RenderDeviceImpl ���� needTranslate ���������� true.
		virtual void TranslateUV(FPoint &uv);
		/// ������������� ���������� ���������. ���������� � RenderDeviceImpl ���� needTranslate ���������� true.
		virtual void TranslateUV(FRect &rect, FRect &uv);

		/// ��������� ��������
		virtual void Upload(bool bCleanAfterUpload = true);
		/// ��������� ��������
		virtual void Bind(int channel = 0, int stageOp = 0);
		/// ��������� �����-����� ��������
		virtual void BindAlpha();
		/// ��������� ��������
		virtual void Release();

		virtual void LoadFromFile(const string& filename);
		virtual void LoadFromImage(const Image& image_);
		virtual void GetPropertiesFromFile(const string& filename);
		/// ��������� �������� � �������� �������, ���� �������� ��� �� ���������, ��� ��������
		virtual void Draw(const IPoint& position);
		/// ��������� �������� � �������� �������, ���� �������� ��� �� ���������, ��� ��������
		virtual void Draw(const IPoint& position, const IRect& rect);
		/// ��������� �������� � �������� ������� � ���������, ���� �������� ��� �� ���������, ��� ��������
		virtual void Draw(const IPoint& position, const RectOrient orient);
		/// ��������� �������� � �������� ������� � ���������, ���� �������� ��� �� ���������, ��� ��������
		virtual void Draw(const IRect& rect, float xStart, float xEnd, float yStart, float yEnd);
		/// ��������� �������� � �������� �������, ���� �������� ��� �� ���������, ��� ��������
		virtual void Draw(const IRect& rect, const FRect& uv);
		/// ��������� �������� � �������� �������, ���� �������� ��� �� ���������, ��� ��������
		virtual void Draw(float x, float y, float width, float height, const FRect& uv);
		/// ��������� �������� � �������� ������� � �����������, ���� �������� ��� �� ���������, ��� ��������
		virtual void DrawCut(const IPoint& position, float cut_factor_x, float cut_factor_y = 1.0f);
		
		/// ��������� �������� � �������� �������, ���� �������� ��� �� ���������, ��� ��������
		virtual void Draw(const FPoint& position);
		/// ��������� �������� � �������� ������� � ���������, ���� �������� ��� �� ���������, ��� ��������
		virtual void Draw(const FPoint& position, const RectOrient orient);
		/// ��������� �������� � �������� ������� � �����������, ���� �������� ��� �� ���������, ��� ��������
		virtual void DrawCut(const FPoint& position, float cut_factor_x, float cut_factor_y = 1.0f);
		
		virtual bool isPixelTransparent(int x, int y);
		virtual bool isPixelOpaque(int x, int y);
	};

}

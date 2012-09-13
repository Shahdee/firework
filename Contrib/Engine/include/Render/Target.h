#pragma once

#if defined(ENGINE_TARGET_WIN32_DX9)
#include "d3d9.h"
#elif defined(ENGINE_TARGET_WIN32_DX8)
#include "d3d8.h"
#endif
#include "Render/Texture.h"

namespace Render {

	enum CompareOp
	{
		CMP_EQ,
		CMP_NE,
		CMP_LT,
		CMP_LE,
		CMP_GT,
		CMP_GE,
		CMP_FALSE,
		CMP_TRUE
	};
//
// ������, ������� ���� ������� ��������,
// � ������� ����� ���-�� ��������.
//
// � public �������� ������ �� ������, ������� ����� ������� ������������
// ��� ���������, � ��� ����� � �����������, � private.
// ����� �������, ��������� ������� � ����� ������ ������ � ��� ����� ������
// ��������� ������ Render::RenderDeviceImpl.
//
// �����������:
// 1) ��� ��� ������ ������ ������� Render::RenderDeviceImpl::CreateRenderTarget,
//    ������ ����� ������� ��� ������� Render::RenderDeviceImpl::DeleteRenderTarget;
// 2) ��� ���� ��������� � Render::Target ����� ���������, ������� �� ��
//    �������� IsValid(); ������ ������ ���������� ����� ��������� ����������;
// 3) ��������� � �������� ����� ������ � Update, �� �� � Draw.
//
// ���, ��������� RenderTarget ������ ��������� �������� ���:
// 
// RenderTarget* _renderTarget;
// ...
// if (_renderTarget != NULL && !_renderTarget->IsValid()) {
//    Render::device.DeleteRenderTarget(_renderTarget);
//	  _renderTarget = NULL;
// }
// if (_renderTarget == NULL) {
//    _renderTarget = Render::device.CreateRenderTarget(_texture->getBitmapRect().width, _texture->getBitmapRect().height);
//    Render::device.BeginRenderTo(_renderTarget);
//    ... // ����� ������ ���-������
//    Render::device.EndRenderTo();
// }
//
// �� ���� �� _�������_ ������� ������ ����� ����, ��� �� ��� �� �����.
// �������� ��������, ��� ���� ��� ������ ���� � Update, �� �� � Draw.
//
class Target
{

public:

	bool needTranslate() const;
	
	void TranslateUV(FPoint& uv) const;
	
	void TranslateUV(FRect& rect, FRect& uv) const;
	
	IRect getRenderRect() const { return IRect(0, 0, _widthPow2, _heightPow2); }
	
	IRect getBitmapRect() const { return IRect(0, 0, _width, _height); }

	//
	// ��������� ������� ���������
	//
	void Bind(int cannel = 0, int stageOp = 0);

	//
	// ��������� ������� ��������� ��� �����-���������
	//
	void BindAlpha();

	//
	// ��������� ��������
	//
	void Draw(const FPoint& position);

	//
	// ������� �� ������
	//
	bool IsValid();

	/// ������ �� ������.
	/// ������ ������ ���� �������� ������, �� ��� ���������� ���� ������� � ���������� ������ ����������
	bool Empty();

	//
	// ��������� � ������� BMP
	// �����������: �������������� �������� �� ���������
	//
	void SaveAsBmp(const std::string & path);

	//
	// ��������� � ������� PNG
	// �����������: �������������� �������� �� ���������
	//
	void SaveAsPng(const std::string & path);
	
	//
	// ��������� � ������� JPEG
	//
	void SaveAsJpeg(const std::string & path, int quality = 80);

	//
	// ����������
	//
	virtual ~Target();

	//
	// �������� ���������� ������� � ������������ �� ������������� (� ���� ������ ���������� false)
	// ������� ��������� ����� ������ ��������� ��� �������� (��. �.2 � ������������ ����)
	// 
	static bool EnsureValidity(Target** t);

	//
	// �������� ������� ������-������� � ��������� ��������������.
	// region -- ���������� �������,
	// cmp_op_rgba -- �������� ��� ��������� ��������� ����� � ���������� ���������� (� ������� RGBA),
	// cmp_ref_value -- ��������� �������� ��������� �����,
	// value -- ����� �������� ��������� �����,
	// value_mask -- ����� ��� ������ ����������, ����������, ����� ���� ���� ������
	//
	bool UpdateContents(const IRect& region, 
								const CompareOp cmp_op_rgba[], const Color& cmp_ref_value,
								const Color& value, const Color& value_mask);

	//
	// ��������� ���������� �������
	//
	void setFilter(Texture::FilteringType filter);

	//
	// ��������� ��������� ���������� ��������� �������
	//
	void setAdress(Texture::AdressType adress);

private:

	friend class RenderDeviceImpl;
	friend class RenderDeviceGLES1;
	friend class RenderDeviceGLES2;
		// ����� ������ ��� ����� ���� ��������� ������� ������ ����

	DEVTEXTURE _texture;	
		// ��������

#if defined(ENGINE_TARGET_WIN32_DX9)
	IDirect3DSurface9* _renderTargetSurface;
		// �����������
	
	IDirect3DSurface9* _depthStencilSuface;
		// Z-�����
#elif defined(ENGINE_TARGET_WIN32_DX8)
	IDirect3DSurface8* _renderTargetSurface;
		// �����������
	
	IDirect3DSurface8* _depthStencilSuface;
		// Z-�����
#endif
	
	bool _valid;
		// ������� �� ���� ���������� (���������� ����������, ���� ���������� ����������������������)
	/// ����� �� ���� ����������
	bool _empty;

	bool _isBinded;
		// ��������� �� ���� ����������

	int _width;
		// ������ ��������

	int _height;
		// ������ ��������
	
	int _widthPow2;
		// ������ ��������, ���������� �� ��������� ������� ������� ������
	
	int _heightPow2;
		// ������ ��������, ���������� �� ��������� ������� ������� ������

	int texWidth, texHeight; // ������ ������, ���������� ��� �������� ��� �������

	bool _alpha;
		// ����� �� �����-����� ����?

	Texture::FilteringType _filter;
		// ��� ����������

	Texture::AdressType _adress;
		// ��� ��������� ���������� ���������

	//
	// ����������� ����� ��� ���� ����� RenderDeviceImpl
	//
	Target(int width, int height);

	//
	// �������� �������, �������� ������� ������
	//
	void ReleaseResources();

	//
	// �������� ��� ������� � ������ ���� ����������.
	//
	void SetInvalid();
	
#if defined(ENGINE_TARGET_WIN32_DX8) || defined(ENGINE_TARGET_WIN32_DX9)
	//
	// ��������� ���������� � Image::image_pool
	//
	bool CopyToImagePool();
#endif
};

} // namespace Render

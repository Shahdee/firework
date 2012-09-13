#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "ColorValue.h"
#include "Render/Texture.h"

namespace SceneGraph {

///
/// Материал.
///
class Material {
public:
	typedef boost::shared_ptr<Material> HardPtr;
	
	typedef boost::weak_ptr<Material> WeakPtr;
	
	typedef boost::shared_ptr<Render::Texture> TexturePtr;
	
	Material();
	
	//Material(const Material&);
	//Material& operator = (const Material&);
		// Конструктор копий и оператор присваивания подойдут те,
		// которые по умолчанию создаст компилятор.
	
	virtual ~Material();
	
	virtual Material::HardPtr Clone();
	
	static Material::HardPtr DefaultMaterial();
		/// Возвращает материал по умолчанию
	
	const ColorValue& GetAmbientColor() const;
		/// Возвращает значение окружающего цвета
	
	void SetAmbientColor(const ColorValue& color);
		/// Устанавливает значение окружающего цвета
	
	const ColorValue& GetDiffuseColor() const;
		/// Возвращает значение рассеиваемого цвета
	
	void SetDiffuseColor(const ColorValue& color);
		/// Устанавливает значение рассеиваемого цвета
	
	const ColorValue& GetSpecularColor() const;
		/// Возвращает значение отражаемого цвета
	
	void SetSpecularColor(const ColorValue& color);
		/// Устанавливает значение отражаемого цвета
	
	const ColorValue& GetEmissiveColor() const;
		/// Возвращает значение испускаемого цвета
	
	void SetEmissiveColor(const ColorValue& color);
		/// Устанавливает значение испускаемого цвета
	
	float GetPower() const;
		/// Возвращает экспоненту отражаемого цвета
	
	void SetPower(float power);
		/// Устанавливает экспоненту отражаемого цвета
	
	TexturePtr GetDiffuseTexture() const;
		/// Возвращает объект текстуры
	
	void SetDiffuseTexture(TexturePtr texture);
		/// Устанавливает объект текстуры
	
private:
	ColorValue _ambient;
		/// Значение окружающего цвета
	
	ColorValue _diffuse;
		/// Значение рассеиваемого цвета
	
	ColorValue _specular;
		/// Значение отражаемого цвета
	
	ColorValue _emissive;
		/// Значение испускаемого цвета
	
	float _power;
		/// Значение экспоненты отражаемого цвета
	
	TexturePtr _diffuseTexture;
		/// Текстура
};

} // namespace SceneGraph

#endif // __MATERIAL_H__

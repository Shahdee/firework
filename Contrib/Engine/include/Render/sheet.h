#pragma once

#include "Render/Texture.h"
#ifdef ENGINE_TARGET_IPHONE
#include <strings.h>
#endif

namespace Render {

	/// Класс упакованного набора текстур
	/// Это класс "простыни" - большой, склееной из нескольких текстур.
	/// В классе хранятся координаты исходных тестур, и существует генерация псевдотекстур,
	/// которые могут отрисовываться из исходной простыни
	class Sheet {

	private:
		
		typedef std::vector<Texture*> TexturesVector;
		TexturesVector _cachedTexturesVector;
			// вектор закэшированных текстур
	
	protected:
		
		/// описание элемента на простынке
		typedef struct SheetItem {
			int x, y, width, height, innerX, innerY, frameWidth, frameHeight;
		} SheetItem;
		
		/// функтор для сравнения строк без учёта регистра
		struct less_string_ci : public std::binary_function<std::string, std::string, bool> {
			bool operator()(const std::string& left, const std::string& right) const {
				int (*compare)(const char* s1, const char* s2);
#ifdef ENGINE_TARGET_IPHONEOS
				// в айфоне регистрозависимая файловая система
				compare = &strcmp;
#else

#	ifdef ENGINE_TARGET_WIN32
				compare = &_stricmp;
#	else
				compare = &strcasecmp;
#	endif

#endif
				return compare(left.c_str(), right.c_str()) < 0;
			}
		};

		typedef std::map<std::string, SheetItem, less_string_ci> SheetItems;

		SheetItems items;
		
		/// текстура простыни
		Texture* tex;
		
		/// файл с текстурой
		std::string path;
		
		/// идентификатор
		std::string id;
		
		/// загрузили ли уже текстуру
		bool loaded;
		
		/// конструктор закрытый, ибо создавать объект только через getFromXml.
		Sheet();
		
		/// прочитать xml файл, описывающий содержащиеся в нём текстуры
		void ProcessXml(const std::string& xmlFile);
		
	public:
		
		~Sheet();
		
		/// генерация простыни из xml
		static Sheet* getFromXml(rapidxml::xml_node<>* elem, const std::string& upperGroup);
		
		/// ручная загрузка простыни
		static Sheet* LoadSheet(const std::string& xml, const std::string& file, const std::string& group = "", bool allowCompress = false, bool biteMask = true, PixelType pixelType = PIXEL_TYPE_DEFAULT);
		
		/// проверка на существование текстуры с заданным названием файла
		/// предполагается, что проверка на совпадение группы выполняется до, вызывающей стороной
		/// (название файла должно совпадать полностью, т.е. с путём)
		bool CheckTexture(const std::string& file);
		
		/// Генерация псевдотекстуры по заданному файлу. До вызова должна быть произведена проверка
		/// наличия такой текстуры (см. CheckTexture). Если такой текстуры нет, возвращается NULL.
		/// В результате создаётся новый экземпляр Render::PartialTexture,
		/// его _нужно удалять самостоятельно_.
		Texture* CreateTexture(const std::string& file);
		
		Texture* GetTexture(const std::string& file) {
			return CreateTexture(file);
		}
		
		/// Генерация псевдотекстуры по заданному номеру.
		/// Если текстуры с таким номером нет (номер больше либо равен GetSize()), возвращается NULL.
		/// В результате создаётся новый экземпляр Render::PartialTexture,
		/// его _нужно удалять самостоятельно_.
		Texture* CreateTexture(uint i);
		
		Texture* GetTexture(uint i) {
			return CreateTexture(i);
		}
		
		/// Аналогично предыдущей функции, только _удалять текстуру не нужно_
		Texture* GetCachedTexture(uint i);
		
		/// Возвращает количество текстур, упакованных в простыню.
		uint GetSize();
		
		/// Возвращает идентификатор 
		std::string GetId();
		
	};
}

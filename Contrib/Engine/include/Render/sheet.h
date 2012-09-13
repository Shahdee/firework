#pragma once

#include "Render/Texture.h"
#ifdef ENGINE_TARGET_IPHONE
#include <strings.h>
#endif

namespace Render {

	/// ����� ������������ ������ �������
	/// ��� ����� "��������" - �������, �������� �� ���������� �������.
	/// � ������ �������� ���������� �������� ������, � ���������� ��������� �������������,
	/// ������� ����� �������������� �� �������� ��������
	class Sheet {

	private:
		
		typedef std::vector<Texture*> TexturesVector;
		TexturesVector _cachedTexturesVector;
			// ������ �������������� �������
	
	protected:
		
		/// �������� �������� �� ���������
		typedef struct SheetItem {
			int x, y, width, height, innerX, innerY, frameWidth, frameHeight;
		} SheetItem;
		
		/// ������� ��� ��������� ����� ��� ����� ��������
		struct less_string_ci : public std::binary_function<std::string, std::string, bool> {
			bool operator()(const std::string& left, const std::string& right) const {
				int (*compare)(const char* s1, const char* s2);
#ifdef ENGINE_TARGET_IPHONEOS
				// � ������ ����������������� �������� �������
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
		
		/// �������� ��������
		Texture* tex;
		
		/// ���� � ���������
		std::string path;
		
		/// �������������
		std::string id;
		
		/// ��������� �� ��� ��������
		bool loaded;
		
		/// ����������� ��������, ��� ��������� ������ ������ ����� getFromXml.
		Sheet();
		
		/// ��������� xml ����, ����������� ������������ � �� ��������
		void ProcessXml(const std::string& xmlFile);
		
	public:
		
		~Sheet();
		
		/// ��������� �������� �� xml
		static Sheet* getFromXml(rapidxml::xml_node<>* elem, const std::string& upperGroup);
		
		/// ������ �������� ��������
		static Sheet* LoadSheet(const std::string& xml, const std::string& file, const std::string& group = "", bool allowCompress = false, bool biteMask = true, PixelType pixelType = PIXEL_TYPE_DEFAULT);
		
		/// �������� �� ������������� �������� � �������� ��������� �����
		/// ��������������, ��� �������� �� ���������� ������ ����������� ��, ���������� ��������
		/// (�������� ����� ������ ��������� ���������, �.�. � ����)
		bool CheckTexture(const std::string& file);
		
		/// ��������� �������������� �� ��������� �����. �� ������ ������ ���� ����������� ��������
		/// ������� ����� �������� (��. CheckTexture). ���� ����� �������� ���, ������������ NULL.
		/// � ���������� �������� ����� ��������� Render::PartialTexture,
		/// ��� _����� ������� ��������������_.
		Texture* CreateTexture(const std::string& file);
		
		Texture* GetTexture(const std::string& file) {
			return CreateTexture(file);
		}
		
		/// ��������� �������������� �� ��������� ������.
		/// ���� �������� � ����� ������� ��� (����� ������ ���� ����� GetSize()), ������������ NULL.
		/// � ���������� �������� ����� ��������� Render::PartialTexture,
		/// ��� _����� ������� ��������������_.
		Texture* CreateTexture(uint i);
		
		Texture* GetTexture(uint i) {
			return CreateTexture(i);
		}
		
		/// ���������� ���������� �������, ������ _������� �������� �� �����_
		Texture* GetCachedTexture(uint i);
		
		/// ���������� ���������� �������, ����������� � ��������.
		uint GetSize();
		
		/// ���������� ������������� 
		std::string GetId();
		
	};
}

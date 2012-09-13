#pragma once

//
// ����������� �����, ���������� ������� ������ �� ���������� ���� bool
// � ��������� ������� �������� � ��������� ������������� � �������
//
class Bool
{
public:

	//
	// ������ �������� ���� bool �� ������
	//
	static bool Parse(const std::string& image) {
		if (image == "true") {
			return true;
		} else if (image == "false") {
			return false;
		} else {
			assert(false); // ����������� ����������� �������� ���� bool
			return false;
		}
	}

	//
	// ������ 0 ��� 1 �� ������, ������ false ��� true ��������������
	//
	static bool Parse01(const std::string& image) {
		if (image == "0") {
			return false;
		} else if (image == "1") {
			return true;
		} else {
			assert(false); // ����������� ��������
			return false;
		}
	}

	//
	// ��������� ������ � ������������ �������� ���� bool
	//
	static std::string ToString(bool value) {
		if (value) {
			return "true";
		} else {
			return "false";
		}
	}
};
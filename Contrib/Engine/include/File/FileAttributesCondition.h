#pragma once

#ifndef ENGINE_TARGET_WIN32
#	define FILE_ATTRIBUTE_DIRECTORY 10
#	define FILE_ATTRIBUTE_HIDDEN 2
#endif

namespace File {
/// ������� �� �������� ������. ������������, ������,
/// ����� �� ������� �������� ������� ����� � �����������.
/// ������ ��� �������� FILE_ATTRIBUTE_DIRECTORY � �.�.
class FileAttributesCondition
{
private:

	/// � ������� ����������� ���� �������������� ���������.
	int _and;

	/// �������� �����, ��������������� ��������� ����� _and,
	/// ����������, ����� �������� ��������� �����.
	/// ��������� ���� �������.
	int _eq;

	/// �������� ������� �� �������� � ��������� ����������� _and � _eq.
	FileAttributesCondition(int _and, int _eq);

public:

	/// �������� �� ������������ ������� �� ��������.
	FileAttributesCondition();

	/// ��������, ��� �������� ������������� �������, ��������� ���� �����������.
	bool IsGood(int attributes);

	/// ���������� ������� "������ ��������".
	FileAttributesCondition DirectoriesOnly();

	/// ���������� ������� "��� ���������".
	FileAttributesCondition NoDirectories();

	/// ���������� ������� "������ �������".
	FileAttributesCondition HiddenOnly();

	/// ���������� ������� "������ �� �������".
	FileAttributesCondition NoHidden();

};
}

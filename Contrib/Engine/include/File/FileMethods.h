#pragma once

#include <string>

namespace File {

	/// �������� ������������� �����
	bool Exist(const std::string& filename);

	/// �������� ������������� ����� �� �������� �������
	bool ExistInFs(const std::string& filename);

	/// �������� ������������� ����� � ������
	bool ExistInPack(const std::string& filename);

	/// ���������� �������� ���������� �������. ���������� false ��� ������.
	bool cd(const std::string& dir);

	/// ���������� ����, ���� ���� ����������, �� �� �� ����������������, � ������������ false;
	bool cp(const std::string& src, const std::string& dst);

	/// ����������� �����, ���� ���� ����������, �� �� �� ����������������, � ������������ false;
	bool mv(const std::string& src, const std::string& dst);

	/// �������� �����.
	bool rm(const std::string& file);

	/// �������� ����������.
	void rmdirr(const std::string& path);

	/// ������� ����������
	void mkdir(const std::string& theDir);

	/// ������� ��� ����� �� ������� ����
	std::string fileName(const std::string &path);

	/// ������� ��� ������ �����
	std::string outputDirectory();

	/// ���������� ������� ����������
	std::string pwd();

	/// ������� "���������"
	std::string GetDocumentsPath();

	/// ������� "����� ������"
	std::string GetCommonAppDataPath();

	/// ������� "������ �����"
	std::string GetUserAppDataPath();
	
	/// �������� ����� ������� � ������, ���������� 0 ��� �������
	/// ����� � ������ ����� ����� ������� �����
	/// ����������� ������ ���� �� �������� �������, �� �� ������, 
	/// ��� ��� ������������ � �������������. ��. ExistInFs()
	char* LoadFile(const std::string& fname, long *filesize=0, int appendSize = 0);
	
}
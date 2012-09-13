#pragma once

///
/// ����� ��� ������ Zip �������.
///
/// � ������ ������ ������� ���������� std::runtime_error.
///
class ZipArchive {
public:
	ZipArchive();
	ZipArchive(const std::string& filename);
	
	virtual ~ZipArchive();
	
	void Open(const std::string& filename);
		/// ��������� �����. �������� ����� ����� ������������� �����������
	void Close();
		/// ��������� �����. ��� �� ���������� � �����������
	bool IsOpen() const;
		/// ���������, ������ �� �����
	
	void ListFiles(std::vector<std::string>& vec);
		/// ���������� ������ ���� ������, ������������ � ������
	bool FileExists(const std::string& filename);
		/// ���������, ���������� �� ���� � ������
	void ReadFile(const std::string& filename, std::vector<unsigned char>& data, int appendExtraZeros = 0);
		/// ������ ���������� ����� � �����. ��������� � ������ ��������� ���������� �����

private:	
	ZipArchive(const ZipArchive&);
	ZipArchive& operator=(const ZipArchive&);
		// ��������� ����������� ����������� ������

private:
	struct Impl;
	Impl* _pimpl;
		// ���������� ����������
};

#ifndef ENGINE_WRAPPER_INCLUDED
#define ENGINE_WRAPPER_INCLUDED

// �����, �������������� �� ���� Objective-C ��������� �
// ����� ������������ �������� ������
// (����� ����� �� ��������� Objective-C � C++ � ����� ������
// ���� �����������)
@interface EngineWrapper : NSObject {
	
}

//
// ������� ����� �� ������-���������
// ���������� GetSource(), �� ���� ������������������ �����
//
+(NSString*)getText:(const char*)idText;

@end

#endif

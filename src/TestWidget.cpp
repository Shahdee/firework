#include "stdafx.h"
#include "TestWidget.h"

TestWidget::TestWidget(const std::string& name_)
	: Widget(name_) 
{
	Init();
}

TestWidget::TestWidget(const string& name_, Xml::TiXmlElement* xmlElement) 
	: Widget(name_)
	, _curTex(0)
	, _smoothTex(NULL)
	, _timer(0)
	, _timeScale(1)
	, _angle(0)
	, _eff(NULL)
{
	Init();
}

void TestWidget::Init()
{
	_textures.push_back(Core::resourceManager.getTexture("btnStart_Text"));
	_textures.push_back(Core::resourceManager.getTexture("Circle"));
	_smoothTex = new SmoothTextureChanger(_textures[0]);
	_curTex = 0;
	_angle = 0;
}

TestWidget::~TestWidget()
{
}

void TestWidget::Draw() 
{
	IPoint mouse_pos = Core::mainInput.GetMousePos();

	// ��������� �������������� �������� � ����, ������� ����������� ����� ����� �����
	Render::device.PushMatrix();
	Render::device.MatrixTranslate(math::Vector3(mouse_pos.x + 0.f, mouse_pos.y + 0.f, 0));	// - 3�� ��������. ����� �������� ���������� (� ���� ����� ����� ������ �����, ������������ ������� ������������)
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);				// - 2�� ��������. ������������.
	_smoothTex->Draw(IPoint(-50, -50));											// - 1�� ��������. ����� �����, ������������ ������� ����� ������� (��������� � ������� ���������)
	Render::device.PopMatrix();

    Render::device.SetTexturing(false);
	Render::device.SetCurrentColor(Color(255,128,0,255));
	Render::DrawRect(700, 0, 100, 100);
	Render::device.SetTexturing(true);

	// ������������ ��� �������, ������� �������� � ��������� (Update ��� ���������� �������� �� �����)
	_effCont.Draw();

	Render::BindFont("arial");
	Render::PrintString(720, 20, utils::lexical_cast(mouse_pos.x) + " " + utils::lexical_cast(mouse_pos.y));

}

void TestWidget::Update(float dt)
{
	_smoothTex->Update(dt);
}

void TestWidget::MouseDoubleClick(const IPoint &mouse_pos)
{
	MouseDown(mouse_pos);
}

bool TestWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseRightButton())
	{
		// ������ ����� �� ������ �� �����
		_eff = _effCont.AddEffect("Iskra");
		_eff->posX = mouse_pos.x + 0.f;
		_eff->posY = mouse_pos.y + 0.f;
		_eff->Reset();
		_angle += 25;
	}
	else
	{
		// ������ ����������� ��������������, �� ���� �� ��� ������� � ��������� ���������� � ������
		ParticleEffect *eff = _effCont.AddEffect("FindItem2");
		eff->posX = mouse_pos.x + 0.f;
		eff->posY = mouse_pos.y + 0.f;
		eff->Reset();

		_curTex++;
		if (_curTex >= (int)_textures.size())
		{
			_curTex = 0;
		}
		_smoothTex->SetTexture(_textures[_curTex]);
	}
	return false;	
}

void TestWidget::MouseMove(const IPoint &mouse_pos)
{
	if (_eff)
	{
		// ���� ������ ������, �� ������� ��� ����� �� ������
		_eff->posX = mouse_pos.x + 0.f;
		_eff->posY = mouse_pos.y + 0.f;
	}
}

void TestWidget::MouseUp(const IPoint &mouse_pos)
{
	if (_eff)
	{
		// ���� ������ ������, �� ��� ���������� ���� ��������� ���.
		_eff->Finish();
		_eff = NULL;
	}
}

void TestWidget::AcceptMessage(const Message& message)
{
	if (message.getPublisher() == "KeyPress") 
	{
		int code = utils::lexical_cast<int>(message.getData());
		if (code < 0) return;
		if (code == 'a') 
		{		
		}
	}
}

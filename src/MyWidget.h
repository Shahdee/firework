#pragma once


class Firework
{
friend class MyWidget;
private:
	FPoint _pos;
	FPoint _velocity;
	ParticleEffect *_eff;
	bool _isAlive;
	bool _isAccesable;
	Firework(int,ParticleEffect*);
public:
	void CreateOne();
	void UpdatePosition(float,float,float);
	void DestroyOne();
};

class MyWidget: public GUI::Widget
{
private:
	void Init();
	int _level; // ������� �����������
	float _lifeTime;
	float _children; // ����� �������� �� �����
	float _currLevel;
	float _currAge;
	float _gravity;
	float _factor;
	float _alpha;
    std::list<Firework*> _forest; // ������ � �����������
	bool _isCreated;
	bool _wasLastGroup;
	bool _lastGroupWasDestroyed;
	EffectsContainer _effCont;
	EffectsContainer _deadContainer;

public:
	MyWidget(const std::string& name_);
	MyWidget(const std::string& name_, Xml::TiXmlElement* xmlElement);

	~MyWidget(void);
	virtual bool MouseDown(const IPoint &mouse_pos);
	virtual void Draw();
	virtual void Update(float dt);
	virtual void UpdateFirePosition(float);
	virtual void CreateFirework(); // ������� ����� ��������
	virtual void InitializeFireLevel(string name);
	virtual void ReadParamsFromFile(); 
	virtual bool TimeToExplodeLevel1();
	virtual void DeleteDead(); // ������� ������� �� ���� ����������
	virtual void DestroyAllFire(); // ���������� ���� ��������
	virtual void ResetFireworkVals(); // ������������� ��� ������������� ��������� ��������� �� �������
};

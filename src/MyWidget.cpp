#include "stdafx.h"
#include "MyWidget.h"
#include "math.h"

using namespace std;


Firework::Firework(int i, ParticleEffect* eff)
{
	_eff=eff;
	_isAlive=true;

	if(i==1)
	{
		_pos = Core::mainInput.GetMousePos();
		_eff->posX = _pos.x;
		_eff->posY = _pos.y;
		_velocity.x = -30 + (rand() / (float)RAND_MAX) * 40;
		_velocity.y = Core::appInstance->GAME_CONTENT_HEIGHT/4 + (rand() / (float)RAND_MAX) *(Core::appInstance->GAME_CONTENT_HEIGHT/3);
		_eff->Reset();
		_isAccesable=true;
	}
	else
	{
		_velocity.x = -50 + (rand() / (float)RAND_MAX) * 150;
		_velocity.y = -50 + (rand() / (float)RAND_MAX) * 150;
		_isAccesable=true;
	}

}


void Firework::UpdatePosition(float delta,float gravity, float factor)
{
	_velocity.x*=factor;
	_pos.x+=_velocity.x*delta;
	_pos.y+=_velocity.y*delta;
	_velocity.y-=gravity;
	_eff->posX =_pos.x;
	_eff->posY =_pos.y;
}

void Firework::DestroyOne()
{
	if(this)
	{
		delete this;
	}
}

MyWidget::MyWidget(const std::string& name_)
	:Widget(name_)
{
	Init();
	
}

MyWidget::MyWidget(const std::string &name_, Xml:: TiXmlElement *xmlElement)
	:Widget(name_)
	,_isCreated(false)
	,_wasLastGroup(false)
	,_level(3)
	,_lifeTime(2.5)
	,_children(5)
	,_currLevel(1)
	,_currAge(0)
	,_gravity(0.05)
	,_factor(1.0)
	,_alpha(1.0)
{
	Init();
	ReadParamsFromFile();
}



void MyWidget::CreateFirework()
{
	_isCreated = true;
	_lastGroupWasDestroyed = false;
	ParticleEffect *eff = _effCont.AddEffect("Tail");
	_forest.push_front(new Firework(1,eff));
}


MyWidget::~MyWidget(void)
{

}

void MyWidget::Init()
{
	
}

void MyWidget::Draw()
{
	if(_isCreated || _wasLastGroup)
	{
		_effCont.Draw();
	}
}

void MyWidget::DeleteDead() // удаляем взорвавшиеся фейрверки
{
	std::list<Firework*>::iterator el=_forest.begin();
	while(_forest.size()!=0 && !((*el)->_isAlive))
	{
		_forest.front()->_eff->Finish();
		_forest.front()->_eff=NULL;
		_forest.front()->DestroyOne();
		_forest.pop_front();
		el=_forest.begin();
	}
}


void MyWidget::DestroyAllFire()
{
	_forest.clear();
}

void MyWidget::ResetFireworkVals()
{
	_isCreated = false;
	_currLevel=1;
	_currAge=0;
	_lifeTime=2.5;
	_gravity=0.05;
	_alpha=1.0;
	_wasLastGroup = false;
}


void MyWidget::UpdateFirePosition(float dt) 
{
	std::list<Firework*>::iterator el=_forest.begin();
	while(el!=_forest.end())
	{
		if((*el)->_isAlive)
			(*el)->UpdatePosition(dt,_gravity, _factor);
		++el;
	}
}

bool MyWidget::TimeToExplodeLevel1()
{
	if((_forest.front()->_velocity.y<=0  ||  _forest.front()->_pos.y>=(Core::appInstance->GAME_CONTENT_HEIGHT*0.6)) && _currLevel==1) 
	{
		return true;
	}
	return false;
}


void MyWidget::Update(float dt)
{
	int  num=0;
	if(_isCreated)
	{	
		if(_lastGroupWasDestroyed)
		{
				_lastGroupWasDestroyed=false;
				DeleteDead();
				if(_wasLastGroup)
				{
					_isCreated=false;
					return;
				}
		}
		if(TimeToExplodeLevel1()) 
		{
			_currAge =_lifeTime;
		}
		if(_currAge<_lifeTime)
		{
			_currAge+=dt;
		}
		else
		{
			_currAge=0;
			_gravity=0.02;
			_factor=1;
			if(_lifeTime>0.2)
				_lifeTime-=0.002;
			else
				_lifeTime=2.0;
			_lastGroupWasDestroyed=true;
			int currLevelFireCounter=0;
			int currLevelFire = pow(_children,(_currLevel-1));
			list<Firework*>::iterator el=_forest.begin();
			ParticleEffect* eff;
			if(_currLevel>=_level)
			{
				_wasLastGroup=true;
			}
			while(el!=_forest.end() && currLevelFireCounter<currLevelFire) // группа которая будет уничтожена
			{
				(*el)->_isAlive=false;
				(*el)->_eff->Finish();

				 if(!_wasLastGroup)
				 {
					for(int i=0; i<_children; i++)
					{
						ParticleEffect* eff =_effCont.AddEffect("Tail");
						_forest.push_back(new Firework(0,eff));
						_forest.back()->_pos = (*el)->_pos;
						_forest.back()->_eff->posX = (*el)->_pos.x;
						_forest.back()->_eff->posY = (*el)->_pos.y;
						_forest.back()->_eff->Reset();
					}

					(*el)->_eff= _effCont.AddEffect("Exp");
					(*el)->_eff->posX = (*el)->_pos.x;
					(*el)->_eff->posY = (*el)->_pos.y;
					(*el)->_eff->Reset();
				}
				currLevelFireCounter++;
				++el;
			}
			_currLevel++;
		}
		UpdateFirePosition(dt);
	}
}

static bool IsNumber(char &z)
{
	string control="0123456789";
	for(int i=0; i<control.length(); i++)
	{
		if(z==control[i])
		{
			return true;
		}
	}
	return false;
}

void MyWidget::InitializeFireLevel(string name)
{
	bool first=true;
	bool second=false;
	string level="";
	string children="";
	int i=1;
	while(i<name.size())
	{
		 if(name[i-1]!='=')
			i++;
		 else
		 {
			 if(first)
			 {
				while(IsNumber(name[i]))
				{
					level.append(name.substr(i,1));
					i++;
				}
				first=false;
			 }
			 else
			 {
				while(IsNumber(name[i]))
				{
					children.append(name.substr(i,1));
					i++;
				}
				break;
			 }
			
		 }
	}

_level = utils::lexical_cast<int>(level); 
_children = utils::lexical_cast<int>(children); 
}

void MyWidget::ReadParamsFromFile()
{
	string fileName="../input.txt";
	string file;
	if(File::Exist(fileName))
	{
		file=File::LoadFile(fileName);
		InitializeFireLevel(file);
	}
	else
	{
		_level=3; 
		_children=2; 
	}
}

bool MyWidget::MouseDown(const IPoint &mouse_pos)
{
	DestroyAllFire();
	_effCont.KillAllEffects();
	ResetFireworkVals();

	if(Core::mainInput.GetMouseLeftButton() && !_isCreated) 
	{
		ReadParamsFromFile();
		CreateFirework();
	}
	return false;
}


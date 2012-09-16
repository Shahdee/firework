#include "stdafx.h"
#include "MyWidget.h"
#include "math.h"

using namespace std;


Firework::Firework(int i, ParticleEffect* eff)
{
	_eff=eff;
	_isAlive=true;
	_isAccesable=true;

	if(i==1)
	{
		_pos = Core::mainInput.GetMousePos();
		_eff->posX = _pos.x;
		_eff->posY = _pos.y;
		_angle = utils::random(math::PI/2.f - math::PI/6.f , math::PI/2.f + math::PI/6.f); 
		_velocity.x = 0;
		_velocity.y =  Core::appInstance->GAME_CONTENT_HEIGHT/4 + (rand() / (float)RAND_MAX) *(Core::appInstance->GAME_CONTENT_HEIGHT/3);
		_direction.x = math::cos(_angle);
		_direction.y = math::sin(_angle);
		_eff->Reset();
	}
	else
	{
		_angle = utils::random(0.f,1.f)*math::PI*2;
		float speed =utils::random(0.f,1.f)*200; 
		_velocity.x = math::cos(_angle)*speed;
		_velocity.y = math::sin(_angle)*speed;
		_direction.x = math::cos(_angle); 
		_direction.y = math::sin(_angle);
	}
}


void Firework::UpdatePosition(float delta,float gravity, float factor, float fuel, float level)
{
	_velocity.y-=gravity;
	_velocity+=_direction*fuel;
	if(level>1)
	{
		_angle = 0.02 * (utils::random(0.f,1.f) < 0.5 ? 1 : -1);
		_direction.x= math::cos(_angle) * _direction.x - math::sin(_angle) * _direction.y;
		_direction.y= math::sin(_angle) * _direction.y + math::cos(_angle) * _direction.y;
	}
	_pos.x+=_velocity.x*delta;
	_pos.y+=_velocity.y*delta;
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
	,_fuel(0.2)
	,_velocityCoeff(0.1)
{
	Init();
	ReadParamsFromFile();
}



void MyWidget::CreateFirework()
{
	if(_level!=1) // если наш фейрверк это нечто большее, чем 1 заряд
		_isCreated = true;
	_lastGroupWasDestroyed = false;
	ParticleEffect *eff = _effCont.AddEffect("Tail2");
	_forest.push_front(new Firework(1,eff));
}

MyWidget::~MyWidget(void){}

void MyWidget::Init(){}

void MyWidget::Draw()
{
	_effCont.Draw();
}

void MyWidget::DeleteDead() // удаляем взорвавшиеся фейрверки на всех уровнях, кроме последнего
{
	std::list<Firework*>::iterator el=_forest.begin();
	while(_forest.size()!=0 && !((*el)->_isAlive) && !((*el)->_isAccesable))
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
	_fuel = 0.2;
	_velocityCoeff=0.1;
	_wasLastGroup = false;
}


void MyWidget::UpdateFirePosition(float dt) 
{
	if(_forest.size()!=0)
	{
		std::list<Firework*>::iterator el=_forest.begin();
		while(el!=_forest.end())
		{
			if(_effCont.CheckEffect((*el)->_eff) && ((*el)->_isAlive || (*el)->_isAccesable))
				(*el)->UpdatePosition(dt,_gravity, _factor, _fuel, _currLevel);
			++el;
		}
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

void MyWidget::CheckAccesibility() // проверяет жизнь последнего уровня
{
	int i=0;
	int sz;
	if(_forest.size()!=0)
	{
		sz=_forest.size();
		list<Firework*>::iterator el = _forest.begin();
		while(el!=_forest.end() && i<sz)
		{
			if((*el)->_eff!=NULL && (*el)->_eff->isEnd())
			{
					(*el)->_isAccesable = false;
					_forest.front()->_eff->Finish();
					_forest.front()->_eff=NULL;
					_forest.front()->DestroyOne();
					_forest.pop_front();
					el=_forest.begin();
			}
			i++;
		}
	}
}


void MyWidget::Update(float dt)
{
	if(_isCreated)
	{	
		if(_lastGroupWasDestroyed)
		{
				_lastGroupWasDestroyed=false;
				DeleteDead();
				if(_wasLastGroup)
				{
					_isCreated=false;
					UpdateFirePosition(dt);
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
			_factor=1;
			_fuel=0;
			_gravity=0.15;
			_lifeTime=_lifeTime/2.f;
			_alpha*=0.5;
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
				 if(!_wasLastGroup)
				 {
					(*el)->_isAlive=false;
					(*el)->_isAccesable=false;
					(*el)->_eff->Finish();

					for(int i=0; i<_children; i++)
					{
						ParticleEffect* eff =_effCont.AddEffect("Tail2");
						_forest.push_back(new Firework(0,eff));
						_forest.back()->_pos = (*el)->_pos;
						_forest.back()->_eff->posX = (*el)->_pos.x;
						_forest.back()->_eff->posY = (*el)->_pos.y;
						_forest.back()->_velocity+= (*el)->_velocity*_velocityCoeff;
						_forest.back()->_eff->Reset();
					}
					if(_currLevel==1) // взрыв на 1-ом уровне
					{
						(*el)->_eff= _effCont.AddEffect("Exp");
						(*el)->_eff->posX = (*el)->_pos.x;
						(*el)->_eff->posY = (*el)->_pos.y;
						(*el)->_eff->Reset();
					}
				}
				currLevelFireCounter++;
				++el;
			}
			_currLevel++;
			_velocityCoeff*=0.5;
		}
	}
	else // если осталось только уничтожить последнюю группу 
	{	
		if(_forest.size()!=0)
		{
			list<Firework*>::iterator el=_forest.begin();
			while(el!=_forest.end()) 
			{
				// если заряд выходит за рамки экрана, уничтожить его
				if(((*el)->_pos.y <= 0 || (*el)->_pos.y >= Core::appInstance->GAME_CONTENT_HEIGHT || (*el)->_pos.x <= 0 || (*el)->_pos.x >= Core::appInstance->GAME_CONTENT_WIDTH)  && (*el)->_isAlive && (*el)->_isAccesable )
				{
					(*el)->_isAlive=false;
					(*el)->_isAccesable=false;
					(*el)->_eff->Finish();
					(*el)->_eff=NULL;
				}
				++el;
			}
			if(_level>1) // увеличиваем гравитацию если у нас больше одного заряда
				_gravity+=0.01;
		}
	}
	UpdateFirePosition(dt);
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


#ifndef _PLAYRIX_LAYER_H_
#define _PLAYRIX_LAYER_H_

#include "GUI/Widget.h"

namespace Render {
	class Texture;
}

#include "MessageFunc.h"

class Layer 
{
private:
	typedef std::map<std::string, GUI::Widget*>::iterator MapIterator;
	typedef std::vector<GUI::Widget*>::iterator VectorIterator;
	typedef std::vector<GUI::Widget*>::reverse_iterator VectorReverseIterator;

	GUI::Widget *_activeWidget;
	
	Render::Texture* _background;
	
	std::map<std::string, GUI::Widget*> _widgetsMap;
	
	std::vector<GUI::Widget*> _widgets;
	
	std::vector<std::string> _resourceGroups;
		// Группы ресурсов привязанные к слою. Они будут загружаться и выгружаться автоматически.
	
	bool _isInputTransparent;
		// Прозрачен слой ли для событий ввода (мышь, клавиатура);
		// прозрачные для событий слои получают их, но не задерживают,
		// таким образом, события доходят до нижних слоев;
		// флаг регулируется в XML атрибутом inputTransparent с возможными значениями "true" или "false";
		// значение по умолчанию - "false".
	
	//void LinkChildren();
	
	void LoadWidgets(Xml::TiXmlElement* elem, const std::string& parentName = "", GUI::Widget *parent = 0);
	
	// Пересчёт позиции мыша с учётом поворота, смещения и масштаба
	IPoint CalcMousePos(const IPoint& mousePos);
	
	void deleteWidget(GUI::Widget* w);
public:
	MessageFunc* messageFunc;
	std::string name;
	bool alternative;
	math::Vector3 position;
	math::Vector3 centerRotation;
	float angleZ;
	float scale;
	
	bool allowDeinit;
		// Позволить ли деинициализацию слоя

	Layer();
	Layer(Xml::TiXmlElement* elem);
	virtual ~Layer();
	GUI::Widget* activeWidget();
	void setActiveWidget(GUI::Widget* w);
	void ResetWidgetPositions();
	void Load(Xml::TiXmlElement* elem);
	void Draw(float scale=1.f, float angle=.0f);
	//void ProcessMessages();
	//void Update();
	void AcceptMessage(const Message& message);
	void BroadcastMessage(const Message& message);
	void addWidget(GUI::Widget* widget);
	void UpdateRotateCenter(const std::string& widgetName);
	void deleteWidget(const std::string& name);
	GUI::Widget* getWidget(const std::string& name);
	void setMessageFunc(MessageFunc* func);
	bool MouseDown(const IPoint &mousePos);
	void MouseUp(const IPoint &mousePos);
	void MouseMove(const IPoint &mousePos);
	void Update(float dt);
	void MouseDoubleClick(const IPoint &mousePos);
	void KeyPress(int keyCode);
	void MouseWheel(int delta);
	float GetScale() { return scale; };

	// Существует ли виджет с таким именем
	bool IsWidgetExists(std::string name);

	// Вернуть первый виджет в лэйере
	GUI::Widget* GetFirstWidget();
	
	// Грузит ресурсы и вызывает lua инициализатор
	void InitLayer();
	
	// Выгружает ресурсы и вызывает lua деинициализатор
	void DeinitLayer();
	
	void UploadResources();
	
	void ReleaseResources();
	
	// Прозрачен ли для событий ввода
	bool IsInputTransparent();

	// Устанавливает флаг, указывающий, можно ли производить 
	// деинициализацию слоя (выгрузку ресурсов группы слоя)
	void SetAllowDeinit(bool allow);

	// Можно ли деинициализировать слой (выгрузить его ресурсы)
	bool IsAllowDeinit() const;
};

#endif

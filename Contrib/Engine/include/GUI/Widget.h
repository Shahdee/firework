#pragma once

#include "Core/MessageManager.h"
#include "Core/ResourceManager.h"

#include "Render/Texture.h"

#include "Text.h"
#include "Core/cursor.h"

namespace GUI {
	class Widget;
}
class ParticleEffect;
struct EffectProxy;
class EffectsContainer;
class Layer;

typedef std::vector<GUI::Widget*> widget_container;
typedef std::vector<GUI::Widget*>::iterator widget_iterator;

/// Пространство имён для элементов GUI.

/// Тут собраны Widget и все его потомки. Графический интерфейс обычно создаётся посредством Layer и Factory::widgetFactoryXml.
namespace GUI {

	/// Предок всех классов графического интерфейса.
	class Widget
	{
		friend class ::Layer;
	public:
		bool InternalMouseDown(const IPoint& mouse_pos);
		void InternalMouseDoubleClick(const IPoint& mouse_pos);
		void InternalMouseUp(const IPoint& mouse_pos);
		void InternalMouseMove(const IPoint& mouse_pos);
		void InternalMouseWheel(int delta);
	protected:

		widget_container _child;
		Widget* _parent;

		bool _isFreeze;
		bool _isVisible;
		bool _isMouseCheck;

		bool _isMouseClick;
		bool _isUnderMouse;
		bool _isStatic;
		bool _isNeedUpdate;

		IPoint _mouse_down;
		IPoint _click_pos;

		Text _widgetText;

		Color _color;

		Render::Texture* _inputMask;

		int _maskLevel;
		int _clientOffset;

		//std::list<EffectProxy*> m_effects;
		void DragWidget(const IPoint& mouse_pos);

	public:
		static Core::Cursor* _cursor;

		EffectsContainer* m_effects;

		Widget(const std::string& name_);
		Widget(const std::string& name_, const IRect& rect);
		Widget(const std::string &name_, Xml::TiXmlElement* xmlElement);
		Widget(const std::string &name_, rapidxml::xml_node<>* xmlElement);

		std::string name;
		std::string parentName;
		std::string layerName;

		int ID;

		int width, height;

		IPoint position;
		IRect clientRect;
		IPoint initPosition;

		virtual ~Widget();

		static void setCursor(Core::Cursor* cursor);

		virtual bool CheckPoint(const IPoint& point);
		bool MouseOnWindow();

		void setInputMask(Render::Texture* inputMask);

		void setWidgetText(const std::string& text);

		void setClientRect(const IRect& rect);

		void setPosition(const IPoint& position_);

		void setColor(const Color& color);

		//void setColorWithChilds(const Color& color);

		Color getColor();

		void AddChild(Widget* child);

		widget_container& getChildList();

		Widget* getChild(const std::string &name);
		
		// recursive search
		Widget* FindChild(const std::string &name);

		void setParent(Widget* parent);

		void setStatic(bool bStatic);

		bool isStatic() const;

		void setVisible(bool bVis);
		
		bool isVisible() const;

		Widget* getParent();

		IPoint getParentPosition();

		ParticleEffect* AddEffect(const std::string& effectName);

		void setUpdate(bool bNeedUpdate)	{_isNeedUpdate = bNeedUpdate;}
		bool isUpdate()	{return _isNeedUpdate;}

		virtual bool MouseDown(const IPoint& mouse_pos);
		virtual void MouseDoubleClick(const IPoint& mouse_pos);
		virtual void MouseUp(const IPoint& mouse_pos);
		virtual void MouseMove(const IPoint& mouse_pos);
		virtual void MouseWheel(int delta);
		virtual void Draw();
		virtual void Reset();
		virtual void Update(float) {};

		virtual void AcceptMessage(const Message& message);
		virtual Message QueryState(const Message& message) const;
		
		void SetCenterPosition(const IPoint& pos);
		IPoint GetCenterPosition();
		void ResetPosition();
		void SetInitPosition();

		virtual void FullDraw();
		void FullUpdate(float dt);
		Widget* activeWidget();
		void setActiveWidget();
	private:
		void InitWithXml(Xml::TiXmlElement* xmlElement);
		void InitWithXml(rapidxml::xml_node<>* xmlElement);
	};
}

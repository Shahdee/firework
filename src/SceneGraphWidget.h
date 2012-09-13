#pragma once

using namespace SceneGraph;

///
/// ������, ������������ 3D �����.
///
class SceneGraphWidget : public GUI::Widget {
public:
	SceneGraphWidget(const std::string& name, Xml::TiXmlElement* xe);
	
	void Update(float dt);
	
	void Draw();

private:
	Scene::HardPtr _scene;
		/// 3D �����
};

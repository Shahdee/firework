#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/AxisAlignedBoundingBox.h"
#include "Utils/Matrix4.h"
#include "Utils/Quaternion.h"

namespace SceneGraph {

class Scene;

typedef boost::weak_ptr<Scene> SceneWeakPtr;
	// ����� ������������ ����������� ��� ������ ������ ��� ������ Scene,
	// �.�. �� �� ����� �������� ����� ���� ������������ ���� �� ��� ��������������
	// ����������� �����������.

///
/// ������� ����� ��� ���� ����� �����.
///
class SceneNode {
public:
	typedef boost::shared_ptr<SceneNode> HardPtr;
	
	typedef boost::weak_ptr<SceneNode> WeakPtr;
	
	typedef std::map<std::string, SceneNode::HardPtr> SceneNodesMap;
	
	///
	/// ����������� ���� ����� �����.
	///
	enum Type {
		Unknown,
			/// ����������� ���� (�� ������������)
		Frame,
			/// �����
		Mesh,
			/// ���
		Model,
			/// ������
		Light,
			/// �������� �����
		Camera
			/// ������
	};
	
	SceneNode(const std::string& name, SceneNode::WeakPtr parent, SceneWeakPtr scene, SceneNode::Type type = SceneNode::Unknown);
	
	virtual ~SceneNode() {}
	
	virtual SceneNode::HardPtr Clone();
	
	SceneNode::Type GetType() const;
		/// ���������� ��� ���� �����
	
	void SetType(SceneNode::Type type);
		/// ������������� ��� ���� �����
	
	virtual unsigned int GetRenderPass() const;
		/// ���������� ���� �������� ������������, ��� ������� ������ ������������� ��������� ����
	
	const std::string& GetName() const;
		/// ���������� ��� ����
	
	void SetName(const std::string& name);
		/// ������������� ��� ����
	
	SceneNode::HardPtr GetParent() const;
		/// ���������� ������������ ����
	
	void SetParent(SceneNode::WeakPtr parent);
		/// ������������� ������������ ����
	
	SceneWeakPtr GetScene() const;
		/// ���������� �����, ������� ����������� ������ ����
	
	void SetScene(SceneWeakPtr scene);
		/// ������������� �����, ������� ����������� ������ ����
	
	const math::Vector3& GetOriginalPosition() const;
	const math::Quaternion& GetOriginalRotation() const;
	const math::Vector3& GetOriginalScaling() const;
		/// ���������� �������� ������ �������������

	const math::Matrix4& GetOriginalTransform() const;
		/// ���������� ������� ��������� �������������� ����
	
	void SetOriginalTransform(const math::Matrix4& transform);
		/// ������������� ������� ��������� �������������� ����
	
	void MultiplyOriginalTransform(const math::Matrix4& transform);
		/// �������� ������� ��������� �������������� ���� �� ��������� ������� �������������
	
	void MultiplyOriginalTransformLocal(const math::Matrix4& transform);
		/// �������� �������� ������� ��������� �������������� ���� �� ��������� ������� �������������
	
	void ResetRelativeTransform();
		/// ������������� ������� �������������� �������������� ������� ��������� ��������������
	
	const math::Matrix4& GetRelativeTransform() const;
		/// ���������� ������� �������������� �������������� ����
	
	void SetRelativeTransform(const math::Matrix4& transform);
		/// ������������� �������������� �������������� ����
	
	void AddRelativeTransform(const math::Matrix4& transform);
		/// ��������� �������������� � �������������� �������������� ����
	
	void MultiplyRelativeTransform(const math::Matrix4& transform);
		/// �������� ������������� �������������� ���� �� ��������� ������� �������������
	
	void MultiplyRelativeTransformLocal(const math::Matrix4& transform);
		/// �������� �������� ������������� �������������� ���� �� ��������� ������� �������������
	
	void UpdateAbsoluteTransform();
		/// ���������� ��������� ������������� ���� ������������ ������� ������� ���������
	
	const math::Matrix4& GetAbsoluteTransform() const;
		/// ���������� ������� ����������� �������������� ����
	
	const AxisAlignedBoundingBox& GetBoundingBox() const;
		/// ���������� ����������� �� ���� �������������� �������������
	
	AxisAlignedBoundingBox GetTransformedBoundingBox() const;
		/// ���������� ������������������ �������������� �������������
	
	void SetBoundingBox(const AxisAlignedBoundingBox& aabbox);
		/// ������������� �������������� �������������, ����������� �� ����
	
	const SceneNodesMap& GetChildren() const;
		/// ���������� ��������� �������� �����
	
	bool AddChild(SceneNode::HardPtr node);
		/// ��������� ���� � ������ �������� �����
	
	SceneNode::HardPtr RemoveChild(const std::string& name);
		/// ������� ���� �� ������ �������� ����� ������������
	
	void Remove();
		/// ������� ���� �� ������ �������� ����� ��������
	
	SceneNode::HardPtr FindChild(const std::string& name) const;
		/// ���������� ���� ���� ����� �����
	
	virtual void Update(float dt);
		/// ���������� ������ ����� ��� ������� ���� �� ������� �������
	
	virtual void Draw() const;
		/// ���������� ������ ����� ��� ��������� ����
	
protected:
	static SceneNode::HardPtr FindChildInCollection(const SceneNodesMap& collection, const std::string& name);
		/// ���������� ���� ���� ����� ��������� ��������� ���������
	
	SceneNode(const SceneNode& rhs);
	
	SceneNode& operator = (const SceneNode& rhs);

protected:
	SceneNode::Type _type;
		/// ��� ���� �����
	
	std::string _name;
		/// ���������� ��� ����
	
	SceneNode::WeakPtr _parent;
		/// ������������ ����
	
	SceneNodesMap _children;
		/// ����������� ����� �� ���� ��� �������� ������ �����
	
	SceneWeakPtr _scene;
		/// �����, ������� ����������� ������ ����
	
	math::Matrix4 _originalTransform;
		/// �������� ������������� ����.
		///
		/// �������������� OriginalTransform ������ ����� ������������� �������������� ����
		/// �� ��������� � �������������� ������������� ����, ������� ���������� �� �����
		/// ������������ � ��������������� �� ����� �������� ������.
		///
		/// �������������� RelativeTransform ��������������� ������ OriginalTransform
		/// � ������ ������� ����� � ����������� ���������������� �� ����� ��������� ��������.

	math::Vector3 _originalPosition;
	math::Quaternion _originalRotation;
	math::Vector3 _originalScaling;
		/// �������� �������������� ������������� (����������� �� ������ ������������ _originalTransform
		/// ����� ��� ��������� ������ ������������� ��-��������� ��� KeyframeAnimation
	
	math::Matrix4 _relativeTransform;
		/// ������������� ���� ������������ ������������ ������������� ����.
	
	math::Matrix4 _absoluteTransform;
		/// ������������� ������������ �������� ������������.
		///
		/// �������������� AbsoluteTransform �������� ���������� �� ��������� � ����
		/// � �������������� ��� ���� �������� ������������ ����� ����,
		/// ��� ����� ����������� ��� ��������� � ������������� �������������� ���� ����� �����.
	
	AxisAlignedBoundingBox _aabbox;
		/// �������������� �������������, ����������� �� ����
};

} // namespace SceneGraph

#endif // __SCENENODE_H__

#ifndef __BONECONTENT_H__
#define __BONECONTENT_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Utils/Matrix4.h"
#include "SceneGraph/SceneNode.h"

namespace SceneGraph {

///
/// ���������� ����� (���� ������ ����������� ����).
/// ���������� �������� ������ ���� � ��������� �����.
///
class BoneContent {
public:
	typedef boost::shared_ptr<BoneContent> HardPtr;
	
	typedef boost::weak_ptr<BoneContent> WeakPtr;
	
	typedef std::pair<std::size_t, float> VertexWeight;
	
	BoneContent(SceneNode::WeakPtr bone, const math::Matrix4& offset);
	
	virtual BoneContent::HardPtr Clone() const;
	
	SceneNode::HardPtr GetBone() const;
		/// ���������� �����, � ������� ��������� �������
	
	void SetBone(SceneNode::WeakPtr bone);
		/// ������������� �����, � ������� ��������� �������
	
	const math::Matrix4& GetBoneOffset() const;
		/// ���������� ������� �������������� �� ������������ ���� � ������������ ����� � ����
	
	void SetBoneOffset(const math::Matrix4& offset);
		/// ������������� ������� �������������� �� ������������ ���� � ������������ ����� � ����
	
	const std::vector<VertexWeight>& GetWeights() const;
		/// ���������� ��������� ����� ������ �����
	
	void AddWeight(const VertexWeight& weight);
		/// ��������� ��� ������� � ���������

private:
	SceneNode::WeakPtr _bone;
		/// �����, � ������� ��������� �������
	
	struct Content {
		math::Matrix4 _offset;
			/// ������� ��������� �������������� �� ������������ ���� � ������������ ���� �����
		
		std::vector<VertexWeight> _weights;
			/// ����� ����� ������ ��� ������ �����
		
		Content(const math::Matrix4& offset)
			: _offset(offset)
		{}
	};
	
	boost::shared_ptr<Content> _content;
		// ������������ ������ ��� ������������ ������������� ���������� �� ������, � �� �� ��������
};

} // namespace SceneGraph

#endif // __BONECONTENT_H__

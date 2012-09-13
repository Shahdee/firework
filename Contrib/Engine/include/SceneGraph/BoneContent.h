#ifndef __BONECONTENT_H__
#define __BONECONTENT_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "Utils/Matrix4.h"
#include "SceneGraph/SceneNode.h"

namespace SceneGraph {

///
/// —одержимое кости (веса вершин конкретного меша).
/// ќпредел€ет прив€зку вершин меша к указанной кости.
///
class BoneContent {
public:
	typedef boost::shared_ptr<BoneContent> HardPtr;
	
	typedef boost::weak_ptr<BoneContent> WeakPtr;
	
	typedef std::pair<std::size_t, float> VertexWeight;
	
	BoneContent(SceneNode::WeakPtr bone, const math::Matrix4& offset);
	
	virtual BoneContent::HardPtr Clone() const;
	
	SceneNode::HardPtr GetBone() const;
		/// ¬озвращает кость, к которой прив€заны вершины
	
	void SetBone(SceneNode::WeakPtr bone);
		/// ”станавливает кость, к которой прив€заны вершины
	
	const math::Matrix4& GetBoneOffset() const;
		/// ¬озвращает матрицу преобразовани€ из пространства меша в пространство кости в позе
	
	void SetBoneOffset(const math::Matrix4& offset);
		/// ”станавливает матрицу преобразовани€ из пространства меша в пространство кости в позе
	
	const std::vector<VertexWeight>& GetWeights() const;
		/// ¬озвращает коллекцию весов вершин кости
	
	void AddWeight(const VertexWeight& weight);
		/// ƒобавл€ет вес вершины к коллекции

private:
	SceneNode::WeakPtr _bone;
		///  ость, к которой прив€заны вершины
	
	struct Content {
		math::Matrix4 _offset;
			/// ћатрица обратного преобразовани€ из пространства меша в пространство позы кости
		
		std::vector<VertexWeight> _weights;
			/// Ќабор весов вершин дл€ данной кости
		
		Content(const math::Matrix4& offset)
			: _offset(offset)
		{}
	};
	
	boost::shared_ptr<Content> _content;
		// Ќеизмен€емые данные при клонировании целесообразно копировать по ссылке, а не по значению
};

} // namespace SceneGraph

#endif // __BONECONTENT_H__

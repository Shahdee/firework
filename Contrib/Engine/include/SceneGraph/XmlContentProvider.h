#ifndef __XMLCONTENTPROVIDER_H__
#define __XMLCONTENTPROVIDER_H__

#ifdef _MSC_VER
#pragma once
#endif // _MSC_VER

#include "SceneGraph/ContentProvider.h"
#include "SceneGraph/ModelNode.h"
#include "SceneGraph/Mesh.h"
#include "SceneGraph/SkinnedMesh.h"
#include "SceneGraph/KeyFramedAnimation.h"
#include "SceneGraph/Material.h"

namespace SceneGraph {

///
/// œÓ‚‡È‰Â ÍÓÌÚÂÌÚ‡, Á‡„ÛÊ‡˛˘ËÈ ÒÍÂÎÂÚÌÛ˛ ÏÓ‰ÂÎ¸ ËÁ XML ÓÔËÒ‡ÌËˇ.
///
class XmlContentProvider : public ContentProvider {
public:
	XmlContentProvider();
	
	~XmlContentProvider();
	
	ModelNode::HardPtr LoadModel(const std::string& filename);
		/// «‡„ÛÊ‡ÂÚ ÏÓ‰ÂÎ¸ ËÁ Ù‡ÈÎ‡
	
	ModelNode::HardPtr LoadModel(rapidxml::xml_node<char>* xe);

private:
	///
	///  ÓÌÚÂÍÒÚ, ‡Á‰ÂÎˇÂÏ˚È ÏÂÚÓ‰‡ÏË Á‡„ÛÁ˜ËÍ‡.
	///
	struct Context {
		typedef std::multimap<std::string, BoneContent::HardPtr> BonesMap;
			// Œ‰Ì‡ ÍÓÒÚ¸ ÏÓÊÂÚ ‚ÎËˇÚ¸ Ì‡ ÌÂÒÍÓÎ¸ÍÓ ÏÂ¯ÂÈ, ÔÓ˝ÚÓÏÛ ‰ÓÔÛÒÚËÏÓ
			// ËÏÂÚ¸ ÌÂÒÍÓÎ¸ÍÓ Ó·˙ÂÍÚÓ‚ BoneContent, ‡ÒÒÓˆËËÓ‚‡ÌÌ˚ı
			// Ò Ó‰ÌËÏ Ë ÚÂÏ ÊÂ ËÏÂÌÂÏ ÍÓÒÚË.
		BonesMap bones;
	};
	
	void FindMeshNodes(ModelNode::HardPtr pModel, SceneNode::HardPtr pNode);
		/// –ÂÍÛÒË‚ÌÓ Ë˘ÂÚ ÛÁÎ˚ ÏÂ¯ÂÈ Ë ‰Ó·‡‚ÎˇÂÚ Ëı Í ÍÓÎÎÂÍˆËË ‰ÂÚÂÈ ÏÓ‰ÂÎË
	
	SceneNode::HardPtr LoadNode(SceneNode::HardPtr parent, rapidxml::xml_node<char>* xe, Context& context);
		/// –ÂÍÛÒË‚ÌÓ Á‡„ÛÊ‡ÂÚ ÛÁÂÎ Ò ÔÓÚÓÏÍ‡ÏË
	
	Mesh::HardPtr LoadMesh(rapidxml::xml_node<char>* xe, Context& context);
		/// «‡„ÛÊ‡ÂÚ ÏÂ¯
	
	BoneContent::HardPtr LoadBoneContent(rapidxml::xml_node<char>* xe, Context& context);
		/// «‡„ÛÊ‡ÂÚ ‚ÂÒ‡ ‚Â¯ËÌ ‰Îˇ ÍÓÒÚÂÈ ÒÍÂÎÂÚ‡
	
	Animation::HardPtr LoadAnimation(ModelNode::HardPtr pModel, rapidxml::xml_node<char>* xe);
		/// «‡„ÛÊ‡ÂÚ ‡ÌËÏ‡ˆË˛
	
	AnimationChannel::HardPtr LoadAnimationChannel(KeyFramedAnimation::WeakPtr pAnimation, ModelNode::HardPtr pModel, rapidxml::xml_node<char>* xe);
		/// «‡„ÛÊ‡ÂÚ Í‡Ì‡Î ‡ÌËÏ‡ˆËË
	
	Material::HardPtr LoadMaterial(rapidxml::xml_node<char>* xe);
		/// «‡„ÛÊ‡ÂÚ Ï‡ÚÂË‡Î
	
	math::Matrix4 LoadMatrix(rapidxml::xml_node<char>* xe);
		/// «‡„ÛÊ‡ÂÚ Ï‡ÚËˆÛ Ú‡ÌÒÙÓÏ‡ˆËË
	
	math::Vector3 LoadVector(rapidxml::xml_node<char>* xe);
		/// «‡„ÛÊ‡ÂÚ ‚ÂÍÚÓ
	
	math::Quaternion LoadQuaternion(rapidxml::xml_node<char>* xe);
		/// «‡„ÛÊ‡ÂÚ Í‚‡ÚÂÌËÓÌ
};

} // namespace SceneGraph

#endif // __XMLCONTENTPROVIDER_H__

#pragma once

#include "Render/VertexBuffer.h"

namespace Render {
	class Texture;
}

class Animation3D
{
	typedef std::vector<math::Vector3> PointsArray;
	struct Triangle
	{
		int A, B, C, AT, BT, CT;
		Color cA, cB, cC;

		Triangle()
			: cA(Color(255, 255, 255, 255))
			, cB(Color(255, 255, 255, 255))
			, cC(Color(255, 255, 255, 255))
		{};
	};

	struct MyMesh
	{
		PointsArray meshVertexList;
		PointsArray texVertices;
		std::vector<Triangle> triangles;
	};

	// внутри какого элемента находимся
	enum Tag {
		None = 0, // пока не зашли ни в какой элемент
		GeomObject,
		TmAnimation,
		ControlRotTrack,
		MeshAnimation,
		Mesh,
		MeshVertexList,
		MeshFaceList,
		MeshTVertList,
		MeshTFaceList,
		MeshNormals,
		Unknown,
	};

	std::vector<MyMesh> _meshes;

	enum TransformType
	{
		NoTrans = 0,
		Rotate,
	};

	struct Transform
	{
		TransformType type;
		math::Vector3 vRot;
		float angle;
	};

	std::vector<Transform> _transforms;

	MyMesh _currentMesh;

	VertexBuffer _vertexBuffer;

	std::vector<Tag> _tags;

	size_t _q;
	
	math::Vector3 _light;

public:
	Animation3D();
	~Animation3D();

	void CalcColor(math::Vector3 norm, math::Vector3 light, Color &color);
	bool prefixIs(const std::string &s, const std::string &prefix);
	void LoadFromASE(const std::string &fileName);

	// mirror = true для использования в инвертированных по x координатах
	void Draw(float time, bool mirror = false);

	static void RotateX(math::Vector3 &v, float angle);
	static void RotateY(math::Vector3 &v, float angle);
	static void RotateZ(math::Vector3 &v, float angle);
	void RotateV(math::Vector3 &v, math::Vector3 vRot, float angle);

	void EatNumber(std::string &s);
	void FindNumber(std::string &s);

	void LoadFromBinary(const string &fileName);
	void SaveToBinary(const string &fileName);


private:
	void FillVertexBuffer(MyMesh &mesh1, MyMesh &mesh2, float local_time, bool mirror);
	void ResetPushVertex();
	void PushVertex(const Render::QuadVert &v);
	void FillVertexA(const MyMesh & mesh1, const MyMesh & mesh2, const Triangle& tr1, const Triangle& tr2, float local_time, Render::QuadVert* v);
	void FillVertexB(const MyMesh & mesh1, const MyMesh & mesh2, const Triangle& tr1, const Triangle& tr2, float local_time, Render::QuadVert* v);
	void FillVertexC(const MyMesh & mesh1, const MyMesh & mesh2, const Triangle& tr1, const Triangle& tr2, float local_time, Render::QuadVert* v);
};



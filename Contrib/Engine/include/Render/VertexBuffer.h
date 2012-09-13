#pragma once

class VertexBuffer;
class VertexBufferIndexed;

#include "Render/RenderDevice.h"
#include "Assert.h"

#if defined(ENGINE_TARGET_WIN32_DX9)
#	define HARDWAREBUFFER IDirect3DVertexBuffer9*
#	define HARDWAREIBUFFER IDirect3DIndexBuffer9* 
#	define INDEX WORD
#elif defined(ENGINE_TARGET_WIN32_DX8)
#	define HARDWAREBUFFER IDirect3DVertexBuffer8*
#	define HARDWAREIBUFFER IDirect3DIndexBuffer8* 
#	define INDEX WORD
#else
#	define HARDWAREBUFFER GLuint
#	define HARDWAREIBUFFER GLuint
#	define INDEX GLushort
#endif

class VertexBuffer 
{
private:
	bool reloadWithAlpha;
public:

	HARDWAREBUFFER _deviceBuffer;

	struct triangle
	{
		unsigned int v[3];
	};

	struct face_normal
	{
		math::Vector3 normal[3];
	};
	
	std::vector<float> _vertex_data;
	std::vector<triangle> _index_data;

    unsigned int numVertices;
	unsigned int numPrimitives;
	unsigned int numFaces;

	std::vector<math::Vector3> _coord;
	std::vector<face_normal> _normals;
	std::vector<math::Vector3> _uv;
	std::vector<triangle> _uv_index_data;

	std::vector<Render::QuadVert> _buffer;
	std::vector<Render::QuadVert> _buffer2;

	VertexBuffer();
	VertexBuffer(const VertexBuffer& vb);
	virtual ~VertexBuffer();

	struct VertexAttribute
	{
		bool bNormal;
		bool bVertexColor;
		bool bTexCoords;
		int numOfMappingChannels;
	};

	VertexAttribute vertexAttribs;

	virtual void Init(int numOfVertices);

	virtual void InitQuadBuffer(int numOfQuads);

	void LoadData(const std::string& filename);

	virtual void SetQuad(int quadIndex, float x, float y, float width, float height, Color color);

	void SetQuad(int quadIndex, IRect rect, FRect uv);
	void SetQuad(int quadIndex, float x, float y, float width, float height, FRect uv, Color color);
	
	/// x, y - центр вращения 
	virtual void SetQuad(int quadIndex, float x, float y, float width, float height, float angle, Color color);

	/// x, y - центр вращения
	virtual void SetQuad(int quadIndex, float x, float y, float width, float height, float angle,
		Color color, float uStart, float uEnd, float vStart, float vEnd);
	
	virtual void SetQuad(int quadIndex, const math::Vector3& v0, const math::Vector3& v1, 
		const math::Vector3& v2, const math::Vector3& v3, const Color& color,
		float uStart = 0.0f, float uEnd = 1.0f, float vStart = 0.0f, float vEnd = 1.0f);

	virtual void SetQuad(int quadIndex, const math::Vector3& v0, const math::Vector3& v1, 
		const math::Vector3& v2, const math::Vector3& v3,
		const Color& c1, const Color& c2, const Color& c3, const Color& c4,
		float uStart = 0.0f, float uEnd = 1.0f, float vStart = 0.0f, float vEnd = 1.0f);
	
	void SetRawData(Render::QuadVert *buf);
	virtual void Upload(int verticesCount = -1);
			// VerticesCount - количество вершин для подгрузки (-1 - будут подгружены все вершины в буффере)
	virtual void Draw(int verticesCount = -1);
			// VerticesCount - количество вершин для отрисовки (-1 - будут отрисованы все вершины в буффере)
	void DrawAlphaBounded();
	
};

class VertexBufferIndexed : public VertexBuffer
{
public:
	int numIndices;
	HARDWAREIBUFFER _deviceIndex;
	std::vector<INDEX> _ibuffer;

public:
	VertexBufferIndexed();
	VertexBufferIndexed(const VertexBufferIndexed &v);
	virtual ~VertexBufferIndexed();

	virtual void Init(int numOfVertices, int numOfIndices = 0);
	virtual void Reinit(int numOfVertices, int numOfIndices = 0); 
	virtual void InitQuadBuffer(int numOfQuads);

	virtual void SetQuad(int quadIndex, float x, float y, float width, float height, Color color);

	/// x, y - центр вращения
	virtual void SetQuad(int quadIndex, float x, float y, float width, float height, float angle, Color color);

	/// x, y - центр вращения
	virtual void SetQuad(int quadIndex, float x, float y, float width, float height, float angle,
		Color color, float uStart, float uEnd, float vStart, float vEnd);
	
	/// x, y - центр вращения
	void SetQuad(int quadIndex, float x, float y, float width, float height, float sx, float sy, float angle,
		Color color, float uStart, float uEnd, float vStart, float vEnd);

	virtual void SetQuad(int quadIndex, const math::Vector3& v0, const math::Vector3& v1, 
		const math::Vector3& v2, const math::Vector3& v3, const Color& color,
		float uStart = 0.0f, float uEnd = 1.0f, float vStart = 0.0f, float vEnd = 1.0f);

	virtual void SetQuad(int quadIndex, const math::Vector3& v0, const math::Vector3& v1, 
		const math::Vector3& v2, const math::Vector3& v3,
		const Color& c1, const Color& c2, const Color& c3, const Color& c4,
		float uStart = 0.0f, float uEnd = 1.0f, float vStart = 0.0f, float vEnd = 1.0f);
	
	virtual void Upload(int verticesCount = -1);
	virtual void Draw(int verticesCount = -1);
	
	void setVertex(int qIndex, Render::QuadVert quad);
	void setIndex(int qIndex, int index);
	void setBuffer(const std::vector<Render::QuadVert> &buffer);
	void setIndexBuffer(const std::vector<INDEX> &ibuffer);
	void UploadVertex();
	void UploadIndex(); 
};
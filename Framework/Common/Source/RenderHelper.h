#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include "Vertex.h"

class Mesh;

class RenderHelper
{
public:
	static void RenderMesh(Mesh* _mesh);
	static void RenderItem(Mesh* _item, float pos_x, float pos_y, float scale_x, float scale_y);
	static void RenderMeshWithLight(Mesh* _mesh);
	static void RenderText(Mesh* _mesh, const std::string& _text, Color _color);
	static void RenderSprite(Mesh* _mesh, unsigned frame);
};

#endif // RENDER_HELPER_H
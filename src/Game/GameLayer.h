#pragma once

#include"Application/Layer.h"

#include"../OpenGL/VertexArray.h"
#include"../OpenGL/Shader.h"
#include"../OpenGL/Texture.h"

#include"Object/MapTile.h"
#include"Object/Quad.h"

#include<vector>

class GameLayer : public Layer
{
public:
	GameLayer();

	void onAttach();
	void onDetach();
	void onUpdate(float dt);
private:
	VertexArray m_va;
	Shader m_shader;
	Texture m_texture;

	std::vector<MapTile> m_map;
	std::vector<Quad> m_quads;
	Quad m_quad;
};
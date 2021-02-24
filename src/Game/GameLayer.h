#pragma once

#include"Application/Layer.h"

#include"../OpenGL/VertexArray.h"
#include"../OpenGL/Shader.h"

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
};
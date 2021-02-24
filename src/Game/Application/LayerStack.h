#pragma once

#include<vector>
#include<memory>

#include"Layer.h"

using LayerPtr = std::unique_ptr<Layer>;

class LayerStack
{
public:
	LayerStack() = default;

	void pushLayer(LayerPtr&& layer) { layer->onAttach(); m_layerStack.push_back(std::move(layer)); }
	void popLayer() { m_layerStack.back()->onDetach(); m_layerStack.pop_back(); }

	std::vector<LayerPtr>::iterator begin() { return m_layerStack.begin(); }
	std::vector<LayerPtr>::iterator end() { return m_layerStack.end(); }
private:
	std::vector<LayerPtr> m_layerStack;
};
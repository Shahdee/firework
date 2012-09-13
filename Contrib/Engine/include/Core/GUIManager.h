#pragma once

#include "Text.h"

#include "Layer.h"

#include "Assert.h"

namespace Core
{

	class GUIManager
	{
	public :
		typedef std::map <std::string, Layer *> LayerMap;

	private :
		typedef LayerMap::iterator layer_iterator;

		LayerMap _layers;
		LayerMap _altlayers;

	public:

		GUIManager(void);
		~GUIManager(void);

		void addLayer(Layer* layer);

		const LayerMap& GetLayers() const;
		Layer* getLayer(const string& name);
		Layer* getLayerAlt(const string& name, bool alt);

		void ReloadLayers(const string& filename);
		void LoadLayers(const string& filename);
		bool isLayerLoaded(const string &name);

		void Update(float dt);

		//
		// Очистить все слои
		// Должна вызываться из Application::Shutdown, таким образом,
		// все виджеты могут быть уверены, что их деструкторы вызовутся
		// _до_ разрушения статических объектов и вправе обращаться к ним.
		//
		void ClearLayers();
	};

	extern GUIManager guiManager;
}

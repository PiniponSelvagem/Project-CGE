#pragma once
#include "../../engine/ui/SceneUI.h"

enum texture_enum {
	TEX_CRATE, TEX_CRATE_MASK
};

enum material_enum {
	MAT_CRATE,
	MAT_FRAGILE
};

enum mesh_enum {
	MESH_CUBE
};

class TestUI : public SceneUI {
	private:
		void initShaders();
		void initTextures();
		void initMaterials();
		void initModels();

	public:
		TestUI();
		~TestUI();

		void update();
};


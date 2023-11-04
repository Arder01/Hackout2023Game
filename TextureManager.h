#pragma once

//includes
#include<string>
#include  "SDL.h"
#include "SDL_image.h"
#include <map>

class TextureManager
{
public:

	static TextureManager* GetInstance()

	{
		return s_Instacne = (s_Instacne != nullptr) ? s_Instacne : new TextureManager();
	}

	bool Load(std::string id, std::string filename);
	bool ParseTextures(std::string source);
	void Drop(std::string id);
	void Clean();

	void Draw(std::string id, int x, int y, int width, int height, float FlowRatio = 0, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	TextureManager() {}
	std::map<std::string, SDL_Texture*> m_TextureMap;
	static TextureManager* s_Instacne;
};

//#endif //TEXTUREMANGAER_H
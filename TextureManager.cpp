#include "TextureManager.h"
#include "Engine.h"
#include "TinyXml/tinyxml.h"

TextureManager* TextureManager::s_Instacne = nullptr;

bool TextureManager::Load(std::string id, std::string filename)
{
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (surface == nullptr)
	{
		SDL_Log("Failed to load Texture: %s, %s", filename.c_str(), SDL_GetError());
		return  false;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), surface);
	if (texture == nullptr)
	{
		SDL_Log("Failed to create texture from surface: %s, %s", filename.c_str(), SDL_GetError());
		return  false;
	}

	m_TextureMap[id] = texture;

	return  true;

}

bool TextureManager::ParseTextures(std::string source)
{
	TiXmlDocument xml;
	xml.LoadFile(source);
	if (xml.Error())
	{
		std::cout << "Failed to Load: " << source << std::endl;
		return  false;
	}
	TiXmlElement* root = xml.RootElement();
	for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("Textures")) {
			std::string id = e->Attribute("id");
			std::string src = e->Attribute("source");
			Load(id, src);
		}
	}
	return true;
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, float FlowRatio, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { 0,0,width,height };
	SDL_Rect dstRect = { x, y, width * 1, height * 1 };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);

}

void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{

	SDL_Rect srcRect = { width * frame, height * (row - 1),width,height };
	SDL_Rect dstRect = { x , y , width * 1.5, height * 1.5 };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), m_TextureMap[id], &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::DrawTile(std::string tilesetID, int tileSize, int x, int y, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect srcRect = { tileSize * frame, tileSize * (row),tileSize,tileSize };
	SDL_Rect dstRect = { x , y , tileSize, tileSize };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), m_TextureMap[tilesetID], &srcRect, &dstRect, 0, 0, flip);
}

void TextureManager::Drop(std::string id)
{
	SDL_DestroyTexture(m_TextureMap[id]);
	m_TextureMap.erase(id);
}


void TextureManager::Clean()
{
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = m_TextureMap.begin(); it != m_TextureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
	m_TextureMap.clear();
	SDL_Log("Texture Map Cleaned");
}
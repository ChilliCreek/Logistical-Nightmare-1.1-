#include "pch.h"
#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

TextureHolder::~TextureHolder()
{
	for (auto const& [name, texture] : m_Textures) {
		delete texture;
	}
}

sf::Texture& TextureHolder::getTexture(std::string const& filename)
{
	// auto = map<string, Texture>
	auto& texturesRef = m_s_Instance->m_Textures;

	// auto = map<string, Texture>::iterator
	auto keyValuePair = texturesRef.find(filename);

	if (keyValuePair == texturesRef.end()) {
		// auto = Texture
		texturesRef[filename] = new sf::Texture;
		texturesRef[filename]->loadFromFile(filename);
		return *texturesRef[filename];
	}
	else {
		return *(keyValuePair->second);
	}
}

#include "pch.h"
#include "TextureHolder.h"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;
TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::getTexture(std::string const& filename)
{
	// auto = map<string, Texture>
	auto& texturesRef = m_s_Instance->m_Textures;

	// auto = map<string, Texture>::iterator
	auto keyValuePair = texturesRef.find(filename);

	if (keyValuePair == texturesRef.end()) {
		// auto = Texture
		auto& newTexture = texturesRef[filename];
		newTexture.loadFromFile(filename);
		return newTexture;
	}
	else {
		return keyValuePair->second;
	}
}

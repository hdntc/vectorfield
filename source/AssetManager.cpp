#include "AssetManager.hpp"

void AssetManager::load_texture(std::string name, std::string filename) {
	sf::Texture texture;
	
	if (texture.loadFromFile(filename)) {
		this->_textures[name] = texture;
	}
}

sf::Texture& AssetManager::get_texture(std::string name) {
	return this->_textures.at(name);
}

void AssetManager::load_font(std::string name, std::string filename) {
	sf::Font font;

	if (font.loadFromFile(filename)) {
		this->_fonts[name] = font;
	}
}

sf::Font& AssetManager::get_font(std::string name) {
	return this->_fonts.at(name);
}
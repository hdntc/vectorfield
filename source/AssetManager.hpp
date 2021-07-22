#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager {
public:
	void load_texture(std::string name, std::string filename);
	sf::Texture& get_texture(std::string name);

	void load_font(std::string name, std::string filename);
	sf::Font& get_font(std::string name);

private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
};
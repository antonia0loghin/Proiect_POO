#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class non_interactive_prop
{
	private:
		sf::Vector2f Position;
		std::string TextureFile;

	public:
		non_interactive_prop(sf::Vector2f NewPosition, std::string NewTextureFile)
		{
			this->Position = NewPosition;
			this->TextureFile = NewTextureFile;
		}
		void Draw(sf::RenderWindow& window, sf::Vector2f Origin, sf::Vector2f change)
		{
			const sf::Texture texture(this->TextureFile);
			sf::Sprite sprite(texture);
			sprite.setOrigin(Origin);
			sprite.setPosition(change);
			window.draw(sprite);
		}
};
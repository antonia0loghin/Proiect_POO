#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class Player{
	private:
		std::string Name;

		sf::Vector2f OriginPosition;

		std::string BodyTextureFile;
		sf::Vector2f BodyOrigin;
		
		std::string HatTextureFile;
		sf::Vector2f HatPosition;

		std::string ShirtTextureFile;
		sf::Vector2f ShirtPosition;

		std::string PantsTextureFile;
		sf::Vector2f PantsPosition;

		std::string ShoesTextureFile;
		sf::Vector2f ShoesPosition;
		
	public:
		Player(std::string NewName, std::string NewBodyTextureFile, sf::Vector2f NewBodyOrigin, std::string NewHatTextureFile, sf::Vector2f NewHatPosition, std::string NewShirtTextureFile, sf::Vector2f NewShirtPosition, std::string NewPantsTextureFile, sf::Vector2f NewPantsPosition, std::string NewShoesTextureFile, sf::Vector2f NewShoesPosition)
		{
			this->Name = NewName;

			this->BodyTextureFile = NewBodyTextureFile;
			this->BodyOrigin = NewBodyOrigin;

			this->HatTextureFile = NewHatTextureFile;
			this->HatPosition = NewHatPosition;

			this->ShirtTextureFile = NewShirtTextureFile;
			this->ShirtPosition = NewShirtPosition;

			this->PantsTextureFile = NewPantsTextureFile;
			this->PantsPosition = NewPantsPosition;

			this->ShoesTextureFile = NewShoesTextureFile;
			this->ShoesPosition = NewShoesPosition;
		}
		void Draw(sf::RenderWindow& window)
		{
			non_interactive_prop Body(this->BodyOrigin, this->BodyTextureFile);
			Body.Draw(window, this->BodyOrigin, {0,0});

			non_interactive_prop Hat(this->HatPosition, this->HatTextureFile);
			Hat.Draw(window, this->BodyOrigin, this->HatPosition);

			non_interactive_prop Shirt(this->ShirtPosition, this->ShirtTextureFile);
			Shirt.Draw(window, this->BodyOrigin, this->ShirtPosition);

			non_interactive_prop Pants(this->PantsPosition, this->PantsTextureFile);
			Pants.Draw(window, this->BodyOrigin, this->PantsPosition);

			non_interactive_prop Shoes(this->ShoesPosition, this->ShoesTextureFile);
			Shoes.Draw(window, this->BodyOrigin, this->ShoesPosition);

		}
		
		
		
};
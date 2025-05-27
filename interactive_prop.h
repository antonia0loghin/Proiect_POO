#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



class interactive_prop {
private:
	int State;///0=open, 1=close, 2=working

	//object position
	sf::Vector2f Position;


	///object image sources
	std::string TextureFile;


	//object sound source
	std::string ClosingSoundFile;
	std::string OpeningSoundFile;
	std::string WorkingSoundFile;
	sf::Texture Texture;

	sf::IntRect CurrentFrame;

public:
	std::string GetTexture()
	{
		return this->TextureFile;
	}
	void Draw(sf::RenderWindow &window, int a, int b, int c, int d)
	{ 
		sf::Sprite sprite(this->Texture);
		sprite.setPosition(this->Position);
		sprite.setTextureRect(sf::IntRect({ a, b }, { c, d }));
		window.draw(sprite);
		
	}
	interactive_prop(sf::RenderWindow &window, sf::Vector2f NewPosition, std::string NewTextureFile, std::string NewClosingSoundFile, std::string NewOpeningSoundFile, std::string NewWorkingSoundFile)
	{
		this->State = 0;
		this->Position = NewPosition;
		this->TextureFile = NewTextureFile;

		//this->Image.loadFromFile(this->TextureFile);

		this->ClosingSoundFile = NewClosingSoundFile;
		this->OpeningSoundFile = NewOpeningSoundFile;
		this->WorkingSoundFile = NewWorkingSoundFile;
		this->Texture.loadFromFile(this->TextureFile);
		window.clear();
		this->Draw(window,  432, 0 ,  432, 496 );

	}
	
	
	void Update(sf::RenderWindow& window)
	{
		if (this->State == 0)
		{
			
			this->Draw(window, 432, 0, 432, 496 );
		}
		else
		{
			this->Draw(window, 0, 0 , 432, 496 );
		}
	}
	void SoundPlay(std::string File)
	{
		const sf::SoundBuffer Buffer(File);
		sf::Sound sound(Buffer);
		sound.play();
	}

	int GetState()
	{
		return this->State;
	}


	void Open(sf::RenderWindow& window)
	{
		this->State = 0;
		this->SoundPlay(this->OpeningSoundFile);
		this->Update(window);
	}

	void Close(sf::RenderWindow& window)
	{
		this->State = 1;
		//this->SoundPlay(this->ClosingSoundFile);
		this->Update(window);
	}

	void Work(sf::RenderWindow& window)
	{
		this->State = 2;
		this->SoundPlay(this->WorkingSoundFile);
	}


};
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <sstream>

int main()
{
	//Create the rendering window
	sf::RenderWindow Pong(sf::VideoMode(1200, 600, 32), "Pong");
	
	//Load the sprite image from a file
	sf::Image PaddleImage;
	if (!PaddleImage.LoadFromFile("paddle.png"))
		return EXIT_FAILURE;
		
	sf::Image BallImage;
	if (!BallImage.LoadFromFile("ball.png"))
		return EXIT_FAILURE;
		
	//Create the Sprites
	sf::Sprite PaddleSpriteLeft(PaddleImage);	
	PaddleSpriteLeft.SetPosition(20.f, 250.f);
	
	sf::Sprite PaddleSpriteRight(PaddleImage);
	PaddleSpriteRight.SetPosition(1150.f, 250.f);
	
	sf::Sprite BallSprite(BallImage);
	BallSprite.SetPosition(570.f, 250.f);
	
	float VelocityX = 200.f;
	float VelocityY = 100.f;
			
	int ScoreLeft = 0;
	int ScoreRight = 0;	
	
	//position the initial Score
	sf::String Score;
	Score.SetText("Score:  0 | 0");
	Score.SetFont(sf::Font::GetDefaultFont());	
	Score.SetPosition(530.f, 10.f);
	
	sf::SoundBuffer Buffer;
	if (!Buffer.LoadFromFile("bip.ogg"))
	{
    // Do nothing - the game is playable without sound
	}
	sf::Sound Beep;
	Beep.SetBuffer(Buffer);
	
	while (Pong.IsOpened())
	{
		sf::Event Event;
		while (Pong.GetEvent(Event))
		{
		  //Close window : exit
			if (Event.Type == sf::Event::Closed)
				Pong.Close();
			
			//Escape key : exit	
			if ((Event.Type == sf::Event::KeyPressed) 
			&& (Event.Key.Code == sf::Key::Escape))
				Pong.Close();
		}
		
		//Get elapsed time
		float ElapsedTime = Pong.GetFrameTime();
		
		//Move the left paddle
		if (Pong.GetInput().IsKeyDown(sf::Key::W))
		  if (PaddleSpriteLeft.GetPosition().y > 0)
  			PaddleSpriteLeft.Move(0, -250 * ElapsedTime);
			
		if (Pong.GetInput().IsKeyDown(sf::Key::S))
		  if (PaddleSpriteLeft.GetPosition().y < 500)
				PaddleSpriteLeft.Move(0, 250 * ElapsedTime);
			
		//Move the right paddle
		if (Pong.GetInput().IsKeyDown(sf::Key::Up))
		  if (PaddleSpriteRight.GetPosition().y > 0)
		  	PaddleSpriteRight.Move(0, -250 * ElapsedTime);
			
		if (Pong.GetInput().IsKeyDown(sf::Key::Down))
			if (PaddleSpriteRight.GetPosition().y < 500)
				PaddleSpriteRight.Move(0, 250 * ElapsedTime);	
		
		//Move the ball with collision detection	
		BallSprite.Move(VelocityX * ElapsedTime, VelocityY * ElapsedTime);
		if (BallSprite.GetPosition().x < 1)
		{
		  ScoreRight++;
			std::stringstream stream;
			stream << "Score:  " << ScoreLeft << " | " << ScoreRight;
			std::string result = stream.str();

			Score.SetText(result);
			sf::Sleep(0.7f); 
		  BallSprite.SetPosition(570.f, 250.f);
		  VelocityX = 200.f;
	    VelocityY = -100.f;
		}
		
		if (BallSprite.GetPosition().x >1170)
		{
			ScoreLeft++;
			std::stringstream	stream (std::stringstream::in | std::stringstream::out);
			stream << "Score:  " << ScoreLeft << " | " << ScoreRight;
			std::string result = stream.str();

			Score.SetText(result);
			sf::Sleep(0.7f); 
		  BallSprite.SetPosition(570.f, 250.f);
		  VelocityX = -200.f;
	    VelocityY = 100.f;
		}
		 
		if (BallSprite.GetPosition().y < 0 || BallSprite.GetPosition().y > 570)
		{
		  VelocityY *= -1.;
			Beep.Play();
		}
		if (BallSprite.GetPosition().x < 48 && BallSprite.GetPosition().x > 20 
				&& BallSprite.GetPosition().y > PaddleSpriteLeft.GetPosition().y
				&& BallSprite.GetPosition().y < PaddleSpriteLeft.GetPosition().y + 			        100)
		{
		  VelocityX *= -1.2;
			Beep.Play();
		}
		
		if (BallSprite.GetPosition().x > 1122 && BallSprite.GetPosition().x < 1150 				&& BallSprite.GetPosition().y > PaddleSpriteRight.GetPosition().y
				&& BallSprite.GetPosition().y < PaddleSpriteRight.GetPosition().y + 						100)
		{
		  VelocityX *= -1.2;
			Beep.Play();		
		}		  
		//Clear the screen
		Pong.Clear();
		
		Pong.Draw(PaddleSpriteLeft);
		Pong.Draw(PaddleSpriteRight);
		Pong.Draw(BallSprite);
		Pong.Draw(Score);
		
		Pong.Display();
		
	}
	
	std::cout << "Final Score:  " << ScoreLeft << " | " << ScoreRight << 			     std::endl;
	return EXIT_SUCCESS;
	 
}

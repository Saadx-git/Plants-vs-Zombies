#include <iostream>
#include <ctime>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.
// Don't edit unless required. Use functions on lines 43, 44, 45 for resizing the game window.
const int resolutionX = 960;
const int resolutionY = 960;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};

// The following exist purely for readability.
const int x = 0;
const int y = 1;
const int exists = 2;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

//Player Related
void movePlayer(float player[], const float playervelocity);
void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite);

//Bullet Related
void moveBullet(float bullet[], sf::Clock& bulletClock, const float firevelocity);
void drawBullet(sf::RenderWindow& window, float bullet[], float player[], sf::Sprite& bulletSprite);

//Centipede Related
void initializeCentipede(float centipede[][4], sf::Texture& centipedeTexture, sf::Texture& centipedeheadTexture, sf::Sprite centipedeSprite[], int bodyparts, int maxbodyparts);
void drawcentipede(sf::RenderWindow& window, float centipede[], sf::Sprite centipedeSprite[], int n);
void movecentipede(float centipede[][4], bool& shift, float mushroom[][3], float cvelocity, int bodyparts, const int mushrooms);

//Mushroom Related
void initializeMushrooms(float mushroom[][3], sf::Texture& mushroomTexture, sf::Sprite mushroomSprite[], const int mushrooms, int mushroomhealth[], int m);
void drawmushroom(sf::RenderWindow& window, float mushroom[][3], sf::Sprite mushroomSprite[], const int mushrooms);

//All Collisions
void collision(sf::RenderWindow& window, float centipede[][4], float bullets[][3], sf::Sprite centipedeSprite[], sf::Texture& centipedeheadTexture, float cvelocity, const int maxbodyparts,
	const int maxBullets, float mushroom[][3], const int mushrooms, int& m, int& points, sf::Sprite mushroomSprite[]);
void playerCollision(float player[], float centipede[][4], int bodyparts, float mushroom[][3], int mushroomhealth[], int points);
void mushroomcollision(sf::RenderWindow& window, float mushroom[][3], float bullets[][3], const int maxBullets, const int mushrooms, int mushroomhealth[], int& points, sf::Sprite mushroomSprite[]);
void playermushroomcollision(sf::RenderWindow& window, int points, float player[], float mushroom[][3], int mushrooms);
void spiderplayercollision(sf::RenderWindow& window, int points, float player[], float spider[], int& highestpoints);
void spiderbulletcollision(sf::RenderWindow& window, float spider[], float bullets[][3], sf::Sprite& spiderSprite, int& points, int maxbullets, float player[]);
void spidermushroomcollision(float spider[], float mushroom[][3], int mushrooms, sf::Sprite mushroomSprite[]);
void scorpionPlayerCollision(sf::RenderWindow& window, int points, float player[], float scorpion[], int& highestpoints);

//Spider Related
void initializeSpider(float spider[], sf::Texture& spiderTexture, sf::Sprite& spiderSprite);
void drawSpider(sf::RenderWindow& window, float spider[], sf::Sprite& spiderSprite);
void moveSpider(float spider[], float& spiderVelocityX, float& spiderVelocityY);

//Scorpion Related
void initializeScorpion(float scorpion[], sf::Texture& scorpionTexture, sf::Sprite& scorpionSprite);
void drawScorpion(sf::RenderWindow& window, float scorpion[], sf::Sprite& scorpionSprite);
void movescorpion(sf::RenderWindow& window, float scorpion[], float scorpionvelocity, float mushroom[][3], const int mushrooms, sf::Sprite mushroomSprite[], sf::Texture& poisonmushroomTexture);
void scorpionBulletCollision(float scorpion[], float bullets[][3], const int maxBullets, int& points);

//Points Related
void displayPoints(sf::RenderWindow& window, int points, int fontsize);
void saveScore(int score);
void readHighestScore(int& highestpoints, int points);
void displayhighestPoints(sf::RenderWindow& window, int highestpoints, int fontsize);

int main()
{
	// 23i-0822 Saad Azhar CS-E
	cout << "Roll no: 23i-0822." << endl << "Name: Saad Azhar" << endl << "Section: CS-E" << endl;
	srand(time(0));

	//  Variables . Strings(ropes) that change the output
	const float playervelocity = 10;
	const float firevelocity = 40;
	const int maxBullets = 1;

	int centipedeparts = 12;
	float cvelocity = 0.3;
	int bodyparts = centipedeparts + 1;
	const int maxbodyparts = 50;

	float spidervelocityX = 1.5;
	float spidervelocityY = 1.5;

	float scorpionvelocity = 5;

	const int mushrooms = 100;
	int m = (rand() % 11) + 20;
	int mushroomhealth[mushrooms];

	int level;

	int fontsize = 30;
	int points = 0;
	int highestpoints = 0;

	// Declaring RenderWindow.
	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Centipede", sf::Style::Close | sf::Style::Titlebar);

	// Used to resize your window if it's too big or too small. Use according to your needs.
	window.setSize(sf::Vector2u(640, 640)); // Recommended for 1366x768 (768p) displays.
	// window.setSize(sf::Vector2u(1280, 1280)); // Recommended for 2560x1440 (1440p) displays.
	// window.setSize(sf::Vector2u(1920, 1920)); // Recommended for 3840x2160 (4k) displays.

	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(sf::Vector2i(400, 0));

	// Initializing Background Music.
	sf::Music bgMusic;
	bgMusic.openFromFile("Music/field_of_hopes.ogg");
	bgMusic.play();
	bgMusic.setVolume(25);

	// Initializing Background.
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/pxfuel.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setColor(sf::Color(255, 255, 255, 255 * 0.4)); // Reduces Opacity to 25%

	// Initializing Player and Player Sprites.
	float player[2] = {};
	player[x] = (gameColumns / 2) * boxPixelsX;
	player[y] = (gameColumns * 7 / 8) * boxPixelsY;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	playerTexture.loadFromFile("Textures/spaceship.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	playerSprite.setScale(1.3f, 1.3f);

	// Initializing Mushroom and Mushroom Sprites.
	float mushroom[mushrooms][3] = {};
	sf::Texture mushroomTexture;
	sf::Sprite mushroomSprite[mushrooms];

	initializeMushrooms(mushroom, mushroomTexture, mushroomSprite, mushrooms, mushroomhealth, m);

	int mx[mushrooms];
	int my[mushrooms];

	for (int i = 0; i < mushrooms; i++)
	{
		mx[i] = mushroom[i][x];
		my[i] = mushroom[i][y];
	}

	// Initializing centipede and centipede Sprites.
	bool shift = false;
	float centipede[maxbodyparts][4] = {};

	sf::Texture centipedeTexture;
	sf::Texture centipedeheadTexture;
	sf::Sprite centipedeSprite[maxbodyparts];

	initializeCentipede(centipede, centipedeTexture, centipedeheadTexture, centipedeSprite, bodyparts, maxbodyparts);

	// Initializing Bullet and Bullet Sprites.
	int currentbullet = 0;
	float bullets[maxBullets][3] = {};
	for (int i = 0; i < maxBullets; i++) {
		bullets[i][x] = -4004;
		bullets[i][y] = 4004;
		bullets[i][exists] = false;
	}
	sf::Clock bulletClock;
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/fire.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	//Initializing Spider
	float spider[3] = {};
	sf::Texture spiderTexture;
	sf::Sprite spiderSprite;
	initializeSpider(spider, spiderTexture, spiderSprite);

	// Initializing Scorpion
	float scorpion[4] = {};
	sf::Texture scorpionTexture;
	sf::Sprite scorpionSprite;

	sf::Texture poisonmushroomTexture;
	poisonmushroomTexture.loadFromFile("Textures/mushroom.png");

	initializeScorpion(scorpion, scorpionTexture, scorpionSprite);

	///////////////////////////////////////////////////////////////
	//                                                           //
	// Game.............. 					        			 //
	// 										................Loop //
	//                                                           //
	///////////////////////////////////////////////////////////////

	while (window.isOpen()) {
		window.setFramerateLimit(60);
		///////////////////////////////////////////////////////////////
		//                                                           //
		// Call Your Functions Here. Some have been written for you. //
		// Be vary of the order you call them, SFML draws in order.  //
		//                                                           //
		///////////////////////////////////////////////////////////////
		window.draw(backgroundSprite);
		for (int i = 0; i < mushrooms; i++)
		{
			drawmushroom(window, mushroom, mushroomSprite, mushrooms);
		}

		drawPlayer(window, player, playerSprite);

		mushroomcollision(window, mushroom, bullets, maxBullets, mushrooms, mushroomhealth, points, mushroomSprite);

		for (int i = 0; i < bodyparts; i++) {
			if (centipede[i][3] == true) {
				drawcentipede(window, centipede[i], centipedeSprite, i);
				movecentipede(centipede, shift, mushroom, cvelocity, bodyparts, mushrooms);
			}
		}

		drawSpider(window, spider, spiderSprite);
		moveSpider(spider, spidervelocityX, spidervelocityY);

		drawScorpion(window, scorpion, scorpionSprite);
		movescorpion(window, scorpion, scorpionvelocity, mushroom, mushrooms, mushroomSprite, poisonmushroomTexture);
		scorpionBulletCollision(scorpion, bullets, maxBullets, points);


		for (int i = 0; i < mushrooms; i++)
		{
			if (mushroom[i][exists] == 1) {
				mushroom[i][x] = mx[i];
				mushroom[i][y] = my[i];
			}
		}

		displayPoints(window, points, fontsize);
		readHighestScore(highestpoints, points);
		displayhighestPoints(window, highestpoints, fontsize);

		movePlayer(player, playervelocity);
		//cout << "moveplayer done " << endl;

		//Bullet System
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
			for (int i = 0; i < maxBullets; ++i) {
				if (bullets[i][exists] == false) {
					if (bulletClock.getElapsedTime().asMilliseconds() < 50) {}
					else {

						bullets[i][exists] = true;
						bullets[i][x] = player[x];
						bullets[i][y] = player[y] - boxPixelsY;
						currentbullet = i;

						break;
					}
				}
			}
		}

		if (bullets[currentbullet][exists] == false) {
			bullets[currentbullet][x] = -4000;
			bullets[currentbullet][y] = -4000;
		}



		for (int i = 0; i < maxBullets; ++i) {
			if (bullets[i][exists]) {
				drawBullet(window, bullets[i], player, bulletSprite);
				moveBullet(bullets[i], bulletClock, firevelocity);
			}
		}
		collision(window, centipede, bullets, centipedeSprite, centipedeheadTexture, cvelocity, bodyparts, maxBullets, mushroom, mushrooms, m, points, mushroomSprite);

		playermushroomcollision(window, points, player, mushroom, mushrooms);

		spiderplayercollision(window, points, player, spider, highestpoints);

		spiderbulletcollision(window, spider, bullets, spiderSprite, points, maxBullets, player);

		playerCollision(player, centipede, bodyparts, mushroom, mushroomhealth, points);

		spidermushroomcollision(spider, mushroom, mushrooms, mushroomSprite);

		scorpionPlayerCollision(window, points, player, scorpion, highestpoints);


		//Bullet System


		//Next Level System
		level = 0;
		centipede[0][3] = false;
		for (int i = 0; i < bodyparts; i++)
		{
			if (centipede[i][3] == true) {
				level = 0;
				break;
			}
			else {
				level = 1;
			}
		}
		if (level == 1) {
			level = 0;
			bodyparts += 1;
			if (m < (mushrooms - (0.2 * m))) {
				m += (0.2 * m);
			}
			initializeMushrooms(mushroom, mushroomTexture, mushroomSprite, mushrooms, mushroomhealth, m);
			initializeSpider(spider, spiderTexture, spiderSprite);
			initializeScorpion(scorpion, scorpionTexture, scorpionSprite);

			cvelocity += cvelocity;
			if (bodyparts > 1) {
				bodyparts -= 1;
			}
			//maxBullets++;
			for (int i = 0; i < bodyparts; i++) {
				centipede[i][x] = (i)*boxPixelsX;
				centipede[i][y] = (gameColumns - 30) * boxPixelsY;
				centipede[i][2] = 1;
				centipede[i][3] = true;
			}
			for (int i = 0; i < bodyparts; i++) {
				if (i == (1)) {
					centipedeSprite[i].setTexture(centipedeheadTexture);
					centipedeSprite[i].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
				}
				else {
					centipedeSprite[i].setTexture(centipedeTexture);
					centipedeSprite[i].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
				}
			}
		}
		//Next Level System


		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				saveScore(points);
				return 0;
			}
		}
		window.display();
		window.clear();
	}
}

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// 								Initialize Functions	                   //
//  					Used to initialize the objects in game       	   //
/////////////////////////////////////////////////////////////////////////////
void initializeMushrooms(float mushroom[][3], sf::Texture& mushroomTexture, sf::Sprite mushroomSprite[], const int mushrooms, int mushroomhealth[], int m) {
	mushroomTexture.loadFromFile("Textures/mushroom.png");
	for (int i = 0; i < mushrooms; i++) {
		mushroom[i][exists] = 0;
		mushroomhealth[i] = 0;
		mushroomSprite[i].setTexture(mushroomTexture);
		mushroomSprite[i].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
		mushroom[i][3] = 1;
	}

	/////////////////////////////////////////////////////////////////////////////
	//                                                                         //
	// 	This funtion works to initialize the mushrooms as an  array 		   //
	//  that has elements that show the properties of each fragment      	   //
	/////////////////////////////////////////////////////////////////////////////


	for (int i = 0; i < m; i++) {
		mushroom[i][x] = (rand() % (gameColumns - 2) + 1) * boxPixelsX;
		mushroom[i][y] = (rand() % gameColumns) * boxPixelsY;
		mushroom[i][exists] = 1;
	}
}
void initializeCentipede(float centipede[][4], sf::Texture& centipedeTexture, sf::Texture& centipedeheadTexture, sf::Sprite centipedeSprite[], int bodyparts, int maxbodyparts) {


	/////////////////////////////////////////////////////////////////////////////
	//                                                                         //
	// 	This funtion works to initialize the centipede as an array 		       //
	//  that has elements that show the properties of each fragment      	   //
	/////////////////////////////////////////////////////////////////////////////

	int xpos = (rand() % 12) + 1;
	for (int i = 0; i < bodyparts; i++) {
		centipede[i][x] = (xpos++) * boxPixelsX;
		centipede[i][y] = (gameColumns - 30) * boxPixelsY;
		centipede[i][2] = 0;
		centipede[i][3] = true;
	}
	centipede[0][3] = false;

	centipedeTexture.loadFromFile("Textures/c_body.png");
	centipedeheadTexture.loadFromFile("Textures/c_head.png");

	for (int i = 0; i < maxbodyparts; i++) {
		if (i == (1)) {
			centipedeSprite[i].setTexture(centipedeheadTexture);
			centipedeSprite[i].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
		}
		else {
			centipedeSprite[i].setTexture(centipedeTexture);
			centipedeSprite[i].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
		}
	}
}
void initializeSpider(float spider[], sf::Texture& spiderTexture, sf::Sprite& spiderSprite) {

	/////////////////////////////////////////////////////////////////////////////
	//                                                                         //
	// 	This funtion works to initialize the spider    as an  array 		   //
	//  that has elemests that show the properties of each fragment      	   //
	/////////////////////////////////////////////////////////////////////////////
	spiderTexture.loadFromFile("Textures/spider_score.png");
	spiderSprite.setTexture(spiderTexture);
	spiderSprite.setTextureRect(sf::IntRect(0, 0, (2 * boxPixelsX), boxPixelsY));
	//spiderSprite.setScale(1.3f,1.3f);

	spider[x] = (rand() % (gameColumns)) * boxPixelsX;
	spider[y] = ((rand() % (gameRows - 25)) + 25) * boxPixelsY;
	spider[exists] = true;
}
void initializeScorpion(float scorpion[], sf::Texture& scorpionTexture, sf::Sprite& scorpionSprite) {

	/////////////////////////////////////////////////////////////////////////////
	//                                                                         //
	// 	This funtion works to initialize the scorpion   as an  array 		   //
	//  that has elemests that show the properties of each fragment      	   //
	/////////////////////////////////////////////////////////////////////////////
	scorpionTexture.loadFromFile("Textures/scorpion.png");
	scorpionSprite.setTexture(scorpionTexture);
	scorpionSprite.setTextureRect(sf::IntRect(0, 0, (boxPixelsX * 2), boxPixelsY));
	//scorpionSprite.setScale(1.3f, 1.3f);

	scorpion[x] = (rand() % (gameColumns)) * boxPixelsX;
	scorpion[y] = (rand() % (gameRows)) * boxPixelsY;


	scorpion[exists] = true;
	scorpion[3] = 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// 								Draw Functions		                       //
//  					Used to draw the objects in the Game         	   //
/////////////////////////////////////////////////////////////////////////////
void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite) {

	playerSprite.setPosition(player[x], player[y]);
	window.draw(playerSprite);
}
void drawBullet(sf::RenderWindow& window, float bullet[], float player[], sf::Sprite& bulletSprite) {

	bulletSprite.setPosition(bullet[x], bullet[y]);
	window.draw(bulletSprite);
}
void drawcentipede(sf::RenderWindow& window, float centipede[], sf::Sprite centipedeSprite[], int n) {

	centipedeSprite[n].setPosition(centipede[x], centipede[y]);
	window.draw(centipedeSprite[n]);
}

void drawmushroom(sf::RenderWindow& window, float mushroom[][3], sf::Sprite mushroomSprite[], const int mushrooms) {
	for (int i = 0; i < mushrooms; i++)
	{
		if (mushroom[i][exists] == 1)
		{
			mushroomSprite[i].setPosition(mushroom[i][x], mushroom[i][y]);
			window.draw(mushroomSprite[i]);
		}
	}
}
void drawSpider(sf::RenderWindow& window, float spider[], sf::Sprite& spiderSprite) {
	if (spider[exists]) {
		spiderSprite.setPosition(spider[x], spider[y]);
		window.draw(spiderSprite);
	}
}
void drawScorpion(sf::RenderWindow& window, float scorpion[], sf::Sprite& scorpionSprite) {
	if (scorpion[exists]) {
		scorpionSprite.setPosition(scorpion[x], scorpion[y]);
		window.draw(scorpionSprite);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// 								Move  Functions		                       //
//  					Used to draw the objects in the Game         	   //
/////////////////////////////////////////////////////////////////////////////
void moveBullet(float bullet[], sf::Clock& bulletClock, const float firevelocity) {

	bullet[y] -= firevelocity;
	if (bullet[y] < 0) {
		bullet[exists] = false;
	}
}
void movePlayer(float player[], const float playervelocity) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player[y] > 0) {
		player[y] -= playervelocity;
		if (player[y] < (25 * boxPixelsY))
		{
			player[y] += playervelocity;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player[y] < resolutionY - boxPixelsY) {
		player[y] += playervelocity;
		if (player[y] > resolutionY)
		{
			player[y] -= playervelocity;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player[x] > 0) {
		player[x] -= playervelocity;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player[x] < resolutionX - boxPixelsX) {
		player[x] += playervelocity;
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player[y] > 0) {
		player[y] -= playervelocity;
		if (player[y] < (25 * boxPixelsY))
		{
			player[y] += playervelocity;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player[y] < resolutionY - boxPixelsY) {
		player[y] += playervelocity;
		if (player[y] > resolutionY)
		{
			player[y] -= playervelocity;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player[x] > 0) {
		player[x] -= playervelocity;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player[x] < resolutionX - boxPixelsX) {
		player[x] += playervelocity;
	}
}
void movecentipede(float centipede[][4], bool& shift, float mushroom[][3], float cvelocity, int bodyparts, const int mushrooms) {
	for (int i = 0; i < bodyparts; i++) {
		if (centipede[i][2] == 0) {
			centipede[i][x] -= cvelocity;
		}
		else {
			centipede[i][x] += cvelocity;
		}

		for (int k = 0; k < mushrooms; k++) {
			if (centipede[i][3] == true) {
				if ((centipede[i][x] <= mushroom[k][x] + boxPixelsX) &&
					(centipede[i][x] + boxPixelsX >= mushroom[k][x]) &&
					(centipede[i][y] == mushroom[k][y])) {

					centipede[i][y] += boxPixelsY;

					if (centipede[i][2] == 0) {
						centipede[i][2] = 1;
					}
					else {
						centipede[i][2] = 0;
					}
				}
			}
		}

		if (centipede[i][3] == true) {
			if ((centipede[i][x] >= resolutionX) || (centipede[i][x] <= 0)) {
				if (i != 0) {
					if (((centipede[i][x] == 960) && (centipede[i][y] == 960)) || ((centipede[i][x] <= 0) && (centipede[i][y] >= 960))) {
						centipede[i][x] = 2;
						centipede[i][y] = 25 * boxPixelsY;
						centipede[i][2] = 1;
					}
					else {
						centipede[i][y] += boxPixelsY;
						if (centipede[i][2] == 0) {
							centipede[i][2] = 1;
						}
						else {
							centipede[i][2] = 0;
						}
					}
				}
			}
		}
	}
}

void moveSpider(float spider[], float& spiderVelocityX, float& spiderVelocityY) {

	if (spider[exists]) {
		spider[x] += spiderVelocityX;
		spider[y] += spiderVelocityY;

		if (spider[x] <= 0 || spider[x] >= resolutionX - boxPixelsX) {
			spiderVelocityX = -1 * spiderVelocityX;
			spider[x] += spiderVelocityX;
		}

		if (spider[y] <= 800 || spider[y] >= resolutionY - boxPixelsY) {
			spiderVelocityY = -1 * spiderVelocityY;
			spider[y] += spiderVelocityY;
		}
	}
}
void movescorpion(sf::RenderWindow& window, float scorpion[], float scorpionvelocity, float mushroom[][3], const int mushrooms, sf::Sprite mushroomSprite[]
	, sf::Texture& poisonmushroomTexture) {
	if (scorpion[3] == 1) {
		scorpion[x] += scorpionvelocity;
	}
	else {
		scorpion[x] -= scorpionvelocity;
	}

	if (scorpion[x] >= resolutionX || scorpion[x] <= 0) {
		scorpion[y] += boxPixelsY;
		scorpion[3] = 1 - scorpion[3];
	}
	if ((scorpion[x] == 960 && scorpion[y] == 960) || (scorpion[x] <= 0 && scorpion[y] >= 960)) {
		scorpion[x] = 2;
		scorpion[y] = 25 * boxPixelsY;
		scorpion[3] = 1;
	}


	for (int k = 0; k < mushrooms; k++) {
		if (scorpion[exists] == true) {
			if ((scorpion[x] <= mushroom[k][x] + boxPixelsX) &&
				(scorpion[x] + boxPixelsX >= mushroom[k][x]) &&
				(scorpion[y] == mushroom[k][y])) {

				mushroom[k][3] = 0;
				mushroomSprite[k].setTexture(poisonmushroomTexture);
				mushroomSprite[k].setTextureRect(sf::IntRect(0, 32, boxPixelsX, boxPixelsY));
				window.draw(mushroomSprite[k]);
				window.display();
				break;
			}
		}
	}


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// 								Collision  Functions		               //
//  					Collisions between objects in the Game         	   //
/////////////////////////////////////////////////////////////////////////////
void scorpionBulletCollision(float scorpion[], float bullets[][3], const int maxBullets, int& points) {
	for (int i = 0; i < maxBullets; i++) {
		if ((bullets[i][x] < scorpion[x] + boxPixelsX) &&
			(bullets[i][x] + boxPixelsX > scorpion[x]) &&
			(bullets[i][y] < scorpion[y] + boxPixelsY) &&
			(bullets[i][y] + boxPixelsY > scorpion[y])) {

			bullets[i][exists] = false;
			scorpion[exists] = false;

			points += 1000;

			scorpion[x] = -10000;
			scorpion[y] = -10000;
			break;
		}
	}
}

void collision(sf::RenderWindow& window, float centipede[][4], float bullets[][3], sf::Sprite centipedeSprite[], sf::Texture& centipedeheadTexture, float cvelocity, const int maxbodyparts,
	const int maxBullets, float mushroom[][3], const int mushrooms, int& m, int& points, sf::Sprite mushroomSprite[]) {

	for (int i = 0; i < maxBullets; i++)
	{
		for (int j = 0; j < maxbodyparts; j++)
		{
			if ((bullets[i][x] < centipede[j][x] + boxPixelsX) &&
				(bullets[i][x] + boxPixelsX > centipede[j][x]) &&
				(bullets[i][y] < centipede[j][y] + boxPixelsY) &&
				(bullets[i][y] + boxPixelsY > centipede[j][y])) {

				bullets[i][exists] = false;
				centipede[j][3] = false;

				m += 1;
				if (m == 100) {
					m = 0;
				}

				mushroom[m][x] = centipede[j][x];
				mushroom[m][y] = centipede[j][y];
				mushroom[m][exists] = 1;

				if (mushroom[m][y] >= 25 * boxPixelsY) {
					mushroomSprite[m].setTextureRect(sf::IntRect(0, 32, boxPixelsX, boxPixelsY));
					window.draw(mushroomSprite[m]);
				}

				centipede[j][x] = -200;
				centipede[j][y] = -200;


				//centipede[j-2][3] == true &&
									// int nhead=0;
									// for (int i2 = j+1; i2 < maxbodyparts; i2++)
									// {
									// 	if(centipede[i2][3] == true){
									// 		nhead = i2;
									// 		break;
									// 	}
									// }


				if (centipede[j + 2][3] == true && centipede[j + 1][3] == true) {
					centipedeSprite[j + 1].setTexture(centipedeheadTexture);
					centipedeSprite[j + 1].setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
				}

				for (int k = (j - 1); k > 0; k--) {
					if (centipede[k][3] == false) {
						break;
					}
					if (centipede[k][2] == 0) {
						centipede[k][2] = 1;
					}
					else if (centipede[k][2] == 1) {
						centipede[k][2] = 0;
					}
				}

				if (centipede[j + 1][3]) {
					points += 10;
				}
				else {
					points += 20;
				}

				bullets[i][x] = -500;
				//cvelocity +=0.01;

				break;
			}
		}

	}
	for (int i = 0; i < mushrooms; i++)
	{

		if (mushroom[i][x] <= 0 + boxPixelsX && mushroom[i][y] == 0) {
			mushroom[i][x] = -100;
		}
	}


}
void mushroomcollision(sf::RenderWindow& window, float mushroom[][3], float bullets[][3], const int maxBullets, const int mushrooms, int mushroomhealth[], int& points, sf::Sprite mushroomSprite[]) {

	for (int i = 0; i < maxBullets; i++)
	{
		for (int j = 0; j < mushrooms; j++)
		{
			if ((bullets[i][x] < mushroom[j][x] + boxPixelsX) &&
				(bullets[i][x] + boxPixelsX > mushroom[j][x]) &&
				(bullets[i][y] < mushroom[j][y] + boxPixelsY) &&
				(bullets[i][y] + boxPixelsY > mushroom[j][y])) {
				mushroomhealth[j] += 1;

				if (mushroomhealth[j] == 1) {
					if (mushroom[j][y] > 25 * boxPixelsY) {
						mushroomSprite[j].setTextureRect(sf::IntRect(64, 32, boxPixelsX, boxPixelsY));
						window.draw(mushroomSprite[j]);
					}
					else {
						mushroomSprite[j].setTextureRect(sf::IntRect(64, 0, boxPixelsX, boxPixelsY));
						window.draw(mushroomSprite[j]);
					}
				}

				if (mushroomhealth[j] == 2) {
					mushroom[j][exists] = 0;
					mushroom[j][x] = -600;
					mushroom[j][y] = -500;
					mushroomhealth[j] = 0;
					points += 1;
				}

				bullets[i][x] = -500;
				bullets[i][y] = -500;
				bullets[i][exists] = false;
				break;
			}
		}

	}

}
void playerCollision(float player[], float centipede[][4], int bodyparts, float mushroom[][3], int mushroomhealth[], int points) {
	int collisionBuffer = 12;
	for (int i = 0; i < bodyparts; i++) {
		if ((centipede[i][x] <= player[x] + boxPixelsX - collisionBuffer) &&
			(centipede[i][x] + boxPixelsX >= player[x] + collisionBuffer) &&
			(centipede[i][y] <= player[y] + boxPixelsY - collisionBuffer) &&
			(centipede[i][y] + boxPixelsY >= player[y] + collisionBuffer)) {

			cout << "Game Over - Player collided with the centipede!" << endl;
			saveScore(points);
			exit(0);
		}
	}
}
void playermushroomcollision(sf::RenderWindow& window, int points, float player[], float mushroom[][3], int mushrooms) {
	for (int i = 0; i < mushrooms; i++) {
		if ((mushroom[i][3] == 0 &&
			player[x] <= mushroom[i][x] + boxPixelsX) &&
			(player[x] + boxPixelsX >= mushroom[i][x]) &&
			(player[y] <= mushroom[i][y] + boxPixelsY) &&
			(player[y] + boxPixelsY >= mushroom[i][y])) {
			saveScore(points);
			cout << "Game Over - Player collided with the Poisonous Mushroom!" << endl;
			window.display();
			window.clear();
			exit(0);
		}
	}
}
void spiderplayercollision(sf::RenderWindow& window, int points, float player[], float spider[], int& highestpoints) {
	if ((spider[x] <= player[x] + boxPixelsX) &&
		(spider[x] + boxPixelsX >= player[x]) &&
		(spider[y] <= player[y] + boxPixelsY) &&
		(spider[y] + boxPixelsY >= player[y])) {

		saveScore(points);
		cout << "Game Over - Player collided with the spider!" << endl;
		exit(0);
	}
}
void scorpionPlayerCollision(sf::RenderWindow& window, int points, float player[], float scorpion[], int& highestpoints) {
	int collisionBuffer = 12;
	if ((scorpion[x] <= player[x] + boxPixelsX - collisionBuffer) &&
		(scorpion[x] + boxPixelsX >= player[x] + collisionBuffer) &&
		(scorpion[y] <= player[y] + boxPixelsY - collisionBuffer) &&
		(scorpion[y] + boxPixelsY >= player[y] + collisionBuffer)) {

		saveScore(points);
		cout << "Game Over - Player collided with the scorpion!" << endl;
		exit(0);
	}
}
void spiderbulletcollision(sf::RenderWindow& window, float spider[], float bullets[][3], sf::Sprite& spiderSprite, int& points, int maxbullets, float player[]) {
	sf::Texture pointtexture;
	pointtexture.loadFromFile("Textures/spider_score.png");

	for (int i = 0; i < maxbullets; i++) {
		if ((bullets[i][x] < spider[x] + boxPixelsX) &&
			(bullets[i][x] + boxPixelsX > spider[x]) &&
			(bullets[i][y] < spider[y] + boxPixelsY) &&
			(bullets[i][y] + boxPixelsY > spider[y])) {

			int distance = player[y] - spider[y];

			if (distance <= (2 * boxPixelsY)) {
				points += 900;
				spiderSprite.setTexture(pointtexture);
				spiderSprite.setTextureRect(sf::IntRect(128, 32, (2 * boxPixelsX), boxPixelsY));
				window.draw(spiderSprite);
				window.display();
			}
			else if (distance <= (3 * boxPixelsY)) {
				points += 600;
				spiderSprite.setTexture(pointtexture);
				spiderSprite.setTextureRect(sf::IntRect(64, 32, (2 * boxPixelsX), boxPixelsY));
				window.draw(spiderSprite);
				window.display();
			}
			else {
				points += 300;
				spiderSprite.setTexture(pointtexture);
				spiderSprite.setTextureRect(sf::IntRect(0, 32, (2 * boxPixelsX), boxPixelsY));
				window.draw(spiderSprite);
				window.display();
			}


			spider[x] = -5000;
			spider[y] = -5070;
			spider[exists] = false;
			bullets[i][exists] = false;
			break;
		}
	}
}

void spidermushroomcollision(float spider[], float mushroom[][3], int mushrooms, sf::Sprite mushroomSprite[]) {
	for (int i = 0; i < mushrooms; i++) {
		if ((spider[x] <= mushroom[i][x] + boxPixelsX) &&
			(spider[x] + boxPixelsX >= mushroom[i][x]) &&
			(spider[y] <= mushroom[i][y] + boxPixelsY) &&
			(spider[y] + boxPixelsY >= mushroom[i][y])) {

			mushroom[i][x] = -500;
			mushroom[i][y] = -500;
			mushroom[i][exists] = false;
			break;
		}
	}
}
void bulletscorpioncollision(float scorpion[], float bullets[][3], const int maxBullets, int& points) {
	for (int i = 0; i < maxBullets; i++) {
		if ((bullets[i][x] < scorpion[x] + boxPixelsX) &&
			(bullets[i][x] + boxPixelsX > scorpion[x]) &&
			(bullets[i][y] < scorpion[y] + boxPixelsY) &&
			(bullets[i][y] + boxPixelsY > scorpion[y])) {

			bullets[i][exists] = false;
			scorpion[exists] = false;

			points += 1000;

			scorpion[x] = -10760;
			scorpion[y] = -10340;
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// 								Points  Functions		                   //
//  				File Handaling and displaying points in the Game        //
/////////////////////////////////////////////////////////////////////////////
void displayPoints(sf::RenderWindow& window, int points, int fontsize) {
	sf::Font font;
	font.loadFromFile("minecraft/Minecraft.ttf");
	sf::Text pointsText;
	pointsText.setFont(font);
	pointsText.setCharacterSize(fontsize);
	pointsText.setFillColor(sf::Color::Green);
	pointsText.setPosition(0, 38);
	pointsText.setString("Score: " + to_string(points));

	window.draw(pointsText);
}
void displayhighestPoints(sf::RenderWindow& window, int highestpoints, int fontsize) {
	sf::Font font;
	font.loadFromFile("minecraft/Minecraft.ttf");
	sf::Text pointsText;
	pointsText.setFont(font);
	pointsText.setCharacterSize(fontsize);
	pointsText.setFillColor(sf::Color::Red);
	pointsText.setPosition(0, 0);
	pointsText.setString("HighestScore: " + to_string(highestpoints));

	window.draw(pointsText);
}
void saveScore(int score) {

	ofstream file("scores.txt", ios::app);
	if (file.is_open()) {
		file << score << endl;
		file.close();
	}
}
void readHighestScore(int& highestpoints, int points) {
	std::ifstream file("scores.txt");
	file.is_open();

	int currentscore;

	while (file >> currentscore) {
		if (currentscore > highestpoints) {
			highestpoints = currentscore;
		}
	}

	file.close();
}



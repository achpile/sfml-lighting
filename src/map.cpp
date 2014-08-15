/***********************************************************************
     * File       : map.cpp
     * Created    : Aug 15, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "demo.hpp"



/***********************************************************************
     * Map
     * constructor

***********************************************************************/
Map::Map() {
	bgTex = new sf::Texture();
	bgSpr = new sf::Sprite();

	bgTex->loadFromFile("data/background.jpg");
	bgSpr->setTexture(*bgTex);


	tileTex = new sf::Texture();
	tileSpr = new sf::Sprite();

	tileTex->loadFromFile("data/brick.png");
	tileSpr->setTexture(*tileTex);


	char _tiles[MAP_SIZE_X][MAP_SIZE_Y + 1] = {
		"                                  .XXX",
		"                                  .XXX",
		"                                  .XXX",
		"                           X      .XXX",
		"                           XXXXX...XXX",
		"                          XX.......XXX",
		"                          XX.......XXX",
		"                         XXX.......XXX",
		"X......X                 XXX.......XXX",
		"X......XX               XXXX.......XXX",
		"X.......XX              XXXX.......XXX",
		"X........XX             XXXX.......XXX",
		"X.........X             XXXX.......XXX",
		"X.........X              XXX.......XXX",
		"X.........XX             XXX.......XXX",
		"X...........              XX.......XXX",
		"X.........XX              XX.......XXX",
		"X.........XXX              XXXXX...XXX",
		"X.........XXX              X      .XXX",
		"X.........XXX                     .XXX",
		"X.........XXXX                    .XXX",
		"X.........XXXX                    .XXX",
		"X.........XXXX                    .XXX",
		"X.........XXXXX                   .XXX",
		"X.........XXXXX                   .XXX",
		"X.........XXXXX                   .XXX",
		"X.........XXXXX                   .XXX",
		"X..............                   .XXX",
		"X..............                   .XXX",
		"X..............                   .XXX",
		"X.........XXXXX                   .XXX",
		"X.........XXXXX                   .XXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX...XXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXX........XXX",
		"XX........XXXXX.....XXXXXXX........XXX",
		"XX.   ....XXXXX....................XXX",
		"XX.   ....XXXXX....................XXX",
		"XX.   ....XXXXX....................XXX",
		"XX.   ....XXXXX.....XXXXXXX........XXX",
		"XX.   ....XXXXX.....XXXXXXX........XXX",
		"XX........XXXXX.....XXXXXXX........XXX",
		"XX........XXXXX.....XXXXXXX........XXX",
		"XX........XXXXXXXXXXXXXXXXX........XXX",
		"XX.   ....XXXXXXXXXXXXXXXXX........XXX",
		"XX.   .............................XXX",
		"XX.   .............................XXX",
		"XX.   .............................XXX",
		"XX.   ....XXXXXXXXXXXXXXXXX........XXX",
		"XX........XXXXXXXXXXXXXXXXX........XXX",
		"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
	};

	for (int i = 0; i < MAP_SIZE_X; i++) for (int j = 0; j < MAP_SIZE_Y; j++) {
		tiles[i][j].index = sf::Vector2i(i, j);

		switch (_tiles[i][j]) {
			case 'X':
				tiles[i][j].type   = mtSolid;
				tiles[i][j].absorb = 4;
				break;

			case '.':
				tiles[i][j].type   = mtWall;
				tiles[i][j].absorb = 1;
				break;

			case ' ':
				tiles[i][j].type = mtAir;
				tiles[i][j].absorb = 1;
				break;
		}
	}

	int lightCount = MAP_SIZE_X * MAP_SIZE_Y;
	for (int i = 0; i < LIGHT_MAX_LIGHTLEVEL; i++) lightTiles[i] = new MapTile*[lightCount];
}



/***********************************************************************
     * Map
     * destructor

***********************************************************************/
Map::~Map() {
	for (int i = 0; i < LIGHT_MAX_LIGHTLEVEL; delete lightTiles[i++]);

	delete bgTex;
	delete bgSpr;

	delete tileTex;
	delete tileSpr;

	deleteList(sources);
}



/***********************************************************************
     * Map
     * update

***********************************************************************/
void Map::update(StaticLightSource *tmpSource) {
	updateList(sources);

	resetLight();
	render();

	if (sf::IntRect(0, 0, MAP_SIZE_X, MAP_SIZE_Y).contains(tmpSource->position))
		addIntensity(tmpSource->position, tmpSource->intensity, tmpSource->color);

	light();
}



/***********************************************************************
     * Map
     * render

***********************************************************************/
void Map::render() {
	renderTiles();
}



/***********************************************************************
     * Map
     * renderTiles

***********************************************************************/
void Map::renderTiles() {
	sf::Color tileColor;

	app->draw(*bgSpr);

	for (int i = 0; i < MAP_SIZE_X; i++) for (int j = 0; j < MAP_SIZE_Y; j++) {
		tileColor = sf::Color::White;

		switch (tiles[i][j].type) {
			case mtWall:
				tileColor = sf::Color(140, 140, 140, 255);

			case mtSolid:
				tileSpr->setPosition(i * TILE_SIZE, j * TILE_SIZE);
				tileSpr->setColor(tileColor);
				app->draw(*tileSpr);
				break;

			case mtAir:
				break;
		}
	}
}

#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
const int WS_WIDTH = 900, WS_HEIGHT = 597;
const int addSpace = 180;
int difficult = 0;

RenderWindow window(VideoMode(WS_WIDTH, WS_HEIGHT), L"Игра Sudoku", Style::Close);
Font font;
Text text;
Texture background;
Sprite backSprite;

void showStartMenu() {
	while (window.isOpen()) {
		//выключение повтора при удержании клавиши
		Event event;
		window.clear(Color::Black);
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		window.draw(backSprite);
		int diff = 0;
		if (event.type == Event::MouseMoved) {
			int x = sf::Mouse::getPosition(window).x;
			int y = sf::Mouse::getPosition(window).y;
			if (x > 300 && y > 110 && x < 600 && y < 150) {
				diff = 1;
			}
			if (x > 300 && y > 200 && x < 600 && y < 250) {
				diff = 2;
			}
			if (x > 300 && y > 280 && x < 600 && y < 320) {
				diff = 3;
			}
		}

		text.setString(L"Лёгкий");
		text.setPosition(318, 100);
		text.setCharacterSize(60);
		if (diff == 1) {
			text.setFillColor(Color::Green);
		}
		else {
			text.setFillColor(Color::White);
		}
		window.draw(text);

		text.setString(L"Средний");
		text.setPosition(298, 180);
		text.setCharacterSize(60);
		if (diff == 2) {
			text.setFillColor(Color::Yellow);
		}
		else {
			text.setFillColor(Color::White);
		}

		window.draw(text);

		text.setString(L"Сложный");
		text.setPosition(298, 260);
		text.setCharacterSize(60);
		if (diff == 3) {
			text.setFillColor(Color::Red);
		}
		else {
			text.setFillColor(Color::White);
		}
		window.draw(text);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int x = sf::Mouse::getPosition(window).x;
			int y = sf::Mouse::getPosition(window).y;
			window.setTitle("X=" + std::to_string(x + 1) + ", Y=" + std::to_string(y + 1));
			if (x > 300 && y > 110 && x < 600 && y < 150) {
				difficult = 20;
				break;
			}
			if (x > 300 && y > 200 && x < 600 && y < 250) {
				difficult = 40;
				break;
			}
			if (x > 300 && y > 280 && x < 600 && y < 320) {
				difficult = 60;
				break;
			}
		}


		window.display();

	}

}
void showVictory() {
	//отрисовка фона с победой
	background.loadFromFile("qljor-scaled.jpg");
	backSprite.setTexture(background);
	//цикл ожидания закрытия окна
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.clear(Color::Green);
		//отрисовать фон
		window.draw(backSprite);
		text.setString(L"Вы победили!");
		text.setPosition(10, 10);
		window.draw(text);
		window.display();
	}

}

int main() {
	int gridSize = 9;
	float lineThink = 1.8;
	float hSpacing = (window.getSize().x-addSpace) / gridSize;
	float vSpacing = window.getSize().y / gridSize;
	//стартовое поле
	int startField[9][9]{
		{5, 3, 9, 8, 7, 6, 4, 1, 2},
		{7, 2, 8, 3, 1, 4, 9, 6, 5},
		{6, 4, 1, 2, 9, 5, 7, 3, 8},
		{4, 6, 2, 5, 3, 9, 8, 7, 1},
		{3, 8, 5, 7, 2, 1, 6, 4, 9},
		{1, 9, 7, 4, 6, 8, 2, 5, 3},
		{2, 5, 6, 1, 8, 7, 3, 9, 4},
		{9, 1, 3, 6, 4, 2, 5, 8, 7},
		{8, 7, 4, 9, 5, 3, 1, 2, 6}
	};
	//начальное игровое поле
	int gameField[9][9];
	//поле для заполнения
	int userField[9][9]{ 0 };
	
	//загрузка и установка шрифта

	font.loadFromFile("cour.ttf");
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setStyle(sf::Text::Bold);
	//загрузка и подготовка фона
	background.loadFromFile("1644832389_2-fikiwiki-com-p-krasivie-kartinki-barseloni-2.jpg");
	backSprite.setTexture(background);
	//стрвртовое меню с выбором сложности
	showStartMenu();
	srand(time(NULL));
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			int r = rand() % 100;
			if (r > difficult) {
				gameField[i][j] = startField[i][j];
				userField[i][j] = startField[i][j];
			}
			else {
				gameField[i][j] = 0;
			}
		}
	}

	bool musicPlay = false; //признак воспроизведения музыки
	int userNumber = 0;		//выбранное число пользрвателя
	int delayHint = 3;		//удержание подсказки в секундах
	bool showHint = false;		//признак включения пдсказки
	long startShowHint = 0;		//время начала отображения пдсказки
	long startTime = time(NULL);		//время начала игры
	Music music;							//подготовка и загрузка музыкального фона
	music.openFromFile("pornhub.mp3");
	music.setLoop(true);
	music.play();
	//подготовка и загрузка звукового эффекта
	SoundBuffer buf;
	buf.loadFromFile("babuin.mp3");
	Sound sound;
	sound.setBuffer(buf);
	int countError = 0;			//количество ошибок
	bool isCountError = true;		//признак наличия ошибок
	//основной цикл игрового процесса
	
	while (window.isOpen()) {
		Event event;
		window.clear(Color::White);
		while (window.pollEvent(event)) {		//очищаем окно
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.draw(backSprite);		//отображаем фон если нажата клавиша
		if (Event::KeyReleased) {
			//если это число, включаем пдсказки
			if (event.key.code >= 49 &&
				event.key.code <= 57 ) {
				userNumber = event.key.code - 48;
			}
			//если пробел включаем подсказки
			if (Keyboard::isKeyPressed(Keyboard::Space)) {
				showHint = true;
				startShowHint = time(NULL);
				//sound.play();
				countError = 0;
				isCountError = false;
			}

		}
			if (Keyboard::isKeyPressed(Keyboard::M)) {
					if (!musicPlay) {
						window.setTitle("Music off");
						music.play();
						musicPlay = true;
						while (Keyboard::isKeyPressed(Keyboard::M));
					}
				else if (musicPlay) {
					window.setTitle("Music on");
					music.stop();
					musicPlay = false;
					while (Keyboard::isKeyPressed(Keyboard::M));
				}
			}
		
		//удаление подсказки по времени
		if (time(NULL) > startShowHint + delayHint) {
			showHint = false;
		}
		//если нажата лев клав мыши вычисляем квадрат ее нахождения
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int x = sf::Mouse::getPosition(window).x/hSpacing;
			int y = sf::Mouse::getPosition(window).y/vSpacing;
			window.setTitle("X="+std::to_string(x+1)+", Y="+std::to_string(y+1));
			userField[x][y] = userNumber;
			if (gameField[x][y] == 0) userField[x][y] = userNumber;
		}
		//отрисовка сетки игрового поля
		for (int i = 0; i <= gridSize; i++) {
			int think = 1;
			if (i % 3 == 0) { think = 3; }
			RectangleShape line(Vector2f(window.getSize().x - addSpace, think));
			line.setPosition(0, i * vSpacing);
			line.setFillColor(Color::White);
			RectangleShape line2(Vector2f(window.getSize().y, think));
			line2.setPosition(i * hSpacing, 0);
			line2.rotate(90);
			line2.setFillColor(Color::White);
			window.draw(line);
			window.draw(line2);
		}
	
		for (int i = 0; i < gridSize; i++) {
			
			VertexArray vLine(Lines, 2);
			vLine[0].position = Vector2f(i * hSpacing, 0);
			vLine[1].position = Vector2f(i * hSpacing, window.getSize() .y);
			vLine[0].color = Color::White;
			vLine[1].color = Color::White;
			window.draw(vLine);
			
		}
		//отрисовка изначальных чисел и чисел пользователя
		for (int i = 0; i < gridSize; i++) {
			for (int j = 0; j < gridSize; j++) {
				char num{ 32 };
				if (gameField[i][j] != 0) {
					num = gameField[i][j] + 48;
					text.setFillColor(Color::White);
				}
				else if (userField[i][j] != 0) {
					num = userField[i][j] + 48;
					if (showHint) {
						if (startField[i][j] == userField[i][j]) {
							text.setFillColor(Color::Green);
						}
						else {
							text.setFillColor(Color::Red);
							if (!isCountError) { countError++; }

						}
					}else {
						text.setFillColor(Color::Yellow);
					}
				}
				text.setCharacterSize(52);
				text.setString(num);
				text.setPosition(Vector2f(i * hSpacing+25, j * vSpacing));
				window.draw(text);
			}
		}
		isCountError = true;
		//отрисовка правого блока информации - выбранное число
		text.setString(std::to_string(userNumber));
		text.setFillColor(Color::Magenta);
		text.setPosition(Vector2f(WS_WIDTH - (addSpace/1.75) , vSpacing));
		window.draw(text);
		text.setString(L"Выбрано");
		text.setPosition(Vector2f(WS_WIDTH - addSpace+10, 10));
		text.setCharacterSize(36);
		window.draw(text);
		//правый блок - прошло времени
		text.setString(L"Прошло");
		text.setPosition(Vector2f(hSpacing*gridSize+10, vSpacing * 2));
		window.draw(text);
		//расчёт прошедшего времени и отрисовка
		int hour = (time(NULL) - startTime) / 3600;
		int minute = (time(NULL) - startTime) / 60;
		int second = (time(NULL) - startTime) % 60;
		std::string strTime = std::to_string(hour) + ":" +
		std::to_string(minute) + ":" + std::to_string(second);
		text.setString(strTime);
		text.setPosition(Vector2f(hSpacing * gridSize + 20, vSpacing * 3));
		window.draw(text);

		text.setString(L"Ошибок");
		text.setFillColor(Color::Red);
		text.setPosition(Vector2f(hSpacing* gridSize + 10, vSpacing * 4));
		window.draw(text);
		//количество допущенных ошибок
		text.setString(std::to_string(countError));
		text.setPosition(Vector2f(hSpacing* gridSize + 10, vSpacing * 5));
		window.draw(text);
		window.display();
		//количсетсво правильных совпадений
		int countRight = 0;

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (userField[i][j] == startField[i][j]) {
					countRight++;
				}
				else {
					break;
				}
			}
		}
		if (countRight == 81) {
			//если правильных 81, то конец иры, выход из основоного цикла
			break;
		}

	}
	//показать окно победы
	showVictory();
	return 0;

}

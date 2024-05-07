#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
const int WS_WIDTH = 900, WS_HEIGHT = 597;
const int addSpace = 180;
int difficult = 0;

RenderWindow window(VideoMode(WS_WIDTH, WS_HEIGHT), L"���� Sudoku", Style::Close);
Font font;
Text text;
Texture background;
Sprite backSprite;

void showStartMenu() {
	while (window.isOpen()) {
		//���������� ������� ��� ��������� �������
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

		text.setString(L"˸����");
		text.setPosition(318, 100);
		text.setCharacterSize(60);
		if (diff == 1) {
			text.setFillColor(Color::Green);
		}
		else {
			text.setFillColor(Color::White);
		}
		window.draw(text);

		text.setString(L"�������");
		text.setPosition(298, 180);
		text.setCharacterSize(60);
		if (diff == 2) {
			text.setFillColor(Color::Yellow);
		}
		else {
			text.setFillColor(Color::White);
		}

		window.draw(text);

		text.setString(L"�������");
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
	//��������� ���� � �������
	background.loadFromFile("qljor-scaled.jpg");
	backSprite.setTexture(background);
	//���� �������� �������� ����
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.clear(Color::Green);
		//���������� ���
		window.draw(backSprite);
		text.setString(L"�� ��������!");
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
	//��������� ����
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
	//��������� ������� ����
	int gameField[9][9];
	//���� ��� ����������
	int userField[9][9]{ 0 };
	
	//�������� � ��������� ������

	font.loadFromFile("cour.ttf");
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setStyle(sf::Text::Bold);
	//�������� � ���������� ����
	background.loadFromFile("1644832389_2-fikiwiki-com-p-krasivie-kartinki-barseloni-2.jpg");
	backSprite.setTexture(background);
	//���������� ���� � ������� ���������
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

	bool musicPlay = false; //������� ��������������� ������
	int userNumber = 0;		//��������� ����� ������������
	int delayHint = 3;		//��������� ��������� � ��������
	bool showHint = false;		//������� ��������� ��������
	long startShowHint = 0;		//����� ������ ����������� ��������
	long startTime = time(NULL);		//����� ������ ����
	Music music;							//���������� � �������� ������������ ����
	music.openFromFile("pornhub.mp3");
	music.setLoop(true);
	music.play();
	//���������� � �������� ��������� �������
	SoundBuffer buf;
	buf.loadFromFile("babuin.mp3");
	Sound sound;
	sound.setBuffer(buf);
	int countError = 0;			//���������� ������
	bool isCountError = true;		//������� ������� ������
	//�������� ���� �������� ��������
	
	while (window.isOpen()) {
		Event event;
		window.clear(Color::White);
		while (window.pollEvent(event)) {		//������� ����
			if (event.type == Event::Closed) {
				window.close();
			}
		}
		window.draw(backSprite);		//���������� ��� ���� ������ �������
		if (Event::KeyReleased) {
			//���� ��� �����, �������� ��������
			if (event.key.code >= 49 &&
				event.key.code <= 57 ) {
				userNumber = event.key.code - 48;
			}
			//���� ������ �������� ���������
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
		
		//�������� ��������� �� �������
		if (time(NULL) > startShowHint + delayHint) {
			showHint = false;
		}
		//���� ������ ��� ���� ���� ��������� ������� �� ����������
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int x = sf::Mouse::getPosition(window).x/hSpacing;
			int y = sf::Mouse::getPosition(window).y/vSpacing;
			window.setTitle("X="+std::to_string(x+1)+", Y="+std::to_string(y+1));
			userField[x][y] = userNumber;
			if (gameField[x][y] == 0) userField[x][y] = userNumber;
		}
		//��������� ����� �������� ����
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
		//��������� ����������� ����� � ����� ������������
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
		//��������� ������� ����� ���������� - ��������� �����
		text.setString(std::to_string(userNumber));
		text.setFillColor(Color::Magenta);
		text.setPosition(Vector2f(WS_WIDTH - (addSpace/1.75) , vSpacing));
		window.draw(text);
		text.setString(L"�������");
		text.setPosition(Vector2f(WS_WIDTH - addSpace+10, 10));
		text.setCharacterSize(36);
		window.draw(text);
		//������ ���� - ������ �������
		text.setString(L"������");
		text.setPosition(Vector2f(hSpacing*gridSize+10, vSpacing * 2));
		window.draw(text);
		//������ ���������� ������� � ���������
		int hour = (time(NULL) - startTime) / 3600;
		int minute = (time(NULL) - startTime) / 60;
		int second = (time(NULL) - startTime) % 60;
		std::string strTime = std::to_string(hour) + ":" +
		std::to_string(minute) + ":" + std::to_string(second);
		text.setString(strTime);
		text.setPosition(Vector2f(hSpacing * gridSize + 20, vSpacing * 3));
		window.draw(text);

		text.setString(L"������");
		text.setFillColor(Color::Red);
		text.setPosition(Vector2f(hSpacing* gridSize + 10, vSpacing * 4));
		window.draw(text);
		//���������� ���������� ������
		text.setString(std::to_string(countError));
		text.setPosition(Vector2f(hSpacing* gridSize + 10, vSpacing * 5));
		window.draw(text);
		window.display();
		//����������� ���������� ����������
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
			//���� ���������� 81, �� ����� ���, ����� �� ���������� �����
			break;
		}

	}
	//�������� ���� ������
	showVictory();
	return 0;

}

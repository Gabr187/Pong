#include <raylib.h>
#include <iostream>

const int screen_width = 1280;
const int screen_height = 720;
int player_score = 0;
int player2_score = 0;

class Ball {
public:
	float x, y;
	int speed_x, speed_y;
	int radius;

	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}
	void Update() {
		x += speed_x;
		y += speed_y;

		if (y + radius >= screen_height || y - radius <= 0) {
			speed_y *= -1;
		}
		if (x + radius >= screen_width) {
			player_score++;
			ResetBall();
		}
		if (x - radius <= 0) {
			player2_score++;
			ResetBall();
		}
	}
	void ResetBall() {
		x = screen_width / 2;
		y = screen_height / 2;

		int directionChoices[2] = { -1, 1 };

		speed_x *= directionChoices[GetRandomValue(0, 1)];
		speed_y *= directionChoices[GetRandomValue(0, 1)];
	}
};

class Player {
public:
	float x, y;
	float width, height;
	int speed;

	void Draw() {
		DrawRectangle(x, y, width, height, WHITE);
	}
	void Update() {
		if (IsKeyDown(KEY_W)) {
			y = y - speed;
		}
		if (IsKeyDown(KEY_S)) {
			y = y + speed;
		}
		if (y <= 0) {
			y = 0;
		}
		if (y + height >= screen_height) {
			y = screen_height - height;
		}
	}
};

class Player2 : public Player {
public:
	void Update() {
		if (IsKeyDown(KEY_UP)) {
			y = y - speed;
		}
		if (IsKeyDown(KEY_DOWN)) {
			y = y + speed;
		}
		if (y <= 0) {
			y = 0;
		}
		if (y + height >= screen_height) {
			y = screen_height - height;
		}
	}
};

Ball ball;
Player player;
Player2 player2;

int main() {
	ball.radius = 20;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.speed_x = 8;
	ball.speed_y = 8;

	player.width = 25;
	player.height = 100;
	player.x = 0 - player.width + (10 + player.width);
	player.y = (screen_height / 2) - (player.height / 2);
	player.speed = 7;

	player2.width = 25;
	player2.height = 100;
	player2.x = screen_width - player2.width - 10;
	player2.y = (screen_height / 2) - (player2.height / 2);
	player2.speed = 7;

	std::cout << "Starting the game" << '\n';
	InitWindow(screen_width, screen_height, "Pong");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		//Update
		ball.Update();
		player.Update();
		player2.Update();

		//Check Colisions
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
		{
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player2.x, player2.y, player2.width, player2.height }))
		{
			ball.speed_x *= -1;
		}
		//Clear Background
		ClearBackground(BLACK);

		//Draw Center Line
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);

		//Draw Player/CPU
		player.Draw();
		player2.Draw();

		//Draw Score
		DrawText(TextFormat("%i", player_score), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", player2_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

		//Draw Ball
		ball.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}

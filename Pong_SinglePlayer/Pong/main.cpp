#include <raylib.h>
#include <iostream>

const int screen_width = 1280;
const int screen_height = 720;
int player_score = 0;
int cpu_score = 0;

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
			cpu_score++;
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

class CPU : public Player {
public:
	void Update(int ball_y) {
		if (y + height / 2 > ball_y) {
			y = y - speed;
		}
		if (y + height / 2 <= ball_y) {
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
CPU cpu;

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

	cpu.width = 25;
	cpu.height = 100;
	cpu.x = screen_width - cpu.width - 10;
	cpu.y = (screen_height / 2) - (cpu.height / 2);
	cpu.speed = 7;

	std::cout << "Starting the game" << '\n';
	InitWindow(screen_width, screen_height, "Pong");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();

		//Update
		ball.Update();
		player.Update();
		cpu.Update(ball.y);

		//Check Colisions
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height }))
		{
			ball.speed_x *= -1;
		}
		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ cpu.x, cpu.y, cpu.width, cpu.height }))
		{
			ball.speed_x *= -1;
		}
		//Clear Background
		ClearBackground(BLACK);

		//Draw Center Line
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
		
		//Draw Player/CPU
		player.Draw();
		cpu.Draw();

		//Draw Score
		DrawText(TextFormat("%i", player_score), screen_width / 4 - 20, 20, 80, WHITE);
		DrawText(TextFormat("%i", cpu_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
		
		//Draw Ball
		ball.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
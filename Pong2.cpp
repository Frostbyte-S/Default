#include <iostream>
#include <string>
#include <raylib.h>
using namespace std;

int main()
{
    InitWindow(1000, 600, "Pong");
    SetTargetFPS(60);

    double Time_A, Time_B, Pause_Duration = 2;
    int Score_L_int = 0, Score_R_int = 0, Winning_Score = 5;
    string Score_L_str = "0", Score_R_str = "0";
    float Left_Paddle = 260, Right_Paddle = 260, Ball_Speed = 5, Ball_x_increase = Ball_Speed, Ball_y_increase = Ball_Speed;
    Vector2 Ball = {500, 300}, tls = {1, 1}, tle = {1000, 1}, bls = {1, 600}, ble = {1000, 600}, lls = {1, 1}, lle = {1, 600}, rls = {1000, 1}, rle = {1000, 600};
    Rectangle LP_Rec = {50, Left_Paddle, 10, 80}, RP_Rec = {950, Right_Paddle, 10, 80};
    bool Game_Start = false, is_pause = false, Game_Begin = true;

    Time_A = GetTime();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(GRAY);

        if (!is_pause && GetTime() - Time_A >= 3)
        {
            Ball_Speed += 0.5;
            Time_A = GetTime();
            Ball_x_increase = (Ball_x_increase > 0 ? 1 : -1) * Ball_Speed;
            Ball_y_increase = (Ball_y_increase > 0 ? 1 : -1) * Ball_Speed;
        }

        if (IsKeyPressed(KEY_SPACE))
            Game_Start = true;

    replay:

        if (Game_Start)
        {
            if (Game_Begin)
            {
                Ball = {500, 300};
                Time_A = GetTime();
                is_pause = true;
                Game_Begin = false;
            }

            if (Score_L_int == Winning_Score || Score_R_int == Winning_Score)
            {
                if (Score_L_int > Score_R_int)
                {
                    DrawText("Left Wins!!!", 330, 250, 50, BLUE);
                    DrawText("Press SPACE to play again OR ECS to quit", 150, 400, 30, BLUE);
                    if (IsKeyPressed(KEY_SPACE))
                    {
                        Score_L_int = 0, Score_R_int = 0;
                        Score_R_str = to_string(Score_R_int);
                        Score_L_str = to_string(Score_L_int);
                        Ball_Speed = 5;
                        Time_A = GetTime();
                        Game_Begin = true;
                        goto replay;
                    }
                }
                else
                {
                    DrawText("Right Wins!!!", 330, 250, 50, BLUE);
                    DrawText("Press SPACE to play again OR ECS to quit", 150, 400, 30, BLUE);
                    if (IsKeyPressed(KEY_SPACE))
                    {
                        Score_L_int = 0, Score_R_int = 0;
                        Score_R_str = to_string(Score_R_int);
                        Score_L_str = to_string(Score_L_int);
                        Ball_Speed = 5;
                        Time_A = GetTime();
                        Game_Begin = true;
                        goto replay;
                    }
                }
            }
            else
            {
                if (IsKeyDown(KEY_W))
                {
                    if (Left_Paddle >= 10)
                    {
                        Left_Paddle -= 15;
                        LP_Rec.y = Left_Paddle;
                    }
                }
                if (IsKeyDown(KEY_S))
                {
                    if (Left_Paddle + 80 <= 580)
                    {
                        Left_Paddle += 15;
                        LP_Rec.y = Left_Paddle;
                    }
                }
                if (IsKeyDown(KEY_O))
                {
                    if (Right_Paddle >= 10)
                    {
                        Right_Paddle -= 15;
                        RP_Rec.y = Right_Paddle;
                    }
                }
                if (IsKeyDown(KEY_L))
                {
                    if (Right_Paddle + 80 <= 580)
                    {
                        Right_Paddle += 15;
                        RP_Rec.y = Right_Paddle;
                    }
                }
                if (CheckCollisionCircleLine(Ball, 8, tls, tle))
                    Ball_y_increase = -Ball_y_increase;
                if (CheckCollisionCircleLine(Ball, 8, bls, ble))
                    Ball_y_increase = -Ball_y_increase;
                if (CheckCollisionCircleLine(Ball, 8, lls, lle))
                {
                    Ball = {500, 300};
                    Score_R_int++;
                    Score_R_str = to_string(Score_R_int);
                    Ball_Speed = 5;
                    is_pause = true;
                    Time_A = GetTime();
                }
                if (CheckCollisionCircleLine(Ball, 8, rls, rle))
                {
                    Ball = {500, 300};
                    Score_L_int++;
                    Score_L_str = to_string(Score_L_int);
                    DrawCircleV(Ball, 8, YELLOW);
                    Ball_Speed = 5;
                    is_pause = true;
                    Time_A = GetTime();
                }
                if (CheckCollisionCircleRec(Ball, 8, LP_Rec))
                    Ball_x_increase = -Ball_x_increase;
                if (CheckCollisionCircleRec(Ball, 8, RP_Rec))
                    Ball_x_increase = -Ball_x_increase;

                if (is_pause)
                {
                    Ball_x_increase = 0;
                    Ball_y_increase = 0;

                    if (GetTime() - Time_A >= 1.5)
                    {
                        Ball_x_increase = Ball_Speed * (GetRandomValue(0, 1) ? 1 : -1);
                        Ball_y_increase = Ball_Speed * (GetRandomValue(0, 1) ? 1 : -1);
                        is_pause = false;
                    }
                }
                else
                {
                    Ball.x += Ball_x_increase;
                    Ball.y += Ball_y_increase;
                }

                DrawRectangle(50, Left_Paddle, 10, 80, GREEN);   // Left Paddle
                DrawRectangle(950, Right_Paddle, 10, 80, GREEN); // Right Paddle
                DrawLine(1, 1, 1000, 1, RED);                    // Top Border
                DrawLine(1, 600, 1000, 600, RED);                // Bottom Border
                DrawLine(1, 1, 1, 600, RED);                     // Left Border
                DrawLine(1000, 1, 1000, 600, RED);               // Right Border
                DrawRectangle(490, 0, 15, 600, RED);             // Middle Line
                DrawText(Score_L_str.c_str(), 200, 200, 150, DARKGRAY);
                DrawText(Score_R_str.c_str(), 700, 200, 150, DARKGRAY);
                DrawCircleV(Ball, 8, YELLOW); // Ball
            }
        }
        else
        {
            DrawText("PONG", 210, 160, 200, BLUE);
            DrawText("Press SPACE to start", 250, 450, 40, BLUE);
        }

        EndDrawing();
    }

    return 0;
}
#include <raylib.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
using namespace std;
int main()
{
    int sw = 960, sh = 720;
    InitWindow(sw, sh, "Program");
    int n = 6, d = 71;
    float scale = 300.0f;
    Vector2 *points = new Vector2[361];
    Vector2 *outline = new Vector2[361];
    Vector2 origin = Vector2{sw / 2.0f, sh / 2.0f};
    for (int i = 0; i <= 360; i++)
    {
        float k1 = i * d * M_PI / 180;
        float r1 = sinf(n * k1);
        points[i] = Vector2{r1 * cosf(k1), r1 * sinf(k1)};
        float k2 = i * M_PI / 180;
        float r2 = sinf(n * k2);
        outline[i] = Vector2{r2 * cosf(k2), r2 * sinf(k2)};
    }
    float zoomFactor = 1.1f;
    bool outlineOn = false;
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_O))
            outlineOn = !outlineOn;
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            if (wheel > 0)
                scale *= zoomFactor;
            else
                scale /= zoomFactor;
            scale = max(min(scale, 500.0f), 100.0f);
        }
        BeginDrawing();
        ClearBackground(BLACK);
        for (int i = 0; i < 360; i++)
        {
            DrawLine(points[i].x * scale + origin.x, points[i].y * scale + origin.y,
                     points[i + 1].x * scale + origin.x, points[i + 1].y * scale + origin.y,
                     BLUE);
        }
        if (outlineOn)
        {
            for (int i = 0; i < 360; i++)
            {
                DrawLine(outline[i].x * scale + origin.x, outline[i].y * scale + origin.y,
                         outline[i + 1].x * scale + origin.x, outline[i + 1].y * scale + origin.y,
                         BLUE);
            }
        }
        EndDrawing();
    }
    delete[] points;
    delete[] outline;
    CloseWindow();
    return 0;
}
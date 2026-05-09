#include <raylib.h>
#define _USE_MATH_DEFINES
#include <cmath>
using namespace std;
int main()
{
    int sw = 960, sh = 720;
    InitWindow(sw, sh, "Program");
    int n = 7, d = 29;
    Vector2 *points = new Vector2[361];
    Vector2 *outlines = new Vector2[361];
    Vector2 origin = Vector2{sw / 2.0f, sh / 2.0f};
    points[0] = outlines[0] = origin;
    for (int i = 1; i <= 360; i++)
    {
        float k1 = i * d * M_PI / 180;
        float r1 = 300 * sinf(n * k1);
        points[i] = Vector2{r1 * cosf(k1) + origin.x, r1 * sinf(k1) + origin.y};
        float k2 = i * M_PI / 180;
        float r2 = 300 * sinf(n * k2);
        outlines[i] = Vector2{r2 * cosf(k2) + origin.x, r2 * sinf(k2) + origin.y};
    }
    bool outlinesOn = false;
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_O))
            outlinesOn = !outlinesOn;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawLineStrip(points, 361, BLUE);
        if (outlinesOn)
            DrawSplineLinear(outlines, 361, 4.0f, RED);
        EndDrawing();
    }
    delete[] points;
    delete[] outlines;
    CloseWindow();
    return 0;
}
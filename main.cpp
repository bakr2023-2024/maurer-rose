#include <raylib.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <string>
using namespace std;
Color hexToRGB(unsigned long hex)
{
    return Color{
        (unsigned char)(hex >> 16 & 0xff),
        (unsigned char)(hex >> 8 & 0xff),
        (unsigned char)(hex & 0xff),
        255};
}
int main(int argc, char **argv)
{
    Color backgroundColor = BLACK;
    Color roseColor = WHITE;
    int n = 6, d = 71;
    if (argc == 5)
        roseColor = hexToRGB(stoul(argv[4], nullptr, 0));
    if (argc >= 4)
        backgroundColor = hexToRGB(stoul(argv[3], nullptr, 0));
    if (argc >= 3)
        d = stoi(argv[2]);
    if (argc >= 2)
        n = stoi(argv[1]);
    int sw = 960, sh = 720;
    InitWindow(sw, sh, "Program");
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
        ClearBackground(backgroundColor);
        for (int i = 0; i < 360; i++)
        {
            DrawLine(points[i].x * scale + origin.x, points[i].y * scale + origin.y,
                     points[i + 1].x * scale + origin.x, points[i + 1].y * scale + origin.y,
                     roseColor);
        }
        if (outlineOn)
        {
            for (int i = 0; i < 360; i++)
            {
                DrawLineEx({outline[i].x * scale + origin.x, outline[i].y * scale + origin.y},
                           {outline[i + 1].x * scale + origin.x, outline[i + 1].y * scale + origin.y},
                           4.0f, RED);
            }
        }
        EndDrawing();
    }
    delete[] points;
    delete[] outline;
    CloseWindow();
    return 0;
}
#ifndef INC_3DRENDERER_H
#define INC_3DRENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>
#include <cmath>
#include <unistd.h>

typedef struct Point2D {
    float x, y;
} Point2D;

typedef struct Point3D {
    float x, y, z;
} Point3D;

typedef struct Vertex {
    int start, end;
} Vertex;

typedef struct Shape3D {
    std::vector<Point3D> points;
    std::vector<Vertex> vertices;

    Shape3D(const std::vector<Point3D>& p, const std::vector<Vertex>& v) : points(p), vertices(v) {}
} Shape3D;

class Renderer3D {
public:
    Renderer3D(SDL_Window *window_, SDL_Renderer *renderer_);
    void render(std::vector<Point3D> &points, std::vector<Vertex> &vertices);
    void renderShapes(std::vector<Shape3D> &shapes);

    void pauseRotation();

private:
    bool pause = false;
    float rotation = 45.0f;
    float FOV = 500.0f;
    float DeltaTime = 0.0f;

    int WindowSizeX;
    int WindowSizeY;

    Point3D RotateX(Point3D point, float rotation_);
    Point3D RotateY(Point3D point, float rotation_);
    Point2D Projection(Point3D point);


    SDL_Renderer* renderer;
};

#endif //INC_3DRENDERER_H

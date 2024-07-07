#include "3DRenderer.h"

Renderer3D::Renderer3D(SDL_Window *window_, SDL_Renderer *renderer_) {
    renderer = renderer_;
    SDL_GetWindowSize(window_, &WindowSizeX, &WindowSizeY);
}

void Renderer3D::render(std::vector<Point3D> &points, std::vector<Vertex> &vertices) {
    auto time1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration(0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer); SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

    if (!pause)
        rotation += (1 * DeltaTime);

    for (auto & vertex : vertices) {
        Point3D rotatedStartPoint = RotateY(RotateX(points[vertex.start], rotation), rotation);
        Point3D rotatedEndPoint = RotateY(RotateX(points[vertex.end], rotation), rotation);
        Point2D start = Projection(rotatedStartPoint);
        Point2D end = Projection(rotatedEndPoint);
        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }
    SDL_RenderPresent(renderer);
    auto time2 = std::chrono::high_resolution_clock::now();
    duration = time2 - time1;
    DeltaTime = duration.count();
    time1 = time2;
}

void Renderer3D::renderShapes(std::vector<Shape3D> &shapes) {
    auto time1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration(0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

    if (!pause)
        rotation += (1 * DeltaTime);

    for (auto &shape : shapes)
        for (auto & vertex : shape.vertices) {
            Point3D rotatedStartPoint = RotateY(RotateX(shape.points[vertex.start], rotation), rotation);
            Point3D rotatedEndPoint = RotateY(RotateX(shape.points[vertex.end], rotation), rotation);
            Point2D start = Projection(rotatedStartPoint);
            Point2D end = Projection(rotatedEndPoint);
            SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
        }
    SDL_RenderPresent(renderer);
    auto time2 = std::chrono::high_resolution_clock::now();
    duration = time2 - time1;
    DeltaTime = duration.count();
    time1 = time2;
}


Point2D Renderer3D::Projection(Point3D point) {
    Point2D projectedPoint;
    float factor = FOV / (point.z + FOV);
    projectedPoint.x = (point.x * factor) + (WindowSizeX / 2.0);
    projectedPoint.y = (point.y * factor) + (WindowSizeY / 2.0);
    return projectedPoint;
}

Point3D Renderer3D::RotateX(Point3D point, float rotation_) {
    Point3D rotatedPoint;
    rotatedPoint.x = point.x;
    rotatedPoint.y = point.y * cos(rotation_) - point.z * sin(rotation_);
    rotatedPoint.z = sin(rotation_) * point.y + cos(rotation_) * point.z;
    return rotatedPoint;
}

Point3D Renderer3D::RotateY(Point3D point, float rotation_) {
    Point3D rotatedPoint;
    rotatedPoint.x = cos(rotation_) * point.x - sin(rotation_) * point.z;
    rotatedPoint.y = point.y;
    rotatedPoint.z = sin(rotation_) * point.x + cos(rotation_) * point.z;
    return rotatedPoint;
}

void Renderer3D::pauseRotation() {
    pause = !pause;
}

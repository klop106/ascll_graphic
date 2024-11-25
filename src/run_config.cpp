#include "render/frame.h"
#include "render/render.h"
#include "scene/object.h"
#include "scene/poligon.h"
#include "scene/point_of_view.h"
#include "scene/light_source.h"

#include "linear_field_operations/linear_transform.h"
#include "linear_field_operations/vector.h"
#include "linear_field_operations/point.h"

#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <ncurses.h>


int main() {

    // Point position1(-2.1, 0, 0.5);
    // Vector3 vec1(1, 0, 0);
    // Vector3 vec2(0, 1, 0);
    // Vector3 vec3(0, 0, 1);

    // Point point1(-2, -2, 1);

    // Object piramid("../objects/piramid.json");
    // Object plane("../objects/plane.json");
    // PointOfView pov(vec1, vec2, vec3, position1);
    // LightSource light(point1, 3);
    // Frame scene;

    // std::vector<Object> v1;
    // v1.push_back(piramid);
    // v1.push_back(plane);

    // Render render(&pov, &v1, &light, &scene);

    // double v = 0.01;
    // std::vector<std::string> film;
    // for (size_t i = 0; i < 100; i++)
    // {
    //     double matr[3][3] = {{cos(v * i), -sin(v * i), 0}, {sin(v * i), cos(v * i), 0}, {0, 0, 1}};
    //     LinearTransformation transformation(matr);
    //     light.transform(transformation);
    //     render.render();
    //     //film.push_back(scene.get_image());
    // }

    initscr

    // Измеряем размер экрана в рядах и колонках
    int row, col;
    getmaxyx(stdscr, row, col);
    
    // перемещение курсора в стандартном экране
    move(row / 2, col / 2);

    printw("Hello world"); // вывод строки
    refresh(); // обновить экран
    getch(); // ждём нажатия символа
    
    endwin(); // завершение работы с ncurses

    // while (true)
    // {
    //     for (size_t i = 0; i < 100; i++)
    //     {
    //         std::cout << film[i];
    //         std::this_thread::sleep_for(std::chrono::milliseconds(42));
    //     }
    // }
    
    
}
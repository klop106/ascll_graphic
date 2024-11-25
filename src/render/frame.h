#ifndef FRAME
#define FRAME

#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <ncurses.h>

#include "vector_2d.h"

class Frame
{
private:
    int size_x;
    int size_y;

public:
    Frame();
    ~Frame();

    size_t get_size_x() { return size_x; }
    size_t get_size_y() { return size_y; }

    void clean_up();
    void show();
    void mark_pixel(const size_t _i, const size_t _j, const char _pixel_value);

    Vector2 get_pixel_position(const size_t _i, const size_t _j) const;
};

#endif

#include "frame.h"

Frame::Frame() 
{  
    initscr();
    getmaxyx(stdscr, size_x, size_y);
    move(0, 0);
}

Frame::~Frame()
{
    endwin();
}

void Frame::show()
{
    refresh();
}

void Frame::clean_up()
{
    clear();
    refresh();
}

void Frame::mark_pixel(const size_t _i, const size_t _j, const char _pixel_value) 
{ 
    move(_i, _j);
    printw(&_pixel_value);
}

Vector2 Frame::get_pixel_position(const size_t _i, const size_t _j) const
{
    return Vector2(_i, _j);
}

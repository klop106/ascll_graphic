#include "frame.h"


winsize Frame::get_window_size()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w;
}

Frame::Frame() 
{  
    clean_up();
    size_x = get_window_size().ws_col;
    size_y = get_window_size().ws_row;    
    init();
}

void Frame::show()
{
    clean_up();
    std::cout << image;
    init();
}

std::string Frame::get_frame()
{   
    std::string _image;
    _image = image;
    init();
    return _image;
}

void Frame::clean_up()
{
    std::cout << "\x1B[2J\x1B[H";
}

void Frame::init()
{
    for(int i = 0; i < size_y; i++){
        for(int j = 0; j < size_x; j++) { image[i*size_x + j] = ' '; }
        image[(i + 1)*size_x - 1] = '\n';
    }
    image[size_x * size_y] = '\0';
}

void Frame::mark_pixel(const size_t _i, const size_t _j, const char _pixel_value) 
{ 
   image[_j*size_x + _i] = _pixel_value;
}

Vector2 Frame::get_pixel_position(const size_t _i, const size_t _j) const
{
    float koeff_screen = static_cast<float>(size_x) / static_cast<float>(size_y);
    return Vector2((2. * (_i - size_x / 2.) / size_x) * koeff_screen, 2. * (size_y / 2. - _j) / size_y);
}


// Frame::Frame() 
// {  
//     initscr();
//     getmaxyx(stdscr, size_x, size_y);
//     move(0, 0);
// }

// Frame::~Frame()
// {
//     endwin();
// }

// void Frame::show()
// {
//     refresh();
// }

// void Frame::clean_up()
// {
//     clear();
//     refresh();
// }

// void Frame::mark_pixel(const size_t _i, const size_t _j, const char _pixel_value) 
// { 
//     move(_i, _j);
//     printw(&_pixel_value);
// }

// Vector2 Frame::get_pixel_position(const size_t _i, const size_t _j) const
// {
//     return Vector2(_i, _j);
// }

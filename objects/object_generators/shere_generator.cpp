#include <fstream>
#include <cmath>

using namespace std;

int main() 
{
    const double PI = 3.14;
    const double r = 1;

    double step = 1;

    ofstream points;
    points.open("sphere_points.csv");
    int p = 2;
    points << 1 << "," << 0 << "," << 0 << "," << -1 << ",\n";
    for (double i = -PI / 2 + step; i < PI / 2 - step; i += step)
    {
        for (double j = 0 ; j < PI * 2; j += step)
        {
            points << p << "," << r * cos(i) * cos(j) << "," << r * cos(i) * sin(j) << "," << r * sin(i) << ",\n";
            p++;
        }
    }
    points << p << "," << 0 << "," << 0 << "," << 1 << ",\n";
    points.close();

    ofstream poligons;
    poligons.open("sphere_poligons.csv");
    
    for (int i = 2 ; i < p - static_cast<int>(2 * PI / step); i++)
    {
            poligons << i << "," << i << "," << i + 1 << "," << i + static_cast<int>(2 * PI / step) << ",\n";
            poligons << i << "," << i << "," << i + static_cast<int>(2 * PI / step) - 1 << "," << i + static_cast<int>(2 * PI / step) << ",\n";
    }
    for (int i = 2 ; i < static_cast<int>(2 * PI / step) - 1; i++)
    {
            poligons << i << "," << 1 << "," << i << "," << i + 1 << ",\n";
    }
    for (int i = p - static_cast<int>(2 * PI / step); i < p - 2; i++)
    {
            poligons << i << "," << p << "," << i << "," << i + 1 << ",\n";
    }
    poligons.close();

}

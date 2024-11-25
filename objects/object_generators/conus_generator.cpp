#include <fstream>
#include <cmath>

using namespace std;

int main() 
{
    const double PI = 3.14;
    const double r = 1;
    const size_t n = 50;

    double step_phi = 2 * PI / n;
    double phi = 0;

    ofstream points;
    points.open("conus_points.csv");
    points << 1 << "," << 0 << "," << 0 << "," << 2 << ",\n";
    for (size_t i = 1; i < n; i++)
    {
        points << i + 1 << "," << r * cos(phi)  << "," << r * sin(phi) << "," << 0 << ",\n";
        phi += step_phi;
    }
    points << n + 1 << "," << 0 << "," << 0 << "," << 0 << ",\n";
    points.close();

    ofstream poligons;
    poligons.open("conus_poligons.csv");
    for (size_t i = 1; i < n - 1; i++)
    {
        poligons << i << "," << i + 1 << "," << i + 2 << "," << 1 << ",\n";
        phi += step_phi;
    }
    poligons << n - 1 << "," << n << "," << 2 << "," << 1 << ",\n";

    for (size_t i = 1; i < n - 1; i++)
    {
        poligons << n - 1 + i << "," << i + 1 << "," << i + 2 << "," << n + 1 << ",\n";
        phi += step_phi;
    }
    poligons << 2 * (n - 1) << "," << n << "," << 2 << "," << n + 1 << ",\n";
    poligons.close();
}

#include <fstream>
#include <cmath>

using namespace std;

int main() 
{
    const int N = 20;
    const double PI = 3.14;    
    const double delta_phi = PI / N;
    const double r = 1;

    double step = 1;

    ofstream points;
    points.open("sphere_points.csv");
    int p = 2;
    points << 1 << "," << 0 << "," << 0 << "," << -1 << ",\n";
    for (double i = 0; i < N / 2; i++)
    {
        for (double j = 0 ; j < N; j++)
        {
            points << p << "," << r * cos(i * delta_phi - PI / 2) * cos(j * delta_phi) << "," << r * cos(i * delta_phi - PI / 2) * sin(j * delta_phi) << "," << r * sin(i * delta_phi - PI / 2) << ",\n";
            p++;
        }
    }
    points << p << "," << 0 << "," << 0 << "," << 1 << ",\n";
    points.close();

    ofstream poligons;
    poligons.open("sphere_poligons.csv");
    
    for (int i = 2 ; i < N -1 ; i++)
    {
        poligons << i << "," << 1 << "," << i << "," << i + 1 << ",\n";
    }
    for (int i = 2 ; i < p; i++)
    {
        poligons << i << "," << i << "," << i + 1 << "," << i + N << ",\n";
    }
    for (int i = 1 + N * (N / 2 - 1); i < N * (N / 2); i++)
    {
        poligons << i << "," << i << "," <<  i + 1 << "," << N * (N / 2) << ",\n";
    }
    poligons.close();

}

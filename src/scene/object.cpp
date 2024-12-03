#include "object.h"

Object::Object(std::string _file_name, const Material& _material)
{
    material = _material;

    Json::Value root;
    Json::Reader reader;

    std::ifstream file(_file_name);
    if(!reader.parse(file, root, true)){
	    std::cerr  << "Failed to parse object\n" << reader.getFormattedErrorMessages();
        exit(1);
    }

    std::ifstream _points, _poligons;
    _points.open(root["points"].asString());
    _poligons.open(root["poligons"].asString());

    std::vector<Point> points;
    while (!_points.eof())
    {
        std::string s;
        _points >> s;
        points.push_back(Point(get_points(s)[0], get_points(s)[1], get_points(s)[2]));
    }
    while (!_poligons.eof())
    {
        std::string s;
        _poligons >> s;
        poligons.push_back(Poligon(points[get_node_ids(s)[0] - 1], points[get_node_ids(s)[1] - 1], points[get_node_ids(s)[2] - 1]));
    }
    _points.close();
    _poligons.close();
}


double* Object::get_points(const std::string _str)
{
    double coords[3];
    std::string value = "";
    int p = -1;
    for (size_t i = 0; i < _str.length(); i++)
    {
        if(_str[i] == ',')
        {
            if (p != -1)
            {
                coords[p] = stod(value);
            }
            value = "";
            p++;
        } else {
            value += _str[i];
        }   
    }
    return coords;
}


int* Object::get_node_ids(const std::string _str)
{
    int ids[3];
    std::string value = "";
    int p = -1;
    for (size_t i = 0; i < _str.length(); i++)
    {
        if(_str[i] == ',')
        {
            if (p != -1)
            {
                ids[p] = stoi(value);
            }
            value = "";
            p++;
        } else {
            value += _str[i];
        }
    }
    return ids;
}


info Object::intersect(const Vector3 _direc, const Point _pos, const Poligon* _parent_polig)
{
    double min_distance = __DBL_MAX__;
    Point intersection_point;
    inter_info _info = std::make_tuple(false, Point(), nullptr);

    for (size_t i = 0; i < poligons.size(); i++) {
        if (&poligons[i] == _parent_polig)
        {
           continue;
        }
        std::tuple<bool, Point, Poligon*> intersect = poligons[i].intersect(_direc, _pos);
        if (std::get<0>(intersect))
        {
            Point point = std::get<1>(intersect);
            double distance = (point - _pos).norm();
            if (min_distance > distance) 
            { 
                min_distance = distance; 
                _info = intersect;
            }
        }
    }
    return std::tuple_cat(_info, std::make_tuple(material));   
}


Object Object::transform(const LinearTransformation _transform)
{
    for (auto it = poligons.begin(); it != poligons.end(); it++) {
        (*it).transform(_transform);
    } 
    return *this;
}


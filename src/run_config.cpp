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
#include <json/json.h>

const std::string CONFIG_PATH = "../configs/";

class Runner
{
private:
    std::vector<Object> parseObjects(const Json::Value root);
    std::vector<LightSource> parseLights(const Json::Value root);
    PointOfView parsePov(const Json::Value root);
    size_t progressBarLength();
   
public:
    Runner(int argc, char *argv[]);
    
};

size_t Runner::progressBarLength()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col - 17;
}

PointOfView Runner::parsePov(const Json::Value root)
{
    Json::Value itr = root["pov"];
    return  PointOfView(
                Vector3(
                    itr["normal"]["x"].asFloat(), 
                    itr["normal"]["y"].asFloat(), 
                    itr["normal"]["z"].asFloat()
                ),
                Vector3(
                    itr["tang1"]["x"].asFloat(), 
                    itr["tang1"]["y"].asFloat(), 
                    itr["tang1"]["z"].asFloat()
                ),
                Vector3(
                    itr["tang2"]["x"].asFloat(), 
                    itr["tang2"]["y"].asFloat(), 
                    itr["tang2"]["z"].asFloat()
                ),
                Point(
                    itr["position"]["x"].asFloat(), 
                    itr["position"]["y"].asFloat(), 
                    itr["position"]["z"].asFloat()
                )
            );
}


std::vector<Object> Runner::parseObjects(const Json::Value root)
{
    std::vector<Object> objects;
    for (auto itr : root["objects"]) {
        float albedo[3] = {
            itr["material"]["attenuation"][0].asFloat(), 
            itr["material"]["attenuation"][1].asFloat(), 
            itr["material"]["attenuation"][2].asFloat()
        };
        objects.push_back(
            Object(
                itr["template"].asString(), 
                Material(
                    itr["material"]["spec_reflect"].asFloat(), 
                    itr["material"]["diffuse_reflect"].asFloat(), 
                    itr["material"]["specular_exponent"].asFloat(),
                    itr["material"]["specularity"].asFloat(),
                    albedo
                )
            ).transform(
                LinearTransformation().scaleTransform(itr["scale"].asFloat())
            ).transform(
                LinearTransformation().shiftTransform(
                    Vector3(
                        itr["position"]["x"].asFloat(), 
                        itr["position"]["y"].asFloat(), 
                        itr["position"]["z"].asFloat()
                    )
                )
            )
        );
    }
    return objects;
}


std::vector<LightSource> Runner::parseLights(const Json::Value root)
{
    std::vector<LightSource> lights;
    for (auto itr : root["light_sources"]) {
        lights.push_back(
            LightSource(
                Point(
                    itr["position"]["x"].asFloat(), 
                    itr["position"]["y"].asFloat(), 
                    itr["position"]["z"].asFloat()
                ),
                itr["intensity"].asFloat()
            )
        );
    }
    return lights;
}


Runner::Runner(int argc, char *argv[])
{
    std::cout << "Compiling scene - start" << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (argc > 2)
    {
        std::cerr << "invalid keys";
        exit(1);
    }

    std::ifstream config;
    Json::Value root;
    Json::Reader reader;

    try
    {
        config.open(CONFIG_PATH + argv[1]);
    }
    catch(const std::ifstream::failure& e)
    {
        std::cerr << "Exception opening file";
        exit(1);
    }

    if(!reader.parse(config, root, true)){
	    std::cout  << "Failed to parse object\n" << reader.getFormattedErrorMessages();
    }

    Frame frame;
    PointOfView pov = parsePov(root);
    std::vector<LightSource> lights = parseLights(root);
    std::vector<Object> objects = parseObjects(root);
    Render render(&pov, &objects, &lights, &frame);
    
    std::vector<std::string> film;
    double v = 0.1;
    size_t scene_length = 100;

    std::cout << "Compiling objects - done" << std::endl;
    std::cout << "Render scene - start" << std::endl;
    std::cout << "Render progress: " << std::flush;

    pov.transform(LinearTransformation().rotationTransform(Vector3(0, 1, 0), 0.5));
    for (size_t i = 0; i < scene_length; i++)
    {   
        size_t progress = 0;
        if (static_cast<size_t>(scene_length / progressBarLength()) == progress)
        {
            std::cout << "#" << std::flush;
            progress = 0;
        }
        progress++;
        
        pov.transform(LinearTransformation().rotationTransform(Vector3(0, 0, 1), 0.05));
        render.render();
        film.push_back(frame.get_frame());
    }

    std::cout << "\nRender scene - done" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    while (true)
    {
        for (size_t i = 0; i < 100; i++)
        {
            std::cout << film[i] << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

}

int main(int argc, char *argv[]) {
    Runner(argc, argv);
}
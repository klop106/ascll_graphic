
# [AscllGraphic](https://github.com/klop106/AscllGraphic.git)
---
## Автор

[Веретельник В.Д](https://github.com/klop106)

## Стек технологий

[![c++](https://img.shields.io/badge/C++-v13.1.6-red)]()
[![c++](https://img.shields.io/badge/ncurses-v2.6.32-green)]()

## Общий обзор 
---
AscllGraphic это пакет для визуализации 3d моделей, создания сцен с несколькими обьектами, освещением и анимациями. Взаимодействие с программой происходит через терминал linux и json файлы конфигурации. Изображение генерируется в терминале.

## Установка
---
Клонировать репозиторий и перейти в него в командной строке
```terminal
git clone https://github.com/klop106/ascll_graphic.git
cd ascll_graphic 
```
Собрать бинарный файл
```terminal
mkdir build
cd build
cmake ..
make
```

## Структура пакета
---
```bash
├── CMakeLists.txt
├── CMakePresets.json
├── CMakeUserPresets.json
├── README.md
├── configs
│   ├── config.json
│   └── sphere.json
├── motion
│   ├── circle.json
│   └── line.json
├── objects
│   ├── 1poligon.json
│   ├── 1poligon_points.csv
│   ├── 1poligon_poligons.csv
│   ├── conus.json
│   ├── conus_points.csv
│   ├── conus_poligons.csv
│   ├── object_generators
│   │   ├── conus_generator.cpp
│   │   └── shere_generator.cpp
│   ├── piramid.json
│   ├── piramid_points.csv
│   ├── piramid_poligons.csv
│   ├── plane.json
│   ├── plane_points.csv
│   ├── plane_poligons.csv
│   ├── sphere.json
│   ├── sphere_points.csv
│   ├── sphere_poligons.csv
│   └── tor.json
├── src
│   ├── linear_field_operations
│   │   ├── CMakeLists.txt
│   │   ├── linear_transform.cpp
│   │   ├── linear_transform.h
│   │   ├── point.cpp
│   │   ├── point.h
│   │   ├── vector.cpp
│   │   └── vector.h
│   ├── render
│   │   ├── CMakeLists.txt
│   │   ├── frame.cpp
│   │   ├── frame.h
│   │   ├── render.cpp
│   │   ├── render.h
│   │   ├── vector_2d.cpp
│   │   └── vector_2d.h
│   ├── run_config.cpp
│   └── scene
│       ├── CMakeLists.txt
│       ├── light_source.cpp
│       ├── light_source.h
│       ├── object.cpp
│       ├── object.h
│       ├── point_of_view.cpp
│       ├── point_of_view.h
│       ├── poligon.cpp
│       └── poligon.h
├── vcpkg-configuration.json
└── vcpkg.json

```
* ```code``` содержит исходники проекта
* ```configs``` конфигурационные файлы сцен
* ```motion``` траектории движения камеры и объектов
* ```objects``` объекты которые можно расположить на сцене

## Интерфейс взаимодействия
---
Создание сцен и анимаций происходит через  заполнение конфигурационного файла *config.json*. После чего вводится команда:
```
.\run_scene args
``` 
Ключи ```args``` реализуют дополнительное взаимодействие с выводимым контентом.
Возможные ключи:

* ```config_name``` в случае, если *config.json* не один необходимо ввести этот ключ и название нужного файла, иначе будет выбран первый *.json* файл в папке */config* 
### Структура *config.json*
Поле ```"type"``` содержит тип генерируемого контента:
* ```Animation = 0```
* ```Picture = 1```
  
Содержание поля ```"pov"```  генерируемого контента определяется полем ```"type"``` и может содержать:
* POV
* Движение POV по заданной траектории
```json
{
    "type": "тип генерируемого контента bool",
    "objects": [
        {
            "pos": {
                "x": "double value",
                "y": "double value",
                "z": "double value"
            },
            "scale": "double value",
            "template": "../objects/object.json"
        },
        {
            "pos": {
                "x": "double value",
                "y": "double value",
                "z": "double value"
            },
            "scale": "double value",
            "template": "../objects/object1.json",
            "material": {
                "spec_reflect": 0,
                "diffuse_reflect": 0,
                "specular_exponent": 0,
                "specularity": 0.5,
                "attenuation": [1.0, 0.1, 0.0]
            }
        },
        ...
    ],
    "light_sources": [
        {
            "pos": {
                "x": "double value",
                "y": "double value",
                "z": "double value"
            },
            "intensity": "intensity value int"
        },
        {
            "pos": {
                "x": "double value",
                "y": "double value",
                "z": "double value"
            },
            "intensity": "intensity value int"
        }
        ...
    ],
    "pov": {
        "position": {
                "x": -12.0,
                "y": 0,
                "z": 0
        },
        "normal": {
                "x": 1,
                "y": 0,
                "z": 0
        },
        "tang1": {
                "x": 0,
                "y": 1,
                "z": 0
        },
        "tang2": {
                "x": 0,
                "y": 0,
                "z": 1
        }
    }
}
``` 

### Задание собственных 3D объектов
Создание пользовательских объктов также реализуется путем задания значений в *.json* файле.
Каждый объект состоит из набора полигонов, кодируемых тремя точками в системе отсчета связанной с нулевой системой отсчета .
```json
{
    "points": "../objects/conus_points.csv",
    "poligons": "../objects/conus_poligons.csv"
}
```
## Пользовательские сценарии
---
Рассмотрим некоторые из примеров взаимодействия пользователя с программным пактом. Вместо создания новых объектов в пользовательских сцеариях будут использоваться предустановленные.  
### Изображение куба с одним источником освещения
Заполним файл *config.json*. Добавим на сцену куб с координатами *(4.0, 7.0, 8.5)* и источник света с координатами *(2.0, 0.5, 1.5)* и минимальной интенсивностью (0 интенсивность соответсвуют отсутствию света). Установим положение камеры(```"pos"```) и ее направление(```"orient"```).

```json
{
    "type": 0,
    "objects": [
        {
            "pos": {
                "x": 4.0,
                "y": 7.0,
                "z": 8.5
            },
            "scale": 1,
            "template": "./AscllGraphic/objects/cub.json"
        }
    ],
    "light_sources": [
        {
            "pos": {
                "x": 2.0,
                "y": 0.5,
                "z": 1.5
            },
            "intensity": 1
        }
    ],
    "pov": {
        "pos": {
                "x": 2.0,
                "y": 0.5,
                "z": 1.5
        },
        "orient": {
                "orient_x": 2.0,
                "orient_y": 0.5,
                "orient_z": 1.5
        }
    }
}
``` 
Теперь сохраним изображение данной сцены в файл *cub.txt*.
```
.\run_scene -s cub.txt
```
### Анимация пролета камеры вокруг сферы
Заполним файл *config.json*. Добавим на сцену сферу с координатами *(0.0, 0.0, 0.0)* и источник света с координатами *(2.0, 0.5, 1.5)*. В данном случае, так как тип контента анимация, ```"pov"``` будет меняться динамически со временем. Параметры поля ```"motion"``` зависят от выбранного типа движения камеры.

```json
{
    "type": 0,
    "objects": [
        {
            "position": {
                "x": 0.0,
                "y": 0.0,
                "z": 0.0
            },
            "scale": 1,
            "template": "./AscllGraphic/objects/sphere.json",
            "motion": {
                "type": 0
            }
        }
    ],
    "light_sources": [
        {
            "pos": {
                "x": 2.0,
                "y": 0.5,
                "z": 1.5
            },
            "intensity": 1
        }
    ],
    "pov": {
        "start_pos": {
                "x": 2.0,
                "y": 0.5,
                "z": 1.5
        },
        "start_orient": {
                "orient_x": 2.0,
                "orient_y": 0.5,
                "orient_z": 1.5
        },
        "motion": {
            "type": 1,
            "center": {
                "x": 0.0,
                "y": 0.0,
                "z": 0.0
            },
            "orientation": {
                "orient_x": 2.0,
                "orient_y": 0.5,
                "orient_z": 1.5
            },
            "radius": 10,
            "speed": 5,
        }
    }
}
``` 
У обьектов поле ```"motion"``` работает аналогично данному полю у ```"pov"```. В данном случае ```"motion": { "type": 0}``` , что соответсвует состоянию покоя.

Теперь выведем анимацию на экран. 
```
.\run_scene 
```
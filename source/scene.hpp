#ifndef SCENE_HPP
#define SCENE_HPP

#include<vector>
#include<functional>

#include"shaderset.hpp"
#include"doubleframebuffer.hpp"
#include"shape/shape.hpp"

class Scene
{
private:
    std::vector<std::pair<Shape*,fvec4>> initial;
    std::vector<std::pair<Shape*,fvec4>> fixed;
public:
    void performInitial(std::function<void(Shape*,const fvec4&)> func)
    {
        for(auto &p : initial)
        {
            func(p.first,p.second);
        }
    }
    void preformFixed(std::function<void(Shape*,const fvec4&)> func)
    {
        for(auto &p : fixed)
        {
            func(p.first,p.second);
        }
    }
};

#endif // SCENE_HPP

#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>

class Entity{
private:
    string name;
public:
    virtual ~Entity() = default;
};

#endif
#include "attribute.h"
#include <stdio.h>

void initializeAttribute(void* value, char* type, char* name, Attribute* dest)
{
    dest->value = value;
    dest->type = type;
    dest->name = name;
}

void* getAttrValue(const char* name, Attribute* attributes, unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (attributes[i].name == name)
        {
            return attributes[i].value;
        }
    }
}

void setAttrValue(const char* name, Attribute* attributes, unsigned int size, void* value)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        if (attributes[i].name == name)
        {
            attributes[i].value = value;
        }
    }
}

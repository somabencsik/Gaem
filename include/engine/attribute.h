#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

typedef struct _attribute Attribute;
struct _attribute
{
    void* value;
    char* type;
    char* name;
};

void initializeAttribute(void* value, char* type, char* name, Attribute* dest);
void* getAttrValue(const char* name, Attribute* attributes, unsigned int size);
void setAttrValue(const char* name, Attribute* attributes, unsigned int size, void* value);

#endif // ATTRIBUTE_H
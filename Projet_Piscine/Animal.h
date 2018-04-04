#ifndef ANIMAL_H_INCLUDED
#define ANIMAL_H_INCLUDED
#include"Espece.h"

class Animal: public Espece
{
private:
    float m_taille; ///à titre informatif ...

public:
    Animal();
    ~Animal();

};


#endif // ANIMAL_H_INCLUDED

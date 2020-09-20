#include "Tekil.h"

Tekil::Tekil()
{
  this->veri=-1;
}

int Tekil::getVeri()
{
    return veri;
}

void Tekil::setVeri(int veri)
{
    this->veri=veri;
}

Tekil::~Tekil()
{
}

Tekil* Tekil::instance=NULL;

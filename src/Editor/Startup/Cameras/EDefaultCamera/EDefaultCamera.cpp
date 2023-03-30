#include "EDefaultCamera.h"

EDefaultCamera::EDefaultCamera() :
    IECamera("", 0)
{
    this->setType(IEResource::Type::Editor);
}

EDefaultCamera::~EDefaultCamera()
{

}

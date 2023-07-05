#include "IESerializeTranslator.h"

void IESerializeTranslator::write(QDataStream& out, const std::any& val)
{
    size_t hashcode = val.type().hash_code();

    if(hashcode == hashcodes[0]) { out << hashcode << std::any_cast<QVector2D>(val); }
    else if(hashcode == hashcodes[1]) { out << hashcode << std::any_cast<QVector3D>(val); }
    else if(hashcode == hashcodes[2]) { out << hashcode << std::any_cast<QVector4D>(val); }
    else if(hashcode == hashcodes[3]) { out << hashcode << std::any_cast<QMatrix4x4>(val); }
    else { out << typeid(char).hash_code() << (char)'~'; }
}

std::any IESerializeTranslator::read(QDataStream& in)
{
    size_t hashcode = 0;
    in >> hashcode;

    std::any data;

    if(hashcode == hashcodes[0]) { QVector2D temp; in >> temp; return (data = temp); }
    else if(hashcode == hashcodes[1]) { QVector3D temp; in >> temp; return (data = temp); }
    else if(hashcode == hashcodes[2]) { QVector4D temp; in >> temp; return (data = temp); }
    else if(hashcode == hashcodes[3]) { QMatrix4x4 temp; in >> temp; return (data = temp); }
    else { char temp; in >> temp; return (data = temp); }
}

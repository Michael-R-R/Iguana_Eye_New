#include "IEGameState.h"
#include "IEGame.h"
#include "IESerialize.h"
#include "IEFile.h"

void IEGameState::onResize(const glm::vec2& val)
{
    onResize(val[0], val[1]);
}

void IEGameState::serializeTemporary(IEGame& game)
{
    game.onSerialize();
    IESerialize::write<IEGame>("./resources/temp/backup/game.iedat", &game);
}

void IEGameState::deserializeTemporary(IEGame& game)
{
    if(!IEFile::doesFileExist("./resources/temp/backup/game.iedat"))
        return;

    game.onDeserialize();
    IESerialize::read<IEGame>("./resources/temp/backup/game.iedat", &game);

    IEFile::removeFile("./resources/temp/backup/game.iedat");
}

QDataStream& IEGameState::serialize(QDataStream& out, const IESerializable&) const
{
    return out;
}

QDataStream& IEGameState::deserialize(QDataStream& in, IESerializable&)
{
    return in;
}

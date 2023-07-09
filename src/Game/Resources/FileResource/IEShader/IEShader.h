#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QString>
#include <glm/glm.hpp>

#include "IEFileResource.h"

class IEShader : public QOpenGLShaderProgram, public IEFileResource
{
protected:
    QString vertexSource;
    QString fragmentSource;

public:
    IEShader(QObject* parent = nullptr);
    IEShader(const QString& path, QObject* parent = nullptr);
    IEShader(const IEShader&) = delete;
    virtual ~IEShader();

    bool operator==(const IEShader& other) { return IEResource::operator==(other); }
    bool operator!=(const IEShader& other) { return IEResource::operator!=(other); }
    bool operator<(const IEShader& other) { return IEResource::operator<(other); }
    bool operator>(const IEShader& other) { return IEResource::operator>(other); }

    bool build();

    void setBool(const char* name, const bool val);
    void setInt(const char* name, const int val);
    void setFloat(const char* name, const float val);
    void setVec2(const char* name, const glm::vec2& val);
    void setVec3(const char* name, const glm::vec3& val);
    void setVec4(const char* name, const glm::vec4& val);
    void setMat2(const char* name, const glm::mat3& val);
    void setMat3(const char* name, const glm::mat3& val);
    void setMat4(const char* name, const glm::mat4& val);

    QString getVertexSrc() const { return vertexSource; }
    QString getFragmentSrc() const { return fragmentSource; }

    void setVertexSrc(const QString& val) { vertexSource = val; }
    void setFragmentSrc(const QString& val) { fragmentSource = val; }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

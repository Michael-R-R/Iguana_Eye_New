#pragma once

#include <QDataStream>
#include <QOpenGLVertexArrayObject>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <gl/GL.h>

#include "IEResource.h"
#include "IEBufferContainer.h"
#include "IEUniform.h"

class IEShader;

class IERenderable : public QOpenGLVertexArrayObject, public IEResource
{
public:
    enum class RenderType
    {
        None, Vertex, Index, I_Vertex, I_Index
    };

private:
    RenderType renderType;
    GLenum drawType;

    unsigned long long meshId;
    unsigned long long materialId;
    unsigned long long shaderId;

    IEBufferContainer<QVector2D>* vec2BufferContainer;
    IEBufferContainer<QVector3D>* vec3BufferContainer;
    IEBufferContainer<QVector4D>* vec4BufferContainer;
    IEBufferContainer<QMatrix4x4>* mat4BufferContainer;

    IEUniform uniformData;

public:
    IERenderable();
    IERenderable(const unsigned long long id);
    IERenderable(const IERenderable& other);
    ~IERenderable();

    bool operator==(const IERenderable& other) { return IEResource::operator==(other); }
    bool operator!=(const IERenderable& other) { return IEResource::operator!=(other); }
    bool operator<(const IERenderable& other) { return IEResource::operator<(other); }
    bool operator>(const IERenderable& other) { return IEResource::operator>(other); }

    void build(IEShader* shader);
    void bindUniformData(IEShader* shader);
    int instanceCount() const;

    RenderType getRenderType() const { return renderType; }
    GLenum getDrawType() const { return drawType; }
    unsigned long long getMeshId() const { return meshId; }
    unsigned long long getMaterialId() const { return materialId; }
    unsigned long long getShaderId() const { return shaderId; }
    IEBufferContainer<QVector2D>* getVec2BufferContainer() const { return vec2BufferContainer; }
    IEBufferContainer<QVector3D>* getVec3BufferContainer() const { return vec3BufferContainer; }
    IEBufferContainer<QVector4D>* getVec4BufferContainer() const { return vec4BufferContainer; }
    IEBufferContainer<QMatrix4x4>* getMat4BufferContainer() const { return mat4BufferContainer; }
    IEUniform& getUniformData() { return uniformData; }

    void setRenderType(const RenderType val) { renderType = val; }
    void setDrawType(const GLenum val) { drawType = val; }
    void setMeshId(const unsigned long long val) { meshId = val; }
    void setMaterialId(const unsigned long long val) { materialId = val; }
    void setShaderId(const unsigned long long val) { shaderId = val; }

    friend QDataStream& operator<<(QDataStream& out, const IERenderable& renderable)
    {
        out << renderable.id
            << renderable.renderType
            << renderable.meshId
            << renderable.materialId
            << renderable.shaderId
            << *renderable.vec2BufferContainer
            << *renderable.vec3BufferContainer
            << *renderable.vec4BufferContainer
            << *renderable.mat4BufferContainer
            << renderable.uniformData;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IERenderable& renderable)
    {
        in >> renderable.id
           >> renderable.renderType
           >> renderable.meshId
           >> renderable.materialId
           >> renderable.shaderId
           >> *renderable.vec2BufferContainer
           >> *renderable.vec3BufferContainer
           >> *renderable.vec4BufferContainer
           >> *renderable.mat4BufferContainer
           >> renderable.uniformData;

        return in;
    }
};

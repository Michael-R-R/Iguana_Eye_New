#pragma once

class IEECSHierarchySystem;
class IEECSInputSystem;
class IEECSTransformSystem;

class ECSOnUpdateEvent
{
    // Does not own these pointers
    IEECSHierarchySystem* hierarchy;
    IEECSInputSystem* input;
    IEECSTransformSystem* transform;

public:
    ECSOnUpdateEvent(IEECSHierarchySystem* hierarchy_, IEECSInputSystem* input_,
                     IEECSTransformSystem* transform_);
    ~ECSOnUpdateEvent();

    IEECSHierarchySystem* getHierarchy() const;
    IEECSInputSystem* getInput() const;
    IEECSTransformSystem* getTransform() const;
};


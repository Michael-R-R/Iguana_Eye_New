#pragma once

class IEECSHierarchySystem;
class IEECSInputSystem;
class IEECSTransformSystem;

class ECSOnUpdateEvent
{
    // Does not own these pointers
    const IEECSHierarchySystem* hierarchy;
    const IEECSInputSystem* input;
    const IEECSTransformSystem* transform;

public:
    ECSOnUpdateEvent(IEECSHierarchySystem* hierarchy_, IEECSInputSystem* input_,
                     IEECSTransformSystem* transform_);
    ~ECSOnUpdateEvent();

    const IEECSHierarchySystem* getHierarchy() const;
    const IEECSInputSystem* getInput() const;
    const IEECSTransformSystem* getTransform() const;
};


local l_entity = nil
local inputComponent = nil
local cameraComponent = nil
local transformComponent = nil

local lastX = 0.0
local lastY = 0.0
local isCaptured = false
local yaw = -90.0
local pitch = 0.0

function start(entity)
    l_entity = entity

    inputComponent = game.ECS:inputComponent()
    cameraComponent = game.ECS:cameraComponent()
    transformComponent = game.ECS:transformComponent()
end

function update()
    local inputIndex = inputComponent:lookUpIndex(l_entity)
    local hasInput = inputComponent:getHasInput(inputIndex)
    if not hasInput then return nil end

    local cameraIndex = cameraComponent:lookUpIndex(l_entity)
    local activeIndex = cameraComponent:getActiveIndex()
    if cameraIndex ~= activeIndex then return nil end

    local transformIndex = transformComponent:lookUpIndex(l_entity)
    if transformIndex < 0 then return nil end

    local camera = cameraComponent:getActiveCamera()
    local dt = game.IETime:deltaTime()

    checkIfDirty(camera)
    updateMovement(camera, transformIndex, dt)
    updateRotation(camera, transformIndex, dt)
end

function checkIfDirty(camera)
    local isDirty = cameraComponent:getHasDirtyProj()
    if isDirty == false then return nil end

    local aspect = game.Application:viewportWidth() / game.Application:viewportHeight()
    local fov = camera.fov
    local near = camera.near
    local far = camera.far

    local projection = Mat4.new()
    projection:perspective(fov, aspect, near, far)
    camera.projection = projection:get()

    cameraComponent:setHasDirtyProj(false)
end

function updateMovement(camera, transformIndex, dt)
    local speed = camera.speed * dt
    local position = Vec3.new(transformComponent:getPosition(transformIndex))
    local rotation = Vec3.new(transformComponent:getRotation(transformIndex))
    local up = Vec3.new(camera.up)

    if game.IEInput:isPressed("Forward") then
        position = Vec3.new(position + (rotation * speed))
        transformComponent:setPosition(transformIndex, position:get())
    end

    if game.IEInput:isPressed("Backward") then
        position = Vec3.new(position - (rotation * speed))
        transformComponent:setPosition(transformIndex, position:get())
    end

    if game.IEInput:isPressed("Left") then
        local temp = Vec3.new()
        temp = temp:cross(rotation, up)
        temp = temp:normalize(temp)

        position = Vec3.new(position - (temp * speed))
        transformComponent:setPosition(transformIndex, position:get())
    end

    if game.IEInput:isPressed("Right") then
        local temp = Vec3.new()
        temp = temp:cross(rotation, up)
        temp = temp:normalize(temp)

        position = Vec3.new(position + (temp * speed))
        transformComponent:setPosition(transformIndex, position:get())
    end

    if game.IEInput:isPressed("Up") then
        position = Vec3.new(position + (up * speed))
        transformComponent:setPosition(transformIndex, position:get())
    end

    if game.IEInput:isPressed("Down") then
        position = Vec3.new(position - (up * speed))
        transformComponent:setPosition(transformIndex, position:get())
    end
end

function updateRotation(camera, transformIndex, dt)
    if game.IEInput:isPressed("Right Click") then
        local cursorPos = Vec2.new(game.IEInput:getCursorPos())

        if not isCaptured then
            isCaptured = true
            lastX = cursorPos:x()
            lastY = cursorPos:y()
        end

        local xoffset = cursorPos:x() - lastX
        local yoffset = cursorPos:y() - lastY

        lastX = cursorPos:x()
        lastY = cursorPos:y()

        local sensitivity = camera.sensitivity
        xoffset = xoffset * (sensitivity * dt)
        yoffset = yoffset * (sensitivity * dt)

        yaw = yaw + xoffset
        pitch = pitch - yoffset

        if pitch > 89.0 then pitch = 89.0
        elseif pitch < -89.0 then pitch = -89.0 end

        local x = math.cos(math.rad(yaw)) * math.cos(math.rad(pitch))
        local y = math.sin(math.rad(pitch))
        local z = math.sin(math.rad(yaw)) * math.cos(math.rad(pitch))
        local direction = Vec3.new(x, y, z)

        transformComponent:setRotation(transformIndex, direction:get())
    else
        isCaptured = false
    end
end
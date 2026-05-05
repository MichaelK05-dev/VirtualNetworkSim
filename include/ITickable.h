#pragma once

class ITickable {
public: 
virtual ~ITickable() = default;
virtual void onTick() = 0;
};
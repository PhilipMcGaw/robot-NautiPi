#pragma once
class ThermalController {
public:
    void update(float temp);
    bool shouldShutdown();
};

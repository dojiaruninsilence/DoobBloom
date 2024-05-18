#pragma once

#include "dUtils/dEvents/dInput.h"

namespace doob {

    class dWindowsInput : public dInput {
    public:
        virtual void init() override;

        virtual void shutdown() override;

        virtual bool isKeyPressed(const keyCode key) override;

        virtual bool isMouseButtonPressed(const mouseCode button) override;

        virtual dVec2<float> getMousePosition() override;
    };
}
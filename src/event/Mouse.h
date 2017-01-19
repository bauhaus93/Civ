#pragma once

enum class MouseButton{
    LEFT,
    RIGHT
};

struct Mouse{
    MouseButton button;
    Point pos;

    Mouse(MouseButton button_, const Point& pos_):
        button{ button_ },
        pos{ pos_ }{
    }

    Mouse(const Mouse& other):
        button{ other.button},
        pos{ other.pos }{
    }
};

#pragma once

namespace DawnBoard
{
    enum class FieldProgress {
        NEED_INIT, READY, RUNNING, END
    };

    struct FieldState
    {
        FieldProgress progress = FieldProgress::NEED_INIT;
    };

    struct Action
    {
    };
} // namespace DawnBoard

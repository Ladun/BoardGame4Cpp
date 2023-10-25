#pragma once

#include <DawnBoard/Base/Field.hpp>

namespace DawnBoard::Chess
{
    class ChessField : public Field
    {

        virtual void ApplyAction(Action action);

        virtual void AddObject(std::shared_ptr<Object> obj);
        virtual std::shared_ptr<Object> FindObject();

    };
} // namespace DawnBoard::Chess

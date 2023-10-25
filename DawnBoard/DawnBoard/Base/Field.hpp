#pragma once

#include <memory>

#include <DawnBoard/Base/Object.hpp>
#include <DawnBoard/Base/DataStruct.hpp>

namespace DawnBoard
{

    class Field
    {
    public:
        Field() = default;
        virtual ~Field() = default;

        virtual void ApplyAction(Action action) = 0;

        virtual void AddObject(std::shared_ptr<Object> obj) = 0;
        virtual std::shared_ptr<Object> FindObject() = 0;

        template<typename StateClass>
        StateClass* GetState() { return reinterpret_cast<StateClass*>(m_State.get()); }

    private:
        std::unique_ptr<FieldState> m_State;
    };
} // namespace DawnBoard

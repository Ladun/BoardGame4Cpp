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

        virtual void Init() = 0;
        virtual void Start() = 0;
        virtual void Clear() = 0;

        virtual void ApplyAction(Action& action) = 0;

        template<typename StateClass>
        StateClass* GetState() { return reinterpret_cast<StateClass*>(m_State.get()); }

    protected:
        std::unique_ptr<FieldState> m_State = nullptr;
    };
} // namespace DawnBoard

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

        virtual bool ApplyAction(Action& action) = 0;

        template<typename StateClass>
        StateClass* GetState() { return reinterpret_cast<StateClass*>(_state.get()); }

    protected:
        std::unique_ptr<FieldState> _state = nullptr;
    };
} // namespace DawnBoard

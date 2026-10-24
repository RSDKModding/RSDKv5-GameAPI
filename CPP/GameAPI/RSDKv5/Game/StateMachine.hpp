#pragma once

#include "../Types.hpp"
#include "Object.hpp"
#include <cstddef>

#if __clang__
#pragma clang diagnostic ignored "-Wmicrosoft-cast"
#endif

namespace RSDK
{
#define SET_CURRENT_STATE() RSDK::currentState = __func__
#define StateMachine_None   nullptr

extern const char *currentState;

template <typename E> static RSDK_FORCE_INLINE void *ToGenericPtr(void (E::*ptr)())
{
    // converts from E:: -> void* without the compiler interfering :]
    union {
        void (E::*in)();
        void *out;
    } u;
    u.in = ptr;
    return u.out;
}

template <typename T> struct StateMachine {

    enum Priorities {
        PRIORITY_NONE   = 0,
        PRIORITY_LOCKED = 0xFF,
    };

    RSDK_FORCE_INLINE void Init()
    {
        state    = nullptr;
        timer    = 0;
        unknown1 = 0;
        unknown2 = 0;
        unknown3 = 0;
        priority = 0;
    }

    RSDK_FORCE_INLINE bool32 Set(void (T::*state)(), uint8 priority = PRIORITY_NONE)
    {
        if (priority < this->priority || this->priority == PRIORITY_LOCKED)
            return false;

        this->state    = state;
        this->timer    = 0;
        this->priority = priority;
        return true;
    }

    RSDK_FORCE_INLINE bool32 SetAndRun(void (T::*state)(), GameObject::Entity *self, uint8 priority = PRIORITY_NONE)
    {
        bool32 applied = Set(state, priority);
        if (applied)
            Run(self);
        return applied;
    }

    RSDK_FORCE_INLINE bool32 QueueForTime(void (T::*state)(), uint32 duration, uint8 priority = PRIORITY_NONE)
    {
        if (priority < this->priority || this->priority == PRIORITY_LOCKED)
            return false;

        this->state    = state;
        this->timer    = duration;
        this->priority = priority;

        return true;
    }

    template <typename E> RSDK_FORCE_INLINE bool32 Set(void (E::*state)(), uint8 priority = PRIORITY_NONE)
    {
        if (priority < this->priority || this->priority == PRIORITY_LOCKED)
            return false;

        // converts from E:: -> T:: without the compiler interfering :]
        union {
            void (E::*in)();
            void (T::*out)();
        } u;
        u.in = state;

        this->state    = u.out;
        this->timer    = 0;
        this->priority = priority;
        return true;
    }

    template <typename E> RSDK_FORCE_INLINE bool32 SetAndRun(void (E::*state)(), GameObject::Entity *self, uint8 priority = PRIORITY_NONE)
    {
        bool32 applied = Set(state, priority);
        if (applied)
            Run(self);
        return applied;
    }

    template <typename E> RSDK_FORCE_INLINE bool32 QueueForTime(void (E::*state)(), uint32 duration, uint8 priority = PRIORITY_NONE)
    {
        if (priority < this->priority || this->priority == PRIORITY_LOCKED)
            return false;

        // converts from E:: -> T:: without the compiler interfering :]
        union {
            void (E::*in)();
            void (T::*out)();
        } u;
        u.in = state;

        this->state    = u.out;
        this->timer    = duration;
        this->priority = priority;
        return true;
    }

    RSDK_FORCE_INLINE bool32 Set(std::nullptr_t, uint8 priority = PRIORITY_NONE)
    {
        if (priority < this->priority || this->priority == PRIORITY_LOCKED)
            return false;

        this->state    = nullptr;
        this->timer    = 0;
        this->priority = priority;
        return true;
    }

    RSDK_FORCE_INLINE bool32 QueueForTime(std::nullptr_t, uint32 duration, uint8 priority = PRIORITY_NONE)
    {
        if (priority < this->priority || this->priority == PRIORITY_LOCKED)
            return false;

        this->state    = nullptr;
        this->timer    = duration;
        this->priority = priority;
        return true;
    }

    // overloads below are for member function pointer states, keeping the syntax consistent
    // Say that State_Idle is a public function: .Set(TestObject::State_Idle) -> .Set(&TestObject::State_Idle)
    RSDK_FORCE_INLINE bool32 Set(void (T::**state)(), uint8 priority = PRIORITY_NONE) { return Set(*state, priority); }
    RSDK_FORCE_INLINE bool32 SetAndRun(void (T::**state)(), GameObject::Entity *self, uint8 priority = PRIORITY_NONE)
    {
        return SetAndRun(*state, self, priority);
    }

    template <typename E> RSDK_FORCE_INLINE bool32 Set(void (E::**state)(), uint8 priority = PRIORITY_NONE) { return Set(*state, priority); }
    template <typename E> RSDK_FORCE_INLINE bool32 SetAndRun(void (E::**state)(), GameObject::Entity *self, uint8 priority = PRIORITY_NONE)
    {
        return SetAndRun(*state, self, priority);
    }

    RSDK_FORCE_INLINE bool32 QueueForTime(void (T::**state)(), uint32 duration, uint8 priority = PRIORITY_NONE)
    {
        return QueueForTime(*state, duration, priority);
    }

    template <typename E> RSDK_FORCE_INLINE bool32 QueueForTime(void (E::**state)(), uint32 duration, uint8 priority = PRIORITY_NONE)
    {
        return QueueForTime(*state, duration, priority);
    }

    RSDK_FORCE_INLINE void Run(GameObject::Entity *self)
    {
        if (timer)
            timer--;

        if (state) {
            currentState = NULL;

#if RETRO_USE_MOD_LOADER
            // converts from T:: -> void* without the compiler interfering :]
            union {
                void (T::*in)();
                void (*out)();
            } u;
            u.in = state;

            bool32 skipState = modTable->HandleRunState_HighPriority(u.out);

            if (!skipState)
                (((T *)self)->*state)();

            modTable->HandleRunState_LowPriority(u.out, skipState);
#else
            (((T *)self)->*state)();
#endif
        }
    }

    RSDK_FORCE_INLINE bool32 Matches(void (T::*other)()) { return state == other; }
    RSDK_FORCE_INLINE bool32 Matches(void (T::**other)()) { return ToGenericPtr(state) == ToGenericPtr(*other); }

    template <typename E> RSDK_FORCE_INLINE bool32 Matches(void (E::*other)()) { return state == (void (T::*)())other; }
    template <typename E> RSDK_FORCE_INLINE bool32 Matches(void (E::**other)()) { return ToGenericPtr(state) == ToGenericPtr(*other); }

    RSDK_FORCE_INLINE bool32 Matches(std::nullptr_t) { return state == nullptr; }

    RSDK_FORCE_INLINE void Copy(StateMachine<T> *other)
    {
        this->state    = other->state;
        this->timer    = other->timer;
        this->unknown1 = other->unknown1;
        this->unknown2 = other->unknown2;
        this->unknown3 = other->unknown3;
        this->priority = other->priority;
    }

    template <typename E> RSDK_FORCE_INLINE void Copy(StateMachine<T> *other)
    {
        // converts from E:: -> T:: without the compiler interfering :]
        union {
            void (E::*in)();
            void (T::*out)();
        } u;
        u.in = other->state;

        this->state    = u.out;
        this->timer    = other->timer;
        this->unknown1 = other->unknown1;
        this->unknown2 = other->unknown2;
        this->unknown3 = other->unknown3;
        this->priority = other->priority;
    }

    void (T::*state)();
    int32 timer;
    uint8 unknown1;
    uint8 unknown2;
    uint8 unknown3;
    uint8 priority;
};

} // namespace RSDK
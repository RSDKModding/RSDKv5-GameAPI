#pragma once

#include "../Types.hpp"
#include "Object.hpp"

#if __clang__
#pragma clang diagnostic ignored "-Wmicrosoft-cast"
#endif

namespace RSDK
{
#define SET_CURRENT_STATE() RSDK::currentState = __func__
#define StateMachine_None nullptr

extern const char *currentState;

template <typename E> static inline void *ToGenericPtr(void (E::*ptr)())
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

    inline void Init()
    {
        state    = nullptr;
        timer    = 0;
        unknown1 = 0;
        unknown2 = 0;
        unknown3 = 0;
        priority = 0;
    }

    inline bool32 Set(void (T::*state)(), uint8 priority = PRIORITY_NONE)
    {
        if (priority < this->priority || this->priority == PRIORITY_LOCKED)
            return false;

        this->state    = state;
        this->timer    = 0;
        this->priority = priority;
        return true;
    }

    inline bool32 SetAndRun(void (T::*state)(), GameObject::Entity *self, uint8 priority = PRIORITY_NONE)
    {
        bool32 applied = Set(state, priority);
        if (applied)
            Run(self);
        return applied;
    }

    inline bool32 QueueForTime(void (T::*state)(), uint32 duration, uint8 priority = PRIORITY_NONE)
    {
        if (priority < this->priority || this->priority == PRIORITY_LOCKED)
            return false;

        this->state    = state;
        this->timer    = duration;
        this->priority = priority;

        return true;
    }

    template <typename E> inline bool32 Set(void (E::*state)(), uint8 priority = PRIORITY_NONE)
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

    template <typename E> inline bool32 SetAndRun(void (E::*state)(), GameObject::Entity *self, uint8 priority = PRIORITY_NONE)
    {
        bool32 applied = Set(state, priority);
        if (applied)
            Run(self);
        return applied;
    }

    template <typename E> inline bool32 QueueForTime(void (E::*state)(), uint32 duration, uint8 priority = PRIORITY_NONE)
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

    inline void Run(GameObject::Entity *self)
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

    inline bool32 Matches(void (T::*other)()) { return state == other; }
    template <typename E> inline bool32 Matches(void (E::*other)()) { return state == (void(T::*)())other; }

    inline void Copy(StateMachine<T> *other)
    {
        this->state    = other->state;
        this->timer    = other->timer;
        this->unknown1 = other->unknown1;
        this->unknown2 = other->unknown2;
        this->unknown3 = other->unknown3;
        this->priority = other->priority;
    }

    template <typename E> inline void Copy(StateMachine<T> *other)
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
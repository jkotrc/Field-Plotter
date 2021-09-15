/*
** Implementation inspired by TheCherno's game engine series, more specifically Hazel's event system:
** https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Events/Event.h
*/
#ifndef EVENT_H_
#define EVENT_H_

#include "core.h"
#include <functional>

/*
** Event system:
** The window needs to have its onEvent callback set. This will be done by the application.
** The onEvent callback will point to a function that handles every single possible event
** in the program.
**
** This function takes events and spawns an event dispatcher to give it to the layers.
**
** Actual window callbacks create events and spawn OnEvent() with them.
**
** TODO implement an event queue that will be processed in another thread
*/
namespace fieldplotter {


    // enum class EventType {
    //     WindowEvent,
    //     KeyPressedEvent,
    //     KeyTypedEvent,
    //     KeyReleasedEvent
    // };

    enum EventCategory {
        None=0,
        ApplicationEvent=BIT(0),
        InputEvent=BIT(1),
        KeyboardEvent=BIT(2),
        MouseEvent=BIT(3),
        MouseButtonEvent=BIT(4)
    };

    // template <typename Name>
    // struct EventType {
    //     static constexpr const char* getName() {
    //         return "NoneType";
    //     }
    // };

    class Event {
    public:
        virtual ~Event() = default;
        virtual int getCategories() const = 0;
        virtual std::string getName() const = 0;
        bool isInCategory(EventCategory c) {
            return c & getCategories();
        }
        bool handled=false;
    };

    using EventCallback = std::function<void(Event const&)>;

    class EventDispatcher {
    public:
        EventDispatcher(Event& event) : m_event(event) {}
        template <typename T, typename F>
            bool dispatch(F const& func) {
            if (m_event.getName() == T::getStaticName()) {
                m_event.handled |= func(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }

    private:
        Event& m_event;
    };

    class KeyPressEvent;
    class KeyReleaseEvent;
    class KeyRepeatEvent;
    class WindowCloseEvent;

    template <typename>
    struct EventType;

    template<>
    struct EventType<KeyPressEvent> {
        static constexpr const char* getName() {
            return "KeyPressEvent";
        }
    };

    template<>
    struct EventType<KeyReleaseEvent> {
        static constexpr const char* getName() {
            return "KeyReleaseEvent";
        }
    };

    template<>
    struct EventType<KeyRepeatEvent> {
        static constexpr const char* getName() {
            return "KeyRepeatEvent";
        }
    };

    template<>
    struct EventType<WindowCloseEvent> {
        static constexpr const char* getName() {
            return "WindowCloseEvent";
        }
    };

} //namespace fieldplotter
#endif // EVENT_H_

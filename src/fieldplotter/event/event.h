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
    enum EventCategory {
        None=0,
        ApplicationEvent=BIT(0),
        InputEvent=BIT(1),
        KeyboardEvent=BIT(2),
        MouseEvent=BIT(3),
    };

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



} //namespace fieldplotter
#endif // EVENT_H_

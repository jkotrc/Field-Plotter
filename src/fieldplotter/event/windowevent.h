#ifndef WINDOWEVENT_H_
#define WINDOWEVENT_H_

#include "core.h"
#include "event/event.h"

namespace fieldplotter {
    class KeyPressEvent : public Event {
        public:
            int key, mods; //Is it okay to not encapsulate these?
            KeyPressEvent(int key, int mods) : key(key), mods(mods) {}
            int getCategories() const override {
                return InputEvent | KeyboardEvent;
            }
            std::string getName() const override {
                return std::string(EventType<KeyPressEvent>::getName());
            }
    };

    class KeyReleaseEvent : public Event {
        public:
            int key, mods; //Is it okay to not encapsulate these?
            KeyReleaseEvent(int key, int mods) : key(key), mods(mods) {}
            int getCategories() const override {
                return InputEvent | KeyboardEvent;
            }
            std::string getName() const override {
                return std::string(EventType<KeyReleaseEvent>::getName());
            }
    };

    class KeyRepeatEvent : public Event {
        public:
            int key, mods; //Is it okay to not encapsulate these?
            KeyRepeatEvent(int key, int mods) : key(key), mods(mods) {}
            int getCategories() const override {
                return InputEvent | KeyboardEvent;
            }
            std::string getName() const override {
                return std::string(EventType<KeyRepeatEvent>::getName());
            }
    };

    class WindowCloseEvent : public Event {
        public:
            WindowCloseEvent() = default;
            int getCategories() const override {
                return ApplicationEvent;
            }
            std::string getName() const override {
                return std::string(EventType<WindowCloseEvent>::getName());
            }
    };
}


#endif // WINDOWEVENT_H_

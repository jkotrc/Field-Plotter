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
                return "KeyPressEvent";
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
                return "KeyReleaseEvent";
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
                return "KeyRepeatEvent";
            }
    };

    class WindowCloseEvent : public Event {
        public:
            WindowCloseEvent() = default;
            int getCategories() const override {
                return ApplicationEvent;
            }
            std::string getName() const override {
                return "WindowCloseEvent";
            }
    };

    class WindowErrorEvent : public Event {

        public:
            WindowErrorEvent(int code, std::string desc) : code(code), description(desc) {}
            int getCategories() const override {
                return ApplicationEvent;
            }
            std::string getName() const override {
                return "WindowErrorEvent";
            }
            int getErrorCode() const { return code; }
            std::string getDescription() const { return description; }
        private:
            int code;
            std::string description;
    };
}


#endif // WINDOWEVENT_H_

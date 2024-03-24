#ifndef WINDOWEVENT_H_
#define WINDOWEVENT_H_

#include "core.h"
#include "event/event.h"



namespace fieldplotter {
    class KeyPressEvent : public Event {
        public:
            int key, action, mods;
            KeyPressEvent(int key, int action, int mods) : key(key),action(action), mods(mods) {}
            int getCategories() const override {
                return InputEvent | KeyboardEvent;
            }
            std::string getName() const override {
                return "KeyPressEvent";
            }
    };

    class KeyReleaseEvent : public Event {
        public:
            int key, mods;
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
            int key, mods;
            KeyRepeatEvent(int key, int mods) : key(key), mods(mods) {}
            int getCategories() const override {
                return InputEvent | KeyboardEvent;
            }
            std::string getName() const override {
                return "KeyRepeatEvent";
            }
    };
    class MouseButtonEvent : public Event {
        public:
            int button,action,mods;
            MouseButtonEvent(int button, int action, int mods) : button(button), action(action), mods(mods) {}
            int getCategories() const override {
                return InputEvent | MouseEvent;
            }
            std::string getName() const override {
                return "MouseButtonEvent";
            }
    };
    class MouseMoveEvent : public Event {
        public:
            double xpos, ypos;
            MouseMoveEvent(double xpos, double ypos) : xpos(xpos), ypos(ypos) {}
            int getCategories() const override {
                return InputEvent | MouseEvent;
            }
            std::string getName() const override {
                return "MouseMoveEvent";
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

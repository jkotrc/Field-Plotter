#ifndef LOGGING_H_
#define LOGGING_H_

#include <string>

namespace fieldplotter {
    enum class Severity {ERR,WARN,INFO,DEBUG};

    class Message {
        public:
            Message() = default;
            Message(std::string message, Severity severity);
            std::string toString() const;
        private:
            std::string message;
            Severity severity;

    };
}

#endif // LOGGING_H_

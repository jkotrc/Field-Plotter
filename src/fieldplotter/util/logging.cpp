#include "logging.h"


using namespace fieldplotter;

Message::Message(std::string message, Severity severity) {
    this->message = message;
    this->severity = severity;

}

std::string Message::toString() const {
    return this->message;
}

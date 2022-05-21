#include <thread.h>

using namespace fieldplotter;

Thread::Thread(StandardFunction const& stfunc) : starter_function(stfunc) {}


void Thread::run() {
    this->thread = boost::thread(boost::bind(&Thread::_run, this));
}

void Thread::_run() {
    this->running = true;
    this->exitcode = starter_function();
    this->running = false;
}

void Thread::join() {
    this->thread.join();
}

void Thread::push_message(Message const& msg) {

}

Message Thread::read_message() {
    Message msg;
    this->message_queue->try_pull(msg);
    return msg;
}

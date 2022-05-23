#ifndef THREAD_H_
#define THREAD_H_

#include <functional>
#include <boost/thread.hpp>
#include <boost/thread/concurrent_queues/sync_queue.hpp>

#include <util/logging.h>

//what if the thread needs parameters?
namespace fieldplotter {

    using StandardFunction = std::function<int()>;

    //finished callback?
    class Thread {
        public:
            Thread(StandardFunction const& stfunc);
            void run();
            void join();
            void push_message(Message const& msg);
            Message read_message();
            bool is_running() const {return running;}
        private:
            void _run();
            bool running;
            int exitcode;
            StandardFunction starter_function;
            boost::sync_queue<Message>* message_queue;
            boost::thread thread;
    };
}


#endif // THREAD_H_

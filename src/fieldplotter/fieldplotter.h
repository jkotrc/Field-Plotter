#ifndef FIELDPLOTTER_H_
#define FIELDPLOTTER_H_

#include "window.h"
#include "event/event.h"

#include "util/logging.h"

#include <boost/thread.hpp>
#include <boost/thread/concurrent_queues/sync_queue.hpp>

namespace fieldplotter {
    class FieldPlotter {
        public:
            FieldPlotter();
            ~FieldPlotter();
            int run();
            void onEvent(Event const& e);
            void close();
        private:
            Window* win;
            bool running;
            bool minimized;
    };
}
#endif // FIELDPLOTTER_H_

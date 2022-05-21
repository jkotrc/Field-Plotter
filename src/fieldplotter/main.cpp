#include <iostream>

#include "fieldplotter.h"
#include "thread.h"

#include <boost/log/trivial.hpp>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include <util/logging.h>

using namespace std;



int main() {
    fieldplotter::FieldPlotter* fp = new fieldplotter::FieldPlotter();

    fieldplotter::Thread thread(
        boost::bind(
            &fieldplotter::FieldPlotter::run, fp)
            );

    thread.run();

    while (thread.is_running()) {
        std::cout << "Still Running\n";
        boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
    }

    thread.join();

    std::cout << "Bye\n";

    return 0;
}

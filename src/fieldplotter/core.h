#ifndef CORE_H_
#define CORE_H_

#include <iostream>

#ifdef DEBUG
# define DEBUG_ERR(X) std::cerr << X << "\n";
# define DEBUG_MSG(X) std::cout << X << "\n";
#else
# define DEBUG_ERR(X)
# define DEBUG_MSG(X)
#endif

#endif // CORE_H_

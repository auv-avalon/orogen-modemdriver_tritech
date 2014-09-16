#ifndef modemdriver_TYPES_HPP
#define modemdriver_TYPES_HPP

/* If you need to define types specific to your oroGen components, define them
 * here. Required headers must be included explicitly
 *
 * However, it is common that you will only import types from your library, in
 * which case you do not need this file
 */
#include <vector>
#include <base/time.h>

namespace modemdriver {
    struct modem_message {
        base::Time time;
        std::string message;
    };
}

#endif


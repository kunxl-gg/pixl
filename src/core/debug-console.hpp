#ifndef PIXL_DEBUG_CONSOLE_HPP
#define PIXL_DEBUG_CONSOLE_HPP

#include "pixl/src/pixl-precomp.hpp"
#include <string>

namespace pixl {

class DebugConsole {
public:
    static DebugConsole &getInstance() {
        static DebugConsole instance;
        return instance;
    }

    std::vector<std::string> getMessages() {
        return _messages;
    }
    void addMessage(const char *message) {
        _messages.push_back(message);
    }
private:
    DebugConsole() = default;
    std::vector<std::string> _messages;
};

} // namespace pixl

#endif // PIXL_DEBUG_CONSOLE_HPP

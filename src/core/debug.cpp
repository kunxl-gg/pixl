#include <cstdarg>
#include <ctime>

#include "pixl/src/core/debug.hpp"
#include "pixl/src/core/debug-console.hpp"

namespace pixl {

void debug(const char *s, ...) {
    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [DEBUG]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);

    DebugConsole::getInstance().addMessage(buffer);
}

void debugN(const char *s, ...) {
    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [DEBUG]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);

    DebugConsole::getInstance().addMessage(buffer);
}

void info(const char *s, ...) {
    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [INFO]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);

    DebugConsole::getInstance().addMessage(buffer);
}

void infoN(const char *s, ...) {
    char buffer[1024];
    std::time_t currentTime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S [INFO]", std::localtime(&currentTime));

    snprintf(buffer + strlen(buffer), 1024, " %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);

    DebugConsole::getInstance().addMessage(buffer);
}

void error(const char *s, ...) {
    char buffer[1024];
    std::time_t currenttime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%h:%m:%s [ERROR]", std::localtime(&currenttime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);

    DebugConsole::getInstance().addMessage(buffer);
}

void errorN(const char *s, ...) {
    char buffer[1024];
    std::time_t currenttime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%h:%m:%s [ERROR]", std::localtime(&currenttime));

    snprintf(buffer + strlen(buffer), 1024, " %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);

    DebugConsole::getInstance().addMessage(buffer);
}

void success(const char *s, ...) {
    char buffer[1024];
    std::time_t currenttime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%h:%m:%s [SUCCESS]", std::localtime(&currenttime));

    snprintf(buffer + strlen(buffer), 1024, " %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);

    DebugConsole::getInstance().addMessage(buffer);
}

void successN(const char *s, ...) {
    char buffer[1024];
    std::time_t currenttime = std::time(nullptr);
    std::strftime(buffer, sizeof(buffer), "%h:%m:%s [SUCCESS]", std::localtime(&currenttime));

    snprintf(buffer + strlen(buffer), 1024, " %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);

    DebugConsole::getInstance().addMessage(buffer);
}

} // namespace pixl

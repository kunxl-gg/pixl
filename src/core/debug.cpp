#include <cstdarg>
#include <cstdio>

#include "pixl/src/core/debug.hpp"

namespace pixl {

void debug(const char *s, ...) {
    char buffer[1024];
    snprintf(buffer, 1024, "[DEBUG] %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void debugN(const char *s, ...) {
    char buffer[1024];
    snprintf(buffer, 1024, "[DEBUG] %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void info(const char *s, ...) {
    char buffer[1024];
    snprintf(buffer, 1024, "[INFO] %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void infoN(const char *s, ...) {
    char buffer[1024];
    snprintf(buffer, 1024, "[INFO] %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void error(const char *s, ...) {
    char buffer[1024];
    snprintf(buffer, 1024, "[ERROR] %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void errorN(const char *s, ...) {
    char buffer[1024];
    snprintf(buffer, 1024, "[ERROR] %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void success(const char *s, ...) {
    char buffer[1024];
    snprintf(buffer, 1024, "[SUCCESS] %s\n", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

void successN(const char *s, ...) {
    char buffer[1024];
    snprintf(buffer, 1024, "[SUCCESS] %s", s);

    va_list args;
    va_start(args, s);
    vprintf(buffer, args);
    va_end(args);
}

} // namespace pixl

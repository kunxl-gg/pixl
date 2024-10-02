#include "pixl/src/core/debug.hpp"
#include <cstdarg>
#include <cstdio>

namespace pxil {

void writeToConsole(const char *s, va_list args, unsigned int level, unsigned int channel, bool newLine = true) {
    char *buf;
    int len = vasprintf(&buf, s, args);
    printf("%d", len);
}

} // namespace pxil

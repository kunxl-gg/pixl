#ifndef PIXL_H
#define PIXL_H

namespace pixl {

/**
 * Print a debug message to the console.
 * Appends a newline.
 */
void debug(const char *s, ...);

/**
 * Print a debug message to the console.
 * Does not appends a newline.
 */
void debugN(const char *s, ...);

/**
 * Print a debug message to the console but only if
 * gDebugLevel is greater than or equal to the specified level.
 * By convention more important messages are at the lowest level.
 * Automatically appends a neweline
 *
 * @param level:
 * @param channel:
 */
void debugC(unsigned int level, unsigned int channel, const char *s, ...);

/**
 * Print a debug message to the console but only if
 * gDebugLevel is greater than or equal to the specified level.
 * By convention more important messages are at the lowest level.
 * Does not appends a newline
 *
 * @param level         The debug level that must be active for the message to be printed
 * @param channel       The debug channel that must be cross checked against
 */
void debugCN(unsigned int level, unsigned int channel, const char *s, ...);

}

#endif // !PIXL_H

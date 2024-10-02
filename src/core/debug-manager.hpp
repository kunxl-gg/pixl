#ifndef PIXL_DEBUG_CHANNEL_H
#define PIXL_DEBUG_CHANNEL_H

namespace pixl {

struct DebugChannel {
    unsigned int channel;
    const char *name;
    const char *description;
};

class DebugManager {
public:
    bool addDebugChannel(const DebugChannel &channel);
    bool addDebugChannels(const DebugChannel *channels);
private:
    unsigned int g_debugChannel;
};

} // namespace pixl

#endif // PIXL_DEBUG_CHANNEL_H

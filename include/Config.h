#pragma once
namespace Config {
    namespace Ethernet {
        inline constexpr int INTERFRAME_GAP_TICKS = 96;
        inline constexpr int SLOT_TIME_TICKS = 512; // binary exponential backoff is [0,d^COLLISION ATTEMPTS-1], this is the config for d.
        inline constexpr int MAX_COLLISION_ATTEMPTS = 16; // if reached, binary exponential backoff will terminate and frame is discarded
        inline constexpr int BACKOFF_LIMIT_K = 10;

    }
}
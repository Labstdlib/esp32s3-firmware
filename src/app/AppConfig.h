#pragma once

#include <stdint.h>

namespace eps32s3_firmware {

struct AppConfig {
    static constexpr uint32_t kAndroidBaudRate = 115200;
    static constexpr uint32_t kMdbBaudRate = 9600;

    static constexpr size_t kAndroidLineMaxLength = 256;
    static constexpr size_t kMdbFrameMaxLength = 64;

    static constexpr uint32_t kMdbResponseTimeoutMs = 100;
    static constexpr uint32_t kMdbPollIntervalMs = 100;

    static constexpr uint32_t kMaxVendAmountMinorUnits = 999999;
    static constexpr uint8_t kMaxItemId = 99;

    // Change this per deployed machine. In production, store/provision it
    // securely rather than compiling a universal shared secret.
    static constexpr const char* kAndroidAuthToken =
        "CHANGE-ME-TO-A-LONG-RANDOM-SECRET";
};

}  // namespace eps32s3_firmware
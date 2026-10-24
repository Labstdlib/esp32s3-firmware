#pragma once

#include <stddef.h>
#include <stdint.h>

namespace eps32s3_firmware {

    enum class MdbAddress : uint8_t {
        CashlessDevice1 = 0x10,
        CashlessDevice2 = 0x20,
        CoinChanger = 0x30,
        BillValidator = 0x40
    };

    enum class MdbCommand : uint8_t {
        Reset = 0x00,
        Setup = 0x01,
        Poll = 0x03,
        VendRequest = 0x04,
        VendSuccess = 0x05,
        VendFailure = 0x06
    };

    struct MdbFrame {
        uint8_t address;
        uint8_t command;
        uint8_t data[32];
        size_t dataLength;
        bool isAddressByte;
    };

}  // namespace eps32s3_firmware
/** 
 * @file MdbTransport.h
 * 
 * 
 * This is hardware boundary, 
 * Replace its its internals with your validate 
 * MDB transceiver implementation
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "../utils/Result.h"
#include "MdbTypes.h"

namespace eps32s3_firmware {

class MdbTransport {
public:
    bool begin();
    void end();

    Result sendFrame(const MdbFrame& frame);
    Result receiveFrame(MdbFrame& frame, uint32_t timeoutMs);

private:
    Result transmitByte(uint8_t value, bool isAddressByte);
    Result receiveByte(uint16_t& value, uint32_t timeoutMs);

    bool initialized_ = false;
};

}  // namespace eps32s3_firmware
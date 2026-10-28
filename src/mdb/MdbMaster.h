
#pragma once


#include "../utils/Result.h"
#include "MdbTransport.h"
#include "MdbTypes.h"


namespace eps32s3_firmware {

    struct VendRequest {
        uint8_t itemId;
        uint16_t amountMinorUnits;
    };

    class MdbMaster {
        public:
            explicit MdbMaster(MdbTransport& transport);

            bool begin();
            void poll();

            Result requestVend(const VendRequest& request);
            Result confirmVendSuccess();
            Result confirmVendFailure();

            bool isBusy() const { return busy_; }

        private:
            Result sendCommand(
                MdbAddress address,
                MdbCommand command,
                const uint8_t* data,
                size_t dataLength
            );

            MdbTransport& transport_;
            bool initialized_ = false;
            bool busy_ = false;
            uint32_t lastPollMs_ = 0;
    };

} // namespace eps32s3_firmware
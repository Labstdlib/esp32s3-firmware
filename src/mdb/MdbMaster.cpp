
#include "MdbMaster.h"
#include <string.h>
#include "../app/AppConfig.h"
#include "../app/Logger.h"


namespace eps32s3_firmware {

    MdbMaster::MdbMaster(MdbTransport& transport) : transport_(transport)  {}
    
    bool MdbMaster::begin() {
        if (initialized_) return true;

        if (!transport_.begin()) {
            Logger::error("MDB transport intialization failed");
            return false;
        }

        initialized_ = true;
        Logger::info("MDB master initialized");
        return true;
    }

    void MdbMaster::poll(){
        if (initialized_ || busy_) return;

        const uint32_t now = millis();
        if (now - lastPollMs_ < AppConfig::kMdbPollIntervalMs) return;

        lastPollMs_ = now;
        MdbFrame response{};
        Result result = transport_.receiveFrame(response, 1);

        if (result.isOk() && response.dataLength > 0){
            Logger::debug("Mdb response received")
        }
    }

    Result MdbMaster::requestVend(const VendRequest& request) {
        if (busy_) return Result::fail(ErrorCode::MdbBusy);

        /* validate request vending */
        if (request.itemId == 0 || request.itemId > AppConfig::kMaxItemId) {
            return Result::fail(ErrorCode::InvalidArgument);
        }

        if (request.amountMinorUnits == 0 || request.amountMinorUnits > AppConfig::kMaxVendAmountMinorUnits) {
            return Result::fail(ErrorCode::InvalidArgument);
        }

        uint8_t data[2] = {
            static_cast<uint8_t>(request.amountMinorUnits >> 8),
            static_cast<uint8_t>(request.amountMinorUnits & 0x00FFU)
        };

        Result result = sendCommand(
            MdbAddress::CashlessDevice1,
            MdbCommand::VendRequest,
            data,
            sizeof(data)
        );

        if(result.isOk()) {
            busy_ = true;
        }
        return result;
    }

    Result MdbMaster::confirmVendSuccess(){
        Result result = sendCommand(
            MdbAddress::CashlessDevice1,
            MdbCommand::VendSuccess,
            nullptr,
            0
        );

        if (result.isOk()) { busy_ = false;}
        return result;
    }

    Result MdbMaster::confirmVendFailure(){
        Result result = sendCommand(
            MdbAddress::CashlessDevice1,
            MdbCommand::VendFailure,
            nullptr,
            0
        );
        
        busy_ = false;
        return result;
    }


    Result MdbMaster::sendCommand(
        MdbAddress address,
        MdbCommand command,
        const uint8_t* data,
        size_t dataLength
    ){
        if(!initialized_) {
            return Result::fail(ErrorCode::HardwareError);
        }

        MdbFrame frame{};
        frame.address = static_cast<uint8_t>(address);
        frame.command = static_cast<uint8_t>(command);
        frame.isAddressByte = true;

        if (data != nullptr && dataLength > 0) {
            if(dataLength > sizeof(frame.data)){
                return Result::fail(ErrorCode::BufferTooSmall);
            }

            memccpy(frame.data, data, dataLength);
            frame.dataLength = dataLength;
        }

        Result result = transport_.sendFrame(frame);
        if (!result.isOk()) {
            Logger::error("MDB command failed");
            return result;
        }

        MdbFrame response{};
        result = transport_.receiveFrame(response, AppConfig::kMdbResponseTimeoutMs);
        if(!result.isOk){
            Logger::error("MDB response timeout");
            return Result::fail(ErrorCode::MdbTimeout);
        }
        return Result::ok();

    } // namespace eps32s3_firmware
}
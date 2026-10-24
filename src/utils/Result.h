
#pragma once

#include <stdint.h>

namespace eps32s3_firmware {
    
    enum class ErrorCode : uint8_t {
        Ok = 0,
        InvalidArgument,
        BufferTooSmall,
        MalformedCommand,
        Unauthorized,
        UnknownCommand,
        MdbTimeout,
        MdbNak,
        MdbBusy,
        HardwareError,
        InternalError
    };

    struct Result {
        ErrorCode code;
        uint16_t detail;

        static Result ok(){
            return {ErrorCode::Ok, 0};
        }
        static Result fail(ErrorCode c, uint16_t d = 0){
            return {c, d};
        }

        bool isOk() const {
            return code == ErrorCode::Ok;
        }
    };


    inline const char* errorCodeName(ErrorCode code){
        switch (code) {
            case ErrorCode::Ok: return "OK";
            case ErrorCode::InvalidArgument: return "INVALID_ARGUMENT";
            case ErrorCode::BufferTooSmall: return "BUFFER_TOO_SMALL";
            case ErrorCode::MalformedCommand: return "MALFORMED_COMMAND";
            case ErrorCode::Unauthorized: return "UNAUTHORIZED";
            case ErrorCode::UnknownCommand: return "UNKNOWN_COMMAND";
            case ErrorCode::MdbTimeout: return "MDB_TIMEOUT";
            case ErrorCode::MdbNak: return "MDB_NAK";
            case ErrorCode::MdbBusy: return "MDB_BUSY";
            case ErrorCode::HardwareError: return "HARDWARE_ERROR";
            case ErrorCode::InternalError: return "INTERNAL_ERROR";
        }
        return "UNKNOWN";
    }
} // namespace eps32s3_firmware
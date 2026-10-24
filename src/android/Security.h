/** 
 * @file Security.h
 * 
 * Security and validation included:
 * - Every Android command requrires a token
 * - JSON parser is bounded field count and bounded line length
 * - Item ID and amount are range-checked before reaching MDB
 * - USB RX lines that are too long are discarded instead of overflowing the memory
 * - MDB transport returns typed errors instead of raw integer code
 * - MDB hardware accesss is isolated behind MdbTransport, So the protocal logic
 *   can be unit tested without real 24V hardware
 */


#pragma once

#include <string.h>
#include "../app/AppConfig.h"
#include "../utils/Result.h"

namespace eps32s3_firmware {
    
    class Security {
        public:

            static bool isTokenValid(const char* token) {
                if (token == nullptr) return false;


                /* Constant-time-ish comparison; avoids retuning immediately 
                * on the first mismatch, still use a long random token is production
                */
               const char* expected = AppConfig::kAndroidAuthToken;
               size_t expectedLen = strlen(expected);
               size_t providedLen = strlen(token);

               if (expectedLen != providedLen) return false;

               volatile uint8_t difference = 0;
               for (size_t i = 0; i <expectedLen; ++i){
                    difference |= static_cast<uint8_t>(expected[i] ^ static_cast<uint8_t>(token[i]));
               }
               return difference == 0;
            }
    };
} // namespace eps32s3_firmware
#pragma once

#include<ctype.h>
#include<string.h>

namespace vending {
    
    inline bool equalIgnoreCase(const char* left, const char* right){
        if (left == nullptr || right == nullptr) {
            return false;
        }

        while (*left != '\0' && *right != '\0'){
            if (tolower(static_cast<unsigned char>(*left)) != tolower(static_cast<unsigned char>(*right))){
                return false;
            }
            ++left;
            ++right;
        }
        return *left == '\0' && *right == '\0';
    }

    inline bool parseUint16(const char* txt, u_int16_t& output){
        if (txt == nullptr || *txt == '\0'){
            return false;
        }

        uint32_t value = 0;
        for (const char* p = txt; *p != '\0'; ++p){
            if (!isdigit(static_cast<unsigned char>(*p))){
                return false;
            }
            
            value = value * 10U + static_cast<uint32_t>(*p - '0');
            if (value > 0xFFFFU){
                return false;
            }
        }
        output = static_cast<u_int16_t>(value);
        return true;
    }
} // namespace vending
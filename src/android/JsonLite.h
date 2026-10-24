/*
* JsonLite.h
*
*
* A small, dependency-free parser fro the Android command protocol,
* It intentionally supports only flat JSON objects with string/number values,
* which is enough for the embedded command and avoids a large JSON library dependency.
*/

#pragma once

#include <stddef.h>
#include <stdint.h>

namespace eps32s3_firmware {

    struct JsonField {
        const char* key;
        const char* value;
        bool isNumber;
    };

    class JsonLite {
    public:
        static bool parse(
            char* json,
            JsonField* fields,
            size_t maxFields,
            size_t& fieldCount
        );

    private:
        static char* skipWhitespace(char* p);
        static bool parsePair(char*& p, JsonField& field);
    };

}  // namespace eps32s3_firmware
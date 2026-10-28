
#include "JsonLite.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

namespace eps32s3_firmware
{


    bool JsonLite::parse(
        char *json,
        JsonField *fields,
        size_t maxFields,
        size_t &fieldCount)
    {

        fieldCount = 0;

        if (json == nullptr || fields == nullptr || maxFields == 0)
        {
            return false;
        }

        char *p = skipWhitespace(json);

        if (*p != '{')
        {
            return false;
        }

        ++p;
        p = skipWhitespace(p);

        if (*p == '}')
        {
            return true;
        }

        while (*p != '\0')
        {
            if (fieldCount >= maxFields)
            {
                return false;
            }

            JsonField field{};

            if (!parsePair(p, field))
            {
                return false;
            }

            fields[fieldCount++] = field;
            p = skipWhitespace(p);

            if (*p == ',')
            {
                ++p;
                p = skipWhitespace(p);
                continue;
            }

            if (*p == '}')
            {
                return true;
            }

            return false;
        }

        return false;
    }

    char *JsonLite::skipWhitespace(char *p)
    {
        while (p != nullptr && *p != '\0' &&
               isspace(static_cast<unsigned char>(*p)))
        {
            ++p;
        }

        return p;
    }

    bool JsonLite::parsePair(char *&p, JsonField &field)
    {
        p = skipWhitespace(p);

        if (*p != '"')
        {
            return false;
        }

        field.key = ++p;

        while (*p != '\0' && *p != '"')
        {
            if (*p == '\\')
            {
                ++p;
            }

            ++p;
        }

        if (*p != '"')
        {
            return false;
        }

        *p++ = '\0';
        p = skipWhitespace(p);

        if (*p != ':')
        {
            return false;
        }

        ++p;
        p = skipWhitespace(p);

        if (*p == '"')
        {
            field.isNumber = false;
            field.value = ++p;

            while (*p != '\0' && *p != '"')
            {
                if (*p == '\\')
                {
                    ++p;
                }

                ++p;
            }

            if (*p != '"')
            {
                return false;
            }

            *p++ = '\0';
            return true;
        }

        field.isNumber = true;
        field.value = p;

        while (*p != '\0' && *p != ',' && *p != '}')
        {
            if (!isdigit(static_cast<unsigned char>(*p)) && *p != '-' &&
                *p != '.')
            {
                return false;
            }

            ++p;
        }

        if (*p == '\0')
        {
            return false;
        }

        *p++ = '\0';
        return true;
    }

} // namespace vending
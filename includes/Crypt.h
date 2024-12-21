#ifndef MYCRYPT_H
#define MYCRYPT_H

#include <string>
#include <vector>
#include <cstdint>
#include <cstring>
#include <stdexcept>

class Crypt
{
private:
    static constexpr uint32_t encryptionKey = 0xC4A2B3D8;

public:
    static std::vector<uint8_t> Encrypt(const std::string& text);
};

#endif
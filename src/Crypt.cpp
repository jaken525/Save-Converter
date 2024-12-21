#include "../includes/Crypt.h"

std::vector<uint8_t> Crypt::Encrypt(const std::string& text)
{
    std::vector<uint8_t> fileBytes(text.begin(), text.end());
    std::vector<uint8_t> encryptedBytes(fileBytes.size());

    for (size_t i = 0; i < fileBytes.size(); i += 2)
    {
        uint16_t block = 0;
        if (i + 1 < fileBytes.size())
            block = static_cast<uint16_t>(fileBytes[i]) | (static_cast<uint16_t>(fileBytes[i + 1]) << 8);
        else
            block = fileBytes[i];

        uint16_t encryptedBlock = static_cast<uint16_t>(block ^ (encryptionKey & 0xFFFF));

        encryptedBytes[i] = static_cast<uint8_t>(encryptedBlock & 0xFF);
        if (i + 1 < fileBytes.size())
            encryptedBytes[i + 1] = static_cast<uint8_t>((encryptedBlock >> 8) & 0xFF);
    }

    return encryptedBytes;
}
#pragma once

#include <vector>

#include <mbedtls/sha256.h>
#include <decl.h>

class Aes {
    public:
    Aes();
    ~Aes();
    void update(const std::vector<u8>& input);
    void finish(std::vector<u8>& output);

    mbedtls_sha256_context threadCtx{};
};
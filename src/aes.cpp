#include <aes.h>

Aes::Aes() {
    mbedtls_sha256_init(&threadCtx);
    mbedtls_sha256_starts(&threadCtx, 0);
}

Aes::~Aes() {
    mbedtls_sha256_free(&threadCtx);
}

void Aes::update(const std::vector<u8>& input) {
    mbedtls_sha256_update(&threadCtx, &input[0], input.size());
}
void Aes::finish(std::vector<u8>& output) {
    if (output.size() < 32)
        throw std::runtime_error("Output too small");
    mbedtls_sha256_finish(&threadCtx, output.data());

    mbedtls_sha256_starts(&threadCtx, 0);
}
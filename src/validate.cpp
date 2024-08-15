#include <fstream>
#include <vector>

#include <decl.h>
#include <aes.h>

void validateRegular(const std::filesystem::directory_entry& entry) {
    const auto& target{entry.path()};

    std::ifstream io(target, std::ios::binary | std::ios::in);
    if (!io.is_open()) {
        quit("The file {} cannot be opened due to missing administrator permissions", target);
    }
    std::vector<u8> buffer(16 * 1024);
    bool done{};
    if (file_size(target) < buffer.size()) {
        readInto(buffer, io);
        if (io.gcount() > buffer.size()) {
            quit("The file {} cannot be read", target);
        }
        buffer.resize(io.gcount());
        done = true;
    }
    Aes checksum{};
    std::vector<u8> hash(32);

    if (!done) {
        do {
            readInto(buffer, io);
            buffer.resize(io.gcount());
            checksum.update(buffer);
        } while (io.tellg() > 0);

        checksum.finish(hash);
    }
    checksum.update(buffer);
    checksum.finish(hash);

    addIntoFilter(hash, entry.path());
}

void readInto(std::vector<u8>& output, std::ifstream& input) {
    input.read(reinterpret_cast<char*>(&output[0]),
        static_cast<std::streamsize>(output.size()));
}

#pragma once
#include <llvm/Support/Error.h>
#include <llvm/Support/ErrorHandling.h>
#include <llvm/ADT/Twine.h>
#include <llvm/Support/BinaryStreamRef.h>
#include <llvm/Support/BinaryStreamError.h>
#include <system_error>

namespace pryst {
namespace llvm_utils {

// Helper function to create StringError with proper Twine usage
inline llvm::Error createStringError(const std::string& message, std::error_code EC) {
    return llvm::createStringError(EC, llvm::Twine(message));
}

// Helper function to create StringError with a generic error code
inline llvm::Error createStringError(const std::string& message) {
    return createStringError(message, std::make_error_code(std::errc::invalid_argument));
}

// Helper function to handle BinaryStreamRef operations safely
inline uint64_t getStreamLength(const llvm::BinaryStreamRef& stream) {
    return stream.getLength();
}

// Helper function to slice BinaryStreamRef safely
inline llvm::Expected<llvm::BinaryStreamRef> sliceStream(
    const llvm::BinaryStreamRef& stream,
    uint64_t offset,
    uint64_t length) {
    if (offset + length > stream.getLength()) {
        return createStringError("Invalid stream slice range");
    }
    return stream.slice(offset, length);
}

// Helper function to create a BinaryStreamRef from a buffer
inline llvm::BinaryStreamRef createStreamRef(
    const uint8_t* data,
    size_t length) {
    return llvm::BinaryStreamRef(llvm::ArrayRef<uint8_t>(data, length));
}

// Helper function to convert an error to string
inline std::string toString(const llvm::Error& err) {
    std::string result;
    llvm::raw_string_ostream stream(result);
    stream << err;
    return result;
}

// Helper function to handle BinaryStreamRef read operations
template<typename T>
inline llvm::Error readFromStream(
    const llvm::BinaryStreamRef& stream,
    uint64_t offset,
    T& value) {
    auto expectedRef = stream.slice(offset, sizeof(T));
    if (!expectedRef)
        return expectedRef.takeError();

    auto ref = expectedRef.get();
    if (ref.getLength() < sizeof(T))
        return llvm::createStringError(
            std::make_error_code(std::errc::invalid_argument),
            llvm::Twine("Stream too short for requested read"));

    const uint8_t* data = ref.data().data();
    memcpy(&value, data, sizeof(T));
    return llvm::Error::success();
}

} // namespace llvm_utils
} // namespace pryst

#include "io.hpp"
#include "runtime_registry.hpp"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"

void registerFileClass(RuntimeRegistry& registry) {
    // Create LLVM struct type for File class
    auto& context = registry.getContext();

    // File class members (filename, isOpen)
    std::vector<llvm::Type*> fileMembers = {
        llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0), // filename (char*)
        llvm::Type::getInt1Ty(context)  // isOpen (bool)
    };

    auto fileStructTy = llvm::StructType::create(context, fileMembers, "pryst::io::File");

    // Register File class
    registry.registerClass("File", "pryst::io::File", fileStructTy);

    // Register constructor
    registry.registerClassMethod("File", {
        "File",  // Using class name as constructor name
        llvm::FunctionType::get(
            fileStructTy->getPointerTo(),
            {llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0)},  // filename
            false
        )
    });

    // Register readToString method
    registry.registerClassMethod("File", {
        "readToString",
        llvm::FunctionType::get(
            llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0),  // returns char*
            {fileStructTy->getPointerTo()},  // this pointer
            false
        )
    });

    // Register writeAll method
    registry.registerClassMethod("File", {
        "writeAll",
        llvm::FunctionType::get(
            llvm::Type::getVoidTy(context),
            {
                fileStructTy->getPointerTo(),  // this pointer
                llvm::PointerType::get(llvm::Type::getInt8Ty(context), 0)  // content
            },
            false
        )
    });

    // Register close method
    registry.registerClassMethod("File", {
        "close",
        llvm::FunctionType::get(
            llvm::Type::getVoidTy(context),
            {fileStructTy->getPointerTo()},  // this pointer
            false
        )
    });

    // Register destructor
    registry.registerClassMethod("File", {
        "delete",
        llvm::FunctionType::get(
            llvm::Type::getVoidTy(context),
            {fileStructTy->getPointerTo()},  // this pointer
            false
        )
    });
}

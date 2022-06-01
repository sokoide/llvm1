#include "headers.hpp"

llvm::Function* writeFunc;
llvm::Function* writelnFunc;
llvm::Value* expression();

int main() {
    llvm::LLVMContext context;
    llvm::Module* module = new llvm::Module("sokoide_module", context);
    llvm::IRBuilder<> builder(context);

    auto* funcType = llvm::FunctionType::get(builder.getInt64Ty(), false);
    auto* mainFunc = llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, "main", module);
    auto* entrypoint =
        llvm::BasicBlock::Create(context, "entrypoint", mainFunc);

    // builtin
    {
        std::vector<llvm::Type*> param_types(1, builder.getInt64Ty());
        auto* funcType =
            llvm::FunctionType::get(builder.getInt64Ty(), param_types, false);
        writeFunc = llvm::Function::Create(
            funcType, llvm::Function::ExternalLinkage, "write", module);
    }

    {
        auto* funcType = llvm::FunctionType::get(builder.getInt64Ty(), false);
        writelnFunc = llvm::Function::Create(
            funcType, llvm::Function::ExternalLinkage, "writeln", module);
    }

    builder.SetInsertPoint(entrypoint);

    // call write(42)
    builder.CreateCall(writeFunc,
                       std::vector<llvm::Value*>(1, builder.getInt64(42)));

    // ret 42
    builder.CreateRet(builder.getInt64(42));

    std::error_code error_info;
    llvm::raw_fd_ostream raw_stream("out.ll", error_info,
                                    llvm::sys::fs::OpenFlags::OF_None);

    // IR
    module->print(raw_stream, nullptr);
    // module->print(llvm::outs(), nullptr); // print LLVM IR to stdout

    // Bitcode
    // llvm::raw_fd_ostream raw_stream_bit("out.bc", error_info,
    //                                     llvm::sys::fs::OpenFlags::F_None);
    // llvm::WriteBitcodeToFile(*module,
    //                          raw_stream_bit); // write LLVM Bitcode to file
    return 0;
}

cmake_minimum_required (VERSION 3.16)

ENABLE_LANGUAGE(CXX)
project(llvm1 VERSION 1.0)

# use target_compile_features if you want to use different options per target
set(CMAKE_CXX_STANDARD 14)
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# use target_compile_options if you want to use different opsitons per target
add_compile_options(-O2 -g -Wall)
add_link_options(-rdynamic)

# define output of 'llvm-config --cxxflags --ldflags --libs core'
# in target_include_directories, target_link_directories and target_link_libraries

# includes
set (COMMON_INCLUDES
)
# sources
set(COMMON_SOURCES )
set(TARGET_SOURCES
	main.cpp
)

# default target 'spike.out'
add_executable(${PROJECT_NAME}.out ${COMMON_SOURCES} ${TARGET_SOURCES})

# use precompiled header
target_precompile_headers(${PROJECT_NAME}.out PRIVATE headers.hpp)

# include
target_include_directories(${PROJECT_NAME}.out PUBLIC
	"/usr/local/opt/llvm/include"
	# "/usr/local/Cellar/llvm/10.0.1/include/c++/v1"
	# "/Library/Developer/CommandLineTools/usr/include/c++/v1"
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}"
    "${COMMON_INCLUDES}"
)


# link
target_link_directories(${PROJECT_NAME}.out PUBLIC
	"/usr/local/Cellar/llvm/10.0.1/lib")
target_link_libraries(${PROJECT_NAME}.out PUBLIC
	"LLVMX86Disassembler;LLVMX86AsmParser;LLVMX86CodeGen;LLVMCFGuard;LLVMGlobalISel;LLVMSelectionDAG;LLVMAsmPrinter;LLVMDebugInfoDWARF;LLVMCodeGen;LLVMScalarOpts;LLVMInstCombine;LLVMAggressiveInstCombine;LLVMTransformUtils;LLVMBitWriter;LLVMX86Desc;LLVMMCDisassembler;LLVMX86Utils;LLVMX86Info;LLVMMCJIT;LLVMExecutionEngine;LLVMTarget;LLVMAnalysis;LLVMProfileData;LLVMRuntimeDyld;LLVMObject;LLVMTextAPI;LLVMMCParser;LLVMBitReader;LLVMMC;LLVMDebugInfoCodeView;LLVMDebugInfoMSF;LLVMCore;LLVMRemarks;LLVMBitstreamReader;LLVMBinaryFormat;LLVMSupport;LLVMDemangle;z;curses;m;libxml2.tbd"
)




# custom target: run
# uses custom command. otherwise, stdin for lldb is closed by ninja
add_custom_target(run
    DEPENDS ${PROJECT_NAME}.out
    DEPENDS run_command
)

add_custom_command(OUTPUT run_command
    USES_TERMINAL
    COMMAND ${PROJECT_NAME}.out
)

# custom target: lldb
# uses custom command. otherwise, stdin for lldb is closed by ninja
add_custom_target(lldb
    DEPENDS ${PROJECT_NAME}.out
    DEPENDS lldb_command
)

add_custom_command(OUTPUT lldb_command
    USES_TERMINAL
    COMMAND lldb ${PROJECT_NAME}.out
)

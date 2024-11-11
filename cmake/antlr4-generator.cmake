# ANTLR4 Generator CMake Module
function(antlr4_generate_cpp grammar_file generated_files)
    set(ANTLR4_JAR_LOCATION "/usr/local/lib/antlr-4.13.2-complete.jar")
    set(ANTLR4_GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR})

    # Parse arguments
    set(options NO_LISTENER VISITOR)
    set(oneValueArgs NAMESPACE)
    cmake_parse_arguments(ANTLR4 "${options}" "${oneValueArgs}" "" ${ARGN})

    # Build command line options
    set(ANTLR4_COMMAND
        ${Java_JAVA_EXECUTABLE} -jar ${ANTLR4_JAR_LOCATION}
        -Dlanguage=Cpp
        ${grammar_file}
        -o ${ANTLR4_GENERATED_DIR}
    )

    if(ANTLR4_NO_LISTENER)
        list(APPEND ANTLR4_COMMAND -no-listener)
    endif()

    if(ANTLR4_VISITOR)
        list(APPEND ANTLR4_COMMAND -visitor)
    endif()

    if(ANTLR4_NAMESPACE)
        list(APPEND ANTLR4_COMMAND -package ${ANTLR4_NAMESPACE})
    endif()

    # Add custom command
    add_custom_command(
        OUTPUT ${generated_files}
        COMMAND ${ANTLR4_COMMAND}
        DEPENDS ${grammar_file}
        COMMENT "Generating ANTLR4 parser"
    )
endfunction()

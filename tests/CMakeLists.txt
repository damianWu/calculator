# Set TARGET(binary file) name for convenience
set(calculator ${PROJECT_NAME}_calculator_test)


# Executable that runs the tests.
add_executable(
        ${lippman}             # Executable tests file name
        main.test.cpp
        calculator.test.cpp
)


# Link the executable to needed libraries.
target_link_libraries(
        ${calculator}
        calculator              # Library we are testing
        # gtest_main            # GTest libraries
        # gtest
        # pthread
        # gmock_main
        # gmock
        # ${CONAN_LIBS}
)

# Add gtest to be able to run ctest.
add_test(
        NAME calculator_test                    # Test name
        COMMAND ${calculator} --gtest_color=1   # Executable tests file name
)
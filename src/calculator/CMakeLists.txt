add_library(calculator_lib ./calculator.cpp)            # .cpp file path

target_include_directories(calculator_lib PUBLIC .)     # path to catalog that contain
                                                        # .hpp file
                                                        # (not directly to .hpp file!)

target_link_libraries(calculator_lib  token_lib token_stream_lib    variables_lib)

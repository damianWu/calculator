add_library(token_stream_lib ./token_stream.cpp)        # .cpp file path

target_include_directories(token_stream_lib PUBLIC .)   # path to catalog that contain
                                                        # .hpp file
                                                        # (not directly to .hpp file!)

target_link_libraries(token_stream_lib  token_lib   calculator_lib)
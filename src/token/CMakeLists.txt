add_library(token_lib ./token.cpp)                      # .cpp file path

target_include_directories(token_lib PUBLIC .)          # path to catalog that contain
                                                        # .hpp file
                                                        # (not directly to .hpp file!)
add_library(variables_lib ./variables.cpp)              # .cpp file path

target_include_directories(variables_lib PUBLIC .)      # path to catalog that contain
                                                        # .hpp file
                                                        # (not directly to .hpp file!)
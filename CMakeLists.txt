cmake_minimum_required(VERSION 3.1)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
        cmake_policy(VERSION {CMAKE_MAJOR_VERSION.${CMAKE_MINOR_VERSION}})
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(DEBUG_ASAN "AddressSanitizer" OFF)

project(colt
        VERSION 0.0.1
        LANGUAGES C
)

find_package(X11 REQUIRED)
include_directories(${X11_INCLUDE_DIR})

add_executable(${PROJECT_NAME}
        src/main.c
)

target_link_libraries(${PROJECT_NAME}
        ${X11_LIBRARIES}
        ${X11_Xrandr_LIB}
)

target_compile_features(${PROJECT_NAME}
        PRIVATE c_std_11
)

set(CMAKE_C_FLAGS_DEBUG
        "-O0 -g -fno-omit-frame-pointer -fno-optimize-sibling-calls"
)

target_compile_options(${PROJECT_NAME}
        PRIVATE -Wall -Wextra -Werror
)

if (DEBUG_ASAN)
        set(CMAKE_BUILD_TYPE DEBUG)
        target_compile_options(${PROJECT_NAME}
                PRIVATE -fsanitize=address -fsanitize-address-use-after-scope
        )
        set_target_properties(${PROJECT_NAME}
                PROPERTIES LINK_FLAGS -fsanitize=address
        )
endif()

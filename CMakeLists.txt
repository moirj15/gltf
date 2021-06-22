cmake_minimum_required(VERSION 3.10)
project(gltf)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
        include/
        focus/pub_include
)
link_directories(
    libs
    )


set(SRC
    src/main.cpp
    src/gltfParser.hpp
)

add_subdirectory(focus)
add_subdirectory(fmt)


add_executable(
        gltf
        ${SRC})

add_custom_command(TARGET gltf PRE_BUILD COMMAND cp ${PROJECT_SOURCE_DIR}/build/compile_commands.json ${PROJECT_SOURCE_DIR})

if (WIN32)
    set(CMAKE_CXX_FLAGS "/std:c++latest /MTd /MP /TP /W3 -D_CRT_SECURE_NO_WARNINGS")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG -D_CRT_SECURE_NO_WARNINGS")
    set(CompilerFlags
            CMAKE_CXX_FLAGS
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_C_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE
            )
    foreach (CompilerFlag ${CompilerFlags})
        string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
        string(REPLACE "/MDd" "/MTd" ${CompilerFlag} "${${CompilerFlag}}")
    endforeach ()
    target_link_libraries(
            gltf
            e:/projects/focus/lib/focus.lib
            e:/projects/focus/libs/windows/SDL2-static.lib
            e:/projects/focus/libs/windows/SDL2main.lib
            ${CMAKE_SOURCE_DIR}/libs/fmt.lib

            opengl32.lib
            gdi32.lib
            user32.lib
            kernel32.lib
            msvcrtd.lib
            winmm.lib
            imm32.lib
            version.lib
            d3d11.lib
            d3d12.lib
            libcmt.lib
            dxgi.lib
            dxguid.lib
            d3dcompiler.lib
            winmm.lib
            gdi32
            opengl32
            Setupapi.lib
    )
else ()
    set(CMAKE_CXX_FLAGS "-std=c++2a -Wall -Wextra -pedantic")
    target_link_libraries(
        gltf
        ${OPENGL_LIBRARY}
        focus
        fmt
        /usr/local/lib/libSDL2.so
        X11
        dl
        pthread
        )

endif ()



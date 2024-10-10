cmake_minimum_required(VERSION 3.20)  # 确保使用适当的 CMake 版本

project(Jigsaw VERSION 1.0 LANGUAGES CXX)

#=========Settings=============================================================================================#
    # 设置 C++ 标准
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    # 声明为非 win32 项目
    set(CMAKE_WIN32_EXECUTABLE OFF)
    # 指定 vcpkg 的前缀
    set(CMAKE_PREFIX_PATH "E:/vcpkg/vcpkg/installed/x64-mingw-static")
    set(CMAKE_TOOLCHAIN_FILE "E:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")

    # vcpkg include
    set(VCPKG_INCLUDE_DIR "E:/vcpkg/vcpkg/installed/x64-mingw-static/include")

    # 查找 OpenGL, GLFW 和 spdlog
    find_package(OpenGL REQUIRED)
    find_package(spdlog REQUIRED)
    find_package(fmt REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)
#=========Settings=============================================================================================#


#=========Jigsaw Target========================================================================================#
    # 创建 Jigsaw 项目
    file(GLOB_RECURSE JIGSAW_SOURCES "Jigsaw/src/*.cpp" "Jigsaw/src/*.h")
    add_library(Jigsaw SHARED
        Jigsaw/src/jspch.cpp
        ${JIGSAW_SOURCES}
    )

    # 包含目录
    target_include_directories(Jigsaw PRIVATE
            "${PROJECT_SOURCE_DIR}/Jigsaw/src"

            "${VCPKG_INCLUDE_DIR}"
    )

    # 添加链接库
    target_link_libraries(Jigsaw PUBLIC
        glfw
        OpenGL::GL
        GLEW::GLEW
        opengl32.lib
        spdlog::spdlog
        fmt::fmt
        $<$<BOOL:${MINGW}>:ws2_32>
    )

    # 定义预处理器宏
    target_compile_definitions(Jigsaw PRIVATE
        JS_PLATFORM_WINDOWS
        JS_BUILD_DLL

        GLFW_STATIC
    )
#=========Jigsaw Target========================================================================================#


#=========Sandbox Target=======================================================================================#
    # 创建 Sandbox 项目
    file(GLOB_RECURSE SANDBOX_SOURCES "Sandbox/src/*.cpp" "Sandbox/src/*.h")
    add_executable(Sandbox
        ${SANDBOX_SOURCES}
    )

    # include directories
    target_include_directories(Sandbox PRIVATE
        "${PROJECT_SOURCE_DIR}/Jigsaw/src"
    )

    # 添加链接库
    target_link_libraries(Sandbox PRIVATE
        Jigsaw
    )

    # 定义预处理器宏
    target_compile_definitions(Sandbox PRIVATE
        JS_PLATFORM_WINDOWS
    )
#=========Sandbox Target=======================================================================================#


#========Configuration Settings================================================================================#
    # 配置不同的构建类型
    foreach(CONFIGURATION Debug Release Dist)
        string(TOUPPER ${CONFIGURATION} CONFIG)
        if (CMAKE_BUILD_TYPE STREQUAL ${CONFIG})
            target_compile_definitions(Jigsaw PRIVATE JS_DEBUG)
            target_compile_definitions(Sandbox PRIVATE JS_DEBUG)
        endif()

        if (CMAKE_BUILD_TYPE STREQUAL Release)
            target_compile_definitions(Jigsaw PRIVATE JS_RELRASE)
            target_compile_definitions(Sandbox PRIVATE JS_RELRASE)
            target_compile_options(Jigsaw PRIVATE -O2)
            target_compile_options(Sandbox PRIVATE -O2)
        endif()

        if (CMAKE_BUILD_TYPE STREQUAL Dist)
            target_compile_definitions(Jigsaw PRIVATE JS_DIST)
            target_compile_definitions(Sandbox PRIVATE JS_DIST)
            target_compile_options(Jigsaw PRIVATE -O2)
            target_compile_options(Sandbox PRIVATE -O2)
        endif()
    endforeach()

    # 设置库和可执行文件的输出目录
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")
    # 设置配置输出目录
    foreach(CONFIGURATION Debug Release Dist)
        string(TOUPPER ${CONFIGURATION} CONFIG)
        set(TRIPLET_DIR "${CONFIGURATION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

        set_target_properties(Jigsaw PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_DIR}/Jigsaw/${TRIPLET_DIR}
                LIBRARY_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_DIR}/Jigsaw/${TRIPLET_DIR}
                RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_DIR}/Jigsaw/${TRIPLET_DIR}
        )

        set_target_properties(Sandbox PROPERTIES
                ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_DIR}/Sandbox/${TRIPLET_DIR}
                LIBRARY_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_DIR}/Sandbox/${TRIPLET_DIR}
                RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${OUTPUT_DIR}/Sandbox/${TRIPLET_DIR}
        )
    endforeach()

    # 设置输出拷贝命令
    string(TOUPPER ${CMAKE_BUILD_TYPE} CONFIG)
    add_custom_command(TARGET Jigsaw Sandbox POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:Jigsaw> $<TARGET_FILE_DIR:Sandbox>
    )
#========Configuration Settings================================================================================#

cmake_minimum_required(VERSION 3.13)
project(libpag_native)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Recursively collect all source files for this project
file(GLOB_RECURSE PAG_FILES
    "cangjie/*.cpp"
    "../external/platform/*.cpp"
)

# Declare an imported shared library target named 'libpag'
add_library(libpag SHARED IMPORTED)

# Specify the location of the prebuilt libpag.so for the current architecture
set_target_properties(libpag PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs/${OHOS_ARCH}/libpag.so)

# Include directories required for building the native library
include_directories(
    "cangjie"
    "../external/include"
    "../external/platform"
    "../external/third_party/tgfx/include"
    "../external/third_party/lz4/lib"
)

# Define the native shared library target and link it with the source files
add_library(pag_native SHARED ${PAG_FILES})

# Link the native library with prebuilt system and third-party libraries
target_link_libraries(pag_native
    libpag
    libnative_window.so
    libhilog_ndk.z.so
    libnative_vsync.so
    libnative_buffer.so
    libnative_media_vdec.so
    libnative_media_codecbase.so
    libnative_media_core.so
    libGLESv3.so
    libEGL.so
    libpixelmap_ndk.z.so
    libimage_source_ndk.z.so
    libpixelmap.so
    libimage_source.so
    libace_ndk.z.so
    libace_napi.z.so
    libnative_image.so
    librawfile.z.so
)
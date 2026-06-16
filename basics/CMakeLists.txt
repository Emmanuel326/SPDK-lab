cmake_minimum_required(VERSION 3.10)
project(ReactorLifecycle C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 1. Define paths
set(SPDK_DIR "/home/sheriff/Desktop/projects/oss/spdk")

# 2. Find modules
find_package(PkgConfig REQUIRED)
pkg_check_modules(SPDK REQUIRED spdk_event spdk_env_dpdk)

# 3. Add Library Search Paths
# This tells the linker: "Look in these folders for the -l flags"
link_directories(${SPDK_LIBRARY_DIRS})

# 4. Executable
add_executable(reactor_lifecycle reactor_lifecycle.c)

# 5. Include Headers
target_include_directories(reactor_lifecycle PRIVATE ${SPDK_INCLUDE_DIRS})

# 6. The "Sheriff" Link
# Use --whole-archive for SPDK components
target_link_options(reactor_lifecycle PRIVATE "LINKER:--whole-archive")
target_link_libraries(reactor_lifecycle PRIVATE ${SPDK_LIBRARIES} pthread rt dl m numa crypto uuid ssl)
target_link_options(reactor_lifecycle PRIVATE "LINKER:--no-whole-archive")

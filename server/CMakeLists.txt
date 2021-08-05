set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TARGET_NAME server)

set(SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/func.cpp
    ${SRC_DIR}/server.cpp
    ${SRC_DIR}/Client.cpp
)

add_executable(${TARGET_NAME} ${SRC_FILES})

target_include_directories(
    ${TARGET_NAME} PUBLIC
    ${INC_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_options(
    ${TARGET_NAME} PUBLIC
    -pthread
)
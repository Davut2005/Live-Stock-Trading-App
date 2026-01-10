cmake_minimum_required(VERSION 3.26)

# Project name
set(MAIN_PROJECT_NAME "oop_executable")
project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Project sources
set(PROJECT_SOURCES
    includes/Trader.cpp
    includes/Portfolio.cpp
    includes/Logger.cpp
    includes/ScopeTimer.cpp
    includes/Stock.cpp
    includes/HealthStock.cpp
    includes/Transaction.cpp
    includes/TransactionLog.cpp
    includes/BuyOrder.cpp
    includes/SellOrder.cpp
    
    data/CryptoStockData.cpp
    data/EnergyStockData.cpp
    data/HealthStockData.cpp
    data/TechStockData.cpp
    data/TraderData.cpp
)

# External cmake scripts
include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

# ---------------------------
# External dependencies
# ---------------------------

# ASIO path (committed in third-party folder)
set(ASIO_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third-party/asio-asio-1-36-0/asio/include")

# ---------------------------
# Executables
# ---------------------------

add_executable(${MAIN_PROJECT_NAME} main.cpp ${PROJECT_SOURCES})
add_executable(server server.cpp ${PROJECT_SOURCES})

# ---------------------------
# Include directories
# ---------------------------

target_include_directories(${MAIN_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}/exceptions
    ${ASIO_INCLUDE_DIR}
)

target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}/exceptions
    ${CMAKE_SOURCE_DIR}/includes/Crow
    ${ASIO_INCLUDE_DIR}
    /usr/include
)

# ---------------------------
# Compiler flags
# ---------------------------

set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_PROJECT_NAME})

# ---------------------------
# Install & copy helpers
# ---------------------------

install(TARGETS ${MAIN_PROJECT_NAME} DESTINATION ${DESTINATION_DIR})

copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_PROJECT_NAME})
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_PROJECT_NAME})
# copy_files(DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_PROJECT_NAME})

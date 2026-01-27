cmake_minimum_required(VERSION 3.26)

# Project name
set(MAIN_PROJECT_NAME "oop")
project(${MAIN_PROJECT_NAME})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
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
    includes/StockFactory.cpp
    includes/MarketDataManager.cpp
    includes/RiskManager.cpp
    includes/TradingEngine.cpp
    includes/OrderBook.cpp
    includes/PerformanceAnalyzer.cpp
    includes/MarketSimulator.cpp
    includes/TechnicalAnalysis.cpp

    data/CryptoStockData.cpp
    data/EnergyStockData.cpp
    data/HealthStockData.cpp
    data/TechStockData.cpp
    data/TraderData.cpp
    data/HistoricalData.cpp
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

target_link_libraries(oop PRIVATE Threads::Threads)
target_link_libraries(server PRIVATE Threads::Threads)

target_include_directories(server PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${CMAKE_SOURCE_DIR}/exceptions
    ${CMAKE_SOURCE_DIR}/includes/Crow
    ${ASIO_INCLUDE_DIR}
    /usr/include
)

# Link Winsock library for ASIO on Windows
if(WIN32)
    # Link server and oop with Windows networking libraries
    target_link_libraries(oop PRIVATE ws2_32 mswsock advapi32)
    target_link_libraries(server PRIVATE ws2_32 mswsock advapi32)
endif()

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

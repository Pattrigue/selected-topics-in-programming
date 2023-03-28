# Downloads and compiles Google Benchmark
include(FetchContent)
set(FETCHCONTENT_QUIET ON)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

set(BENCHMARK_ENABLE_GTEST_TESTS
    OFF
    CACHE BOOL "" FORCE) # disable google tests
set(BENCHMARK_ENABLE_TESTING
    OFF
    CACHE BOOL "" FORCE) # suppress internal tests
FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.7.1 # "main" for latest
  GIT_SHALLOW TRUE # download specific revision only (git clone --depth 1)
  GIT_PROGRESS TRUE # show download progress in Ninja
  USES_TERMINAL_DOWNLOAD TRUE)
FetchContent_MakeAvailable(googlebenchmark)

message(
  STATUS "!!! Benchmark comparison require python3 and `pip install scipy` !!!")
set(benchmark_cmp python3 ${googlebenchmark_SOURCE_DIR}/tools/compare.py)

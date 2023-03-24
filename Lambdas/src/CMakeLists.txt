add_library(doctest OBJECT doctest.cpp)

add_executable(visitor visitor.cpp)

add_executable(lambda_puzzle1 lambda-puzzle1.cpp doctest.cpp)

add_executable(lambda_puzzle2 lambda-puzzle2.cpp doctest.cpp)

add_executable(lambda_puzzle3 lambda-puzzle3.cpp doctest.cpp)

add_executable(lambda_api lambda_api.cpp)

add_test(NAME visitor COMMAND visitor)
add_test(NAME lambda_puzzle1 COMMAND lambda_puzzle1)
add_test(NAME lambda_puzzle2 COMMAND lambda_puzzle2)
add_test(NAME lambda_puzzle3 COMMAND lambda_puzzle3)
add_test(NAME lambda_api COMMAND lambda_api)
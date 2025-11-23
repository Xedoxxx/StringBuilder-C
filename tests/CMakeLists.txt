add_executable(test_strbld test_strbld.c)
target_link_libraries(test_strbld strbld_t)
target_include_directories(test_strbld PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(NAME strbldTest COMMAND test_strbld)
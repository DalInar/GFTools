message(STATUS "Building tests")

add_library(gf_test gf_test.cpp)
target_link_libraries(gf_test ${LINK_ALL})
list(APPEND LINK_ALL gf_test)

set (test_src
  index_test 
  mesh_test
  one_index_gf_test
  two_index_gf_test
  three_index_gf_test
  four_index_gf_test 
  four_index_gf_pn_test 
  itime_gf_test
    )


foreach(test ${test_src})
    add_gtest(${test})
endforeach(test)

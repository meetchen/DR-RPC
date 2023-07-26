set(SRC_LIST userService.cc ../user.pb.cc)
add_executable(provider ${SRC_LIST})

# 链接 protoc 库
target_link_libraries(provider drrpc protobuf  stdc++fs)


set(SRC_LIST callUserService.cc ../user.pb.cc)
add_executable(comsumer ${SRC_LIST})

# 链接 protoc 库
target_link_libraries(comsumer drrpc protobuf zookeeper_mt stdc++fs)



# 使用 Alpine Linux 作为基础镜像
FROM alpine:latest

# 安装 g++ 和 JsonCpp 的依赖
RUN apk add --update g++ cmake make
RUN apk add jsoncpp-dev --repository=http://dl-cdn.alpinelinux.org/alpine/edge/testing

# 设置工作目录
WORKDIR /app

# 将你的源代码添加到容器中
COPY . /app

# 编译程序
RUN g++ -o jsoncpp_demo01 jsoncpp_demo01.cpp -ljsoncpp

# 运行程序
CMD ["./jsoncpp_demo01"]

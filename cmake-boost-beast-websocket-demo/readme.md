
```shell
sudo apt-get install libboost-all-dev -y
```
```shell
g++ -std=c++14 websocket_server.cpp -o websocket_server -lboost_system -lpthread
```

```shell
./websocket_server
```
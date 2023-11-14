#include <iostream>

// 定义一个简单的结构体
struct MyData {
  int number;
  double value;
};

// 一个接受void指针的函数
void process(void* ptr) {
  // 将void指针转换为MyData类型的指针
  MyData* dataPtr = (MyData*) ptr;

  // 解引用指针来访问成员变量
  std::cout << "Number: " << dataPtr->number << std::endl;
  std::cout << "Value: " << dataPtr->value << std::endl;
}

int main() {
  // 创建一个MyData结构体实例
  MyData data;
  data.number = 42;
  data.value = 3.14;

  // 传递结构体的指针给函数
  process(&data);

  return 0;
}

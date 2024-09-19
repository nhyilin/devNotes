前几天在甲方驻场开发，碰到一个关于c++解析网络消息的共性问题，因为这个点卡了很多次bug。

<!--more-->

解析网络消息是一项常见的任务，通常涉及将接收到的字节数据（如`char*`数组）转换为特定的应用程序所需的结构。这通常意味着你需要了解消息的格式，然后将其解析为自定义的结构或类对象。

## 基本方法举例

下面是一个基本的示例：

假设我们有一个简单的消息格式，其中包含一个整数和一个浮点数，需要将其解析为一个自定义的数据结构。

假设我们目标对象的类名为`HFDJDNRTOutput`（先别管为啥叫这个奇怪的名字了）。

```cp
struct HFDJDNRTOutput {
    int id;
    float value;
    std::string message;
};
```

接下来就是一个解析消息的函数，将`char*`类型的消息转换为`HFDJDNRTOutput`对象：

```cp
HFDJDNRTOutput parseComplexMessage(const char *message, size_t length) {
    if (length < 12)  
    		// Minimum size check (4 bytes for id, 4 for float, 2 for string length, 2 for total length)
        throw std::invalid_argument("Message is too short");

    size_t offset = 0;

    // Read total message length (2 bytes, not used after this in this example)
    uint16_t totalLength;
    std::memcpy(&totalLength, message + offset, sizeof(totalLength));
    offset += sizeof(totalLength);

    // Read ID
    int id;
    std::memcpy(&id, message + offset, sizeof(id));
    offset += sizeof(id);

    // Read Value
    float value;
    std::memcpy(&value, message + offset, sizeof(value));
    offset += sizeof(value);

    // Read string length
    uint16_t strLength;
    std::memcpy(&strLength, message + offset, sizeof(strLength));
    offset += sizeof(strLength);

    // Boundary check
    if (offset + strLength > length) {
        throw std::length_error("String length exceeds message size");
    }

    // Read string data
    std::string strData(message + offset, strLength);

    return HFDJDNRTOutput{id, value, strData};
}

int main() {
    // Example message
    const char exampleMessage[] = {
            0x00, 0x12, // total message length
            0x00, 0x00, 0x00, 0x2A, // id = 42
            0x40, 0x48, 0xF5, 0xC3, // value = 3.14 in IEEE 754 format
            0x00, 0x05, // string length = 5
            'H', 'e', 'l', 'l', 'o'
    };

    size_t messageLength = sizeof(exampleMessage);

    try {
        HFDJDNRTOutput result = parseComplexMessage(exampleMessage, messageLength);

        std::cout << "ID: " << result.id
                  << ", Value: " << result.value
                  << ", Message: " << result.message << std::endl;
    } catch (const std::exception &e)
        std::cerr << "Failed to parse message: " << e.what() << std::endl;

    return 0;
}
```

这样解析不会发生任何错误，并且越界拷贝异常会被捕获。

## 带有vector对象的结构

如果`HFDJDNRTOutput`里包含`std::vector`对象会发生什么。

用一段实际的代码来解释。

```cpp
#include <iostream>
#include <vector>

const int DATA_LEN = 24 * 1024;

struct CTranjInfo {
    double p_x = 0;
    double p_y = 0;
    double p_z = 0;
    double v_x = 0;
    double v_y = 0;
    double v_z = 0;
};

struct HFDJDNRTOutput {
    int ID;
    int ForceType;
    int WeaponType;
    double Size[3];                         //长宽高尺寸(m)
    int VehicleNum;                         //车队数量
    double VehicleSpeed;
    double CurLLA[3];                       //当前经纬高
    int size_Vec;                           //TranjInfoVec的大小
    std::vector<CTranjInfo> TranjInfoVec;   //弹道信息
};

struct BasicHeader {
    int head_num = 0;//Message packet header
};

void UupdateRealTimeData(const HFDJDNRTOutput &hfobj) {
    // do something...
}

void HandleHFDNRealTimeData(char *_data, int _side) {
    BasicHeader _head;
    std::memcpy(&_head, _data, sizeof(BasicHeader));//Retrieve interactive packet header
    int head_info = _head.head_num;

    char *p_recvbuf = new char[DATA_LEN];
    const char *p_body = _data;
    p_body = p_body + sizeof(BasicHeader);
    std::memcpy(p_recvbuf, p_body, DATA_LEN);

    char *p_recv = p_recvbuf;
    for (int i = 0; i < head_info; i++) {
        HFDJDNRTOutput objtemp;
        std::memcpy(&objtemp, p_recv, sizeof(HFDJDNRTOutput));
        UupdateRealTimeData(objtemp);
        p_recv = p_recv + sizeof(HFDJDNRTOutput);
    }
    delete[] p_recvbuf;
}

void TestHandleHFDNRealTimeDataV() {
    BasicHeader _header{3};
    HFDJDNRTOutput _body{1, 1, 1, {1.1, 2.2, 3.3}, 1,
                         1.1, {1.1, 2.2, 3.3}, 2, {}};
    char *data_buffer = new char[sizeof(BasicHeader) + 3 * sizeof(HFDJDNRTOutput)];

    std::memcpy(data_buffer, &_header, sizeof(BasicHeader));
    std::memcpy(data_buffer + sizeof(BasicHeader), &_body, sizeof(_body));
    std::memcpy(data_buffer + sizeof(BasicHeader), &_body, sizeof(_body));
    std::memcpy(data_buffer + sizeof(BasicHeader), &_body, sizeof(_body));

    HandleHFDNRealTimeData(data_buffer, 0);
    delete[]data_buffer;
}

int main() {
    TestHandleHFDNRealTimeDataV();
    return 0;
}
```

## bug分析

这里看起来是没有问题的，其实这段代码在Linux下虽然可以通过编译，但是有时会报内存访问越界的error，在` for (int i = 0; i < head_info; i++) `退出第一个循环的时候报错。

调试过程会发现`TranjInfoVec`对象会出现size很大的情况（结合业务显然是一个错误的size），并且每一个成员为空，所以基本可以断定问题出在`HFDJDNRTOutput`里`TranjInfoVec`的身上。

综上我认为问题出在`std::memcpy(&objtemp, p_recv, sizeof(HFDJDNRTOutput));`，直接把一块已知内存长度的内存数据，复制给未知`std::vector`元素个数的内存空间上，是一个很危险的操作。特殊的，当出现`vector.size() == 0`时，但是代码依旧给出了固定内存长度的数据进行复制，就会导致内存访问越界。

所以修改后较为安全的`HandleHFDNRealTimeData`函数如下：

```cpp
void HandleHFDNRealTimeDataV2(char *_data, int _side) {
    BasicHeader _head;
    std::memcpy(&_head, _data, sizeof(BasicHeader));//取交互数据包头
    int head_info = _head.head_num;

    char *p_recvbuf = new char[DATA_LEN];
    const char *p_body = _data;
    p_body = p_body + sizeof(BasicHeader);
    std::memcpy(p_recvbuf, p_body, DATA_LEN);

    char *p_recv = p_recvbuf;
    for (int i = 0; i < head_info; i++) {
        HFDJDNRTOutput objtemp;
        size_t p_offset = 0;
        std::memcpy(&objtemp + p_offset, p_recv, 3 * sizeof(int));
        p_offset += 3 * sizeof(int);
        std::memcpy(&objtemp + p_offset, p_recv, 3 * sizeof(double));
        p_offset += 3 * sizeof(double);
        std::memcpy(&objtemp + p_offset, p_recv, sizeof(int));
        p_offset += sizeof(int);
        std::memcpy(&objtemp + p_offset, p_recv, 4 * sizeof(double));
        p_offset += 4 * sizeof(double);
        std::memcpy(&objtemp + p_offset, p_recv, sizeof(int));
        p_offset += sizeof(int);

        int size_Vec = 0;
        std::memcpy(&size_Vec, p_recv, sizeof(int));
        std::memcpy(&objtemp + p_offset, p_recv, sizeof(int));
        p_offset += sizeof(int);

        if (size_Vec != 0) {
            std::vector<CTranjInfo> _TranjInfoVec{};
            for (int i = 0; i < size_Vec; i++) {
                CTranjInfo _temp{};
                std::memcpy(&objtemp + p_offset, p_recv, sizeof(CTranjInfo));
                p_offset += sizeof(CTranjInfo);
                _TranjInfoVec.emplace_back(_temp);
            }
        }

        UupdateRealTimeData(objtemp);
        p_recv = p_recv + sizeof(HFDJDNRTOutput);
    }
    delete[] p_recvbuf;
}
```

看起来很蠢很麻烦是不是，没错。

## 一点个人编码习惯

个人倾向将复制部分写进`HFDJDNRTOutput`的构造函数里，然后在每次需要复制相同类型的消息包时，不需要重复写解析消息包的方法，只需要在构造函数里传入`char *`指针即可完成。

结构体改为如下：

```cpp
struct HFDJDNRTOutput {
    int ID;
    int ForceType;
    int WeaponType;
    double Size[3];                         //长宽高尺寸(m)
    int VehicleNum;                         //车队数量
    double VehicleSpeed;
    double CurLLA[3];                       //当前经纬高
    int size_Vec;                           //TranjInfoVec的大小

    std::vector<CTranjInfo> TranjInfoVec;   //弹道信息

    HFDJDNRTOutput(char *){
        // ... to do the copy things like func HandleHFDNRealTimeDataV2
    }
};
```

解析函数改为如下：

```cpp
void HandleHFDNRealTimeDataV3(char *_data, int _side) {
    BasicHeader _head;
    std::memcpy(&_head, _data, sizeof(BasicHeader));//取交互数据包头
    int head_info = _head.head_num;

    char *p_recvbuf = new char[DATA_LEN];
    const char *p_body = _data;
    p_body = p_body + sizeof(BasicHeader);
    std::memcpy(p_recvbuf, p_body, DATA_LEN);

    char *p_recv = p_recvbuf;
    for (int i = 0; i < head_info; i++) {
        HFDJDNRTOutput objtemp(p_recv);
        p_recv+=sizeof (objtemp);
    }
    delete[] p_recvbuf;
}
```

## 闲言多叙

这个bug的优化方式还有很多，比如C++20 引入的位操作和改进的标准库，都可以更好的改进解析，特别是对于简单场景：

借助 `std::copy`：

```cpp
std::vector<int> readVectorData(const char* buffer, size_t vectorSize) {
    std::vector<int> data(vectorSize);
    std::copy(buffer, buffer + vectorSize * sizeof(int), reinterpret_cast<char*>(data.data()));
    return data;
}
```

借助`std::span` 提供数组视图，可以更安全地操作：

```cp
#include <span>

HFDJDNRTOutput parseWithSpan(const char* buffer, size_t length) {
    std::span<const char> spanBuffer(buffer, length);

    size_t offset = 0;

    auto read = [&](auto& dest) {
        std::memcpy(&dest, spanBuffer.data() + offset, sizeof(dest));
        offset += sizeof(dest);
    };

    HFDJDNRTOutput output;
    int vectorSize;

    // Ensure safe bounds checks using span
    read(output.id);
    read(output.value);
    read(vectorSize);

    // Check available length for vector data
    if (offset + vectorSize * sizeof(int) <= spanBuffer.size()) {
        output.data.resize(vectorSize);
        std::memcpy(output.data.data(), spanBuffer.data() + offset, vectorSize * sizeof(int));
    } else {
        throw std::length_error("Insufficient data for vector");
    }

    return output;
}
```

这个bug的深究让我想起来之前第一个带我写c++的师傅，那时候他曾多次督促我阅读《重构》。

不管你有多么喜欢一个人，都不要纠结他能陪你多久，或者能不能走到最后。因为我们来到这个世界上，朋友也好，爱人也罢，都是上天赐给我们最好的礼物，拥有过就好。

不是每个问题都有答案，不是每件事都能如愿，所以没关系，以后我们都会阳光万里。

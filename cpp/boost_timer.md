借用boost库实现timer

## 基础延迟


```cpp
#include <cstdio>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
    boost::asio::io_service io;
    

boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
t.async_wait([](const boost::system::error_code& /*e*/){
    printf("Printed after 1s\n"); });

boost::asio::deadline_timer t2(io, boost::posix_time::seconds(3));
t2.async_wait([](const boost::system::error_code& /*e*/){
    printf("Printed after 3s\n"); });

// both prints happen at the same time,
// but only a single thread is used to handle both timed tasks
// - namely the main thread calling io.run();

io.run();

return 0;

}
```

## 时间段内均匀计时

```cpp
#include <boost/asio.hpp>
#include <iostream>
namespace asio = boost::asio;
using boost::system::error_code;

using namespace std::chrono_literals;
auto now = std::chrono::steady_clock::now;

int main() {
    asio::io_service io;
    asio::steady_timer t(io, 1s);
    int count = 0;
    
    std::function<void(error_code)> handler;
    
    auto const start = now();
    handler = [&](error_code ec) {
        std::cout << "at " << (now() - start) / 1.0ms
                  << "ms handler: " << ec.message() << '\n';
        if (ec.failed())
            return;
        
        if (count++ < 10) {
            t.expires_from_now(500ms);
            t.async_wait(handler);
        }
    };
    
    t.async_wait(handler);
    
    io.run();
    std::cout << "at " << (now() - start) / 1.0ms << " Done\n";
}
```








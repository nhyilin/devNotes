#include <iostream>
#include <thread>
class background_task
{
public:
    void operator()() const
    {
        do_something();
        do_something_else();
    }
};


int main() {
    background_task f;
    std::thread my_thread(f);
}

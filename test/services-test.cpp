#include "microlith/executable_interface.h"
#include "microlith/in_process_service_discoverer.h"
#include "microlith/service_executor.h"
#include "microlith/services.h"

#include <iostream>

class test_interface : public services::service_interface<test_interface>
{
public:
    virtual void test() = 0;
};

class test_service
    : public services::service<test_service>
    , public services::provides_services<services::executable_interface,
                                         test_interface>
    , public services::receives_services<test_interface>
{
public:
    virtual void receive(std::shared_ptr<test_interface> service) override
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void test() override
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void start() override
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }

    void stop() override
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

int main(int argc, char* argv[])
{
    auto app = std::make_shared<services::in_process_service_discoverer>();

    app->discover(std::make_shared<test_service>());
    app->discover(std::make_shared<services::service_executor>());

    return 0;
}

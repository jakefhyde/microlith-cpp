#include "microlith/executable_interface.h"
#include "microlith/in_process_service_discoverer.h"
#include "microlith/service_executor.h"
#include "microlith/services.h"

#include <gtest/gtest.h>

class test_service
    : public microlith::service<test_service>
    , public microlith::provides_services<microlith::executable_interface>
{
public:
    void start() override
    {
        _running = true;
    }

    void stop() override
    {
        _running = false;
    }

    bool _running{};
};

TEST(ServiceExecutorTest, StartAndStop)
{
    auto app = std::make_shared<microlith::in_process_service_discoverer>();

    auto service = std::make_shared<test_service>();
    auto executor = std::make_shared<microlith::service_executor>();

    app->discover(service);

    ASSERT_FALSE(service->_running);

    app->discover(executor);

    ASSERT_TRUE(service->_running);

    executor->stop();

    ASSERT_FALSE(service->_running);
}

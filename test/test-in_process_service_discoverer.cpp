#include "microlith/in_process_service_discoverer.h"
#include "microlith/services.h"

#include <gtest/gtest.h>

class test_interface : public microlith::service_interface<test_interface>
{
public:
};

class test_service
    : public microlith::service<test_service>
    , public microlith::provides_services<test_interface>
    , public microlith::receives_services<test_interface>
{
public:
    virtual void receive(std::shared_ptr<test_interface> service) override
    {
        ASSERT_EQ(id(), service->id());
        ASSERT_EQ(provides(), service->provides());
        ASSERT_EQ(receives(), service->receives());
    }
};

TEST(SelfSubscribeTest, SelfSubscribeTest)
{
    auto app = std::make_shared<microlith::in_process_service_discoverer>();

    app->discover(std::make_shared<test_service>());
}

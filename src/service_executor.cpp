#include "microlith/service_executor.h"

using namespace microlith;

service_executor::~service_executor()
{
    stop();
}

void service_executor::receive(std::shared_ptr<executable_interface> service)
{
    _services.insert(service);

    if (started() || (this == service.get() && !started()))
    {
        service->start();
        _running_services.emplace(std::move(service));
    }
}

void service_executor::start()
{
    if (started())
    {
        MICROLITH_DEBUG("{} already started", id());
        return;
    }

    for (auto service : _services)
    {
        _running_services.insert(service);
        service->start();
    }
}

void service_executor::stop()
{
    if (!started())
    {
        return;
    }

    // prevent double call
    _running_services.erase(_running_services.find(std::shared_ptr<executable_interface>{this, [](auto *) {}}));

    for (auto service : _running_services)
    {
        service->stop();
    }

    _running_services.clear();
}

bool service_executor::started()
{
    return _running_services.find(std::shared_ptr<executable_interface>{this, [](auto *) {}}) != std::end(_running_services);
}

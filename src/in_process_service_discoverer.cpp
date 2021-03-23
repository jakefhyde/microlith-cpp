#include "microlith/in_process_service_discoverer.h"

using namespace services;

void in_process_service_discoverer::discover(std::shared_ptr<abstract_service> service)
{
    if (_services.find(service) != std::end(_services))
    {
        return;
    }

    for (auto s : _services)
    {
        service->_receive_services(s);
        s->_receive_services(service);
    }

    service->_receive_services(service);

    _services.emplace(std::move(service));
}

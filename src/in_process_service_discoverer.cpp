#include "microlith/in_process_service_discoverer.h"

using namespace microlith;

void in_process_service_discoverer::discover(
    std::shared_ptr<abstract_service> service)
{
    MICROLITH_DEBUG("Discovering {}", service->id());

    if (has_service(service->id())) {
        MICROLITH_DEBUG("{} already discovered", service->id());
        return;
    }

    for (auto [i, s] : _services) {
        service->_receive_services(s);
        s->_receive_services(service);
    }

    service->_receive_services(service);

    _services.emplace(service->id(), std::move(service));
}

bool in_process_service_discoverer::has_service(service_id id)
{
    return _services.find(id) != std::end(_services);
}

std::shared_ptr<abstract_service>
in_process_service_discoverer::get_service(service_id id)
{
    if (has_service(id)) {
        return _services[id];
    }
    MICROLITH_DEBUG("{} not discovered", service->id());
    return {};
}

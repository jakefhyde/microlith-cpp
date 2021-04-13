#include "microlith/services.h"

using namespace microlith;

abstract_service::~abstract_service() = default;

service_id abstract_service::id() const
{
    MICROLITH_CRITICAL("Default id called, an interface was provided without inherting abstract_service");
    return {};
}

std::unordered_set<interface_id> abstract_service::provides() const 
{ 
    return {};
}

std::unordered_set<interface_id> abstract_service::receives() const 
{ 
    return {}; 
}

void abstract_service::_receive_services(std::shared_ptr<abstract_service> /* service */)
{

}
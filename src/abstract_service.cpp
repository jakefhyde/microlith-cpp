#include "microlith/services.h"

using namespace services;

abstract_service::~abstract_service() = default;

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
/*!
 * \file in_process_service_discoverer.h
 * 
 * This file is part of the microlith library.
 * microlith is free software, licensed under the MIT License. A copy of the
 * license is provided with the library in the LICENSE file.
 * 
 */

#ifndef MICROLITH_IN_PROCESS_SERVICE_DISCOVERER_H
#define MICROLITH_IN_PROCESS_SERVICE_DISCOVERER_H

#include "microlith/services.h"

namespace services
{

class in_process_service_discoverer
    : public service<in_process_service_discoverer>
    , public provides_services<service_discovery_interface>
{
public:
    void discover(std::shared_ptr<abstract_service> service) override;

private:
    std::unordered_set<std::shared_ptr<abstract_service>> _services{};

}; // class in_process_service_discoverer

} // namespace services

#endif // MICROLITH_IN_PROCESS_SERVICE_DISCOVERER_H

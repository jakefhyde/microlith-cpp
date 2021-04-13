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

namespace microlith
{

class in_process_service_discoverer
    : public service<in_process_service_discoverer>
    , public provides_services<service_discovery_interface>
{
public:
    void discover(std::shared_ptr<abstract_service> service) override;

    bool has_service(service_id id);
    std::shared_ptr<abstract_service> get_service(service_id id);

private:
    std::unordered_map<service_id, std::shared_ptr<abstract_service>> _services{};

}; // class in_process_service_discoverer

} // namespace microlith

#endif // MICROLITH_IN_PROCESS_SERVICE_DISCOVERER_H

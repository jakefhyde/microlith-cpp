/*!
 * \file service_executor.h
 * 
 * This file is part of the microlith library.
 * microlith is free software, licensed under the MIT License. A copy of the
 * license is provided with the library in the LICENSE file.
 * 
 */

#ifndef MICROLITH_SERVICE_EXECUTOR_H
#define MICROLITH_SERVICE_EXECUTOR_H

#include "microlith/executable_interface.h"
#include "microlith/services.h"

#include <unordered_set>

namespace services
{

class service_executor
    : public service<service_executor>
    , public provides_services<executable_interface>
    , public receives_services<executable_interface>
{
public:
    ~service_executor() override;

    void receive(std::shared_ptr<executable_interface> service) override;

    void start() override;
    void stop() override;

    bool started();

private:
    std::unordered_set<std::shared_ptr<executable_interface>> _services{};
    std::unordered_set<std::shared_ptr<executable_interface>>
        _running_services{};

}; // class service_executor

} // namespace services

#endif // MICROLITH_SERVICE_EXECUTOR_H

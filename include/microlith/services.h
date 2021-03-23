/*!
 * \file services.h
 * 
 * This file is part of the microlith library.
 * microlith is free software, licensed under the MIT License. A copy of the
 * license is provided with the library in the LICENSE file.
 * 
 */

#ifndef MICROLITH_SERVICES_H
#define MICROLITH_SERVICES_H

#include <ctti/type_id.hpp>
#include <memory>
#include <unordered_set>

namespace services
{

using interface_id = std::string;
using service_id   = std::string;

namespace detail
{

template <typename T>
interface_id get_interface_id()
{
    return ctti::nameof<T>().str();
}

} // namespace detail

class abstract_service
{
public:
    virtual ~abstract_service();

    virtual std::unordered_set<interface_id> provides() const;
    virtual std::unordered_set<interface_id> receives() const;

    virtual void _receive_services(std::shared_ptr<abstract_service> service);

}; // class abstract_service

template <typename T>
class service : public virtual abstract_service
{
public:
}; // class service

template <typename T>
class service_interface : public virtual abstract_service
{
public:
}; // class service_interface

template <typename T>
class provides_service
    : public T
    , public virtual abstract_service
{
public:
}; // class provides_service

template <typename T>
class receives_service : public virtual abstract_service
{
public:
    virtual void receive(std::shared_ptr<T> service)
    {
    }

    void _receive_service(std::shared_ptr<abstract_service> service)
    {
        const auto& receives = this->receives();
        for (auto provider : service->provides()) {
            if (receives.find(provider) == std::end(receives)) {
                continue;
            }

            receive(std::dynamic_pointer_cast<T>(service));
        }
    }

}; // class receives_service

template <typename... Args>
class provides_services : public provides_service<Args>...
{
public:
    std::unordered_set<interface_id> provides() const override
    {
        return {detail::get_interface_id<Args>()...};
    }

}; // class provides_service

template <typename... Args>
class receives_services : public receives_service<Args>...
{
public:
    std::unordered_set<interface_id> receives() const override
    {
        return {detail::get_interface_id<Args>()...};
    }

    void _receive_services(std::shared_ptr<abstract_service> service)
    {
        (receives_service<Args>::_receive_service(service), ...);
    }

}; // class receives_services

class service_discovery_interface
    : public service_interface<service_discovery_interface>
{
public:
    virtual void discover(std::shared_ptr<abstract_service> service) = 0;

}; // class service_discovery_interface

} // namespace services

#endif // MICROLITH_SERVICES_H
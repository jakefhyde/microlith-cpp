/*!
 * MIT License
 *
 * Copyright (c) 2021 Dragozir
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * \file services.h
 *
 * This file is part of the microlith library.
 * microlith is free software, licensed under the MIT License. A copy of the
 * license is provided with the library in the LICENSE file.
 *
 */

#ifndef INCLUDE_MICROLITH_SERVICES_H_
#define INCLUDE_MICROLITH_SERVICES_H_

#include <memory>
#include <string>
#include <unordered_set>
// noreorder
#include <ctti/type_id.hpp>

#include "detail/log.h"

namespace microlith {

using interface_id = std::string;
using service_id = std::string;

namespace detail {

template <typename T>
interface_id get_interface_id() {
  return ctti::nameof<T>().str();
}

template <typename T>
service_id get_service_id() {
  return ctti::nameof<T>().str();
}

}  // namespace detail

class abstract_service {
 public:
  virtual ~abstract_service();

  virtual service_id id() const;

  virtual std::unordered_set<interface_id> provides() const;
  virtual std::unordered_set<interface_id> receives() const;

  virtual void _receive_services(std::shared_ptr<abstract_service> service);
};  // class abstract_service

template <typename T>
class service : public virtual abstract_service {
 public:
  service_id id() const override { return detail::get_service_id<T>(); }
};  // class service

template <typename T>
class service_interface : public virtual abstract_service {
 public:
};  // class service_interface

template <typename T>
class provides_service : public T, public virtual abstract_service {
 public:
};  // class provides_service

template <typename T>
class receives_service : public virtual abstract_service {
 public:
  virtual void receive(std::shared_ptr<T> /* service */) {}

  void _receive_service(std::shared_ptr<abstract_service> service) {
    const auto &receives = this->receives();
    for (auto provider : service->provides()) {
      if (receives.find(provider) == std::end(receives)) {
        continue;
      }

      MICROLITH_TRACE("{} receiving {} as {}", abstract_service::id(),
                      service->id(), provider);
      receive(std::dynamic_pointer_cast<T>(service));
    }
  }
};  // class receives_service

template <typename... Args>
class provides_services : public provides_service<Args>... {
 public:
  std::unordered_set<interface_id> provides() const override {
    return {detail::get_interface_id<Args>()...};
  }
};  // class provides_service

template <typename... Args>
class receives_services : public receives_service<Args>... {
 public:
  std::unordered_set<interface_id> receives() const override {
    return {detail::get_interface_id<Args>()...};
  }

  void _receive_services(std::shared_ptr<abstract_service> service) {
    (receives_service<Args>::_receive_service(service), ...);
  }
};  // class receives_services

class service_discovery_interface
    : public service_interface<service_discovery_interface> {
 public:
  virtual void discover(std::shared_ptr<abstract_service> service) = 0;
};  // class service_discovery_interface

}  // namespace microlith

#endif  // INCLUDE_MICROLITH_SERVICES_H_

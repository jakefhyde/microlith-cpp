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
 * \file in_process_service_discoverer.cpp
 *
 */

#include "microlith/in_process_service_discoverer.h"

namespace microlith {

void in_process_service_discoverer::discover(
    std::shared_ptr<abstract_service> service) {
  auto id = service->id();
  MICROLITH_DEBUG("Discovering {}", id);

  if (has_service(id)) {
    MICROLITH_DEBUG("{} already discovered", id);
    return;
  }

  for (auto [i, s] : _services) {
    service->_receive_services(s);
    s->_receive_services(service);
  }

  service->_receive_services(service);

  _services.emplace(id, std::move(service));
}

bool in_process_service_discoverer::has_service(service_id id) {
  return _services.find(id) != std::end(_services);
}

std::shared_ptr<abstract_service> in_process_service_discoverer::get_service(
    service_id id) {
  if (has_service(id)) {
    return _services[id];
  }
  MICROLITH_DEBUG("{} not discovered", service->id());
  return {};
}

}  // namespace microlith

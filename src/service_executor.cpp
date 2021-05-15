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
 * \file service_executor.cpp
 *
 */

#include "microlith/service_executor.h"

namespace microlith {

service_executor::~service_executor() { stop(); }

void service_executor::receive(std::shared_ptr<executable_interface> service) {
  _services.insert(service);

  if (started() || (this == service.get() && !started())) {
    service->start();
    _running_services.emplace(std::move(service));
  }
}

void service_executor::start() {
  if (started()) {
    MICROLITH_DEBUG("{} already started", id());
    return;
  }

  for (auto service : _services) {
    _running_services.insert(service);
    service->start();
  }
}

void service_executor::stop() {
  if (!started()) {
    return;
  }

  // prevent double call
  _running_services.erase(_running_services.find(
      std::shared_ptr<executable_interface>{this, [](auto *) {}}));

  for (auto service : _running_services) {
    service->stop();
  }

  _running_services.clear();
}

bool service_executor::started() {
  return _running_services.find(std::shared_ptr<executable_interface>{
             this, [](auto *) {}}) != std::end(_running_services);
}
}  // namespace microlith

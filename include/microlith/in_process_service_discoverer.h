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
 * \file in_process_service_discoverer.h
 *
 * This file is part of the microlith library.
 * microlith is free software, licensed under the MIT License. A copy of the
 * license is provided with the library in the LICENSE file.
 *
 */

#ifndef INCLUDE_MICROLITH_IN_PROCESS_SERVICE_DISCOVERER_H_
#define INCLUDE_MICROLITH_IN_PROCESS_SERVICE_DISCOVERER_H_

#include <memory>
#include <unordered_map>

#include "microlith/services.h"

namespace microlith {

class in_process_service_discoverer
    : public service<in_process_service_discoverer>,
      public provides_services<service_discovery_interface<0>> {
 public:
  void discover(std::shared_ptr<abstract_service> service) override;

  bool has_service(service_id id);
  std::shared_ptr<abstract_service> get_service(service_id id);

 private:
  std::unordered_map<service_id, std::shared_ptr<abstract_service>> _services{};
};  // class in_process_service_discoverer

}  // namespace microlith

#endif  // INCLUDE_MICROLITH_IN_PROCESS_SERVICE_DISCOVERER_H_

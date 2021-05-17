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
 * \file test-service_executor.cpp
 *
 */

#include <gtest/gtest.h>

#include "microlith/executable_interface.h"
#include "microlith/in_process_service_discoverer.h"
#include "microlith/service_executor.h"
#include "microlith/services.h"

class test_service1
    : public microlith::service<test_service1>,
      public microlith::provides_services<microlith::executable_interface> {
 public:
  void start() override { _running = true; }

  void stop() override { _running = false; }

  bool _running{};
};

TEST(ServiceExecutorTest, StartAndStop) {
  auto app = std::make_shared<microlith::in_process_service_discoverer>();

  auto service = std::make_shared<test_service1>();
  auto executor = std::make_shared<microlith::service_executor>();

  app->discover(service);

  ASSERT_FALSE(service->_running);

  app->discover(executor);

  ASSERT_TRUE(service->_running);

  executor->stop();

  ASSERT_FALSE(service->_running);
}

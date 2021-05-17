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
 * \file test-in_process_service_discoverer.cpp
 *
 */

#include <gtest/gtest.h>

#include "microlith/in_process_service_discoverer.h"
#include "microlith/services.h"

class empty_interface : public microlith::service_interface<test_interface> {
 public:
};

class test_service : public microlith::service<test_service>,
                     public microlith::provides_services<empty_interface>,
                     public microlith::receives_services<empty_interface> {
 public:
  void receive(std::shared_ptr<empty_interface> service) override {
    ASSERT_EQ(id(), service->id());
    ASSERT_EQ(provides(), service->provides());
    ASSERT_EQ(receives(), service->receives());
  }
};

TEST(SelfSubscribeTest, SelfSubscribeTest) {
  auto app = std::make_shared<microlith::in_process_service_discoverer>();

  app->discover(std::make_shared<test_service>());
}

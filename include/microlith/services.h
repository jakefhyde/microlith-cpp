// MIT License

// Copyright (c) 2021 Dragozir

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef MICROLITH_SERVICES_H
#define MICROLITH_SERVICES_H

#include <memory>

namespace services
{

class abstract_service
{
public:
};

template <typename T>
class service 
    : public abstract_service
{
public:
}; // service

template <typename T>
class service_interface
    : public virtual abstract_service
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
class receives_service
    : public virtual abstract_service
{
public:
    virtual void receive(std::shared_ptr<T> service) {};

}; // class receives_service

template <typename... Args>
class provides_services
    : public provides_service<T>
{
public:
}; // class provides_service

template <typename... Args>
class receives_services
    : public receives_services<Args...>
{
public:
    virtual void receive(std::shared_ptr<T> service) {};
}; // receives_services

class service_discoverer
    : public service_interface<service_discoverer>
{
public:
    virtual void discover(std::shared_ptr<abstract_service> service) = 0;
}; // service_discoverer

class in_process_service_discoverer
    : public service<in_process_service_discoverer>
    , public provides_services<service_discoverer>
{
public:
    void discover(std::shared_ptr<abstract_service> service) override
    {

    }
}; // in_process_service_discoverer

} // namespace services

#endif // MICROLITH_SERVICES_H
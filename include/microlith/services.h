
namespace services
{

class abstract_service
{

};

template <typename T>
class service_interface
    : public virtual abstract_service
{

};

template <typename T>
class provides_service
    : public T
    , public virtual abstract_service
{

};

template <typename T>
class receives_service
    : public virtual abstract_service
{
    virtual void receive(std::shared_ptr<T> service) {};
};


} // namespace services
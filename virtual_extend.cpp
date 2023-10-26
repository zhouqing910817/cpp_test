#include <string>
#include <iostream>
class Proxy;
class BaseService;
class Listener {
    public:
    Proxy* adapter_;
    void f();
};
Listener lis;
class BaseService {
protected:
    std::string app_id_;
    std::string app_name_;
    std::string service_address_ = "NOT INIT";

public:
    BaseService(const std::string& app_id, const std::string& app_name, const std::string& service_addr) {
        std::cout << "BaseService()" << std::endl;
        std::cout << "BaseService() app_id_:" << app_id_ << std::endl;
        std::cout << "BaseService() app_name_" << app_name_ << std::endl;
        std::cout << "BaseService() service_address_:" << service_address_ << std::endl;
        std::cout << "BaseService() app_id:" << app_id << std::endl;
        std::cout << "BaseService() app_name:" << app_name << std::endl;
        std::cout << "BaseService() service_addr:" << service_addr << std::endl;
    }
    BaseService() : app_id_("def"), app_name_("def"), service_address_("def"){
        std::cout << "BaseService()" << std::endl;
        std::cout << "BaseService() app_id_:" << app_id_ << std::endl;
        std::cout << "BaseService() app_name_" << app_name_ << std::endl;
        std::cout << "BaseService() service_address_:" << service_address_ << std::endl;
    }
    const std::string& ServiceAddress() const { return service_address_; }
};

class Interface {
    public:
        virtual void interface() = 0;
};

class Proxy : public Interface, virtual public BaseService {
    public:
        Proxy(const std::string& app_id, const std::string& app_name, const std::string& service_addr) {
            app_id_ = app_id;
            app_name_ = app_name;
            service_address_ = service_addr;
            lis.adapter_ = this;
            std::cout << "Proxy()" << std::endl;
            std::cout << "Proxy() app_id_:" << app_id_ << std::endl;
            std::cout << "Proxy() app_name_" << app_name_ << std::endl;
            std::cout << "Proxy() service_address_:" << service_address_ << std::endl;
            std::cout << "Proxy() app_id:" << app_id << std::endl;
            std::cout << "Proxy() app_name" << app_name << std::endl;
            std::cout << "Proxy() service_addr:" << service_addr << std::endl;
        }
        void interface() override {
            std::cout << ((BaseService*)this)->ServiceAddress() << std::endl;
            std::cout << this->ServiceAddress() << std::endl;
            lis.f();
        }
};

class RegisterService : virtual public BaseService {
    public:
        RegisterService() {
            std::cout << "RegisterService()" << std::endl;
            std::cout << "RegisterService() app_id_:" << app_id_ << std::endl;
            std::cout << "RegisterService() app_name_" << app_name_ << std::endl;
            std::cout << "RegisterService() service_address_:" << service_address_ << std::endl;
        }
};

class App : virtual public Proxy, virtual public RegisterService {
    public:
        App(const std::string& app_id, const std::string& app_name, const std::string& service_addr):Proxy(app_id,app_name,service_addr) {
            std::cout << "App()" << std::endl;
            std::cout << "App() app_id_:" << app_id_ << std::endl;
            std::cout << "App() app_name_" << app_name_ << std::endl;
            std::cout << "App() service_address_:" << service_address_ << std::endl;
            std::cout << "App() app_id:" << app_id << std::endl;
            std::cout << "App() app_name" << app_name << std::endl;
            std::cout << "App() service_addr:" << service_addr << std::endl;
        }

};

void Listener::f() {
    std::cout << "f() " << ((BaseService*)adapter_)->ServiceAddress() << std::endl;
    std::cout << "f() " << adapter_->ServiceAddress() << std::endl;
}
int main() {

    auto app = new App("1", "2", "my_service_addr");
    app->interface();
    delete app;
}

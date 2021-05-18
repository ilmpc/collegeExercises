#include "IOperationFactory.h"


IOperationFactory::IOperationFactory(stack *stack) : mCache(new std::map<std::string, IOperation *>()),
                                                       mStack(stack) {}

IOperation *IOperationFactory::createOperation(std::string name, const std::list<double> *args) {
    auto it = mCache->find(name);
    auto t_context = new context(mStack,args);
    if (it != mCache->end()) {
        auto temp = mCache->at(name);
        assert(temp != nullptr);
        temp->set_context(*t_context);
        delete t_context; //TODO: Так вообще можно делать?
        return temp;
    }
    IOperation *temp;
    SWITCH(name) {
        CASE("pop"):
            temp = new pop(*t_context);
            delete t_context;
            mCache->insert(std::pair<std::string, IOperation *>("pop", temp));
            return temp;
        CASE("push"):
            temp = new push(*t_context);
            delete t_context;
            mCache->insert(std::pair<std::string, IOperation *>("push", temp));
            return temp;
        CASE("print"):
            temp = new print(*t_context);
            delete t_context;
            mCache->insert(std::pair<std::string, IOperation *>("print", temp));
            return temp;
        CASE("+"):
            temp = new sum(*t_context);
            delete t_context;
            mCache->insert(std::pair<std::string, IOperation *>("+", temp));
            return temp;
        CASE("-"):
            temp = new subtraction(*t_context);
            delete t_context;
            mCache->insert(std::pair<std::string, IOperation *>("-", temp));
            return temp;
        CASE("/"):
            temp = new division(*t_context);
            delete t_context;
            mCache->insert(std::pair<std::string, IOperation *>("/", temp));
            return temp;
        CASE("*"):
            temp = new multiplication(*t_context);
            delete t_context;
            mCache->insert(std::pair<std::string, IOperation *>("*", temp));
            return temp;
        CASE("sqrt"):
            temp = new class sqrt(*t_context);
            delete t_context;
            mCache->insert(std::pair<std::string, IOperation *>("sqrt", temp));
            return temp;
        DEFAULT:
            throw std::logic_error("No such command \""+name+"\"");
    }
}

IOperationFactory::~IOperationFactory() {
    delete mCache;
}

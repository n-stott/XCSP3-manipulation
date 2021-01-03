#ifndef XPOOL_H
#define XPOOL_H

#include <vector>
#include <memory>
#include <utility>
#include <iostream>
#include <typeinfo>

namespace XCSP3Core {

    template<typename Data>
    struct Pool {
        std::vector<std::unique_ptr<Data>> pool_;

        template <typename T, typename... U>
        T* make(U&&... us) {
            pool_.emplace_back(new T(std::forward<U>(us)...));
            return static_cast<T*>(pool_.back().get());
        }

        ~Pool() {
            std::cout << typeid(Data).name() << " : " << pool_.size() << " freed from pool" << std::endl;
        }
    };

    class XEntity;
    class XIntegerEntity;
    class XDomain;
    class XConstraint;
    class XObjective;
    class Node;

    struct DataPool {
        static Pool<XEntity> EntityPool;
        static Pool<XIntegerEntity> IntegerEntityPool;
        static Pool<XDomain> DomainPool;
        static Pool<XConstraint> ConstraintPool;
        static Pool<XObjective> ObjectivePool;
        static Pool<Node> NodePool;
    };

}

#endif
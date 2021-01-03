#include "XCSP3Pool.h"
#include "XCSP3Domain.h"
#include "XCSP3Objective.h"
#include "XCSP3Variable.h"
#include "XCSP3Constraint.h"

namespace XCSP3Core {
    Pool<XEntity> DataPool::EntityPool;
    Pool<XIntegerEntity> DataPool::IntegerEntityPool;
    Pool<XDomain> DataPool::DomainPool;
    Pool<XConstraint> DataPool::ConstraintPool;
    Pool<XObjective> DataPool::ObjectivePool;
}
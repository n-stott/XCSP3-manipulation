/*=============================================================================
 * parser for CSP instances represented in XCSP3 Format
 * 
 * Copyright (c) 2015 xcsp.org (contact <at> xcsp.org)
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *=============================================================================
 */
#ifndef XCSP3CONSTANTS_H
#define XCSP3CONSTANTS_H
#include <cassert>
#include <climits>
#include <string>

namespace XCSP3Core {

    enum class InstanceType {
        CSP,
        COP
    };

    enum class ConstraintType {
        UNKNOWN,
        EXTENSION,
        INTENSION,
        ALLDIFF,
        ALLEQUAL,
        SUM,
        ORDERED,
        COUNT,
        NVALUES,
        CARDINALITY,
        MAXIMUM,
        MINIMUM,
        ELEMENT,
        ELEMENTMATRIX,
        NOOVERLAP,
        STRETCH,
        LEX,
        CHANNEL,
        REGULAR,
        MDD,
        CUMULATIVE,
        INSTANTIATION,
        CIRCUIT,
        CLAUSE
    };

    enum class OrderType {
        LE,
        LT,
        GE,
        GT,
        IN,
        EQ,
        NE
    };

    inline std::string OrderTypeToString(OrderType op) {
        switch (op) {
        case OrderType::LE:
            return "<=";
        case OrderType::LT:
            return "<";
        case OrderType::GE:
            return ">=";
        case OrderType::GT:
            return ">";
        case OrderType::IN:
            return "in";
        case OrderType::EQ:
            return "==";
        case OrderType::NE:
            return "!=";
        }
        assert(false);
        return "undefined";
    }

    enum class OperandType {
        INTEGER,
        INTERVAL,
        VARIABLE
    };

    enum class Tag {
        UNKNOWNTAG,
        LISTTAG,
        FUNCTIONALTAG,
        VALUESTAG,
        VALUETAG,
        CONDITIONTAG,
        INDEXTAG,
        LENGTHSTAG
    };

    enum class RankType {
        ANY,
        FIRST,
        LAST
    };

    enum class ObjectiveGoal {
        MINIMIZE,
        MAXIMIZE
    };

    enum class ExpressionObjective {
        EXPRESSION_O,
        SUM_O,
        PRODUCT_O,
        MINIMUM_O,
        MAXIMUM_O,
        NVALUES_O,
        LEX_O
    };

    inline std::string ExpressionObjectiveToString(ExpressionObjective op) {
        switch (op) {
        case ExpressionObjective::EXPRESSION_O:
            return "0*";
        case ExpressionObjective::SUM_O:
            return "sum";
        case ExpressionObjective::PRODUCT_O:
            return "prod";
        case ExpressionObjective::MINIMUM_O:
            return "min";
        case ExpressionObjective::MAXIMUM_O:
            return "max";
        case ExpressionObjective::NVALUES_O:
            return "0*";
        case ExpressionObjective::LEX_O:
            return "0*";
        }
        assert(false);
        return "0*";
    }

#define STAR INT_MAX
} // namespace XCSP3Core
#endif /* XCSP3CONSTANTS_H */

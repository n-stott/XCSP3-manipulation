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
#ifndef XCONSTRAINT_H
#define XCONSTRAINT_H

#include "XCSP3Constants.h"
#include "XCSP3Variable.h"
#include "XCSP3utils.h"
#include <map>
#include <regex>
#include <typeinfo>

namespace XCSP3Core {

    class XConstraintGroup;

    class XConstraintIntension;

    /***************************************************************************
     * A constraint XValue
     **************************************************************************/
    class XConstraint {
    public:
        std::string id;
        std::vector<XVariable*> list;
        std::string classes;

        XConstraint(std::string dd, std::string c) : id(dd), classes(c) {}

        virtual ~XConstraint() {}

        virtual void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original);
    };

    /***************************************************************************
     * A constraint group
     * Only basic abstraction is implemented: All parameters occur in the same tag
     **************************************************************************/

    class XConstraintGroup : public XConstraint {
    public:
        XConstraint* constraint;                        // A Constraint group contains a constraint
        std::vector<std::vector<XVariable*>> arguments; // The list of all arguments
        ConstraintType type;                            // Use it to discover the type of constraint... and perform cast
        std::map<std::string, XVariable*> toArguments;

        XConstraintGroup(std::string idd, std::string c) : XConstraint(idd, c), constraint(NULL), type(ConstraintType::UNKNOWN) {}

        virtual ~XConstraintGroup() {  }

        void unfoldVector(std::vector<XVariable*>& toUnfold, std::vector<XVariable*>& args, std::vector<XVariable*>& initial);
        void unfoldString(std::string& toUnfold, std::vector<XVariable*>& args);
        void unfoldArgumentNumber(int, XConstraint* builtConstraint);
    };

    // All different structures related to XVariables used in constraints
    // This facilitates the unfolding of group constraint

    class XCondition {
    public:
        OrderType op;
        OperandType operandType;
        int val;
        int min, max;
        std::string var;

        friend std::ostream& operator<<(std::ostream& f, const XCSP3Core::XCondition& ie);
    };

    class XInitialCondition {
    public:
        std::string condition;

        virtual void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original);
        void extractCondition(XCondition& xc); // Create the op and the operand (which can be a value, an interval or a XVariable)
    };

    class XValues {
    public:
        std::vector<XVariable*> values; // Only XVariable or XInteger

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original);
    };

    class XValue {
    public:
        XVariable* value;

        XValue() : value(0) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original);
    };

    class XIndex {
    public:
        XVariable* index;

        XIndex() : index(0) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original);
    };

    class XLengths {
    public:
        std::vector<XVariable*> lengths;

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original);
    };

    /***************************************************************************
     * constraint extension
     **************************************************************************/
    class XConstraintExtension : public XConstraint {

    public:
        std::vector<std::vector<int>> tuples;
        bool isSupport;
        bool containsStar;

        XConstraintExtension(std::string idd, std::string c) : XConstraint(idd, c), containsStar(false) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     * constraint intension
     **************************************************************************/
    class XConstraintIntension : public XConstraint {

    public:
        std::string function;

        XConstraintIntension(std::string idd, std::string c) : XConstraint(idd, c) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     ****************************************************************************
     *                  CONSTRAINTS DEFINED ON LANGAGES
     ****************************************************************************
     ***************************************************************************/

    /***************************************************************************
     * constraint regular
     **************************************************************************/
    class XTransition {
    public:
        XTransition(std::string f, int v, std::string t) : from(f), val(v), to(t) {}

        std::string from;
        int val;
        std::string to;
    };

    extern std::vector<XTransition> tr; // Not beautiful but remove code to fixed data in group constraint.
    extern std::string st;
    extern std::vector<std::string> fi;

    class XConstraintRegular : public XConstraint {
    public:
        std::string& start;
        std::vector<std::string>& final;
        std::vector<XTransition>& transitions;

        XConstraintRegular(std::string idd, std::string c) : XConstraint(idd, c), start(st), final(fi), transitions(tr) {}
    };

    /***************************************************************************
     * constraint mdd
     **************************************************************************/

    class XConstraintMDD : public XConstraint {
    public:
        std::vector<XTransition>& transitions;

        XConstraintMDD(std::string idd, std::string c) : XConstraint(idd, c), transitions(tr) {}
    };

    /***************************************************************************
     ****************************************************************************
     *                  COMPARISON BASED CONSTRAINTS
     ****************************************************************************
     ***************************************************************************/
    extern std::vector<int> _except;

    class XConstraintAllDiff : public XConstraint {
    public:
        std::vector<int>& except;

        XConstraintAllDiff(std::string idd, std::string c) : XConstraint(idd, c), except(_except) {}
    };

    class XConstraintAllDiffMatrix : public XConstraint {
    public:
        std::vector<std::vector<XVariable*>> matrix;

        XConstraintAllDiffMatrix(std::string idd, std::string c) : XConstraint(idd, c) {}

        XConstraintAllDiffMatrix(std::string idd, std::string c, std::vector<std::vector<XVariable*>>& mat) : XConstraint(idd, c) {
            matrix.resize(mat.size());
            for (unsigned int i = 0; i < mat.size(); i++)
                matrix[i].assign(mat[i].begin(), mat[i].end());
        }

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    typedef XConstraintAllDiffMatrix XConstraintAllDiffList;

    typedef XConstraint XConstraintAllEqual;

    /***************************************************************************
     * constraint ordered and lex
     **************************************************************************/

    extern OrderType _op;

    class XConstraintOrdered : public XConstraint, public XLengths {
    public:
        OrderType& op;

        XConstraintOrdered(std::string idd, std::string c) : XConstraint(idd, c), op(_op) {}
        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    class XConstraintLex : public XConstraintOrdered {
    public:
        // list is cleard and all lists are stored in lists
        std::vector<std::vector<XVariable*>> lists;

        XConstraintLex(std::string idd, std::string c) : XConstraintOrdered(idd, c) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    class XConstraintLexMatrix : public XConstraintOrdered {
    public:
        std::vector<std::vector<XVariable*>> matrix;

        XConstraintLexMatrix(std::string idd, std::string c) : XConstraintOrdered(idd, c) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     ****************************************************************************
     *                  SUMMING and COUNTING CONSTRAINTS
     ****************************************************************************
     ***************************************************************************/

    /***************************************************************************
     * constraint sum
     **************************************************************************/

    //static vector<int> _coeffs;

    class XConstraintSum : public XConstraint, public XInitialCondition, public XValues {
    public:
        //     vector<int> &coeffs;

        XConstraintSum(std::string idd, std::string c) : XConstraint(idd, c) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    class XConstraintNValues : public XConstraint, public XInitialCondition {
    public:
        std::vector<int>& except;

        XConstraintNValues(std::string idd, std::string c) : XConstraint(idd, c), except(_except) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    class XConstraintCardinality : public XConstraint, public XValues {
    public:
        std::vector<XVariable*> occurs;
        bool closed;

        XConstraintCardinality(std::string idd, std::string c) : XConstraint(idd, c) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     * constraint count
     **************************************************************************/

    class XConstraintCount : public XConstraint, public XInitialCondition, public XValues {
    public:
        XConstraintCount(std::string idd, std::string c) : XConstraint(idd, c) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     ****************************************************************************
     *                  CONNECTION  CONSTRAINTS
     ****************************************************************************
     ***************************************************************************/

    /***************************************************************************
     * constraint minimum and maximum
     * startIndex and rank are useful iff index!=NULL
     * in such a case condition is optionnal (=="")
     **************************************************************************/

    class XConstraintMaximum : public XConstraint, public XInitialCondition, public XIndex {
    public:
        int startIndex;
        RankType rank;

        XConstraintMaximum(std::string idd, std::string c) : XConstraint(idd, c), startIndex(0), rank(RankType::ANY) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    typedef XConstraintMaximum XConstraintMinimum;

    /***************************************************************************
     * constraint element
     **************************************************************************/

    class XConstraintElement : public XConstraint, public XIndex, public XValue {
    public:
        int startIndex;
        RankType rank;

        XConstraintElement(std::string idd, std::string c) : XConstraint(idd, c), startIndex(0), rank(RankType::ANY) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    class XConstraintElementMatrix : public XConstraintElement {
    public:
        std::vector<std::vector<XVariable*>> matrix;
        XVariable* index2;
        int startRowIndex, startColIndex;

        XConstraintElementMatrix(std::string idd, std::string c) : XConstraintElement(idd, c) {}

        XConstraintElementMatrix(std::string idd, std::string c, std::vector<std::vector<XVariable*>>& mat) : XConstraintElement(idd, c) {
            matrix.resize(mat.size());
            for (unsigned int i = 0; i < mat.size(); i++)
                matrix[i].assign(mat[i].begin(), mat[i].end());
        }

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     * constraint channel
     **************************************************************************/

    class XConstraintChannel : public XConstraint, public XValue {
    public:
        std::vector<XVariable*> secondList;
        int startIndex1;
        int startIndex2;

        XConstraintChannel(std::string idd, std::string c) : XConstraint(idd, c), startIndex1(0), startIndex2(0) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     ****************************************************************************
     *                  PACKING AND SCHEDULING CONSTRAINTS
     ****************************************************************************
     ***************************************************************************/

    /***************************************************************************
     * constraint noOverlap
     **************************************************************************/

    class XConstraintNoOverlap : public XConstraint, public XLengths {
    public:
        // Be careful origins is the vector list!!!
        std::vector<XVariable*>& origins;
        bool zeroIgnored;

        XConstraintNoOverlap(std::string idd, std::string c) : XConstraint(idd, c), origins(list) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     * constraint Cumulative
     **************************************************************************/
    class XConstraintCumulative : public XConstraint, public XLengths, public XInitialCondition {
    public:
        // Be careful origin is the vector list!!!
        std::vector<XVariable*>& origins;
        std::vector<XVariable*> ends;
        std::vector<XVariable*> heights;

        XConstraintCumulative(std::string idd, std::string c) : XConstraint(idd, c), origins(list) {}

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     * constraint stretch
     **************************************************************************/

    class XConstraintStretch : public XConstraint {
    public:
        std::vector<int> values;       // Only integers
        std::vector<XInterval> widths; // interval
        std::vector<std::vector<int>> patterns;

        XConstraintStretch(std::string idd, std::string c) : XConstraint(idd, c) {}

        // Group is valied with lists only.
        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     * constraint instantiation
     **************************************************************************/

    extern std::vector<int> _values;

    class XConstraintInstantiation : public XConstraint {
    public:
        std::vector<int>& values;

        XConstraintInstantiation(std::string idd, std::string c) : XConstraint(idd, c), values(_values) {}
    };

    /***************************************************************************
     * constraint clause
     **************************************************************************/

    class XConstraintClause : public XConstraint {
    public:
        std::vector<XVariable*> positive;
        std::vector<XVariable*> negative;

        XConstraintClause(std::string idd, std::string c) : XConstraint(idd, c) {}
        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

    /***************************************************************************
     ****************************************************************************
    *                  COMPARISON BASED CONSTRAINTS
    ****************************************************************************
    ***************************************************************************/

    class XConstraintCircuit : public XConstraint, public XValue { // value => size
    public:
        XConstraintCircuit(std::string idd, std::string c) : XConstraint(idd, c) {}
        int startIndex;

        void unfoldParameters(XConstraintGroup* group, std::vector<XVariable*>& arguments, XConstraint* original) override;
    };

} // namespace XCSP3Core

#endif /* XCONSTRAINT_H */

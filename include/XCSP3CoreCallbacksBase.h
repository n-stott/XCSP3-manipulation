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
#ifndef COSOCO_XCSP3CORECALLBACKSBASE_H
#define COSOCO_XCSP3CORECALLBACKSBASE_H

#include "XCSP3Constants.h"
#include "XCSP3Constraint.h"
#include "XCSP3Tree.h"
#include "XCSP3Variable.h"
#include <string>
#include <vector>

namespace XCSP3Core {

    class XCSP3CoreCallbacksBase {
        friend class XCSP3Manager;

    protected:
        std::vector<std::string> classesToDiscard;
        std::vector<std::vector<XVariable*>>* _arguments;

    public:
        /**
         * If true, the intension constraint are retrieved with an expression (nothing is done in order to help you)
         * (false by default)
         * Otherwise, the callback that take a canonized tree of the expression is called
         */
        bool intensionUsingString;

        /**
         * If true, the parse recognizes special intensional constraints such as x + k op y and call a specific callback.
         */
        bool recognizeSpecialIntensionCases;

        /**
         * If true, the parser recognizes special count constraints: atleast, atmost, exactly, among, exctalyVariable
         * and call a specific callback
         */
        bool recognizeSpecialCountCases;

        /**
         * If true, the parser recognizes special nvalues constraints: AllEqual, NotAllEqual, AllDiff
         * and call a specific callback
         */
        bool recognizeNValuesCases;

        /**
         * if true, sum are normalized: merge same variables, remove variables with coef equal to zero..
         */
        bool normalizeSum;

        XCSP3CoreCallbacksBase() {
            intensionUsingString = false;
            recognizeSpecialIntensionCases = true;
            recognizeSpecialCountCases = true;
            recognizeNValuesCases = true;
            normalizeSum = true;
        }

        /**
         * remove specific classes such as symmetryBreaking, clues...
         * @param cl
         */
        void addClassToDiscard(const std::string& cl) {
            classesToDiscard.push_back(cl);
        }

        bool discardedClasses(const std::string& classes) {
            if (classes == "")
                return false;

            for (std::string c : classesToDiscard)
                if (classes.find(c) != std::string::npos)
                    return true;
            return false;
        }

        // All these callbacks are called when the tag starts and when it ends.
        // This is not necessary to override them.

        /**
         * Start to parse a XCSP instance.
         * Related to tag <instance type="CSP/COP">
         * See http://xcsp.org/specifications/skeleton
         * @param type COP or CSP
         */
        virtual void beginInstance(InstanceType) = 0;

        /**
         * End of parsing
         * Related to tag </instance>
         * See http://xcsp.org/specifications/skeleton
         */
        virtual void endInstance() = 0;

        /**
         * Start to parse variables
         * Related to tag <variables>
         * See http://xcsp.org/specifications/skeleton
         */
        virtual void beginVariables() = 0;

        /**
         * The end of parsing variables
         * Related to tag </variables>
         * See http://xcsp.org/specifications/skeleton
         */
        virtual void endVariables() = 0;

        /**
         * Start to parse an array of variables
         * Related to tag <array>
         * See http://xcsp.org/specifications/arrays
         * Note that for each variable in the array a call is done to one of the functions #buildVariableInteger
         *
         * @param id the id (name) of the array variable
         */
        virtual void beginVariableArray(const std::string&) = 0; //beginArray

        /**
         * End of parsing an array of variables
         * Related to tag </array>
         * See http://xcsp.org/specifications/arrays
         */
        virtual void endVariableArray() = 0;

        /**
         * Start to parse constraints
         * Related to tag <constraints>
         * See http://xcsp.org/specifications/skeleton
         */
        virtual void beginConstraints() = 0;

        /**
         * The end of parsing constraints
         * Related to tag </constraints>
         * See http://xcsp.org/specifications/skeleton
         */
        virtual void endConstraints() = 0;

        /**
         * Start to parse a group of constraints
         * Related to tag <group>
         * See http://xcsp.org/specifications/groups
         * Note that for each constraint of the group a call is done to the related callback
         *
         * @param id the id (name) of the group
         */
        virtual void beginGroup(const std::string&) = 0;

        /**
         * Retrieve the  arguments of a group/slide  of constraints
         * Arguments are available juste before the first constraint is called
         * that is, after the beginGroup/beginSlide callback
         * @return
         */
        std::vector<std::vector<XVariable*>>* arguments() {
            return _arguments;
        }

        /**
         * The end of parsing group of constraints
         * Related to tag </group>
         * See http://xcsp.org/specifications/groups
         */
        virtual void endGroup() = 0;

        /**
         * Start to parse a block of constraints
         * Related to tag <block>
         * See http://xcsp.org/specifications/blocks
         * Note that for each constraint of the block a call is done to the related callback
         *
         * Note that if you want to discard some blocks, you need to call the function addClassToDiscard with the related class
         *
         * @param classes the classes related to the block symmetryBreaking, clues...
         */
        virtual void beginBlock(const std::string&) = 0;

        /**
         * The end of parsing a block of constraints
         * Related to tag </block>
         * See http://xcsp.org/specifications/blocks
         */
        virtual void endBlock() = 0;

        /**
         * Start to parse a slide constraint
         * Related to tag <slide>
         * See http://xcsp.org/specifications/slide
         * Note that for each constraint of the block a call is done to the related callback
         *
         * @param id the id (name) of the slide
         * @param circular is the slide circular?
         */
        virtual void beginSlide(const std::string&, bool) = 0;

        /**
         * The end of parsing a slide constraint
         * Related to tag </slide>
         * See http://xcsp.org/specifications/slide
         */
        virtual void endSlide() = 0;

        /**
         * Start to parse objectives
         * Related to tag <objectives>
         * See http://xcsp.org/specifications/objectives
         */
        virtual void beginObjectives() = 0;

        /**
         * The end of parsing objectives
         * Related to tag </objectives>
         * See http://xcsp.org/specifications/objectives
         */
        virtual void endObjectives() = 0;

        /**
         * The start of parsing annotations
         * Related to tag </annotations>
         */
        virtual void beginAnnotations() = 0;

        /**
         * The end of parsing annotations
         * Related to tag </annotations>
         */
        virtual void endAnnotations() = 0;

        //--------------------------------------------------------------------------------------
        // Build Variable. Must be implemented.
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to an integer variable with a range domain
         * See http://xcsp.org/specifications/integers
         *
         * Example: <var id="bar"> 0..6 </var>
         *
         * @param id the id (name) of the group
         * @param minValue the minimum value in the range
         * @param maxValue the maxnimum value in the range
         */
        virtual void buildVariableInteger(const std::string& id, int minValue, int maxValue) = 0;

        /**
         * The callback function related to an integer variable with a domain consisting in a sequence of integers
         * See http://xcsp.org/specifications/integers
         *
         * Example <var id="bar"> 1 3 5 10 </var>
         *
         * @param id the id (name) of the group
         * @param values the set of values in the domain
        */
        virtual void buildVariableInteger(const std::string& id, std::vector<int>& values) = 0;

        /**
         * All callbacks related to constraints.
         * Note that the variables related to a constraint are #XVariable instances. A XVariable contains an id and
         * the related domain.
         * (see XCSP3Variable.h)
         *
         */

        //--------------------------------------------------------------------------------------
        // Universal Constraints
        //--------------------------------------------------------------------------------------

        /**
         * The special constraint always true
         * Nothing to do
         * @param id
         * @param list
         */
        virtual void buildConstraintTrue(const std::string& id) = 0;

        /**
         * The special constraint always false
         * The problem is unsatisfiable
         * @param id
         * @param list
         */
        virtual void buildConstraintFalse(const std::string& id) = 0;

        //--------------------------------------------------------------------------------------
        // Basic constraints
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to an constraint in extension
         * See http://xcsp.org/specifications/extension
         *
         * Example:
         * <extension>
         *   <list> y1 y2 y3 y4 </list>
         *   <conflicts> (1,2,3,4)(3,1,3,4) </conflicts>
         * </extension>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param tuples the set of tuples in the constraint
         * @param support  support or conflicts?
         * @param hasStar is the tuples contain star values?
         */
        virtual void buildConstraintExtension(const std::string& id, std::vector<XVariable*> list, std::vector<std::vector<int>>& tuples, bool support, bool hasStar) = 0;

        /*
         * The callback function related to an constraint in extension
         * Note that this callback is related to an unary constraint
         * See http://xcsp.org/specifications/extension
         * Example:
         * <extension>
         *   <list> x </list>
         *   <conflicts> 2 6 </conflicts>
         * </extension>
         *
         * @param id the id (name) of the constraint
         * @param variable the variable
         * @param tuples the set of tuple (here just set of ints)
         * @param support  support or conflicts?
         * @param hasStar is the tuples contain star values?
         */
        virtual void buildConstraintExtension(const std::string& id, XVariable* variable, std::vector<int>& tuples, bool support, bool hasStar) = 0;

        /**
         * The callback function related to a constraint in extension where the set of tuples is exactly the same
         * than the previous one.
         * It is the case when a group of constraint contains an extension constraint.
         * This is useful to save space and share the set of tuples of all constraints.
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param support  support or conflicts?
         * @param hasStar is the tuples contain star values?
         */
        virtual void buildConstraintExtensionAs(const std::string& id, std::vector<XVariable*> list, bool support, bool hasStar) = 0;

        /**
         * The callback function related to a constraint in intension
         * Only called if intensionUsingString is set to true (otherwise the next function is called
         * See http://xcsp.org/specifications/intension
         * Example:
         * <intension> eq(add(x,y),z) </intension>
         * If you need a class that is able to manage expressions you can use the class Tree (see includes/XCS3Tree.h)
         * And an example is given in samples/testTree.cc
         * In such a case, set intensionUsingString to false and make a callback to the next function
         *
         * @param id the id (name) of the constraint
         * @param expr the expression
         */
        virtual void buildConstraintIntension(const std::string& id, std::string expr) = 0;

        /**
         * The callback function related to a constraint in intension
         * Only called if intensionUsingString is set to false (otherwise the previous function is called
         * See http://xcsp.org/specifications/intension
         * Example:
         * <intension> eq(add(x,y),z) </intension>
         *
         * @param id the id (name) of the constraint
         * @param tree the canonized form related to the tree
         */
        virtual void buildConstraintIntension(const std::string& id, Tree* tree) = 0;

        /**
         * If  #recognizeSpecialIntensionCases is enabled (this is the case by default)
         * intensional constraint of the form : x +-k op y is recognized.
         * If such a intensional constraint is recognized, a callback to this function is done and not to  #buildConstraintIntension
         *
         * @param id the id (name) of the constraint
         * @param op the order LE, LT...
         * @param x the variable
         * @param k the constant
         * @param y the other variable
         */
        virtual void buildConstraintPrimitive(const std::string& id, OrderType op, XVariable* x, int k, XVariable* y) = 0;

        /**
         * If  #recognizeSpecialIntensionCases is enabled (this is the case by default)
         * intensional constraint of the form : x op k  is recognized.
         * If such a intensional constraint is recognized, a callback to this function is done and not to  #buildConstraintIntension
         *
         * @param id the id (name) of the constraint
         * @param op the order LE or GE (EQ and NE are performed using #buildConstrantExtension)
         * @param x the variable
         * @param k the constant
         */
        virtual void buildConstraintPrimitive(const std::string& id, OrderType op, XVariable* x, int k) = 0;

        /**
         * If  #recognizeSpecialIntensionCases is enabled (this is the case by default)
         * intensional constraint of the form : x in/notin [min max] are recognized
         * If such a intensional constraint is recognized, a callback to this function is done and not to  #buildConstraintIntension
         *
         * @param id the id (name) of the constraint
         * @param x the variable
         * @param in true if x is in this interval
         * @param min the constant
         * @param max the constant
         *
         */
        virtual void buildConstraintPrimitive(const std::string& id, XVariable* x, bool in, int min, int max) = 0;

        /**
         * If  #recognizeSpecialIntensionCases is enabled (this is the case by default)
         * intensional constraint of the form : x*y=z are recognized
         * If such a intensional constraint is recognized, a callback to this function is done and not to  #buildConstraintIntension
         *
         * @param id the id (name) of the constraint
         * @param x,y,z  the variables
         */
        virtual void buildConstraintMult(const std::string& id, XVariable* x, XVariable* y, XVariable* z) = 0;

        //--------------------------------------------------------------------------------------
        // Language constraints
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to a regular constraint.
         * See http://xcsp.org/specifications/regular
         * Example:
         * <regular>
         *  <list> x1 x2 x3 x4 x5 x6 x7 </list>
         *  <transitions>
         *    (a,0,a)(a,1,b)(b,1,c)(c,0,d)(d,0,d)(d,1,e)(e,0,e)
         *  </transitions>
         *  <start> a </start>
         *  <final> e </final>
         * </regular>
         * XTransition is an object with 3 fields: from (std::string), val(int) and to(std::string)
         * Then, in the first transition of the example from=a, to=a and val=0
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param start the starting node
         * @param final the set of final nodes
         * @param transitions the set of transitions
         */
        virtual void buildConstraintRegular(const std::string& id, std::vector<XVariable*>& list, std::string start, std::vector<std::string>& final, std::vector<XTransition>& transitions) = 0;

        /**
         * The callback function related to a MDD constraint.
         * See http://xcsp.org/specifications/mdd
         *
         * Example:
         * <mdd>
         *   <list> x1 x2 x3 </list>
         *   <transitions>
         *     (r,0,n1)(r,1,n2)(r,2,n3)
         *     (n1,2,n4)(n2,2,n4)(n3,0,n5)
         *     (n4,0,t)(n5,0,t)
         *   </transitions>
         * </mdd>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param transitions the set of transitions
         */
        virtual void buildConstraintMDD(const std::string& id, std::vector<XVariable*>& list, std::vector<XTransition>& transitions) = 0;

        //--------------------------------------------------------------------------------------
        // Comparison constraints
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to a alldifferent constraint.
         * See http://xcsp.org/specifications/alldifferent
         *
         * Example:
         * <allDifferent>
         *   x1 x2 x3 x4 x5
         * </allDifferent>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         */
        virtual void buildConstraintAlldifferent(const std::string& id, std::vector<XVariable*>& list) = 0;

        /**
         * The callback function related to a alldifferent constraint with expression
         * See http://xcsp.org/specifications/alldifferent
         *
         * Example:
         * <allDifferent>
         *   add(q[0],0) add(q[1],1) add(q[2],2) add(q[3],3) add(q[4],4) add(q[5],5) add(q[6],6) add(q[7],7)
         * </allDifferent>
         *
         * @param id the id (name) of the constraint
         * @param list the trees of the constraint
         */
        virtual void buildConstraintAlldifferent(const std::string& id, std::vector<Tree*>& list) = 0;

        /**
         * The callback function related to a alldifferent with some excepted values constraint
         * See http://xcsp.org/specifications/alldifferent
         *
         * Example:
         * <allDifferent>
         *   x1 x2 x3 x4 x5
         *   <except>0</except>
         * </allDifferent>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param except the set of excepted values
         */
        virtual void buildConstraintAlldifferentExcept(const std::string& id, std::vector<XVariable*>& list, std::vector<int>& except) = 0;

        /**
         * The callback function related to a alldifferent  list constraint
         * See http://xcsp.org/specifications/alldifferent
         *
         * Example:
         * <allDifferent id="c1">
         *    <list> x1 x2 x3 x4 </list>
         *    <list> y1 y2 y3 y4 </list>
         * </allDifferent>
         *
         * @param id the id (name) of the constraint
         * @param lists the set of lists (not the scope, a variable may appear at different place!)
         */
        virtual void buildConstraintAlldifferentList(const std::string& id, std::vector<std::vector<XVariable*>>& lists) = 0;

        /**
         * The callback function related to a alldifferent  matrix constraint
         * See http://xcsp.org/specifications/alldifferent
         *
         * Example:
         * <allDifferent id="c1">
         *    <matrix>
         *     (x1,x2,x3,x4,x5)
         *     (y1,y2,y3,y4,y5)
         *     (z1,z2,z3,z4,z5)
         *    </matrix>
         * </allDifferent>
         *
         * @param id the id (name) of the constraint
         * @param matrix the matrix (not the scope, a variable may appear at different place!)
         */
        virtual void buildConstraintAlldifferentMatrix(const std::string& id, std::vector<std::vector<XVariable*>>& matrix) = 0;

        /**
         * The callback function related to a allequal constraint
         * See http://xcsp.org/specifications/allEqual
         *
         * Example:
         * <allEqual>
         *  x1 x2 x3 x4 x5
         * </allEqual>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         *
         */
        virtual void buildConstraintAllEqual(const std::string& id, std::vector<XVariable*>& list) = 0;

        /**
         * The callback function related to a not all equal constraint
         * This is a special case of nvalues constraint
         * Recognized if #recognizeNValuesCases is enabled (this is the case by default)
         * See http://xcsp.org/specifications/nValues
         *
         * Example:
         * <nValues id="c1">
         *   <list> x1 x2 x3 x4 </list>
         *   <condition> (gt,1) </condition>
         * </nValues>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         */
        virtual void buildConstraintNotAllEqual(const std::string& id, std::vector<XVariable*>& list) = 0;

        /**
         * The callback function related to an ordered constraint
         * See http://xcsp.org/specifications/ordered
         *
         * Ordered is LE, LT, GE, GT... See OrderType in XCSPConstants.h
         *
         * Example:
         * <ordered>
         *   <list> x1 x2 x3 x4 </list>
         *   <operator> lt </operator>
         * </ordered>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param order the order LT, LE...
         */
        virtual void buildConstraintOrdered(const std::string& id, std::vector<XVariable*>& list, OrderType order) = 0;

        /**
         * The callback function related to an ordered constraint
         * See http://xcsp.org/specifications/ordered
         *
         * Ordered is LE, LT, GE, GT... See OrderType in XCSPConstants.h
         *
         * Example:
         * <ordered>
         *   <list> x1 x2 x3 x4 </list>
         *   <operator> lt </operator>
         * </ordered>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param order the order LT, LE...
         */
        virtual void buildConstraintOrdered(const std::string& id, std::vector<XVariable*>& list, std::vector<int>& lengths, OrderType order) = 0;

        /**
         * The callback function related to an ordered list constraint (this is a lex constraint)
         * See http://xcsp.org/specifications/ordered
         *
         *
         * Example:
         * <ordered>
         *   <list> x1 x2 x3 x4 </list>
         *   <list> y1 y2 y3 y4 </list>
         *   <operator> lt </operator>
         * </ordered>
         *
         * @param id  the id (name) of the constraint
         * @param lists the set of lists (not the scope, a variable may appear at different place!)
         * @param order the order LT, LE...
         */
        virtual void buildConstraintLex(const std::string& id, std::vector<std::vector<XVariable*>>& lists, OrderType order) = 0;

        /**
        * The callback function related to an ordered matrix constraint
        * See http://xcsp.org/specifications/ordered
        *
        *
        * Example:
        * <ordered>
        *   <matrix>
        *     (z1,z2,z3)
        *     (z4,z5,z6)
        *     (z7,z8,z9)
        *   </matrix>
        *   <operator> lt </operator>
        * </ordered>
        *
        * @param id the id (name) of the constraint
        * @param matrix the matrix (not the scope, a variable may appear at different place!)
        * @param order the order LT, LE...
        */
        virtual void buildConstraintLexMatrix(const std::string& id, std::vector<std::vector<XVariable*>>& matrix, OrderType order) = 0;

        //--------------------------------------------------------------------------------------
        // Summing and counting constraints
        //--------------------------------------------------------------------------------------

        /**
        * The callback function related to an sum constraint
        * See http://xcsp.org/specifications/sum
        *
        * XCondition is an object with on OrderType (LE, LT...) an operandType (INTEGER, INTERVAL or VARIABLE)
        * depending the value of this field, either val (if operandType is INTEGER), min/max (INTERVAL) or var (VARIABLE)
        * is useful.
        * Example:
        * <sum>
        *   <list> x1 x2 x3 </list>
        *   <coeffs> 1 2 3 </coeffs>
        *   <condition> (gt,y) </condition>
        * </sum>
        *
        * @param id the id (name) of the constraint
        * @param list the scope of the constraint
        * @param coeffs the coefficients (here int)
        * @param cond the condition (See XCondition object)
        */
        virtual void buildConstraintSum(const std::string& id, std::vector<XVariable*>& list, std::vector<int>& coeffs, XCondition& cond) = 0;

        /**
         * The callback function related to an sum constraint with all coefs are equal to one
         * See http://xcsp.org/specifications/sum
         *
         * Example:
         * <sum>
         *   <list> x1 x2 x3 </list>
         *   <condition> (gt,y) </condition>
         * </sum>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param cond the condition (See XCondition object)
         */
        virtual void buildConstraintSum(const std::string& id, std::vector<XVariable*>& list, XCondition& cond) = 0;

        /**
         * The callback function related to a sum constraint with all coefs are variables
         * See http://xcsp.org/specifications/sum
         *
         * Example:
         * <sum>
         *   <list> x1 x2 x3 </list>
         *   <coeffs> y1 y2 y3 </coeffs>
         *   <condition> (gt,y) </condition>
         * </sum>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param coeffs the coefficients (here XVariable)
         * @param cond the condition (See XCondition object)
         */
        virtual void buildConstraintSum(const std::string& id, std::vector<XVariable*>& list, std::vector<XVariable*>& coeffs, XCondition& cond) = 0;

        /**
         * The callback function related to a sum constraint with trees in list
         *
         * Example:
         * <sum>
         *   <list>or(eq(x[5],0),eq(x[7],0)) or(eq(x[1],0),eq(x[2],0),eq(x[8],0)) or(eq(x[0],0),eq(x[3],0),eq(x[4],0),eq(x[6],0),eq(x[9],0))</list>
         *   <condition> (gt,y) </condition>
         * </sum>
         *
         * @param id the id (name) of the constraint
         * @param list the different trees
         * @param cond the condition (See XCondition object)
         */
        virtual void buildConstraintSum(const std::string& id, std::vector<Tree*>& trees, XCondition& cond) = 0;

        /**
         * The callback function related to a sum constraint with trees in list
         *
         * Example:
         * <sum>
         *   <list>or(eq(x[5],0),eq(x[7],0)) or(eq(x[1],0),eq(x[2],0),eq(x[8],0)) or(eq(x[0],0),eq(x[3],0),eq(x[4],0),eq(x[6],0),eq(x[9],0))</list>
         *   <coeffs>1 2 3</coeffs>
         *   <condition> (gt,y) </condition>
         * </sum>
         *
         * @param id the id (name) of the constraint
         * @param list the different trees
         * @param coefs the coefs.
         * @param cond the condition (See XCondition object)
         */
        virtual void buildConstraintSum(const std::string& id, std::vector<Tree*>& trees, std::vector<int>& coefs, XCondition& cond) = 0;

        /**
         * The callback function related to a atmost constraint
         * This is a special count constraint
         * This callback is called if #recognizeSpecialCountCases is enabled (this is the case by default)
         * See http://xcsp.org/specifications/count
         *
         *
         * Example:
         * <count id="c4">
         *   <list> y1 y2 y3 y4 </list>
         *   <values> 0 </values>
         *   <condition> (le,2) </condition>
         * </count>
         *
         * Here at most 2 variables from y1...y4 can have value 0
         *
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param value the value
         * @param k the maximum number of variables that can take the value
         */
        virtual void buildConstraintAtMost(const std::string& id, std::vector<XVariable*>& list, int value, int k) = 0;

        /**
         * The callback function related to a atleast constraint
         * This is a special count constraint
         * This callback is called if #recognizeSpecialCountCases is enabled
         * See http://xcsp.org/specifications/count
         *
         *
         * Example:
         * <count id="c3">
         *    <list> x1 x2 x3 x4 x5 </list>
         *    <values> 1 </values>
         *    <condition> (ge,3) </condition>
         * </count>
         *
         * Here at least 3 variables from x1...x5 must have value 1
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param value the value
         * @param k the minimum number of variables that can take the value
         */
        virtual void buildConstraintAtLeast(const std::string& id, std::vector<XVariable*>& list, int value, int k) = 0;

        /**
         * The callback function related to a exactly k  constraint
         * This is a special count constraint
         * This callback is called if #recognizeSpecialCountCases is enabled
         * See http://xcsp.org/specifications/count
         *
         *
         * Example:
         * <count id="c5">
         *    <list> z1 z2 z3  Z4</list>
         *    <values> 0 </values>
         *    <condition> (eq,2) </condition>
         * </count>
         * Here exactly 2 variables from z1...z4 must have value 0
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param value the value
         * @param k the exact number of variables that can take the value
         */
        virtual void buildConstraintExactlyK(const std::string& id, std::vector<XVariable*>& list, int value, int k) = 0;

        /**
         * The callback function related to a exactly k variable constraint
         * This is a special count constraint
         * This callback is called if #recognizeSpecialCountCases is enabled
         * See http://xcsp.org/specifications/count
         *
         *
         * Example:
         * <count id="c5">  <!-- exactly -->
         *    <list> z1 z2 z3  Z4</list>
         *    <values> 0 </values>
         *    <condition> (eq,z5) </condition>
         * </count>
         * Here exactly z5 variables from z1...z4 must have value 0
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param value the value
         * @param x the exact number of variables that can take the value (here it is a variable)
         */
        virtual void buildConstraintExactlyVariable(const std::string& id, std::vector<XVariable*>& list, int value, XVariable* x) = 0;

        /**
         * The callback function related to a among constraint
         * This is a special count constraint
         * This callback is called if #recognizeSpecialCountCases is enabled
         * See http://xcsp.org/specifications/count
         *
         *
         * Example:
         * <count id="c2">
         *   <list> w1 w2 w3 w4 </list>
         *   <values> 1 5 8 </values>
         *   <condition> (eq,k2) </condition>
         * </count>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param value the value
         * @param k
         */
        virtual void buildConstraintAmong(const std::string& id, std::vector<XVariable*>& list, std::vector<int>& values, int k) = 0;

        /**
         * The callback function related to a count constraint with integer values
         * See http://xcsp.org/specifications/count
         * Example:
         * <count id="c1">
         *     <list> v1 v2 v3 v4 </list>
         *     <values> 2 4 </values>
         *     <condition> (ne,k1) </condition>
         * </count>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param value the set of  values (here set of ints)
         * @param k the  number of variables
         * @param xc the condition (see #XCondition)
         */
        virtual void buildConstraintCount(const std::string& id, std::vector<XVariable*>& list, std::vector<int>& values, XCondition& xc) = 0;

        /**
         * The callback function related to a count constraint with integer variables
         * See http://xcsp.org/specifications/count
         * Example:
         * <count id="c1">
         *     <list> v1 v2 v3 v4 </list>
         *     <values> x1 x2 </values>
         *     <condition> (ne,k1) </condition>
         * </count>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param value the set of  values (here set of variables)
         * @param k the  number of variables
         * @param xc the condition (see #XCondition)
         */
        virtual void buildConstraintCount(const std::string& id, std::vector<XVariable*>& list, std::vector<XVariable*>& values, XCondition& xc) = 0;

        /**
         * The callback function related to a nValues constraint with exception
         * See http://xcsp.org/specifications/nValues
         * Example:
         * <nValues id="c3">
         *   <list> z1 z2 z3 z4 </list>
         *    <except> 0 </except>
         *    <condition> (eq,2) </condition>
         * </nValues>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param except the set of excepted values
         * @param xc the condition (see #XCondition)
         */
        virtual void buildConstraintNValues(const std::string& id, std::vector<XVariable*>& list, std::vector<int>& except, XCondition& xc) = 0;

        /**
         * The callback function related to a nValues constraint with exception
         * See http://xcsp.org/specifications/nValues
         * Example:
         * <nValues id="c3">
         *   <list> z1 z2 z3 z4 </list>
         *   <condition> (eq,2) </condition>
         * </nValues>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param xc the condition (see #XCondition)
         */
        virtual void buildConstraintNValues(const std::string& id, std::vector<XVariable*>& list, XCondition& xc) = 0;

        /**
         * The callback function related to a cardinality constraint with int values and int occurs
         * See http://xcsp.org/specifications/cardinality
         *
         * Example:
         * <cardinality>
         *   <list> x1 x2 x3 x4 </list>
         *   <values> 2 5 10 </values>
         *   <occurs> 1 2 3 </occurs>
         * </cardinality>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param values the set of values (here int)
         * @param occurs the number of occurences (here int)
         * @param closed is the constraint is closed
         */
        virtual void buildConstraintCardinality(const std::string& id, std::vector<XVariable*>& list, std::vector<int> values, std::vector<int>& occurs, bool closed) = 0;

        //
        /**
         * The callback function related to a cardinality constraint with int values and variable occurs
         * See http://xcsp.org/specifications/cardinality
         *
         * Example:
         * <cardinality>
         *   <list> x1 x2 x3 x4 </list>
         *   <values> 0 1 2 3 </values>
         *   <occurs> z0 z1 z2 z3 </occurs>
         * </cardinality>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param values the set of values (here int)
         * @param occurs the number of occurences (here variables)
         * @param closed is the constraint is closed
         */
        virtual void buildConstraintCardinality(const std::string& id, std::vector<XVariable*>& list, std::vector<int> values, std::vector<XVariable*>& occurs, bool closed) = 0;

        //
        /**
         * The callback function related to a cardinality constraint with int values and interval occurs
         * See http://xcsp.org/specifications/cardinality
         *
         * Example:
         * <cardinality>
         *   <list> x1 x2 x3 x4 </list>
         *   <values> 2 5 10 </values>
         *   <occurs> 0..1 1..3 2..3 </occurs>
         * </cardinality>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param values the set of values (here int)
         * @param occurs the number of occurences (here intervals)
         * @param closed is the constraint is closed
         */
        virtual void buildConstraintCardinality(const std::string& id, std::vector<XVariable*>& list, std::vector<int> values, std::vector<XInterval>& occurs, bool closed) = 0;

        /**
         * The callback function related to a cardinality constraint with variable values and int occurs
         * See http://xcsp.org/specifications/cardinality
         *
         * Example:
         * <cardinality>
         *   <list> x1 x2 x3 x4 </list>
         *   <values> z1 z2 z3 </values>
         *   <occurs> 1 2 3 </occurs>
         * </cardinality>
         *
         * @param id the id (name) of the constraint
         * @param list the list of the constraint (not the scope...)
         * @param values the set of values (here variable)
         * @param occurs the number of occurences (here int)
         * @param closed is the constraint is closed
         */
        virtual void buildConstraintCardinality(const std::string& id, std::vector<XVariable*>& list, std::vector<XVariable*> values, std::vector<int>& occurs, bool closed) = 0;

        /**
         * The callback function related to a cardinality constraint with variable values and variable occurs
         * See http://xcsp.org/specifications/cardinality
         *
         * Example:
         * <cardinality>
         *   <list> x1 x2 x3 x4 </list>
         *   <values> z1 z2 z3 </values>
         *   <occurs> y1 y2 y3 </occurs>
         * </cardinality>
         *
         * @param id the id (name) of the constraint
         * @param list the list of the constraint (not the scope)
         * @param values the set of values (here variables)
         * @param occurs the number of occurences (here variables)
         * @param closed is the constraint is closed
         */
        virtual void buildConstraintCardinality(const std::string& id, std::vector<XVariable*>& list, std::vector<XVariable*> values, std::vector<XVariable*>& occurs, bool closed) = 0;

        /**
         * The callback function related to a cardinality constraint with variable values and interval occurs
         * See http://xcsp.org/specifications/cardinality
         *
         * Example:
         * <cardinality>
         *   <list> x1 x2 x3 x4 </list>
         *   <values> z1 z2 z3 </values>
         *   <occurs> 1..2 3..5 2..4 </occurs>
         * </cardinality>
         *
         * @param id the id (name) of the constraint
         * @param list the list of the constraint (not the scope)
         * @param values the set of values (here variables)
         * @param occurs the number of occurences (here intervals)
         * @param closed is the constraint is closed
         */
        virtual void buildConstraintCardinality(const std::string& id, std::vector<XVariable*>& list, std::vector<XVariable*> values, std::vector<XInterval>& occurs, bool closed) = 0;
        //--------------------------------------------------------------------------------------
        // Connection constraints
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to a minimum constraint
         * See http://xcsp.org/specifications/minimum
         *
         * Example:
         * <minimum>
         *    <list> x1 x2 x3 x4 </list>
         *    <condition> (eq,y) </condition>
         * </minimum>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param xc the condition (see #XCondition)
         */
        virtual void buildConstraintMinimum(const std::string& id, std::vector<XVariable*>& list, XCondition& xc) = 0;

        /**
         * The callback function related to a minimum constraint
         * See http://xcsp.org/specifications/minimum
         *
         * Example:
         * <minimum>
         *    <list> x1 x2 x3 x4 </list>
         *    <condition> (eq,y) </condition>
         * </minimum>
         *
         * @param id the id (name) of the constraint
         * @param list set of expression
         * @param xc the condition (see #XCondition)
         */
        virtual void buildConstraintMinimum(const std::string& id, std::vector<Tree*>& list, XCondition& xc) = 0;

        /**
         * The callback function related to a minimum constraint (arg_min)
         * See http://xcsp.org/specifications/minimum
         *
         * Example:
         * <minimum>
         *    <list> x1 x2 x3 x4 </list>
         *    <index  rank="any"> z1 </index>
         *    <condition> (eq,3) </condition>
         * </minimum>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param index the index variable
         * @param startIndex 0 or something else ?
         * @param rank ANY, ALL...
         * @param xc the condition (see #XCondition)
         */
        virtual void buildConstraintMinimum(const std::string& id, std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType rank, XCondition& xc) = 0;

        /**
         * The callback function related to a maximum constraint
         * See http://xcsp.org/specifications/maximum
         *
         * Example:
         * <maximum>
         *    <list> x1 x2 x3 x4 </list>
         *    <condition> (ge,2) </condition>
         * </maximum>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param xc the condition (see #XCondition)
         */
        virtual void buildConstraintMaximum(const std::string& id, std::vector<XVariable*>& list, XCondition& xc) = 0;

        /**
                * The callback function related to a maximum constraint
                * See http://xcsp.org/specifications/maximum
                *
                * Example:
                * <maximum>
                *    <list> add(x1,2) x2 x3 x4 </list>
                *    <condition> (ge,2) </condition>
                * </maximum>
                *
                * @param id the id (name) of the constraint
                * @param list the expressions of the constraint
                * @param xc the condition (see #XCondition)
                */
        virtual void buildConstraintMaximum(const std::string& id, std::vector<Tree*>& list, XCondition& xc) = 0;

        /**
         * The callback function related to a maximum constraint (arg_max)
         * See http://xcsp.org/specifications/maximum
         *
         * Example:
         * <maximum>
         *    <list> x1 x2 x3 x4 </list>
         *    <index  rank="any"> z1 </index>
         *    <condition> (eq,3) </condition>
         * </maximum>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param index the index variable
         * @param startIndex 0 or something else ?
         * @param rank ANY, ALL...
         * @param xc the condition (see #XCondition)
         */
        virtual void buildConstraintMaximum(const std::string& id, std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType rank, XCondition& xc) = 0;

        /**
         * The callback function related to a element constraint with int value
         * See http://xcsp.org/specifications/element
         *
         * Example:
         * <element>
         *    <list> y[] </list>
         *    <value> 2 </value>
         * </element>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param value the value (here an int)
         */
        virtual void buildConstraintElement(const std::string& id, std::vector<XVariable*>& list, int value) = 0;

        /**
         * The callback function related to a element constraint matrix
         * See http://xcsp.org/specifications/element
         *
         * Example:  matrix[t][v] = z
         * <element>
         *    <matrix> (x1 x2 x3)(y1 y2 y3) </matrix>
         *    <index> t v </index>
         *    <value> z </value>
         * </element>
         *
         * @param id the id (name) of the constraint
         * @param matrix the matrix (of variables)
         * @param rowIndex the row index
         * @param colIndex the col index
         * @param startRowIndex the start index for rows
         * @param startColIndex the start index for cols
         * @param value the value (here a variable)
         */
        virtual void buildConstraintElement(const std::string& id, std::vector<std::vector<XVariable*>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, XVariable* value) = 0;

        /**
        * The callback function related to a element constraint matrix
        * See http://xcsp.org/specifications/element
        *
        * Example:  matrix[t][v] = 2
        * <element>
        *    <matrix> (x1 x2 x3)(y1 y2 y3) </matrix>
        *    <index> t v </index>
        *    <value> z </value>
        * </element>
        *
        * @param id the id (name) of the constraint
        * @param matrix the matrix (of variables)
        * @param rowIndex the row index
        * @param colIndex the col index
        * @param startRowIndex the start index for rows
        * @param startColIndex the start index for cols
        * @param value the value (here an int)
        */
        virtual void buildConstraintElement(const std::string& id, std::vector<std::vector<XVariable*>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, int value) = 0;

        /**
        * The callback function related to a element constraint matrix
        * See http://xcsp.org/specifications/element
        *
        * Example:  matrix[t][v] = z
        * <element>
        *    <matrix> (1 2 3)(4 5 6) </matrix>
        *    <index> t v </index>
        *    <value> z </value>
        * </element>
        *
        * @param id the id (name) of the constraint
        * @param matrix the matrix (here a matrix of int)
        * @param rowIndex the row index
        * @param colIndex the col index
        * @param startRowIndex the start index for rows
        * @param startColIndex the start index for cols
        * @param value the value (here a variable)
        */

        virtual void buildConstraintElement(const std::string& id, std::vector<std::vector<int>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, XVariable* value) = 0;

        /**
         * The callback function related to a element constraint with variable value
         * See http://xcsp.org/specifications/element
         *
         * Example:
         * <element>
         *    <list> y[] </list>
         *    <value> z </value>
         * </element>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param value the value (here a variable)
         */
        virtual void buildConstraintElement(const std::string& id, std::vector<XVariable*>& list, XVariable* value) = 0;

        /**
         * The callback function related to a element constraint with variable index and  int value
         * See http://xcsp.org/specifications/element
         *
         * Example:
         * <element>
         *    <list> y[] </list>
         *    <index> i </index>
         *    <value> 2 </value>
         * </element>
         *
         * @param id the id (name) of the constraint
         * @param list the list of the constraint (not necessary the scope)
         * @param index the index variable
         * @param startIndex 0 or something else ?
         * @param rank ANY, ALL...
         * @param value the value (here an int)
         */
        virtual void buildConstraintElement(const std::string& id, std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType rank, int value) = 0;

        /**
         * The callback function related to a element constraint with variable index and variable value
         * See http://xcsp.org/specifications/element
         *
         * Example:
         * <element>
         *    <list> y[] </list>
         *    <index> i </index>
         *    <value> z </value>
         * </element>
         *
         * @param id the id (name) of the constraint
         * @param list the list of the constraint (not necessary the scope)
         * @param index the index variable
         * @param startIndex 0 or something else ?
         * @param rank ANY, ALL...
         * @param value the value (here a variable)
         */
        virtual void buildConstraintElement(const std::string& id, std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType rank, XVariable* value) = 0;

        /**
         * The callback function related to a element constraint with int list variable index and variable value
         * See http://xcsp.org/specifications/element
         *
         * Example:
         * <element>
         *    <list> 1 2 3 4  </list>
         *    <index> i </index>
         *    <value> z </value>
         * </element>
         *
         * @param id the id (name) of the constraint
         * @param list the list of int
         * @param index the index variable
         * @param startIndex 0 or something else ?
         * @param rank ANY, ALL...
         * @param value the value (here a variable)
         */
        virtual void buildConstraintElement(const std::string& id, std::vector<int>& list, int startIndex, XVariable* index, RankType rank, XVariable* value) = 0;

        /**
         * The callback function related to a channel constraint
         * See http://xcsp.org/specifications/channel
         *
         * Example:
         * <channel>
         *    <list> z1 z2 z3 z4 z5 </list>
         * </channel>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         */
        virtual void buildConstraintChannel(const std::string& id, std::vector<XVariable*>& list, int startIndex) = 0;

        /**
         * The callback function related to a channel constraint
         * See http://xcsp.org/specifications/channel
         *
         * Example:
         * <channel>
         *     <list> x1 x2 x3 x4 </list>
         *     <list> y1 y2 y3 y4 </list>
         * </channel>
         *
         * The size of the array {@code list1} must be less than or equal to the size of {@code list2}.
         *
         * If list1.size() == list2.size() then list1[i] = j <=> list2[j] = i
         * If list1.size() <  list2.size() then list1[i] = j  => list2[j] = i
         *
         * @param id the id (name) of the constraint
         * @param list1 the first list
         * @param startIndex1 the starting index for list1
         * @param list2 the second list
         * @param startIndex2 the starting index for list2
         *
         */
        virtual void buildConstraintChannel(const std::string& id, std::vector<XVariable*>& list1, int startIndex1, std::vector<XVariable*>& list2, int startIndex2) = 0;

        /**
         * The callback function related to a channel constraint with a value
         * See http://xcsp.org/specifications/channel
         *
         * Example:
         * <channel>
         * <list> z1 z2 z3 z4 z5 </list>
         * <value> v </value>
         * </channel>
         *
         * @param id the id (name) of the constraint
         * @param list the list of the constraint not necessary the scope)
         * @param startIndex the starting index for list
         * @param value the vaule
         */
        virtual void buildConstraintChannel(const std::string& id, std::vector<XVariable*>& list, int startIndex, XVariable* value) = 0;

        //--------------------------------------------------------------------------------------
        // packing and schedulling constraints
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to a strectch constraint with values and widths
         * See http://xcsp.org/specifications/stretch
         *
         * Example:
         * <stretch>
         *   <list> x1 x2 x3 x4 x5 x6 x7 </list>
         *   <values> 1 2 3 0 </values>
         *   <widths> 1..3 1..3 2..3 2..4 </widths>
         * </stretch>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param values thelist of values
         * @param widths the list of intervals for widths
         */
        virtual void buildConstraintStretch(const std::string& id, std::vector<XVariable*>& list, std::vector<int>& values, std::vector<XInterval>& widths) = 0;

        /**
         * The callback function related to a strectch constraint with values, widths and patterns
         * See http://xcsp.org/specifications/stretch
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param values thelist of values
         * @param widths the list of intervals for widths
         * @param patterns
         *
         */
        virtual void buildConstraintStretch(const std::string& id, std::vector<XVariable*>& list, std::vector<int>& values, std::vector<XInterval>& widths, std::vector<std::vector<int>>& patterns) = 0;

        /**
         * The callback function related to a no overlap constraint with variable origins and int lenghts
         * See http://xcsp.org/specifications/noOverlap
         *
         * Example:
         * <noOverlap>
         *    <origins> x1 x2 x3 </origins>
         *    <lengths> l1 l2 l3 </lengths>
         * </noOverlap>
         *
         * @param id  the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here int)
         * @param zeroIgnored are zero ignored?
         */
        virtual void buildConstraintNoOverlap(const std::string& id, std::vector<XVariable*>& origins, std::vector<int>& lengths, bool zeroIgnored) = 0;

        /**
         * The callback function related to a no overlap constraint with variable origins and variable lenghts
         * See http://xcsp.org/specifications/noOverlap
         *
         * Example:
         * <noOverlap>
         *    <origins> x1 x2 x3 </origins>
         *    <lengths> z1 z2 z3 </lengths>
         * </noOverlap>
         *
         * @param id  the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here variables)
         * @param zeroIgnored are zero ignored?
         */
        virtual void buildConstraintNoOverlap(const std::string& id, std::vector<XVariable*>& origins, std::vector<XVariable*>& lengths, bool zeroIgnored) = 0;

        /**
         * The callback function related to a no overlap constraint with variable origins and 3 dimensional int  lenghts
         * See http://xcsp.org/specifications/noOverlap
         *
         * Example:
         * <noOverlap>
         *    <origins> (x1,y1,z1)(x2,y2,z2)(x3,y3,z3)(x4,y4,z4) </origins>
         *    <lengths> (2,4,1)(4,2,3)(5,1,2)(3,3,2) </lengths>
         * </noOverlap>
         *
         * @param id  the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here std::vector of int)
         * @param zeroIgnored are zero ignored?
         */
        virtual void buildConstraintNoOverlap(const std::string& id, std::vector<std::vector<XVariable*>>& origins, std::vector<std::vector<int>>& lengths, bool zeroIgnored) = 0;

        /**
         * The callback function related to a no overlap constraint with variable origins and 3 dimensional variable  lenghts
         * See http://xcsp.org/specifications/noOverlap
         *
         * Example:
         * <noOverlap>
         *    <origins> (x1,y1,z1)(x2,y2,z2)(x3,y3,z3)(x4,y4,z4) </origins>
         *    <lengths> (a,b,c)(d,e,f)(g,h,i)(l,m,n) </lengths>
         * </noOverlap>
         *
         * @param id  the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here std::vector of variables)
         * @param zeroIgnored are zero ignored?
         */
        virtual void buildConstraintNoOverlap(const std::string& id, std::vector<std::vector<XVariable*>>& origins, std::vector<std::vector<XVariable*>>& lengths, bool zeroIgnored) = 0;

        /**
         * The callback function related to a cumulative constraint with variable origins, int lengths and int heights
         * See http://xcsp.org/specifications/cumulative
         *
         * Example:
         * <cumulative>
         *     <origins> s1 s2 s3 s4 </origins>
         *     <lengths> 1 2 3 4 </lengths>
         *     <heights> 3 4 5 6 </heights>
         *     <condition> (le,4) </condition>
         * </cumulative>
         *
         * @param id the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here ints)
         * @param heights the std::vector of heights (here ints)
         * @param xc the condition (see XCondition)
         */
        virtual void buildConstraintCumulative(const std::string& id, std::vector<XVariable*>& origins, std::vector<int>& lengths, std::vector<int>& heights, XCondition& xc) = 0;

        /**
         * The callback function related to a cumulative constraint with variable origin, int lengths and variable heights
         * See http://xcsp.org/specifications/cumulative
         *
         * Example:
         * <cumulative>
         *     <origins> s1 s2 s3 s4 </origins>
         *     <lengths> 1 2 3 4 </lengths>
         *     <heights> h1 h2 h3 h4 </heights>
         *     <condition> (le,4) </condition>
         * </cumulative>
         *
         * @param id the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here ints)
         * @param heights the std::vector of heights (here variables)
         * @param xc the condition (see XCondition)
         */
        virtual void buildConstraintCumulative(const std::string& id, std::vector<XVariable*>& origins, std::vector<int>& lengths, std::vector<XVariable*>& varHeights, XCondition& xc) = 0;

        /**
         * The callback function related to a cumulative constraint with variable origin, variable lengths and int heights
         * See http://xcsp.org/specifications/cumulative
         *
         * Example:
         * <cumulative>
         *     <origins> s1 s2 s3 s4 </origins>
         *     <lengths> l1 l2 l3 l4 </lengths>
         *     <heights> 1 2 3 4 </heights>
         *     <condition> (le,4) </condition>
         * </cumulative>
         *
         * @param id the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here variables)
         * @param heights the std::vector of heights (here ints)
         * @param xc the condition (see XCondition)
         */
        virtual void buildConstraintCumulative(const std::string& id, std::vector<XVariable*>& origins, std::vector<XVariable*>& lengths, std::vector<int>& heights, XCondition& xc) = 0;

        /**
         * The callback function related to a cumulative constraint with variable origin, variable lengths and variable heights
         * See http://xcsp.org/specifications/cumulative
         *
         * Example:
         * <cumulative>
         *     <origins> s1 s2 s3 s4 </origins>
         *     <lengths> l1 l2 l3 l4 </lengths>
         *     <heights> h1 h2 h3 h4 </heights>
         *     <condition> (le,4) </condition>
         * </cumulative>
         *
         * @param id the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here variables)
         * @param heights the std::vector of heights (here variables)
         * @param xc the condition (see XCondition)
         */
        virtual void
        buildConstraintCumulative(const std::string& id, std::vector<XVariable*>& origins, std::vector<XVariable*>& lengths, std::vector<XVariable*>& heights, XCondition& xc) = 0;

        /**
         * The callback function related to a cumulative constraint with variable origin, int lengths and int heights and variable ends
         * See http://xcsp.org/specifications/cumulative
         *
         * Example:
         * <cumulative>
         *     <origins> s1 s2 s3 s4 </origins>
         *     <lengths> 1 2 3 4 </lengths>
         *     <heights> 1 2 3 4 </heights>
         *     <end> e1 e2 e3 e4 </end>
         *     <condition> (le,4) </condition>
         * </cumulative>
         *
         * @param id the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here ints)
         * @param heights the std::vector of heights (here ints)
         * @param ends the std::vector of ends (here variables)
         * @param xc the condition (see XCondition)
         */
        virtual void buildConstraintCumulative(const std::string& id, std::vector<XVariable*>& origins, std::vector<int>& lengths, std::vector<int>& heights, std::vector<XVariable*>& ends,
                                               XCondition& xc) = 0;

        /**
         * The callback function related to a cumulative constraint with variable origin, int lengths and variable heights and variable ends
         * See http://xcsp.org/specifications/cumulative
         *
         * Example:
         * <cumulative>
         *     <origins> s1 s2 s3 s4 </origins>
         *     <lengths> 1 2 3 4 </lengths>
         *     <heights> h1 h2 h3 h4 </heights>
         *     <end> e1 e2 e3 e4 </end>
         *     <condition> (le,4) </condition>
         * </cumulative>
         *
         * @param id the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here ints)
         * @param heights the std::vector of heights (here variables)
         * @param ends the std::vector of ends (here variables)
         * @param xc the condition (see XCondition)
         */
        virtual void
        buildConstraintCumulative(const std::string& id, std::vector<XVariable*>& origins, std::vector<int>& lengths, std::vector<XVariable*>& varHeights, std::vector<XVariable*>& ends,
                                  XCondition& xc) = 0;

        /**
         * The callback function related to a cumulative constraint with variable origin, variable lengths and int heights and variable ends
         * See http://xcsp.org/specifications/cumulative
         *
         * Example:
         * <cumulative>
         *     <origins> s1 s2 s3 s4 </origins>
         *     <lengths> l1 l2 l3 l4 </lengths>
         *     <heights> 1 2 3 4 </heights>
         *     <end> e1 e2 e3 e4 </end>
         *     <condition> (le,4) </condition>
         * </cumulative>
         *
         * @param id the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here variables)
         * @param heights the std::vector of heights (here ints)
         * @param ends the std::vector of ends (here variables)
         * @param xc the condition (see XCondition)
         */
        virtual void
        buildConstraintCumulative(const std::string& id, std::vector<XVariable*>& origins, std::vector<XVariable*>& lengths, std::vector<int>& heights, std::vector<XVariable*>& ends,
                                  XCondition& xc) = 0;

        /**
         * The callback function related to a cumulative constraint with variable origin, variable lengths and variable heights and variable ends
         * See http://xcsp.org/specifications/cumulative
         *
         * Example:
         * <cumulative>
         *     <origins> s1 s2 s3 s4 </origins>
         *     <lengths> l1 l2 l3 l4 </lengths>
         *     <heights> h1 h2 h3 h4 </heights>
         *     <end> e1 e2 e3 e4 </end>
         *     <condition> (le,4) </condition>
         * </cumulative>
         *
         * @param id the id (name) of the constraint
         * @param origins the std::vector of origins
         * @param lengths the std::vector of lenghts (here variables)
         * @param heights the std::vector of heights (here variables)
         * @param ends the std::vector of ends (here variables)
         * @param xc the condition (see XCondition)
         */
        virtual void
        buildConstraintCumulative(const std::string& id, std::vector<XVariable*>& origins, std::vector<XVariable*>& lengths, std::vector<XVariable*>& heights,
                                  std::vector<XVariable*>& ends, XCondition& xc) = 0;

        //--------------------------------------------------------------------------------------
        // instantiation constraints
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to an instantiation  constraint
         * See http://xcsp.org/specifications/instantiation
         *
         * Example:
         * <instantiation>
         *   <list> x y z </list>
         *   <values> 12 4 30 </values>
         * </instantiation>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param values the value for each variable
         */
        virtual void buildConstraintInstantiation(const std::string& id, std::vector<XVariable*>& list, std::vector<int>& values) = 0;

        //--------------------------------------------------------------------------------------
        // Clause constraints
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to an clause  constraint
         *
         * Example:
         * <clause>
         *   <list> x not(y) z </list>
         * </clause>
         *
         * @param id the id (name) of the constraint
         * @param positive the positive variables in the clause
         * @param negative the negative variables in the clause
         */
        virtual void buildConstraintClause(const std::string& id, std::vector<XVariable*>& positive, std::vector<XVariable*>& negative) = 0;

        //--------------------------------------------------------------------------------------
        // Graph constraints
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to circuit   constraint
         * See http://xcsp.org/specifications/circuit
         *
         * Example:
         * <circuit>
         *   <list> x y z </list>
         * </circuit>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param startIndex the start index for the list
         */
        virtual void buildConstraintCircuit(const std::string& id, std::vector<XVariable*>& list, int startIndex) = 0;

        /**
         * The callback function related to circuit   constraint with defined int size
         * See http://xcsp.org/specifications/circuit
         *
         * Example:
         * <circuit>
         *   <list> x y z </list>
         *   <size> 4 </size>
         * </circuit>
         *
         * @param id the id (name) of the constraint
         * @param list the scope of the constraint
         * @param startIndex the start index for the list
         * @param size the size of the circuit (here an int)
         */
        virtual void buildConstraintCircuit(const std::string& id, std::vector<XVariable*>& list, int startIndex, int size) = 0;

        /**
         * The callback function related to circuit   constraint with defined variable size
         * See http://xcsp.org/specifications/circuit
         *
         * Example:
         * <circuit>
         *   <list> x y z </list>
         *   <size> s </size>
         * </circuit>
         *
         * @param id the id (name) of the constraint
         * @param list the list of variables (not necessary the scope)
         * @param startIndex the start index for the list
         * @param size the size of the circuit (here an variable)
         */
        virtual void buildConstraintCircuit(const std::string& id, std::vector<XVariable*>& list, int startIndex, XVariable* size) = 0;

        //--------------------------------------------------------------------------------------
        // Objectives
        //--------------------------------------------------------------------------------------

        /**
         * The callback function related to an objective minimize an expression
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *    <minimize> add(x,mul(y,2)) </minimize>
         * </objectives>
         *
         * @param expr the expression
         */
        virtual void buildObjectiveMinimizeExpression(std::string expr) = 0;

        /**
         * The callback function related to an objective maximize an expression
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *    <maximize> add(x,2) </maximize>
         * </objectives>
         *
         * @param expr the expression
         */
        virtual void buildObjectiveMaximizeExpression(std::string expr) = 0;

        /**
         * The callback function related to an objective minimize a variable
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *    <minimize> x </minimize>
         * </objectives>
         *
         * @param x the variable
         */
        virtual void buildObjectiveMinimizeVariable(XVariable* x) = 0;

        /**
         * The callback function related to an objective maximize a variable
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *    <maximize> x </maximize>
         * </objectives>
         *
         * @param x the variable
         */
        virtual void buildObjectiveMaximizeVariable(XVariable* x) = 0;

        /**
         * The callback function related to an objective minimize a sum/product
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *   <minimize type="sum">
         *     <list> x1 x2 x3 x4 x5 </list>
         *     <coeffs> 2 4 1 4 8 </coeffs>
         *   </minimize>
         * <objectives>
         *
         * @param type SUM, PRODUCT...
         * @param list the scope
         * @param coefs the std::vector of coefficients
         */
        virtual void buildObjectiveMinimize(ExpressionObjective type, std::vector<XVariable*>& list, std::vector<int>& coefs) = 0;

        /**
         * The callback function related to an objective maximize a sum/product
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *   <maximize type="sum">
         *     <list> x1 x2 x3 x4 x5 </list>
         *     <coeffs> 2 4 1 4 8 </coeffs>
         *   </maximize>
         * <objectives>
         *
         * @param type SUM, PRODUCT...
         * @param list the scope
         * @param coefs the std::vector of coefficients
         */
        virtual void buildObjectiveMaximize(ExpressionObjective type, std::vector<XVariable*>& list, std::vector<int>& coefs) = 0;

        /**
         * The callback function related to an objective minimize a sum/product with coefs = 1
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *   <minimize type="sum">
         *     <list> x1 x2 x3 x4 x5 </list>
         *   </minimize>
         * <objectives>
         *
         * @param type SUM, PRODUCT...
         * @param list the scope
         */
        virtual void buildObjectiveMinimize(ExpressionObjective type, std::vector<XVariable*>& list) = 0;

        /**
         * The callback function related to an objective maximize a sum/product with coefs = 1
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *   <maximize type="sum">
         *     <list> x1 x2 x3 x4 x5 </list>
         *   </maximize>
         * <objectives>
         *
         * @param type SUM, PRODUCT...
         * @param list the scope
         */
        virtual void buildObjectiveMaximize(ExpressionObjective type, std::vector<XVariable*>& list) = 0;

        /**
         * The callback function related to an objective minimize a sum/product
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *   <minimize type="sum">
         *     <list> ne(s[2],2) ne(s[3],3) ... </list>
         *     <coeffs> 2 4 ... </coeffs>
         *   </minimize>
         * <objectives>
         *
         * @param type SUM, PRODUCT...
         * @param trees the expressions
         * @param coefs the std::vector of coefficients
         */
        virtual void buildObjectiveMinimize(ExpressionObjective type, std::vector<Tree*>& trees, std::vector<int>& coefs) = 0;

        /**
         * The callback function related to an objective maximize a sum/product
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *   <maximize type="sum">
         *     <list> ne(s[2],2) ne(s[3],3) ... </list>
         *     <coeffs> 2 4 ... </coeffs>
         *   </maximize>
         * <objectives>
         *
         * @param type SUM, PRODUCT...
         * @param list the scope
         * @param coefs the std::vector of coefficients
         */
        virtual void buildObjectiveMaximize(ExpressionObjective type, std::vector<Tree*>& trees, std::vector<int>& coefs) = 0;

        /**
         * The callback function related to an objective minimize a sum/product with coefs = 1
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *   <minimize type="sum">
         *     <list> ne(s[2],2) ne(s[3],3) ... </list>
         *   </minimize>
         * <objectives>
         *
         * @param type SUM, PRODUCT...
         * @param list the scope
         */
        virtual void buildObjectiveMinimize(ExpressionObjective type, std::vector<Tree*>& trees) = 0;

        /**
         * The callback function related to an objective maximize a sum/product with coefs = 1
         * See http://xcsp.org/specifications/objectives
         *
         * Example:
         * <objectives>
         *   <maximize type="sum">
         *     <list> ne(s[2],2) ne(s[3],3) ... </list>
         *   </maximize>
         * <objectives>
         *
         * @param type SUM, PRODUCT...
         * @param list the scope
         */
        virtual void buildObjectiveMaximize(ExpressionObjective type, std::vector<Tree*>& trees) = 0;

        /**
         * The callback function related to annotations.
         * It provides the set of decision variables related to the problem.
         * @param list
         */

        virtual void buildAnnotationDecision(std::vector<XVariable*>& list) = 0;
    };

} // namespace XCSP3Core

#endif //COSOCO_XCSP3CORECALLBACKS_H

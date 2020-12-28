/*=============================================================================
 * parser for CSP instances represented in XCSP3 Format
 *
 * Copyright (c) 2015 xcsp.org (contact <at> xcsp.org)
 * Copyright (c) 2008 Olivier ROUSSEL (olivier.roussel <at> cril.univ-artois.fr)
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
#ifndef COSOCO_XCSP3PRINTCALLBACKS_H
#define COSOCO_XCSP3PRINTCALLBACKS_H

#include "XCSP3CoreCallbacks.h"
#include "XCSP3Variable.h"
#include <XCSP3Tree.h>
/**
 * This is an example that prints useful informations of a XCSP3 instance.
 * You need to create your own class and to override functions of the callback.
 * We suggest to make a map between XVariable and your own variables in order to
 * facilitate the constructions of constraints.
 *
 * see main.cc to show declaration of the parser
 *
 */

namespace XCSP3Core {

    class XCSP3PrintCallbacks : public XCSP3CoreCallbacks {
    public:
        XCSP3PrintCallbacks();

        virtual void beginInstance(InstanceType type) override;

        virtual void endInstance() override;

        virtual void beginVariables() override;

        virtual void endVariables() override;

        virtual void beginVariableArray(std::string id) override;

        virtual void endVariableArray() override;

        virtual void beginConstraints() override;

        virtual void endConstraints() override;

        virtual void beginGroup(std::string id) override;

        virtual void endGroup() override;

        virtual void beginBlock(std::string classes) override;

        virtual void endBlock() override;

        virtual void beginSlide(std::string id, bool circular) override;

        virtual void endSlide() override;

        virtual void beginObjectives() override;

        virtual void endObjectives() override;

        virtual void beginAnnotations() override;

        virtual void endAnnotations() override;

        virtual void buildVariableInteger(std::string id, int minValue, int maxValue) override;

        virtual void buildVariableInteger(std::string id, std::vector<int>& values) override;

        virtual void buildConstraintExtension(std::string id, std::vector<XVariable*> list, std::vector<std::vector<int>>& tuples, bool support, bool hasStar) override;

        virtual void buildConstraintExtension(std::string id, XVariable* variable, std::vector<int>& tuples, bool support, bool hasStar) override;

        virtual void buildConstraintExtensionAs(std::string id, std::vector<XVariable*> list, bool support, bool hasStar) override;

        virtual void buildConstraintIntension(std::string id, std::string expr) override;

        virtual void buildConstraintIntension(std::string id, Tree* tree) override;

        virtual void buildConstraintPrimitive(std::string id, OrderType op, XVariable* x, int k, XVariable* y) override;

        virtual void buildConstraintPrimitive(std::string id, OrderType op, XVariable* x, int k) override;

        virtual void buildConstraintPrimitive(std::string id, XVariable* x, bool in, int min, int max) override;

        virtual void buildConstraintRegular(std::string id, std::vector<XVariable*>& list, std::string st, std::vector<std::string>& final, std::vector<XTransition>& transitions) override;

        virtual void buildConstraintMDD(std::string id, std::vector<XVariable*>& list, std::vector<XTransition>& transitions) override;

        virtual void buildConstraintAlldifferent(std::string id, std::vector<XVariable*>& list) override;

        virtual void buildConstraintAlldifferentExcept(std::string id, std::vector<XVariable*>& list, std::vector<int>& except) override;

        virtual void buildConstraintAlldifferent(std::string id, std::vector<Tree*>& list) override;

        virtual void buildConstraintAlldifferentList(std::string id, std::vector<std::vector<XVariable*>>& lists) override;

        virtual void buildConstraintAlldifferentMatrix(std::string id, std::vector<std::vector<XVariable*>>& matrix) override;

        virtual void buildConstraintAllEqual(std::string id, std::vector<XVariable*>& list) override;

        virtual void buildConstraintNotAllEqual(std::string id, std::vector<XVariable*>& list) override;

        virtual void buildConstraintOrdered(std::string id, std::vector<XVariable*>& list, OrderType order) override;

        virtual void buildConstraintOrdered(std::string id, std::vector<XVariable*>& list, std::vector<int>& lengths, OrderType order) override;

        virtual void buildConstraintLex(std::string id, std::vector<std::vector<XVariable*>>& lists, OrderType order) override;

        virtual void buildConstraintLexMatrix(std::string id, std::vector<std::vector<XVariable*>>& matrix, OrderType order) override;

        virtual void buildConstraintSum(std::string id, std::vector<XVariable*>& list, std::vector<int>& coeffs, XCondition& cond) override;

        virtual void buildConstraintSum(std::string id, std::vector<XVariable*>& list, XCondition& cond) override;

        virtual void buildConstraintSum(std::string id, std::vector<XVariable*>& list, std::vector<XVariable*>& coeffs, XCondition& cond) override;

        virtual void buildConstraintSum(std::string id, std::vector<Tree*>& list, std::vector<int>& coeffs, XCondition& cond) override;

        virtual void buildConstraintSum(std::string id, std::vector<Tree*>& list, XCondition& cond) override;

        virtual void buildConstraintAtMost(std::string id, std::vector<XVariable*>& list, int value, int k) override;

        virtual void buildConstraintAtLeast(std::string id, std::vector<XVariable*>& list, int value, int k) override;

        virtual void buildConstraintExactlyK(std::string id, std::vector<XVariable*>& list, int value, int k) override;

        virtual void buildConstraintAmong(std::string id, std::vector<XVariable*>& list, std::vector<int>& values, int k) override;

        virtual void buildConstraintExactlyVariable(std::string id, std::vector<XVariable*>& list, int value, XVariable* x) override;

        virtual void buildConstraintCount(std::string id, std::vector<XVariable*>& list, std::vector<int>& values, XCondition& xc) override;

        virtual void buildConstraintCount(std::string id, std::vector<XVariable*>& list, std::vector<XVariable*>& values, XCondition& xc) override;

        virtual void buildConstraintNValues(std::string id, std::vector<XVariable*>& list, std::vector<int>& except, XCondition& xc) override;

        virtual void buildConstraintNValues(std::string id, std::vector<XVariable*>& list, XCondition& xc) override;

        virtual void buildConstraintCardinality(std::string id, std::vector<XVariable*>& list, std::vector<int> values, std::vector<int>& occurs, bool closed) override;

        virtual void buildConstraintCardinality(std::string id, std::vector<XVariable*>& list, std::vector<int> values, std::vector<XVariable*>& occurs,
                                                bool closed) override;

        virtual void buildConstraintCardinality(std::string id, std::vector<XVariable*>& list, std::vector<int> values, std::vector<XInterval>& occurs,
                                                bool closed) override;

        virtual void buildConstraintCardinality(std::string id, std::vector<XVariable*>& list, std::vector<XVariable*> values, std::vector<int>& occurs,
                                                bool closed) override;

        virtual void buildConstraintCardinality(std::string id, std::vector<XVariable*>& list, std::vector<XVariable*> values, std::vector<XVariable*>& occurs,
                                                bool closed) override;

        virtual void buildConstraintCardinality(std::string id, std::vector<XVariable*>& list, std::vector<XVariable*> values, std::vector<XInterval>& occurs,
                                                bool closed) override;

        virtual void buildConstraintMinimum(std::string id, std::vector<XVariable*>& list, XCondition& xc) override;

        virtual void buildConstraintMinimum(std::string id, std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType rank,
                                            XCondition& xc) override;

        virtual void buildConstraintMaximum(std::string id, std::vector<XVariable*>& list, XCondition& xc) override;

        virtual void buildConstraintMaximum(std::string id, std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType rank,
                                            XCondition& xc) override;

        virtual void buildConstraintElement(std::string id, std::vector<XVariable*>& list, int value) override;

        virtual void buildConstraintElement(std::string id, std::vector<XVariable*>& list, XVariable* value) override;

        virtual void buildConstraintElement(std::string id, std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType rank, int value) override;

        virtual void buildConstraintElement(std::string id, std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType rank, XVariable* value) override;

        virtual void buildConstraintElement(std::string id, std::vector<int>& list, int startIndex, XVariable* index, RankType rank, XVariable* value) override;

        virtual void buildConstraintElement(std::string id, std::vector<std::vector<int>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, XVariable* value) override;

        virtual void buildConstraintChannel(std::string id, std::vector<XVariable*>& list, int startIndex) override;

        virtual void buildConstraintChannel(std::string id, std::vector<XVariable*>& list1, int startIndex1, std::vector<XVariable*>& list2, int startIndex2) override;

        virtual void buildConstraintChannel(std::string id, std::vector<XVariable*>& list, int startIndex, XVariable* value) override;

        virtual void buildConstraintStretch(std::string id, std::vector<XVariable*>& list, std::vector<int>& values, std::vector<XInterval>& widths) override;

        virtual void
        buildConstraintStretch(std::string id, std::vector<XVariable*>& list, std::vector<int>& values, std::vector<XInterval>& widths, std::vector<std::vector<int>>& patterns) override;

        virtual void buildConstraintNoOverlap(std::string id, std::vector<XVariable*>& origins, std::vector<int>& lengths, bool zeroIgnored) override;

        virtual void buildConstraintNoOverlap(std::string id, std::vector<XVariable*>& origins, std::vector<XVariable*>& lengths, bool zeroIgnored) override;

        virtual void buildConstraintNoOverlap(std::string id, std::vector<std::vector<XVariable*>>& origins, std::vector<std::vector<int>>& lengths, bool zeroIgnored) override;

        virtual void buildConstraintNoOverlap(std::string id, std::vector<std::vector<XVariable*>>& origins, std::vector<std::vector<XVariable*>>& lengths, bool zeroIgnored) override;

        virtual void buildConstraintInstantiation(std::string id, std::vector<XVariable*>& list, std::vector<int>& values) override;

        virtual void buildConstraintClause(std::string id, std::vector<XVariable*>& positive, std::vector<XVariable*>& negative) override;

        virtual void buildConstraintCircuit(std::string id, std::vector<XVariable*>& list, int startIndex) override;

        virtual void buildConstraintCircuit(std::string id, std::vector<XVariable*>& list, int startIndex, int size) override;

        virtual void buildConstraintCircuit(std::string id, std::vector<XVariable*>& list, int startIndex, XVariable* size) override;

        virtual void buildObjectiveMinimizeExpression(std::string expr) override;

        virtual void buildObjectiveMaximizeExpression(std::string expr) override;

        virtual void buildObjectiveMinimizeVariable(XVariable* x) override;

        virtual void buildObjectiveMaximizeVariable(XVariable* x) override;

        virtual void buildObjectiveMinimize(ExpressionObjective type, std::vector<XVariable*>& list, std::vector<int>& coefs) override;

        virtual void buildObjectiveMaximize(ExpressionObjective type, std::vector<XVariable*>& list, std::vector<int>& coefs) override;

        virtual void buildObjectiveMinimize(ExpressionObjective type, std::vector<XVariable*>& list) override;

        virtual void buildObjectiveMaximize(ExpressionObjective type, std::vector<XVariable*>& list) override;

        virtual void buildAnnotationDecision(std::vector<XVariable*>& list) override;
        bool canonize;
    };

} // namespace XCSP3Core

using namespace XCSP3Core;

XCSP3PrintCallbacks::XCSP3PrintCallbacks() : XCSP3CoreCallbacks(), canonize(true) {}

template <class T>
void displayList(std::vector<T>& list, std::string separator = " ") {
    if (list.size() > 8) {
        for (int i = 0; i < 3; i++)
            std::cout << list[i] << separator;
        std::cout << " ... ";
        for (unsigned int i = list.size() - 4; i < list.size(); i++)
            std::cout << list[i] << separator;
        std::cout << std::endl;
        return;
    }
    for (unsigned int i = 0; i < list.size(); i++)
        std::cout << list[i] << separator;
    std::cout << std::endl;
}

void displayList(std::vector<XVariable*>& list, std::string separator = " ") {
    if (list.size() > 8) {
        for (int i = 0; i < 3; i++)
            std::cout << list[i]->id << separator;
        std::cout << " ... ";
        for (unsigned int i = list.size() - 4; i < list.size(); i++)
            std::cout << list[i]->id << separator;
        std::cout << std::endl;
        return;
    }
    for (unsigned int i = 0; i < list.size(); i++)
        std::cout << list[i]->id << separator;
    std::cout << std::endl;
}

void XCSP3PrintCallbacks::beginInstance(InstanceType type) {
    std::cout << "Start Instance - type=" << static_cast<int>(type) << std::endl;
}

void XCSP3PrintCallbacks::endInstance() {
    std::cout << "End SAX parsing " << std::endl;
}

void XCSP3PrintCallbacks::beginVariables() {
    std::cout << " start variables declaration" << std::endl;
}

void XCSP3PrintCallbacks::endVariables() {
    std::cout << " end variables declaration" << std::endl
              << std::endl;
}

void XCSP3PrintCallbacks::beginVariableArray(std::string id) {
    std::cout << "    array: " << id << std::endl;
}

void XCSP3PrintCallbacks::endVariableArray() {
}

void XCSP3PrintCallbacks::beginConstraints() {
    std::cout << " start constraints declaration" << std::endl;
}

void XCSP3PrintCallbacks::endConstraints() {
    std::cout << "\n end constraints declaration" << std::endl
              << std::endl;
}

void XCSP3PrintCallbacks::beginGroup(std::string id) {
    std::cout << "   start group of constraint " << id << std::endl;
}

void XCSP3PrintCallbacks::endGroup() {
    std::cout << "   end group of constraint" << std::endl;
}

void XCSP3PrintCallbacks::beginBlock(std::string classes) {
    std::cout << "   start block of constraint classes = " << classes << std::endl;
}

void XCSP3PrintCallbacks::endBlock() {
    std::cout << "   end block of constraint" << std::endl;
}

// std::string id, bool circular
void XCSP3PrintCallbacks::beginSlide(std::string id, bool) {
    std::cout << "   start slide " << id << std::endl;
}

void XCSP3PrintCallbacks::endSlide() {
    std::cout << "   end slide" << std::endl;
}

void XCSP3PrintCallbacks::beginObjectives() {
    std::cout << "   start Objective " << std::endl;
}

void XCSP3PrintCallbacks::endObjectives() {
    std::cout << "   end Objective " << std::endl;
}

void XCSP3PrintCallbacks::beginAnnotations() {
    std::cout << "   begin Annotations " << std::endl;
}

void XCSP3PrintCallbacks::endAnnotations() {
    std::cout << "   end Annotations " << std::endl;
}

void XCSP3PrintCallbacks::buildVariableInteger(std::string id, int minValue, int maxValue) {
    std::cout << "    var " << id << " : " << minValue << "..." << maxValue << std::endl;
}

void XCSP3PrintCallbacks::buildVariableInteger(std::string id, std::vector<int>& values) {
    std::cout << "    var " << id << " : ";
    std::cout << "        ";
    displayList(values);
}

void XCSP3PrintCallbacks::buildConstraintExtension(std::string id, std::vector<XVariable*> list, std::vector<std::vector<int>>& tuples, bool support, bool hasStar) {
    std::cout << "\n    extension constraint : " << id << std::endl;
    std::cout << "        " << (support ? "support" : "conflict") << " arity: " << list.size() << " nb tuples: " << tuples.size() << " star: " << hasStar << std::endl;
    std::cout << "        ";
    displayList(list);
}

void XCSP3PrintCallbacks::buildConstraintExtension(std::string id, XVariable* variable, std::vector<int>& tuples, bool support, bool hasStar) {
    std::cout << "\n    extension constraint with one variable: " << id << std::endl;
    std::cout << "        " << (*variable) << " " << (support ? "support" : "conflict") << " nb tuples: " << tuples.size() << " star: " << hasStar << std::endl;
    std::cout << std::endl;
}

// std::string id, std::vector<XVariable *> list, bool support, bool hasStar
void XCSP3PrintCallbacks::buildConstraintExtensionAs(std::string id, std::vector<XVariable*>, bool, bool) {
    std::cout << "\n    extension constraint similar as previous one: " << id << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintIntension(std::string id, std::string expr) {
    std::cout << "\n    intension constraint (using string) : " << id << " : " << expr << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintIntension(std::string id, Tree* tree) {
    std::cout << "\n    intension constraint using canonized tree: " << id << " : ";
    tree->prefixe();
    std::cout << "\n";
}

void XCSP3PrintCallbacks::buildConstraintPrimitive(std::string id, OrderType, XVariable* x, int k, XVariable* y) {
    std::cout << "\n   intension constraint " << id << ": " << x->id << (k >= 0 ? "+" : "") << k << " op " << y->id << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintPrimitive(std::string id, OrderType op, XVariable* x, int k) {
    (void)op;
    std::cout << "\n   constraint  " << id << ":" << x->id << " op " << k << "\n";
}

void XCSP3PrintCallbacks::buildConstraintPrimitive(std::string id, XVariable* x, bool in, int min, int max) {
    std::cout << "\n   constraint  " << id << ":" << x->id << (in ? " in " : " not in ") << min << ".." << max << "\n";
}

// std::string id, std::vector<XVariable *> &list, string start, std::vector<string> &final, std::vector<XTransition> &transitions
void XCSP3PrintCallbacks::buildConstraintRegular(std::string, std::vector<XVariable*>& list, std::string start, std::vector<std::string>& final, std::vector<XTransition>& transitions) {
    std::cout << "\n    regular constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        start: " << start << std::endl;
    std::cout << "        final: ";
    displayList(final, ",");
    std::cout << std::endl;
    std::cout << "        transitions: ";
    for (unsigned int i = 0; i < (transitions.size() > 4 ? 4 : transitions.size()); i++) {
        std::cout << "(" << transitions[i].from << "," << transitions[i].val << "," << transitions[i].to << ") ";
    }
    if (transitions.size() > 4)
        std::cout << "...";
    std::cout << std::endl;
}

// std::string id, std::vector<XVariable *> &list, std::vector<XTransition> &transitions
void XCSP3PrintCallbacks::buildConstraintMDD(std::string, std::vector<XVariable*>& list, std::vector<XTransition>& transitions) {
    std::cout << "\n    mdd constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        transitions: ";
    for (unsigned int i = 0; i < (transitions.size() > 4 ? 4 : transitions.size()); i++) {
        std::cout << "(" << transitions[i].from << "," << transitions[i].val << "," << transitions[i].to << ") ";
    }
    if (transitions.size() > 4)
        std::cout << "...";
    std::cout << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintAlldifferent(std::string id, std::vector<XVariable*>& list) {
    std::cout << "\n    allDiff constraint" << id << std::endl;
    std::cout << "        ";
    displayList(list);
}

void XCSP3PrintCallbacks::buildConstraintAlldifferentExcept(std::string id, std::vector<XVariable*>& list, std::vector<int>& except) {
    std::cout << "\n    allDiff constraint with exceptions" << id << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        Exceptions:";
    displayList(except);
}

void XCSP3PrintCallbacks::buildConstraintAlldifferent(std::string id, std::vector<Tree*>& list) {
    std::cout << "\n    allDiff constraint with expresions" << id << std::endl;
    std::cout << "        ";
    for (Tree* t : list) {
        t->prefixe();
        std::cout << " ";
    }
    std::cout << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintAlldifferentList(std::string id, std::vector<std::vector<XVariable*>>& lists) {
    std::cout << "\n    allDiff list constraint" << id << std::endl;
    for (unsigned int i = 0; i < (lists.size() < 4 ? lists.size() : 3); i++) {
        std::cout << "        ";
        displayList(lists[i]);
    }
}

void XCSP3PrintCallbacks::buildConstraintAlldifferentMatrix(std::string id, std::vector<std::vector<XVariable*>>& matrix) {
    std::cout << "\n    allDiff matrix constraint" << id << std::endl;
    for (unsigned int i = 0; i < matrix.size(); i++) {
        std::cout << "        ";
        displayList(matrix[i]);
    }
}

void XCSP3PrintCallbacks::buildConstraintAllEqual(std::string id, std::vector<XVariable*>& list) {
    std::cout << "\n    allEqual constraint" << id << std::endl;
    std::cout << "        ";
    displayList(list);
}

void XCSP3PrintCallbacks::buildConstraintNotAllEqual(std::string id, std::vector<XVariable*>& list) {
    std::cout << "\n    not allEqual constraint" << id << std::endl;
    std::cout << "        ";
    displayList(list);
}

// std::string id, std::vector<XVariable *> &list, OrderType order
void XCSP3PrintCallbacks::buildConstraintOrdered(std::string, std::vector<XVariable*>& list, OrderType order) {
    std::cout << "\n    ordered constraint" << std::endl;
    std::string sep;
    if (order == OrderType::LT)
        sep = " < ";
    if (order == OrderType::LE)
        sep = " <= ";
    if (order == OrderType::GT)
        sep = " > ";
    if (order == OrderType::GE)
        sep = " >= ";
    std::cout << "        ";
    displayList(list, sep);
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> &lengths, OrderType order
void XCSP3PrintCallbacks::buildConstraintOrdered(std::string, std::vector<XVariable*>& list, std::vector<int>& lengths, OrderType order) {
    std::cout << "\n    ordered constraint with lengths" << std::endl;
    std::string sep;
    if (order == OrderType::LT)
        sep = " < ";
    if (order == OrderType::LE)
        sep = " <= ";
    if (order == OrderType::GT)
        sep = " > ";
    if (order == OrderType::GE)
        sep = " >= ";
    std::cout << "        ";
    displayList(lengths);
    std::cout << "      ";
    displayList(list, sep);
}

// std::string id, std::vector<std::vector<XVariable *>> &lists, OrderType order
void XCSP3PrintCallbacks::buildConstraintLex(std::string, std::vector<std::vector<XVariable*>>& lists, OrderType order) {
    std::cout << "\n    lex constraint   nb lists: " << lists.size() << std::endl;
    std::string sep;
    if (order == OrderType::LT)
        sep = " < ";
    if (order == OrderType::LE)
        sep = " <= ";
    if (order == OrderType::GT)
        sep = " > ";
    if (order == OrderType::GE)
        sep = " >= ";
    std::cout << "        operator: " << sep << std::endl;
    for (unsigned int i = 0; i < lists.size(); i++) {
        std::cout << "        list " << i << ": ";
        std::cout << "        ";
        displayList(lists[i], " ");
    }
}

// std::string id, std::vector<std::vector<XVariable *>> &matrix, OrderType order
void XCSP3PrintCallbacks::buildConstraintLexMatrix(std::string, std::vector<std::vector<XVariable*>>& matrix, OrderType order) {
    std::cout << "\n    lex matrix constraint   matrix  " << std::endl;
    std::string sep;
    if (order == OrderType::LT)
        sep = " < ";
    if (order == OrderType::LE)
        sep = " <= ";
    if (order == OrderType::GT)
        sep = " > ";
    if (order == OrderType::GE)
        sep = " >= ";

    for (unsigned int i = 0; i < (matrix.size() < 4 ? matrix.size() : 3); i++) {
        std::cout << "        ";
        displayList(matrix[i]);
    }
    std::cout << "        Order " << sep << std::endl;
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> &coeffs, XCondition &cond
void XCSP3PrintCallbacks::buildConstraintSum(std::string, std::vector<XVariable*>& list, std::vector<int>& coeffs, XCondition& cond) {
    std::cout << "\n        sum constraint:";
    if (list.size() > 8) {
        for (int i = 0; i < 3; i++)
            std::cout << (coeffs.size() == 0 ? 1 : coeffs[i]) << "*" << *(list[i]) << " ";
        std::cout << " ... ";
        for (unsigned int i = list.size() - 4; i < list.size(); i++)
            std::cout << (coeffs.size() == 0 ? 1 : coeffs[i]) << "*" << *(list[i]) << " ";
    } else {
        for (unsigned int i = 0; i < list.size(); i++)
            std::cout << (coeffs.size() == 0 ? 1 : coeffs[i]) << "*" << *(list[i]) << " ";
    }
    std::cout << cond << std::endl;
}

// std::string id, std::vector<XVariable *> &list, XCondition &cond
void XCSP3PrintCallbacks::buildConstraintSum(std::string, std::vector<XVariable*>& list, XCondition& cond) {
    std::cout << "\n        unweighted sum constraint:";
    std::cout << "        ";
    displayList(list, "+");
    std::cout << cond << std::endl;
}

// std::string id, std::vector<XVariable *> &list, std::vector<XVariable *> &coeffs, XCondition &cond
void XCSP3PrintCallbacks::buildConstraintSum(std::string, std::vector<XVariable*>& list, std::vector<XVariable*>& coeffs, XCondition& cond) {
    std::cout << "\n        scalar sum constraint:";
    if (list.size() > 8) {
        for (int i = 0; i < 3; i++)
            std::cout << coeffs[i]->id << "*" << *(list[i]) << " ";
        std::cout << " ... ";
        for (unsigned int i = list.size() - 4; i < list.size(); i++)
            std::cout << coeffs[i]->id << "*" << *(list[i]) << " ";
    } else {
        for (unsigned int i = 0; i < list.size(); i++)
            std::cout << coeffs[i]->id << "*" << *(list[i]) << " ";
    }
    std::cout << cond << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintSum(std::string id, std::vector<Tree*>& list, std::vector<int>& coeffs, XCondition& cond) {
    (void)id;
    std::cout << "\n        sum with expression constraint;";
    if (list.size() > 8) {
        for (int i = 0; i < 3; i++) {
            std::cout << coeffs[i];
            list[i]->prefixe();
        }
        std::cout << " ... ";
        for (unsigned int i = list.size() - 4; i < list.size(); i++) {
            std::cout << coeffs[i];
            list[i]->prefixe();
        }
    } else {
        for (unsigned int i = 0; i < list.size(); i++) {
            std::cout << coeffs[i];
            list[i]->prefixe();
        }
    }
    std::cout << cond << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintSum(std::string id, std::vector<Tree*>& list, XCondition& cond) {
    (void)id;
    if (list.size() > 8) {
        for (int i = 0; i < 3; i++) {
            list[i]->prefixe();
        }
        std::cout << " ... ";
        for (unsigned int i = list.size() - 4; i < list.size(); i++) {
            list[i]->prefixe();
        }
    } else {
        for (unsigned int i = 0; i < list.size(); i++) {
            list[i]->prefixe();
        }
    }
    std::cout << cond << std::endl;
}

// std::string id, std::vector<XVariable *> &list, int value, int k
void XCSP3PrintCallbacks::buildConstraintAtMost(std::string, std::vector<XVariable*>& list, int value, int k) {
    std::cout << "\n    AtMost constraint: val=" << value << " k=" << k << std::endl;
    std::cout << "        ";
    displayList(list);
}

// std::string id, std::vector<XVariable *> &list, int value, int k
void XCSP3PrintCallbacks::buildConstraintAtLeast(std::string, std::vector<XVariable*>& list, int value, int k) {
    std::cout << "\n    Atleast constraint: val=" << value << " k=" << k << std::endl;
    std::cout << "        ";
    displayList(list);
}

// std::string id, std::vector<XVariable *> &list, int value, int k
void XCSP3PrintCallbacks::buildConstraintExactlyK(std::string, std::vector<XVariable*>& list, int value, int k) {
    std::cout << "\n    Exactly constraint: val=" << value << " k=" << k << std::endl;
    std::cout << "        ";
    displayList(list);
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> &values, int k
void XCSP3PrintCallbacks::buildConstraintAmong(std::string, std::vector<XVariable*>& list, std::vector<int>& values, int k) {
    std::cout << "\n    Among constraint: k=" << k << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
}

// std::string id, std::vector<XVariable *> &list, int value, XVariable *x
void XCSP3PrintCallbacks::buildConstraintExactlyVariable(std::string, std::vector<XVariable*>& list, int value, XVariable* x) {
    std::cout << "\n    Exactly Variable constraint: val=" << value << " variable=" << *x << std::endl;
    std::cout << "        ";
    displayList(list);
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> &values, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintCount(std::string, std::vector<XVariable*>& list, std::vector<int>& values, XCondition& xc) {
    std::cout << "\n    count constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values: ";
    std::cout << "        ";
    displayList(values);
    std::cout << "        condition: " << xc << std::endl;
}

// std::string id, std::vector<XVariable *> &list, std::vector<XVariable *> &values, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintCount(std::string, std::vector<XVariable*>& list, std::vector<XVariable*>& values, XCondition& xc) {
    std::cout << "\n    count constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values: ";
    displayList(values);
    std::cout << "        condition: " << xc << std::endl;
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> &except, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintNValues(std::string, std::vector<XVariable*>& list, std::vector<int>& except, XCondition& xc) {
    std::cout << "\n    NValues with exceptions constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        exceptions: ";
    displayList(except);
    std::cout << "        condition:" << xc << std::endl;
}

// std::string id, std::vector<XVariable *> &list, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintNValues(std::string, std::vector<XVariable*>& list, XCondition& xc) {
    std::cout << "\n    NValues  constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        condition:" << xc << std::endl;
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> values, std::vector<int> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(std::string, std::vector<XVariable*>& list, std::vector<int> values, std::vector<int>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (int values, int occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> values, std::vector<XVariable *> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(std::string, std::vector<XVariable*>& list, std::vector<int> values, std::vector<XVariable*>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (int values, var occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> values, std::vector<XInterval> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(std::string, std::vector<XVariable*>& list, std::vector<int> values, std::vector<XInterval>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (int values, interval occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
}

// std::string id, std::vector<XVariable *> &list, std::vector<XVariable *> values, std::vector<int> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(std::string, std::vector<XVariable*>& list, std::vector<XVariable*> values, std::vector<int>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (var values, int occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
}

// std::string id, std::vector<XVariable *> &list, std::vector<XVariable *> values, std::vector<XVariable *> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(std::string, std::vector<XVariable*>& list, std::vector<XVariable*> values, std::vector<XVariable*>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (var values, var occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
}

// std::string id, std::vector<XVariable *> &list, std::vector<XVariable *> values, std::vector<XInterval> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(std::string, std::vector<XVariable*>& list, std::vector<XVariable*> values, std::vector<XInterval>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (var values, interval occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
}

// std::string id, std::vector<XVariable *> &list, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMinimum(std::string, std::vector<XVariable*>& list, XCondition& xc) {
    std::cout << "\n    minimum  constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        condition: " << xc << std::endl;
}

// std::string id, std::vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMinimum(std::string, std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType, XCondition& xc) {
    std::cout << "\n    arg_minimum  constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        index:" << *index << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        condition: " << xc << std::endl;
}

// std::string id, std::vector<XVariable *> &list, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMaximum(std::string, std::vector<XVariable*>& list, XCondition& xc) {
    std::cout << "\n    maximum  constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        condition: " << xc << std::endl;
}

// std::string id, std::vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMaximum(std::string, std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType, XCondition& xc) {
    std::cout << "\n    arg_maximum  constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        index:" << *index << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        condition: " << xc << std::endl;
}

// std::string id, std::vector<XVariable *> &list, int value
void XCSP3PrintCallbacks::buildConstraintElement(std::string, std::vector<XVariable*>& list, int value) {
    std::cout << "\n    element constant constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << value << std::endl;
}

// std::string id, std::vector<XVariable *> &list, XVariable *value
void XCSP3PrintCallbacks::buildConstraintElement(std::string, std::vector<XVariable*>& list, XVariable* value) {
    std::cout << "\n    element variable constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << *value << std::endl;
}

// std::string id, std::vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, int value
void XCSP3PrintCallbacks::buildConstraintElement(std::string, std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType, int value) {
    std::cout << "\n    element constant (with index) constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << value << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        index : " << *index << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintElement(std::string id, std::vector<std::vector<int>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, XVariable* value) {
    (void)id;
    (void)startRowIndex;
    (void)startColIndex;
    std::cout << "\n    element matrix with rowIndex, colIndex and Value variables\n";
    for (unsigned int i = 0; i < matrix.size(); i++) {
        for (unsigned int j = 0; j < matrix.size(); j++)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << "        row index : " << *rowIndex << std::endl;
    std::cout << "        col index : " << *colIndex << std::endl;
    std::cout << "        value     : " << *value << std::endl;
}

// std::string id, std::vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, XVariable *value
void XCSP3PrintCallbacks::buildConstraintElement(std::string, std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType, XVariable* value) {
    std::cout << "\n    element variable (with index) constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << *value << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        index : " << *index << std::endl;
}

// string, std::vector<int> &list, int startIndex, XVariable *index, RankType rank, XVariable *value
void XCSP3PrintCallbacks::buildConstraintElement(std::string, std::vector<int>& list, int startIndex, XVariable* index, RankType, XVariable* value) {
    std::cout << "\n    element variable with list of integers (with index) constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << *value << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        index : " << *index << std::endl;
}

// std::string id, std::vector<XVariable *> &list, int startIndex
void XCSP3PrintCallbacks::buildConstraintChannel(std::string, std::vector<XVariable*>& list, int startIndex) {
    std::cout << "\n    channel constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        Start index : " << startIndex << std::endl;
}

// std::string id, std::vector<XVariable *> &list1, int startIndex1, std::vector<XVariable *> &list2, int startIndex2
void XCSP3PrintCallbacks::buildConstraintChannel(std::string, std::vector<XVariable*>& list1, int, std::vector<XVariable*>& list2, int) {
    std::cout << "\n    channel constraint" << std::endl;
    std::cout << "        list1 ";
    displayList(list1);
    std::cout << "        list2 ";
    displayList(list2);
}

// std::string id, std::vector<XVariable *> &list, int startIndex, XVariable *value
void XCSP3PrintCallbacks::buildConstraintChannel(std::string, std::vector<XVariable*>& list, int, XVariable* value) {
    std::cout << "\n    channel constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << *value << std::endl;
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> &values, std::vector<XInterval> &widths
void XCSP3PrintCallbacks::buildConstraintStretch(std::string, std::vector<XVariable*>& list, std::vector<int>& values, std::vector<XInterval>& widths) {
    std::cout << "\n    stretch constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values :";
    displayList(values);
    std::cout << "        widths:";
    displayList(widths);
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> &values, std::vector<XInterval> &widths, std::vector<std::vector<int>> &patterns
void XCSP3PrintCallbacks::buildConstraintStretch(std::string, std::vector<XVariable*>& list, std::vector<int>& values, std::vector<XInterval>& widths, std::vector<std::vector<int>>& patterns) {
    std::cout << "\n    stretch constraint (with patterns)" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values :";
    displayList(values);
    std::cout << "        widths:";
    displayList(widths);
    std::cout << "        patterns";
    for (unsigned int i = 0; i < patterns.size(); i++)
        std::cout << "(" << patterns[i][0] << "," << patterns[i][1] << ") ";
    std::cout << std::endl;
}

// std::string id, std::vector<XVariable *> &origins, std::vector<int> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(std::string, std::vector<XVariable*>& origins, std::vector<int>& lengths, bool) {
    std::cout << "\n    nooverlap constraint" << std::endl;
    std::cout << "        origins";
    displayList(origins);
    std::cout << "        lengths";
    displayList(lengths);
}

// std::string id, std::vector<XVariable *> &origins, std::vector<XVariable *> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(std::string, std::vector<XVariable*>& origins, std::vector<XVariable*>& lengths, bool) {
    std::cout << "\n    nooverlap constraint" << std::endl;
    std::cout << "        origins:";
    displayList(origins);
    std::cout << "        lengths";
    displayList(lengths);
}

// std::string id, std::vector<std::vector<XVariable *>> &origins, std::vector<std::vector<int>> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(std::string, std::vector<std::vector<XVariable*>>& origins, std::vector<std::vector<int>>& lengths, bool) {
    std::cout << "\n    kdim (int lengths) nooverlap constraint" << std::endl;
    std::cout << "origins: " << std::endl;
    for (unsigned int i = 0; i < origins.size(); i++) {
        std::cout << "        ";
        displayList(origins[i]);
    }
    std::cout << "lengths: " << std::endl;
    for (unsigned int i = 0; i < origins.size(); i++) {
        std::cout << "        ";
        displayList(lengths[i]);
    }
}

// std::string id, std::vector<std::vector<XVariable *>> &origins, std::vector<std::vector<XVariable *>> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(std::string, std::vector<std::vector<XVariable*>>& origins, std::vector<std::vector<XVariable*>>& lengths, bool) {
    std::cout << "\n    kdim (lenghts vars nooverlap constraint" << std::endl;
    std::cout << "origins: " << std::endl;
    for (unsigned int i = 0; i < origins.size(); i++) {
        std::cout << "        ";
        displayList(origins[i]);
    }
    std::cout << "lengths: " << std::endl;
    for (unsigned int i = 0; i < origins.size(); i++) {
        std::cout << "        ";
        displayList(lengths[i]);
    }
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> &values
void XCSP3PrintCallbacks::buildConstraintInstantiation(std::string, std::vector<XVariable*>& list, std::vector<int>& values) {
    std::cout << "\n    instantiation constraint" << std::endl;
    std::cout << "        list:";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
}

// std::string id, std::vector<XVariable *> &list, std::vector<int> &values
void XCSP3PrintCallbacks::buildConstraintClause(std::string, std::vector<XVariable*>& positive, std::vector<XVariable*>& negative) {
    std::cout << "\n    Clause constraint" << std::endl;
    std::cout << "        positive lits size:" << positive.size() << " ";
    displayList(positive);
    std::cout << "        negative lits size:" << negative.size() << " ";
    displayList(negative);
}

// std::string id, std::vector<XVariable *> &list, int startIndex
void XCSP3PrintCallbacks::buildConstraintCircuit(std::string, std::vector<XVariable*>& list, int startIndex) {
    std::cout << "\n    circuit constraint" << std::endl;
    std::cout << "        list:";
    displayList(list);
    std::cout << "        startIndex:" << startIndex << std::endl;
}

// std::string id, std::vector<XVariable *> &list, int startIndex, int size
void XCSP3PrintCallbacks::buildConstraintCircuit(std::string, std::vector<XVariable*>& list, int startIndex, int size) {
    std::cout << "\n    circuit constraint" << std::endl;
    std::cout << "        list:";
    displayList(list);
    std::cout << "        startIndex:" << startIndex << std::endl;
    std::cout << "        size: " << size << std::endl;
}

// std::string id, std::vector<XVariable *> &list, int startIndex, XVariable *size
void XCSP3PrintCallbacks::buildConstraintCircuit(std::string, std::vector<XVariable*>& list, int startIndex, XVariable* size) {
    std::cout << "\n    circuit constraint" << std::endl;
    std::cout << "        list:";
    displayList(list);
    std::cout << "        startIndex:" << startIndex << std::endl;
    std::cout << "        size: " << size->id << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMinimizeExpression(std::string expr) {

    std::cout << "\n    objective: minimize" << expr << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMaximizeExpression(std::string expr) {
    std::cout << "\n    objective: maximize" << expr << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMinimizeVariable(XVariable* x) {
    std::cout << "\n    objective: minimize variable " << x << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMaximizeVariable(XVariable* x) {
    std::cout << "\n    objective: maximize variable " << x << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMinimize(ExpressionObjective type, std::vector<XVariable*>& list, std::vector<int>& coefs) {
    XCSP3CoreCallbacks::buildObjectiveMinimize(type, list, coefs);
}

void XCSP3PrintCallbacks::buildObjectiveMaximize(ExpressionObjective type, std::vector<XVariable*>& list, std::vector<int>& coefs) {
    XCSP3CoreCallbacks::buildObjectiveMaximize(type, list, coefs);
}

void XCSP3PrintCallbacks::buildObjectiveMinimize(ExpressionObjective type, std::vector<XVariable*>& list) {
    XCSP3CoreCallbacks::buildObjectiveMinimize(type, list);
}

void XCSP3PrintCallbacks::buildObjectiveMaximize(ExpressionObjective type, std::vector<XVariable*>& list) {
    XCSP3CoreCallbacks::buildObjectiveMaximize(type, list);
}

void XCSP3PrintCallbacks::buildAnnotationDecision(std::vector<XVariable*>& list) {
    std::cout << "       decision variables" << std::endl
              << "       ";
    displayList(list);
}

#endif //COSOCO_XCSP3PRINTCALLBACKS_H

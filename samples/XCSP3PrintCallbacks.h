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
#include "XCSP3Tree.h"
#include "XCSP3Variable.h"
#include <algorithm>
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

    class XCSP3PrintCallbacks : public XCSP3CoreCallbacksBase {
    public:
        XCSP3PrintCallbacks();

        void beginInstance(InstanceType type) override;
        void endInstance() override;

        void beginVariables() override;
        void endVariables() override;

        void beginVariableArray(const std::string& id) override;
        void endVariableArray() override;

        void beginConstraints() override;
        void endConstraints() override;

        void beginGroup(const std::string& id) override;
        void endGroup() override;

        void beginBlock(const std::string& classes) override;
        void endBlock() override;

        void beginSlide(const std::string& id, bool circular) override;
        void endSlide() override;

        void beginObjectives() override;
        void endObjectives() override;

        void beginAnnotations() override;
        void endAnnotations() override;

        void buildVariableInteger(const std::string& id, int minValue, int maxValue) override;
        void buildVariableInteger(const std::string& id, const std::vector<int>& values) override;

        void buildAnnotationDecision(std::vector<XVariable*>& list) override;

        void buildConstraintTrue(const std::string& id) override;
        void buildConstraintFalse(const std::string& id) override;

        void buildConstraintExtension(const std::string& id, const std::vector<XVariable*>& list, const std::vector<std::vector<int>>& tuples, bool support, bool hasStar) override;
        void buildConstraintExtension(const std::string& id, XVariable* variable, const std::vector<int>& tuples, bool support, bool hasStar) override;

        void buildConstraintExtensionAs(const std::string& id, const std::vector<XVariable*>& list, bool support, bool hasStar) override;

        void buildConstraintIntension(const std::string& id, std::string expr) override;
        void buildConstraintIntension(const std::string& id, Tree* tree) override;

        void buildConstraintPrimitive(const std::string& id, OrderType op, XVariable* x, int k, XVariable* y) override;
        void buildConstraintPrimitive(const std::string& id, OrderType op, XVariable* x, int k) override;
        void buildConstraintPrimitive(const std::string& id, XVariable* x, bool in, int min, int max) override;

        void buildConstraintRegular(const std::string& id, const std::vector<XVariable*>& list, std::string st, const std::vector<std::string>& final, const std::vector<XTransition>& transitions) override;

        void buildConstraintMDD(const std::string& id, const std::vector<XVariable*>& list, const std::vector<XTransition>& transitions) override;

        void buildConstraintAlldifferent(const std::string& id, const std::vector<XVariable*>& list) override;
        void buildConstraintAlldifferentExcept(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& except) override;
        void buildConstraintAlldifferent(const std::string& id, const std::vector<Tree*>& list) override;
        void buildConstraintAlldifferentList(const std::string& id, const std::vector<std::vector<XVariable*>>& lists) override;
        void buildConstraintAlldifferentMatrix(const std::string& id, const std::vector<std::vector<XVariable*>>& matrix) override;

        void buildConstraintAllEqual(const std::string& id, const std::vector<XVariable*>& list) override;

        void buildConstraintNotAllEqual(const std::string& id, const std::vector<XVariable*>& list) override;

        void buildConstraintOrdered(const std::string& id, const std::vector<XVariable*>& list, OrderType order) override;
        void buildConstraintOrdered(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& lengths, OrderType order) override;

        void buildConstraintLex(const std::string& id, const std::vector<std::vector<XVariable*>>& lists, OrderType order) override;
        void buildConstraintLexMatrix(const std::string& id, const std::vector<std::vector<XVariable*>>& matrix, OrderType order) override;

        void buildConstraintSum(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& coeffs, XCondition& cond) override;
        void buildConstraintSum(const std::string& id, const std::vector<XVariable*>& list, XCondition& cond) override;
        void buildConstraintSum(const std::string& id, const std::vector<XVariable*>& list, const std::vector<XVariable*>& coeffs, XCondition& cond) override;
        void buildConstraintSum(const std::string& id, const std::vector<Tree*>& list, const std::vector<int>& coeffs, XCondition& cond) override;
        void buildConstraintSum(const std::string& id, const std::vector<Tree*>& list, XCondition& cond) override;

        void buildConstraintMult(const std::string& id, XVariable* x, XVariable* y, XVariable* z) override;

        void buildConstraintAtMost(const std::string& id, const std::vector<XVariable*>& list, int value, int k) override;
        void buildConstraintAtLeast(const std::string& id, const std::vector<XVariable*>& list, int value, int k) override;
        void buildConstraintExactlyK(const std::string& id, const std::vector<XVariable*>& list, int value, int k) override;
        void buildConstraintAmong(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& values, int k) override;
        void buildConstraintExactlyVariable(const std::string& id, const std::vector<XVariable*>& list, int value, XVariable* x) override;

        void buildConstraintCount(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& values, XCondition& xc) override;
        void buildConstraintCount(const std::string& id, const std::vector<XVariable*>& list, const std::vector<XVariable*>& values, XCondition& xc) override;

        void buildConstraintNValues(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& except, XCondition& xc) override;
        void buildConstraintNValues(const std::string& id, const std::vector<XVariable*>& list, XCondition& xc) override;

        void buildConstraintCardinality(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int> values, const std::vector<int>& occurs, bool closed) override;
        void buildConstraintCardinality(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int> values, const std::vector<XVariable*>& occurs, bool closed) override;
        void buildConstraintCardinality(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int> values, const std::vector<XInterval>& occurs, bool closed) override;
        void buildConstraintCardinality(const std::string& id, const std::vector<XVariable*>& list, const std::vector<XVariable*> values, const std::vector<int>& occurs, bool closed) override;
        void buildConstraintCardinality(const std::string& id, const std::vector<XVariable*>& list, const std::vector<XVariable*> values, const std::vector<XVariable*>& occurs, bool closed) override;
        void buildConstraintCardinality(const std::string& id, const std::vector<XVariable*>& list, const std::vector<XVariable*> values, const std::vector<XInterval>& occurs, bool closed) override;

        void buildConstraintMinimum(const std::string& id, const std::vector<XVariable*>& list, XCondition& xc) override;
        void buildConstraintMinimum(const std::string& id, const std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType rank, XCondition& xc) override;
        void buildConstraintMinimum(const std::string& id, const std::vector<Tree*>& list, XCondition& xc) override;

        void buildConstraintMaximum(const std::string& id, const std::vector<XVariable*>& list, XCondition& xc) override;
        void buildConstraintMaximum(const std::string& id, const std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType rank, XCondition& xc) override;
        void buildConstraintMaximum(const std::string& id, const std::vector<Tree*>& list, XCondition& xc) override;

        void buildConstraintElement(const std::string& id, const std::vector<XVariable*>& list, int value) override;
        void buildConstraintElement(const std::string& id, const std::vector<XVariable*>& list, XVariable* value) override;
        void buildConstraintElement(const std::string& id, const std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType rank, int value) override;
        void buildConstraintElement(const std::string& id, const std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType rank, XVariable* value) override;
        void buildConstraintElement(const std::string& id, const std::vector<int>& list, int startIndex, XVariable* index, RankType rank, XVariable* value) override;
        void buildConstraintElement(const std::string& id, const std::vector<std::vector<int>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, XVariable* value) override;
        void buildConstraintElement(const std::string& id, const std::vector<std::vector<XVariable*>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, XVariable* value) override;
        void buildConstraintElement(const std::string& id, const std::vector<std::vector<XVariable*>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, int value) override;

        void buildConstraintChannel(const std::string& id, const std::vector<XVariable*>& list, int startIndex) override;
        void buildConstraintChannel(const std::string& id, const std::vector<XVariable*>& list1, int startIndex1, const std::vector<XVariable*>& list2, int startIndex2) override;
        void buildConstraintChannel(const std::string& id, const std::vector<XVariable*>& list, int startIndex, XVariable* value) override;

        void buildConstraintStretch(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& values, const std::vector<XInterval>& widths) override;
        void buildConstraintStretch(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& values, const std::vector<XInterval>& widths, const std::vector<std::vector<int>>& patterns) override;

        void buildConstraintNoOverlap(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, bool zeroIgnored) override;
        void buildConstraintNoOverlap(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, bool zeroIgnored) override;
        void buildConstraintNoOverlap(const std::string& id, const std::vector<std::vector<XVariable*>>& origins, const std::vector<std::vector<int>>& lengths, bool zeroIgnored) override;
        void buildConstraintNoOverlap(const std::string& id, const std::vector<std::vector<XVariable*>>& origins, const std::vector<std::vector<XVariable*>>& lengths, bool zeroIgnored) override;

        void buildConstraintInstantiation(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& values) override;

        void buildConstraintClause(const std::string& id, const std::vector<XVariable*>& positive, const std::vector<XVariable*>& negative) override;

        void buildConstraintCircuit(const std::string& id, const std::vector<XVariable*>& list, int startIndex) override;
        void buildConstraintCircuit(const std::string& id, const std::vector<XVariable*>& list, int startIndex, int size) override;
        void buildConstraintCircuit(const std::string& id, const std::vector<XVariable*>& list, int startIndex, XVariable* size) override;

        void buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, const std::vector<int>& heights, XCondition& xc) override;
        void buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, const std::vector<int>& heights, XCondition& xc) override;
        void buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, const std::vector<XVariable*>& varHeights, XCondition& xc) override;
        void buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, const std::vector<XVariable*>& heights, XCondition& xc) override;
        void buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, const std::vector<int>& heights, const std::vector<XVariable*>& ends, XCondition& xc) override;
        void buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, const std::vector<XVariable*>& varHeights, const std::vector<XVariable*>& ends, XCondition& xc) override;
        void buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, const std::vector<int>& heights, const std::vector<XVariable*>& ends, XCondition& xc) override;
        void buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, const std::vector<XVariable*>& heights, const std::vector<XVariable*>& ends, XCondition& xc) override;

        void buildObjectiveMinimizeExpression(std::string expr) override;
        void buildObjectiveMaximizeExpression(std::string expr) override;

        void buildObjectiveMinimizeVariable(XVariable* x) override;
        void buildObjectiveMaximizeVariable(XVariable* x) override;

        void buildObjectiveMinimize(ExpressionObjective type, const std::vector<XVariable*>& list, const std::vector<int>& coefs) override;
        void buildObjectiveMaximize(ExpressionObjective type, const std::vector<XVariable*>& list, const std::vector<int>& coefs) override;

        void buildObjectiveMinimize(ExpressionObjective type, const std::vector<XVariable*>& list) override;
        void buildObjectiveMaximize(ExpressionObjective type, const std::vector<XVariable*>& list) override;

        void buildObjectiveMinimize(ExpressionObjective type, const std::vector<Tree*>& trees) override;
        void buildObjectiveMaximize(ExpressionObjective type, const std::vector<Tree*>& trees) override;

        void buildObjectiveMinimize(ExpressionObjective type, const std::vector<Tree*>& trees, const std::vector<int>& coefs) override;
        void buildObjectiveMaximize(ExpressionObjective type, const std::vector<Tree*>& trees, const std::vector<int>& coefs) override;
    };

} // namespace XCSP3Core

using namespace XCSP3Core;

XCSP3PrintCallbacks::XCSP3PrintCallbacks() : XCSP3CoreCallbacksBase() {}

template <class T>
void displayList(const std::vector<T>& list, std::string separator = " ") {
    for (unsigned int i = 0; i < list.size(); i++) {
        std::cout << list[i];
        if (i + 1 != list.size()) std::cout << separator;
    }
}

void displayList(const std::vector<XVariable*>& list, std::string separator = " ") {
    for (unsigned int i = 0; i < list.size(); i++) {
        std::cout << list[i]->id;
        if (i + 1 != list.size()) std::cout << separator;
    }
}

template <class T, class U>
void displayLists(const std::vector<T>& list1, const std::vector<U>& list2, std::string interleave = "*", std::string separator = " ") {
    assert(list1.size() == list2.size());
    for (unsigned int i = 0; i < list1.size(); i++) {
        std::cout << list2[i] << interleave << list1[i];
        if (i + 1 != list1.size()) std::cout << separator;
    }
}

template <class T, class U>
void displayLists(const std::vector<T*>& list1, const std::vector<U*>& list2, std::string interleave = "*", std::string separator = " ") {
    assert(list1.size() == list2.size());
    for (unsigned int i = 0; i < list1.size(); i++) {
        std::cout << *list2[i] << interleave << *list1[i];
        if (i + 1 != list1.size()) std::cout << separator;
    }
}

template <class T, class U>
void displayLists(const std::vector<T*>& list1, const std::vector<U>& list2, std::string interleave = "*", std::string separator = " ") {
    assert(list1.size() == list2.size());
    for (unsigned int i = 0; i < list1.size(); i++) {
        std::cout << list2[i] << interleave << *list1[i];
        if (i + 1 != list1.size()) std::cout << separator;
    }
}

void displayListsNoStars(const std::vector<XVariable*>& list1, const std::vector<int>& list2, std::string interleave = "*", std::string separator = " ") {
    assert(list1.size() == list2.size());
    for (unsigned int i = 0; i < list1.size(); i++) {
        if (list2[i] != STAR) {
            std::cout << list2[i] << interleave << list1[i]->id;
            if (i + 1 != list1.size()) std::cout << separator;
        }
    }
}

void XCSP3PrintCallbacks::beginInstance(InstanceType type) {
    std::cout << "// Start Instance - type=" << static_cast<int>(type) << std::endl;
    if (type == InstanceType::CSP) {
        std::cout << "   minimize 0;" << std::endl;
    }
}

void XCSP3PrintCallbacks::endInstance() {
    std::cout << "// End SAX parsing " << std::endl;
}

void XCSP3PrintCallbacks::beginVariables() {
    std::cout << "// Start variables declaration" << std::endl;
}

void XCSP3PrintCallbacks::endVariables() {
    std::cout << "// End variables declaration" << std::endl;
}

void XCSP3PrintCallbacks::beginVariableArray(const std::string& id) {
    std::cout << "//   Start array: " << id << std::endl;
}

void XCSP3PrintCallbacks::endVariableArray() {
    std::cout << "//   End array: " << std::endl;
}

void XCSP3PrintCallbacks::beginConstraints() {
    std::cout << "// Start constraints declaration" << std::endl;
}

void XCSP3PrintCallbacks::endConstraints() {
    std::cout << "// End constraints declaration" << std::endl
              << std::endl;
}

void XCSP3PrintCallbacks::beginGroup(const std::string& id) {
    std::cout << "//   Start group of constraint " << id << std::endl;
}

void XCSP3PrintCallbacks::endGroup() {
    std::cout << "//   End group of constraint" << std::endl;
}

void XCSP3PrintCallbacks::beginBlock(const std::string& classes) {
    std::cout << "//   Start block of constraint classes = " << classes << std::endl;
}

void XCSP3PrintCallbacks::endBlock() {
    std::cout << "//   End block of constraint" << std::endl;
}

void XCSP3PrintCallbacks::beginSlide(const std::string& id, bool circular) {
    (void)circular;
    std::cout << "//   Start slide " << id << std::endl;
}

void XCSP3PrintCallbacks::endSlide() {
    std::cout << "//   End slide" << std::endl;
}

void XCSP3PrintCallbacks::beginObjectives() {
    std::cout << "//   Start Objective " << std::endl;
}

void XCSP3PrintCallbacks::endObjectives() {
    std::cout << "//   End Objective " << std::endl;
}

void XCSP3PrintCallbacks::beginAnnotations() {
    std::cout << "//   Start Annotations " << std::endl;
}

void XCSP3PrintCallbacks::endAnnotations() {
    std::cout << "//   End Annotations " << std::endl;
}

void XCSP3PrintCallbacks::buildVariableInteger(const std::string& id, int minValue, int maxValue) {
    std::cout << "   " << id << " <- int(" << minValue << "," << maxValue << ");\n";
}

void XCSP3PrintCallbacks::buildVariableInteger(const std::string& id, const std::vector<int>& values) {
    auto p = std::minmax_element(values.begin(), values.end());
    if (*p.second - *p.first + 1 == static_cast<int>(values.size())) {
        buildVariableInteger(id, *p.first, *p.second);
    } else if(values.size() == 2) {
        std::cout << "   _" << id << " <- bool();\n";
        std::cout << "   " << id << " <- " << values[0] << "+ _" << id << "*" << (values[1]-values[0]) << ";\n";
    } else {
        std::vector<std::string> aliases;
        for (unsigned int i = 0; i < values.size(); ++i) {
            aliases.emplace_back("_" + id + "[" + std::to_string(i) + "]");
            buildVariableInteger(aliases[i], 0, 1);
        }
        std::cout << "   constraint sum(";
        displayList(aliases, ", ");
        std::cout << ") == 1;\n";
        std::cout << "   " << id << " <- sum(";
        displayLists(aliases, values, "*", ", ");
        std::cout << ");" << std::endl;
    }
}

void XCSP3PrintCallbacks::buildConstraintExtension(const std::string& id, const std::vector<XVariable*>& list, const std::vector<std::vector<int>>& tuples, bool support, bool hasStar) {
    (void)id;
    (void)hasStar;
    if (support) {
        std::cout << "   constraint or(" << std::endl;
        for (unsigned int i = 0; i < tuples.size(); ++i) {
            std::cout << "     and(";
            displayListsNoStars(list, tuples[i], " == ", ", ");
            std::cout << ')';
            if (i + 1 != tuples.size()) std::cout << ',';
            std::cout << '\n';
        }
        std::cout << "   );\n";
    } else {
        std::cout << "   constraint and(" << std::endl;
        for (unsigned int i = 0; i < tuples.size(); ++i) {
            std::cout << "     or(";
            displayListsNoStars(list, tuples[i], " != ", ", ");
            std::cout << ')';
            if (i + 1 != tuples.size()) std::cout << ',';
            std::cout << '\n';
        }
        std::cout << "   );\n";
    }
}

void XCSP3PrintCallbacks::buildConstraintExtension(const std::string& id, XVariable* variable, const std::vector<int>& tuples, bool support, bool hasStar) {
    (void)id;
    (void)hasStar;
    std::vector<XVariable*> list(tuples.size(), variable);
    if (support) {
        std::cout << "     and(";
        displayListsNoStars(list, tuples, " == ", ", ");
        std::cout << ");\n";
    } else {
        std::cout << "     or(";
        displayListsNoStars(list, tuples, " != ", ", ");
        std::cout << ");\n";
    }
}

// std::string id, const std::vector<XVariable *> list, bool support, bool hasStar
void XCSP3PrintCallbacks::buildConstraintExtensionAs(const std::string& id, const std::vector<XVariable*>&, bool, bool) {
    std::cout << "\n    extension constraint similar as previous one: " << id << std::endl;
    throw std::runtime_error("Constraint extension not supported yet #3");
}

void XCSP3PrintCallbacks::buildConstraintIntension(const std::string& id, std::string expr) {
    std::cout << "\n    intension constraint (using string) : " << id << " : " << expr << std::endl;
    throw std::runtime_error("String based constraint intenseion not supported");
}

void XCSP3PrintCallbacks::buildConstraintIntension(const std::string& id, Tree* tree) {
    (void)id;
    std::cout << "   constraint " << tree->toString();
    std::cout << ";\n";
}

void XCSP3PrintCallbacks::buildConstraintPrimitive(const std::string& id, OrderType op, XVariable* x, int k, XVariable* y) {
    (void)id;
    std::cout << "   constraint " << x->id << (k >= 0 ? "+" : "") << k << " " << OrderTypeToString(op) << " " << y->id << ";" << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintPrimitive(const std::string& id, OrderType op, XVariable* x, int k) {
    (void)op;
    std::cout << "\n   constraint  " << id << ":" << x->id << OrderTypeToString(op) << k << "\n";
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintPrimitive(const std::string& id, XVariable* x, bool in, int min, int max) {
    std::cout << "\n   constraint  " << id << ":" << x->id << (in ? " in " : " not in ") << min << ".." << max << "\n";
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, string start, const std::vector<string> &final, const std::vector<XTransition> &transitions
void XCSP3PrintCallbacks::buildConstraintRegular(const std::string&, const std::vector<XVariable*>& list, std::string start, const std::vector<std::string>& final, const std::vector<XTransition>& transitions) {
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
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<XTransition> &transitions
void XCSP3PrintCallbacks::buildConstraintMDD(const std::string&, const std::vector<XVariable*>& list, const std::vector<XTransition>& transitions) {
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
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintAlldifferent(const std::string& id, const std::vector<XVariable*>& list) {
    (void)id;
    std::cout << "   constraint allDifferent({";
    displayList(list, ", ");
    std::cout << "});\n";
}

void XCSP3PrintCallbacks::buildConstraintAlldifferentExcept(const std::string& id, const std::vector<XVariable*>& list, const std::vector<int>& except) {
    std::cout << "\n    allDiff constraint with exceptions" << id << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        Exceptions:";
    displayList(except);
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintAlldifferent(const std::string& id, const std::vector<Tree*>& list) {
    std::cout << "\n    allDiff constraint with expresions" << id << std::endl;
    std::cout << "        ";
    for (Tree* t : list) {
        t->prefixe();
        std::cout << " ";
    }
    std::cout << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintAlldifferentList(const std::string& id, const std::vector<std::vector<XVariable*>>& lists) {
    std::cout << "\n    allDiff list constraint" << id << std::endl;
    for (unsigned int i = 0; i < (lists.size() < 4 ? lists.size() : 3); i++) {
        std::cout << "        ";
        displayList(lists[i]);
    }
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintAlldifferentMatrix(const std::string& id, const std::vector<std::vector<XVariable*>>& matrix) {
    std::cout << "\n    allDiff matrix constraint" << id << std::endl;
    for (unsigned int i = 0; i < matrix.size(); i++) {
        std::cout << "        ";
        displayList(matrix[i]);
    }
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintAllEqual(const std::string& id, const std::vector<XVariable*>& list) {
    std::cout << "\n    allEqual constraint" << id << std::endl;
    std::cout << "        ";
    displayList(list);
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintNotAllEqual(const std::string& id, const std::vector<XVariable*>& list) {
    std::cout << "\n    not allEqual constraint" << id << std::endl;
    std::cout << "        ";
    displayList(list);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, OrderType order
void XCSP3PrintCallbacks::buildConstraintOrdered(const std::string&, const std::vector<XVariable*>& list, OrderType order) {
    std::string sep;
    if (order == OrderType::LT)
        sep = " < ";
    if (order == OrderType::LE)
        sep = " <= ";
    if (order == OrderType::GT)
        sep = " > ";
    if (order == OrderType::GE)
        sep = " >= ";
    for (unsigned int i = 1; i < list.size(); ++i) {
        std::cout << "   constraint " << *list[i - 1] << sep << *list[i] << ";" << std::endl;
    }
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> &lengths, OrderType order
void XCSP3PrintCallbacks::buildConstraintOrdered(const std::string&, const std::vector<XVariable*>& list, const std::vector<int>& lengths, OrderType order) {
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
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<std::vector<XVariable *>> &lists, OrderType order
void XCSP3PrintCallbacks::buildConstraintLex(const std::string&, const std::vector<std::vector<XVariable*>>& lists, OrderType order) {
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
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<std::vector<XVariable *>> &matrix, OrderType order
void XCSP3PrintCallbacks::buildConstraintLexMatrix(const std::string&, const std::vector<std::vector<XVariable*>>& matrix, OrderType order) {
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
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> &coeffs, XCondition &cond
void XCSP3PrintCallbacks::buildConstraintSum(const std::string&, const std::vector<XVariable*>& list, const std::vector<int>& coeffs, XCondition& cond) {
    std::cout << "   constraint ";
    for (unsigned int i = 0; i < list.size(); i++) {
        std::cout << (coeffs.size() == 0 ? 1 : coeffs[i]) << "*" << *(list[i]);
        if (i + 1 != list.size()) std::cout << " + ";
    }
    std::cout << cond << ";" << std::endl;
}

// std::string id, const std::vector<XVariable *> &list, XCondition &cond
void XCSP3PrintCallbacks::buildConstraintSum(const std::string&, const std::vector<XVariable*>& list, XCondition& cond) {
    std::cout << "   constraint ";
    displayList(list, "+");
    std::cout << cond << ";" << std::endl;
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<XVariable *> &coeffs, XCondition &cond
void XCSP3PrintCallbacks::buildConstraintSum(const std::string&, const std::vector<XVariable*>& list, const std::vector<XVariable*>& coeffs, XCondition& cond) {
    std::cout << "   constraint ";
    displayLists(list, coeffs);
    std::cout << cond << ";" << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintSum(const std::string& id, const std::vector<Tree*>& list, const std::vector<int>& coeffs, XCondition& cond) {
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
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintSum(const std::string& id, const std::vector<Tree*>& list, XCondition& cond) {
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
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, int value, int k
void XCSP3PrintCallbacks::buildConstraintAtMost(const std::string&, const std::vector<XVariable*>& list, int value, int k) {
    std::cout << "   constraint sum(";
    for (unsigned int i = 0; i < list.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << list[i]->id << " == " << value;
    }
    std::cout << ") <= " << k << ";" << std::endl;
}

// std::string id, const std::vector<XVariable *> &list, int value, int k
void XCSP3PrintCallbacks::buildConstraintAtLeast(const std::string&, const std::vector<XVariable*>& list, int value, int k) {
    std::cout << "   constraint sum(";
    for (unsigned int i = 0; i < list.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << list[i]->id << " == " << value;
    }
    std::cout << ") >= " << k << ";" << std::endl;
}

// std::string id, const std::vector<XVariable *> &list, int value, int k
void XCSP3PrintCallbacks::buildConstraintExactlyK(const std::string&, const std::vector<XVariable*>& list, int value, int k) {
    std::cout << "   constraint sum(";
    for (unsigned int i = 0; i < list.size(); ++i) {
        if (i > 0) std::cout << ", ";
        std::cout << list[i]->id << " == " << value;
    }
    std::cout << ") == " << k << ";" << std::endl;
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> &values, int k
void XCSP3PrintCallbacks::buildConstraintAmong(const std::string&, const std::vector<XVariable*>& list, const std::vector<int>& values, int k) {

    std::cout << "\n    Among constraint: k=" << k << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    throw std::runtime_error("among constraint not handled yet");
}

// std::string id, const std::vector<XVariable *> &list, int value, XVariable *x
void XCSP3PrintCallbacks::buildConstraintExactlyVariable(const std::string&, const std::vector<XVariable*>& list, int value, XVariable* x) {
    std::cout << "\n    Exactly Variable constraint: val=" << value << " variable=" << *x << std::endl;
    std::cout << "        ";
    displayList(list);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> &values, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintCount(const std::string&, const std::vector<XVariable*>& list, const std::vector<int>& values, XCondition& xc) {
    std::cout << "\n    count constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values: ";
    std::cout << "        ";
    displayList(values);
    std::cout << "        condition: " << xc << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<XVariable *> &values, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintCount(const std::string&, const std::vector<XVariable*>& list, const std::vector<XVariable*>& values, XCondition& xc) {
    std::cout << "\n    count constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values: ";
    displayList(values);
    std::cout << "        condition: " << xc << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> &except, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintNValues(const std::string&, const std::vector<XVariable*>& list, const std::vector<int>& except, XCondition& xc) {
    std::cout << "\n    NValues with exceptions constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        exceptions: ";
    displayList(except);
    std::cout << "        condition:" << xc << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintNValues(const std::string&, const std::vector<XVariable*>& list, XCondition& xc) {
    std::cout << "\n    NValues  constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        condition:" << xc << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> values, const std::vector<int> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(const std::string&, const std::vector<XVariable*>& list, const std::vector<int> values, const std::vector<int>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (int values, int occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> values, const std::vector<XVariable *> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(const std::string&, const std::vector<XVariable*>& list, const std::vector<int> values, const std::vector<XVariable*>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (int values, var occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> values, const std::vector<XInterval> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(const std::string&, const std::vector<XVariable*>& list, const std::vector<int> values, const std::vector<XInterval>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (int values, interval occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<XVariable *> values, const std::vector<int> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(const std::string&, const std::vector<XVariable*>& list, const std::vector<XVariable*> values, const std::vector<int>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (var values, int occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<XVariable *> values, const std::vector<XVariable *> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(const std::string&, const std::vector<XVariable*>& list, const std::vector<XVariable*> values, const std::vector<XVariable*>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (var values, var occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<XVariable *> values, const std::vector<XInterval> &occurs, bool closed
void XCSP3PrintCallbacks::buildConstraintCardinality(const std::string&, const std::vector<XVariable*>& list, const std::vector<XVariable*> values, const std::vector<XInterval>& occurs, bool closed) {
    std::cout << "\n    Cardinality constraint (var values, interval occurs)  constraint closed: " << closed << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    std::cout << "        occurs:";
    displayList(occurs);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMinimum(const std::string&, const std::vector<XVariable*>& list, XCondition& xc) {
    std::cout << "   constraint min(";
    displayList(list, ", ");
    std::cout << ") " << xc << ";" << std::endl;
}

// std::string id, const std::vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMinimum(const std::string&, const std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType, XCondition& xc) {
    std::cout << "\n    arg_minimum  constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        index:" << *index << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        condition: " << xc << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMaximum(const std::string&, const std::vector<XVariable*>& list, XCondition& xc) {
    std::cout << "\n    maximum  constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        condition: " << xc << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, XVariable *index, int startIndex, RankType rank, XCondition &xc
void XCSP3PrintCallbacks::buildConstraintMaximum(const std::string&, const std::vector<XVariable*>& list, XVariable* index, int startIndex, RankType, XCondition& xc) {
    std::cout << "\n    arg_maximum  constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        index:" << *index << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        condition: " << xc << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, int value
void XCSP3PrintCallbacks::buildConstraintElement(const std::string&, const std::vector<XVariable*>& list, int value) {
    std::cout << "\n    element constant constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << value << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, XVariable *value
void XCSP3PrintCallbacks::buildConstraintElement(const std::string&, const std::vector<XVariable*>& list, XVariable* value) {
    std::cout << "\n    element variable constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << *value << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, int value
void XCSP3PrintCallbacks::buildConstraintElement(const std::string&, const std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType, int value) {
    std::cout << "\n    element constant (with index) constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << value << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        index : " << *index << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintElement(const std::string& id, const std::vector<std::vector<int>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, XVariable* value) {
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
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, int startIndex, XVariable *index, RankType rank, XVariable *value
void XCSP3PrintCallbacks::buildConstraintElement(const std::string&, const std::vector<XVariable*>& list, int startIndex, XVariable* index, RankType, XVariable* value) {
    std::cout << "\n    element variable (with index) constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << *value << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        index : " << *index << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// string, const std::vector<int> &list, int startIndex, XVariable *index, RankType rank, XVariable *value
void XCSP3PrintCallbacks::buildConstraintElement(const std::string&, const std::vector<int>& list, int startIndex, XVariable* index, RankType, XVariable* value) {
    std::cout << "\n    element variable with list of integers (with index) constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << *value << std::endl;
    std::cout << "        Start index : " << startIndex << std::endl;
    std::cout << "        index : " << *index << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, int startIndex
void XCSP3PrintCallbacks::buildConstraintChannel(const std::string&, const std::vector<XVariable*>& list, int startIndex) {
    std::cout << "\n    channel constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        Start index : " << startIndex << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list1, int startIndex1, const std::vector<XVariable *> &list2, int startIndex2
void XCSP3PrintCallbacks::buildConstraintChannel(const std::string&, const std::vector<XVariable*>& list1, int, const std::vector<XVariable*>& list2, int) {
    std::cout << "\n    channel constraint" << std::endl;
    std::cout << "        list1 ";
    displayList(list1);
    std::cout << "        list2 ";
    displayList(list2);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, int startIndex, XVariable *value
void XCSP3PrintCallbacks::buildConstraintChannel(const std::string&, const std::vector<XVariable*>& list, int, XVariable* value) {
    std::cout << "\n    channel constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        value: " << *value << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> &values, const std::vector<XInterval> &widths
void XCSP3PrintCallbacks::buildConstraintStretch(const std::string&, const std::vector<XVariable*>& list, const std::vector<int>& values, const std::vector<XInterval>& widths) {
    std::cout << "\n    stretch constraint" << std::endl;
    std::cout << "        ";
    displayList(list);
    std::cout << "        values :";
    displayList(values);
    std::cout << "        widths:";
    displayList(widths);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> &values, const std::vector<XInterval> &widths, const std::vector<std::vector<int>> &patterns
void XCSP3PrintCallbacks::buildConstraintStretch(const std::string&, const std::vector<XVariable*>& list, const std::vector<int>& values, const std::vector<XInterval>& widths, const std::vector<std::vector<int>>& patterns) {
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
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &origins, const std::vector<int> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(const std::string&, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, bool) {
    std::cout << "\n    nooverlap constraint" << std::endl;
    std::cout << "        origins";
    displayList(origins);
    std::cout << "        lengths";
    displayList(lengths);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &origins, const std::vector<XVariable *> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(const std::string&, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, bool) {
    std::cout << "\n    nooverlap constraint" << std::endl;
    std::cout << "        origins:";
    displayList(origins);
    std::cout << "        lengths";
    displayList(lengths);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<std::vector<XVariable *>> &origins, const std::vector<std::vector<int>> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(const std::string&, const std::vector<std::vector<XVariable*>>& origins, const std::vector<std::vector<int>>& lengths, bool) {
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
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<std::vector<XVariable *>> &origins, const std::vector<std::vector<XVariable *>> &lengths, bool zeroIgnored
void XCSP3PrintCallbacks::buildConstraintNoOverlap(const std::string&, const std::vector<std::vector<XVariable*>>& origins, const std::vector<std::vector<XVariable*>>& lengths, bool) {
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
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> &values
void XCSP3PrintCallbacks::buildConstraintInstantiation(const std::string&, const std::vector<XVariable*>& list, const std::vector<int>& values) {
    std::cout << "\n    instantiation constraint" << std::endl;
    std::cout << "        list:";
    displayList(list);
    std::cout << "        values:";
    displayList(values);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, const std::vector<int> &values
void XCSP3PrintCallbacks::buildConstraintClause(const std::string&, const std::vector<XVariable*>& positive, const std::vector<XVariable*>& negative) {
    std::cout << "\n    Clause constraint" << std::endl;
    std::cout << "        positive lits size:" << positive.size() << " ";
    displayList(positive);
    std::cout << "        negative lits size:" << negative.size() << " ";
    displayList(negative);
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, int startIndex
void XCSP3PrintCallbacks::buildConstraintCircuit(const std::string&, const std::vector<XVariable*>& list, int startIndex) {
    std::cout << "\n    circuit constraint" << std::endl;
    std::cout << "        list:";
    displayList(list);
    std::cout << "        startIndex:" << startIndex << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, int startIndex, int size
void XCSP3PrintCallbacks::buildConstraintCircuit(const std::string&, const std::vector<XVariable*>& list, int startIndex, int size) {
    std::cout << "\n    circuit constraint" << std::endl;
    std::cout << "        list:";
    displayList(list);
    std::cout << "        startIndex:" << startIndex << std::endl;
    std::cout << "        size: " << size << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

// std::string id, const std::vector<XVariable *> &list, int startIndex, XVariable *size
void XCSP3PrintCallbacks::buildConstraintCircuit(const std::string&, const std::vector<XVariable*>& list, int startIndex, XVariable* size) {
    std::cout << "\n    circuit constraint" << std::endl;
    std::cout << "        list:";
    displayList(list);
    std::cout << "        startIndex:" << startIndex << std::endl;
    std::cout << "        size: " << size->id << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildObjectiveMinimizeExpression(std::string expr) {
    std::cout << "\n    objective: minimize" << expr << std::endl;
    throw std::runtime_error("minimize with string not yet handled");
}

void XCSP3PrintCallbacks::buildObjectiveMaximizeExpression(std::string expr) {
    std::cout << "\n    objective: maximize" << expr << std::endl;
    throw std::runtime_error("maximize with string not yet handled");
}

void XCSP3PrintCallbacks::buildObjectiveMinimizeVariable(XVariable* x) {
    std::cout << "   minimize " << x->id << ";" << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMaximizeVariable(XVariable* x) {
    std::cout << "   maximize " << x->id << ";" << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMinimize(ExpressionObjective type, const std::vector<XVariable*>& list, const std::vector<int>& coefs) {
    std::cout << "   minimize " << ExpressionObjectiveToString(type) << "(";
    displayLists(list, coefs, "*", ", ");
    std::cout << ");" << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMaximize(ExpressionObjective type, const std::vector<XVariable*>& list, const std::vector<int>& coefs) {
    std::cout << "   maximize " << ExpressionObjectiveToString(type) << "(";
    displayLists(list, coefs, "*", ", ");
    std::cout << ");" << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMinimize(ExpressionObjective type, const std::vector<XVariable*>& list) {
    std::cout << "   minimize " << ExpressionObjectiveToString(type) << "(";
    displayList(list, ", ");
    std::cout << ");" << std::endl;
}

void XCSP3PrintCallbacks::buildObjectiveMaximize(ExpressionObjective type, const std::vector<XVariable*>& list) {
    std::cout << "   maximize " << ExpressionObjectiveToString(type) << "(";
    displayList(list, ", ");
    std::cout << ");" << std::endl;
}

void XCSP3PrintCallbacks::buildAnnotationDecision(std::vector<XVariable*>& list) {
    std::cout << "       decision variables" << std::endl
              << "       ";
    displayList(list);
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintTrue(const std::string& id) {
    (void)id;
}

void XCSP3PrintCallbacks::buildConstraintFalse(const std::string& id) {
    (void)id;
}

void XCSP3PrintCallbacks::buildConstraintMult(const std::string& id, XVariable* x, XVariable* y, XVariable* z) {
    (void)id;
    std::cout << "   constraint " << z->id << " == " << x->id << "*" << y->id << ";" << std::endl;
}

void XCSP3PrintCallbacks::buildConstraintMinimum(const std::string& id, const std::vector<Tree*>& list, XCondition& xc) {
    (void)id;
    (void)list;
    (void)xc;
    throw std::runtime_error("minimum constraint over trees is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintMaximum(const std::string& id, const std::vector<Tree*>& list, XCondition& xc) {
    (void)id;
    (void)list;
    (void)xc;
    throw std::runtime_error("maximum constraint over trees is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintElement(const std::string& id, const std::vector<std::vector<XVariable*>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, XVariable* value) {
    (void)id;
    (void)matrix;
    (void)startRowIndex;
    (void)rowIndex;
    (void)startColIndex;
    (void)colIndex;
    (void)value;
    throw std::runtime_error("Element matrix constraint is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintElement(const std::string& id, const std::vector<std::vector<XVariable*>>& matrix, int startRowIndex, XVariable* rowIndex, int startColIndex, XVariable* colIndex, int value) {
    (void)id;
    (void)matrix;
    (void)startRowIndex;
    (void)rowIndex;
    (void)startColIndex;
    (void)colIndex;
    (void)value;
    throw std::runtime_error("Element matrix constraint is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, const std::vector<int>& heights, XCondition& xc) {
    (void)id;
    (void)origins;
    (void)lengths;
    (void)heights;
    (void)xc;
    std::cout << "Cumulative\n";
    std::cout << "Origins : ";
    displayList(origins);
    std::cout << "Lengths : ";
    displayList(lengths);
    std::cout << "heights : ";
    displayList(heights);
    std::cout << "Condition : " << xc << std::endl;
    throw std::runtime_error("Constraint not supported yet");
}

void XCSP3PrintCallbacks::buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, const std::vector<int>& heights, XCondition& xc) {
    (void)id;
    (void)origins;
    (void)lengths;
    (void)heights;
    (void)xc;
    throw std::runtime_error("cumulative (var lengths, int heights) constraint is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, const std::vector<XVariable*>& varHeights, XCondition& xc) {
    (void)id;
    (void)origins;
    (void)lengths;
    (void)varHeights;
    (void)xc;
    throw std::runtime_error("cumulative (int lengths, var heights) constraint is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, const std::vector<XVariable*>& heights, XCondition& xc) {
    (void)id;
    (void)origins;
    (void)lengths;
    (void)heights;
    (void)xc;
    throw std::runtime_error("cumulative (var lengths, var heights) constraint is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, const std::vector<int>& heights, const std::vector<XVariable*>& ends, XCondition& xc) {
    (void)id;
    (void)origins;
    (void)lengths;
    (void)heights;
    (void)ends;
    (void)xc;
    throw std::runtime_error("cumulative (int lengths, int heights) constraint is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<int>& lengths, const std::vector<XVariable*>& varHeights, const std::vector<XVariable*>& ends, XCondition& xc) {
    (void)id;
    (void)origins;
    (void)lengths;
    (void)varHeights;
    (void)ends;
    (void)xc;
    throw std::runtime_error("cumulative (int lengths, var heights, ends) constraint is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, const std::vector<int>& heights, const std::vector<XVariable*>& ends, XCondition& xc) {
    (void)id;
    (void)origins;
    (void)lengths;
    (void)heights;
    (void)ends;
    (void)xc;
    throw std::runtime_error("cumulative (var lengths, int heights, ends) constraint is not yet supported");
}

void XCSP3PrintCallbacks::buildConstraintCumulative(const std::string& id, const std::vector<XVariable*>& origins, const std::vector<XVariable*>& lengths, const std::vector<XVariable*>& heights, const std::vector<XVariable*>& ends, XCondition& xc) {
    (void)id;
    (void)origins;
    (void)lengths;
    (void)heights;
    (void)ends;
    (void)xc;
    throw std::runtime_error("cumulative (var lengths, var heights, ends) constraint is not yet supported");
}

void XCSP3PrintCallbacks::buildObjectiveMinimize(ExpressionObjective type, const std::vector<Tree*>& trees, const std::vector<int>& coefs) {
    (void)type;
    (void)trees;
    (void)coefs;
    throw std::runtime_error("minimize objective sum with expression  not yet supported");
}

void XCSP3PrintCallbacks::buildObjectiveMaximize(ExpressionObjective type, const std::vector<Tree*>& trees, const std::vector<int>& coefs) {
    (void)type;
    (void)trees;
    (void)coefs;
    throw std::runtime_error("maximize objective with expression  not yet supported");
}

void XCSP3PrintCallbacks::buildObjectiveMinimize(ExpressionObjective type, const std::vector<Tree*>& trees) {
    (void)type;
    (void)trees;
    throw std::runtime_error("minimize objective with expression  not yet supported");
}

void XCSP3PrintCallbacks::buildObjectiveMaximize(ExpressionObjective type, const std::vector<Tree*>& trees) {
    (void)type;
    (void)trees;
    throw std::runtime_error("maximize objective with expression not yet supported");
}

#endif //COSOCO_XCSP3PRINTCALLBACKS_H

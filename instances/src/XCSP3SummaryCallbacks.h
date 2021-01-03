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
 * furnished to do so, subject to the followingitions:
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
#ifndef COSOCO_XCSP3SummaryCallbacks_H
#define COSOCO_XCSP3SummaryCallbacks_H

#include "XCSP3CoreCallbacks.h"
#include "XCSP3Variable.h"
#include <XCSP3Tree.h>
/**
 * This is an example that prints useful informations of a XCSP3 instance.
 * You need to create your own class and to override functions of the callback.
 * We suggest to make a map between XVariable and your owns in to
 * facilitate the constructions of constraints.
 *
 * see main.cc to show declaration of the parser
 *
 */

namespace XCSP3Core {

    class XCSP3SummaryCallbacks : public XCSP3CoreCallbacksBase {
    public:
        int nbv, nbc;
        std::string minmax, type;

        XCSP3SummaryCallbacks();

        virtual void beginInstance(InstanceType type) override;
        virtual void endInstance() override;
        virtual void beginVariables() override;
        virtual void endVariables() override;
        virtual void beginVariableArray(const std::string&) override;
        virtual void endVariableArray() override;
        virtual void beginConstraints() override;
        virtual void endConstraints() override;
        virtual void beginGroup(const std::string&) override;
        virtual void endGroup() override;
        virtual void beginBlock(const std::string& classes) override;
        virtual void endBlock() override;
        virtual void beginSlide(const std::string&, bool circular) override;
        virtual void endSlide() override;
        virtual void beginObjectives() override;
        virtual void endObjectives() override;
        virtual void beginAnnotations() override;
        virtual void endAnnotations() override;
        virtual void buildVariableInteger(const std::string&, int minValue, int maxValue) override;
        virtual void buildVariableInteger(const std::string&, std::vector<int>&) override;
        virtual void buildConstraintExtension(const std::string&, std::vector<XVariable*> list, std::vector<std::vector<int>>&, bool, bool) override;
        virtual void buildConstraintExtension(const std::string&, XVariable*, std::vector<int>&, bool, bool) override;
        virtual void buildConstraintExtensionAs(const std::string&, std::vector<XVariable*> list, bool, bool) override;
        virtual void buildConstraintIntension(const std::string&, std::string) override;
        virtual void buildConstraintIntension(const std::string&, Tree*) override;
        virtual void buildConstraintPrimitive(const std::string&, OrderType, XVariable*, int, XVariable*) override;
        virtual void buildConstraintPrimitive(const std::string&, OrderType, XVariable*, int) override;
        virtual void buildConstraintPrimitive(const std::string&, XVariable*, bool in, int min, int max) override;
        virtual void buildConstraintRegular(const std::string&, std::vector<XVariable*>&, std::string st, std::vector<std::string>& final, std::vector<XTransition>&) override;
        virtual void buildConstraintMDD(const std::string&, std::vector<XVariable*>&, std::vector<XTransition>&) override;
        virtual void buildConstraintAlldifferent(const std::string&, std::vector<XVariable*>&) override;
        virtual void buildConstraintAlldifferentExcept(const std::string&, std::vector<XVariable*>&, std::vector<int>&) override;
        virtual void buildConstraintAlldifferent(const std::string&, std::vector<Tree*>&) override;
        virtual void buildConstraintAlldifferentList(const std::string&, std::vector<std::vector<XVariable*>>&) override;
        virtual void buildConstraintAlldifferentMatrix(const std::string&, std::vector<std::vector<XVariable*>>&) override;
        virtual void buildConstraintAllEqual(const std::string&, std::vector<XVariable*>&) override;
        virtual void buildConstraintNotAllEqual(const std::string&, std::vector<XVariable*>&) override;
        virtual void buildConstraintOrdered(const std::string&, std::vector<XVariable*>&, OrderType) override;
        virtual void buildConstraintOrdered(const std::string&, std::vector<XVariable*>&, std::vector<int>&, OrderType) override;
        virtual void buildConstraintLex(const std::string&, std::vector<std::vector<XVariable*>>&, OrderType) override;
        virtual void buildConstraintLexMatrix(const std::string&, std::vector<std::vector<XVariable*>>&, OrderType) override;
        virtual void buildConstraintSum(const std::string&, std::vector<XVariable*>&, std::vector<int>&, XCondition&) override;
        virtual void buildConstraintSum(const std::string&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintSum(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintSum(const std::string&, std::vector<Tree*>&, std::vector<int>&, XCondition&) override;
        virtual void buildConstraintSum(const std::string&, std::vector<Tree*>&, XCondition&) override;
        virtual void buildConstraintAtMost(const std::string&, std::vector<XVariable*>&, int, int) override;
        virtual void buildConstraintAtLeast(const std::string&, std::vector<XVariable*>&, int, int) override;
        virtual void buildConstraintExactlyK(const std::string&, std::vector<XVariable*>&, int, int) override;
        virtual void buildConstraintAmong(const std::string&, std::vector<XVariable*>&, std::vector<int>&, int) override;
        virtual void buildConstraintExactlyVariable(const std::string&, std::vector<XVariable*>&, int, XVariable*) override;
        virtual void buildConstraintCount(const std::string&, std::vector<XVariable*>&, std::vector<int>&, XCondition&) override;
        virtual void buildConstraintCount(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintNValues(const std::string&, std::vector<XVariable*>&, std::vector<int>&, XCondition&) override;
        virtual void buildConstraintNValues(const std::string&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<int>, std::vector<int>&, bool) override;
        virtual void buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<int>, std::vector<XVariable*>&, bool) override;
        virtual void buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<int>, std::vector<XInterval>&, bool) override;
        virtual void buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>, std::vector<int>&, bool) override;
        virtual void buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>, std::vector<XVariable*>&, bool) override;
        virtual void buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>, std::vector<XInterval>&, bool) override;
        virtual void buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<int>&, std::vector<int>&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintMinimum(const std::string&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintMinimum(const std::string&, std::vector<XVariable*>&, XVariable*, int, RankType, XCondition&) override;
        virtual void buildConstraintMaximum(const std::string&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintMaximum(const std::string&, std::vector<XVariable*>&, XVariable*, int, RankType, XCondition&) override;
        virtual void buildConstraintElement(const std::string&, std::vector<XVariable*>&, int) override;
        virtual void buildConstraintElement(const std::string&, std::vector<XVariable*>&, XVariable*) override;
        virtual void buildConstraintElement(const std::string&, std::vector<XVariable*>&, int, XVariable*, RankType, int) override;
        virtual void buildConstraintElement(const std::string&, std::vector<XVariable*>&, int, XVariable*, RankType, XVariable*) override;
        virtual void buildConstraintElement(const std::string&, std::vector<int>&, int, XVariable*, RankType, XVariable*) override;
        virtual void buildConstraintElement(const std::string&, std::vector<std::vector<int>>&, int, XVariable*, int, XVariable*, XVariable*) override;
        virtual void buildConstraintChannel(const std::string&, std::vector<XVariable*>&, int) override;
        virtual void buildConstraintChannel(const std::string&, std::vector<XVariable*>&, int, std::vector<XVariable*>&, int) override;
        virtual void buildConstraintChannel(const std::string&, std::vector<XVariable*>&, int, XVariable*) override;
        virtual void buildConstraintStretch(const std::string&, std::vector<XVariable*>&, std::vector<int>&, std::vector<XInterval>&) override;
        virtual void buildConstraintStretch(const std::string&, std::vector<XVariable*>&, std::vector<int>&, std::vector<XInterval>&, std::vector<std::vector<int>>&) override;
        virtual void buildConstraintNoOverlap(const std::string&, std::vector<XVariable*>& , std::vector<int>&, bool) override;
        virtual void buildConstraintNoOverlap(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, bool) override;
        virtual void buildConstraintNoOverlap(const std::string&, std::vector<std::vector<XVariable*>>& , std::vector<std::vector<int>>&, bool) override;
        virtual void buildConstraintNoOverlap(const std::string&, std::vector<std::vector<XVariable*>>& , std::vector<std::vector<XVariable*>>&, bool) override;
        virtual void buildConstraintInstantiation(const std::string&, std::vector<XVariable*>&, std::vector<int>&) override;
        virtual void buildConstraintClause(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>&) override;
        virtual void buildConstraintCircuit(const std::string&, std::vector<XVariable*>&, int) override;
        virtual void buildConstraintCircuit(const std::string&, std::vector<XVariable*>&, int, int size) override;
        virtual void buildConstraintCircuit(const std::string&, std::vector<XVariable*>&, int, XVariable* size) override;
        virtual void buildObjectiveMinimizeExpression(std::string) override;
        virtual void buildObjectiveMaximizeExpression(std::string) override;
        virtual void buildObjectiveMinimizeVariable(XVariable*) override;
        virtual void buildObjectiveMaximizeVariable(XVariable*) override;
        virtual void buildObjectiveMinimize(ExpressionObjective, std::vector<XVariable*>&, std::vector<int>& ) override;
        virtual void buildObjectiveMaximize(ExpressionObjective, std::vector<XVariable*>&, std::vector<int>& ) override;
        virtual void buildObjectiveMinimize(ExpressionObjective, std::vector<XVariable*>&) override;
        virtual void buildObjectiveMaximize(ExpressionObjective, std::vector<XVariable*>&) override;
        virtual void buildAnnotationDecision(std::vector<XVariable*>&) override;
        virtual void buildConstraintTrue(const std::string&) override;
        virtual void buildConstraintFalse(const std::string&) override;
        virtual void buildConstraintMult(const std::string&, XVariable*, XVariable*, XVariable*) override;
        virtual void buildConstraintMinimum(const std::string&, std::vector<Tree*>&, XCondition&) override;
        virtual void buildConstraintMaximum(const std::string&, std::vector<Tree*>&, XCondition&) override;
        virtual void buildConstraintElement(const std::string&, std::vector<std::vector<XVariable*>>&, int, XVariable*, int, XVariable*, XVariable*) override;
        virtual void buildConstraintElement(const std::string&, std::vector<std::vector<XVariable*>>&, int, XVariable*, int, XVariable*, int) override;
        virtual void buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<int>&, std::vector<int>&, XCondition&) override;
        virtual void buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<int>&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, std::vector<int>&, XCondition&) override;
        virtual void buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<int>&, std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, std::vector<int>&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) override;
        virtual void buildObjectiveMinimize(ExpressionObjective, std::vector<Tree*>&, std::vector<int>& ) override;
        virtual void buildObjectiveMaximize(ExpressionObjective, std::vector<Tree*>&, std::vector<int>& ) override;
        virtual void buildObjectiveMinimize(ExpressionObjective, std::vector<Tree*>&) override;
        virtual void buildObjectiveMaximize(ExpressionObjective, std::vector<Tree*>&) override;
        bool canonize;
    };

} // namespace XCSP3Core

using namespace XCSP3Core;

XCSP3SummaryCallbacks::XCSP3SummaryCallbacks() : XCSP3CoreCallbacksBase(), canonize(true) {
    nbv = 0;
    nbc = 0;
}

void XCSP3SummaryCallbacks::beginInstance(InstanceType _type) {
    if (_type == InstanceType::CSP) {
        minmax = "";
        type = "";
    }
}

void XCSP3SummaryCallbacks::endInstance() {
    std::cout << nbv << "," << nbc << "," << minmax << "," << type << std::endl;
}

void XCSP3SummaryCallbacks::beginVariables() {
}

void XCSP3SummaryCallbacks::endVariables() {
}

void XCSP3SummaryCallbacks::beginVariableArray(const std::string&) {
}

void XCSP3SummaryCallbacks::endVariableArray() {
}

void XCSP3SummaryCallbacks::beginConstraints() {
}

void XCSP3SummaryCallbacks::endConstraints() {
}

void XCSP3SummaryCallbacks::beginGroup(const std::string&) {
}

void XCSP3SummaryCallbacks::endGroup() {
}

void XCSP3SummaryCallbacks::beginBlock(const std::string&) {
}

void XCSP3SummaryCallbacks::endBlock() {
}

// const std::string&, bool circular
void XCSP3SummaryCallbacks::beginSlide(const std::string&, bool) {
}

void XCSP3SummaryCallbacks::endSlide() {
}

void XCSP3SummaryCallbacks::beginObjectives() {
}

void XCSP3SummaryCallbacks::endObjectives() {
}

void XCSP3SummaryCallbacks::beginAnnotations() {
}

void XCSP3SummaryCallbacks::endAnnotations() {
}

void XCSP3SummaryCallbacks::buildVariableInteger(const std::string&, int, int) {
    nbv++;
}

void XCSP3SummaryCallbacks::buildVariableInteger(const std::string&, std::vector<int>&) {
    nbv++;
}

void XCSP3SummaryCallbacks::buildConstraintExtension(const std::string&, std::vector<XVariable*>, std::vector<std::vector<int>>&, bool, bool) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintExtension(const std::string&, XVariable*, std::vector<int>&, bool, bool) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> list, bool, bool
void XCSP3SummaryCallbacks::buildConstraintExtensionAs(const std::string&, std::vector<XVariable*>, bool, bool) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintIntension(const std::string&, std::string) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintIntension(const std::string&, Tree*) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintPrimitive(const std::string&, OrderType, XVariable*, int, XVariable*) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintPrimitive(const std::string&, OrderType, XVariable*, int) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintPrimitive(const std::string&, XVariable*, bool, int, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, const std::string& start, std::vector<const std::string&> &final, std::vector<XTransition> &transitions
void XCSP3SummaryCallbacks::buildConstraintRegular(const std::string&, std::vector<XVariable*>&, std::string, std::vector<std::string>&, std::vector<XTransition>&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<XTransition> &transitions
void XCSP3SummaryCallbacks::buildConstraintMDD(const std::string&, std::vector<XVariable*>&, std::vector<XTransition>&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintAlldifferent(const std::string&, std::vector<XVariable*>&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintAlldifferentExcept(const std::string&, std::vector<XVariable*>&, std::vector<int>&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintAlldifferent(const std::string&, std::vector<Tree*>&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintAlldifferentList(const std::string&, std::vector<std::vector<XVariable*>>&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintAlldifferentMatrix(const std::string&, std::vector<std::vector<XVariable*>>&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintAllEqual(const std::string&, std::vector<XVariable*>&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintNotAllEqual(const std::string&, std::vector<XVariable*>&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, OrderType
void XCSP3SummaryCallbacks::buildConstraintOrdered(const std::string&, std::vector<XVariable*>&, OrderType) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int> &lengths, OrderType
void XCSP3SummaryCallbacks::buildConstraintOrdered(const std::string&, std::vector<XVariable*>&, std::vector<int>&, OrderType) {
    nbc++;
}

// const std::string&, std::vector<std::vector<XVariable *>> &lists, OrderType
void XCSP3SummaryCallbacks::buildConstraintLex(const std::string&, std::vector<std::vector<XVariable*>>&, OrderType) {
    nbc++;
}

// const std::string&, std::vector<std::vector<XVariable *>> &matrix, OrderType
void XCSP3SummaryCallbacks::buildConstraintLexMatrix(const std::string&, std::vector<std::vector<XVariable*>>&, OrderType) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int> &coeffs, XCondition &cond
void XCSP3SummaryCallbacks::buildConstraintSum(const std::string&, std::vector<XVariable*>&, std::vector<int>&, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, XCondition &cond
void XCSP3SummaryCallbacks::buildConstraintSum(const std::string&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<XVariable *> &coeffs, XCondition &cond
void XCSP3SummaryCallbacks::buildConstraintSum(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintSum(const std::string&, std::vector<Tree*>&, std::vector<int>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintSum(const std::string&, std::vector<Tree*>&, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int, int
void XCSP3SummaryCallbacks::buildConstraintAtMost(const std::string&, std::vector<XVariable*>&, int, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int, int
void XCSP3SummaryCallbacks::buildConstraintAtLeast(const std::string&, std::vector<XVariable*>&, int, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int, int
void XCSP3SummaryCallbacks::buildConstraintExactlyK(const std::string&, std::vector<XVariable*>&, int, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int> &values, int
void XCSP3SummaryCallbacks::buildConstraintAmong(const std::string&, std::vector<XVariable*>&, std::vector<int>&, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int, XVariable *x
void XCSP3SummaryCallbacks::buildConstraintExactlyVariable(const std::string&, std::vector<XVariable*>&, int, XVariable*) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int> &values, XCondition &xc
void XCSP3SummaryCallbacks::buildConstraintCount(const std::string&, std::vector<XVariable*>&, std::vector<int>&, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<XVariable *> &values, XCondition &xc
void XCSP3SummaryCallbacks::buildConstraintCount(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int> &except, XCondition &xc
void XCSP3SummaryCallbacks::buildConstraintNValues(const std::string&, std::vector<XVariable*>&, std::vector<int>&, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, XCondition &xc
void XCSP3SummaryCallbacks::buildConstraintNValues(const std::string&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int>, std::vector<int> &occurs, bool
void XCSP3SummaryCallbacks::buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<int>, std::vector<int>&, bool) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int>, std::vector<XVariable *> &occurs, bool
void XCSP3SummaryCallbacks::buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<int>, std::vector<XVariable*>&, bool) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int>, std::vector<XInterval> &occurs, bool
void XCSP3SummaryCallbacks::buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<int>, std::vector<XInterval>&, bool) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<XVariable *>, std::vector<int> &occurs, bool
void XCSP3SummaryCallbacks::buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>, std::vector<int>&, bool) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<XVariable *>, std::vector<XVariable *> &occurs, bool
void XCSP3SummaryCallbacks::buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>, std::vector<XVariable*>&, bool) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<XVariable *>, std::vector<XInterval> &occurs, bool
void XCSP3SummaryCallbacks::buildConstraintCardinality(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>, std::vector<XInterval>&, bool) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, XCondition &xc
void XCSP3SummaryCallbacks::buildConstraintMinimum(const std::string&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, XVariable *index, int, RankType, XCondition &xc
void XCSP3SummaryCallbacks::buildConstraintMinimum(const std::string&, std::vector<XVariable*>&, XVariable*, int, RankType, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, XCondition &xc
void XCSP3SummaryCallbacks::buildConstraintMaximum(const std::string&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, XVariable *index, int, RankType, XCondition &xc
void XCSP3SummaryCallbacks::buildConstraintMaximum(const std::string&, std::vector<XVariable*>&, XVariable*, int, RankType, XCondition&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int
void XCSP3SummaryCallbacks::buildConstraintElement(const std::string&, std::vector<XVariable*>&, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, XVariable *value
void XCSP3SummaryCallbacks::buildConstraintElement(const std::string&, std::vector<XVariable*>&, XVariable*) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int, XVariable *index, RankType, int
void XCSP3SummaryCallbacks::buildConstraintElement(const std::string&, std::vector<XVariable*>&, int, XVariable*, RankType, int) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintElement(const std::string&, std::vector<std::vector<int>>&, int, XVariable*, int, XVariable*, XVariable*) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int, XVariable *index, RankType, XVariable *value
void XCSP3SummaryCallbacks::buildConstraintElement(const std::string&, std::vector<XVariable*>&, int, XVariable*, RankType, XVariable*) {
    nbc++;
}

// const std::string&, std::vector<int> &list, int, XVariable *index, RankType, XVariable *value
void XCSP3SummaryCallbacks::buildConstraintElement(const std::string&, std::vector<int>&, int, XVariable*, RankType, XVariable*) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int
void XCSP3SummaryCallbacks::buildConstraintChannel(const std::string&, std::vector<XVariable*>&, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list1, int1, std::vector<XVariable *> &list2, int2
void XCSP3SummaryCallbacks::buildConstraintChannel(const std::string&, std::vector<XVariable*>&, int, std::vector<XVariable*>&, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int, XVariable *value
void XCSP3SummaryCallbacks::buildConstraintChannel(const std::string&, std::vector<XVariable*>&, int, XVariable*) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int> &values, std::vector<XInterval> &widths
void XCSP3SummaryCallbacks::buildConstraintStretch(const std::string&, std::vector<XVariable*>&, std::vector<int>&, std::vector<XInterval>&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int> &values, std::vector<XInterval> &widths, std::vector<std::vector<int>> &patterns
void XCSP3SummaryCallbacks::buildConstraintStretch(const std::string&, std::vector<XVariable*>&, std::vector<int>&, std::vector<XInterval>&, std::vector<std::vector<int>>&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &, std::vector<int> &lengths, bool
void XCSP3SummaryCallbacks::buildConstraintNoOverlap(const std::string&, std::vector<XVariable*>& , std::vector<int>&, bool) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &, std::vector<XVariable *> &lengths, bool
void XCSP3SummaryCallbacks::buildConstraintNoOverlap(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, bool) {
    nbc++;
}

// const std::string&, std::vector<std::vector<XVariable *>> &, std::vector<std::vector<int>> &lengths, bool
void XCSP3SummaryCallbacks::buildConstraintNoOverlap(const std::string&, std::vector<std::vector<XVariable*>>& , std::vector<std::vector<int>>&, bool) {
    nbc++;
}

// const std::string&, std::vector<std::vector<XVariable *>> &, std::vector<std::vector<XVariable *>> &lengths, bool
void XCSP3SummaryCallbacks::buildConstraintNoOverlap(const std::string&, std::vector<std::vector<XVariable*>>& , std::vector<std::vector<XVariable*>>&, bool) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int> &values
void XCSP3SummaryCallbacks::buildConstraintInstantiation(const std::string&, std::vector<XVariable*>&, std::vector<int>&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, std::vector<int> &values
void XCSP3SummaryCallbacks::buildConstraintClause(const std::string&, std::vector<XVariable*>&, std::vector<XVariable*>&) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int
void XCSP3SummaryCallbacks::buildConstraintCircuit(const std::string&, std::vector<XVariable*>&, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int, int size
void XCSP3SummaryCallbacks::buildConstraintCircuit(const std::string&, std::vector<XVariable*>&, int, int) {
    nbc++;
}

// const std::string&, std::vector<XVariable *> &list, int, XVariable *size
void XCSP3SummaryCallbacks::buildConstraintCircuit(const std::string&, std::vector<XVariable*>&, int, XVariable*) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildObjectiveMinimizeExpression(std::string expr) {
    type = expr;
    minmax = "Minimize";
}

void XCSP3SummaryCallbacks::buildObjectiveMaximizeExpression(std::string expr) {
    type = expr;
    minmax = "Maximize";
}

void XCSP3SummaryCallbacks::buildObjectiveMinimizeVariable(XVariable*) {
    type = "variable";
    minmax = "Minimize";
}

void XCSP3SummaryCallbacks::buildObjectiveMaximizeVariable(XVariable*) {
    type = "variable";
    minmax = "Maximize";
}

void XCSP3SummaryCallbacks::buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<int>&, std::vector<int>&, std::vector<XVariable*>&, XCondition&) { 
    nbc++;
}

void buildObj(ExpressionObjective _type, std::string _minmax, std::string& type, std::string& minmax) {
    minmax = _minmax;
    switch (_type) {
    case ExpressionObjective::SUM_O:
        type = "sum";
        break;
    case ExpressionObjective::PRODUCT_O:
        type = "product";
        break;
    case ExpressionObjective::MINIMUM_O:
        type = "minimum";
        break;
    case ExpressionObjective::MAXIMUM_O:
        type = "maximum";
        break;
    case ExpressionObjective::NVALUES_O:
        type = "nvalues";
        break;
    case ExpressionObjective::LEX_O:
        type = "lex";
        break;
    case ExpressionObjective::EXPRESSION_O:
        type = "expr";
        break;
    }
}

void XCSP3SummaryCallbacks::buildObjectiveMinimize(ExpressionObjective _type, std::vector<XVariable*>&, std::vector<int>& ) {
    buildObj(_type, "Minimize", type, minmax);
}

void XCSP3SummaryCallbacks::buildObjectiveMaximize(ExpressionObjective _type, std::vector<XVariable*>&, std::vector<int>& ) {
    buildObj(_type, "Maximize", type, minmax);
}

void XCSP3SummaryCallbacks::buildObjectiveMinimize(ExpressionObjective _type, std::vector<XVariable*>&) {
    buildObj(_type, "Minimize", type, minmax);
}

void XCSP3SummaryCallbacks::buildObjectiveMaximize(ExpressionObjective _type, std::vector<XVariable*>&) {
    buildObj(_type, "Maximize", type, minmax);
}

void XCSP3SummaryCallbacks::buildConstraintTrue(const std::string&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintFalse(const std::string&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintMult(const std::string&, XVariable*, XVariable*, XVariable*) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintMinimum(const std::string&, std::vector<Tree*>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintMaximum(const std::string&, std::vector<Tree*>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintElement(const std::string&, std::vector<std::vector<XVariable*>>&, int, XVariable*, int, XVariable*, XVariable*) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintElement(const std::string&, std::vector<std::vector<XVariable*>>&, int, XVariable*, int, XVariable*, int) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<int>&, std::vector<int>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<int>&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, std::vector<int>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<int>&, std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, std::vector<int>&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildConstraintCumulative(const std::string&, std::vector<XVariable*>& , std::vector<XVariable*>&, std::vector<XVariable*>&, std::vector<XVariable*>&, XCondition&) {
    nbc++;
}

void XCSP3SummaryCallbacks::buildObjectiveMinimize(ExpressionObjective _type, std::vector<Tree*>&, std::vector<int>& ) {
    buildObj(_type, "Minimize", type, minmax);
}

void XCSP3SummaryCallbacks::buildObjectiveMaximize(ExpressionObjective _type, std::vector<Tree*>&, std::vector<int>& ) {
    buildObj(_type, "Maximize", type, minmax);
}

void XCSP3SummaryCallbacks::buildObjectiveMinimize(ExpressionObjective _type, std::vector<Tree*>&) {
    buildObj(_type, "Minimize", type, minmax);
}

void XCSP3SummaryCallbacks::buildObjectiveMaximize(ExpressionObjective _type, std::vector<Tree*>&) {
    buildObj(_type, "Maximize", type, minmax);
}


void XCSP3SummaryCallbacks::buildAnnotationDecision(std::vector<XVariable*>&) {
}

#endif //COSOCO_XCSP3SummaryCallbacks_H

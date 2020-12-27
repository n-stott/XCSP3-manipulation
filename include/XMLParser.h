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
#ifndef _XMLParser_h_
#define _XMLParser_h_

/**
 * @file XMLParser.h
 * @brief defines the XMLParser class to parse a CSP instance in XML format
 */

#include <cassert>
#include <cstring>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "XCSP3Constants.h"
#include "XCSP3Constraint.h"
#include "XCSP3Domain.h"
#include "XCSP3Manager.h"
#include "XCSP3Objective.h"
#include "XCSP3Variable.h"
#include "XCSP3utils.h"

#include "AttributeList.h"
#include "UTF8String.h"

/**
 * @namespace CSPXMLParser
 * @brief this namespace encloses all definitions relative to the
 * CSP XML format parser.
 */
namespace XCSP3Core {

    /**
     * @brief contains a parser for the CSP XML format.
     *
     * This class proposes a parser in SAX mode (to use less memory than
     * in DOM mode)
     *
     *
     */
    class XMLParser {
    public:
        // list of attributes and values for a tag
        std::map<std::string, XEntity*> variablesList;
        std::vector<XDomainInteger*> allDomains;
        std::vector<XConstraint*> constraints;
        XCSP3Manager* manager;

        // stack of operands to construct list, dictionaries, predicate
        // parameters and so on

    private:
        /***************************************************************************
         * @brief the action to be performed (callback) when a tag is read in the
         * XML file
         ***************************************************************************/
        class TagAction {
        protected:
            bool activated;
            XMLParser* parser;

        public:
            std::string tagName;
            TagAction(XMLParser* parser, std::string name) : parser(parser), tagName(name) { activated = false; }

            virtual ~TagAction() {}

            void activate() { activated = true; }

            void deactivate() { activated = false; }

            bool isActivated() { return activated; }

            /**
             * return the name of this tag (constant)
             */
            const char* getTagName() { return tagName.c_str(); }

            // AttributeList &attributes
            virtual void beginTag(const AttributeList&) {}

            /**
             *
             * @parm last must be true if this is the last chunk of text
             */
            // UTF8String txt, bool last
            virtual void text(const UTF8String txt, bool) {
                if (!txt.isWhiteSpace())
                    throw std::runtime_error("<" + tagName + "> tag should not have meaningful text");
            }

            virtual void endTag() {}

        protected:
            /**
             * check that the parent tag in the XML file has the indicated name
             *
             * when name is NULL, check that this tag has no parent in the XML file
             *
             * @param parentTag: the expected name of the parent tag or NULL to
             * check that we have no parent
             * @param n: 1 for parent, 2 for grand-parent and so on
             */
            void checkParentTag(const char* parentTag, int n = 1) {
                if (this->parser->getParentTagAction(n) == NULL) {
                    if (parentTag != NULL)
                        throw std::runtime_error("tag has no parent but it should have one");
                    else
                        return;
                }

                if (parentTag == NULL)
                    throw std::runtime_error("tag should have no parent");

#ifdef debug
                cout << "parent tag="
                     << this->parser->getParentTagAction(n)->getTagName() << endl;
#endif
                if (strcmp(this->parser->getParentTagAction(n)->getTagName(),
                           parentTag) != 0)
                    throw std::runtime_error("wrong parent for tag");
            }
        };

        typedef std::map<UTF8String, TagAction*> TagActionList;

        TagActionList tagList;

        struct State {
            bool subtagAllowed;

            State() {
                subtagAllowed = true;
            }
        };

        class ListTagAction;

        // the top of the following stacks is at the FRONT
        std::deque<TagAction*> actionStack;
        std::deque<State> stateStack;
        std::vector<std::vector<XVariable*>> lists;  // used to store Many lists of variables (usefull with lex, channel....)
        std::vector<std::vector<XVariable*>> matrix; // Used in case of matrix tag
        std::vector<std::vector<int>> patterns;

        std::vector<XVariable*> args;   // used to store a list of args
        std::vector<XVariable*> values; // used to store a list of variables
        std::vector<XVariable*> occurs; // used in cardinality

        std::vector<int> integers; // used to store a list of coefficients

        std::vector<XVariable*> origins;     // used to store a origins in noOverlap/cumulative Constraint
        std::vector<XVariable*> lengths;     // used to store lengths in noOverlap/cumulative Constraint
        std::vector<XVariable*> ends;        // used to store a origins in cumulative Constraint
        std::vector<XVariable*> heights;     // used to store a origins in cumulative Constraint
        std::vector<XIntegerEntity*> widths; // used to store lengths in stretch constraint

        std::vector<int> currentTuple;
        ListTagAction* listTag; // The List tag action call

        std::string classes;

        bool zeroIgnored;            // for nooverlap
        std::string condition;       // used to store a condition in prefix form
        bool star;                   // true if the extension contain star in tuples
        int startIndex, startIndex2; // used in some list tag
        int startRowIndex, startColIndex;
        XVariable* index;  // used with tag index
        XVariable* index2; // Only for element matrix
        RankType rank;     // used with rank tag
        OrderType op;
        std::string expr;
        std::string start, final;             // used in regular constraint
        std::vector<XTransition> transitions; // used in regular and mdd constraints
        int nbParameters;
        bool closed;
        std::vector<XEntity*> toFree;
        std::vector<XIntegerEntity*> toFreeEntity;

        bool keepIntervals;

        void registerTagAction(TagActionList& tagList, TagAction* action) {
            tagList[action->getTagName()] = action;
        }

        /**
         *
         */

        /**
         * Parse a sequence of tokens. Each token can represent a compact list of array variables, or a basic entity, or a template parameter
         */

        void parseSequence(const UTF8String& txt, std::vector<XVariable*>& list, std::vector<char> delimiters = std::vector<char>());

        void parseDomain(const UTF8String& txt, XDomainInteger& domain);

        void parseListOfIntegerOrInterval(const UTF8String& txt, std::vector<XIntegerEntity*>& listToFill);

        bool parseTuples(const UTF8String& txt, std::vector<std::vector<int>>& tuples);

        /***************************************************************************
             * a handler to silently ignore unkown tags
             ***************************************************************************/
        class UnknownTagAction : public TagAction {
        public:
            UnknownTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}

            // AttributeList &attributes
            virtual void beginTag(const AttributeList&) {
                throw std::runtime_error("Unknown Tag");
            }
        };

        /***************************************************************************
         * Actions performed on INSTANCE tag
         ***************************************************************************/

        class InstanceTagAction : public TagAction {
        public:
            InstanceTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on VARIABLES tag
         ***************************************************************************/
        class VariablesTagAction : public TagAction {
        public:
            VariablesTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            virtual void beginTag(const AttributeList& attributes) override;
            virtual void endTag() override;
        };

        /***************************************************************************
         * Actions performed on VAR tag
         ***************************************************************************/

        class VarTagAction : public TagAction {
        private:
            XVariable* variable;
            XVariableArray* variableArray;
            XDomainInteger* domain;
            std::string id, classes;

        public:
            VarTagAction(XMLParser* parser, std::string name) : TagAction(parser, name), variable(NULL), variableArray(NULL), domain(NULL) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on ARRAY tag
         ***************************************************************************/

        class ArrayTagAction : public TagAction {

        public:
            XVariableArray* varArray;
            XDomainInteger* domain;
            std::string id, classes;
            std::vector<int> sizes;

            ArrayTagAction(XMLParser* parser, std::string name) : TagAction(parser, name), varArray(NULL), domain(NULL) {}

            void beginTag(const AttributeList& attributes) override;
            void endTag() override;

            // UTF8String txt, bool last
            void text(const UTF8String txt, bool) override {
                this->parser->parseDomain(txt, *domain);
            }
        };

        class DomainTagAction : public TagAction {

        public:
            XDomainInteger* d;
            std::string forAttr;

            DomainTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}

            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on CONSTRAINTS tag
         ***************************************************************************/

        class ConstraintsTagAction : public TagAction {

        public:
            ConstraintsTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}

            // AttributeList &attributes
            virtual void beginTag(const AttributeList&) {
                this->checkParentTag("instance");
                this->parser->manager->beginConstraints();
            }

            virtual void endTag() {
                this->parser->manager->endConstraints();
            }
        };

        /***************************************************************************
         * All constraint MUST inherit this tagAction
         *****************************************************************************/

        class BasicConstraintTagAction : public TagAction {
        public:
            XConstraintGroup* group;
            std::string id;
            BasicConstraintTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
        };

        /***************************************************************************
         * Actions performed on EXTENSION tag
         ****************************************************************************/

        class ExtensionTagAction : public BasicConstraintTagAction {
        public:
            XConstraintExtension* constraint;
            ExtensionTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on INTENSION tag
         ****************************************************************************/
        class IntensionTagAction : public BasicConstraintTagAction {
        protected:
            UTF8String fnc;

        public:
            XConstraintIntension* constraint;
            IntensionTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
        ****************************************************************************
         *                  CONSTRAINTS DEFINED ON LANGAGES
         ***************************************************************************
        ***************************************************************************/

        /***************************************************************************
        * Actions performed on REGULAR tag
        ****************************************************************************/

        class RegularTagAction : public BasicConstraintTagAction {
        public:
            XConstraintRegular* constraint;
            RegularTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on MDD tag
         ****************************************************************************/

        class MDDTagAction : public BasicConstraintTagAction {
        public:
            XConstraintMDD* constraint;
            MDDTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
        ****************************************************************************
         *                  CONSTRAINTS DEFINED ON COMPARISON
        ****************************************************************************
        ***************************************************************************/

        /***************************************************************************
         * Actions performed on ALLDIFF tag / ALLEQUAL
         ****************************************************************************/

        class AllDiffEqualTagAction : public BasicConstraintTagAction {

        public:
            XConstraintAllDiff* alldiff;
            XConstraintAllEqual* allequal;
            XConstraint* ct;
            AllDiffEqualTagAction(XMLParser* parser, std::string tag) : BasicConstraintTagAction(parser, tag) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on ORDERED tag
         ****************************************************************************/
        class OrderedTagAction : public BasicConstraintTagAction {
        public:
            XConstraintOrdered* constraint;
            OrderedTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on LEX tag
         ****************************************************************************/
        class LexTagAction : public BasicConstraintTagAction {
        public:
            XConstraintLex* constraint;
            LexTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
        ****************************************************************************
         *                  COUNTIG AND SUMMING CONSTRAINTS
        ****************************************************************************
         ****************************************************************************/

        /***************************************************************************
         * Actions performed on SUM tag
         ****************************************************************************/

        class SumTagAction : public BasicConstraintTagAction {
        public:
            XConstraintSum* constraint;
            SumTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on NVALUES tag
         ****************************************************************************/
        class NValuesTagAction : public BasicConstraintTagAction {
        public:
            XConstraintNValues* constraint;
            NValuesTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on COUNT tag
         ****************************************************************************/

        class CountTagAction : public BasicConstraintTagAction {
        public:
            XConstraintCount* constraint;
            CountTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
        * Actions performed on CARDINALITY tag
        ****************************************************************************/

        class CardinalityTagAction : public BasicConstraintTagAction {
        public:
            XConstraintCardinality* constraint;
            CardinalityTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
        ****************************************************************************
         *                  CONNECTION CONSTRAINTS
        ****************************************************************************
         ****************************************************************************/

        /***************************************************************************
         * Actions performed on CHANNEL tag
         ****************************************************************************/
        class ChannelTagAction : public BasicConstraintTagAction {
        public:
            XConstraintChannel* constraint;
            ChannelTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on ELEMENT tag
         ****************************************************************************/

        class ElementTagAction : public BasicConstraintTagAction {
        public:
            XConstraintElement* constraint;
            ElementTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on MAXIMUM or MINIMUM tag
         ****************************************************************************/

        class MinMaxTagAction : public BasicConstraintTagAction {

        public:
            XConstraintMaximum* constraint;
            MinMaxTagAction(XMLParser* parser, std::string tag) : BasicConstraintTagAction(parser, tag) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         ****************************************************************************
          *                  PACKING and SCHEDULING CONSTRAINTS
         ****************************************************************************
          ****************************************************************************/

        /***************************************************************************
         * Actions performed on STRETCH tag
         ****************************************************************************/

        class StretchTagAction : public BasicConstraintTagAction {
        public:
            XConstraintStretch* constraint;
            StretchTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on NOOVERLAP tag
         ****************************************************************************/

        class NoOverlapTagAction : public BasicConstraintTagAction {
        public:
            bool diffn;
            XConstraintNoOverlap* constraint;
            NoOverlapTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
           * Actions performed on CUMULATIVE tag
           ****************************************************************************/

        class CumulativeTagAction : public BasicConstraintTagAction {
        public:
            XConstraintCumulative* constraint;
            CumulativeTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         ****************************************************************************
          *                            OBJECTIVES
         ****************************************************************************
          ****************************************************************************/

        class ObjectivesTagAction : public TagAction {
        public:
            XObjective* objective;
            ObjectivesTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        class MinimizeOrMaximizeTagAction : public TagAction {
        public:
            MinimizeOrMaximizeTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            XObjective* obj;
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
         * Actions performed on instantiation tag
         ****************************************************************************/
        class InstantiationTagAction : public BasicConstraintTagAction {
        public:
            InstantiationTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            XConstraintInstantiation* constraint;
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on clause tag
         ****************************************************************************/
        class ClauseTagAction : public BasicConstraintTagAction {
        protected:
            UTF8String literals;

        public:
            ClauseTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            XConstraintClause* constraint;
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on LIST tag
         ****************************************************************************/

        class ListTagAction : public TagAction {
        public:
            int nbCallsToList;
            // The first call stores datas inside this->parser->list
            // the ith call (i>1) stores datas inside this->parser->manyLists[i-1];
            ListTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on SUPPORTS CONFLICTS tag
         ****************************************************************************/

        class ConflictOrSupportTagAction : public TagAction {
        protected:
        public:
            ConflictOrSupportTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
         * Actions performed on COEFFS tag
         ****************************************************************************/

        class ConditionTagAction : public TagAction {
        public:
            ConditionTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}

            // UTF8String txt, bool last
            virtual void text(const UTF8String txt, bool) {
                this->parser->condition += txt.to(this->parser->condition);
            }

            virtual void endTag() {
                this->parser->condition = trim(this->parser->condition);

                std::regex const rglt(R"(\(.*(le|lt|ge|gt|in|eq|ne),%([0-9]+)\).*)");
                std::smatch match;
                std::regex_match(this->parser->condition, match, rglt);

                if (match.size() != 3)
                    return;
                int tmp = std::stoi(match[2].str());
                if (XParameterVariable::max < tmp)
                    XParameterVariable::max = tmp;
            }
        };

        /***************************************************************************
         * Actions performed on CONDITION tag
         ****************************************************************************/

        class ListOfIntegerTagAction : public TagAction {
        public:
            ListOfIntegerTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            virtual void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
         * Actions performed on VALUES / VALUE tag
         ****************************************************************************/

        class ListOfVariablesOrIntegerTagAction : public TagAction {

            std::vector<XVariable*>& listToFill;

        public:
            ListOfVariablesOrIntegerTagAction(XMLParser* parser, std::string nm, std::vector<XVariable*>& ltf) : TagAction(parser, nm), listToFill(ltf) {}
            virtual void beginTag(const AttributeList& attributes) override;
            virtual void text(const UTF8String txt, bool last) override;
        };

        class ListOfVariablesOrIntegerOrIntervalTagAction : public TagAction {

            std::vector<XVariable*>& listToFill;

        public:
            ListOfVariablesOrIntegerOrIntervalTagAction(XMLParser* parser, std::string nm, std::vector<XVariable*>& ltf) : TagAction(parser, nm), listToFill(ltf) {}
            virtual void beginTag(const AttributeList& attributes) override;
            virtual void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
          * Actions performed on  ORIGINS tag
          ****************************************************************************/

        class OriginsTagAction : public TagAction {

            std::vector<XVariable*>& listToFill;

        public:
            OriginsTagAction(XMLParser* parser, std::string nm, std::vector<XVariable*>& ltf) : TagAction(parser, nm), listToFill(ltf) {}
            virtual void beginTag(const AttributeList& attributes) override;
            virtual void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
          * Actions performed on  WIDTH tag
          ****************************************************************************/

        class ListOfIntegerOrIntervalTagAction : public TagAction {

            std::vector<XIntegerEntity*>& listToFill;

        public:
            ListOfIntegerOrIntervalTagAction(XMLParser* parser, std::string nm,
                                             std::vector<XIntegerEntity*>& ltf) : TagAction(parser, nm), listToFill(ltf) {}
            virtual void beginTag(const AttributeList& attributes) override;
            virtual void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
         * Actions performed on GROUP tag
         ****************************************************************************/

        class GroupTagAction : public TagAction {
        public:
            XConstraintGroup* group;
            GroupTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on SLIDE tag
         ****************************************************************************/

        class SlideTagAction : public TagAction {
        public:
            XConstraintGroup* group;
            std::vector<XVariable*> list;

            int offset = 1;
            bool circular = false;

            SlideTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on GROUP tag
         ****************************************************************************/
        class BlockTagAction : public TagAction {
        public:
            std::vector<std::string> classes; // it is possible to have block inside block
            BlockTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on ARGS tag
         ****************************************************************************/

        class ArgsTagAction : public TagAction {
        public:
            ArgsTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            virtual void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on Operator tag
         ****************************************************************************/

        class OperatorTagAction : public TagAction {
        public:
            OperatorTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
         * Actions performed on INDEX tag
         ****************************************************************************/
        class IndexTagAction : public TagAction {
        public:
            IndexTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
         * Actions performed on MATRIX TAG
         ****************************************************************************/

        class MatrixTagAction : public TagAction {
        public:
            MatrixTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on START or FINAL tag
         ****************************************************************************/

        class StringTagAction : public TagAction {
        public:
            StringTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
         * Actions performed on  TRANSITIONS tag
         ****************************************************************************/

        class TransitionsTagAction : public TagAction {
        public:
            int nb, val;
            std::string from, to;
            TransitionsTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
        };

        /***************************************************************************
         * Actions performed on  TRANSITIONS tag
        ****************************************************************************/

        class PatternsTagAction : public TagAction {
        public:
            std::vector<XVariable*> listToFill;
            PatternsTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
        };

        class CircuitTagAction : public BasicConstraintTagAction {
            XConstraintCircuit* constraint;

        public:
            CircuitTagAction(XMLParser* parser, std::string name) : BasicConstraintTagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

        /***************************************************************************
         * Actions performed on  ANNOTATIONS TAG
        ****************************************************************************/

        class AnnotationsTagAction : public TagAction {
        public:
            AnnotationsTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void endTag() override;
        };

        class DecisionTagAction : public TagAction {
            std::vector<XVariable*> list;

        public:
            DecisionTagAction(XMLParser* parser, std::string name) : TagAction(parser, name) {}
            void beginTag(const AttributeList& attributes) override;
            void text(const UTF8String txt, bool last) override;
            void endTag() override;
        };

    public:
        XMLParser(XCSP3CoreCallbacks* cb);
        ~XMLParser();

        /**
         * get the parent tag action that is n levels higher in the current
         * branch of the XML parse tree
         */
        TagAction* getParentTagAction(int n = 1) {
            if (n < 0 || n >= static_cast<int>(actionStack.size()))
                return NULL;

            return actionStack[n];
        }

        /**
         * callbacks from the XML parser
         */
        void startDocument() {
            clearStacks();
        }

        void endDocument() {}

        void startElement(UTF8String name, const AttributeList& attributes);

        void endElement(UTF8String name);

        void characters(UTF8String chars);

        void handleAbridgedNotation(UTF8String chars, bool lastChunk);

    protected:
        void clearStacks() {
            stateStack.clear();
        }

        // text which is left for the next call to characters() because it
        // may not be a complete token
        UTF8String textLeft;

        // specific actions
        VarTagAction* varTagAction;
        //DictTagAction *dictTagAction;
        TagAction* unknownTagHandler; // handler to help ignore all unknown tags

    }; // class XMLParser

} // namespace XCSP3Core

// Local Variables:
// mode: C++
// End:

#endif

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

#ifndef XCSP3PARSER_XCSP3TREENODE_H
#define XCSP3PARSER_XCSP3TREENODE_H

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>

namespace XCSP3Core {

    enum class Expr {
        UNDEF,
        NEG,
        ABS,
        SQR,
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        POW,
        DIST,
        MIN,
        MAX,
        LT,
        LE,
        GE,
        GT,
        NE,
        EQ,
        SET,
        IN,
        NOTIN,
        NOT,
        AND,
        OR,
        XOR,
        IFF,
        IMP,
        IF,
        CARD,
        UNION,
        INTER,
        DIFF,
        SDIFF,
        HULL,
        DJOINT,
        SUBSET,
        SUBSEQ,
        SUPSEQ,
        SUPSET,
        CONVEX,
        FDIV,
        FMOD,
        SQRT,
        NROOT,
        EXP,
        LN,
        LOG,
        SIN,
        COS,
        TAN,
        ASIN,
        ACOS,
        ATAN,
        SINH,
        COSH,
        TANH,
        VAR,
        PAR,
        LONG,
        RATIONAL,
        DECIMAL,
        SYMBOL,
        FAKEOP // Used only to match primitives
    };

    bool isSymmetricOperator(Expr type);

    bool isNonSymmetricRelationalOperator(Expr type);

    Expr arithmeticInversion(Expr type);

    std::string operatorToString(Expr op);
    Expr stringToOperator(const std::string& op);

    Expr logicalInversion(Expr type);

    bool isRelationalOperator(Expr type);

    bool isPredicateOperator(Expr type);
    //-------------------------------------

    class Node {
        friend class Intension;

    public:
        Expr type;

        std::vector<Node*> parameters; // Useless for constant and variables, but avoid many casts!

        Node(Expr o) : type(o) {}

        virtual int evaluate(std::map<std::string, int>& tuple) = 0;

        virtual Node* canonize() = 0;

        virtual std::string toString() = 0;

        static bool areSimilar(Node* canonized, Node* pattern, std::vector<Expr>& operators, std::vector<int>& constants, std::vector<std::string>& variables);
    };

    //-------------------------------------

    class NodeConstant : public Node {

    public:
        int val;

        NodeConstant(int v) : Node(Expr::DECIMAL), val(v) {}

        // std::map<std::string, int> &tuple
        int evaluate(std::map<std::string, int>&) override {
            return val;
        }

        Node* canonize() override {
            return this;
        }

        std::string toString() override {
            return std::to_string(val);
        }
    };

    //-------------------------------------

    class NodeVariable : public Node {

    public:
        std::string var;

        NodeVariable(std::string v) : Node(Expr::VAR), var(v) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return tuple[var];
        }

        Node* canonize() override {
            return this;
        }

        std::string toString() override {
            return var;
        }
    };

    //-------------------------------------

    class NodeOperator : public Node {
    public:
        std::string op;

        NodeOperator(std::string o, Expr _operator) : Node(_operator), op(o) {}

        NodeOperator* addParameter(Node* p) {
            parameters.push_back(p);
            return this;
        }

        NodeOperator* addParameters(std::vector<Node*> params) {
            parameters.insert(parameters.end(), params.begin(), params.end());
            return this;
        }

        std::string toString() override {
            std::string tmp = op + "(";
            for (unsigned int i = 0; i < parameters.size(); i++) {
                if (i != 0)
                    tmp = tmp + ",";
                tmp = tmp + parameters[i]->toString();
            }
            tmp = tmp + ")";
            return tmp;
        }

        Node* canonize() override;
    };

    class NodeUnary : public NodeOperator {
    public:
        NodeUnary(std::string o, Expr _operator) : NodeOperator(o, _operator) {}
    };

    //-------------------------------------

    class NodeBinary : public NodeOperator {
    public:
        NodeBinary(std::string o, Expr _operator) : NodeOperator(o, _operator) {}
    };

    //-------------------------------------

    class NodeNAry : public NodeOperator {
        friend class NodeIn;

        friend class NodeNotIn;

    public:
        NodeNAry(std::string o, Expr _operator) : NodeOperator(o, _operator) {}
    };

    //-------------------------------------

    class NodeNeg : public NodeUnary {
    public:
        NodeNeg() : NodeUnary("neg", Expr::NEG) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return -parameters[0]->evaluate(tuple);
        }
    };

    // --------------------------------------------------------------------------

    class NodeAbs : public NodeUnary {
    public:
        NodeAbs() : NodeUnary("abs", Expr::ABS) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int v = parameters[0]->evaluate(tuple);
            return v > 0 ? v : -v;
        }
    };

    class NodeSquare : public NodeUnary {
    public:
        NodeSquare() : NodeUnary("sqr", Expr::SQR) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int v = parameters[0]->evaluate(tuple);
            return v * v;
        }
    };

    class NodeNot : public NodeUnary {
    public:
        NodeNot() : NodeUnary("not", Expr::NOT) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int v = parameters[0]->evaluate(tuple);
            return v == 0 ? 1 : 0; // Must return 0....
        }
    };
    // --------------------------------------------------------------------------

    class NodeSub : public NodeBinary {
    public:
        NodeSub() : NodeBinary("sub", Expr::SUB) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return parameters[0]->evaluate(tuple) - parameters[1]->evaluate(tuple);
        }
    };

    class NodeDiv : public NodeBinary {
    public:
        NodeDiv() : NodeBinary("div", Expr::DIV) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return parameters[0]->evaluate(tuple) / parameters[1]->evaluate(tuple);
        }
    };

    class NodeMod : public NodeBinary {
    public:
        NodeMod() : NodeBinary("mod", Expr::MOD) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return parameters[0]->evaluate(tuple) % parameters[1]->evaluate(tuple);
        }
    };

    class NodePow : public NodeBinary {
    public:
        NodePow() : NodeBinary("pow", Expr::POW) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return pow(parameters[0]->evaluate(tuple), parameters[1]->evaluate(tuple));
        }
    };

    class NodeDist : public NodeBinary {
    public:
        NodeDist() : NodeBinary("dist", Expr::DIST) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int v = parameters[0]->evaluate(tuple) - parameters[1]->evaluate(tuple);
            return v > 0 ? v : -v;
        }
    };

    class NodeLE : public NodeBinary {
    public:
        NodeLE() : NodeBinary("le", Expr::LE) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return parameters[0]->evaluate(tuple) <= parameters[1]->evaluate(tuple);
        }
    };

    class NodeLT : public NodeBinary {
    public:
        NodeLT() : NodeBinary("lt", Expr::LT) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return parameters[0]->evaluate(tuple) < parameters[1]->evaluate(tuple);
        }
    };

    class NodeGE : public NodeBinary {
    public:
        NodeGE() : NodeBinary("ge", Expr::GE) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return parameters[0]->evaluate(tuple) >= parameters[1]->evaluate(tuple);
        }
    };

    class NodeGT : public NodeBinary {
    public:
        NodeGT() : NodeBinary("gt", Expr::GT) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return parameters[0]->evaluate(tuple) > parameters[1]->evaluate(tuple);
        }
    };

    class NodeNE : public NodeBinary {
    public:
        NodeNE() : NodeBinary("ne", Expr::NE) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return parameters[0]->evaluate(tuple) != parameters[1]->evaluate(tuple);
        }
    };

    class NodeImp : public NodeBinary {
    public:
        NodeImp() : NodeBinary("imp", Expr::IMP) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            return parameters[0]->evaluate(tuple) == 0 || parameters[1]->evaluate(tuple) != 0; // Must return 0 or 1
        }
    };

    //-------------------------------------

    class NodeAdd : public NodeNAry {
    public:
        NodeAdd() : NodeNAry("add", Expr::ADD) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int nb = 0;
            for (unsigned int i = 0; i < parameters.size(); i++)
                nb += parameters[i]->evaluate(tuple);
            return nb;
        }
    };

    class NodeMult : public NodeNAry {
    public:
        NodeMult() : NodeNAry("mul", Expr::MUL) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int nb = 1;
            for (unsigned int i = 0; i < parameters.size(); i++)
                nb *= parameters[i]->evaluate(tuple);
            return nb;
        }
    };

    class NodeMin : public NodeNAry {
    public:
        NodeMin() : NodeNAry("min", Expr::MIN) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            for (unsigned int i = 1; i < parameters.size(); i++) {
                int v = parameters[i]->evaluate(tuple);
                if (v < nb)
                    nb = v;
            }
            return nb;
        }
    };

    class NodeMax : public NodeNAry {
    public:
        NodeMax() : NodeNAry("max", Expr::MAX) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            for (unsigned int i = 1; i < parameters.size(); i++) {
                int v = parameters[i]->evaluate(tuple);
                if (v > nb)
                    nb = v;
            }
            return nb;
        }
    };

    class NodeEQ : public NodeNAry {
    public:
        NodeEQ() : NodeNAry("eq", Expr::EQ) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            for (unsigned int i = 1; i < parameters.size(); i++) {
                if (nb != parameters[i]->evaluate(tuple))
                    return 0;
            }
            return 1;
        }
    };

    class NodeAnd : public NodeNAry {
    public:
        NodeAnd() : NodeNAry("and", Expr::AND) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            for (unsigned int i = 0; i < parameters.size(); i++)
                if (!parameters[i]->evaluate(tuple))
                    return 0;
            return 1;
        }
    };

    class NodeOr : public NodeNAry {
    public:
        NodeOr() : NodeNAry("or", Expr::OR) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            for (unsigned int i = 0; i < parameters.size(); i++)
                if (parameters[i]->evaluate(tuple)) {
                    return 1;
                }
            return 0;
        }
    };

    class NodeXor : public NodeNAry {
    public:
        NodeXor() : NodeNAry("xor", Expr::XOR) {}

        int evaluate(std::map<std::string, int>& tuple) override {

            int nb = 0;
            for (unsigned int i = 0; i < parameters.size(); i++)
                nb = nb + parameters[i]->evaluate(tuple);
            return nb % 2 == 1;
        }
    };

    class NodeIf : public NodeNAry {
    public:
        NodeIf() : NodeNAry("if", Expr::IF) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            if (nb)
                return parameters[1]->evaluate(tuple);
            return parameters[2]->evaluate(tuple);
        }
    };

    class NodeIff : public NodeNAry {
    public:
        NodeIff() : NodeNAry("iff", Expr::IFF) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            assert(parameters.size() == 2); // TODO if greater!!
            int nb = parameters[0]->evaluate(tuple);
            return (nb) ? parameters[1]->evaluate(tuple) != 0 : parameters[1]->evaluate(tuple) == 0;
        }
    };

    class NodeSet : public NodeNAry {
    public:
        NodeSet() : NodeNAry("set", Expr::SET) {}

        // std::map<std::string, int> &tuple
        int evaluate(std::map<std::string, int>&) override {
            throw std::runtime_error("can't evaluate set");
        }
    };

    class NodeIn : public NodeBinary {
    protected:
        std::vector<int> set;

    public:
        NodeIn() : NodeBinary("in", Expr::IN) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            set.clear();
            NodeSet* nodeSet;
            if ((nodeSet = dynamic_cast<NodeSet*>(parameters[1])) == NULL)
                throw std::runtime_error("intension constraint : in requires a set as second parameter");
            for (unsigned int i = 0; i < nodeSet->parameters.size(); i++)
                set.push_back(nodeSet->parameters[i]->evaluate(tuple));
            return find(set.begin(), set.end(), nb) != set.end();
        }
    };

    class NodeNotIn : public NodeBinary {
    protected:
        std::vector<int> set;

    public:
        NodeNotIn() : NodeBinary("notin", Expr::NOTIN) {}

        int evaluate(std::map<std::string, int>& tuple) override {
            int nb = parameters[0]->evaluate(tuple);
            set.clear();
            NodeSet* nodeSet;
            if ((nodeSet = dynamic_cast<NodeSet*>(parameters[1])) == NULL)
                throw std::runtime_error("intension constraint : in requires a set as second parameter");
            for (unsigned int i = 0; i < nodeSet->parameters.size(); i++)
                set.push_back(nodeSet->parameters[i]->evaluate(tuple));
            return find(set.begin(), set.end(), nb) == set.end();
        }
    };

} // namespace XCSP3Core
#endif //XCSP3PARSER_XCSP3TREENODE_H

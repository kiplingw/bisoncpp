#ifndef _INCLUDED_GENERATOR_
#define _INCLUDED_GENERATOR_

#include <vector>
#include <map>
#include <string>
#include <iosfwd>

#include <bobcat/arg>

#include "../writer/writer.h"

class Terminal;
class Parser;
class Rules;

class Generator
{
    typedef void (Generator::*Inserter)(std::ostream &) const;
    typedef std::map<std::string, Inserter>     Map;
    typedef Map::value_type                     MapValue;
    typedef Map::const_iterator                 MapConstIter;

    FBB::Arg &d_arg;
    Rules const &d_rules;
    Parser const &d_parser;

    std::string d_baseclassScope;
    std::string const &d_nameSpace;
    std::string const *d_matchedTextFunction;
    std::string const *d_scannerTokenFunction;

    mutable std::string d_key;          // extracted at $insert statements
    mutable size_t d_indent;

    mutable std::string d_line;
    bool d_debug;
    bool d_print;
    
    mutable Writer d_writer;                // maintains its own const-ness

    static Map s_insert;
    static char const *s_baseFlag;          // text to change to the class 
                                            // name
    static size_t const s_baseFlagSize;     // # of characters in s_baseFlag

    static std::string s_matchedTextFunction;   // default way to call the
    static std::string s_scannerTokenFunction;  // scanner's token en text
                                                // functions.

    public:
        Generator(Rules const &rules, Parser const &parser);

        void baseclassHeader() const;
        void classHeader() const;
        void implementationHeader() const;
        void parseFunction() const;

    private:
        void filter(std::istream &in, std::ostream &out) const;
        void insert(std::ostream &out) const;
        void key(std::ostream &out) const;          // show which $insert is
                                                    // called, just before the
                                                    // generated code 
        void actionCases(std::ostream &out) const;
        void baseClass(std::ostream &out) const;
        void classH(std::ostream &out) const;
        void classIH(std::ostream &out) const;
        void debug(std::ostream &out) const;
        void debugIncludes(std::ostream &out) const;
        void debugFunctions(std::ostream &out) const;
        void debugInit(std::ostream &out) const;
        void debugDecl(std::ostream &out) const;
        void debugLookup(std::ostream &out) const;
        void errorVerbose(std::ostream &out) const;
        void lex(std::ostream &out) const;
        void ltype(std::ostream &out) const;
        void ltypeData(std::ostream &out) const;
        void ltypePop(std::ostream &out) const;
        void ltypePush(std::ostream &out) const;
        void ltypeResize(std::ostream &out) const;
        void ltypeStack(std::ostream &out) const;
        void namespaceClose(std::ostream &out) const;
        void namespaceOpen(std::ostream &out) const;
        void namespaceUse(std::ostream &out) const;
        void preIncludes(std::ostream &out) const;
        void print(std::ostream &out) const;
        void requiredTokens(std::ostream &out) const;
        void scannerH(std::ostream &out) const;
        void scannerObject(std::ostream &out) const;
        void staticData(std::ostream &out) const;
        void stype(std::ostream &out) const;
        void threading(std::ostream &out) const;
        void tokens(std::ostream &out) const;

        static void selectSymbolic(Terminal const *terminal, 
                                   Terminal::ConstVector *symbolicTokens);
};

#endif
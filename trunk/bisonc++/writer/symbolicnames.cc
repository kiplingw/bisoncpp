#include "writer.ih"

void Writer::symbolicNames() const
{
    *d_out <<  
        "typedef std::map<int, char const *> SMap;\n"
        "typedef SMap::value_type SMapVal;\n"
        "\n"
        "SMapVal s_symArr[] =\n"
        "{\n"
        "    SMapVal(-2, \"_UNDETERMINED_\"),  // predefined symbols\n"
        "    SMapVal(-1, \"_EOF_\"),\n"
        "    SMapVal(256, \"_error_\"),\n"
        "\n";

    for_each(d_rules.terminals().begin(), d_rules.terminals().end(),
            FnWrap::unary(terminalSymbol, *d_out));

    for_each(d_rules.nonTerminals().begin(), d_rules.nonTerminals().end(),
            FnWrap::unary(nonTerminalSymbol, *d_out));

    *d_out <<  "};\n"
            "\n"
            "SMap s_symbol\n"
            "(\n"
            "    s_symArr, s_symArr + sizeof(s_symArr) / sizeof(SMapVal)\n"
            ");\n"
            "\n";
}
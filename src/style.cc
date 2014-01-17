#include "style.h"

namespace Style {

    const char* K_BOLD="\x1B[1m";
    const char* K_NO_STYLE="\x1B[0m";
    const char* K_BLACK_ON_WHITE="\x1B[37;40m";
    const char* K_WHITE_ON_BLUE="\x1B[37;44m";

}

namespace Style {
    namespace Labels {

    const char* ID      = "Id";
    const char* PRI     = "Pri";
    const char* STATE   = "State";
    const char* DESC    = "Desc";

    const char* STATE_VAL[] ={
        "",
        "P",
        "S",
        "D"
    };
    } // namespace Labels
} // namespace Style


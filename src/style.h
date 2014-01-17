#ifndef STYLE_H
#define STYLE_H

namespace Style {

    enum {
        FIELD_WIDTH_ID    = 5,
        FIELD_WIDTH_PRI   = 5,
        FIELD_WIDTH_STATE = 7,
        FIELD_WIDTH_DESC  = 70

    };

    extern const char* K_BOLD;
    extern const char* K_NO_STYLE;
    extern const char* K_BLACK_ON_WHITE;
    extern const char* K_WHITE_ON_BLUE;

} // namespace Style

namespace Style {
    namespace Labels {

    extern const char* ID;
    extern const char* PRI;
    extern const char* STATE;
    extern const char* DESC;

    extern const char* STATE_VAL[];

    } // namespace Labels
} // namespace Style


#endif // STYLE_H

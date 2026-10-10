/* CGARM C99 locale compatibility.  SIDBOX currently has only the C locale.
 * No dependency on Newlib locale tables, heap or firmware state.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_locale.c requires SIDBOX_APPLET_V2"
#endif
#include <locale.h>
#include <limits.h>
#include <errno.h>
#include <string.h>

char *setlocale(int category, const char *locale)
{
    switch (category) {
    case LC_ALL:
    case LC_COLLATE:
    case LC_CTYPE:
    case LC_MONETARY:
    case LC_NUMERIC:
    case LC_TIME:
        break;
    default:
        errno = EINVAL;
        return NULL;
    }
    if (!locale || !*locale || strcmp(locale, "C") == 0 ||
        strcmp(locale, "POSIX") == 0) {
        return "C";
    }
    /* Never silently pretend to support an unavailable locale. */
    return NULL;
}

struct lconv *localeconv(void)
{
    static struct lconv c = {
        .decimal_point = ".",
        .thousands_sep = "",
        .grouping = "",
        .int_curr_symbol = "",
        .currency_symbol = "",
        .mon_decimal_point = "",
        .mon_thousands_sep = "",
        .mon_grouping = "",
        .positive_sign = "",
        .negative_sign = "",
        .int_frac_digits = CHAR_MAX,
        .frac_digits = CHAR_MAX,
        .p_cs_precedes = CHAR_MAX,
        .p_sep_by_space = CHAR_MAX,
        .n_cs_precedes = CHAR_MAX,
        .n_sep_by_space = CHAR_MAX,
        .p_sign_posn = CHAR_MAX,
        .n_sign_posn = CHAR_MAX,
        .int_p_cs_precedes = CHAR_MAX,
        .int_p_sep_by_space = CHAR_MAX,
        .int_n_cs_precedes = CHAR_MAX,
        .int_n_sep_by_space = CHAR_MAX,
        .int_p_sign_posn = CHAR_MAX,
        .int_n_sign_posn = CHAR_MAX,
    };
    return &c;
}

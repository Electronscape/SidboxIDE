/* SIDBOX CGARM Phase 6: minimal UTC C calendar, using the existing SBOS RTC.
 * No TFCard file handles, Newlib state or firmware changes.
 * RTC 00..99 is interpreted as years 2000..2099, clock assumed to be UTC.
 * Supported epoch range: 1970-01-01 through the positive limit of time_t.
 * The local timezone model is currently UTC only.
 */
#ifndef SIDBOX_APPLET_V2
#error "cgarm_time.c requires SIDBOX_APPLET_V2"
#endif
#include <time.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include "apis.h"

static int cg_leap(int year)
{
    return ((year % 4) == 0 && (year % 100 != 0 || year % 400 == 0));
}

static int cg_month_days(int year, int month)
{
    static const unsigned char days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (month < 1 || month > 12) return 0;
    return (int)days[month-1] + (month == 2 && cg_leap(year));
}

/* Year 1970..2099. 32-bit unsigned arithmetic avoids 64-bit division helpers. */
static int cg_epoch(int year, int month, int day, int hour, int minute, int second,
                    uint32_t *out)
{
    if (year < 1970 || year > 2099 || month < 1 || month > 12 ||
        day < 1 || day > cg_month_days(year, month) ||
        hour < 0 || hour > 23 || minute < 0 || minute > 59 || second < 0 || second > 59)
        return 0;
    uint32_t days = 0;
    for (int y = 1970; y < year; ++y) days += cg_leap(y) ? 366u : 365u;
    for (int m = 1; m < month; ++m) days += (uint32_t)cg_month_days(year, m);
    days += (uint32_t)(day - 1);
    /* 2099 extends past UINT32 epoch; reject, never wrap. */
    if (days > (UINT32_MAX / 86400u)) return 0;
    uint32_t value = days * 86400u;
    uint32_t tod = (uint32_t)hour * 3600u + (uint32_t)minute * 60u + (uint32_t)second;
    if (value > UINT32_MAX - tod) return 0;
    *out = value + tod;
    return 1;
}

static int cg_usable_timestamp(uint32_t secs)
{
    time_t t = (time_t)secs;
    return t >= (time_t)0 && (uint32_t)t == secs;
}

time_t time(time_t *value)
{
    uint8_t yy = 0, mm = 0, dd = 0, weekday = 0;
    uint8_t hh = 0, mi = 0, ss = 0;
    uint8_t yy2 = 0, mm2 = 0, dd2 = 0, weekday2 = 0;
    time_t result = (time_t)-1;
    if (API && API->hwl && API->hwl->rtc_getdate && API->hwl->rtc_gettime) {
        API->hwl->rtc_getdate(&yy, &mm, &dd, &weekday);
        API->hwl->rtc_gettime(&hh, &mi, &ss);
        API->hwl->rtc_getdate(&yy2, &mm2, &dd2, &weekday2);
        if (yy == yy2 && mm == mm2 && dd == dd2) {
            uint32_t secs = 0;
            if (cg_epoch(2000 + (int)yy, mm, dd, hh, mi, ss, &secs) &&
                cg_usable_timestamp(secs)) result = (time_t)secs;
        }
    }
    if (result == (time_t)-1) errno = EINVAL;
    if (value) *value = result;
    return result;
}

struct tm *gmtime_r(const time_t *timer, struct tm *result)
{
    if (!timer || !result || *timer < (time_t)0) { errno = EINVAL; return NULL; }
    uint32_t secs = (uint32_t)*timer;
    uint32_t d = secs / 86400u;
    uint32_t tod = secs % 86400u;
    result->tm_hour = (int)(tod / 3600u);
    result->tm_min = (int)((tod % 3600u) / 60u);
    result->tm_sec = (int)(tod % 60u);
    result->tm_wday = (int)((d + 4u) % 7u);
    int year = 1970;
    while (year < 2100) {
        uint32_t n = cg_leap(year) ? 366u : 365u;
        if (d < n) break;
        d -= n; ++year;
    }
    if (year >= 2100) { errno = ERANGE; return NULL; }
    result->tm_year = year - 1900;
    result->tm_yday = (int)d;
    int month = 1;
    while (month < 12 && d >= (uint32_t)cg_month_days(year, month)) {
        d -= (uint32_t)cg_month_days(year, month);
        ++month;
    }
    result->tm_mon = month - 1;
    result->tm_mday = (int)d + 1;
    result->tm_isdst = 0;
    return result;
}

struct tm *gmtime(const time_t *timer)
{
    static struct tm result;
    return gmtime_r(timer, &result);
}

struct tm *localtime_r(const time_t *timer, struct tm *result)
{
    return gmtime_r(timer, result); /* CGARM currently has no timezone/DST database. */
}

struct tm *localtime(const time_t *timer)
{
    static struct tm result;
    return localtime_r(timer, &result);
}

time_t mktime(struct tm *input)
{
    if (!input) { errno = EINVAL; return (time_t)-1; }
    uint32_t secs;
    if (!cg_epoch(input->tm_year + 1900, input->tm_mon + 1,
                  input->tm_mday, input->tm_hour, input->tm_min, input->tm_sec, &secs) ||
        !cg_usable_timestamp(secs)) { errno = ERANGE; return (time_t)-1; }
    time_t timestamp = (time_t)secs;
    (void)gmtime_r(&timestamp, input);
    return timestamp;
}

double difftime(time_t later, time_t earlier)
{
    return (double)later - (double)earlier;
}

static const char *const cg_wdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
static const char *const cg_months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

/* A conservative, bounded, C-locale strftime subset, suitable for log timestamps. */
size_t strftime(char *dst, size_t cap, const char *format, const struct tm *tm)
{
    if (!dst || !cap || !format || !tm) return 0;
    size_t pos = 0;
    for (const char *p = format; *p; ++p) {
        const char *literal = NULL;
        char number[16];
        size_t len = 0;
        int n = 0, width = 0;
        if (*p == '%') {
            ++p;
            if (!*p) return 0;
            number[0] = '\0';
            switch (*p) {
            case '%': literal = "%"; break;
            case 'Y': n = tm->tm_year + 1900; width = 4; break;
            case 'y': n = (tm->tm_year + 1900) % 100; width = 2; break;
            case 'm': n = tm->tm_mon + 1; width = 2; break;
            case 'd': n = tm->tm_mday; width = 2; break;
            case 'H': n = tm->tm_hour; width = 2; break;
            case 'M': n = tm->tm_min; width = 2; break;
            case 'S': n = tm->tm_sec; width = 2; break;
            case 'j': n = tm->tm_yday + 1; width = 3; break;
            case 'w': n = tm->tm_wday; width = 1; break;
            case 'u': n = tm->tm_wday == 0 ? 7 : tm->tm_wday; width = 1; break;
            case 'a': if (tm->tm_wday < 0 || tm->tm_wday > 6) return 0; literal = cg_wdays[tm->tm_wday]; len = 3; break;
            case 'A': if (tm->tm_wday < 0 || tm->tm_wday > 6) return 0; literal = cg_wdays[tm->tm_wday]; break;
            case 'b': if (tm->tm_mon < 0 || tm->tm_mon > 11) return 0; literal = cg_months[tm->tm_mon]; len = 3; break;
            case 'B': if (tm->tm_mon < 0 || tm->tm_mon > 11) return 0; literal = cg_months[tm->tm_mon]; break;
            case 'p': literal = tm->tm_hour < 12 ? "AM" : "PM"; break;
            case 'Z': literal = "UTC"; break;
            case 'z': literal = "+0000"; break;
            case 'F': literal = "%Y-%m-%d"; break;
            case 'T': literal = "%H:%M:%S"; break;
            case 'R': literal = "%H:%M"; break;
            case 'D': literal = "%m/%d/%y"; break;
            case 'c': literal = "%a %b %d %H:%M:%S %Y"; break;
            case 'x': literal = "%m/%d/%y"; break;
            case 'X': literal = "%H:%M:%S"; break;
            default: return 0; /* unsupported conversion: fail visibly */
            }
            if (width) {
                if (n < 0) return 0;
                for (int i = width - 1; i >= 0; --i) { number[i] = (char)('0' + n % 10); n /= 10; }
                number[width] = '\0';
                if (n != 0) return 0;
                literal = number;
            }
        }
        if (literal && *literal == '%') {
            char expansion[96];
            size_t xlen = strftime(expansion, sizeof(expansion), literal, tm);
            if (!xlen || xlen >= cap - pos) return 0;
            for (size_t i = 0; i < xlen; ++i) dst[pos++] = expansion[i];
        } else if (literal) {
            if (!len) { while (literal[len]) ++len; }
            if (len >= cap - pos) return 0;
            for (size_t i = 0; i < len; ++i) dst[pos++] = literal[i];
        } else {
            if (pos + 1u >= cap) return 0;
            dst[pos++] = *p;
        }
    }
    dst[pos] = '\0';
    return pos;
}

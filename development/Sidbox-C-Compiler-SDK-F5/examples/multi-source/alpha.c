/* These statics are private to alpha.c. beta.c uses the same names. */
static int offset = 11;
static int adjustment(int number)
{
    return number + offset;
}
int alpha(int value)
{
    return adjustment(value) * 2;
}

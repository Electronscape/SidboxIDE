static int offset = 22;
static int adjustment(int number)
{
    return number + offset;
}
int beta(int value)
{
    return adjustment(value) + 3;
}

/* External functions from other .c files need prototypes before their call. */
int alpha(int value);
int beta(int value);
int wide_value(void);

int main(void)
{
    int value = 0;
    int total = 0;
    while (value < 20) {
        value = value + 1;
        if (value == 4)
            continue;
        if (value == 16)
            break;
        if (value < 12) {
            if (value % 2 == 0)
                total = total + alpha(value);
            else
                total = total + beta(value);
        } else {
            total = total + alpha(beta(value));
        }
    }
    return total + wide_value();
}

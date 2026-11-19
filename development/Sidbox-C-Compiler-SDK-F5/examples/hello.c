extern int sidbox_message(const char *message);

int multiply(int value, int count)
{
    int total = 0;
    while (count > 0) {
        total = total + value;
        count = count - 1;
    }
    return total;
}

int main(void)
{
    if (multiply(6, 7) == 42) {
        sidbox_message("Hello from Sidbox!\n6 * 7 = 42");
        return 0;
    }
    sidbox_message("The calculation failed.");
    return 1;
}

extern void logging(const char*);

int add(int a, int b) {
    logging("entering function: int add(int, int)");
    return a + b;
}

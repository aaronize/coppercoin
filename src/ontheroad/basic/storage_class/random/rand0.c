// 产生随机数
static unsigned long int next = 1; // seed

int rand0(void)
{
    next = next * 1103515245 + 12345;
    return next;
}

void srand1(unsigned int seed)
{
    next = seed;
}

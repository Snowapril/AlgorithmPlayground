#include <stdio.h>
#include <stdbool.h>

int main()
{
    FILE* in = fopen("ct.inp", "r");
    FILE* out = fopen("ct.out", "w");

    unsigned int N;
    fscanf(in, "%u", &N);
    unsigned int diagonalN = 2 * N - 1;
    
    //! 1. Get Input
    //! Memory access 최소화를 위해서 2-dimensional array는 사용하지 않았습니다.
    unsigned int zrayVertical[8];
    unsigned int zrayHorizontal[8];
    unsigned int zrayRightDiagonal[15];
    unsigned int zrayLeftDiagonal[15];
    for (int i = 0; i < N; ++i)
        fscanf(in, "%u", (zrayVertical + i));
    for (int i = 0; i < N; ++i)
        fscanf(in, "%u", (zrayHorizontal + i));
    for (int i = 0; i < diagonalN; ++i)
        fscanf(in, "%u", (zrayRightDiagonal + i));
    for (int i = 0; i < diagonalN; ++i)
        fscanf(in, "%u", (zrayLeftDiagonal + i));

    //! 2. Back-tracking
    unsigned int stack[8], top = 0;
    stack[top++] = (1 << zrayHorizontal[0]) - 1;

    while (top > 0)
    {
        unsigned int depth = top - 1;
        unsigned int curPerm = stack[depth];

        //! z-ray test
        bool passTest = true;
        for (unsigned int i = 0; i < N; ++i)
        {
            if (((1 << i) & curPerm) && (zrayVertical[N - i - 1] == 0 || zrayRightDiagonal[i + depth] == 0 || zrayLeftDiagonal[N - i - 1 + depth] == 0))
            {
                passTest = false;
                break;
            }
        }
        
        if (passTest)
        {
            if (top == N) //! Now traverse is over
                break;
            else //! traverse is not done yet
            {
                for (unsigned int i = 0; i < N; ++i)
                {
                    const bool present = (1 << i) & curPerm;
                    zrayVertical[N - i - 1] -= present;
                    zrayRightDiagonal[i + depth] -= present;
                    zrayLeftDiagonal[N - i - 1 + depth] -= present;
                }
                stack[top++] = (1 << zrayHorizontal[depth + 1]) - 1;
            }
        }
        else
        {
            //! pop stack until permutation satisfied
            while (curPerm == ((1 << N) - (1 << (N - zrayHorizontal[depth]))))
            {
                --top;
                --depth;
                curPerm = stack[depth];
                for (unsigned int i = 0; i < N; ++i)
                {
                    const bool present = (1 << i) & curPerm;
                    zrayVertical[N - i - 1] += present;
                    zrayRightDiagonal[i + depth] += present;
                    zrayLeftDiagonal[N - i - 1 + depth] += present;
                }
            }
            //! reference on http://graphics.stanford.edu/~seander/bithacks.html#NextBitPermutation
            //! Binary number permutation 최적화를 위해 bitwise level operation을 위의 reference에서
            //! 참고하여 작성하였습니다.
            unsigned int t = curPerm | (curPerm - 1);
            stack[depth] = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(curPerm) + 1));
        }
    }
    
    for (unsigned int i = 0; i < top; ++i)
    {
        for (unsigned int j = 0; j < N; ++j)
            if ((1 << (N - j - 1)) & stack[i])
                fprintf(out, "B ");
            else
                fprintf(out, "- ");
        fprintf(out, "\n");
    }

    fclose(out);
    fclose(in);
    return 0;
}
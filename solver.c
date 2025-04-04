#include "sudoku.h"

//Creats maps so the solver doesn't have to do all the math everytime
void initLookup()
{
    int i, idx, startRow, startCol, cellIndex;
    printf("Generateing lookup tables.\n");
    for (i = 0; i < 81; i++)
    {
        //Address to Colum Row and Cell Maps
        AddCol[i] = i % 9;
        AddRow[i] = i / 9;
        AddCel[i] = AddCol[i] / 3 + (AddRow[i] / 3) * 3;
    }

    for (i = 0; i < 9; i++)
    {
        for (idx = 0; idx < 9; idx++)
        {
            //Colum Row and Cell maps back to address.
            colAdds[i][idx] = i + idx * 9;
            rowAdds[i][idx] = i * 9 + idx;
            startRow = (i / 3) * 3;
            startCol = (i % 3) * 3;
            cellIndex = startRow * 9 + startCol;
            celAdds[i][idx] = cellIndex + (idx / 3) * 9 + (idx % 3);
        }
    }
}
//The basic test performed by the solver.   Can value v be plased in address ad
int testAdr(int ad, int v)
{
    int i;
    for (i = 0; i < 9; i++)
    {
        if (ad != colAdds[AddCol[ad]][i] && puzzle[colAdds[AddCol[ad]][i]] == v)
            return 0;
        if (ad != rowAdds[AddRow[ad]][i] && puzzle[rowAdds[AddRow[ad]][i]] == v)
            return 0;
        if (ad != celAdds[AddCel[ad]][i] && puzzle[celAdds[AddCel[ad]][i]] == v)
            return 0;
    }
    return 1;
}

//Identify addresses that need a solution
void findBlanks()
{
    int i;
    blanks[0] = 0;
    for (i = 0; i < 81; i++)
    {
        if (puzzle[i] == 0)
        {
            blanks[blanks[0] + 1] = i;
            blanks[0]++;
        }
    }
}

//Find the possible values that can be pluged into each cell and identify any that only have one option
void simplify()
{
    int i, vals;
stlp:
    for (i = 0; i < blanks[0]; i++)
    {
        posBlanks[i][0] = 0;
        for (vals = 1; vals < 10; vals++)
        {
            if (testAdr(blanks[i + 1], vals) > 0)
            {
                posBlanks[i][posBlanks[i][0] + 1] = vals;
                posBlanks[i][0]++;
            }
        }
    }
    vals = 0;
    for (i = 0; i < blanks[0]; i++)
    {
        if (posBlanks[i][0] == 1)
        {
            vals = 1;
            break;
        }
    }
    showComp();
    if (vals == 1)
    {
        fillones();
        findBlanks();
        goto stlp;
    }
}
//For blanks with only one possble answer plug that answer into the puzzle.
void fillones()
{
    int i;
    for (i = 0; i < blanks[0]; i++)
    {
        if (posBlanks[i][0] == 1)
        {
            puzzle[blanks[i + 1]] = posBlanks[i][1];
        }
    }
}
//This is meant to show how well the simply function has worked but due to float
//suport not being implemented in cc65 currently this function was reduced to just showing
//the count of blank spaces
void showComp()
{

    printf("Unknowns: %d\n", blanks[0]);
}


/// <summary>
/// Sort the blanks from fewiest options to most options
/// </summary>
void optOrder()
{
    int idx, val, opnt;
    opnt = 0;
    for (val = 1; val < 10; val++)
    {
        for (idx = 0; idx < blanks[0]; idx++)
        {
            if (posBlanks[idx][0] == val)
            {
                slvOrder[opnt++] = idx;
            }
        }
    }
}
/// <summary>
/// Brute Force solver, with MVR optimization
/// </summary>
/// <returns>1 if solution found 0 if no solution found.</returns>
int solve()
{
    int sidx, cadd, endidx, idxPnt;
    int valpnt[81];
    int valptEnd;
    int dspcnt;
    long sltst;
    int tarval;
    dspcnt = 0;
    sltst = 0;;
    sidx = 0;
    endidx = blanks[0];
smlp:
    idxPnt = slvOrder[sidx];
    cadd = blanks[idxPnt + 1];
    valpnt[idxPnt] = 0;
    valptEnd = posBlanks[idxPnt][0];
mlp:
    dspcnt++;
    if (dspcnt == 10000)
    {
        printf("%ld soultions tested\n", sltst);
        dspcnt = 0;
    }
    tarval = posBlanks[idxPnt][valpnt[idxPnt] + 1];
    if (testAdr(cadd, tarval) > 0)
    {
        puzzle[cadd] = tarval;
        goto ntlp;
    }
idxinc:
    valpnt[idxPnt]++;
    if (valpnt[idxPnt] == valptEnd)
    {
        goto prlp;
    }
    goto mlp;
ntlp:
    sidx++;
    if (sidx == endidx)
    {
        goto slvd;
    }
    goto smlp;
prlp:
    sltst++;
    if (sidx == 0)
    {
        goto fld;
    }
    puzzle[cadd] = 0;
    valpnt[slvOrder[sidx]] = 0;
    sidx--;
    cadd = blanks[slvOrder[sidx] + 1];
    valptEnd = posBlanks[slvOrder[sidx]][0];
    idxPnt = slvOrder[sidx];
    goto idxinc;
slvd:
    sltst++;
    clrscr();
    printf("Solution #%ld\n", sltst);
    return 1;
fld:
    return 0;
}

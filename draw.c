#include "sudoku.h"

const char TOPG[] = { S_BCOLOR,CH_ULCORNER,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,
    CH_HLINE,CH_TTEE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_TTEE,
    CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_URCORNER,0x00 };

const char MIDL[] = { S_BCOLOR,CH_VLINE,S_IBCOLOR,0x20,CH_VLINE,0x20,CH_VLINE,0x20,
                      S_BCOLOR,CH_VLINE,
                     S_IBCOLOR,0x20,CH_VLINE,0x20,CH_VLINE,0x20,S_BCOLOR,CH_VLINE,
                     S_IBCOLOR,0x20,CH_VLINE,0x20,CH_VLINE,0x20,S_BCOLOR,
                     CH_VLINE,0x00 };
const char MIDD[] = { S_BCOLOR, CH_VLINE,S_IBCOLOR,CH_HLINE,CH_CROSS,CH_HLINE,CH_CROSS,CH_HLINE,S_BCOLOR,CH_VLINE,
                    S_IBCOLOR,CH_HLINE,CH_CROSS,CH_HLINE,CH_CROSS,CH_HLINE,S_BCOLOR,CH_VLINE,
                    S_IBCOLOR,CH_HLINE,CH_CROSS,CH_HLINE,CH_CROSS,CH_HLINE,S_BCOLOR,CH_VLINE,0x00 };
const char DVDR[] = { S_BCOLOR,CH_LTEE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_CROSS,
                    CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_CROSS,
                    CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_RTEE,0x00 };
const char BTM[] = { S_BCOLOR,CH_LLCORNER,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,
                     CH_BTEE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,
                     CH_BTEE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,CH_HLINE,
                     CH_LRCORNER,CH_WHITE,0x00 };
const char VERNUM[] = "1.1a";

/// <summary>
/// Splash screen.   Maybe replace with something fancy someday
/// </summary>
void splash()
{
    printf("Sudoku Solver by Nathanael Nunes\n");
    printf("Build V%s %s\n", VERNUM, __DATE__);

}

/// <summary>
/// Draws a grid and an XY location.
/// Current implementation only supports drawing on the right edge
/// </summary>
/// <param name="sx">x origin for puzzle</param>
/// <param name="sy">y origin for puzzle</param>
void drawGrid(int sx, int sy)
{
    gotoxy(sx, sy);
    printf("%s\n", TOPG);
    printf("%s\n", MIDL);
    printf("%s\n", MIDD);
    printf("%s\n", MIDL);
    printf("%s\n", MIDD);
    printf("%s\n", MIDL);
    printf("%s\n", DVDR);
    printf("%s\n", MIDL);
    printf("%s\n", MIDD);
    printf("%s\n", MIDL);
    printf("%s\n", MIDD);
    printf("%s\n", MIDL);
    printf("%s\n", DVDR);
    printf("%s\n", MIDL);
    printf("%s\n", MIDD);
    printf("%s\n", MIDL);
    printf("%s\n", MIDD);
    printf("%s\n", MIDL);
    printf("%s\n", BTM);
}

/// <summary>
/// Rrequires puzzle to alrady have been drawn.   This will populate the the
/// gridd with the included origin with the current puzzle stored in puzzle[]
/// </summary>
/// <param name="orx">Grid X origin</param>
/// <param name="ory">Grid Y origin</param>
void refillPuzzle(int orx, int ory)
{
    int cx, cy;
    int i;
    cx = wherex();
    cy = wherey();
    for (i = 0; i < 81; i++)
    {
        offsetCursor(orx, ory, i);
        if (puzzle[i] > 0 && puzzle[i] < 10)
            cbm_k_chrout(puzzle[i] + 48);
        else
            cbm_k_chrout(0x20);
    }
    gotoxy(cx, cy);
}

/// <summary>
/// Calculats and moves currsor to puzzle index location
/// </summary>
/// <param name="ox">Puzzle Grid X origin</param>
/// <param name="oy">Puzzle Grid y origin</param>
/// <param name="cidx">puzzle index address</param>
void offsetCursor(int ox, int oy, int cidx)
{
    gotoxy(ox + 1 + (AddCol[cidx] * 2), oy + 1 + (AddRow[cidx] * 2));

}

/// <summary>
/// Draws puzzle grid at current locations and populates values.
/// </summary>
void drawPuzzle()

{
    int cx, cy;
    cx = wherex();
    cy = wherey();
    drawGrid(cx, cy);
    refillPuzzle(cx, cy);
    gotoxy(0, cy + 20);
}
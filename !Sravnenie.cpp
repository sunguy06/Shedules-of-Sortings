#include "TXLib.h"
//#define DEBUG

const int Size            = 2000;
const int AmountOfButtons = 2;

struct stButtons
    {
    RECT Area;
    char text[7];
    COLORREF Color;
    void (*Function) (int* , int , COLORREF);
    };

void BubbleSort(int Array[], int CurrentArruaySize, COLORREF Color);
void SelectionSort(int Array[], int CurrentArraySize, COLORREF Color);
void Swap(int *Number1, int *Number2);
void DrawSchedule (int x, int y, int DigitGraf, COLORREF Color);
void FillArray (int Array[], int CurrentArraySize);
void DrawCarte (stButtons Buttons[]);
int InButtonOrNot (stButtons Buttons[]);
#ifdef DEBUG
void StartEverything (int Array[], int Arrayt[], stButtons Buttons[]);
#else
void StartEverything (int Array[], stButtons Buttons[]);
#endif
void PrintArray(int Array[], int CurrentArraySize);

int main()
    {
    int Array[Size] = {};
    #ifdef DEBUG
    int Arrayt[Size] = {};
    for (int i = 0; i < Size; i++) Arrayt[i] = 0;
    printf("Размер элемента: %d, размер массива: %d", sizeof(int), sizeof(int) * Size);
    #endif

    txCreateWindow(1500, 1000);
    srand(time(NULL));
    txTextCursor (false);
    stButtons Buttons[AmountOfButtons] = { { { 100, 800, 600, 900  }, "Bubble", TX_YELLOW, &BubbleSort},
                                           { { 900, 800, 1400, 900 }, "Choice" ,  TX_GREEN,  &SelectionSort} };

    DrawCarte (Buttons);
    #ifdef DEBUG
    StartEverything (Array, Arrayt, Buttons);
    #else
    StartEverything (Array, Buttons);
    #endif
    }

void BubbleSort(int Array[], int CurrentArraySize, COLORREF Color)
    {
    int Sravn = 0;
    int Obmen = 0;
    int j;
    int i;
    #ifdef DEBUG
        //PrintArray(Array, CurrentArraySize);
        printf("Started BubbleSort\n");
    #endif
    for (i = 0; i < CurrentArraySize - 1; i++)
        {
        for (j = i; j < CurrentArraySize - 2; j++)
            {
            if (Array[i] > Array[j+1])
                {
                assert(i < CurrentArraySize);
                assert(j < CurrentArraySize);
                Swap (&Array[i],  &Array[j+1]);
                Obmen ++;
                Sravn ++;
                }
            else Sravn ++;
            }
        }
    #ifdef DEBUG
        printf ("i:%d, j+1:%d\n", i, j+1);
        //PrintArray(Array, CurrentArraySize);
        printf("Обмены:%d, Сравнения:%d\n", Obmen, Sravn);
    #endif
    DrawSchedule (CurrentArraySize, Obmen, 1, Color);
    DrawSchedule (CurrentArraySize, Sravn, 2, Color);
    #ifdef DEBUG
        printf("Stopped BubbleSort\n");
    #endif
    }

void SelectionSort(int Array[], int CurrentArraySize, COLORREF Color)
    {
    int Sravn = 0;
    int Obmen = 0;

    for (int i = 0; i < CurrentArraySize-1; i++)
        {
        int Min = Array[i];
        int MinI = i;
        for (int j = i + 1; j < CurrentArraySize; j++)
            {
            if (Array[j] < Min)
                {
                Min = Array[j];
                MinI = j;
                }
            Sravn ++;
            }
        Swap(&Array[i], &Array[MinI]);
        Obmen ++;
        }
    DrawSchedule (CurrentArraySize, Obmen, 1, Color);
    DrawSchedule (CurrentArraySize, Sravn, 2, Color);
    }

void Swap(int *Number1, int *Number2)
    {
    int TMP = *Number1;
    *Number1 = *Number2;
    *Number2 = TMP;
    }

void DrawSchedule (int x, int y, int DigitGraf, COLORREF Color)
    {
    #ifdef DEBUG
        printf("Started DrawSchedule\n");
    #endif
    if (DigitGraf == 1) txSetPixel (0 + 600*x/Size, 750 - y/Size, Color);
    if (DigitGraf == 2) txSetPixel (700 + 600*x/Size, 750 - 1500*y/(Size*Size), Color);
    #ifdef DEBUG
        printf("Stopped DrawSchedule\n");
    #endif
    }

void FillArray (int Array[], int CurrentArraySize)
    {
    #ifdef DEBUG
    printf("Started FillArray\n");
    #endif
    for (int i = 0; i < CurrentArraySize; i++) Array[i] = random (20000);
    #ifdef DEBUG
    printf("Stopped FillArray\n");
    #endif
    }

void DrawCarte (stButtons Buttons[])
    {
    txBegin ();
    txSetColor (TX_BLACK);
    txSetFillColor (TX_BLACK);

    txRectangle (200, 0, 600,  100);
    txRectangle (900, 0, 1300, 100);

    txSelectFont ("Times New Roman", 50, 20, false, false, false, false, false);
    txSetColor (TX_GREEN);
    txDrawText (200, 0, 600,  100, "Обмены");
    txSetColor (TX_YELLOW);
    txDrawText (900, 0, 1300, 100, "Сравнения");

    for (int i = 0; i < AmountOfButtons; i ++)
        {
        txSetColor  (Buttons[i].Color, 5);
        txRectangle (Buttons[i].Area.left, Buttons[i].Area.top, Buttons[i].Area.right, Buttons[i].Area.bottom);
        txDrawText  (Buttons[i].Area.left, Buttons[i].Area.top, Buttons[i].Area.right, Buttons[i].Area.bottom, Buttons[i].text);
        }

    txEnd ();
    }

int InButtonOrNot (stButtons Buttons[])
    {
    int Sort = 0;
    for (int i = 0; i < AmountOfButtons; i ++)
        {
        if (In (txMousePos(), Buttons[i].Area))
            {
            Sort = i+1;
            break;
            }
        }
    return Sort;
    }

#ifdef DEBUG
void StartEverything (int Array[], int Arrayt[], stButtons Buttons[])
#else
void StartEverything (int Array[], stButtons Buttons[])
#endif
    {
    #ifdef DEBUG
    printf("Started StartEverything\n");
    #endif
    int Pressure = 0;
    while (true)
        {
        if (txMouseButtons() == 1) Pressure = 1;

        if (Pressure == 1)
            {
            if (txMouseButtons() == 0)
                {
                int buttonin = InButtonOrNot(Buttons);
                if (buttonin == 0) return;
                for (int CurrentArraySize = 10; CurrentArraySize <= Size; CurrentArraySize += 10)
                    {
                    FillArray (Array, CurrentArraySize);
                    assert((buttonin >=0) && (buttonin <= 2));
                    Buttons[buttonin-1].Function(Array, CurrentArraySize, Buttons[buttonin-1].Color);
                    #ifdef DEBUG
                    for (int i=0; i < Size; i++)
                      if (Arrayt[i] != 0) {
                        printf("Element %d of Arrayt is not zero. Memory after Array corrupted!\n", i);
                        assert(1);
                      }
                    #endif
                    }
                Pressure = 0;
                }
            }
        }
    #ifdef DEBUG
    printf("Stopped StartEverything\n");
    #endif
    }

void PrintArray(int Array[], int CurrentArraySize)
    {
    for (int i = 0; i < CurrentArraySize; i ++)
        printf ("%d ", Array[i]);
    printf("\n");
    }


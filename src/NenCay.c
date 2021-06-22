#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NenCay.h"
 
int NhapSize()
{
    int size;
    printf("\nNhap so canh: ");   
    scanf("%d", &size);
    return size;
}
void NhapDuLieu(int Prufer[2][MAXLENGTH], int size)
{
    printf("\nNhap cac canh: \n");
    for (int i = 0; i < size; i++)
        scanf("%d %d", &Prufer[0][i], &Prufer[1][i]);
}
void swap(int a[], int b[], int i, int j)
{
    int m = a[i];
    a[i] = a[j];
    a[j] = m;
    int n = b[i];
    b[i] = b[j];
    b[j] = n;
}
void DEM(int Prufer[2][MAXLENGTH], int dem[], int temp1[], int temp2[], int size)
{
    for (int i = 0; i < size + 1; i++)
        dem[i] = 0;
    for (int i = 0; i < size; i++)
    {
        dem[Prufer[0][i]] = dem[Prufer[0][i]] + 1;
        temp1[i] = Prufer[0][i];
        temp2[i] = Prufer[1][i];
    }
}
void sort(int a[], int b[], int l, int r)
{
    if (r <= l)
        return;
    int i = l - 1, j = r;
    int p = l - 1, q = r;
    while (1)
    {
        while (a[++i] < a[r])
            ;
        while (a[r] < a[--j])
            if (j == l)
                break;
        if (i >= j)
            break;
        swap(a, b, i, j);
        if (a[i] == a[r])
            swap(a, b, ++p, i);
        if (a[j] == a[r])
            swap(a, b, --q, j);
    }
    swap(a, b, i, r);
    j = i - 1;
    i = i + 1;
    for (int k = l; k <= p; k++)
        swap(a, b, k, j--);
    for (int k = r - 1; k >= q; k--)
        swap(a, b, k, i++);
    sort(a, b, l, j);
    sort(a, b, i, r);
}
void Prufer_Code(int Prufer[2][MAXLENGTH], int temp1[], int dem[], int size)
{
    int m, j, k[size];
    for (int i = 1; i < size + 1; i++)
    {
        m = 0;
        if (dem[Prufer[0][0]] == 0)   
            break;
        if (k[i] == i)
            m = 1;
        if (m == 1)
            continue;
        if (dem[i] == 0)
        {
            m = 0;
            printf("%d\t", temp1[i - 1]);  
            j = temp1[i - 1];
            dem[j] = dem[j] - 1;
            while (dem[j] == 0)
            {
                if (j == Prufer[0][0])
                    break;
                printf("%d\t", temp1[j - 1]);
                dem[temp1[j - 1]] = dem[temp1[j - 1]] - 1;
                k[j] = j; 
                j = temp1[j - 1];
            }
        }
    }
}
void NenCay()
{
    int size;
    int Prufer[2][MAXLENGTH];
    size = NhapSize();
    NhapDuLieu(Prufer, size);
    int dem[size + 1];
    int temp1[size];
    int temp2[size];
    DEM(Prufer, dem, temp1, temp2, size);
    sort(temp2, temp1, 0, size - 1);
    printf("\nPrufer code:\t");
    Prufer_Code(Prufer, temp1, dem, size);
    printf("\n");
}
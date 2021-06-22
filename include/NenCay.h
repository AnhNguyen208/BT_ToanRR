#define MAXLENGTH 100

int NhapSize();
void NhapDuLieu(int Prufer[2][MAXLENGTH], int size);
void swap(int a[], int b[], int i, int j);
void DEM(int Prufer[2][MAXLENGTH], int dem[], int temp1[], int temp2[], int size);
void sort(int a[], int b[], int l, int r);
void Prufer_Code(int Prufer[2][MAXLENGTH], int temp1[], int dem[], int size);
void NenCay();
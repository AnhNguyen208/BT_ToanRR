#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NenCay.h"
#include "Tomau.h"
#include "DFS.h"

int main(){
    int menu;
    while (1)
    {
        getchar();
        system("clear");
        cyan();
        printf("Các chức năng của thư viện: \n");
        printf("1. Nén cây\n");
        printf("2. Tô màu đồ thị\n");
        printf("3. Duyệt đồ thi có hướng theo chiều sâu(DFS)\nvà tìm các thành phần liên thông mạnh của đồ thị\n");
        printf("4. Duyệt đồ thị vô hướng theo chiều rộng(BFS)\nvà tìm đường đi ngắn nhất(Dijkstra)\n");
        printf("0. Thoát chương trình\n");
        red();
        printf("Nhâp chức năng muốn thực hiện: \n");
        scanf("%d", &menu);

        if(menu == 1){
            yellow();
            NenCay();
            getchar();
        }
        else if(menu == 2) {
            int temp;
            cyan();
            printf("Đồ thị chính qui (Chọn 1)\n");
            printf("Đồ thị không chính qui (Chọn 2)\n");
            printf("Nhập lựa chọn: \n");
            scanf("%d", &temp);
            yellow();
            if (temp == 1) {
                ToMau("Dothi.txt");
                red();
                printf("Xem kết quả tô màu tại file 'graph.gv.pdf'\n");
            }
            else if(temp == 2) {
                ToMau("Dothi1.txt");
                red();
                printf("Xem kết quả tô màu tại file 'graph.gv.pdf'\n");
            } 
            else {
                white();
                printf("Nhập sai lựa chọn\n");
            }
            
            getchar();
        }
        else if (menu == 3)
        {
            blue();
            printf("Hình ảnh đồ thị tại file 'test.gv.pdf'\n");
            yellow();
            DAG_DFS("Vertex.txt", "Edge.txt");
            getchar();
        }
        else if (menu == 4)
        {
            getchar();
        }
        else if (menu == 5)
        {
            getchar();
        }
        else if (menu == 0)
        {
            reset();
            exit(0);
        }
    }
}
#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define FEE_NORMAL 150000
#define FEE_BHYT 30000

// Hàm tính chi phí dựa trên trạng thái BHYT
int calculateFee(int bhyt_status) {
    return (bhyt_status == 1) ? FEE_BHYT : FEE_NORMAL;
}

// Hàm in hàng chờ và thống kê
void printQueue(int n, int id[], int age[], int bhyt[]) {
    if (n == 0) {
        printf("\n[Thong bao] Hang cho hien dang trong.\n");
        return;
    }

    long long total_revenue = 0;
    int priority_count = 0;

    printf("\n================ DANH SACH HANG CHO ================\n");
    printf("%-5s | %-5s | %-5s | %-12s | %-15s\n", "STT", "ID", "Tuoi", "Trang thai", "Chi phi (VND)");
    printf("----------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int fee = calculateFee(bhyt[i]);
        total_revenue += fee;

        int is_priority = (age[i] >= 70) ? 1 : 0;
        if (is_priority) priority_count++;

        printf("[%2d]  | %-5d | %-5d | %-12s | %d %s\n",
               i, id[i], age[i],
               (bhyt[i] == 1) ? "Co BHYT" : "Khong BHYT",
               fee,
               is_priority ? "(*Uu tien)" : "");
    }
    printf("----------------------------------------------------\n");
    printf("-> Tong so benh nhan: %d\n", n);
    printf("-> Benh nhan uu tien (>= 70 tuoi): %d\n", priority_count);
    printf("-> TONG DOANH THU DU KIEN: %lld VND\n", total_revenue);
    printf("====================================================\n");
}

int main() {
    int id[MAX], age[MAX], bhyt[MAX];
    int n = 0;

    // 1. Nhập số lượng bệnh nhân ban đầu
    do {
        printf("Nhap so luong benh nhan ban dau (0 <= n <= 100): ");
        scanf("%d", &n);
        if (n < 0 || n > MAX) {
            printf("Loi: So luong phai nam trong khoang 0 den 100. Vui long nhap lai.\n");
        }
    } while (n < 0 || n > MAX);

    // 2. Nhập thông tin từng bệnh nhân với ràng buộc chặt chẽ
    for (int i = 0; i < n; i++) {
        printf("\n--- Nhap thong tin benh nhan STT [%d] ---\n", i);

        printf("ID benh nhan: ");
        scanf("%d", &id[i]);

        do {
            printf("Tuoi (1 - 120): ");
            scanf("%d", &age[i]);
            if (age[i] < 1 || age[i] > 120) {
                printf("Loi: Tuoi khong hop le. Vui long nhap lai.\n");
            }
        } while (age[i] < 1 || age[i] > 120);

        do {
            printf("Co BHYT khong? (1 = Co, 0 = Khong): ");
            scanf("%d", &bhyt[i]);
            if (bhyt[i] != 0 && bhyt[i] != 1) {
                printf("Loi: Chi chap nhan 0 hoac 1. Vui long nhap lai.\n");
            }
        } while (bhyt[i] != 0 && bhyt[i] != 1);
    }

    // 3. Hiển thị hàng chờ ban đầu
    printf("\n>>> TRANG THAI HANG CHO BAN DAU <<<");
    printQueue(n, id, age, bhyt);

    // 4. Xử lý nghiệp vụ hủy lượt khám tại vị trí K
    int k;
    printf("\nNhap chi so K can huy luot kham: ");
    scanf("%d", &k);

    if (n == 0) {
        printf("[Loi] Hang cho dang rong. Khong the thuc hien huy!\n");
    } else if (k < 0 || k >= n) {
        printf("[Loi] Chi so K (%d) nam ngoai pham vi. Thao tac bi tu choi!\n", k);
    } else {
        // Thực hiện Shift Array (Dồn dịch mảng)
        for (int i = k; i < n - 1; i++) {
            id[i] = id[i + 1];
            age[i] = age[i + 1];
            bhyt[i] = bhyt[i + 1];
        }
        n--; // Giảm số lượng sau khi dồn

        printf("\n[Thanh cong] Da huy luot kham tai vi tri K = %d.\n", k);

        // 5. Hiển thị lại cấu trúc hàng chờ mới
        printf("\n>>> TRANG THAI HANG CHO SAU KHI CAP NHAT <<<");
        printQueue(n, id, age, bhyt);
    }

    return 0;
}
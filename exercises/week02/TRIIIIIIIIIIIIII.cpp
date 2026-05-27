#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Dinh nghia mot Rap Chieu Phim
class RapChieuPhim {
private:
    int soLuongPhim;
    vector<vector<int>> danhSachYeuCau; // Phim A phai chieu truoc phim B
    vector<int> bacVao;                 // So luong phim dieu kien can chieu truoc
    vector<string> tenPhim;             // Ten cac bo phim tuong ung voi ma so (0, 1, 2...)

public:
    RapChieuPhim(int n) {
        this->soLuongPhim = n;
        danhSachYeuCau.resize(n);
        bacVao.assign(n, 0);
        tenPhim.resize(n);
    }

    // Dat ten cho phim bang Tieng Viet khong dau
    void datTenPhim(int maPhim, string ten) {
        tenPhim[maPhim] = ten;
    }

    // Them dieu kien: Phim `truoc` phai chieu xong thi phim `sau` moi duoc chieu
    void themDieuKienChieu(int truoc, int sau) {
        danhSachYeuCau[truoc].push_back(sau);
        bacVao[sau]++; // Phim `sau` co them 1 phim dieu kien
    }

    // Ham sap xep lich chieu - Dung thuat toan Sap Xep Topo (Topological Sort)
    void sapXepLichChieu() {
        queue<int> hangDoiCho; // Nhung phim da du dieu kien, cho len song

        // Buoc 1: Tim nhung phim khong can dieu kien (Vao xem ngay)
        for (int i = 0; i < soLuongPhim; i++) {
            if (bacVao[i] == 0) {
                hangDoiCho.push(i);
            }
        }

        // Tao mang "Lich Chieu" va bien `suatChieu` (Chinh la v[topo] = x cua cau)
        vector<int> lichChieu(soLuongPhim);
        int suatChieu = 0;

        // Buoc 2: Bat dau xep lich
        while (!hangDoiCho.empty()) {
            int phimHienTai = hangDoiCho.front(); // Day la gia tri x
            hangDoiCho.pop();

            // 🎬 Xep bo phim hien tai vao suat chieu thich hop
            lichChieu[suatChieu] = phimHienTai;
            suatChieu++; // Tang suat chieu tiep theo len

            // Cap nhat cac phim chieu sau
            for (int phimTiepTheo : danhSachYeuCau[phimHienTai]) {
                bacVao[phimTiepTheo]--; // Giam so phim dieu kien di 1
                if (bacVao[phimTiepTheo] == 0) {
                    hangDoiCho.push(phimTiepTheo);
                }
            }
        }

        // Buoc 3: In ra man hinh lich chieu hoan chinh cho khan gia
        if (suatChieu < soLuongPhim) {
            cout << "X Loi roi cau oi! Cac phim bi vong lap dieu kien (Khong the xep lich)!" << endl;
        }
        else {
            cout << "🍿 LICH CHIEU PHIM HOM NAY 🍿" << endl;
            cout << "-----------------------------------" << endl;
            for (int i = 0; i < soLuongPhim; i++) {
                cout << "Suat thu " << i + 1 << ": " << tenPhim[lichChieu[i]] << endl;
            }
            cout << "-----------------------------------" << endl;
            cout << "🎉 Chuc cau xem phim vui ve!" << endl;
        }
    }
};

int main() {
    // Giha su rap co 4 noi dung can chieu
    RapChieuPhim rap(4);

    rap.datTenPhim(0, "Video quang cao bap rang bo");
    rap.datTenPhim(1, "Trailer phim bom tan moi");
    rap.datTenPhim(2, "Phim chinh: Biet Doi Sieu Anh Hung 1");
    rap.datTenPhim(3, "Phim chinh: Biet Doi Sieu Anh Hung 2 (After credit)");

    // Thiet lap dieu kien chieu
    rap.themDieuKienChieu(0, 1); // Quang cao bap phai chieu truoc Trailer
    rap.themDieuKienChieu(1, 2); // Trailer phai chieu truoc Phan 1
    rap.themDieuKienChieu(2, 3); // Phan 1 phai chieu truoc Phan 2

    // Chay he thong xep lich
    rap.sapXepLichChieu();

    // 🛠️ Giu man hinh Console tren Visual Studio 2022 khong bi tat tu dong
    system("pause");
    return 0;
}
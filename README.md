# mo.unit-clone

Smart Dashboard + Power Controller cho Yamaha SR400.

Thay thế toàn bộ hộp cầu chì và rơ-le cơ học bằng ESP32-S3 điều khiển qua relay module, hiển thị tốc độ GPS, vòng tua (RPM từ bô-bin), và thông báo Bluetooth trên màn hình tròn 3.5".

---

## Yêu cầu phần mềm

- [VS Code](https://code.visualstudio.com/)
- Extension **PlatformIO IDE** (cài trong VS Code Extensions)
- Extension **Wokwi Simulator** (cài trong VS Code Extensions)
- Tài khoản Wokwi miễn phí tại [wokwi.com](https://wokwi.com) (để lấy license)

---

## Cài đặt & Chạy thử (Simulation)

### 1. Clone project

```bash
git clone https://github.com/Jajajou/mo-clone.git
cd mo-clone
```

### 2. Mở trong VS Code

```bash
code .
```

PlatformIO sẽ tự động nhận diện project và tải thư viện (LVGL, TFT_eSPI, TinyGPSPlus).

### 3. Lấy Wokwi license

Nhấn `F1` → gõ `Wokwi: Request a New License` → làm theo hướng dẫn trên browser.

### 4. Build firmware

Nhấn `Cmd+Shift+P` (macOS) hoặc `Ctrl+Shift+P` (Windows/Linux) → `PlatformIO: Build`

Hoặc nhấn icon **Build** (dấu tick) ở thanh dưới cùng VS Code.

Lần đầu tải thư viện mất khoảng 5-10 phút. Thành công khi thấy:
```
===== [SUCCESS] =====
```

### 5. Chạy mô phỏng

`F1` → `Wokwi: Start Simulator`

Màn hình sẽ hiển thị đồng hồ tốc độ (0→120 km/h), vòng cung RPM, và các nút bấm xi nhan/đèn pha.

---

## Cấu trúc project

```
mo.unit-clone/
├── BOM.md                  Danh sách linh kiện cần mua (có giá + từ khóa Shopee)
├── platformio.ini          Cấu hình build ESP32-S3
├── diagram.json            Sơ đồ mạch Wokwi
├── wokwi.toml              Config Wokwi simulator
├── include/
│   └── lv_conf.h           Cấu hình LVGL (fonts, widgets)
└── src/
    ├── config.h            Pin mapping và thông số xe SR400
    ├── main.cpp            Vòng lặp chính
    ├── ui/
    │   ├── dashboard.h
    │   └── dashboard.cpp   Giao diện màn hình tròn (LVGL)
    ├── sensors/
    │   ├── gps_reader.*    Đọc GPS NEO-6M qua UART
    │   └── rpm_reader.*    Đọc RPM từ xung bô-bin (interrupt)
    └── control/
        ├── turn_signal.*   Logic xi nhan (nháy, toggle)
        └── headlight.*     Điều khiển đèn pha/cốt
```

---

## Phần cứng (khi làm thật)

Xem [BOM.md](BOM.md) để biết danh sách đầy đủ với giá và nơi mua tại Việt Nam.

Tóm tắt:
- **Vi điều khiển:** ESP32-S3 DevKit N16R8
- **Màn hình:** GC9A01 tròn 3.5" SPI
- **GPS:** NEO-6M
- **Relay:** Module 4 kênh có optocoupler
- **Nguồn:** DC-DC Buck 12V→5V

---

## Trạng thái dự án

- [x] Cấu trúc code cơ bản
- [x] UI LVGL (đồng hồ tốc độ + RPM)
- [x] Mock data để test UI
- [x] Logic xi nhan (nháy, nút bấm)
- [x] Điều khiển đèn pha
- [x] Đọc GPS
- [x] Đọc RPM từ bô-bin
- [ ] Tích hợp Bluetooth (thông báo điện thoại)
- [ ] Gắn lên xe thật

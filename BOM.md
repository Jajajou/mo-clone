# Bill of Materials — mo.unit Clone (SR400)

Tổng chi phí ước tính: **1.500.000 – 2.200.000 VND**

---

## PHASE 1 — Màn hình & Não (Bắt đầu ngay)

| # | Linh kiện | Mục đích | Số lượng | Giá ước tính | Từ khóa tìm trên Shopee |
|---|-----------|----------|----------|--------------|------------------------|
| 1 | ESP32-S3 DevKit N16R8 | Vi điều khiển chính, chạy LVGL | 1 | ~200.000đ | `ESP32-S3 DevKit N16R8` |
| 2 | Màn hình tròn 3.5" GC9A01 SPI | Đồng hồ chính | 1 | ~350.000đ | `round LCD 3.5 inch GC9A01 ESP32` |
| 3 | Module GPS NEO-6M | Lấy tốc độ + tọa độ | 1 | ~90.000đ | `GPS NEO-6M module UART` |
| 4 | Module nguồn DC-DC Buck Mini360 | Hạ 12V → 5V nuôi ESP32 | 2 | ~25.000đ/cái | `DC DC buck converter Mini360 5V` |
| 5 | Diode 1N4007 | Chống ngược cực điện từ bình | 5 | ~5.000đ | `diode 1N4007` |
| 6 | Tụ điện 1000uF 25V | Lọc nhiễu điện bô-bin | 3 | ~5.000đ | `tu dien 1000uF 25V` |

**Tổng Phase 1: ~700.000đ**

---

## PHASE 2 — Điều khiển điện xe (Xi nhan, đèn pha)

| # | Linh kiện | Mục đích | Số lượng | Giá ước tính | Từ khóa tìm trên Shopee |
|---|-----------|----------|----------|--------------|------------------------|
| 7 | Relay module 4 kênh 5V | Bật/tắt đèn pha, xi nhan, còi | 1 | ~50.000đ | `relay module 4 kenh 5V optocoupler` |
| 8 | Optocoupler PC817 | Cách ly tín hiệu nút bấm 12V → 3.3V | 10 | ~15.000đ | `PC817 optocoupler DIP` |
| 9 | Điện trở 1kΩ, 10kΩ (gói hỗn hợp) | Chia áp, kéo trở | 1 gói | ~20.000đ | `dien tro 1/4W kit 600 cai` |
| 10 | Dây điện xe máy 0.5mm² | Đi dây trong xe | 5m | ~30.000đ | `day dien o to may 0.5mm cuon` |
| 11 | Giắc cắm chống nước (Deutsch DT 2/4 pin) | Kết nối module dễ tháo lắp | 4 bộ | ~80.000đ | `jack deutsch DT connector chong nuoc` |
| 12 | Hộp nhựa chống nước IP65 | Đựng relay + mạch nguồn | 1 | ~60.000đ | `hop nhua chong nuoc IP65 115x90mm` |

**Tổng Phase 2: ~255.000đ**

---

## PHASE 3 — Cảm biến vòng tua (RPM)

> SR400 không có OBD2. RPM lấy từ xung đánh lửa bô-bin.

| # | Linh kiện | Mục đích | Số lượng | Giá ước tính | Từ khóa tìm trên Shopee |
|---|-----------|----------|----------|--------------|------------------------|
| 13 | Module so sánh LM393 | Đọc xung tín hiệu bô-bin | 1 | ~15.000đ | `LM393 comparator module` |
| 14 | Zener diode 5.1V | Chặn áp spike từ bô-bin | 5 | ~5.000đ | `zener diode 5.1V 1W` |
| 15 | TVS Diode P6KE15A | Bảo vệ mạch khỏi spike cao áp | 5 | ~20.000đ | `TVS diode P6KE15A` |

**Tổng Phase 3: ~40.000đ**

---

## PHASE 4 — Gắn lên xe (Cơ khí)

| # | Linh kiện | Mục đích | Số lượng | Giá ước tính | Từ khóa tìm trên Shopee |
|---|-----------|----------|----------|--------------|------------------------|
| 16 | RAM Mount ball 1" + arm | Gắn màn hình lên ghi-đông | 1 bộ | ~350.000đ | `RAM mount ball 1 inch handlebar` |
| 17 | Ống co nhiệt hỗn hợp | Bọc mối nối điện | 1 bộ | ~30.000đ | `ong co nhiet heat shrink kit` |
| 18 | Keo Silicone trong suốt | Bịt kín hộp mạch | 1 tuýp | ~30.000đ | `keo silicone trong suot chong nuoc` |
| 19 | Breadboard + dây cắm | Để test trước khi hàn | 1 bộ | ~50.000đ | `breadboard 830 holes jumper wire kit` |

**Tổng Phase 4: ~460.000đ**

---

## Dụng cụ cần có (nếu chưa có)

| Dụng cụ | Giá ước tính | Ghi chú |
|---------|--------------|---------|
| Mỏ hàn nhiệt độ điều chỉnh | ~300.000đ | Hakko FX-888D clone trên Shopee |
| Đồng hồ vạn năng (VOM) | ~150.000đ | Bắt buộc để đo điện áp, tránh chập |
| Kéo tuốt dây | ~50.000đ | |

---

## Thứ tự mua

```
Ngay bây giờ (để bắt đầu mô phỏng và test không cần xe):
→ #1 ESP32-S3 + #2 Màn hình GC9A01 + #3 GPS NEO-6M + #19 Breadboard

Sau khi code UI xong:
→ #4 #5 #6 (mạch nguồn) + #7 #8 #9 #10 (điều khiển điện)

Cuối cùng khi đã test ổn định:
→ #13 #14 #15 (RPM) + #16 #17 #18 (gắn lên xe)
```

---

## Lưu ý khi mua

- Mua thêm **2 cái ESP32-S3** dự phòng (dễ chết khi mới học, giá rẻ)
- Màn hình GC9A01 tìm loại có **sẵn driver board** (không phải bare module)
- GPS NEO-6M mua loại **có ceramic antenna** kèm theo
- **Không mua relay không có optocoupler** — relay rẻ nhất thị trường thường không có cách ly quang, dễ nhiễu

## README DÙNG ĐỂ CÀI ĐẶT VÀ CHẠY CHƯƠNG TRÌNH
## Lưu ý: <br>
## I. Các folder trong thư mục là một chương trình đóng gói để xem được thông tin code đó thì ta vào phần src trong từng folder đó nếu cài đặt cho vi điều khiển theo cơ chế thông thường ta copy code trong file main.cpp vào trong ArduinoIDE và chạy chương trình.
## II. Nếu không thì các folder được đóng gói và biên dịch và thông dịch thông PlatformIO một nền tảng code vi xử lí trên vscode <a href = "https://platformio.org/">Đây là trang chủ</a> và <a href = "https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide">Extension Platform IO trên VSCode</a>. Tải Extension Platform IO và chạy chương trình.
---

## Phần 1: Nối dây theo hình ảnh trong slide để tạo ra một hệ thống:
- Thiết lập 2 sensor IR ở cách nhau 10cm để thực hiện độ đo chính xác hơn so với thiệt lập trong chương trình, IR gồm 3 chân chân OUT nối vào digital output (Cụ thể là chân 3 đối với IR1 và IR2 là chân 4 hoặc ngược lại) và VCC nối vào 5V và GND nối vào GND trên ARDUINO.
- Thiết lập bộ động cơ bước thông qua một bộ điều khiển động cơ và cấp nguồn trực tiếp từ ARDUINO thông qua chân Vin và chân GND.
- Trên bộ điều khiển động cơ bước ta sẽ nối 5 dây từ động cơ bước và cable đầu đực trên đó, tiếp theo sẽ nối 4 dây từ IN1->IN4 lần lượt tới chân 9 tới chân 12 trên ARDUINO.
- Sau đó ta sẽ kết nối một còi để báo hiện chạy quá tốc độ vào chân digital output (cụ thể là chân 13) trên ARDUINO.
- Tiếp tục ta sẽ gắn vào Breadboard một module wifi cụ thể là NODEMCU ESP8266 với 2 chân TX, RX trên NODEMCU tới chân 5,6 trên ARDUINO (Tạo ra một trình Serial khác với Serial gốc để giao tiếp với NODEMCU trên ARDUINO), còn NODEMCU sẽ giao tiếp thông qua chân D4 với trân RX (trên ARDUINO vì trên NODEMCU hỗ trợ 2 Serial với cấu hình trên chân D4 sẽ giúp ta có thể giao tiếp UART với các thiết bị khác).<br>

**==> Như vậy ta đã thiết lập xong mô hình của hệ thống, chuyển sang bước tiếp đó là thiết lập môi trường và nạp code vào hệ thống**

---
## Phần 2: Thiết lập mỗi trường để sử dụng cho cả 2 module điều khiển:
- Đối với ARDUINO:
    - Ta tiến hành cài đặt thêm thư viện TinyStepper_28BYJ_48 vào trong project ARDUINO với <a href = "https://github.com/Stan-Reifel/TinyStepper_28BYJ_48">DOC URL</a> với thư viện này cho phép chung ta tinh chỉnh được nhiều việc với hệ thống điều đó làm cho thuận lợi hơn trong việc điều khiển động cơ bước bằng ARDUINO so với bước thông thường.
    - Ngoài ra chúng ta cũng cần thêm một thư viện SoftwareSerial để giúp chúng ta cấu hình thêm một Serial thứ 2 để gửi dữ liệu tới với <a href="https://docs.arduino.cc/learn/built-in-libraries/software-serial">DOC URL</a>.
    - Hệ thống chương trình sẽ được mô tả như sau:
        - Bước 1: Thiết lập các chân đầu vào cho các module điều khiển và thiết lập một serial thứ 2 cho ARDUINO trên 2 chân digital output (cụ thể là chân 5, 6), ngoài ra ta khởi tạo các giá trị cần thiết cho hệ thống gồm các timer, các giá trị cờ để kiểm tra kết quả và độ dài khoảng cách giữa 2 sensor để xác định tốc độ của phương tiện.
        - Bước 2: Trong hàm setup ta khởi tạo các giá trị cần thiết cho hệ thống (OUTPUT cho còi và các chân điều khiển động cơ và INPUT đối với 2 chân out của IR sensor) và trong đó ta thực hiện khởi tạo 2 serial trên baurate 9600 để giao tiếp với module wifi và cuối cùng là thiết lập đối tượng mạch điều khiển với các chân động cơ điều khiển thông qua hàm connectToPins.
        - Bước 3: Trong hàm RunStepper(bool direction) hàm này có tác dụng điều khiển động cơ bước thông qua thư viện với giá trị truyền vào là hướng đi của động cơ (False tương ứng với giá trị bước đi là âm động cơ sẽ quay cùng chiều kim đồng hồ, True tương ứng với giá trị bước đi là dương động cơ sẽ quay ngược chiều kim đồng hồ), trong hàm ni chung ta có thể thiệt lập tốc độ quay, gia tốc quay, vị trị hiên tại của động cơ, thiết lập số bước quay và thực hiện quay.
        - Bước 4: Cuối cùng là trong hàm Loop() trước hết ta sẽ check các hoạt động nhận về từ module wifi và thực hiện các thao tác như sau:
            - Đối với ***manual*** : Ta sẽ thực hiện điều khiển động cơ thủ công không thông qua 2 IR sensor.
            - Đối với ***auto*** : Ta sẽ thực hiện điều khiển động cơ bằng cách kích hoạt qua 2 IR sensor bằng cách tính vận tốc và kiểm tra điều kiện để thực hiện điều khiển trong đó bao gồm vừa thực hiện động cơ và còn truyền dữ liệu về cho module wifi để hiện thị lên đối với người dùng.
            - Còn lại: Ta thực hiện chức năng cập nhật lại giới hạn tốc độ mà phương tiện có thể di chuyển để thực hiện điều khiển động cơ.

- Đối với ESP8266 NODEMCU:
    - Ta tiến hành thiết lập thêm các thư viện cần sử dụng với ESP8266 NODEMCU là ESP8266WiFi và ESP8266WebServer thông qua 2 document này <a href = "https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi">DOC URL FOR ESP8266WiFi</a> và <a href = "https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WebServer"> DOC URL FOR ESP8266WebServer</a>
    - Hệ thống chương trình sẽ được mô tả như sau:
        - Bước 1: Thiết lập một số biến dùng để tính toán và thực hiện chứa đựng thông tin trang web để render ra cho người dùng.
        - BƯớc 2: Ta thiệt lập tổ hợp các route cho từng slash trang web để thực hiện việc view dữ liệu đồng thời điều khiển chức năng của hệ thống
            - AUTO_CONTROL(): Để thực hiện việc tự đông điều khiển hệ thống và truyền dữ liệu về ARDUINO với chức năng auto để đk động cơ
            - MANUAL_CONTROL(): thực hiện việc điều khiển động cơ mặc định không thông qua động cơ
            - DETECT_VEHICLE(): thực hiện việc phát hiện xe và nhận dữ liệu ARDUINO với chức năng auto để đk động cơ và view dữ liệu cho người dùng.
            - PEMITTED_CONTROL(): Thực hiện việc cập nhật tộc đố của vật giới hạn để điều khiển động cơ.
        - Bước 3: Trong phần Setup() ta thiết lập 2 Serial để vừa debug chương trình và nhận thông qua Serial và truyền dữ liệu về thông qua Serial1, tiếp theo là cấu hình AP(Access Point tức là module tự phát wifi) để các thiệt bị khác có thể kết nối với hệ thống. Tiếp đó là tiến hành cấu hình các slash để thực hiện view dữ liệu, truyền dữ liệu cho ARDUINO bằng cách thay đổi các route trên web. (Ở đây có một điểm ESP8266 xử lí realtime 1 và 1 không được do trong việc nó xử handle các request trên ESP8266 nó sẽ không cho phép nhận dữ liệu từ Serial sau khi đã xử lí xong request thì ta mới nhận dữ liệu được và ESP nó không có cơ chế redirect đến trang mà chỉ cho text/plain để view các tiến trình. Nên ở đây nhóm đã xử lí bằng cách khi vào chế độ AUTO thì ESP8266 sẽ tự động redirect đến trang mà không cần phải nhập vào link trên web sau 4 giây để view dữ liệu một lần và thêm 3 giây để redirect lại trang auto ta mất 7s cho một tiến trình sử dụng.
        - Bước 4: Ta thực hiện việc handle dữ liệu và nhận về tốc độ của vật bên ARDUINO đã detect được và View dữ liệu sau 4s như tiến trình nói ở bước 3.

- Về mức độ tốc độ truyền nhận dữ liệu: Cơ bản là nó khá ngắn và khoảng thời gian chênh lệch nhau cỡ 200ms-3s tùy với chế độ kết nối với ESP8266 và khoảng cách có thể lên tới được 5m để có thể xử lí dữ liệu giữa người dùng và ESP8266.

---
## Phần 3: Các thiết lập lên vi điều khiển:
-   Trước hết khi nạp code vào 2 thiết bị ta cần nhổ các dây TX, RX để tiến hành nạp dữ liệu sau khi nạp xong ta gắn dây vào lại đúng vị trí cần thiết và sử dụng.
-   Đối với việc sử dụng trên ARDUINO đóng vai trò điều khiển động cơ và cấp nguồn nên ta không làm việc trên đó mà chỉ làm bằng cách điều khiển từ xa với ESP8266.
-   Sau khi 2 vi điều khiển đã được cắm điện thì trên các thiết bị như mobile hay pc cần kết nối vào Wifi tên ESP8266_AP với mật khẩu 12345678, tiếp theo ta truy cập đường dẫn <a href = "http://192.168.4.1"> 192.168.4.1 </a> để thực hiện việc vô trang chủ ESP8266.
-   Tiếp đến ta có 2 button để thực hiện các chế độ tự động hay thủ công, ngoài ra ta còn 1 Display screen nếu như ta vào chế độ auto để có thể view dữ liệu qua lần detect vật, và có thêm một form bao gồm 1 button và 1 textbox để nhập tốc độ chỉ định cho vật

---
## Đó là toàn bộ qua trình tiến lập của hệ thống với ESP8266 và ARDUINO để điều khiển động cơ bước trong bài toán Speed Tracking kèm với cảm biến hồng ngoại.



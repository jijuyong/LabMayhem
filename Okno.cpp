#include "Okno.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <windows.h>

void Okno(){
    sf::RenderWindow okno(sf::VideoMode({1600,1000}),"The Etherium- Awakening"); // cua so kich thuoc 1600*1000
    okno.setFramerateLimit(60);// khoa game chay toi da 60 khunh hinh/s de ko bi ton pin

    sf::View gameView(sf::FloatRect({0.f, 0.f}, {1600.f, 1000.f})); // Tạo chiếc Camera cố định
    okno.setView(gameView); // Ép cửa sổ nhìn qua Camera này để không bị lỗi co cụm góc màn hình

    //nap hinh nen 
    sf::Texture pozadi1;
    if (!pozadi1.loadFromFile("Obrazky/background.png")){
        std::cerr<<"Loi khong tim thay hinh nen"<<std::endl;
        return;
    }

    sf::Sprite pozadi2(pozadi1);
    sf::Vector2u bgSize = pozadi1.getSize();
    pozadi2.setScale({1600.f / bgSize.x, 1000.f / bgSize.y});
    // Co giãn ảnh nền cho vừa khít màn hình 1600x1000

    //stiskni ENTER
    std::vector <sf::Texture> nap_gif;
    nap_gif.resize(24);

    // chay cach frame
    for(int i=0;i<24;i++){
        std::string soFrame = std::to_string(i);
        // Tự động nối các đoạn chữ lại thành đường dẫn hoàn chỉnh: "Obrazky/frame/frame_0.png"
        std::string fileName = "Obrazky/frame/frame_" + soFrame+".png";

        if (!nap_gif[i].loadFromFile(fileName)) {
            std::cerr << "Loi nghiem trong: Khong tim thay file -> " << fileName << std::endl;
            return ; // Nếu hụt mất ảnh nào, trả về thất bại ngay lập tức
        }
    }

    //hien thi chu
    sf::Sprite GIF1(nap_gif[0]);
    // Tạo một Sprite để vẽ chữ, mặc định lấy khung hình đầu tiên (số 0)

    //tu dong can giua cchu dua theo kich thuoc cua okno
    sf::Vector2u  text_size = nap_gif[0].getSize();
    GIF1.setOrigin({text_size.x/2.f, text_size.y/2.f});// Đặt "tâm" của bức ảnh chữ vào chính giữa nó
    GIF1.setPosition({1600.f / 2.f, 900.f}); // Đặt chữ ở tọa độ X là chính giữa (800) và đẩy xuống sát đáy Y (900)
    GIF1.setScale({0.5f, 0.5f}); // Thu nhỏ ảnh chữ lại một nửa (0.5) vì ảnh gốc quá to

    // khoi dong bo dem
    sf::Clock bo_dem;// Cái đồng hồ bấm giờ bấm tách tách liên tục
    size_t frame_hien_tai = 0;// Biến ghi nhớ xem đang ở khung hình thứ mấy (bắt đầu từ 0)
    float thoi_gian_chay_frame = 0.04f;//Cứ sau 0.04 giây là phải đổi sang hình tiếp theo (tốc độ chuẩn của phim hoạt hình)

    //vong lap game
    while(okno.isOpen()){
        while(const std::optional<sf::Event> event = okno.pollEvent()){
            // 1. Lắng nghe người chơi: Nếu họ bấm nút X trên cửa sổ thì tắt game
            if (event->is<sf::Event::Closed>()) okno.close();
        }
    
        // 2. Chạy ngầm: Liên tục gọi hàm lật trang sách để cập nhật hình ảnh chữ
        if (nap_gif.empty()) return;// nao khong co anh thi ko chay

        // Kiểm tra xem đồng hồ đếm giờ đã chạy qua mức thời gian quy định (0.04 giây) chưa   
        if (bo_dem.getElapsedTime().asSeconds()>= thoi_gian_chay_frame){
            // Chuyển sang khung hình tiếp theo. Phép chia lấy dư (%) giúp khi chạy đến hình 23 sẽ tự động quay về hình 0
            frame_hien_tai = (frame_hien_tai+1)% nap_gif.size();
            // Thay tấm ảnh mới cho Sprite để hiển thị ra màn hình
            GIF1.setTexture(nap_gif[frame_hien_tai]);
            // Bấm nút Reset đồng hồ về lại số 0 để đếm lượt mới
            bo_dem.restart();
        }

        okno.clear();

        okno.draw(pozadi2);
        okno.draw(GIF1);
        okno.display();

    }
}

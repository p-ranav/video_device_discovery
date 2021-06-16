#include <video_device.hpp>

int main() {

  for (auto& vd: roshi::video_devices()) {
    std::cout << vd.file.string() << "\n";
    std::cout << " Driver: " << vd.driver << "\n";
    std::cout << " Card: " << vd.card << "\n";
    std::cout << " Bus info: " << vd.bus_info << "\n";
    std::cout << " Pixel Format: " << vd.pixel_format << "\n";
    std::cout << " Resolutions:\n";
    for (auto& r: vd.resolutions) {
      std::cout << " - " << r.first << "x" << r.second << "\n";
    }
    std::cout << "\n\n";
  }
  
}

#include <video_device_info.hpp>

int main() {
  for (auto& vd: find_video_devices()) {
    std::cout << vd.file.string() << "\n";
    std::cout << " Driver: " << vd.driver << "\n";
    std::cout << " Card: " << vd.card << "\n";
    std::cout << " Bus info: " << vd.bus_info << "\n";

    std::cout << " Pixel Format:\n";
    for (auto& fmt: vd.pixel_formats) {
      std::cout << " - " << fmt << "\n";
    }
    std::cout << " Resolutions:\n";
    for (auto& r: vd.resolutions) {
      std::cout << " - " << r.first << "x" << r.second << "\n";
    }
    std::cout << "\n\n";
  }
}

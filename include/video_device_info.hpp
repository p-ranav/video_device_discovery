#pragma once
#include <algorithm>
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
namespace fs = std::experimental::filesystem;
#include <helpers.hpp>

struct VideoDeviceInfo {

  // e.g., 0 if /dev/video0
  std::size_t sensor_id;
  
  // e.g., "/dev/video0"
  fs::path file;

  // e.g., `10-bit Bayer RGRG/GBGB`
  std::vector<std::string> pixel_formats;

  // {{width, height}, {width, height}, ...}
  std::vector<std::pair<std::size_t, std::size_t>> resolutions;

  // Name of the driver, a unique NUL-terminated ASCII string.
  // For example: "bttv". Driver specific applications
  // can use this information to verify the driver identity.
  std::string driver;

  // Name of the device, a NUL-terminated UTF-8 string.
  // For example: "Yoyodyne TV/FM". One driver may support different brands or models of video hardware.
  // This information is intended for users, for example in a menu of available devices.
  //
  // Since multiple TV cards of the same brand may be installed which are supported
  // by the same driver, this name should be combined with the character device file name (e. g. /dev/video2)
  // or the bus_info string to avoid ambiguities.
  std::string card;

  // Location of the device in the system, a NUL-terminated ASCII string.
  // For example: “PCI:0000:05:06.0”. This information is intended for users,
  // to distinguish multiple identical devices.
  //
  // The bus_info must start with “PCI:” for PCI boards, “PCIe:” for PCI Express boards,
  // "usb-" for USB devices, "I2C:" for i2c devices, "ISA:" for ISA devices,
  // "parport" for parallel port devices and "platform:" for platform devices.
  std::string bus_info;
};

struct video_device_info_less_than {
  inline bool operator() (const VideoDeviceInfo& struct1, const VideoDeviceInfo& struct2) {
    return (struct1.file < struct2.file);
  }
};  


// discovers and returns a list of video devices connected to the sysem
// @param filter_pixel_formats - a list of pixel formats. If provided, this function
//        will only choose video devices that support one of the pixel formats in the list
// @return vector of video devices discovered that meet the requirements of the input
std::vector<VideoDeviceInfo>
find_video_devices(const std::vector<std::string>& filter_pixel_formats = {});

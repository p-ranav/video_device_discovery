#pragma once
#include <algorithm>
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
namespace fs = std::experimental::filesystem;
#include <helpers.hpp>

namespace roshi {

struct VideoDevice {
  // e.g., "/dev/video0"
  fs::path file;

  // e.g., `10-bit Bayer RGRG/GBGB`
  std::string pixel_format;

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

struct video_device_less_than {
  inline bool operator() (const VideoDevice& struct1, const VideoDevice& struct2) {
    return (struct1.file < struct2.file);
  }
};

static inline std::vector<VideoDevice> video_devices() {
  std::vector<roshi::VideoDevice> video_devices;
  
  for (auto& device: get_video_device_files()) {

    VideoDevice new_device;
    new_device.file = device;

    int fd;
    fd = open(device.string().c_str(), O_RDWR);
    if (fd == -1) {
      // couldn't find capture device
      perror("Failed to open video device");
      return {};
    }

    struct v4l2_capability capability;
    if(ioctl(fd, VIDIOC_QUERYCAP, &capability) < 0){
      perror("Failed to get device capabilities, VIDIOC_QUERYCAP");
      return {};
    }

    new_device.driver = std::string{reinterpret_cast<const char*>(capability.driver)};
    new_device.bus_info = std::string{reinterpret_cast<const char*>(capability.bus_info)};
    new_device.card = std::string{reinterpret_cast<const char*>(capability.card)};
    
    // Get supported resolutions
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    struct v4l2_fmtdesc fmt;
    struct v4l2_frmsizeenum frmsize;
    struct v4l2_frmivalenum frmival;

    fmt.index = 0;
    fmt.type = type;
    while (ioctl(fd, VIDIOC_ENUM_FMT, &fmt) >= 0) {
      frmsize.pixel_format = fmt.pixelformat;
      new_device.pixel_format = pixfmt_to_string(fmt.pixelformat);
      frmsize.index = 0;
      while (ioctl(fd, VIDIOC_ENUM_FRAMESIZES, &frmsize) >= 0) {
	if (frmsize.type == V4L2_FRMSIZE_TYPE_DISCRETE) {
	  new_device.resolutions.push_back(std::make_pair(frmsize.discrete.width, frmsize.discrete.height));
	} else if (frmsize.type == V4L2_FRMSIZE_TYPE_STEPWISE) {
	  new_device.resolutions.push_back(std::make_pair(frmsize.stepwise.max_width, frmsize.stepwise.max_height));
	}
	frmsize.index++;
      }
      fmt.index++;
    }

    video_devices.push_back(new_device);
  }

  // sort by file, e.g., /dev/video0, /dev/video1, /dev/video2, ...
  std::sort(video_devices.begin(), video_devices.end(), video_device_less_than());

  return video_devices;
}

}

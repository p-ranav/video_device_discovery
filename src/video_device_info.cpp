#include <video_device_info.hpp>

std::vector<VideoDeviceInfo>
find_video_devices(const std::vector<std::string>& filter_pixel_formats) {
  std::vector<VideoDeviceInfo> video_devices;
  
  for (auto& device: get_video_device_files()) {

    VideoDeviceInfo new_device;
    new_device.file = device;

    // Save sensor_id
    std::string split_on = "/dev/video";
    std::stringstream os(device.string().substr(split_on.length()));
    os >> new_device.sensor_id;

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

    fmt.index = 0;
    fmt.type = type;
    while (ioctl(fd, VIDIOC_ENUM_FMT, &fmt) >= 0) {
      frmsize.pixel_format = fmt.pixelformat;
      new_device.pixel_formats.push_back(pixfmt_to_string(fmt.pixelformat));
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
    
    if (filter_pixel_formats.empty()) {
      // no filter
      video_devices.push_back(new_device);
    } else {
      // filter by pixel format
      for (auto& pxlfmt: filter_pixel_formats) {
	for (auto& supported_formats: new_device.pixel_formats) {
	  if (supported_formats.find(pxlfmt) != std::string::npos) {
	    video_devices.push_back(new_device);
	    break;
	  }
	}
      }
    }
  }

  // sort by file, e.g., /dev/video0, /dev/video1, /dev/video2, ...
  std::sort(video_devices.begin(), video_devices.end(), video_device_info_less_than());

  return video_devices;
}

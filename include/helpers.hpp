#pragma once
#include <algorithm>
#include <experimental/filesystem>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
namespace fs = std::experimental::filesystem;

#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <linux/v4l2-subdev.h>
#include <vector>

// xioctl is a wrapper function over ioctl.
// ioctl() is a function to manipulate device parameters of special files
int xioctl(int fd, int request, void *arg);

// returns true if s1 contains s2
bool string_contains(const std::string& s1, const std::string& s2);

// returns a string representation of a video device pixel format 
std::string pixfmt_to_string(__u32 format);

// discovers all connected video devices
// returns a list of paths, e.g., {"/dev/video0", "/dev/video1", ...}
std::vector<fs::path> get_video_device_files();

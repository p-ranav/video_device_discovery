#include <helpers.hpp>

int xioctl(int fd, int request, void *arg) {
  int r;
  do {
    r = ioctl (fd, request, arg);
  } while (-1 == r && EINTR == errno);
  return r;
}

bool string_contains(const std::string& s1, const std::string& s2) {
  return (s1.find(s2) != std::string::npos);
}

std::string pixfmt_to_string(__u32 format) {
  auto num2s = [](unsigned num, bool is_hex = true) -> std::string {
    char buf[16];
    
    if (is_hex)
      sprintf(buf, "0x%08x", num);
    else
      sprintf(buf, "%u", num);
    return buf;
  };
  
  switch (format) {
  case V4L2_PIX_FMT_RGB332: return "8-bit RGB 3-3-2";
  case V4L2_PIX_FMT_RGB444: return "16-bit A/XRGB 4-4-4-4";
  case V4L2_PIX_FMT_ARGB444: return "16-bit ARGB 4-4-4-4";
  case V4L2_PIX_FMT_XRGB444: return "16-bit XRGB 4-4-4-4";
  case V4L2_PIX_FMT_RGB555: return "16-bit A/XRGB 1-5-5-5";
  case V4L2_PIX_FMT_ARGB555: return "16-bit ARGB 1-5-5-5";
  case V4L2_PIX_FMT_XRGB555: return "16-bit XRGB 1-5-5-5";
  case V4L2_PIX_FMT_RGB565: return "16-bit RGB 5-6-5";
  case V4L2_PIX_FMT_RGB555X: return "16-bit A/XRGB 1-5-5-5 BE";
  case V4L2_PIX_FMT_ARGB555X: return "16-bit ARGB 1-5-5-5 BE";
  case V4L2_PIX_FMT_XRGB555X: return "16-bit XRGB 1-5-5-5 BE";
  case V4L2_PIX_FMT_RGB565X: return "16-bit RGB 5-6-5 BE";
  case V4L2_PIX_FMT_BGR666: return "18-bit BGRX 6-6-6-14";
  case V4L2_PIX_FMT_BGR24: return "24-bit BGR 8-8-8";
  case V4L2_PIX_FMT_RGB24: return "24-bit RGB 8-8-8";
  case V4L2_PIX_FMT_BGR32: return "32-bit BGRA/X 8-8-8-8";
  case V4L2_PIX_FMT_ABGR32: return "32-bit BGRA 8-8-8-8";
  case V4L2_PIX_FMT_XBGR32: return "32-bit BGRX 8-8-8-8";
  case V4L2_PIX_FMT_RGB32: return "32-bit A/XRGB 8-8-8-8";
  case V4L2_PIX_FMT_ARGB32: return "32-bit ARGB 8-8-8-8";
  case V4L2_PIX_FMT_XRGB32: return "32-bit XRGB 8-8-8-8";
  case V4L2_PIX_FMT_GREY: return "8-bit Greyscale";
  case V4L2_PIX_FMT_Y4: return "4-bit Greyscale";
  case V4L2_PIX_FMT_Y6: return "6-bit Greyscale";
  case V4L2_PIX_FMT_Y10: return "10-bit Greyscale";
  case V4L2_PIX_FMT_Y12: return "12-bit Greyscale";
  case V4L2_PIX_FMT_Y16: return "16-bit Greyscale";
  case V4L2_PIX_FMT_Y16_BE: return "16-bit Greyscale BE";
  case V4L2_PIX_FMT_Y10BPACK: return "10-bit Greyscale (Packed)";
  case V4L2_PIX_FMT_Y8I: return "Interleaved 8-bit Greyscale";
  case V4L2_PIX_FMT_Y12I: return "Interleaved 12-bit Greyscale";
  case V4L2_PIX_FMT_Z16: return "16-bit Depth";
  case V4L2_PIX_FMT_INZI: return "Planar 10:16 Greyscale Depth";
  case V4L2_PIX_FMT_PAL8: return "8-bit Palette";
  case V4L2_PIX_FMT_UV8: return "8-bit Chrominance UV 4-4";
  case V4L2_PIX_FMT_YVU410: return "Planar YVU 4:1:0";
  case V4L2_PIX_FMT_YVU420: return "Planar YVU 4:2:0";
  case V4L2_PIX_FMT_YUYV: return "YUYV 4:2:2";
  case V4L2_PIX_FMT_YYUV: return "YYUV 4:2:2";
  case V4L2_PIX_FMT_YVYU: return "YVYU 4:2:2";
  case V4L2_PIX_FMT_UYVY: return "UYVY 4:2:2";
  case V4L2_PIX_FMT_VYUY: return "VYUY 4:2:2";
  case V4L2_PIX_FMT_YUV422P: return "Planar YUV 4:2:2";
  case V4L2_PIX_FMT_YUV411P: return "Planar YUV 4:1:1";
  case V4L2_PIX_FMT_Y41P: return "YUV 4:1:1 (Packed)";
  case V4L2_PIX_FMT_YUV444: return "16-bit A/XYUV 4-4-4-4";
  case V4L2_PIX_FMT_YUV555: return "16-bit A/XYUV 1-5-5-5";
  case V4L2_PIX_FMT_YUV565: return "16-bit YUV 5-6-5";
  case V4L2_PIX_FMT_YUV32: return "32-bit A/XYUV 8-8-8-8";
  case V4L2_PIX_FMT_YUV410: return "Planar YUV 4:1:0";
  case V4L2_PIX_FMT_YUV420: return "Planar YUV 4:2:0";
  case V4L2_PIX_FMT_HI240: return "8-bit Dithered RGB (BTTV)";
  case V4L2_PIX_FMT_HM12: return "YUV 4:2:0 (16x16 Macroblocks)";
  case V4L2_PIX_FMT_M420: return "YUV 4:2:0 (M420)";
  case V4L2_PIX_FMT_NV12: return "Y/CbCr 4:2:0";
  case V4L2_PIX_FMT_NV21: return "Y/CrCb 4:2:0";
  case V4L2_PIX_FMT_NV16: return "Y/CbCr 4:2:2";
  case V4L2_PIX_FMT_NV61: return "Y/CrCb 4:2:2";
  case V4L2_PIX_FMT_NV24: return "Y/CbCr 4:4:4";
  case V4L2_PIX_FMT_NV42: return "Y/CrCb 4:4:4";
  case V4L2_PIX_FMT_NV12M: return "Y/CbCr 4:2:0 (N-C)";
  case V4L2_PIX_FMT_NV21M: return "Y/CrCb 4:2:0 (N-C)";
  case V4L2_PIX_FMT_NV16M: return "Y/CbCr 4:2:2 (N-C)";
  case V4L2_PIX_FMT_NV61M: return "Y/CrCb 4:2:2 (N-C)";
  case V4L2_PIX_FMT_NV12MT: return "Y/CbCr 4:2:0 (64x32 MB, N-C)";
  case V4L2_PIX_FMT_NV12MT_16X16: return "Y/CbCr 4:2:0 (16x16 MB, N-C)";
  case V4L2_PIX_FMT_YUV420M: return "Planar YUV 4:2:0 (N-C)";
  case V4L2_PIX_FMT_YVU420M: return "Planar YVU 4:2:0 (N-C)";
  case V4L2_PIX_FMT_YUV422M: return "Planar YUV 4:2:2 (N-C)";
  case V4L2_PIX_FMT_YVU422M: return "Planar YVU 4:2:2 (N-C)";
  case V4L2_PIX_FMT_YUV444M: return "Planar YUV 4:4:4 (N-C)";
  case V4L2_PIX_FMT_YVU444M: return "Planar YVU 4:4:4 (N-C)";
  case V4L2_PIX_FMT_SBGGR8: return "8-bit Bayer BGBG/GRGR";
  case V4L2_PIX_FMT_SGBRG8: return "8-bit Bayer GBGB/RGRG";
  case V4L2_PIX_FMT_SGRBG8: return "8-bit Bayer GRGR/BGBG";
  case V4L2_PIX_FMT_SRGGB8: return "8-bit Bayer RGRG/GBGB";
  case V4L2_PIX_FMT_SBGGR10: return "10-bit Bayer BGBG/GRGR";
  case V4L2_PIX_FMT_SGBRG10: return "10-bit Bayer GBGB/RGRG";
  case V4L2_PIX_FMT_SGRBG10: return "10-bit Bayer GRGR/BGBG";
  case V4L2_PIX_FMT_SRGGB10: return "10-bit Bayer RGRG/GBGB";
  case V4L2_PIX_FMT_SBGGR10P: return "10-bit Bayer BGBG/GRGR Packed";
  case V4L2_PIX_FMT_SGBRG10P: return "10-bit Bayer GBGB/RGRG Packed";
  case V4L2_PIX_FMT_SGRBG10P: return "10-bit Bayer GRGR/BGBG Packed";
  case V4L2_PIX_FMT_SRGGB10P: return "10-bit Bayer RGRG/GBGB Packed";
  case V4L2_PIX_FMT_SBGGR10ALAW8: return "8-bit Bayer BGBG/GRGR (A-law)";
  case V4L2_PIX_FMT_SGBRG10ALAW8: return "8-bit Bayer GBGB/RGRG (A-law)";
  case V4L2_PIX_FMT_SGRBG10ALAW8: return "8-bit Bayer GRGR/BGBG (A-law)";
  case V4L2_PIX_FMT_SRGGB10ALAW8: return "8-bit Bayer RGRG/GBGB (A-law)";
  case V4L2_PIX_FMT_SBGGR10DPCM8: return "8-bit Bayer BGBG/GRGR (DPCM)";
  case V4L2_PIX_FMT_SGBRG10DPCM8: return "8-bit Bayer GBGB/RGRG (DPCM)";
  case V4L2_PIX_FMT_SGRBG10DPCM8: return "8-bit Bayer GRGR/BGBG (DPCM)";
  case V4L2_PIX_FMT_SRGGB10DPCM8: return "8-bit Bayer RGRG/GBGB (DPCM)";
  case V4L2_PIX_FMT_SBGGR12: return "12-bit Bayer BGBG/GRGR";
  case V4L2_PIX_FMT_SGBRG12: return "12-bit Bayer GBGB/RGRG";
  case V4L2_PIX_FMT_SGRBG12: return "12-bit Bayer GRGR/BGBG";
  case V4L2_PIX_FMT_SRGGB12: return "12-bit Bayer RGRG/GBGB";
  case V4L2_PIX_FMT_SBGGR12P: return "12-bit Bayer BGBG/GRGR Packed";
  case V4L2_PIX_FMT_SGBRG12P: return "12-bit Bayer GBGB/RGRG Packed";
  case V4L2_PIX_FMT_SGRBG12P: return "12-bit Bayer GRGR/BGBG Packed";
  case V4L2_PIX_FMT_SRGGB12P: return "12-bit Bayer RGRG/GBGB Packed";
  case V4L2_PIX_FMT_SBGGR16: return "16-bit Bayer BGBG/GRGR";
  case V4L2_PIX_FMT_SGBRG16: return "16-bit Bayer GBGB/RGRG";
  case V4L2_PIX_FMT_SGRBG16: return "16-bit Bayer GRGR/BGBG";
  case V4L2_PIX_FMT_SRGGB16: return "16-bit Bayer RGRG/GBGB";
  case V4L2_PIX_FMT_SN9C20X_I420: return "GSPCA SN9C20X I420";
  case V4L2_PIX_FMT_SPCA501: return "GSPCA SPCA501";
  case V4L2_PIX_FMT_SPCA505: return "GSPCA SPCA505";
  case V4L2_PIX_FMT_SPCA508: return "GSPCA SPCA508";
  case V4L2_PIX_FMT_STV0680: return "GSPCA STV0680";
  case V4L2_PIX_FMT_TM6000: return "A/V + VBI Mux Packet";
  case V4L2_PIX_FMT_CIT_YYVYUY: return "GSPCA CIT YYVYUY";
  case V4L2_PIX_FMT_KONICA420: return "GSPCA KONICA420";
  case V4L2_PIX_FMT_HSV24: return "24-bit HSV 8-8-8";
  case V4L2_PIX_FMT_HSV32: return "32-bit XHSV 8-8-8-8";
  case V4L2_SDR_FMT_CU8: return "Complex U8";
  case V4L2_SDR_FMT_CU16LE: return "Complex U16LE";
  case V4L2_SDR_FMT_CS8: return "Complex S8";
  case V4L2_SDR_FMT_CS14LE: return "Complex S14LE";
  case V4L2_SDR_FMT_RU12LE: return "Real U12LE";
  case V4L2_SDR_FMT_PCU16BE: return "Planar Complex U16BE";
  case V4L2_SDR_FMT_PCU18BE: return "Planar Complex U18BE";
  case V4L2_SDR_FMT_PCU20BE: return "Planar Complex U20BE";
  case V4L2_TCH_FMT_DELTA_TD16: return "16-bit Signed Deltas";
  case V4L2_TCH_FMT_DELTA_TD08: return "8-bit Signed Deltas";
  case V4L2_TCH_FMT_TU16: return "16-bit Unsigned Touch Data";
  case V4L2_TCH_FMT_TU08: return "8-bit Unsigned Touch Data";
  case V4L2_META_FMT_VSP1_HGO: return "R-Car VSP1 1-D Histogram";
  case V4L2_META_FMT_VSP1_HGT: return "R-Car VSP1 2-D Histogram";
  case V4L2_PIX_FMT_MJPEG: return "Motion-JPEG";
  case V4L2_PIX_FMT_JPEG: return "JFIF JPEG";
  case V4L2_PIX_FMT_DV: return "1394";
  case V4L2_PIX_FMT_MPEG: return "MPEG-1/2/4";
  case V4L2_PIX_FMT_H264: return "H.264";
  case V4L2_PIX_FMT_H264_NO_SC: return "H.264 (No Start Codes)";
  case V4L2_PIX_FMT_H264_MVC: return "H.264 MVC";
  case V4L2_PIX_FMT_H263: return "H.263";
  case V4L2_PIX_FMT_MPEG1: return "MPEG-1 ES";
  case V4L2_PIX_FMT_MPEG2: return "MPEG-2 ES";
  case V4L2_PIX_FMT_MPEG4: return "MPEG-4 Part 2 ES";
  case V4L2_PIX_FMT_XVID: return "Xvid";
  case V4L2_PIX_FMT_VC1_ANNEX_G: return "VC-1 (SMPTE 412M Annex G)";
  case V4L2_PIX_FMT_VC1_ANNEX_L: return "VC-1 (SMPTE 412M Annex L)";
  case V4L2_PIX_FMT_VP8: return "VP8";
  case V4L2_PIX_FMT_VP9: return "VP9";
  case V4L2_PIX_FMT_HEVC: return "HEVC";
  case V4L2_PIX_FMT_CPIA1: return "GSPCA CPiA YUV";
  case V4L2_PIX_FMT_WNVA: return "WNVA";
  case V4L2_PIX_FMT_SN9C10X: return "GSPCA SN9C10X";
  case V4L2_PIX_FMT_PWC1: return "Raw Philips Webcam Type (Old)";
  case V4L2_PIX_FMT_PWC2: return "Raw Philips Webcam Type (New)";
  case V4L2_PIX_FMT_ET61X251: return "GSPCA ET61X251";
  case V4L2_PIX_FMT_SPCA561: return "GSPCA SPCA561";
  case V4L2_PIX_FMT_PAC207: return "GSPCA PAC207";
  case V4L2_PIX_FMT_MR97310A: return "GSPCA MR97310A";
  case V4L2_PIX_FMT_JL2005BCD: return "GSPCA JL2005BCD";
  case V4L2_PIX_FMT_SN9C2028: return "GSPCA SN9C2028";
  case V4L2_PIX_FMT_SQ905C: return "GSPCA SQ905C";
  case V4L2_PIX_FMT_PJPG: return "GSPCA PJPG";
  case V4L2_PIX_FMT_OV511: return "GSPCA OV511";
  case V4L2_PIX_FMT_OV518: return "GSPCA OV518";
  case V4L2_PIX_FMT_JPGL: return "JPEG Lite";
  case V4L2_PIX_FMT_SE401: return "GSPCA SE401";
  case V4L2_PIX_FMT_S5C_UYVY_JPG: return "S5C73MX interleaved UYVY/JPEG";
  case V4L2_PIX_FMT_MT21C: return "Mediatek Compressed Format";
  default:
    return std::string("Unknown (") + num2s(format) + ")";
  }
}

std::vector<fs::path> get_video_device_files() {
  std::vector<fs::path> result; 
  auto root = fs::path("/sys/class/video4linux");
  for(auto& p: fs::directory_iterator(root)) {
    if (fs::is_symlink(p)) {
      auto absolute_path = fs::read_symlink(p);
      if (absolute_path.is_relative()) {
	absolute_path = fs::canonical(root / absolute_path);
      }
      if (string_contains(absolute_path.filename().string(), std::string{"video"}))
	result.push_back(fs::path{"/dev"} / absolute_path.filename());
    }
  }
  return result;
}

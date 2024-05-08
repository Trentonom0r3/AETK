/*****************************************************************/ /**
                                                                     * \file   Image.hpp
                                                                     * \brief  A class for handling images
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   March 2024
                                                                     *********************************************************************/

#ifndef IMAGE_HPP
#define IMAGE_HPP
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

#include <stb_image_write.h>

#include "AETK/AEGP/Core/Core.hpp"

// Include library headers conditionally
#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#endif

#ifdef USE_IMAGEMAGICK
#include <Magick++.h>
#endif

struct UniformImage
{
    // Pixel data pointer. Using a void* allows for flexibility with different
    // data types.
    void *data;

    // Image dimensions
    int width;
    int height;

    // Depth per channel in bits (e.g., 8, 16, 32)
    // Since channels are always 4, we don't need a separate variable for it
    int bitDepth;

    // Row pitch: The number of bytes from one row of pixels in memory to the
    // next row. This accounts for any padding at the end of each row.
    size_t rowPitch;

    // Constructor for initializing the struct with default values
    UniformImage() : data(nullptr), width(0), height(0), bitDepth(0), rowPitch(0) {}

    // Custom constructor for easy initialization
    UniformImage(void *pData, int w, int h, int depth, size_t pitch)
        : data(pData), width(w), height(h), bitDepth(depth), rowPitch(pitch)
    {
    }

    // Destructor
    ~UniformImage()
    {
        // If the structure owns 'data', properly free it here
        // Consider the memory management strategy based on your use case
        data = nullptr;
    }

    // Since channels are fixed to 4, you might add utility functions that
    // specifically handle 4-channel data Example: Converting to and from RGBA
    // format used by specific libraries
};

class Image
{ // Format is always ARGB
  public:
    explicit Image(WorldPtr world) : mWorld(world) {}

    static inline UniformImage data(WorldPtr mWorld)
    {
        if (!mWorld)
		{
			return UniformImage();
		}
        std::tuple<A_long, A_long> size = WorldSuite().getSize(mWorld);
        auto rowbytes = WorldSuite().getRowBytes(mWorld);
        void *baseAddr = nullptr;
        int bitDepth = 8; // Default to 8, adjust based on actual data
        switch (WorldSuite().getType(mWorld))
        {
        case WorldType::NONE:
            break;
        case WorldType::W8:
            baseAddr = WorldSuite().getBaseAddr8(mWorld);
            break;
        case WorldType::W16:
            baseAddr = WorldSuite().getBaseAddr16(mWorld);
            bitDepth = 16;
            break;
        case WorldType::W32:
            baseAddr = WorldSuite().getBaseAddr32(mWorld);
            bitDepth = 32;
            break;
        }
        return UniformImage(baseAddr, std::get<0>(size), std::get<1>(size), bitDepth, rowbytes);
    }
// functions
#ifdef USE_OPENCV
    cv::Mat toFormat() {}            // Implement conversion to cv::Mat
    UniformImage toUniformImage() {} // Implement conversion to UniformImage
#endif

#ifdef USE_IMAGEMAGICK
    Magick::Image toFormat() {}      // Implement conversion to Magick::Image
    UniformImage toUniformImage() {} // Implement conversion to UniformImage
#endif

    // New method to save the image using stb_image_write.h
    static inline void saveImage(const std::string &filename, const std::string &format, UniformImage img)
    {
        auto imageData = img; // Assume this returns your UniformImage type
                              // with image data
        int width = imageData.width;
        int height = imageData.height;
        int channels = 4; // Assuming ARGB format (4 channels)

        // Convert ARGB to RGBA
        unsigned char *rgba = new unsigned char[width * height * channels];
        unsigned char *argb =
            static_cast<unsigned char *>(imageData.data); // Assuming imageData.data is your raw ARGB data

        for (int i = 0; i < width * height; ++i)
        {
            rgba[i * 4 + 0] = argb[i * 4 + 1]; // R
            rgba[i * 4 + 1] = argb[i * 4 + 2]; // G
            rgba[i * 4 + 2] = argb[i * 4 + 3]; // B
            rgba[i * 4 + 3] = argb[i * 4 + 0]; // A (moved from the first to the last position)
        }

        // Save the image
        if (format == "png")
        {
            stbi_write_png(filename.c_str(), width, height, channels, rgba, width * channels);
        }
        else if (format == "bmp")
        {
            stbi_write_bmp(filename.c_str(), width, height, channels, rgba);
        }
        else if (format == "tga")
        {
            stbi_write_tga(filename.c_str(), width, height, channels, rgba);
        }

        // Cleanup
        delete[] rgba;
    }

  private:
    WorldPtr mWorld;
};

#endif // IMAGE_HPP

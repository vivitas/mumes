#include "open_exr_io.h"

#include <ImfRgbaFile.h>
#include <ImathBox.h>

using namespace Imath;

void
writeRgba1
(
        const char fileName[],
        const Rgba *pixels,
        int width,
        int height
)
{
    RgbaOutputFile file(fileName, width, height, WRITE_RGBA); // 1
    file.setFrameBuffer(pixels, 1, width); // 2
    file.writePixels(height); // 3
}

void
readRgba1
(
        const char fileName[],
        Array2D<Rgba> &pixels,
        int &width,
        int &height
)
{
    RgbaInputFile file(fileName);
    Box2i dw = file.dataWindow();
    width = dw.max.x - dw.min.x + 1;
    height = dw.max.y - dw.min.y + 1;
    pixels.resizeErase(height, width);
    file.setFrameBuffer(&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
    file.readPixels(dw.min.y, dw.max.y);
}

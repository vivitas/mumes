#include "open_exr_io.h"

#include <ImfRgbaFile.h>
#include <ImathBox.h>
#include <algorithm>

using namespace Imath;
using namespace std;

float
pw (float x, int y)
{
    float p = 1;

    while (y)
    {
	if (y & 1)
	    p *= x;

	x *= x;
	y >>= 1;
    }

    return p;
}
void
sp (Array2D<Rgba> &px, int w, int h,
    float xc, float yc, float rc,
    float rd, float gn, float bl, float lm)
{
    int x1 = int (max ((float) floor (xc - rc),  0.0f));
    int x2 = int (min ((float) ceil  (xc + rc), w - 1.0f));
    int y1 = int (max ((float) floor (yc - rc),  0.0f));
    int y2 = int (min ((float) ceil  (yc + rc), h - 1.0f));

    for (int y = y1; y <= y2; ++y)
    {
	for (int x = x1; x <= x2; ++x)
	{
	    float xl = (x - xc) / rc;
	    float yl = (y - yc) / rc;
	    float r  = sqrt (xl * xl + yl * yl);

	    if (r >= 1)
		continue;

	    float a = 1;

	    if (r * rc > rc - 1)
		a = rc - r * rc;

	    float zl = sqrt (1 - r * r);
	    float dl = xl * 0.42426 - yl * 0.56568 + zl * 0.70710;

	    if (dl < 0)
		dl *= -0.1;

	    float hl = pw (dl, 50) * 4;
	    float dr = (dl + hl) * rd;
	    float dg = (dl + hl) * gn;
	    float db = (dl + hl) * bl;

	    Rgba &p = px[y][x];
	    p.r = p.r * (1 - a) + dr * lm * a;
	    p.g = p.g * (1 - a) + dg * lm * a;
	    p.b = p.b * (1 - a) + db * lm * a;
	    p.a = 1 - (1 - p.a) * (1 - a);
	}
    }
}
void
drawImage1 (Array2D<Rgba> &px, int w, int h)
{
    for (int y = 0; y < h; ++y)
    {
	for (int x = 0; x < w; ++x)
	{
	    Rgba &p = px[y][x];
	    p.r = 0;
	    p.g = 0;
	    p.b = 0;
	    p.a = 0;
	}
    }

    int n = 5600;

    for (int i = 0; i < n; ++i)
    {
	float t = (i * 2.0 * M_PI) / n;
	float xp = sin (t * 2.0) + 0.2 * sin (t * 15.0);
	float yp = cos (t * 3.0) + 0.2 * cos (t * 15.0);
	float r = float (i + 1) / float (n);
	float xq = xp + 0.3 * r * sin (t * 80.0);
	float yq = yp + 0.3 * r * cos (t * 80.0);
	float xr = xp + 0.3 * r * sin (t * 80.0 + M_PI / 2);
	float yr = yp + 0.3 * r * cos (t * 80.0 + M_PI / 2);

	if (i % 10 == 0)
	    sp (px, w, h,
		xp * w / 3 + w / 2, yp * h / 3 + h / 2,
		w * 0.05 * r,
		2.0, 0.8, 0.1,
		0.5 * r * r);

	sp (px, w, h,
	    xq * w / 3 + w / 2, yq * h / 3 + h / 2,
	    w * 0.01 * r,
	    0.7, 0.2, 2.0,
	    0.5 * r * r);

	sp (px, w, h,
	    xr * w / 3 + w / 2, yr * h / 3 + h / 2,
	    w * 0.01 * r,
	    0.2, 1.5, 0.1,
	    0.5 * r * r);
    }
}

void
writeRgba1
(
        const char fileName[],
        Array2D<Rgba> &pixels,
        int width,
        int height
)
{
    drawImage1(pixels, width, height);
    RgbaOutputFile file(fileName, width, height, WRITE_RGBA); // 1
    file.setFrameBuffer(&pixels[0][0], 1, width); // 2
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

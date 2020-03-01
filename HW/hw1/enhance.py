from PIL import Image, ImageDraw, ImageFilter, ImageEnhance
import math
import sys

def main():
    try:
        image=Image.open("IMG_0600.jpg")
    except:
        print("Error in opening image file.")
        sys.exit()
    cropbox=(800, 1100, 1500, 1800)    # selected area
    xsize, ysize = image.size
    if (cropbox[0]>xsize or cropbox[2]>xsize):  # left & right border
        print("Error: box outside x range")
        sys.exit()
    if (cropbox[1]>ysize or cropbox[3]>ysize):  # upper & bottom
        print("Error: box outside y range")
        sys.exit()
    part=image.crop(cropbox)
    image=ImageEnhance.Color(image).enhance(0.0)
    part=ImageEnhance.Sharpness(part).enhance(10.0)
    part=part.filter(ImageFilter.EDGE_ENHANCE)
    image.paste(part, cropbox)
    draw=ImageDraw.Draw(image)
    for l in range (780, 800):
        for up in range (1080, 1100):
            draw.arc((l, up, 1500, 1800), 0, -90, fill='red')
            draw.arc((l, up, 1500, 1800), -90, 0, fill='red')
    for r in range (1480, 1500):
        for low in range (1780, 1800):
            draw.arc((800, 1100, r, low), 0, -90, fill='red')
            draw.arc((800, 1100, r, low), -90, 0, fill='red')       
    draw.line([(1400, 1200), (1700, 900)], fill='red', width=30)
    draw.polygon([(1400, 1200), (1400, 1050), (1550, 1200)],fill='red')
    image.show()
    image.save("IMG_0600_edge.jpg")

main()
from PIL import Image
import libimagequant as liq

def reduce_png_pallete(image_url):
    print("Reduce image pallete")
    file_format = image_url[image_url.rfind(".")+1:]
    supported_formats = ['png', 'bmp']
    if file_format not in supported_formats:
        print("Error: Unsupported image format\nYou shoud use 'png' or 'bmp'")
        return
    img = Image.open(image_url).convert('RGBA')

    width = img.width
    height = img.height
    input_rgba_pixels = img.tobytes()

    # Use libimagequant to make a palette for the RGBA pixels

    attr = liq.Attr()
    attr.max_colors = 16
    input_image = attr.create_rgba(input_rgba_pixels, width, height, 0)

    result = input_image.quantize(attr)

    # Use libimagequant to make new image pixels from the palette

    result.dithering_level = 1.0

    raw_8bit_pixels = result.remap_image(input_image)
    palette = result.get_palette()

    # Save converted pixels as a PNG file
    # This uses the Pillow library for PNG writing (not part of libimagequant)
    img = Image.frombytes('P', (width, height), raw_8bit_pixels)

    palette_data = []
    for color in palette:
        palette_data.append(color.r)
        palette_data.append(color.g)
        palette_data.append(color.b)
    img.putpalette(palette_data)

    output_png_file_path = image_url
    img.save(output_png_file_path)

    print('Written ' + output_png_file_path)


image_url = "zero_face_2_gen.png"
reduce_png_pallete(
    "zero_face_2_gen.png")

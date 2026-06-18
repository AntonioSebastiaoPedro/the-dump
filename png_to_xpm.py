from PIL import Image

def image_to_xpm(image_path, xpm_path, target_size=(1920, 1010)):
    img = Image.open(image_path).convert('RGB')
    img = img.resize(target_size, Image.Resampling.LANCZOS)
    img = img.quantize(colors=256, method=Image.Quantize.MAXCOVERAGE)
    palette = img.getpalette()
    width, height = img.size
    
    colors = []
    color_map = {}
    chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+~`-={}|[]:;<>?,./"
    char_len = len(chars)
    
    num_colors = len(palette) // 3
    for i in range(num_colors):
        r, g, b = palette[i*3:i*3+3]
        hex_color = f"#{r:02x}{g:02x}{b:02x}"
        c = chars[i % char_len]
        if i >= char_len:
            c = chars[i // char_len] + c
        else:
            c = " " + c
        colors.append(f'"{c} c {hex_color}",')
        color_map[i] = c

    with open(xpm_path, 'w') as f:
        f.write("/* XPM */\n")
        f.write("static char * image[] = {\n")
        chars_per_pixel = 2 if num_colors >= char_len else 2
        f.write(f'"{width} {height} {num_colors} {chars_per_pixel}",\n')
        for c in colors:
            f.write(c + "\n")
        
        pixel_data = img.getdata()
        for y in range(height):
            line = '\"'
            for x in range(width):
                idx = pixel_data[y * width + x]
                line += color_map[idx]
            line += '\"'
            if y < height - 1:
                line += ','
            f.write(line + '\n')
        f.write("};\n")

image_to_xpm("/home/ansebast/.gemini/antigravity/brain/991ac5e8-a6e0-4c20-b28a-ea8fa292688b/media__1781824679665.jpg", "assets/theme/game_over.xpm")

import os

color_map = {
    '"  c #505438",': '"  c #385070",',
    '". c #586044",': '". c #445880",',
    '"X c #343C24",': '"X c #243450",',
    '"o c #444C30",': '"o c #304460",',
    '"O c #2C341C",': '"O c #1C2C40",',
    '"+ c #20280C",': '"+ c #0C2030",',
    '"@ c #101010",': '"@ c #101010",',
    '"# c #141C04",': '"# c #041420",',
    '"% c #64684C",': '"% c #4C6090",'
}

for i in range(9):
    in_file = f"assets/door/door{i}.xpm"
    out_file = f"assets/door_blue/door{i}.xpm"
    with open(in_file, "r") as f:
        content = f.read()
    
    for old, new in color_map.items():
        content = content.replace(old, new)
        
    with open(out_file, "w") as f:
        f.write(content)
print("Blue door generated.")

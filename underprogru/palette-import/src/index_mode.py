image_url = "path_to_image"
process = subprocess.Popen(["aseprite", "-b", image_url, "--dithering-algorithm",
                            "ordered", "--color-mode", "indexed", "--save-as", image_url])
process.wait()

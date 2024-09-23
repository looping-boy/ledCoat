from PIL import Image, ImageSequence
import numpy as np
import pyperclip

def convert_frame_to_progmem(frame):
    progmem_frame = []
    for row in frame:
        for pixel in row:
            # Check if pixel is fully transparent
            if pixel[3] == 0:
                hex_value = "0x000000"  # Fully transparent
            else:
                # Convert RGB pixel to hex format (0xRRGGBB)
                hex_value = f"0x{pixel[0]:02X}{pixel[1]:02X}{pixel[2]:02X}"
            progmem_frame.append(hex_value)
    return progmem_frame

def convert_gif_to_progmem(gif_file):
    with Image.open(gif_file) as im:
        frames = []
        for frame in ImageSequence.Iterator(im):
            # Convert frame to numpy array
            frame_array = np.array(frame.convert('RGBA'))
            # Convert frame to PROGMEM format
            progmem_frame = convert_frame_to_progmem(frame_array)
            frames.append(progmem_frame)
    return frames

# Load the GIF and convert it to PROGMEM format
frames = convert_gif_to_progmem('checkBlue.gif')

# Generate PROGMEM format string
frameNumber = len(frames)
progmem_str = "const uint32_t checkBlue[" + str(frameNumber) + "][2664]PROGMEM = {\n"
for frame in frames:
    progmem_str += "    {" + ", ".join(frame) + "},\n"
progmem_str += "};"

# Copy the PROGMEM format string to the clipboard
pyperclip.copy(progmem_str)

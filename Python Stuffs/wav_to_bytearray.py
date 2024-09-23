import wave
import struct
import sys
import pyperclip

def wav_to_bytearray(input_wav_file):
    try:
        # Open the WAV file
        with wave.open(input_wav_file, 'rb') as wav_file:
            # Check if the file is in the correct format
            if wav_file.getnchannels() != 1:
                raise ValueError("Only mono WAV files are supported")
            
            # Extract parameters
            sample_width = wav_file.getsampwidth()
            num_frames = wav_file.getnframes()
            frame_rate = wav_file.getframerate()

            print(f"Sample width: {sample_width} bytes")
            print(f"Number of frames: {num_frames}")
            print(f"Frame rate: {frame_rate} frames/second")

            # Read the frames
            raw_data = wav_file.readframes(num_frames)

            # Convert frames to amplitude values
            fmt = {1: 'B', 2: 'h', 4: 'i'}[sample_width]
            amplitude_data = struct.unpack(f"<{num_frames}{fmt}", raw_data)

            # Convert amplitude values to a bytearray
            amplitude_bytearray = bytearray()
            for sample in amplitude_data:
                if sample_width == 1:
                    # For 8-bit audio, values are unsigned (0-255)
                    amplitude_bytearray.append(sample)
                else:
                    # For 16-bit and 32-bit audio, normalize to 8-bit (0-255)
                    normalized_sample = int((sample + (1 << (8 * sample_width)) / 2) // (1 << (8 * sample_width - 8)))
                    amplitude_bytearray.append(normalized_sample)

            return amplitude_bytearray

    except Exception as e:
        print(f"An error occurred: {e}")
        return None

def format_bytearray_to_c_array(bytearray_data):
    hex_values = ', '.join(f'0x{byte:02x}' for byte in bytearray_data)
    c_array_str = f"const unsigned char test[] = {{\n{hex_values}\n}};"
    return c_array_str

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python wav_to_bytearray.py <input_wav_file>")
    else:
        input_wav_file = sys.argv[1]
        bytearray_result = wav_to_bytearray(input_wav_file)
        if bytearray_result:
            c_array_result = format_bytearray_to_c_array(bytearray_result)
            pyperclip.copy(c_array_result)
            print("C-style array successfully created and copied to clipboard!")
            print(c_array_result[:100] + "...")  # Print the first 100 characters for demonstration

import os

# Define the lines to append
lines_to_append = [
    "map_Kd face_diffuse.jpeg",
    "map_Bump face_normal.png",
    "map_Ks face_specular.png"
]

# Specify the folder where the files are located
folder_path = "C:\\Users\\home\\Documents\\OpenGL\\resources\\objects\\frame_obj\\"

# Iterate through all files in the folder
for filename in os.listdir(folder_path):
    if os.path.isfile(os.path.join(folder_path, filename)):
        # Check if the file is a text file (you may need to adjust this check)
        if filename.endswith(".mtl"):
            file_path = os.path.join(folder_path, filename)

            # Open the file in append mode and add the lines
            with open(file_path, "a") as file:
                file.write("\n".join(lines_to_append) + "\n")
            print(f"Appended lines to {filename}")

print("Script completed.")


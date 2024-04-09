import os

def rename_files_in_directory(directory_path):
    """
    This function goes through the given directory (and its subdirectories) to find all .hpp files and rename them to .cpp files.
    
    :param directory_path: Path to the directory where the search should begin.
    """
    for dirpath, dirnames, filenames in os.walk(directory_path):
        for filename in filenames:
            if filename.endswith('.hpp'):
                original_file_path = os.path.join(dirpath, filename)
                new_file_path = os.path.join(dirpath, filename[:-4] + '.cpp')
                os.rename(original_file_path, new_file_path)
                print(f'Renamed "{original_file_path}" to "{new_file_path}"')

# Specify the starting directory path
starting_directory = r'C:\Users\tjerf\source\repos\AETK_New\AETK\src'

# Call the function with the path to the directory where you want to start renaming files
rename_files_in_directory(starting_directory)

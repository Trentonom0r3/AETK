import re

def extract_bindings(file_path):
    """
    Extracts all binding function names from an .hpp file.

    :param file_path: The path to the .hpp file.
    :return: A list of function names following the pattern 'void bind_<name>(py::module &m)'.
    """
    with open(file_path, 'r') as file:
        content = file.read()

    # Regular expression to find all function declarations
    function_pattern = re.compile(r'void (bind_[a-zA-Z_]+)\(py::module &m\)')

    # Find and return all matching function names
    return function_pattern.findall(content)

def generate_cpp_file(bindings, output_file_path):
    """
    Generates a .cpp file that calls all given binding functions.

    :param bindings: A list of function names to call.
    :param output_file_path: The path to save the generated .cpp file.
    """
    with open(output_file_path, 'w') as file:
        # Write includes and main function header
        file.write("#include \"bindings.hpp\"\n\n")
        file.write("void bind_all(py::module &m) {\n")

        # Write each function call
        for func in bindings:
            file.write(f"    {func}(m);\n")

        # Close the main function
        file.write("}\n")

# Example usage
bindings_file = r"C:\Users\tjerf\source\repos\AETK\AETK\AEGP\Core\PyFx.hpp"
output_file = "./bindings.cpp"

bindings = extract_bindings(bindings_file)
generate_cpp_file(bindings, output_file)

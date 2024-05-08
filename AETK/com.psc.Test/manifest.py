import PyShiftAE as ae   

def main():
    manifest = Manifest()
    manifest.name = "Test"
    manifest.version = "www"
    manifest.description = ""
    manifest.author = "why"
    manifest.dependencies = ['PyShiftAE']
    manifest.entry = os.path.dirname(os.path.realpath(__file__)) + "/entry.py"
    return manifest

manifest = main()
dependencies = manifest.dependencies  # Expose dependencies at module level

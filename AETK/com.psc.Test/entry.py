import PyShiftAE as ae
    
def display_alert(message: str) -> None:
    app = ae.App() # Get the current After Effects application
    app.reportInfo(message) # Send a message to the user

def search_project_folder_by_name(name: str) -> Item:
    app = ae.App()  # Get the current After Effects application
    project = app.project  # Get the current After Effects project
    for item in project.items:  # Loop through the items in the current After Effects project
        if item.name == name:  # If the item's name matches the name we're looking for
            return item  # Return the item
        if isinstance(item, FolderItem):  # If the item is a folder
            for child in item.children:  # Loop through the children of the folder
                if child.name == name:  # If the child's name matches the name we're looking for
                    return child  # Return the child
    return None   

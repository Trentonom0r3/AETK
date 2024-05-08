/*****************************************************************/ /**
                                                                     * \file
                                                                     *Project.hpp
                                                                     * \brief  A
                                                                     *class
                                                                     *representing
                                                                     *an After
                                                                     *Effects
                                                                     *Project
                                                                     *
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <AETK/AEGP/Core/Core.hpp>


class ItemCollection;
/**
 * @brief A class representing an After Effects Project
 *
 * This class represents an After Effects project and provides methods to
 * interact with it.
 */
class Project
{
  public:
    /**
     * @brief Default constructor
     *
     * Initializes a new Project object by calling the init() function.
     */
    Project() : m_proj(init()) {}
    Project(ProjectPtr proj) : m_proj(proj) {}
    /**
     * @brief Destructor
     *
     * Default destructor for the Project class.
     */
    ~Project() = default;

    /**
     * @brief Open an After Effects Project
     *
     * Opens an After Effects project from the specified path.
     *
     * @param path The path to the project file.
     * @return Project The opened project.
     */
    static Project open(const std::string &path);

    /**
     * @brief Create a new After Effects Project
     *
     * Creates a new After Effects project and saves it to the specified path.
     * If no path is provided, the project will be saved to the default
     * location.
     *
     * @param path The path to save the project to.
     * @return Project The newly created project.
     */
    static Project newProject(const std::string &path = "");

    /**
     * @brief Get the Items in the project
     *
     * \return std::shared_ptr<ItemCollection> The items in the project.
     */
    tk::shared_ptr<ItemCollection> items();
    /**
     * @brief Get the name of the project
     *
     * Retrieves the name of the current project.
     *
     * @return std::string The name of the project.
     */
    std::string name();

    /**
     * @brief Get the path of the project
     *
     * Retrieves the path of the current project.
     *
     * @return std::string The path of the project.
     */
    std::string path();

    /**
     * @brief Get the bit depth of the project
     *
     * Retrieves the bit depth of the current project.
     *
     * @return AE_ProjBitDepth The bit depth of the project.
     */
    ProjBitDepth bitDepth();

    /**
     * @brief Set the bit depth of the project
     *
     * Sets the bit depth of the current project.
     *
     * @param depth The bit depth to set.
     */
    void setBitDepth(ProjBitDepth depth);

    /**
     * @brief Save the project
     *
     * Saves the current project.
     */
    void save();

    /**
     * @brief Save the project to a new path
     *
     * Saves the current project to the specified path.
     *
     * @param path The path to save the project to.
     */
    void saveAs(const std::string &path);

    /**
     * @brief Check if the project is dirty
     *
     * Checks if the current project has unsaved changes.
     *
     * @return bool True if the project is dirty, false otherwise.
     */
    bool isDirty();

  private:
    ProjectPtr m_proj; // Pointer to the After Effects project

    /**
     * @brief Initialize the project
     *
     * Initializes the project by retrieving the active project from the suite.
     * If no project is active, an exception is thrown.
     *
     * @return ProjectPtr The initialized project pointer.
     * @throws AEException If no project is currently active.
     */
    inline ProjectPtr init();
    tk::shared_ptr<ItemCollection> m_itemCollection;
};

#endif // PROJECT_HPP
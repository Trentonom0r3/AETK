/*****************************************************************/ /**
                                                                     * \file
                                                                     *Import.hpp
                                                                     * \brief An
                                                                     *Asset
                                                                     *Importer
                                                                     *for After
                                                                     *Effects
                                                                     * Abstracts
                                                                     *importing
                                                                     *of assets
                                                                     *(and
                                                                     *various
                                                                     *configurations)
                                                                     *into After
                                                                     *Effects
                                                                     *
                                                                     * \author
                                                                     *tjerf
                                                                     * \date
                                                                     *March 2024
                                                                     *********************************************************************/

#pragma once

#ifndef IMPORT_HPP
#define IMPORT_HPP

#include "AETK/AEGP/Core/Base/AEGeneral.hpp"

/**
 * \class ImportOptions
 * \brief Represents the options for importing assets into After Effects.
 *
 * The ImportOptions class provides a set of configuration options for importing
 * assets into After Effects. It supports importing assets as still images,
 * image sequences, compositions, or individual layers.
 */
class ImportOptions
{
  public:
    /**
     * \brief Default constructor for ImportOptions.
     */
    ImportOptions();

    /**
     * \brief Destructor for ImportOptions.
     */
    ~ImportOptions();

    /**
     * \struct Config
     * \brief Represents the configuration options for importing assets.
     *
     * The Config struct defines additional configuration parameters for
     * importing assets. It includes options such as frame rate, width, height,
     * name, and duration.
     */
    struct Config
    {
        std::optional<double>
            frameRate;             ///< The frame rate of the imported assets.
        std::optional<int> width;  ///< The width of the imported assets.
        std::optional<int> height; ///< The height of the imported assets.
        std::optional<std::string> name; ///< The name of the imported assets.
        std::optional<double>
            duration; ///< The duration of the imported assets.
    };

    /**
     * \brief Imports assets into After Effects with the specified configuration
     * options.
     *
     * The importAssets function imports assets into After Effects based on the
     * provided files and configuration options. It supports importing assets as
     * still images, image sequences, compositions, or individual layers.
     *
     * \param files The files to import. It can be a single file or a vector of
     * files. \param config The configuration options for importing the assets.
     * Defaults to an empty configuration. \return bool True if the assets were
     * imported successfully, false otherwise.
     */
    bool importAssets(
        const std::variant<std::string, std::vector<std::string>> &files,
        const Config &config = {});

  private:
    /**
     * \brief Imports assets as individual files.
     *
     * The importAsFiles function imports assets as individual files into After
     * Effects.
     *
     * \param files The files to import.
     * \param config The configuration options for importing the assets.
     * \return bool True if the assets were imported successfully, false
     * otherwise.
     */
    bool importAsFiles(const std::vector<std::string> &files,
                       const Config &config);

    /**
     * \brief Imports assets as image sequences.
     *
     * The importAsFrames function imports assets as image sequences into After
     * Effects.
     *
     * \param files The files to import.
     * \param config The configuration options for importing the assets.
     * \return bool True if the assets were imported successfully, false
     * otherwise.
     */
    bool importAsFrames(const std::vector<std::string> &files,
                        const Config &config);

    /**
     * \brief Imports assets as compositions.
     *
     * The importAsComp function imports assets as compositions into After
     * Effects.
     *
     * \param files The files to import.
     * \param config The configuration options for importing the assets.
     * \return bool True if the assets were imported successfully, false
     * otherwise.
     */
    bool importAsComp(const std::vector<std::string> &files,
                      const Config &config);

    /**
     * \brief Imports assets as individual layers.
     *
     * The importAsLayers function imports assets as individual layers into
     * After Effects.
     *
     * \param files The files to import.
     * \param config The configuration options for importing the assets.
     * \return bool True if the assets were imported successfully, false
     * otherwise.
     */
    bool importAsLayers(const std::vector<std::string> &files,
                        const Config &config);

    /**
     * \brief Stores the last error message encountered during import.
     */
    std::string lastError;

    /**
     * \brief Expands the files to import.
     *
     * The expandFiles function expands the files to import based on the
     * provided variant.
     *
     * \param files The files to expand.
     * \return std::vector<std::string> The expanded files.
     */
    static std::vector<std::string> expandFiles(
        const std::variant<std::string, std::vector<std::string>> &files);

    /**
     * \brief Verifies the validity of the files to import.
     *
     * The verifyFiles function verifies the validity of the files to import.
     *
     * \param files The files to verify.
     * \return bool True if the files are valid, false otherwise.
     */
    static bool verifyFiles(const std::vector<std::string> &files);
};

/**
 * \brief Example usage of the ImportOptions class.
 *
 * The ImportOptions class can be used to import assets into After Effects with
 * specific configuration options.
 *
 * \code{.cpp}
 * ImportOptions import;
 * ImportOptions::Config config;
 *
 * // Define configuration
 * config.frameRate = 24;
 * config.width = 1920;
 * config.height = 1080;
 * config.duration = 10;
 * config.name = "MyImportedComp";
 *
 * // Import as composition
 * import.importAssets("path/to/file.mov", config);
 * \endcode
 */
#endif // IMPORT_HPP
/*****************************************************************/ /**
                                                                     * \file   Import.hpp
                                                                     * \brief  AssetManager header file
                                                                     *
                                                                     * \author tjerf
                                                                     * \date   April 2024
                                                                     *********************************************************************/
#ifndef IMPORT_HPP
#define IMPORT_HPP

#include "AETK/AEGP/Core/Core.hpp"

/**
 * @class AssetManager
 * @brief Manages assets within an After Effects project.
 *
 * Provides methods to import assets, organize them based on various criteria,
 * replace existing assets with new ones, and find assets based on custom predicates.
 */
class AssetManager
{
  public:
    AssetManager(){};

    /**
     * @brief Imports an asset into the project.
     *
     * \param filePath
     * \param name
     * \return ItemPtr to the imported asset.
     */
    inline ItemPtr import(const std::string &filePath, const std::string &name)
    {
        FootageSuite suite;
        ItemPtr item;
        FootagePtr footage;
        /*
        A Few Conditions here:
        1. We need to first see if the filePath has an extension. if not, its a
      folder, and thus a sequence.
      2. If it does have an extension, we pas NULL for sequence options.
        */
        if (filePath.find(".") != std::string::npos)
        {
            // This is a single file
            footage =
                suite.newFootage(filePath, AssetManager::layerkey(name), NULL, InterpretationStyle::NO_DIALOG_NO_GUESS);
        }
        else
        {
            // This is a sequence
            footage = suite.newFootage(filePath, AssetManager::layerkey(name), &FileSequenceImportOptions(AssetManager::sequence()),
                                       InterpretationStyle::NO_DIALOG_NO_GUESS);
        }
        if (footage.get())
        {
            item =
                suite.addFootageToProject(footage, ProjSuite().GetProjectRootFolder(ProjSuite().GetProjectByIndex(0)));
        }
        return item;
    }

    void AssetManager::replaceAsset(const ItemPtr &oldAsset, const std::string &newFilePath)
    {
        FootageSuite suite;
        ItemPtr newFootage = AssetManager::import(newFilePath, "");
        if (newFootage.get())
        {
            suite.replaceItemMainFootage(suite.getMainFootageFromItem(oldAsset), newFootage);
        }
        else
        {
            throw AEException("Failed to import new footage");
        }
    }

    // Finds assets based on a predicate function
    // Will require ItemCollection to be implemented
    //std::vector<ItemPtr> findAssets(const std::function<bool(const ItemPtr &)> &predicate);

  protected:
    static inline AEGP_FootageLayerKey layerkey(const std::string &name)
    {
        AEGP_FootageLayerKey layer_key;
        layer_key.layer_idL = AEGP_LayerID_UNKNOWN;
        layer_key.layer_indexL = AEGP_LayerIndex_MERGED;
        layer_key.layer_draw_style = AEGP_LayerDrawStyle_DOCUMENT_BOUNDS;

        strncpy_s(layer_key.nameAC, name.c_str(), AEGP_FOOTAGE_LAYER_NAME_LEN);
        layer_key.nameAC[AEGP_FOOTAGE_LAYER_NAME_LEN] = '\0'; // Ensure null-termination

        return layer_key;
    }

    static inline AEGP_FileSequenceImportOptions sequence()
    {
        AEGP_FileSequenceImportOptions options;
        options.all_in_folderB = TRUE;
        options.force_alphabeticalB = TRUE;
        options.start_frameL = AEGP_ANY_FRAME;
        options.end_frameL = AEGP_ANY_FRAME;
        return options;
    }
};

#endif // IMPORT_HPP

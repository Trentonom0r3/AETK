#include "AEGeneral.hpp"

/**
 * @function GetNumProjects
 * @brief` Get the number of projects in the current AE session
 *
 * \return
 */
int ProjSuite6::GetNumProjects()
{
    A_Err err = A_Err_NONE;
    int numProjects = 0;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_GetNumProjects(
        &numProjects));
    return numProjects;
}

ProjectPtr ProjSuite6::GetProjectByIndex(A_long projIndex)
{
    AEGP_ProjectH projectH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_GetProjectByIndex(
            projIndex, &projectH));

    return std::make_shared<AEGP_ProjectH>(projectH);
}

std::string ProjSuite6::GetProjectName(ProjectPtr project)
{
    A_Err err = A_Err_NONE;
    A_char name[256];
    AE_CHECK(m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_GetProjectName(
        *project.get(), name));
    return std::string(name);
}

std::string ProjSuite6::GetProjectPath(ProjectPtr project)
{
    A_Err err = A_Err_NONE;
    AEGP_MemHandle pathH;
    if (project.get() == NULL)
    {
        throw AEException("Project is Null");
    }

    AE_CHECK(m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_GetProjectPath(
        *project.get(), &pathH));
    return memHandleToString(pathH);
}

ItemPtr ProjSuite6::GetProjectRootFolder(ProjectPtr project)
{
    AEGP_ItemH rootFolderH;
    CheckNotNull(project.get(),
                 "Error Getting Project Root Folder. Project is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .ProjSuite6()
                 ->AEGP_GetProjectRootFolder(*project.get(), &rootFolderH));
    return std::make_shared<AEGP_ItemH>(rootFolderH);
}

void ProjSuite6::SaveProjectToPath(ProjectPtr project, const std::string &path)
{
    CheckNotNull(project.get(), "Error Saving Project. Project is Null");
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_SaveProjectToPath(
            *project.get(), path16.data()));
}

TimeDisplay3 ProjSuite6::GetProjectTimeDisplay(ProjectPtr project)
{
    AEGP_TimeDisplay3 timeDisplay;
    CheckNotNull(project.get(),
                 "Error Getting Project Time Display. Project is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .ProjSuite6()
                 ->AEGP_GetProjectTimeDisplay(*project.get(), &timeDisplay));
    return TimeDisplay3(timeDisplay);
}

void ProjSuite6::SetProjectTimeDisplay(ProjectPtr project,
                                       TimeDisplay3 timeDisplay)
{
    CheckNotNull(project.get(),
                 "Error Setting Project Time Display. Project is Null");
    const AEGP_TimeDisplay3 timeDisplay3 = timeDisplay.get();
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .ProjSuite6()
                 ->AEGP_SetProjectTimeDisplay(*project.get(), &timeDisplay3));
}

bool ProjSuite6::ProjectIsDirty(ProjectPtr project)
{
    CheckNotNull(project.get(),
                 "Error Checking if Project is Dirty. Project is Null");
    A_Boolean isDirty;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_ProjectIsDirty(
        *project.get(), &isDirty));
    return isDirty;
}

void ProjSuite6::SaveProjectAs(ProjectPtr project, const std::string &path)
{
    CheckNotNull(project.get(), "Error Saving Project As. Project is Null");
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
    AE_CHECK(m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_SaveProjectAs(
        *project.get(), path16.data()));
}

ProjectPtr ProjSuite6::NewProject()
{
    AEGP_ProjectH projectH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_NewProject(
        &projectH));
    return std::make_shared<AEGP_ProjectH>(projectH);
}

ProjectPtr ProjSuite6::OpenProjectFromPath(const std::string &path)
{
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
    AEGP_ProjectH projectH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_OpenProjectFromPath(
            path16.data(), &projectH));
    return std::make_shared<AEGP_ProjectH>(projectH);
}

AE_ProjBitDepth ProjSuite6::GetProjectBitDepth(ProjectPtr project)
{
    AEGP_ProjBitDepth bitDepth;
    CheckNotNull(project.get(),
                 "Error Getting Project Bit Depth. Project is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_GetProjectBitDepth(
            *project.get(), &bitDepth));
    return AE_ProjBitDepth(bitDepth);
}

void ProjSuite6::SetProjectBitDepth(ProjectPtr project,
                                    AE_ProjBitDepth bitDepth)
{
    CheckNotNull(project.get(),
                 "Error Setting Project Bit Depth. Project is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ProjSuite6()->AEGP_SetProjectBitDepth(
            *project.get(), AEGP_ProjBitDepth(bitDepth)));
}

ItemPtr ItemSuite9::GetFirstProjItem(ProjectPtr project)
{
    CheckNotNull(project.get(),
                 "Error Getting First Project Item. Project is Null");
    AEGP_ItemH itemH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetFirstProjItem(
            *project.get(), &itemH));
    return std::make_shared<AEGP_ItemH>(itemH);
}

ItemPtr ItemSuite9::GetNextProjItem(ProjectPtr project, ItemPtr item)
{
    AEGP_ItemH nextItemH;
    CheckNotNull(project.get(),
                 "Error Getting Next Project Item. Project is Null");
    CheckNotNull(project.get(),
                 "Error Getting Next Project Item. Current Item is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetNextProjItem(
            *project.get(), *item.get(), &nextItemH));
    return std::make_shared<AEGP_ItemH>(nextItemH);
}

ItemPtr ItemSuite9::GetActiveItem()
{
    AEGP_ItemH itemH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetActiveItem(
        &itemH));
    if (itemH == NULL)
    {
        return nullptr;
    }
    return std::make_shared<AEGP_ItemH>(itemH);
}

bool ItemSuite9::IsItemSelected(ItemPtr item)
{
    A_Boolean isSelected;
    CheckNotNull(item.get(),
                 "Error Checking if Item is Selected. Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_IsItemSelected(
        *item.get(), &isSelected));
    return isSelected;
}

void ItemSuite9::SelectItem(ItemPtr item, bool select, bool deselectOthers)
{
    CheckNotNull(item.get(), "Error Selecting Item. Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_SelectItem(
        *item.get(), select, deselectOthers));
}

AE_ItemType ItemSuite9::GetItemType(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item Type. Item is Null");
    AEGP_ItemType itemType;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemType(
        *item.get(), &itemType));
    return AE_ItemType(itemType);
}

std::string ItemSuite9::GetTypeName(AE_ItemType itemType)
{
    A_char name[256];
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetTypeName(
        AEGP_ItemType(itemType), name));
    return std::string(name);
}

std::string ItemSuite9::GetItemName(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item Name. Item is Null");
    AEGP_MemHandle nameH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemName(
        *m_suiteManager.GetPluginID(), *item.get(), &nameH));
    return memHandleToString(nameH);
}

void ItemSuite9::SetItemName(ItemPtr item, const std::string &name)
{
    CheckNotNull(item.get(), "Error Setting Item Name. Item is Null");
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_SetItemName(
        *item.get(), name16.data()));
}

A_long ItemSuite9::GetItemID(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item ID. Item is Null");
    A_long id;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemID(
        *item.get(), &id));
    return id;
}

AE_ItemFlag ItemSuite9::GetItemFlags(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item Flags. Item is Null");
    A_long flags;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemFlags(
        *item.get(), &flags));
    return AE_ItemFlag(flags);
}

void ItemSuite9::SetItemUseProxy(ItemPtr item, bool useProxy)
{
    CheckNotNull(item.get(), "Error Setting Item Use Proxy. Item is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_SetItemUseProxy(
            *item.get(), useProxy));
}

ItemPtr ItemSuite9::GetItemParentFolder(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item Parent Folder. Item is Null");
    AEGP_ItemH parentFolderH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemParentFolder(
            *item.get(), &parentFolderH));
    return std::make_shared<AEGP_ItemH>(parentFolderH);
}

void ItemSuite9::SetItemParentFolder(ItemPtr item, ItemPtr parentFolder)
{
    CheckNotNull(item.get(), "Error Setting Item Parent Folder. Item is Null");
    CheckNotNull(parentFolder.get(),
                 "Error Setting Item Parent Folder. Parent Folder is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_SetItemParentFolder(
            *item.get(), *parentFolder.get()));
}

A_Time ItemSuite9::GetItemDuration(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item Duration. Item is Null");
    A_Time duration;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemDuration(
            *item.get(), &duration));
    return duration;
}

A_Time ItemSuite9::GetItemCurrentTime(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item Current Time. Item is Null");
    A_Time currentTime;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemCurrentTime(
            *item.get(), &currentTime));
    return currentTime;
}

std::tuple<A_long, A_long> ItemSuite9::GetItemDimensions(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item Dimensions. Item is Null");
    A_long width;
    A_long height;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemDimensions(
            *item.get(), &width, &height));
    return std::make_tuple(width, height);
}

A_Ratio ItemSuite9::GetItemPixelAspectRatio(ItemPtr item)
{
    CheckNotNull(item.get(),
                 "Error Getting Item Pixel Aspect Ratio. Item is Null");
    A_Ratio pixelAspectRatio;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .ItemSuite9()
            ->AEGP_GetItemPixelAspectRatio(*item.get(), &pixelAspectRatio));
    return pixelAspectRatio;
}

void ItemSuite9::DeleteItem(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Deleting Item. Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_DeleteItem(
        *item.get()));
}

ItemPtr ItemSuite9::CreateNewFolder(const std::string &name,
                                    ItemPtr parentFolder)
{
    CheckNotNull(parentFolder.get(),
                 "Error Creating New Folder. Parent Folder is Null");
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AEGP_ItemH folderH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_CreateNewFolder(
            name16.data(), *parentFolder.get(), &folderH));
    return std::make_shared<AEGP_ItemH>(folderH);
}

void ItemSuite9::SetItemCurrentTime(ItemPtr item, A_Time newTime)
{
    CheckNotNull(item.get(), "Error Setting Item Current Time. Item is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_SetItemCurrentTime(
            *item.get(), &newTime));
}

std::string ItemSuite9::GetItemComment(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item Comment. Item is Null");
    AEGP_MemHandle commentH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemComment(
        *item.get(), &commentH));
    return memHandleToString(commentH);
}

void ItemSuite9::SetItemComment(ItemPtr item, const std::string &comment)
{
    CheckNotNull(item.get(), "Error Setting Item Comment. Item is Null");
    std::vector<A_UTF16Char> comment16 = ConvertUTF8ToUTF16(comment);
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_SetItemComment(
        *item.get(), comment16.data()));
}

AE_Label ItemSuite9::GetItemLabel(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item Label. Item is Null");
    AEGP_LabelID label;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemLabel(
        *item.get(), &label));
    return AE_Label(label);
}

void ItemSuite9::SetItemLabel(ItemPtr item, AE_Label label)
{
    CheckNotNull(item.get(), "Error Setting Item Label. Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_SetItemLabel(
        *item.get(), AEGP_LabelID(label)));
}

ItemViewPtr ItemSuite9::GetItemMRUView(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Item MRU View. Item is Null");
    AEGP_ItemViewP itemViewH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().ItemSuite9()->AEGP_GetItemMRUView(
        *item.get(), &itemViewH));
    return std::make_shared<AEGP_ItemViewP>(itemViewH);
}

A_Time ItemViewSuite1::GetItemViewPlaybackTime(ItemViewPtr itemView,
                                               bool &isCurrentlyPreviewing)
{
    CheckNotNull(itemView.get(),
                 "Error Getting Item View Playback Time. Item View is Null");
    A_Time time;
    A_Boolean isPreviewing = static_cast<A_Boolean>(isCurrentlyPreviewing);
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .ItemViewSuite1()
                 ->AEGP_GetItemViewPlaybackTime(*itemView.get(), &isPreviewing,
                                                &time));
    isCurrentlyPreviewing = isPreviewing;
    return time;
}

SoundDataPtr SoundDataSuite1::NewSoundData(const SoundDataFormat &soundFormat)
{
    AEGP_SoundDataH soundDataH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().SoundDataSuite1()->AEGP_NewSoundData(
            &soundFormat.get(), &soundDataH));
    return toSoundDataPtr(soundDataH);
}

SoundDataFormat SoundDataSuite1::GetSoundDataFormat(SoundDataPtr soundData)
{
    CheckNotNull(soundData.get(),
                 "Error Getting Sound Data Format. Sound Data is Null");
    AEGP_SoundDataFormat format;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .SoundDataSuite1()
                 ->AEGP_GetSoundDataFormat(*soundData.get(), &format));
    return SoundDataFormat(format);
}

void SoundDataSuite1::LockSoundDataSamples(SoundDataPtr soundData,
                                           void **samples)
{
    CheckNotNull(soundData.get(),
                 "Error Locking Sound Data Samples. Sound Data is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .SoundDataSuite1()
                 ->AEGP_LockSoundDataSamples(*soundData.get(), samples));
}

void SoundDataSuite1::UnlockSoundDataSamples(SoundDataPtr soundData)
{
    CheckNotNull(soundData.get(),
                 "Error Unlocking Sound Data Samples. Sound Data is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .SoundDataSuite1()
                 ->AEGP_UnlockSoundDataSamples(*soundData.get()));
}

int SoundDataSuite1::GetNumSamples(SoundDataPtr soundData)
{
    CheckNotNull(soundData.get(),
                 "Error Getting Number of Samples. Sound Data is Null");
    A_long numSamples;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().SoundDataSuite1()->AEGP_GetNumSamples(
            *soundData.get(), &numSamples));
    return numSamples;
}

CompPtr CompSuite11::GetCompFromItem(ItemPtr item)
{
    CheckNotNull(item.get(), "Error Getting Comp From Item. Item is Null");
    AEGP_CompH compH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_GetCompFromItem(
            *item.get(), &compH));
    return std::make_shared<AEGP_CompH>(compH);
}

ItemPtr CompSuite11::GetItemFromComp(CompPtr comp)
{
    AEGP_ItemH itemH;
    CheckNotNull(comp.get(), "Error Getting Item From Comp. Comp is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_GetItemFromComp(
            *comp.get(), &itemH));
    return std::make_shared<AEGP_ItemH>(itemH);
}

std::tuple<short, short> CompSuite11::GetCompDownsampleFactor(CompPtr comp)
{
    AEGP_DownsampleFactor factor;
    CheckNotNull(comp.get(),
                 "Error Getting Comp Downsample Factor. Comp is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_GetCompDownsampleFactor(*comp.get(), &factor));
    return toDownsampleFactor(factor);
}

void CompSuite11::SetCompDownsampleFactor(
    CompPtr comp, const std::tuple<short, short> &factor)
{
    CheckNotNull(comp.get(),
                 "Error Setting Comp Downsample Factor. Comp is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_SetCompDownsampleFactor(
                     *comp.get(), &toAEGP_DownsampleFactor(factor)));
}

ColorVal CompSuite11::GetCompBGColor(CompPtr comp)
{
    CheckNotNull(comp.get(),
                 "Error Getting Comp Background Color. Comp is Null");
    AEGP_ColorVal color;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_GetCompBGColor(
            *comp.get(), &color));
    return toColorVal(color);
}

void CompSuite11::SetCompBGColor(CompPtr comp, const ColorVal &color)
{
    CheckNotNull(comp.get(),
                 "Error Setting Comp Background Color. Comp is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_SetCompBGColor(
            *comp.get(), &toAEGP_ColorVal(color)));
}

AE_CompFlag CompSuite11::GetCompFlags(CompPtr comp)
{
    CheckNotNull(comp.get(), "Error Getting Comp Flags. Comp is Null");
    A_long flags;
    AE_CHECK(m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_GetCompFlags(
        *comp.get(), &flags));
    return AE_CompFlag(flags);
}

bool CompSuite11::GetShowLayerNameOrSourceName(CompPtr comp)
{
    CheckNotNull(comp.get(),
                 "Error Getting Show Layer Name or Source Name. Comp is Null");
    A_Boolean showLayerName;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .CompSuite11()
            ->AEGP_GetShowLayerNameOrSourceName(*comp.get(), &showLayerName));
    return showLayerName;
}

void CompSuite11::SetShowLayerNameOrSourceName(CompPtr comp, bool showLayerName)
{
    CheckNotNull(comp.get(),
                 "Error Setting Show Layer Name or Source Name. Comp is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .CompSuite11()
            ->AEGP_SetShowLayerNameOrSourceName(*comp.get(), showLayerName));
}

bool CompSuite11::GetShowBlendModes(CompPtr comp)
{
    CheckNotNull(comp.get(), "Error Getting Show Blend Modes. Comp is Null");
    A_Boolean showBlendModes;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_GetShowBlendModes(
            *comp.get(), &showBlendModes));
    return showBlendModes;
}

void CompSuite11::SetShowBlendModes(CompPtr comp, bool showBlendModes)
{
    CheckNotNull(comp.get(), "Error Setting Show Blend Modes. Comp is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_SetShowBlendModes(
            *comp.get(), showBlendModes));
}

double CompSuite11::GetCompFramerate(CompPtr comp)
{
    CheckNotNull(comp.get(), "Error Getting Comp Frame Rate. Comp is Null");
    double fps;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_GetCompFramerate(
            *comp.get(), &fps));
    return fps;
}

void CompSuite11::SetCompFrameRate(CompPtr comp, double fps)
{
    CheckNotNull(comp.get(), "Error Setting Comp Frame Rate. Comp is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_SetCompFrameRate(
            *comp.get(), &fps));
}

std::tuple<A_Ratio, A_Ratio> CompSuite11::GetCompShutterAnglePhase(CompPtr comp)
{
    CheckNotNull(comp.get(),
                 "Error Getting Comp Shutter Angle Phase. Comp is Null");
    A_Ratio angle;
    A_Ratio phase;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_GetCompShutterAnglePhase(*comp.get(), &angle, &phase));
    return std::make_tuple(angle, phase);
}

std::tuple<A_Time, A_Time>
CompSuite11::GetCompShutterFrameRange(CompPtr comp, A_Time compTime)
{
    CheckNotNull(comp.get(),
                 "Error Getting Comp Shutter Frame Range. Comp is Null");
    return std::tuple<A_Time, A_Time>();
}

int CompSuite11::GetCompSuggestedMotionBlurSamples(CompPtr comp)
{
    CheckNotNull(
        comp.get(),
        "Error Getting Comp Suggested Motion Blur Samples. Comp is Null");
    int samples;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .CompSuite11()
            ->AEGP_GetCompSuggestedMotionBlurSamples(*comp.get(), &samples));
    return samples;
}

void CompSuite11::SetCompSuggestedMotionBlurSamples(CompPtr comp, int samples)
{
    CheckNotNull(
        comp.get(),
        "Error Setting Comp Suggested Motion Blur Samples. Comp is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .CompSuite11()
            ->AEGP_SetCompSuggestedMotionBlurSamples(*comp.get(), samples));
}

int CompSuite11::GetCompMotionBlurAdaptiveSampleLimit(CompPtr comp)
{
    CheckNotNull(
        comp.get(),
        "Error Getting Comp Motion Blur Adaptive Sample Limit. Comp is Null");
    int samples;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .CompSuite11()
            ->AEGP_GetCompMotionBlurAdaptiveSampleLimit(*comp.get(), &samples));
    return samples;
}

void CompSuite11::SetCompMotionBlurAdaptiveSampleLimit(CompPtr comp,
                                                       int samples)
{
    CheckNotNull(
        comp.get(),
        "Error Setting Comp Motion Blur Adaptive Sample Limit. Comp is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .CompSuite11()
            ->AEGP_SetCompMotionBlurAdaptiveSampleLimit(*comp.get(), samples));
}

A_Time CompSuite11::GetCompWorkAreaStart(CompPtr comp)
{
    CheckNotNull(comp.get(),
                 "Error Getting Comp Work Area Start. Comp is Null");
    A_Time workAreaStart;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_GetCompWorkAreaStart(*comp.get(), &workAreaStart));
    return workAreaStart;
}

A_Time CompSuite11::GetCompWorkAreaDuration(CompPtr comp)
{
    CheckNotNull(comp.get(),
                 "Error Getting Comp Work Area Duration. Comp is Null");
    A_Time workAreaDuration;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .CompSuite11()
            ->AEGP_GetCompWorkAreaDuration(*comp.get(), &workAreaDuration));
    return workAreaDuration;
}

void CompSuite11::SetCompWorkAreaStartAndDuration(CompPtr comp,
                                                  A_Time workAreaStart,
                                                  A_Time workAreaDuration)
{
    CheckNotNull(
        comp.get(),
        "Error Setting Comp Work Area Start and Duration. Comp is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_SetCompWorkAreaStartAndDuration(
                     *comp.get(), &workAreaStart, &workAreaDuration));
}

LayerPtr CompSuite11::CreateSolidInComp(CompPtr comp, const std::string &name,
                                        int width, int height,
                                        const ColorVal &color, A_Time duration)
{
    CheckNotNull(comp.get(), "Error Creating Solid in Comp. Comp is Null");
    AEGP_LayerH layerH;
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_CreateSolidInComp(
            name16.data(), width, height, &toAEGP_ColorVal(color), *comp.get(),
            &duration, &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

LayerPtr CompSuite11::CreateCameraInComp(CompPtr comp, const std::string &name,
                                         A_FloatPoint centerPoint)
{
    CheckNotNull(comp.get(), "Error Creating Camera in Comp. Comp is Null");
    AEGP_LayerH layerH;
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_CreateCameraInComp(
            name16.data(), centerPoint, *comp.get(), &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

LayerPtr CompSuite11::CreateLightInComp(CompPtr comp, const std::string &name,
                                        A_FloatPoint centerPoint)
{
    CheckNotNull(comp.get(), "Error Creating Light in Comp. Comp is Null");
    AEGP_LayerH layerH;
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_CreateLightInComp(
            name16.data(), centerPoint, *comp.get(), &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

CompPtr CompSuite11::CreateComp(ItemPtr parentFolder, const std::string &name,
                                int width, int height,
                                const A_Ratio &pixelAspectRatio,
                                A_Time duration, const A_Ratio &framerate)
{
    AEGP_CompH compH;
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_CreateComp(
        *parentFolder.get(), name16.data(), width, height, &pixelAspectRatio,
        &duration, &framerate, &compH));
    return std::make_shared<AEGP_CompH>(compH);
}

A_Time CompSuite11::GetCompDisplayStartTime(CompPtr comp)
{
    CheckNotNull(comp.get(),
                 "Error Getting Comp Display Start Time. Comp is Null");
    A_Time startTime;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_GetCompDisplayStartTime(*comp.get(), &startTime));
    return startTime;
}

void CompSuite11::SetCompDisplayStartTime(CompPtr comp, A_Time startTime)
{
    CheckNotNull(comp.get(),
                 "Error Setting Comp Display Start Time. Comp is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_SetCompDisplayStartTime(*comp.get(), &startTime));
}

void CompSuite11::SetCompDuration(CompPtr comp, A_Time duration)
{
    CheckNotNull(comp.get(), "Error Setting Comp Duration. Comp is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_SetCompDuration(
            *comp.get(), &duration));
}

CompPtr CompSuite11::DuplicateComp(CompPtr comp)
{
    CheckNotNull(comp.get(), "Error Duplicating Comp. Comp is Null");
    AEGP_CompH newCompH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().CompSuite11()->AEGP_DuplicateComp(
        *comp.get(), &newCompH));
    return std::make_shared<AEGP_CompH>(newCompH);
}

A_Time CompSuite11::GetCompFrameDuration(CompPtr comp)
{
    CheckNotNull(comp.get(), "Error Getting Comp Frame Duration. Comp is Null");
    A_Time frameDuration;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_GetCompFrameDuration(*comp.get(), &frameDuration));
    return frameDuration;
}

CompPtr CompSuite11::GetMostRecentlyUsedComp()
{
    AEGP_CompH compH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_GetMostRecentlyUsedComp(&compH));
    if (compH == NULL)
    {
        return nullptr;
    }
    return std::make_shared<AEGP_CompH>(compH);
}

LayerPtr CompSuite11::CreateVectorLayerInComp(CompPtr comp)
{
    CheckNotNull(comp.get(),
                 "Error Creating Vector Layer in Comp. Comp is Null");
    AEGP_LayerH layerH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_CreateVectorLayerInComp(*comp.get(), &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

StreamRefPtr CompSuite11::GetNewCompMarkerStream(CompPtr parentComp)
{
    CheckNotNull(parentComp.get(),
                 "Error Getting New Comp Marker Stream. Parent Comp is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_GetNewCompMarkerStream(*m_suiteManager.GetPluginID(),
                                               *parentComp.get(), &streamH));
    return toStreamRefPtr(streamH);
}

bool CompSuite11::GetCompDisplayDropFrame(CompPtr comp)
{
    CheckNotNull(comp.get(),
                 "Error Getting Comp Display Drop Frame. Comp is Null");
    A_Boolean dropFrame;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_GetCompDisplayDropFrame(*comp.get(), &dropFrame));
    return dropFrame;
}

void CompSuite11::SetCompDisplayDropFrame(CompPtr comp, bool dropFrame)
{
    CheckNotNull(comp.get(),
                 "Error Setting Comp Display Drop Frame. Comp is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_SetCompDisplayDropFrame(*comp.get(), dropFrame));
}

void CompSuite11::ReorderCompSelection(CompPtr comp, int index)
{
    CheckNotNull(comp.get(), "Error Reordering Comp Selection. Comp is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CompSuite11()
                 ->AEGP_ReorderCompSelection(*comp.get(), index));
}

MemHandlePtr MemorySuite1::NewMemHandle(const std::string &what,
                                        AEGP_MemSize size, AE_MemFlag flags)
{
    AEGP_MemHandle memHandle;
    AE_CHECK(m_suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_NewMemHandle(
        *m_suiteManager.GetPluginID(), what.c_str(), size, AEGP_MemFlag(flags),
        &memHandle));
    return MemorySuite1::createPtr(memHandle);
}

void MemorySuite1::FreeMemHandle(MemHandlePtr memH)
{
    CheckNotNull(memH.get(),
                 "Error Freeing Memory Handle. Memory Handle is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_FreeMemHandle(
            *memH.get()));
}

void MemorySuite1::LockMemHandle(MemHandlePtr memHandle, void **ptrToPtr)
{
    CheckNotNull(memHandle.get(),
                 "Error Locking Memory Handle. Memory Handle is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_LockMemHandle(
            *memHandle.get(), ptrToPtr));
}

void MemorySuite1::UnlockMemHandle(MemHandlePtr memHandle)
{
    CheckNotNull(memHandle.get(),
                 "Error Unlocking Memory Handle. Memory Handle is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_UnlockMemHandle(
            *memHandle.get()));
}

AEGP_MemSize MemorySuite1::GetMemHandleSize(MemHandlePtr memHandle)
{
    CheckNotNull(memHandle.get(),
                 "Error Getting Memory Handle Size. Memory Handle is Null");
    AEGP_MemSize size;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_GetMemHandleSize(
            *memHandle.get(), &size));
    return size;
}

void MemorySuite1::ResizeMemHandle(const std::string &what,
                                   AEGP_MemSize newSize, MemHandlePtr memHandle)
{
    CheckNotNull(memHandle.get(),
                 "Error Resizing Memory Handle. Memory Handle is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_ResizeMemHandle(
            what.c_str(), newSize, *memHandle.get()));
}

void MemorySuite1::SetMemReportingOn(bool turnOn)
{
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_SetMemReportingOn(
            turnOn));
}

std::tuple<A_long, A_long> MemorySuite1::GetMemStats()
{
    A_long totalAllocated;
    A_long totalFreed;
    AE_CHECK(m_suiteManager.GetSuiteHandler().MemorySuite1()->AEGP_GetMemStats(
        *m_suiteManager.GetPluginID(), &totalAllocated, &totalFreed));
    return std::make_tuple(totalAllocated, totalFreed);
}

A_long LayerSuite9::GetCompNumLayers(CompPtr comp)
{
    CheckNotNull(comp.get(),
                 "Error Getting Comp Number of Layers. Comp is Null");
    A_long numLayers;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetCompNumLayers(
            *comp.get(), &numLayers));
    return numLayers;
}

LayerPtr LayerSuite9::GetCompLayerByIndex(CompPtr comp, A_long layerIndex)
{
    CheckNotNull(comp.get(), "Error Getting Comp Layer by Index. Comp is Null");
    AEGP_LayerH layerH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_GetCompLayerByIndex(*comp.get(), layerIndex, &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

LayerPtr LayerSuite9::GetActiveLayer()
{
    AEGP_LayerH layerH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetActiveLayer(
            &layerH));
    if (layerH == NULL)
    {
        return nullptr;
    }
    return std::make_shared<AEGP_LayerH>(layerH);
}

A_long LayerSuite9::GetLayerIndex(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Index. Layer is Null");
    A_long index;
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerIndex(
        *layer.get(), &index));
    return index;
}

ItemPtr LayerSuite9::GetLayerSourceItem(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Source Item. Layer is Null");
    AEGP_ItemH itemH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerSourceItem(
            *layer.get(), &itemH));
    return std::make_shared<AEGP_ItemH>(itemH);
}

A_long LayerSuite9::GetLayerSourceItemID(LayerPtr layer)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer Source Item ID. Layer is Null");
    A_long id;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_GetLayerSourceItemID(*layer.get(), &id));
    return id;
}

CompPtr LayerSuite9::GetLayerParentComp(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Parent Comp. Layer is Null");
    AEGP_CompH compH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerParentComp(
            *layer.get(), &compH));
    return std::make_shared<AEGP_CompH>(compH);
}

std::tuple<std::string, std::string> LayerSuite9::GetLayerName(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Name. Layer is Null");
    AEGP_MemHandle nameH;
    AEGP_MemHandle sourceNameH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerName(
        *m_suiteManager.GetPluginID(), *layer.get(), &nameH, &sourceNameH));
    return std::make_tuple(memHandleToString(nameH),
                           memHandleToString(sourceNameH));
}

AE_LayerQual LayerSuite9::GetLayerQuality(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Quality. Layer is Null");
    AEGP_LayerQuality quality;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerQuality(
            *layer.get(), &quality));
    return AE_LayerQual(quality);
}

void LayerSuite9::SetLayerQuality(LayerPtr layer, AE_LayerQual quality)
{
    CheckNotNull(layer.get(), "Error Setting Layer Quality. Layer is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_SetLayerQuality(
            *layer.get(), AEGP_LayerQuality(quality)));
}

AE_LayerFlag LayerSuite9::GetLayerFlags(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Flags. Layer is Null");
    A_long flags;
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerFlags(
        *layer.get(), &flags));
    return AE_LayerFlag(flags);
}

void LayerSuite9::SetLayerFlag(LayerPtr layer, AE_LayerFlag singleFlag,
                               bool value)
{
    CheckNotNull(layer.get(), "Error Setting Layer Flag. Layer is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_SetLayerFlag(
        *layer.get(), AEGP_LayerFlags(singleFlag), value));
}

bool LayerSuite9::IsLayerVideoReallyOn(LayerPtr layer)
{
    CheckNotNull(layer.get(),
                 "Error Checking if Layer Video is Really On. Layer is Null");
    A_Boolean isOn;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_IsLayerVideoReallyOn(*layer.get(), &isOn));
    return static_cast<bool>(isOn);
}

bool LayerSuite9::IsLayerAudioReallyOn(LayerPtr layer)
{
    CheckNotNull(layer.get(),
                 "Error Checking if Layer Audio is Really On. Layer is Null");
    A_Boolean isOn;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_IsLayerAudioReallyOn(*layer.get(), &isOn));
    return static_cast<bool>(isOn);
}

A_Time LayerSuite9::GetLayerCurrentTime(LayerPtr layer, AE_LTimeMode timeMode)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer Current Time. Layer is Null");
    A_Time time;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_GetLayerCurrentTime(*layer.get(),
                                            AEGP_LTimeMode(timeMode), &time));
    return time;
}

A_Time LayerSuite9::GetLayerInPoint(LayerPtr layer, AE_LTimeMode timeMode)
{
    CheckNotNull(layer.get(), "Error Getting Layer In Point. Layer is Null");
    A_Time time;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerInPoint(
            *layer.get(), AEGP_LTimeMode(timeMode), &time));
    return time;
}

A_Time LayerSuite9::GetLayerDuration(LayerPtr layer, AE_LTimeMode timeMode)
{
    CheckNotNull(layer.get(), "Error Getting Layer Duration. Layer is Null");
    A_Time time;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerDuration(
            *layer.get(), AEGP_LTimeMode(timeMode), &time));
    return time;
}

void LayerSuite9::SetLayerInPointAndDuration(LayerPtr layer,
                                             AE_LTimeMode timeMode,
                                             A_Time inPoint, A_Time duration)
{
    CheckNotNull(layer.get(),
                 "Error Setting Layer In Point and Duration. Layer is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_SetLayerInPointAndDuration(*layer.get(),
                                                   AEGP_LTimeMode(timeMode),
                                                   &inPoint, &duration));
}

A_Time LayerSuite9::GetLayerOffset(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Offset. Layer is Null");
    A_Time offset;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerOffset(
            *layer.get(), &offset));
    return offset;
}

void LayerSuite9::SetLayerOffset(LayerPtr layer, A_Time offset)
{
    CheckNotNull(layer.get(), "Error Setting Layer Offset. Layer is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_SetLayerOffset(
            *layer.get(), &offset));
}

A_Ratio LayerSuite9::GetLayerStretch(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Stretch. Layer is Null");
    A_Ratio stretch;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerStretch(
            *layer.get(), &stretch));
    return stretch;
}

void LayerSuite9::SetLayerStretch(LayerPtr layer, A_Ratio stretch)
{
    CheckNotNull(layer.get(), "Error Setting Layer Stretch. Layer is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_SetLayerStretch(
            *layer.get(), &stretch));
}

void LayerSuite9::SetLayerTransferMode(LayerPtr layer, AE_TransferFlags flags,
                                       AE_TrackMatte trackMatte)
{
}

bool LayerSuite9::IsAddLayerValid(ItemPtr itemToAdd, CompPtr intoComp)
{
    CheckNotNull(itemToAdd.get(),
                 "Error Checking if Add Layer is Valid. Item to Add is Null");
    CheckNotNull(intoComp.get(),
                 "Error Checking if Add Layer is Valid. Comp is Null");
    A_Boolean isValid;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_IsAddLayerValid(
            *itemToAdd.get(), *intoComp.get(), &isValid));
    return static_cast<bool>(isValid);
}

LayerPtr LayerSuite9::AddLayer(ItemPtr itemToAdd, CompPtr intoComp)
{
    CheckNotNull(itemToAdd.get(), "Error Adding Layer. Item to Add is Null");
    CheckNotNull(intoComp.get(), "Error Adding Layer. Comp is Null");
    AEGP_LayerH layerH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_AddLayer(
        *itemToAdd.get(), *intoComp.get(), &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

void LayerSuite9::ReorderLayer(LayerPtr layer, A_long layerIndex)
{
    CheckNotNull(layer.get(), "Error Reordering Layer. Layer is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_ReorderLayer(
        *layer.get(), layerIndex));
}

FloatRect LayerSuite9::GetLayerMaskedBounds(LayerPtr layer,
                                            AE_LTimeMode timeMode, A_Time time)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer Masked Bounds. Layer is Null");
    A_FloatRect rect;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_GetLayerMaskedBounds(
                     *layer.get(), AEGP_LTimeMode(timeMode), &time, &rect));
    return toFloatRect(rect);
}

AE_ObjectType LayerSuite9::GetLayerObjectType(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Object Type. Layer is Null");
    AEGP_ObjectType type;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerObjectType(
            *layer.get(), &type));
    return AE_ObjectType(type);
}

bool LayerSuite9::IsLayer3D(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Checking if Layer is 3D. Layer is Null");
    A_Boolean is3D;
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_IsLayer3D(
        *layer.get(), &is3D));
    return static_cast<bool>(is3D);
}

bool LayerSuite9::IsLayer2D(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Checking if Layer is 2D. Layer is Null");
    A_Boolean is2D;
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_IsLayer2D(
        *layer.get(), &is2D));
    return static_cast<bool>(is2D);
}

bool LayerSuite9::IsVideoActive(LayerPtr layer, AE_LTimeMode timeMode,
                                A_Time time)
{
    CheckNotNull(layer.get(),
                 "Error Checking if Video is Active. Layer is Null");
    A_Boolean isActive;
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_IsVideoActive(
        *layer.get(), AEGP_LTimeMode(timeMode), &time, &isActive));
    return static_cast<bool>(isActive);
}

bool LayerSuite9::IsLayerUsedAsTrackMatte(LayerPtr layer, bool fillMustBeActive)
{
    CheckNotNull(
        layer.get(),
        "Error Checking if Layer is Used as Track Matte. Layer is Null");
    A_Boolean isUsed;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_IsLayerUsedAsTrackMatte(*layer.get(), fillMustBeActive,
                                                &isUsed));
    return static_cast<bool>(isUsed);
}

bool LayerSuite9::DoesLayerHaveTrackMatte(LayerPtr layer)
{
    CheckNotNull(layer.get(),
                 "Error Checking if Layer has Track Matte. Layer is Null");
    A_Boolean hasTrackMatte;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_DoesLayerHaveTrackMatte(*layer.get(), &hasTrackMatte));
    return static_cast<bool>(hasTrackMatte);
}

A_Time LayerSuite9::ConvertCompToLayerTime(LayerPtr layer, A_Time compTime)
{
    CheckNotNull(layer.get(),
                 "Error Converting Comp to Layer Time. Layer is Null");
    A_Time layerTime;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .LayerSuite9()
            ->AEGP_ConvertCompToLayerTime(*layer.get(), &compTime, &layerTime));
    return layerTime;
}

A_Time LayerSuite9::ConvertLayerToCompTime(LayerPtr layer, A_Time layerTime)
{
    CheckNotNull(layer.get(),
                 "Error Converting Layer to Comp Time. Layer is Null");
    A_Time compTime;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .LayerSuite9()
            ->AEGP_ConvertLayerToCompTime(*layer.get(), &layerTime, &compTime));
    return compTime;
}

A_long LayerSuite9::GetLayerDancingRandValue(LayerPtr layer, A_Time compTime)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer Dancing Rand Value. Layer is Null");
    A_long value;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .LayerSuite9()
            ->AEGP_GetLayerDancingRandValue(*layer.get(), &compTime, &value));
    return value;
}

AEGP_LayerIDVal LayerSuite9::GetLayerID(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer ID. Layer is Null");
    AEGP_LayerIDVal id;
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerID(
        *layer.get(), &id));
    return id;
}

A_Matrix4 LayerSuite9::GetLayerToWorldXform(LayerPtr layer, A_Time compTime)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer to World Xform. Layer is Null");
    A_Matrix4 xform;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_GetLayerToWorldXform(*layer.get(), &compTime, &xform));
    return xform;
}

A_Matrix4 LayerSuite9::GetLayerToWorldXformFromView(LayerPtr layer,
                                                    A_Time viewTime,
                                                    A_Time compTime)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer to World Xform from View. Layer is Null");
    A_Matrix4 xform;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_GetLayerToWorldXformFromView(*layer.get(), &viewTime,
                                                     &compTime, &xform));
    return xform;
}

void LayerSuite9::SetLayerName(LayerPtr layer, const std::string &newName)
{
    CheckNotNull(layer.get(), "Error Setting Layer Name. Layer is Null");
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(newName);
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_SetLayerName(
        *layer.get(), name16.data()));
}

LayerPtr LayerSuite9::GetLayerParent(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Parent. Layer is Null");
    AEGP_LayerH parentLayerH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerParent(
            *layer.get(), &parentLayerH));
    return std::make_shared<AEGP_LayerH>(parentLayerH);
}

void LayerSuite9::SetLayerParent(LayerPtr layer, LayerPtr parentLayer)
{
    CheckNotNull(layer.get(), "Error Setting Layer Parent. Layer is Null");
    CheckNotNull(parentLayer.get(),
                 "Error Setting Layer Parent. Parent Layer is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_SetLayerParent(
            *layer.get(), *parentLayer.get()));
}

void LayerSuite9::DeleteLayer(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Deleting Layer. Layer is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_DeleteLayer(
        *layer.get()));
}

LayerPtr LayerSuite9::DuplicateLayer(LayerPtr origLayer)
{
    CheckNotNull(origLayer.get(),
                 "Error Duplicating Layer. Original Layer is Null");
    AEGP_LayerH newLayerH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_DuplicateLayer(
            *origLayer.get(), &newLayerH));
    return std::make_shared<AEGP_LayerH>(newLayerH);
}

LayerPtr LayerSuite9::GetLayerFromLayerID(CompPtr parentComp,
                                          AEGP_LayerIDVal id)
{
    CheckNotNull(parentComp.get(),
                 "Error Getting Layer from Layer ID. Parent Comp is Null");
    AEGP_LayerH layerH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_GetLayerFromLayerID(*parentComp.get(), id, &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

AEGP_LabelID LayerSuite9::GetLayerLabel(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Layer Label. Layer is Null");
    AEGP_LabelID label;
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetLayerLabel(
        *layer.get(), &label));
    return label;
}

void LayerSuite9::SetLayerLabel(LayerPtr layer, AEGP_LabelID label)
{
    CheckNotNull(layer.get(), "Error Setting Layer Label. Layer is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_SetLayerLabel(
        *layer.get(), label));
}

AE_LayerSamplingQual LayerSuite9::GetLayerSamplingQuality(LayerPtr layer)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer Sampling Quality. Layer is Null");
    AEGP_LayerSamplingQuality quality;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_GetLayerSamplingQuality(*layer.get(), &quality));
    return AE_LayerSamplingQual(quality);
}

void LayerSuite9::SetLayerSamplingQuality(LayerPtr layer,
                                          AE_LayerSamplingQual quality)
{
    CheckNotNull(layer.get(),
                 "Error Setting Layer Sampling Quality. Layer is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerSuite9()
                 ->AEGP_SetLayerSamplingQuality(
                     *layer.get(), AEGP_LayerSamplingQuality(quality)));
}

LayerPtr LayerSuite9::GetTrackMatteLayer(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Getting Track Matte Layer. Layer is Null");
    AEGP_LayerH matteLayerH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_GetTrackMatteLayer(
            *layer.get(), &matteLayerH));
    return std::make_shared<AEGP_LayerH>(matteLayerH);
}

void LayerSuite9::SetTrackMatte(LayerPtr layer, LayerPtr trackMatteLayer,
                                AE_TrackMatte trackMatteType)
{
    CheckNotNull(layer.get(), "Error Setting Track Matte. Layer is Null");
    CheckNotNull(trackMatteLayer.get(),
                 "Error Setting Track Matte. Track Matte Layer is Null");

    AE_CHECK(m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_SetTrackMatte(
        *layer.get(), *trackMatteLayer.get(), AEGP_TrackMatte(trackMatteType)));
}

void LayerSuite9::RemoveTrackMatte(LayerPtr layer)
{
    CheckNotNull(layer.get(), "Error Removing Track Matte. Layer is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().LayerSuite9()->AEGP_RemoveTrackMatte(
            *layer.get()));
}

bool StreamSuite6::IsStreamLegal(LayerPtr layer, AE_LayerStream whichStream)
{
    CheckNotNull(layer.get(),
                 "Error Checking if Stream is Legal. Layer is Null");
    A_Boolean isLegal;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().StreamSuite6()->AEGP_IsStreamLegal(
            *layer.get(), AEGP_LayerStream(whichStream), &isLegal));
    return static_cast<bool>(isLegal);
}

bool StreamSuite6::CanVaryOverTime(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Checking if Stream can Vary Over Time. Stream is Null");
    A_Boolean canVary;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().StreamSuite6()->AEGP_CanVaryOverTime(
            *stream.get(), &canVary));
    return static_cast<bool>(canVary);
}

AE_KeyInterpMask StreamSuite6::GetValidInterpolations(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Valid Interpolations. Stream is Null");
    A_long validInterps;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .StreamSuite6()
                 ->AEGP_GetValidInterpolations(*stream.get(), &validInterps));
    return AE_KeyInterpMask(validInterps);
}

StreamRefPtr StreamSuite6::GetNewLayerStream(LayerPtr layer,
                                             AE_LayerStream whichStream)
{
    CheckNotNull(layer.get(), "Error Getting New Layer Stream. Layer is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().StreamSuite6()->AEGP_GetNewLayerStream(
            *m_suiteManager.GetPluginID(), *layer.get(),
            AEGP_LayerStream(whichStream), &streamH));
    return toStreamRefPtr(streamH);
}

A_long StreamSuite6::GetEffectNumParamStreams(EffectRefPtr effectRef)
{
    A_long numStreams;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .StreamSuite6()
            ->AEGP_GetEffectNumParamStreams(*effectRef.get(), &numStreams));
    return numStreams;
}

StreamRefPtr StreamSuite6::GetNewEffectStreamByIndex(EffectRefPtr effectRef,
                                                     A_long paramIndex)
{
    CheckNotNull(effectRef.get(),
                 "Error Getting New Effect Stream by Index. Effect is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .StreamSuite6()
                 ->AEGP_GetNewEffectStreamByIndex(*m_suiteManager.GetPluginID(),
                                                  *effectRef.get(), paramIndex,
                                                  &streamH));
    return toStreamRefPtr(streamH);
}

StreamRefPtr StreamSuite6::GetNewMaskStream(MaskRefPtr maskRef,
                                            AE_MaskStream whichStream)
{
    CheckNotNull(maskRef.get(), "Error Getting New Mask Stream. Mask is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().StreamSuite6()->AEGP_GetNewMaskStream(
            *m_suiteManager.GetPluginID(), *maskRef.get(),
            AEGP_MaskStream(whichStream), &streamH));
    return toStreamRefPtr(streamH);
}

std::string StreamSuite6::GetStreamName(StreamRefPtr stream, bool forceEnglish)
{
    CheckNotNull(stream.get(), "Error Getting Stream Name. Stream is Null");
    AEGP_MemHandle nameH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().StreamSuite6()->AEGP_GetStreamName(
            *m_suiteManager.GetPluginID(), *stream.get(), forceEnglish,
            &nameH));
    return memHandleToString(nameH);
}

std::string StreamSuite6::GetStreamUnitsText(StreamRefPtr stream,
                                             bool forceEnglish)
{
    CheckNotNull(stream.get(),
                 "Error Getting Stream Units Text. Stream is Null");
    A_char *unitsText = nullptr;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .StreamSuite6()
            ->AEGP_GetStreamUnitsText(*stream.get(), forceEnglish, unitsText));
    return std::string(unitsText);
}

std::tuple<AE_StreamFlag, double, double>
StreamSuite6::GetStreamProperties(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Stream Properties. Stream is Null");
    AEGP_StreamFlags flags;
    A_FpLong minVal;
    A_FpLong maxVal;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .StreamSuite6()
                 ->AEGP_GetStreamProperties(*stream.get(), &flags, &minVal,
                                            &maxVal));
    return std::make_tuple(AE_StreamFlag(flags), minVal, maxVal);
}

bool StreamSuite6::IsStreamTimevarying(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Checking if Stream is Timevarying. Stream is Null");
    A_Boolean isTimeVarying;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .StreamSuite6()
                 ->AEGP_IsStreamTimevarying(*stream.get(), &isTimeVarying));
    return static_cast<bool>(isTimeVarying);
}

AE_StreamType StreamSuite6::GetStreamType(StreamRefPtr stream)
{
    CheckNotNull(stream.get(), "Error Getting Stream Type. Stream is Null");
    AEGP_StreamType type;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().StreamSuite6()->AEGP_GetStreamType(
            *stream.get(), &type));
    return AE_StreamType(type);
}

AEGP_StreamValue2 StreamSuite6::GetNewStreamValue(StreamRefPtr stream,
                                                  AE_LTimeMode timeMode,
                                                  A_Time time,
                                                  bool preExpression)
{
    CheckNotNull(stream.get(),
                 "Error Getting New Stream Value. Stream is Null");
    AEGP_StreamValue2 value;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().StreamSuite6()->AEGP_GetNewStreamValue(
            *m_suiteManager.GetPluginID(), *stream.get(),
            AEGP_LTimeMode(timeMode), &time, preExpression, &value));
    return value;
}

void StreamSuite6::DisposeStreamValue(AEGP_StreamValue2 value)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .StreamSuite6()
                 ->AEGP_DisposeStreamValue(&value));
}

void StreamSuite6::SetStreamValue(StreamRefPtr stream, AEGP_StreamValue2 value)
{
    CheckNotNull(stream.get(), "Error Setting Stream Value. Stream is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().StreamSuite6()->AEGP_SetStreamValue(
            *m_suiteManager.GetPluginID(), *stream.get(), &value));
}

std::tuple<AEGP_StreamVal2, AE_StreamType>
StreamSuite6::GetLayerStreamValue(LayerPtr layer, AE_LayerStream whichStream,
                                  AE_LTimeMode timeMode, A_Time time,
                                  bool preExpression)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer Stream Value. Layer is Null");
    AEGP_StreamVal2 value;
    AEGP_StreamType type;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .StreamSuite6()
                 ->AEGP_GetLayerStreamValue(*layer.get(),
                                            AEGP_LayerStream(whichStream),
                                            AEGP_LTimeMode(timeMode), &time,
                                            preExpression, &value, &type));
    return std::make_tuple(value, AE_StreamType(type));
}

StreamRefPtr StreamSuite6::DuplicateStreamRef(StreamRefPtr stream)
{
    CheckNotNull(stream.get(), "Error Duplicating Stream Ref. Stream is Null");
    AEGP_StreamRefH newStreamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .StreamSuite6()
                 ->AEGP_DuplicateStreamRef(*m_suiteManager.GetPluginID(),
                                           *stream.get(), &newStreamH));
    return toStreamRefPtr(newStreamH);
}

int StreamSuite6::GetUniqueStreamID(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Unique Stream ID. Stream is Null");
    A_long id;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().StreamSuite6()->AEGP_GetUniqueStreamID(
            *stream.get(), &id));
    return id;
}

StreamRefPtr DynamicStreamSuite4::GetNewStreamRefForLayer(LayerPtr layer)
{
    CheckNotNull(layer.get(),
                 "Error Getting New Stream Ref for Layer. Layer is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetNewStreamRefForLayer(*m_suiteManager.GetPluginID(),
                                                *layer.get(), &streamH));
    return toStreamRefPtr(streamH);
}

StreamRefPtr DynamicStreamSuite4::GetNewStreamRefForMask(MaskRefPtr mask)
{
    CheckNotNull(mask.get(),
                 "Error Getting New Stream Ref for Mask. Mask is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetNewStreamRefForMask(*m_suiteManager.GetPluginID(),
                                               *mask.get(), &streamH));
    return toStreamRefPtr(streamH);
}

A_long DynamicStreamSuite4::GetStreamDepth(StreamRefPtr stream)
{
    CheckNotNull(stream.get(), "Error Getting Stream Depth. Stream is Null");
    A_long depth;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetStreamDepth(*stream.get(), &depth));
    return depth;
}

AE_StreamGroupingType
DynamicStreamSuite4::GetStreamGroupingType(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Stream Grouping Type. Stream is Null");
    AEGP_StreamGroupingType type;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetStreamGroupingType(*stream.get(), &type));
    return AE_StreamGroupingType(type);
}

A_long DynamicStreamSuite4::GetNumStreamsInGroup(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Number of Streams in Group. Stream is Null");
    A_long numStreams;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetNumStreamsInGroup(*stream.get(), &numStreams));
    return numStreams;
}

AE_DynStreamFlag DynamicStreamSuite4::GetDynamicStreamFlags(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Dynamic Stream Flags. Stream is Null");
    AEGP_DynStreamFlags flags;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetDynamicStreamFlags(*stream.get(), &flags));
    return AE_DynStreamFlag(flags);
}

void DynamicStreamSuite4::SetDynamicStreamFlag(StreamRefPtr stream,
                                               AE_DynStreamFlag oneFlag,
                                               bool undoable, bool set)
{
    CheckNotNull(stream.get(),
                 "Error Setting Dynamic Stream Flag. Stream is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_SetDynamicStreamFlag(*stream.get(),
                                             AEGP_DynStreamFlags(oneFlag),
                                             undoable, set));
}

StreamRefPtr
DynamicStreamSuite4::GetNewStreamRefByIndex(StreamRefPtr parentGroup,
                                            A_long index)
{
    CheckNotNull(parentGroup.get(),
                 "Error Getting New Stream Ref by Index. Parent Group is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetNewStreamRefByIndex(*m_suiteManager.GetPluginID(),
                                               *parentGroup.get(), index,
                                               &streamH));
    return toStreamRefPtr(streamH);
}

StreamRefPtr
DynamicStreamSuite4::GetNewStreamRefByMatchname(StreamRefPtr parentGroup,
                                                const std::string &matchName)
{
    CheckNotNull(
        parentGroup.get(),
        "Error Getting New Stream Ref by Matchname. Parent Group is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetNewStreamRefByMatchname(
                     *m_suiteManager.GetPluginID(), *parentGroup.get(),
                     matchName.c_str(), &streamH));
    return toStreamRefPtr(streamH);
}

void DynamicStreamSuite4::DeleteStream(StreamRefPtr stream)
{
    CheckNotNull(stream.get(), "Error Deleting Stream. Stream is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_DeleteStream(*stream.get()));
}

void DynamicStreamSuite4::ReorderStream(StreamRefPtr stream, A_long newIndex)
{
    CheckNotNull(stream.get(), "Error Reordering Stream. Stream is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_ReorderStream(*stream.get(), newIndex));
}

A_long DynamicStreamSuite4::DuplicateStream(StreamRefPtr stream)
{
    CheckNotNull(stream.get(), "Error Duplicating Stream. Stream is Null");
    A_long newStreamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_DuplicateStream(*m_suiteManager.GetPluginID(),
                                        *stream.get(), &newStreamH));
    return newStreamH;
}

void DynamicStreamSuite4::SetStreamName(StreamRefPtr stream,
                                        const std::string &newName)
{
    CheckNotNull(stream.get(), "Error Setting Stream Name. Stream is Null");
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(newName);
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_SetStreamName(*stream.get(), name16.data()));
}

bool DynamicStreamSuite4::CanAddStream(StreamRefPtr parentGroup,
                                       const std::string &matchName)
{
    CheckNotNull(parentGroup.get(),
                 "Error Checking if Can Add Stream. Parent Group is Null");
    A_Boolean canAdd;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_CanAddStream(*parentGroup.get(), matchName.c_str(),
                                     &canAdd));
    return static_cast<bool>(canAdd);
}

StreamRefPtr DynamicStreamSuite4::AddStream(StreamRefPtr parentGroup,
                                            const std::string &matchName)
{
    CheckNotNull(parentGroup.get(),
                 "Error Adding Stream. Parent Group is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().DynamicStreamSuite4()->AEGP_AddStream(
            *m_suiteManager.GetPluginID(), *parentGroup.get(),
            matchName.c_str(), &streamH));
    return toStreamRefPtr(streamH);
}

std::string DynamicStreamSuite4::GetMatchname(StreamRefPtr stream)
{
    CheckNotNull(stream.get(), "Error Getting Matchname. Stream is Null");
    A_char *matchname = nullptr;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetMatchName(*stream.get(), matchname));
    return std::string(matchname);
}

StreamRefPtr DynamicStreamSuite4::GetNewParentStreamRef(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting New Parent Stream Ref. Stream is Null");
    AEGP_StreamRefH parentStreamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetNewParentStreamRef(*m_suiteManager.GetPluginID(),
                                              *stream.get(), &parentStreamH));
    return toStreamRefPtr(parentStreamH);
}

bool DynamicStreamSuite4::GetStreamIsModified(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Stream is Modified. Stream is Null");
    A_Boolean isModified;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetStreamIsModified(*stream.get(), &isModified));
    return static_cast<bool>(isModified);
}

bool DynamicStreamSuite4::IsSeparationLeader(StreamRefPtr stream)
{
    CheckNotNull(
        stream.get(),
        "Error Checking if Stream is Separation Leader. Stream is Null");
    A_Boolean isLeader;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_IsSeparationLeader(*stream.get(), &isLeader));
    return static_cast<bool>(isLeader);
}

bool DynamicStreamSuite4::AreDimensionsSeparated(StreamRefPtr leaderStream)
{
    CheckNotNull(
        leaderStream.get(),
        "Error Checking if Dimensions are Separated. Leader Stream is Null");
    A_Boolean areSeparated;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .DynamicStreamSuite4()
            ->AEGP_AreDimensionsSeparated(*leaderStream.get(), &areSeparated));
    return static_cast<bool>(areSeparated);
}

void DynamicStreamSuite4::SetDimensionsSeparated(StreamRefPtr leaderStream,
                                                 bool separated)
{
    CheckNotNull(leaderStream.get(),
                 "Error Setting Dimensions Separated. Leader Stream is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_SetDimensionsSeparated(*leaderStream.get(), separated));
}

StreamRefPtr
DynamicStreamSuite4::GetSeparationFollower(A_long dimension,
                                           StreamRefPtr leaderStream)
{
    CheckNotNull(leaderStream.get(),
                 "Error Getting Separation Follower. Leader Stream is Null");
    AEGP_StreamRefH followerStreamH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetSeparationFollower(*leaderStream.get(), dimension,
                                              &followerStreamH));
    return toStreamRefPtr(followerStreamH);
}

bool DynamicStreamSuite4::IsSeparationFollower(StreamRefPtr stream)
{
    CheckNotNull(
        stream.get(),
        "Error Checking if Stream is Separation Follower. Stream is Null");
    A_Boolean isFollower;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_IsSeparationFollower(*stream.get(), &isFollower));
    return static_cast<bool>(isFollower);
}

StreamRefPtr
DynamicStreamSuite4::GetSeparationLeader(StreamRefPtr followerStream)
{
    CheckNotNull(followerStream.get(),
                 "Error Getting Separation Leader. Follower Stream is Null");
    AEGP_StreamRefH leaderStreamH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .DynamicStreamSuite4()
            ->AEGP_GetSeparationLeader(*followerStream.get(), &leaderStreamH));
    return toStreamRefPtr(leaderStreamH);
}

A_short DynamicStreamSuite4::GetSeparationDimension(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Separation Dimension. Stream is Null");
    A_short dimension;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .DynamicStreamSuite4()
                 ->AEGP_GetSeparationDimension(*stream.get(), &dimension));
    return dimension;
}

A_long KeyframeSuite5::GetStreamNumKFs(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Stream Number of Keyframes. Stream is Null");
    A_long numKFs;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().KeyframeSuite5()->AEGP_GetStreamNumKFs(
            *stream.get(), &numKFs));
    return numKFs;
}

A_Time KeyframeSuite5::GetKeyframeTime(StreamRefPtr stream,
                                       AEGP_KeyframeIndex keyIndex,
                                       AE_LTimeMode timeMode)
{
    CheckNotNull(stream.get(), "Error Getting Keyframe Time. Stream is Null");
    A_Time time;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeTime(
            *stream.get(), keyIndex, AEGP_LTimeMode(timeMode), &time));
    return time;
}

AEGP_KeyframeIndex KeyframeSuite5::InsertKeyframe(StreamRefPtr stream,
                                                  AE_LTimeMode timeMode,
                                                  const A_Time &time)
{
    CheckNotNull(stream.get(), "Error Inserting Keyframe. Stream is Null");
    AEGP_KeyframeIndex keyIndex;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().KeyframeSuite5()->AEGP_InsertKeyframe(
            *stream.get(), AEGP_LTimeMode(timeMode), &time, &keyIndex));
    return keyIndex;
}

void KeyframeSuite5::DeleteKeyframe(StreamRefPtr stream,
                                    AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(stream.get(), "Error Deleting Keyframe. Stream is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().KeyframeSuite5()->AEGP_DeleteKeyframe(
            *stream.get(), keyIndex));
}

AEGP_StreamValue2
KeyframeSuite5::GetNewKeyframeValue(StreamRefPtr stream,
                                    AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(stream.get(),
                 "Error Getting New Keyframe Value. Stream is Null");
    AEGP_StreamValue2 value;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_GetNewKeyframeValue(*m_suiteManager.GetPluginID(),
                                            *stream.get(), keyIndex, &value));
    return value;
}

void KeyframeSuite5::SetKeyframeValue(StreamRefPtr stream,
                                      AEGP_KeyframeIndex keyIndex,
                                      AEGP_StreamValue2 value)
{
    CheckNotNull(stream.get(), "Error Setting Keyframe Value. Stream is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_SetKeyframeValue(*stream.get(), keyIndex, &value));
}

A_short KeyframeSuite5::GetStreamValueDimensionality(StreamRefPtr stream)
{
    CheckNotNull(stream.get(),
                 "Error Getting Stream Value Dimensionality. Stream is Null");
    A_short dimension;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .KeyframeSuite5()
            ->AEGP_GetStreamValueDimensionality(*stream.get(), &dimension));
    return dimension;
}

A_short KeyframeSuite5::GetStreamTemporalDimensionality(StreamRefPtr stream)
{
    CheckNotNull(
        stream.get(),
        "Error Getting Stream Temporal Dimensionality. Stream is Null");
    A_short dimension;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .KeyframeSuite5()
            ->AEGP_GetStreamTemporalDimensionality(*stream.get(), &dimension));
    return dimension;
}

std::tuple<AEGP_StreamValue2, AEGP_StreamValue2>
KeyframeSuite5::GetNewKeyframeSpatialTangents(StreamRefPtr stream,
                                              AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(stream.get(),
                 "Error Getting New Keyframe Spatial Tangents. Stream is Null");
    AEGP_StreamValue2 inTan;
    AEGP_StreamValue2 outTan;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_GetNewKeyframeSpatialTangents(
                     *m_suiteManager.GetPluginID(), *stream.get(), keyIndex,
                     &inTan, &outTan));
    return std::make_tuple(inTan, outTan);
}

void KeyframeSuite5::SetKeyframeSpatialTangents(StreamRefPtr stream,
                                                AEGP_KeyframeIndex keyIndex,
                                                AEGP_StreamValue2 inTan,
                                                AEGP_StreamValue2 outTan)
{
    CheckNotNull(stream.get(),
                 "Error Setting Keyframe Spatial Tangents. Stream is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_SetKeyframeSpatialTangents(*stream.get(), keyIndex,
                                                   &inTan, &outTan));
}

std::tuple<AE_KeyframeEase, AE_KeyframeEase>
KeyframeSuite5::GetKeyframeTemporalEase(StreamRefPtr stream,
                                        AEGP_KeyframeIndex keyIndex,
                                        A_long dimension)
{
    CheckNotNull(stream.get(),
				 "Error Getting Keyframe Temporal Ease. Stream is Null");
    AEGP_KeyframeEase inEase;
    AEGP_KeyframeEase outEase;
	AE_CHECK(m_suiteManager.GetSuiteHandler()
				 .KeyframeSuite5()
				 ->AEGP_GetKeyframeTemporalEase(*stream.get(), keyIndex,
											   dimension, &inEase, &outEase));
        return std::make_tuple(toKeyframeEase(inEase), toKeyframeEase(outEase));
}

void KeyframeSuite5::SetKeyframeTemporalEase(StreamRefPtr stream,
                                             AEGP_KeyframeIndex keyIndex,
                                             A_long dimension,
                                             AE_KeyframeEase inEase,
                                             AE_KeyframeEase outEase)
{
    CheckNotNull(stream.get(),
                 "Error Setting Keyframe Temporal Ease. Stream is Null");
AE_CHECK(m_suiteManager.GetSuiteHandler()
.KeyframeSuite5()
				 ->AEGP_SetKeyframeTemporalEase(*stream.get(), keyIndex, dimension,
                     &toAEGP_KeyframeEase(inEase), &toAEGP_KeyframeEase(outEase)));
}

AE_KeyframeFlag KeyframeSuite5::GetKeyframeFlags(StreamRefPtr stream,
                                                 AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(stream.get(), "Error Getting Keyframe Flags. Stream is Null");
    AEGP_KeyframeFlags flags;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_GetKeyframeFlags(*stream.get(), keyIndex, &flags));
    return AE_KeyframeFlag(flags);
}

void KeyframeSuite5::SetKeyframeFlag(StreamRefPtr stream,
                                     AEGP_KeyframeIndex keyIndex,
                                     AE_KeyframeFlag flag, bool value)
{
    CheckNotNull(stream.get(), "Error Setting Keyframe Flag. Stream is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeFlag(
            *stream.get(), keyIndex, AEGP_KeyframeFlags(flag), value));
}

std::tuple<AE_KeyInterp, AE_KeyInterp>
KeyframeSuite5::GetKeyframeInterpolation(StreamRefPtr stream,
                                         AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(stream.get(),
                 "Error Getting Keyframe Interpolation. Stream is Null");
    A_long inInterp;
    A_long outInterp;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_GetKeyframeInterpolation(*stream.get(), keyIndex,
                                                 &inInterp, &outInterp));
    return std::make_tuple(AE_KeyInterp(inInterp), AE_KeyInterp(outInterp));
}

void KeyframeSuite5::SetKeyframeInterpolation(StreamRefPtr stream,
                                              AEGP_KeyframeIndex keyIndex,
                                              AE_KeyInterp inInterp,
                                              AE_KeyInterp outInterp)
{
    CheckNotNull(stream.get(),
                 "Error Setting Keyframe Interpolation. Stream is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_SetKeyframeInterpolation(*stream.get(), keyIndex,
                                                 A_long(inInterp),
                                                 A_long(outInterp)));
}

AddKeyframesInfoPtr KeyframeSuite5::StartAddKeyframes(StreamRefPtr stream)
{
    CheckNotNull(stream.get(), "Error Starting Add Keyframes. Stream is Null");
    AEGP_AddKeyframesInfoH akH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_StartAddKeyframes(*stream.get(), &akH));
    return KeyframeSuite5::createPtr(akH);
}

AEGP_KeyframeIndex KeyframeSuite5::AddKeyframes(AddKeyframesInfoPtr akH,
                                                AE_LTimeMode timeMode,
                                                const A_Time &time)
{
    CheckNotNull(akH.get(),
                 "Error Adding Keyframes. Add Keyframes Info is Null");
    AEGP_KeyframeIndex keyIndex;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().KeyframeSuite5()->AEGP_AddKeyframes(
            *akH.get(), AEGP_LTimeMode(timeMode), &time, &keyIndex));
    return keyIndex;
}

void KeyframeSuite5::SetAddKeyframe(AddKeyframesInfoPtr akH,
                                    AEGP_KeyframeIndex keyIndex,
                                    AEGP_StreamValue2 value)
{
    CheckNotNull(akH.get(),
                 "Error Setting Add Keyframe. Add Keyframes Info is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().KeyframeSuite5()->AEGP_SetAddKeyframe(
            *akH.get(), keyIndex, &value));
}

A_long KeyframeSuite5::GetKeyframeLabelColorIndex(StreamRefPtr stream,
                                                  AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(stream.get(),
                 "Error Getting Keyframe Label Color Index. Stream is Null");
    A_long keyLabel;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_GetKeyframeLabelColorIndex(*stream.get(), keyIndex,
                                                   &keyLabel));
    return keyLabel;
}

void KeyframeSuite5::SetKeyframeLabelColorIndex(StreamRefPtr stream,
                                                AEGP_KeyframeIndex keyIndex,
                                                A_long keyLabel)
{
    CheckNotNull(stream.get(),
                 "Error Setting Keyframe Label Color Index. Stream is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .KeyframeSuite5()
                 ->AEGP_SetKeyframeLabelColorIndex(*stream.get(), keyIndex,
                                                   keyLabel));
}

std::string TextDocumentSuite1::getNewText(TextDocumentPtr text_documentH)
{
    CheckNotNull(text_documentH.get(),
                 "Error Getting New Text. Text Document is Null");
    AEGP_MemHandle textH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().TextDocumentSuite1()->AEGP_GetNewText(
            *m_suiteManager.GetPluginID(), *text_documentH.get(), &textH));
    return memHandleToString(textH);
}

void TextDocumentSuite1::setText(TextDocumentPtr text_documentH,
                                 const std::string &unicodePS)
{
    CheckNotNull(text_documentH.get(),
                 "Error Setting Text. Text Document is Null");
    const A_u_short *unicodeP = ConvertUTF8ToUTF16(unicodePS).data();
    A_long lengthL = static_cast<A_long>(unicodePS.size());
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().TextDocumentSuite1()->AEGP_SetText(
            *text_documentH.get(), unicodeP, lengthL));
}

MarkerValPtr MarkerSuite3::getNewMarker()
{
    AEGP_MarkerValP markerP;
    AE_CHECK(m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_NewMarker(
        &markerP));
    return MarkerSuite3::createPtr(markerP);
}

void MarkerSuite3::disposeMarker(MarkerValPtr markerP) {}

MarkerValPtr MarkerSuite3::duplicateMarker(MarkerValPtr markerP)
{
    CheckNotNull(markerP.get(), "Error Duplicating Marker. Marker is Null");
    AEGP_MarkerValP newMarkerP;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_DuplicateMarker(
            *markerP.get(), &newMarkerP));
    return MarkerSuite3::createPtr(newMarkerP);
}

void MarkerSuite3::setMarkerFlag(MarkerValPtr markerP,
                                 AEGP_MarkerFlagType flagType, bool valueB)
{
    CheckNotNull(markerP.get(), "Error Setting Marker Flag. Marker is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerFlag(
            *markerP.get(), flagType, valueB));
}

bool MarkerSuite3::getMarkerFlag(MarkerValPtr markerP,
                                 AEGP_MarkerFlagType flagType)
{
    CheckNotNull(markerP.get(), "Error Getting Marker Flag. Marker is Null");
    A_Boolean valueB;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerFlag(
            *markerP.get(), flagType, &valueB));
    return static_cast<bool>(valueB);
}

std::string MarkerSuite3::getMarkerString(MarkerValPtr markerP,
                                          AE_MarkerStringType strType)
{
    CheckNotNull(markerP.get(), "Error Getting Marker String. Marker is Null");
    AEGP_MemHandle stringH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerString(
            *m_suiteManager.GetPluginID(), *markerP.get(),
            AEGP_MarkerStringType(strType), &stringH));
    return memHandleToString(stringH);
}

void MarkerSuite3::setMarkerString(MarkerValPtr markerP,
                                   AE_MarkerStringType strType,
                                   const std::string &unicodeP, A_long lengthL)
{
    CheckNotNull(markerP.get(), "Error Setting Marker String. Marker is Null");
    const A_u_short *unicodeP16 = ConvertUTF8ToUTF16(unicodeP).data();
    lengthL = static_cast<A_long>(unicodeP.size());
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerString(
            *markerP.get(), AEGP_MarkerStringType(strType), unicodeP16,
            lengthL));
}

A_long MarkerSuite3::countCuePointParams(MarkerValPtr markerP)
{
    CheckNotNull(markerP.get(),
                 "Error Counting Cue Point Params. Marker is Null");
    A_long countL;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MarkerSuite3()
                 ->AEGP_CountCuePointParams(*markerP.get(), &countL));
    return countL;
}

std::tuple<std::string, std::string>
MarkerSuite3::getIndCuePointParam(MarkerValPtr markerP, A_long param_indexL)
{
    CheckNotNull(markerP.get(),
                 "Error Getting Ind Cue Point Param. Marker is Null");
    AEGP_MemHandle keyH;
    AEGP_MemHandle valueH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MarkerSuite3()
                 ->AEGP_GetIndCuePointParam(*m_suiteManager.GetPluginID(),
                                            *markerP.get(), param_indexL, &keyH,
                                            &valueH));
    return std::make_tuple(memHandleToString(keyH), memHandleToString(valueH));
}

void MarkerSuite3::setIndCuePointParam(
    MarkerValPtr markerP, A_long param_indexL, const std::string &unicodeKeyP,
    A_long key_lengthL, const std::string &unicodeValueP, A_long value_lengthL)
{
    CheckNotNull(markerP.get(),
                 "Error Setting Ind Cue Point Param. Marker is Null");
    const A_u_short *unicodeKeyP16 = ConvertUTF8ToUTF16(unicodeKeyP).data();
    key_lengthL = static_cast<A_long>(unicodeKeyP.size());
    const A_u_short *unicodeValueP16 = ConvertUTF8ToUTF16(unicodeValueP).data();
    value_lengthL = static_cast<A_long>(unicodeValueP.size());
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MarkerSuite3()
                 ->AEGP_SetIndCuePointParam(*markerP.get(), param_indexL,
                                            unicodeKeyP16, key_lengthL,
                                            unicodeValueP16, value_lengthL));
}

void MarkerSuite3::insertCuePointParam(MarkerValPtr markerP,
                                       A_long param_indexL)
{
    CheckNotNull(markerP.get(),
                 "Error Inserting Cue Point Param. Marker is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MarkerSuite3()
                 ->AEGP_InsertCuePointParam(*markerP.get(), param_indexL));
}

void MarkerSuite3::deleteIndCuePointParam(MarkerValPtr markerP,
                                          A_long param_indexL)
{
    CheckNotNull(markerP.get(),
                 "Error Deleting Ind Cue Point Param. Marker is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MarkerSuite3()
                 ->AEGP_DeleteIndCuePointParam(*markerP.get(), param_indexL));
}

void MarkerSuite3::setMarkerDuration(MarkerValPtr markerP,
                                     const A_Time &durationPT)
{
    CheckNotNull(markerP.get(),
                 "Error Setting Marker Duration. Marker is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerDuration(
            *markerP.get(), &durationPT));
}

A_Time MarkerSuite3::getMarkerDuration(MarkerValPtr markerP)
{
    CheckNotNull(markerP.get(),
                 "Error Getting Marker Duration. Marker is Null");
    A_Time durationT;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerDuration(
            *markerP.get(), &durationT));
    return durationT;
}

void MarkerSuite3::setMarkerLabel(MarkerValPtr markerP, A_long value)
{
    CheckNotNull(markerP.get(), "Error Setting Marker Label. Marker is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerLabel(
            *markerP.get(), value));
}

A_long MarkerSuite3::getMarkerLabel(MarkerValPtr markerP)
{
    CheckNotNull(markerP.get(), "Error Getting Marker Label. Marker is Null");
    A_long labelL;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerLabel(
            *markerP.get(), &labelL));
    return labelL;
}

TextOutlinesPtr TextLayerSuite1::getNewTextOutlines(LayerPtr layer,
                                                    const A_Time &layer_time)
{
    CheckNotNull(layer.get(), "Error Getting New Text Outlines. Layer is Null");
    AEGP_TextOutlinesH outlinesH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .TextLayerSuite1()
            ->AEGP_GetNewTextOutlines(*layer.get(), &layer_time, &outlinesH));
    return TextLayerSuite1::createPtr(outlinesH);
}

int TextLayerSuite1::getNumTextOutlines(TextOutlinesPtr outlines)
{
    CheckNotNull(outlines.get(),
                 "Error Getting Number of Text Outlines. Outlines is Null");
    A_long numOutlines;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .TextLayerSuite1()
                 ->AEGP_GetNumTextOutlines(*outlines.get(), &numOutlines));
    return numOutlines;
}

PF_PathOutlinePtr
TextLayerSuite1::getIndexedTextOutline(TextOutlinesPtr outlines, int path_index)
{
    return PF_PathOutlinePtr();
}

A_long EffectSuite4::getLayerNumEffects(LayerPtr layer)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer Number of Effects. Layer is Null");
    A_long numEffects;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .EffectSuite4()
                 ->AEGP_GetLayerNumEffects(*layer.get(), &numEffects));
    return numEffects;
}

EffectRefPtr
EffectSuite4::getLayerEffectByIndex(LayerPtr layer,
                                    AEGP_EffectIndex layer_effect_index)
{
    CheckNotNull(layer.get(),
                 "Error Getting Layer Effect by Index. Layer is Null");
    AEGP_EffectRefH effectH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .EffectSuite4()
                 ->AEGP_GetLayerEffectByIndex(*m_suiteManager.GetPluginID(),
                                              *layer.get(), layer_effect_index,
                                              &effectH));
    return EffectSuite4::createPtr(effectH);
}

AEGP_InstalledEffectKey
EffectSuite4::getInstalledKeyFromLayerEffect(EffectRefPtr effect_ref)
{
    CheckNotNull(
        effect_ref.get(),
        "Error Getting Installed Key from Layer Effect. Effect is Null");
    AEGP_InstalledEffectKey key;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .EffectSuite4()
            ->AEGP_GetInstalledKeyFromLayerEffect(*effect_ref.get(), &key));
    return key;
}

std::tuple<PF_ParamType, PF_ParamDefUnion>
EffectSuite4::getEffectParamUnionByIndex(EffectRefPtr effect_ref,
                                         PF_ParamIndex param_index)
{
    CheckNotNull(effect_ref.get(),
                 "Error Getting Effect Param Union by Index. Effect is Null");
    PF_ParamType type;
    PF_ParamDefUnion def;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .EffectSuite4()
                 ->AEGP_GetEffectParamUnionByIndex(
                     *m_suiteManager.GetPluginID(), *effect_ref.get(),
                     param_index, &type, &def));
    return std::make_tuple(type, def);
}

AE_EffectFlags EffectSuite4::getEffectFlags(EffectRefPtr effect_ref)
{
    CheckNotNull(effect_ref.get(),
                 "Error Getting Effect Flags. Effect is Null");
    AEGP_EffectFlags flags;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_GetEffectFlags(
            *effect_ref.get(), &flags));
    return AE_EffectFlags(flags);
}

void EffectSuite4::setEffectFlags(EffectRefPtr effect_ref,
                                  AE_EffectFlags effect_flags_set_mask,
                                  AE_EffectFlags effect_flags)
{
    CheckNotNull(effect_ref.get(),
                 "Error Setting Effect Flags. Effect is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_SetEffectFlags(
            *effect_ref.get(), AEGP_EffectFlags(effect_flags_set_mask),
            AEGP_EffectFlags(effect_flags)));
}

void EffectSuite4::reorderEffect(EffectRefPtr effect_ref, A_long effect_index)
{
    CheckNotNull(effect_ref.get(), "Error Reordering Effect. Effect is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_ReorderEffect(
            *effect_ref.get(), effect_index));
}

void EffectSuite4::effectCallGeneric(EffectRefPtr effect_ref,
                                     const A_Time *timePT, PF_Cmd effect_cmd,
                                     void *effect_extraPV)
{
    CheckNotNull(effect_ref.get(), "Error Effect Call Generic. Effect is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_EffectCallGeneric(
            *m_suiteManager.GetPluginID(), *effect_ref.get(), timePT,
            effect_cmd, effect_extraPV));
}

void EffectSuite4::disposeEffect(EffectRefPtr effect_ref)
{
    CheckNotNull(effect_ref.get(), "Error Disposing Effect. Effect is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_DisposeEffect(
            *effect_ref.get()));
}

EffectRefPtr
EffectSuite4::applyEffect(LayerPtr layer,
                          AEGP_InstalledEffectKey installed_effect_key)
{
    CheckNotNull(layer.get(), "Error Applying Effect. Layer is Null");
    AEGP_EffectRefH effectH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_ApplyEffect(
        *m_suiteManager.GetPluginID(), *layer.get(), installed_effect_key,
        &effectH));
    return EffectSuite4::createPtr(effectH);
}

void EffectSuite4::deleteLayerEffect(EffectRefPtr effect_ref)
{
    CheckNotNull(effect_ref.get(),
                 "Error Deleting Layer Effect. Effect is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_DeleteLayerEffect(
            *effect_ref.get()));
}

A_long EffectSuite4::getNumInstalledEffects()
{
    A_long numEffects;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .EffectSuite4()
                 ->AEGP_GetNumInstalledEffects(&numEffects));
    return numEffects;
}

AEGP_InstalledEffectKey EffectSuite4::getNextInstalledEffect(
    AEGP_InstalledEffectKey installed_effect_key)
{
    AEGP_InstalledEffectKey nextKey;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .EffectSuite4()
                 ->AEGP_GetNextInstalledEffect(installed_effect_key, &nextKey));
    return nextKey;
}

std::string
EffectSuite4::getEffectName(AEGP_InstalledEffectKey installed_effect_key)
{
    A_char *nameP = nullptr;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_GetEffectName(
            installed_effect_key, nameP));
    return std::string(nameP);
}

std::string
EffectSuite4::getEffectMatchName(AEGP_InstalledEffectKey installed_effect_key)
{
    A_char *matchNameP = nullptr;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .EffectSuite4()
                 ->AEGP_GetEffectMatchName(installed_effect_key, matchNameP));
    return std::string(matchNameP);
}

std::string
EffectSuite4::getEffectCategory(AEGP_InstalledEffectKey installed_effect_key)
{
    A_char *categoryP = nullptr;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_GetEffectCategory(
            installed_effect_key, categoryP));
    return std::string(categoryP);
}

EffectRefPtr EffectSuite4::duplicateEffect(EffectRefPtr original_effect_ref)
{
    CheckNotNull(original_effect_ref.get(),
                 "Error Duplicating Effect. Original Effect is Null");
    AEGP_EffectRefH newEffectH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_DuplicateEffect(
            *original_effect_ref.get(), &newEffectH));
    return EffectSuite4::createPtr(newEffectH);
}

A_u_long EffectSuite4::numEffectMask(EffectRefPtr effect_ref)
{
    CheckNotNull(effect_ref.get(),
                 "Error Getting Number of Effect Masks. Effect is Null");
    A_u_long numMasks;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_NumEffectMask(
            *effect_ref.get(), &numMasks));
    return numMasks;
}

AEGP_MaskIDVal EffectSuite4::getEffectMaskID(EffectRefPtr effect_ref,
                                             A_u_long mask_indexL)
{
    CheckNotNull(effect_ref.get(),
                 "Error Getting Effect Mask ID. Effect is Null");
    AEGP_MaskIDVal id;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_GetEffectMaskID(
            *effect_ref.get(), mask_indexL, &id));
    return id;
}

StreamRefPtr EffectSuite4::addEffectMask(EffectRefPtr effect_ref,
                                         AEGP_MaskIDVal id_val)
{
    CheckNotNull(effect_ref.get(), "Error Adding Effect Mask. Effect is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_AddEffectMask(
            *effect_ref.get(), id_val, &streamH));
    return StreamSuite6::createPtr(streamH);
}

void EffectSuite4::removeEffectMask(EffectRefPtr effect_ref,
                                    AEGP_MaskIDVal id_val)
{
    CheckNotNull(effect_ref.get(),
                 "Error Removing Effect Mask. Effect is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_RemoveEffectMask(
            *effect_ref.get(), id_val));
}

StreamRefPtr EffectSuite4::setEffectMask(EffectRefPtr effect_ref,
                                         A_u_long mask_indexL,
                                         AEGP_MaskIDVal id_val)
{
    CheckNotNull(effect_ref.get(), "Error Setting Effect Mask. Effect is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().EffectSuite4()->AEGP_SetEffectMask(
            *effect_ref.get(), mask_indexL, id_val, &streamH));
    return StreamSuite6::createPtr(streamH);
}

A_long MaskSuite6::getLayerNumMasks(LayerPtr aegp_layerH)
{
    CheckNotNull(aegp_layerH.get(),
                 "Error Getting Layer Number of Masks. Layer is Null");
    A_long numMasks;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_GetLayerNumMasks(
            *aegp_layerH.get(), &numMasks));
    return numMasks;
}

MaskRefPtr MaskSuite6::getLayerMaskByIndex(LayerPtr aegp_layerH,
                                           AEGP_MaskIndex mask_indexL)
{
    CheckNotNull(aegp_layerH.get(),
                 "Error Getting Layer Mask by Index. Layer is Null");
    AEGP_MaskRefH maskH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_GetLayerMaskByIndex(
            *aegp_layerH.get(), mask_indexL, &maskH));
    return MaskSuite6::createPtr(maskH);
}

void MaskSuite6::disposeMask(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(), "Error Disposing Mask. Mask is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_DisposeMask(
        *mask_refH.get()));
}

bool MaskSuite6::getMaskInvert(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(), "Error Getting Mask Invert. Mask is Null");
    A_Boolean invertB;
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_GetMaskInvert(
        *mask_refH.get(), &invertB));
    return static_cast<bool>(invertB);
}

void MaskSuite6::setMaskInvert(MaskRefPtr mask_refH, bool invertB)
{
    CheckNotNull(mask_refH.get(), "Error Setting Mask Invert. Mask is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_SetMaskInvert(
        *mask_refH.get(), invertB));
}

AE_MaskMode MaskSuite6::getMaskMode(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(), "Error Getting Mask Mode. Mask is Null");
    PF_MaskMode mode;
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_GetMaskMode(
        *mask_refH.get(), &mode));
    return AE_MaskMode(mode);
}

void MaskSuite6::setMaskMode(MaskRefPtr maskH, AE_MaskMode mode)
{
    CheckNotNull(maskH.get(), "Error Setting Mask Mode. Mask is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_SetMaskMode(
        *maskH.get(), PF_MaskMode(mode)));
}

AE_MaskMBlur MaskSuite6::getMaskMotionBlurState(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(),
                 "Error Getting Mask Motion Blur State. Mask is Null");
    AEGP_MaskMBlur blur_state;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskSuite6()
                 ->AEGP_GetMaskMotionBlurState(*mask_refH.get(), &blur_state));
    return AE_MaskMBlur(blur_state);
}

void MaskSuite6::setMaskMotionBlurState(MaskRefPtr mask_refH,
                                        AE_MaskMBlur blur_state)
{
    CheckNotNull(mask_refH.get(),
                 "Error Setting Mask Motion Blur State. Mask is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskSuite6()
                 ->AEGP_SetMaskMotionBlurState(*mask_refH.get(),
                                               AEGP_MaskMBlur(blur_state)));
}

AE_MaskFeatherFalloff MaskSuite6::getMaskFeatherFalloff(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(),
                 "Error Getting Mask Feather Falloff. Mask is Null");
    AEGP_MaskFeatherFalloff feather_falloff;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .MaskSuite6()
            ->AEGP_GetMaskFeatherFalloff(*mask_refH.get(), &feather_falloff));
    return AE_MaskFeatherFalloff(feather_falloff);
}

void MaskSuite6::setMaskFeatherFalloff(MaskRefPtr mask_refH,
                                       AE_MaskFeatherFalloff feather_falloffP)
{
    CheckNotNull(mask_refH.get(),
                 "Error Setting Mask Feather Falloff. Mask is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .MaskSuite6()
            ->AEGP_SetMaskFeatherFalloff(
                *mask_refH.get(), AEGP_MaskFeatherFalloff(feather_falloffP)));
}

AEGP_MaskIDVal MaskSuite6::getMaskID(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(), "Error Getting Mask ID. Mask is Null");
    AEGP_MaskIDVal id;
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_GetMaskID(
        *mask_refH.get(), &id));
    return id;
}

MaskRefPtr MaskSuite6::createNewMask(LayerPtr layerH, A_long mask_indexPL0)
{
    CheckNotNull(layerH.get(), "Error Creating New Mask. Layer is Null");
    AEGP_MaskRefH maskH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_CreateNewMask(
        *layerH.get(), &maskH, &mask_indexPL0));
    return MaskSuite6::createPtr(maskH);
}

void MaskSuite6::deleteMaskFromLayer(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(),
                 "Error Deleting Mask from Layer. Mask is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_DeleteMaskFromLayer(
            *mask_refH.get()));
}

ColorVal MaskSuite6::getMaskColor(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(), "Error Getting Mask Color. Mask is Null");
    AEGP_ColorVal color;
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_GetMaskColor(
        *mask_refH.get(), &color));
    return toColorVal(color);
}

void MaskSuite6::setMaskColor(MaskRefPtr mask_refH, ColorVal colorP)
{
    CheckNotNull(mask_refH.get(), "Error Setting Mask Color. Mask is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_SetMaskColor(
        *mask_refH.get(), &toAEGP_ColorVal(colorP)));
}

bool MaskSuite6::getMaskLockState(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(),
                 "Error Getting Mask Lock State. Mask is Null");
    A_Boolean lockB;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_GetMaskLockState(
            *mask_refH.get(), &lockB));
    return static_cast<bool>(lockB);
}

void MaskSuite6::setMaskLockState(MaskRefPtr mask_refH, bool lockB)
{
    CheckNotNull(mask_refH.get(),
                 "Error Setting Mask Lock State. Mask is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_SetMaskLockState(
            *mask_refH.get(), lockB));
}

bool MaskSuite6::getMaskIsRotoBezier(MaskRefPtr mask_refH)
{
    CheckNotNull(mask_refH.get(),
                 "Error Getting Mask Is Roto Bezier. Mask is Null");
    A_Boolean is_roto_bezierB;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_GetMaskIsRotoBezier(
            *mask_refH.get(), &is_roto_bezierB));
    return static_cast<bool>(is_roto_bezierB);
}

void MaskSuite6::setMaskIsRotoBezier(MaskRefPtr mask_refH, bool is_roto_bezierB)
{
    CheckNotNull(mask_refH.get(),
                 "Error Setting Mask Is Roto Bezier. Mask is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_SetMaskIsRotoBezier(
            *mask_refH.get(), is_roto_bezierB));
}

MaskRefPtr MaskSuite6::duplicateMask(MaskRefPtr orig_mask_refH)
{
    CheckNotNull(orig_mask_refH.get(),
                 "Error Duplicating Mask. Original Mask is Null");
    AEGP_MaskRefH new_maskH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().MaskSuite6()->AEGP_DuplicateMask(
        *orig_mask_refH.get(), &new_maskH));
    return MaskSuite6::createPtr(new_maskH);
}

bool MaskOutlineSuite3::isMaskOutlineOpen(MaskOutlineValPtr mask_outlineH)
{
    CheckNotNull(
        mask_outlineH.get(),
        "Error Checking if Mask Outline is Open. Mask Outline is Null");
    A_Boolean openB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_IsMaskOutlineOpen(*mask_outlineH.get(), &openB));
    return static_cast<bool>(openB);
}

void MaskOutlineSuite3::setMaskOutlineOpen(MaskOutlineValPtr mask_outlineH,
                                           bool openB)
{
    CheckNotNull(mask_outlineH.get(),
                 "Error Setting Mask Outline Open. Mask Outline is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_SetMaskOutlineOpen(*mask_outlineH.get(), openB));
}

A_long
MaskOutlineSuite3::getMaskOutlineNumSegments(MaskOutlineValPtr mask_outlineH)
{
    CheckNotNull(
        mask_outlineH.get(),
        "Error Getting Mask Outline Number of Segments. Mask Outline is Null");
    A_long numSegmentsL;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_GetMaskOutlineNumSegments(*mask_outlineH.get(),
                                                  &numSegmentsL));
    return numSegmentsL;
}

AEGP_MaskVertex
MaskOutlineSuite3::getMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH,
                                            AEGP_VertexIndex which_pointL)
{
    AEGP_MaskVertex vertex;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_GetMaskOutlineVertexInfo(*mask_outlineH.get(),
                                                 which_pointL, &vertex));
    return vertex;
}

void MaskOutlineSuite3::setMaskOutlineVertexInfo(
    MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_pointL,
    const AEGP_MaskVertex &vertexP)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_SetMaskOutlineVertexInfo(*mask_outlineH.get(),
                                                 which_pointL, &vertexP));
}

void MaskOutlineSuite3::createVertex(MaskOutlineValPtr mask_outlineH,
                                     AEGP_VertexIndex insert_position)
{
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MaskOutlineSuite3()->AEGP_CreateVertex(
            *mask_outlineH.get(), insert_position));
}

void MaskOutlineSuite3::deleteVertex(MaskOutlineValPtr mask_outlineH,
                                     AEGP_VertexIndex index)
{
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().MaskOutlineSuite3()->AEGP_DeleteVertex(
            *mask_outlineH.get(), index));
}

A_long
MaskOutlineSuite3::getMaskOutlineNumFeathers(MaskOutlineValPtr mask_outlineH)
{
    A_long numFeathersL;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_GetMaskOutlineNumFeathers(*mask_outlineH.get(),
                                                  &numFeathersL));
    return numFeathersL;
}

AEGP_MaskFeather
MaskOutlineSuite3::getMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH,
                                             AEGP_FeatherIndex which_featherL)
{
    AEGP_MaskFeather feather;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_GetMaskOutlineFeatherInfo(*mask_outlineH.get(),
                                                  which_featherL, &feather));
    return feather;
}

void MaskOutlineSuite3::setMaskOutlineFeatherInfo(
    MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_featherL,
    const AEGP_MaskFeather &featherP)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_SetMaskOutlineFeatherInfo(*mask_outlineH.get(),
                                                  which_featherL, &featherP));
}

AEGP_FeatherIndex
MaskOutlineSuite3::createMaskOutlineFeather(MaskOutlineValPtr mask_outlineH,
                                            const AEGP_MaskFeather &featherP0)
{
    AEGP_FeatherIndex index;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_CreateMaskOutlineFeather(*mask_outlineH.get(),
                                                 &featherP0, &index));
    return index;
}

void MaskOutlineSuite3::deleteMaskOutlineFeather(
    MaskOutlineValPtr mask_outlineH, AEGP_FeatherIndex index)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .MaskOutlineSuite3()
                 ->AEGP_DeleteMaskOutlineFeather(*mask_outlineH.get(), index));
}

// FootageSuite5

FootagePtr FootageSuite5::getMainFootageFromItem(ItemPtr itemH)
{
    CheckNotNull(itemH.get(),
                 "Error Getting Main Footage from Item. Item is Null");
    AEGP_FootageH footageH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_GetMainFootageFromItem(*itemH.get(), &footageH));
    return FootageSuite5::createPtr(footageH);
}

FootagePtr FootageSuite5::getProxyFootageFromItem(ItemPtr itemH)
{
    CheckNotNull(itemH.get(),
                 "Error Getting Proxy Footage from Item. Item is Null");
    AEGP_FootageH footageH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_GetProxyFootageFromItem(*itemH.get(), &footageH));
    return FootageSuite5::createPtr(footageH);
}

std::tuple<A_long, A_long>
FootageSuite5::getFootageNumFiles(FootagePtr footageH)
{
    CheckNotNull(footageH.get(),
                 "Error Getting Footage Number of Files. Footage is Null");
    A_long num_filesL;
    A_long num_framesL;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_GetFootageNumFiles(*footageH.get(), &num_filesL,
                                           &num_framesL));
    return std::make_tuple(num_filesL, num_framesL);
}

std::string FootageSuite5::getFootagePath(FootagePtr footageH,
                                          A_long frame_numL, A_long file_indexL)
{
    CheckNotNull(footageH.get(), "Error Getting Footage Path. Footage is Null");
    AEGP_MemHandle pathH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().FootageSuite5()->AEGP_GetFootagePath(
            *footageH.get(), frame_numL, file_indexL, &pathH));
    return memHandleToString(pathH);
}

AEGP_FootageSignature FootageSuite5::getFootageSignature(FootagePtr footageH)
{
    CheckNotNull(footageH.get(),
                 "Error Getting Footage Signature. Footage is Null");
    AEGP_FootageSignature signature;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_GetFootageSignature(*footageH.get(), &signature));
    return signature;
}

/**
 * .
 *
 * \param pathZ
 * \param layer_infoP0
 * \param sequence_optionsP0
 * \param interp_style
 * \return
 */
FootagePtr FootageSuite5::newFootage(

    std::string pathZ, AEGP_FootageLayerKey layer_infoP0,
    AEGP_FileSequenceImportOptions *sequence_optionsP0,
    AE_InterpretationStyle interp_style)
{
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(pathZ);
    AEGP_FootageH footageH;
    if (sequence_optionsP0 == NULL)
    {
        AE_CHECK(
            m_suiteManager.GetSuiteHandler().FootageSuite5()->AEGP_NewFootage(
                *m_suiteManager.GetPluginID(), path16.data(), &layer_infoP0,
                NULL, AEGP_InterpretationStyle(interp_style), NULL, &footageH));
    }
    else
    {
        AE_CHECK(
            m_suiteManager.GetSuiteHandler().FootageSuite5()->AEGP_NewFootage(
                *m_suiteManager.GetPluginID(), path16.data(), &layer_infoP0,
                sequence_optionsP0, AEGP_InterpretationStyle(interp_style),
                NULL, &footageH));
    }
    return FootageSuite5::createPtr(footageH);
}

ItemPtr FootageSuite5::addFootageToProject(FootagePtr footageH, ItemPtr folderH)
{
    CheckNotNull(footageH.get(),
                 "Error Adding Footage to Project. Footage is Null");
    if (!folderH)
    {
        folderH = ProjSuite6().GetProjectRootFolder(
            ProjSuite6().GetProjectByIndex(0));
    }
    FootagePtr footageH2 = std::make_shared<AEGP_FootageH>(*footageH.get());
    AEGP_ItemH itemH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_AddFootageToProject(*footageH2.get(), *folderH.get(),
                                            &itemH));
    return std::make_shared<AEGP_ItemH>(itemH);
}

void FootageSuite5::setItemProxyFootage(FootagePtr footageH, ItemPtr itemH)
{
    CheckNotNull(footageH.get(),
                 "Error Setting Item Proxy Footage. Footage is Null");
    CheckNotNull(itemH.get(), "Error Setting Item Proxy Footage. Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_SetItemProxyFootage(*footageH.get(), *itemH.get()));
}

void FootageSuite5::replaceItemMainFootage(FootagePtr footageH, ItemPtr itemH)
{
    CheckNotNull(footageH.get(),
                 "Error Replacing Item Main Footage. Footage is Null");
    CheckNotNull(itemH.get(),
                 "Error Replacing Item Main Footage. Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_ReplaceItemMainFootage(*footageH.get(), *itemH.get()));
}

void FootageSuite5::disposeFootage(FootagePtr footageH)
{
    CheckNotNull(footageH.get(), "Error Disposing Footage. Footage is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().FootageSuite5()->AEGP_DisposeFootage(
            *footageH.get()));
}

AEGP_FootageInterp FootageSuite5::getFootageInterpretation(ItemPtr itemH,
                                                           bool proxyB)
{
    CheckNotNull(itemH.get(),
                 "Error Getting Footage Interpretation. Item is Null");
    AEGP_FootageInterp interp;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .FootageSuite5()
            ->AEGP_GetFootageInterpretation(*itemH.get(), proxyB, &interp));
    return interp;
}

void FootageSuite5::setFootageInterpretation(ItemPtr itemH, bool proxyB,
                                             const AEGP_FootageInterp *interpP)
{
    CheckNotNull(itemH.get(),
                 "Error Setting Footage Interpretation. Item is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .FootageSuite5()
            ->AEGP_SetFootageInterpretation(*itemH.get(), proxyB, interpP));
}

AEGP_FootageLayerKey FootageSuite5::getFootageLayerKey(FootagePtr footageH)
{
    CheckNotNull(footageH.get(),
                 "Error Getting Footage Layer Key. Footage is Null");
    AEGP_FootageLayerKey layer_key;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_GetFootageLayerKey(*footageH.get(), &layer_key));
    return layer_key;
}

FootagePtr FootageSuite5::newPlaceholderFootage(std::string nameZ, A_long width,
                                                A_long height,
                                                A_Time durationPT)
{
    AEGP_FootageH footageH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_NewPlaceholderFootage(*m_suiteManager.GetPluginID(),
                                              nameZ.c_str(), width, height,
                                              &durationPT, &footageH));
    return FootageSuite5::createPtr(footageH);
}

FootagePtr FootageSuite5::newPlaceholderFootageWithPath(
    std::string pathZ, AE_Platform path_platform, AEIO_FileType file_type,
    A_long widthL, A_long heightL, A_Time durationPT)
{
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(pathZ);
    AEGP_FootageH footageH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_NewPlaceholderFootageWithPath(
                     *m_suiteManager.GetPluginID(), path16.data(),
                     AEGP_Platform(path_platform), file_type, widthL, heightL,
                     &durationPT, &footageH));
    return FootageSuite5::createPtr(footageH);
}

FootagePtr FootageSuite5::newSolidFootage(std::string nameZ, A_long width,
                                          A_long height, ColorVal colorP)
{
    AEGP_FootageH footageH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().FootageSuite5()->AEGP_NewSolidFootage(
            nameZ.c_str(), width, height, &toAEGP_ColorVal(colorP), &footageH));
    return FootageSuite5::createPtr(footageH);
}

ColorVal FootageSuite5::getSolidFootageColor(ItemPtr itemH, bool proxyB)
{
    CheckNotNull(itemH.get(),
                 "Error Getting Solid Footage Color. Item is Null");
    AEGP_ColorVal color;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_GetSolidFootageColor(*itemH.get(), proxyB, &color));
    return toColorVal(color);
}

void FootageSuite5::setSolidFootageColor(ItemPtr itemH, bool proxyB,
                                         ColorVal colorP)
{
    CheckNotNull(itemH.get(),
                 "Error Setting Solid Footage Color. Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_SetSolidFootageColor(*itemH.get(), proxyB,
                                             &toAEGP_ColorVal(colorP)));
}

void FootageSuite5::setSolidFootageDimensions(ItemPtr itemH, bool proxyB,
                                              A_long widthL, A_long heightL)
{
    CheckNotNull(itemH.get(),
                 "Error Setting Solid Footage Dimensions. Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_SetSolidFootageDimensions(*itemH.get(), proxyB, widthL,
                                                  heightL));
}

AEGP_SoundDataFormat
FootageSuite5::getFootageSoundDataFormat(FootagePtr footageH)
{
    CheckNotNull(footageH.get(),
                 "Error Getting Footage Sound Data Format. Footage is Null");
    AEGP_SoundDataFormat format;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .FootageSuite5()
                 ->AEGP_GetFootageSoundDataFormat(*footageH.get(), &format));
    return format;
}

AEGP_FileSequenceImportOptions
FootageSuite5::getFootageSequenceImportOptions(FootagePtr footageH)
{
    CheckNotNull(
        footageH.get(),
        "Error Getting Footage Sequence Import Options. Footage is Null");
    AEGP_FileSequenceImportOptions options;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .FootageSuite5()
            ->AEGP_GetFootageSequenceImportOptions(*footageH.get(), &options));
    return options;
}

void UtilitySuite6::reportInfo(const std::string &info_string)
{
    int id = *m_suiteManager.GetPluginID();
    AE_CHECK(m_suiteManager.GetSuiteHandler().UtilitySuite5()->AEGP_ReportInfo(
        id, info_string.c_str()));
}

void UtilitySuite6::reportInfoUnicode(const std::string &info_string)
{
    std::vector<A_UTF16Char> info16 = ConvertUTF8ToUTF16(info_string);
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_ReportInfoUnicode(*m_suiteManager.GetPluginID(),
                                          info16.data()));
}

std::tuple<A_short, A_short> UtilitySuite6::getDriverPluginInitFuncVersion()
{
    A_short major;
    A_short minor;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_GetDriverPluginInitFuncVersion(&major, &minor));
    return std::make_tuple(major, minor);
}

std::tuple<A_short, A_short> UtilitySuite6::getDriverImplementationVersion()
{
    A_short major;
    A_short minor;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_GetDriverImplementationVersion(&major, &minor));
    return std::make_tuple(major, minor);
}

void UtilitySuite6::startQuietErrors()
{
    AEGP_ErrReportState *err_stateP = nullptr;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().UtilitySuite6()->AEGP_StartQuietErrors(
            err_stateP));
}

void UtilitySuite6::endQuietErrors(bool report_quieted_errorsB)
{
    AEGP_ErrReportState *err_stateP = nullptr;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().UtilitySuite6()->AEGP_EndQuietErrors(
            report_quieted_errorsB, err_stateP));
}

std::string UtilitySuite6::getLastErrorMessage(A_long buffer_size)
{
    A_char *bufferP = nullptr;
    A_Err error = A_Err_NONE;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_GetLastErrorMessage(buffer_size, bufferP, &error));
    return std::string(bufferP);
}

void UtilitySuite6::startUndoGroup(const std::string &undo_name)
{
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().UtilitySuite6()->AEGP_StartUndoGroup(
            undo_name.c_str()));
}

void UtilitySuite6::endUndoGroup()
{
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().UtilitySuite6()->AEGP_EndUndoGroup());
}

void *UtilitySuite6::getMainHWND()
{
    void *hwnd;
    AE_CHECK(m_suiteManager.GetSuiteHandler().UtilitySuite6()->AEGP_GetMainHWND(
        &hwnd));
    return hwnd;
}

void UtilitySuite6::showHideAllFloaters(bool include_tool_palB)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_ShowHideAllFloaters(include_tool_palB));
}

ColorVal UtilitySuite6::getPaintPalForeColor()
{
    AEGP_ColorVal color;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_PaintPalGetForeColor(&color));
    return toColorVal(color);
}

ColorVal UtilitySuite6::getPaintPalBackColor()
{
    AEGP_ColorVal color;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_PaintPalGetBackColor(&color));
    return toColorVal(color);
}

void UtilitySuite6::setPaintPalForeColor(const ColorVal &fore_color)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_PaintPalSetForeColor(&toAEGP_ColorVal(fore_color)));
}

void UtilitySuite6::setPaintPalBackColor(const ColorVal &back_color)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_PaintPalSetBackColor(&toAEGP_ColorVal(back_color)));
}

std::tuple<bool, ColorVal> UtilitySuite6::getCharPalFillColor()
{
    AEGP_ColorVal color;
    A_Boolean is_frontmostB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_CharPalGetFillColor(&is_frontmostB, &color));
    return std::make_tuple(static_cast<bool>(is_frontmostB), toColorVal(color));
}

std::tuple<bool, ColorVal> UtilitySuite6::getCharPalStrokeColor()
{
    AEGP_ColorVal color;
    A_Boolean is_frontmostB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_CharPalGetStrokeColor(&is_frontmostB, &color));
    return std::make_tuple(static_cast<bool>(is_frontmostB), toColorVal(color));
}

void UtilitySuite6::setCharPalFillColor(const ColorVal &fill_color)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_CharPalSetFillColor(&toAEGP_ColorVal(fill_color)));
}

void UtilitySuite6::setCharPalStrokeColor(const ColorVal &stroke_color)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_CharPalSetStrokeColor(&toAEGP_ColorVal(stroke_color)));
}

bool UtilitySuite6::charPalIsFillColorUIFrontmost()
{
    A_Boolean is_frontmostB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_CharPalIsFillColorUIFrontmost(&is_frontmostB));
    return static_cast<bool>(is_frontmostB);
}

A_Ratio UtilitySuite6::convertFpLongToHSFRatio(A_FpLong numberF)
{
    A_Ratio ratio;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_ConvertFpLongToHSFRatio(numberF, &ratio));
    return ratio;
}

A_FpLong UtilitySuite6::convertHSFRatioToFpLong(A_Ratio ratioR)
{
    A_FpLong number;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_ConvertHSFRatioToFpLong(ratioR, &number));
    return number;
}

void UtilitySuite6::causeIdleRoutinesToBeCalled()
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_CauseIdleRoutinesToBeCalled());
}

bool UtilitySuite6::getSuppressInteractiveUI()
{
    A_Boolean suppressB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .UtilitySuite6()
                 ->AEGP_GetSuppressInteractiveUI(&suppressB));
    return static_cast<bool>(suppressB);
}

void UtilitySuite6::writeToOSConsole(const std::string &text)
{
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().UtilitySuite6()->AEGP_WriteToOSConsole(
            text.c_str()));
}

void UtilitySuite6::writeToDebugLog(const std::string &subsystem,
                                    const std::string &eventType,
                                    const std::string &text)
{
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().UtilitySuite6()->AEGP_WriteToDebugLog(
            subsystem.c_str(), eventType.c_str(), text.c_str()));
}

std::string UtilitySuite6::getPluginPath(AE_PluginPathType path_type)
{
    AEGP_MemHandle pathH;
    std::string path = "";
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().UtilitySuite6()->AEGP_GetPluginPaths(
            *m_suiteManager.GetPluginID(), AEGP_GetPathTypes(path_type),
            &pathH));
    path = memHandleToString(pathH);
    return path;
}

A_long RenderQueueItemSuite4::getNumRQItems()
{
    A_long numItemsL;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_GetNumRQItems(
            &numItemsL));
    return numItemsL;
}

RQItemRefPtr RenderQueueItemSuite4::getRQItemByIndex(A_long rq_item_index)
{
    AEGP_RQItemRefH rq_itemH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_GetRQItemByIndex(
            rq_item_index, &rq_itemH));
    return std::make_shared<AEGP_RQItemRefH>(rq_itemH);
}

RQItemRefPtr RenderQueueItemSuite4::getNextRQItem(RQItemRefPtr current_rq_item)
{
    CheckNotNull(current_rq_item.get(),
                 "Error Getting Next RQ Item. Current RQ Item is Null");
    AEGP_RQItemRefH next_rq_itemH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_GetNextRQItem(
            *current_rq_item.get(), &next_rq_itemH));
    return std::make_shared<AEGP_RQItemRefH>(next_rq_itemH);
}

A_long RenderQueueItemSuite4::getNumOutputModulesForRQItem(RQItemRefPtr rq_item)
{
    CheckNotNull(
        rq_item.get(),
        "Error Getting Number of Output Modules for RQ Item. RQ Item is Null");
    A_long numModulesL;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .RQItemSuite3()
            ->AEGP_GetNumOutputModulesForRQItem(*rq_item.get(), &numModulesL));
    return numModulesL;
}

AE_RenderItemStatus RenderQueueItemSuite4::getRenderState(RQItemRefPtr rq_item)
{
    CheckNotNull(rq_item.get(), "Error Getting Render State. RQ Item is Null");
    AEGP_RenderItemStatusType status;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_GetRenderState(
            *rq_item.get(), &status));
    return AE_RenderItemStatus(status);
}

void RenderQueueItemSuite4::setRenderState(RQItemRefPtr rq_item,
                                           AE_RenderItemStatus status)
{
    CheckNotNull(rq_item.get(), "Error Setting Render State. RQ Item is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_SetRenderState(
            *rq_item.get(), AEGP_RenderItemStatusType(status)));
}

A_Time RenderQueueItemSuite4::getStartedTime(RQItemRefPtr rq_item)
{
    CheckNotNull(rq_item.get(), "Error Getting Started Time. RQ Item is Null");
    A_Time time;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_GetStartedTime(
            *rq_item.get(), &time));
    return time;
}

A_Time RenderQueueItemSuite4::getElapsedTime(RQItemRefPtr rq_item)
{
    CheckNotNull(rq_item.get(), "Error Getting Elapsed Time. RQ Item is Null");
    A_Time time;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_GetElapsedTime(
            *rq_item.get(), &time));
    return time;
}

AE_LogType RenderQueueItemSuite4::getLogType(RQItemRefPtr rq_item)
{
    CheckNotNull(rq_item.get(), "Error Getting Log Type. RQ Item is Null");
    AEGP_LogType logtype;
    AE_CHECK(m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_GetLogType(
        *rq_item.get(), &logtype));
    return AE_LogType(logtype);
}

void RenderQueueItemSuite4::setLogType(RQItemRefPtr rq_item, AE_LogType logtype)
{
    CheckNotNull(rq_item.get(), "Error Setting Log Type. RQ Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_SetLogType(
        *rq_item.get(), AEGP_LogType(logtype)));
}

void RenderQueueItemSuite4::removeOutputModule(RQItemRefPtr rq_item,
                                               OutputModuleRefPtr outmod)
{
    CheckNotNull(rq_item.get(),
                 "Error Removing Output Module. RQ Item is Null");
    CheckNotNull(outmod.get(),
                 "Error Removing Output Module. Output Module is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RQItemSuite3()
                 ->AEGP_RemoveOutputModule(*rq_item.get(), *outmod.get()));
}

std::string RenderQueueItemSuite4::getComment(RQItemRefPtr rq_item)
{
    CheckNotNull(rq_item.get(), "Error Getting Comment. RQ Item is Null");
    A_char *commentP = nullptr;
    AE_CHECK(m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_GetComment(
        *rq_item.get(), commentP));
    std::string comment(commentP);
    return comment;
}

void RenderQueueItemSuite4::setComment(RQItemRefPtr rq_item,
                                       const std::string &comment)
{
    CheckNotNull(rq_item.get(), "Error Setting Comment. RQ Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_SetComment(
        *rq_item.get(), comment.c_str()));
}

CompPtr RenderQueueItemSuite4::getCompFromRQItem(RQItemRefPtr rq_item)
{
    CheckNotNull(rq_item.get(),
                 "Error Getting Comp from RQ Item. RQ Item is Null");
    AEGP_CompH compH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_GetCompFromRQItem(
            *rq_item.get(), &compH));
    return std::make_shared<AEGP_CompH>(compH);
}

void RenderQueueItemSuite4::deleteRQItem(RQItemRefPtr rq_item)
{
    CheckNotNull(rq_item.get(), "Error Deleting RQ Item. RQ Item is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().RQItemSuite3()->AEGP_DeleteRQItem(
        *rq_item.get()));
}

OutputModuleRefPtr
OutputModuleSuite4::getOutputModuleByIndex(RQItemRefPtr rq_itemH,
                                           A_long outmod_indexL)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Getting Output Module by Index. RQ Item is Null");
    AEGP_OutputModuleRefH outmodH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_GetOutputModuleByIndex(*rq_itemH.get(), outmod_indexL,
                                               &outmodH));
    return std::make_shared<AEGP_OutputModuleRefH>(outmodH);
}

AE_EmbeddingType OutputModuleSuite4::getEmbedOptions(RQItemRefPtr rq_itemH,
                                                     OutputModuleRefPtr outmodH)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Getting Embed Options. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Getting Embed Options. Output Module is Null");
    AEGP_EmbeddingType embed_options;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_GetEmbedOptions(*rq_itemH.get(), *outmodH.get(),
                                        &embed_options));
    return AE_EmbeddingType(embed_options);
}

void OutputModuleSuite4::setEmbedOptions(RQItemRefPtr rq_itemH,
                                         OutputModuleRefPtr outmodH,
                                         AE_EmbeddingType embed_options)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Setting Embed Options. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Setting Embed Options. Output Module is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_SetEmbedOptions(*rq_itemH.get(), *outmodH.get(),
                                        AEGP_EmbeddingType(embed_options)));
}

AE_PostRenderAction
OutputModuleSuite4::getPostRenderAction(RQItemRefPtr rq_itemH,
                                        OutputModuleRefPtr outmodH)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Getting Post Render Action. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Getting Post Render Action. Output Module is Null");
    AEGP_PostRenderAction post_render_action;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_GetPostRenderAction(*rq_itemH.get(), *outmodH.get(),
                                            &post_render_action));
    return AE_PostRenderAction(post_render_action);
}

void OutputModuleSuite4::setPostRenderAction(
    RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
    AE_PostRenderAction post_render_action)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Setting Post Render Action. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Setting Post Render Action. Output Module is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_SetPostRenderAction(
                     *rq_itemH.get(), *outmodH.get(),
                     AEGP_PostRenderAction(post_render_action)));
}

AE_OutputTypes OutputModuleSuite4::getEnabledOutputs(RQItemRefPtr rq_itemH,
                                                     OutputModuleRefPtr outmodH)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Getting Enabled Outputs. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Getting Enabled Outputs. Output Module is Null");
    AEGP_OutputTypes enabled_types;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_GetEnabledOutputs(*rq_itemH.get(), *outmodH.get(),
                                          &enabled_types));
    return AE_OutputTypes(enabled_types);
}

void OutputModuleSuite4::setEnabledOutputs(RQItemRefPtr rq_itemH,
                                           OutputModuleRefPtr outmodH,
                                           AE_OutputTypes enabled_types)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Setting Enabled Outputs. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Setting Enabled Outputs. Output Module is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_SetEnabledOutputs(*rq_itemH.get(), *outmodH.get(),
                                          AEGP_OutputTypes(enabled_types)));
}

AE_VideoChannels
OutputModuleSuite4::getOutputChannels(RQItemRefPtr rq_itemH,
                                      OutputModuleRefPtr outmodH)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Getting Output Channels. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Getting Output Channels. Output Module is Null");
    AEGP_VideoChannels output_channels;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_GetOutputChannels(*rq_itemH.get(), *outmodH.get(),
                                          &output_channels));
    return AE_VideoChannels(output_channels);
}

void OutputModuleSuite4::setOutputChannels(RQItemRefPtr rq_itemH,
                                           OutputModuleRefPtr outmodH,
                                           AE_VideoChannels output_channels)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Setting Output Channels. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Setting Output Channels. Output Module is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_SetOutputChannels(*rq_itemH.get(), *outmodH.get(),
                                          AEGP_VideoChannels(output_channels)));
}

std::tuple<bool, AE_StretchQuality, bool>
OutputModuleSuite4::getStretchInfo(RQItemRefPtr rq_itemH,
                                   OutputModuleRefPtr outmodH)
{
    CheckNotNull(rq_itemH.get(), "Error Getting Stretch Info. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Getting Stretch Info. Output Module is Null");
    A_Boolean is_enabledB;
    AEGP_StretchQuality stretch_quality;
    A_Boolean is_onB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_GetStretchInfo(*rq_itemH.get(), *outmodH.get(),
                                       &is_enabledB, &stretch_quality,
                                       &is_onB));
    return std::make_tuple(static_cast<bool>(is_enabledB),
                           AE_StretchQuality(stretch_quality),
                           static_cast<bool>(is_onB));
}

void OutputModuleSuite4::setStretchInfo(RQItemRefPtr rq_itemH,
                                        OutputModuleRefPtr outmodH,
                                        bool is_enabledB,
                                        AE_StretchQuality stretch_quality)
{
    CheckNotNull(rq_itemH.get(), "Error Setting Stretch Info. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Setting Stretch Info. Output Module is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_SetStretchInfo(*rq_itemH.get(), *outmodH.get(),
                                       is_enabledB,
                                       AEGP_StretchQuality(stretch_quality)));
}

std::tuple<bool, A_Rect>
OutputModuleSuite4::getCropInfo(RQItemRefPtr rq_itemH,
                                OutputModuleRefPtr outmodH)
{
    CheckNotNull(rq_itemH.get(), "Error Getting Crop Info. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Getting Crop Info. Output Module is Null");
    A_Boolean is_enabledB;
    A_Rect crop_rect;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().OutputModuleSuite4()->AEGP_GetCropInfo(
            *rq_itemH.get(), *outmodH.get(), &is_enabledB, &crop_rect));
    return std::make_tuple(static_cast<bool>(is_enabledB), crop_rect);
}

void OutputModuleSuite4::setCropInfo(RQItemRefPtr rq_itemH,
                                     OutputModuleRefPtr outmodH, bool enableB,
                                     A_Rect crop_rect)
{
    CheckNotNull(rq_itemH.get(), "Error Setting Crop Info. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Setting Crop Info. Output Module is Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().OutputModuleSuite4()->AEGP_SetCropInfo(
            *rq_itemH.get(), *outmodH.get(), enableB, crop_rect));
}

std::tuple<AEGP_SoundDataFormat, bool>
OutputModuleSuite4::getSoundFormatInfo(RQItemRefPtr rq_itemH,
                                       OutputModuleRefPtr outmodH)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Getting Sound Format Info. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Getting Sound Format Info. Output Module is Null");
    AEGP_SoundDataFormat sound_format_info;
    A_Boolean audio_enabledB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_GetSoundFormatInfo(*rq_itemH.get(), *outmodH.get(),
                                           &sound_format_info,
                                           &audio_enabledB));
    return std::make_tuple(sound_format_info,
                           static_cast<bool>(audio_enabledB));
}

void OutputModuleSuite4::setSoundFormatInfo(
    RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
    AEGP_SoundDataFormat sound_format_info, bool audio_enabledB)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Setting Sound Format Info. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Setting Sound Format Info. Output Module is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_SetSoundFormatInfo(*rq_itemH.get(), *outmodH.get(),
                                           sound_format_info, audio_enabledB));
}

std::string OutputModuleSuite4::getOutputFilePath(RQItemRefPtr rq_itemH,
                                                  OutputModuleRefPtr outmodH)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Getting Output File Path. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Getting Output File Path. Output Module is Null");
    AEGP_MemHandle pathH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .OutputModuleSuite4()
            ->AEGP_GetOutputFilePath(*rq_itemH.get(), *outmodH.get(), &pathH));
    return memHandleToString(pathH);
}

void OutputModuleSuite4::setOutputFilePath(RQItemRefPtr rq_itemH,
                                           OutputModuleRefPtr outmodH,
                                           const std::string &path)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Setting Output File Path. RQ Item is Null");
    CheckNotNull(outmodH.get(),
                 "Error Setting Output File Path. Output Module is Null");
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_SetOutputFilePath(*rq_itemH.get(), *outmodH.get(),
                                          path16.data()));
}

OutputModuleRefPtr
OutputModuleSuite4::addDefaultOutputModule(RQItemRefPtr rq_itemH)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Adding Default Output Module. RQ Item is Null");
    AEGP_OutputModuleRefH outmodH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_AddDefaultOutputModule(*rq_itemH.get(), &outmodH));
    return std::make_shared<AEGP_OutputModuleRefH>(outmodH);
}

std::tuple<std::string, std::string, bool, bool>
OutputModuleSuite4::getExtraOutputModuleInfo(RQItemRefPtr rq_itemH,
                                             OutputModuleRefPtr outmodH)
{
    CheckNotNull(rq_itemH.get(),
                 "Error Getting Extra Output Module Info. RQ Item is Null");
    CheckNotNull(
        outmodH.get(),
        "Error Getting Extra Output Module Info. Output Module is Null");
    AEGP_MemHandle formatH;
    AEGP_MemHandle infoH;
    A_Boolean has_custom_optionsB;
    A_Boolean has_custom_render_templateB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .OutputModuleSuite4()
                 ->AEGP_GetExtraOutputModuleInfo(
                     *rq_itemH.get(), *outmodH.get(), &formatH, &infoH,
                     &has_custom_optionsB, &has_custom_render_templateB));
    std::string format = memHandleToString(formatH);
    std::string info = memHandleToString(infoH);
    return std::make_tuple(format, info, static_cast<bool>(has_custom_optionsB),
                           static_cast<bool>(has_custom_render_templateB));
}

WorldPtr WorldSuite3::newWorld(AE_WorldType type, A_long widthL, A_long heightL)
{
    AEGP_WorldH worldH;
    AE_CHECK(m_suiteManager.GetSuiteHandler().WorldSuite3()->AEGP_New(
        *m_suiteManager.GetPluginID(), AEGP_WorldType(type), widthL, heightL,
        &worldH));
    return WorldSuite3::createPtr(worldH);
}

AE_WorldType WorldSuite3::getType(WorldPtr worldH)
{
    CheckNotNull(worldH.get(), "Error Getting World Type. World is Null");
    AEGP_WorldType type;
    AE_CHECK(m_suiteManager.GetSuiteHandler().WorldSuite3()->AEGP_GetType(
        *worldH.get(), &type));
    return AE_WorldType(type);
}

std::tuple<A_long, A_long> WorldSuite3::getSize(WorldPtr worldH)
{
    CheckNotNull(worldH.get(), "Error Getting World Size. World is Null");
    A_long widthL;
    A_long heightL;
    AE_CHECK(m_suiteManager.GetSuiteHandler().WorldSuite3()->AEGP_GetSize(
        *worldH.get(), &widthL, &heightL));
    return std::make_tuple(widthL, heightL);
}

A_u_long WorldSuite3::getRowBytes(WorldPtr worldH)
{
    CheckNotNull(worldH.get(), "Error Getting Row Bytes. World is Null");
    A_u_long row_bytes;
    AE_CHECK(m_suiteManager.GetSuiteHandler().WorldSuite3()->AEGP_GetRowBytes(
        *worldH.get(), &row_bytes));
    return row_bytes;
}

PF_Pixel8 *WorldSuite3::getBaseAddr8(WorldPtr worldH)
{
    CheckNotNull(worldH.get(), "Error Getting Base Address 8. World is Null");
    PF_Pixel8 *base_addrP;
    AE_CHECK(m_suiteManager.GetSuiteHandler().WorldSuite3()->AEGP_GetBaseAddr8(
        *worldH.get(), &base_addrP));
    return base_addrP;
}

PF_Pixel16 *WorldSuite3::getBaseAddr16(WorldPtr worldH)
{
    CheckNotNull(worldH.get(), "Error Getting Base Address 16. World is Null");
    PF_Pixel16 *base_addrP;
    AE_CHECK(m_suiteManager.GetSuiteHandler().WorldSuite3()->AEGP_GetBaseAddr16(
        *worldH.get(), &base_addrP));
    return base_addrP;
}

PF_PixelFloat *WorldSuite3::getBaseAddr32(WorldPtr worldH)
{
    CheckNotNull(worldH.get(), "Error Getting Base Address 32. World is Null");
    PF_PixelFloat *base_addrP;
    AE_CHECK(m_suiteManager.GetSuiteHandler().WorldSuite3()->AEGP_GetBaseAddr32(
        *worldH.get(), &base_addrP));
    return base_addrP;
}

PF_EffectWorld WorldSuite3::fillOutPFEffectWorld(WorldPtr worldH)
{
    CheckNotNull(worldH.get(),
                 "Error Filling Out PF Effect World. World is Null");
    PF_EffectWorld effect_world;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .WorldSuite3()
                 ->AEGP_FillOutPFEffectWorld(*worldH.get(), &effect_world));
    return effect_world;
}

void WorldSuite3::fastBlur(A_FpLong radiusF, PF_ModeFlags mode,
                           PF_Quality quality, WorldPtr worldH)
{
    CheckNotNull(worldH.get(), "Error Fast Blurring World. World is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler().WorldSuite3()->AEGP_FastBlur(
        radiusF, mode, quality, *worldH.get()));
}

PlatformWorldPtr WorldSuite3::newPlatformWorld(AEGP_WorldType type,
                                               A_long widthL, A_long heightL)
{
    AEGP_PlatformWorldH worldH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().WorldSuite3()->AEGP_NewPlatformWorld(
            *m_suiteManager.GetPluginID(), AEGP_WorldType(type), widthL,
            heightL, &worldH));
    return WorldSuite3::createPlatformPtr(worldH);
}

WorldPtr
WorldSuite3::newReferenceFromPlatformWorld(PlatformWorldPtr platform_worldH)
{
    CheckNotNull(
        platform_worldH.get(),
        "Error Creating Reference from Platform World. Platform World is Null");
    AEGP_WorldH worldH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .WorldSuite3()
                 ->AEGP_NewReferenceFromPlatformWorld(
                     *m_suiteManager.GetPluginID(), *platform_worldH.get(),
                     &worldH));
    return WorldSuite3::createPtr(worldH);
}

RenderOptionsPtr RenderOptionsSuite4::newFromItem(ItemPtr itemH)
{
    CheckNotNull(itemH.get(),
                 "Error Creating Render Options from Item. Item is Null");
    AEGP_RenderOptionsH optionsH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_NewFromItem(*m_suiteManager.GetPluginID(), *itemH.get(),
                                    &optionsH));
    return RenderOptionsSuite4::createPtr(optionsH);
}

RenderOptionsPtr RenderOptionsSuite4::duplicate(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Duplicating Render Options. Options are Null");
    AEGP_RenderOptionsH new_optionsH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RenderOptionsSuite3()->AEGP_Duplicate(
            *m_suiteManager.GetPluginID(), *optionsH.get(), &new_optionsH));
    return RenderOptionsSuite4::createPtr(new_optionsH);
}

void RenderOptionsSuite4::setTime(RenderOptionsPtr optionsH, A_Time time)
{
    CheckNotNull(optionsH.get(), "Error Setting Time. Options are Null");
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetTime(
            *optionsH.get(), time));
}

A_Time RenderOptionsSuite4::getTime(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(), "Error Getting Time. Options are Null");
    A_Time time;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetTime(
            *optionsH.get(), &time));
    return time;
}

void RenderOptionsSuite4::setTimeStep(RenderOptionsPtr optionsH,
                                      A_Time time_step)
{
    CheckNotNull(optionsH.get(), "Error Setting Time Step. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_SetTimeStep(*optionsH.get(), time_step));
}

A_Time RenderOptionsSuite4::getTimeStep(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(), "Error Getting Time Step. Options are Null");
    A_Time time;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_GetTimeStep(*optionsH.get(), &time));
    return time;
}

void RenderOptionsSuite4::setFieldRender(RenderOptionsPtr optionsH,
                                         PF_Field field_render)
{
    CheckNotNull(optionsH.get(),
                 "Error Setting Field Render. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_SetFieldRender(*optionsH.get(), field_render));
}

PF_Field RenderOptionsSuite4::getFieldRender(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Getting Field Render. Options are Null");
    PF_Field field_render;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_GetFieldRender(*optionsH.get(), &field_render));
    return field_render;
}

void RenderOptionsSuite4::setWorldType(RenderOptionsPtr optionsH,
                                       AE_WorldType type)
{
    CheckNotNull(optionsH.get(), "Error Setting World Type. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_SetWorldType(*optionsH.get(), AEGP_WorldType(type)));
}

AE_WorldType RenderOptionsSuite4::getWorldType(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(), "Error Getting World Type. Options are Null");
    AEGP_WorldType type;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_GetWorldType(*optionsH.get(), &type));
    return AE_WorldType(type);
}

void RenderOptionsSuite4::setDownsampleFactor(RenderOptionsPtr optionsH,
                                              A_short x, A_short y)
{
    CheckNotNull(optionsH.get(),
                 "Error Setting Downsample Factor. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_SetDownsampleFactor(*optionsH.get(), x, y));
}

std::tuple<A_short, A_short>
RenderOptionsSuite4::getDownsampleFactor(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Getting Downsample Factor. Options are Null");
    A_short x;
    A_short y;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_GetDownsampleFactor(*optionsH.get(), &x, &y));
    return std::make_tuple(x, y);
}

void RenderOptionsSuite4::setRegionOfInterest(RenderOptionsPtr optionsH,
                                              const A_LRect *roiP)
{
    CheckNotNull(optionsH.get(),
                 "Error Setting Region of Interest. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_SetRegionOfInterest(*optionsH.get(), roiP));
}

A_LRect RenderOptionsSuite4::getRegionOfInterest(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Getting Region of Interest. Options are Null");
    A_LRect roi;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_GetRegionOfInterest(*optionsH.get(), &roi));
    return roi;
}

void RenderOptionsSuite4::setMatteMode(RenderOptionsPtr optionsH,
                                       AE_MatteMode mode)
{
    CheckNotNull(optionsH.get(), "Error Setting Matte Mode. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_SetMatteMode(*optionsH.get(), AEGP_MatteMode(mode)));
}

AE_MatteMode RenderOptionsSuite4::getMatteMode(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(), "Error Getting Matte Mode. Options are Null");
    AEGP_MatteMode mode;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_GetMatteMode(*optionsH.get(), &mode));
    return AE_MatteMode(mode);
}

void RenderOptionsSuite4::setChannelOrder(RenderOptionsPtr optionsH,
                                          AE_ChannelOrder channel_order)
{
    CheckNotNull(optionsH.get(),
                 "Error Setting Channel Order. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_SetChannelOrder(*optionsH.get(),
                                        AEGP_ChannelOrder(channel_order)));
}

AE_ChannelOrder RenderOptionsSuite4::getChannelOrder(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Getting Channel Order. Options are Null");
    AEGP_ChannelOrder channel_order;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_GetChannelOrder(*optionsH.get(), &channel_order));
    return AE_ChannelOrder(channel_order);
}

bool RenderOptionsSuite4::getRenderGuideLayers(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Getting Render Guide Layers. Options are Null");
    A_Boolean render_themB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_GetRenderGuideLayers(*optionsH.get(), &render_themB));
    return static_cast<bool>(render_themB);
}

void RenderOptionsSuite4::setRenderGuideLayers(RenderOptionsPtr optionsH,
                                               bool render_themB)
{
    CheckNotNull(optionsH.get(),
                 "Error Setting Render Guide Layers. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderOptionsSuite3()
                 ->AEGP_SetRenderGuideLayers(*optionsH.get(), render_themB));
}

LayerRenderOptionsPtr LayerRenderOptionsSuite2::newFromLayer(LayerPtr layer)
{
    CheckNotNull(
        layer.get(),
        "Error Creating Layer Render Options from Layer. Layer is Null");
    AEGP_LayerRenderOptionsH optionsH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_NewFromLayer(*m_suiteManager.GetPluginID(),
                                     *layer.get(), &optionsH));
    return LayerRenderOptionsSuite2::createPtr(optionsH);
}

LayerRenderOptionsPtr
LayerRenderOptionsSuite2::newFromUpstreamOfEffect(EffectRefPtr effect_ref)
{
    CheckNotNull(
        effect_ref.get(),
        "Error Creating Layer Render Options from Upstream of Effect. Effect "
        "is Null");
    AEGP_LayerRenderOptionsH optionsH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_NewFromUpstreamOfEffect(*m_suiteManager.GetPluginID(),
                                                *effect_ref.get(), &optionsH));
    return LayerRenderOptionsSuite2::createPtr(optionsH);
}

LayerRenderOptionsPtr
LayerRenderOptionsSuite2::newFromDownstreamOfEffect(EffectRefPtr effect_ref)
{
    CheckNotNull(
        effect_ref.get(),
        "Error Creating Layer Render Options from Downstream of Effect. Effect "
        "is Null");
    AEGP_LayerRenderOptionsH optionsH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_NewFromDownstreamOfEffect(*m_suiteManager.GetPluginID(),
                                                  *effect_ref.get(),
                                                  &optionsH));
    return LayerRenderOptionsSuite2::createPtr(optionsH);
}

LayerRenderOptionsPtr
LayerRenderOptionsSuite2::duplicate(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Duplicating Layer Render Options. Options are Null");
    AEGP_LayerRenderOptionsH new_optionsH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_Duplicate(*m_suiteManager.GetPluginID(),
                                  *optionsH.get(), &new_optionsH));
    return LayerRenderOptionsSuite2::createPtr(new_optionsH);
}

void LayerRenderOptionsSuite2::dispose(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Disposing Layer Render Options. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_Dispose(*optionsH.get()));
}

void LayerRenderOptionsSuite2::setTime(LayerRenderOptionsPtr optionsH,
                                       A_Time time)
{
    CheckNotNull(optionsH.get(), "Error Setting Time. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_SetTime(*optionsH.get(), time));
}

A_Time LayerRenderOptionsSuite2::getTime(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(), "Error Getting Time. Options are Null");
    A_Time time;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_GetTime(*optionsH.get(), &time));
    return time;
}

void LayerRenderOptionsSuite2::setTimeStep(LayerRenderOptionsPtr optionsH,
                                           A_Time time_step)
{
    CheckNotNull(optionsH.get(), "Error Setting Time Step. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_SetTimeStep(*optionsH.get(), time_step));
}

A_Time LayerRenderOptionsSuite2::getTimeStep(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(), "Error Getting Time Step. Options are Null");
    A_Time time;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_GetTimeStep(*optionsH.get(), &time));
    return time;
}

void LayerRenderOptionsSuite2::setWorldType(LayerRenderOptionsPtr optionsH,
                                            AE_WorldType type)
{
    CheckNotNull(optionsH.get(), "Error Setting World Type. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_SetWorldType(*optionsH.get(), AEGP_WorldType(type)));
}

AE_WorldType
LayerRenderOptionsSuite2::getWorldType(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(), "Error Getting World Type. Options are Null");
    AEGP_WorldType type;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_GetWorldType(*optionsH.get(), &type));
    return AE_WorldType(type);
}

void LayerRenderOptionsSuite2::setDownsampleFactor(
    LayerRenderOptionsPtr optionsH, A_short x, A_short y)
{
    CheckNotNull(optionsH.get(),
                 "Error Setting Downsample Factor. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_SetDownsampleFactor(*optionsH.get(), x, y));
}

std::tuple<A_short, A_short>
LayerRenderOptionsSuite2::getDownsampleFactor(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Getting Downsample Factor. Options are Null");
    A_short x;
    A_short y;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_GetDownsampleFactor(*optionsH.get(), &x, &y));
    return std::make_tuple(x, y);
}

void LayerRenderOptionsSuite2::setMatteMode(LayerRenderOptionsPtr optionsH,
                                            AE_MatteMode mode)
{
    CheckNotNull(optionsH.get(), "Error Setting Matte Mode. Options are Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_SetMatteMode(*optionsH.get(), AEGP_MatteMode(mode)));
}

AE_MatteMode
LayerRenderOptionsSuite2::getMatteMode(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(), "Error Getting Matte Mode. Options are Null");
    AEGP_MatteMode mode;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .LayerRenderOptionsSuite2()
                 ->AEGP_GetMatteMode(*optionsH.get(), &mode));
    return AE_MatteMode(mode);
}

Collection2Ptr CollectionSuite2::newCollection()
{
    AEGP_Collection2H collectionH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CollectionSuite2()->AEGP_NewCollection(
            *m_suiteManager.GetPluginID(), &collectionH));
    return CollectionSuite2::createPtr(collectionH);
}

void CollectionSuite2::disposeCollection(Collection2Ptr collectionH)
{
    CheckNotNull(collectionH.get(),
                 "Error Disposing Collection. Collection is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CollectionSuite2()
                 ->AEGP_DisposeCollection(*collectionH.get()));
}

A_long CollectionSuite2::getCollectionNumItems(Collection2Ptr collectionH)
{
    CheckNotNull(
        collectionH.get(),
        "Error Getting Collection Number of Items. Collection is Null");
    A_u_long numItemsL;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CollectionSuite2()
                 ->AEGP_GetCollectionNumItems(*collectionH.get(), &numItemsL));
    return static_cast<A_long>(numItemsL);
}

AEGP_CollectionItemV2
CollectionSuite2::getCollectionItemByIndex(Collection2Ptr collectionH,
                                           A_long indexL)
{
    CheckNotNull(collectionH.get(),
                 "Error Getting Collection Item by Index. Collection is Null");
    AEGP_CollectionItemV2 item;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler()
            .CollectionSuite2()
            ->AEGP_GetCollectionItemByIndex(*collectionH.get(), indexL, &item));
    return item;
}

void CollectionSuite2::collectionPushBack(Collection2Ptr collectionH,
                                          const AEGP_CollectionItemV2 &itemP)
{
    CheckNotNull(collectionH.get(),
                 "Error Pushing Back to Collection. Collection is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CollectionSuite2()
                 ->AEGP_CollectionPushBack(*collectionH.get(), &itemP));
}

void CollectionSuite2::collectionErase(Collection2Ptr collectionH,
                                       A_long index_firstL, A_long index_lastL)
{
    CheckNotNull(collectionH.get(),
                 "Error Erasing Collection. Collection is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CollectionSuite2()
                 ->AEGP_CollectionErase(*collectionH.get(), index_firstL,
                                        index_lastL));
}

void RegisterSuite5::registerCommandHook(AEGP_HookPriority hook_priority,
                                         AEGP_Command command,
                                         AEGP_CommandHook command_hook_func,
                                         AEGP_CommandRefcon refconP)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RegisterSuite5()
                 ->AEGP_RegisterCommandHook(*m_suiteManager.GetPluginID(),
                                            hook_priority, command,
                                            command_hook_func, refconP));
}

void RegisterSuite5::registerUpdateMenuHook(
    AEGP_UpdateMenuHook update_menu_hook_func, AEGP_UpdateMenuRefcon refconP)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RegisterSuite5()
                 ->AEGP_RegisterUpdateMenuHook(*m_suiteManager.GetPluginID(),
                                               update_menu_hook_func, refconP));
}

void RegisterSuite5::registerDeathHook(AEGP_DeathHook death_hook_func,
                                       AEGP_DeathRefcon refconP)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RegisterSuite5()
                 ->AEGP_RegisterDeathHook(*m_suiteManager.GetPluginID(),
                                          death_hook_func, refconP));
}

void RegisterSuite5::registerIdleHook(AEGP_IdleHook idle_hook_func,
                                      AEGP_IdleRefcon refconP)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RegisterSuite5()
                 ->AEGP_RegisterIdleHook(*m_suiteManager.GetPluginID(),
                                         idle_hook_func, refconP));
}

void RegisterSuite5::registerPresetLocalizationString(
    const std::string &english_nameZ, const std::string &localized_nameZ)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RegisterSuite5()
                 ->AEGP_RegisterPresetLocalizationString(
                     english_nameZ.c_str(), localized_nameZ.c_str()));
}

AEGP_Command CommandSuite1::getUniqueCommand()
{
    AEGP_Command command;
    AE_CHECK(SuiteManager::GetInstance()
                 .GetSuiteHandler()
                 .CommandSuite1()
                 ->AEGP_GetUniqueCommand(&command));
    return command;
}

void CommandSuite1::insertMenuCommand(AEGP_Command command,
                                      const std::string &nameZ,
                                      AE_MenuID menu_id, A_long after_itemL)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CommandSuite1()
                 ->AEGP_InsertMenuCommand(command, nameZ.c_str(),
                                          AEGP_MenuID(menu_id), after_itemL));
}

void CommandSuite1::removeMenuCommand(AEGP_Command command)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CommandSuite1()
                 ->AEGP_RemoveMenuCommand(command));
}

void CommandSuite1::setMenuCommandName(AEGP_Command command,
                                       const std::string &nameZ)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CommandSuite1()
                 ->AEGP_SetMenuCommandName(command, nameZ.c_str()));
}

void CommandSuite1::enableCommand(AEGP_Command command)
{
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CommandSuite1()->AEGP_EnableCommand(
            command));
}

void CommandSuite1::disableCommand(AEGP_Command command)
{
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().CommandSuite1()->AEGP_DisableCommand(
            command));
}

void CommandSuite1::checkMarkMenuCommand(AEGP_Command command, A_Boolean checkB)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .CommandSuite1()
                 ->AEGP_CheckMarkMenuCommand(command, checkB));
}

void CommandSuite1::doCommand(AEGP_Command command)
{
    AE_CHECK(m_suiteManager.GetSuiteHandler().CommandSuite1()->AEGP_DoCommand(
        command));
}

FrameReceiptPtr RenderSuite5::renderAndCheckoutFrame(RenderOptionsPtr optionsH)
{
    CheckNotNull(optionsH.get(),
                 "Error Rendering and Checking Out Frame. Options are Null");
    AEGP_FrameReceiptH receiptH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderSuite5()
                 ->AEGP_RenderAndCheckoutFrame(*optionsH.get(), NULL, NULL,
                                               &receiptH));
    return RenderSuite5::createPtr(receiptH);
}

FrameReceiptPtr
RenderSuite5::renderAndCheckoutLayerFrame(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(
        optionsH.get(),
        "Error Rendering and Checking Out Layer Frame. Options are Null");
    AEGP_FrameReceiptH receiptH;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderSuite5()
                 ->AEGP_RenderAndCheckoutLayerFrame(*optionsH.get(), NULL, NULL,
                                                    &receiptH));
    return RenderSuite5::createPtr(receiptH);
}

A_u_longlong RenderSuite5::renderAndCheckoutLayerFrameAsync(
    LayerRenderOptionsPtr optionsH, AEGP_AsyncFrameReadyCallback callback)
{
    CheckNotNull(
		optionsH.get(),
		"Error Rendering and Checking Out Layer Frame Asynchronously. Options "
		"are Null");
	A_u_longlong id;
	AE_CHECK(m_suiteManager.GetSuiteHandler()
    				 .RenderSuite5()
    				 ->AEGP_RenderAndCheckoutLayerFrame_Async(*optionsH.get(),
                         									  callback, NULL,
                         									  &id));
	return id;
}

void RenderSuite5::cancelAsyncRequest(AEGP_AsyncRequestId async_request_id) {
    AE_CHECK(m_suiteManager.GetSuiteHandler()
    				 .RenderSuite5()
    				 ->AEGP_CancelAsyncRequest(async_request_id));
}

WorldPtr RenderSuite5::getReceiptWorld(FrameReceiptPtr receiptH)
{
    CheckNotNull(receiptH.get(),
                 "Error Getting Receipt World. Receipt is Null");
    AEGP_WorldH worldH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RenderSuite5()->AEGP_GetReceiptWorld(
            *receiptH.get(), &worldH));
    return WorldSuite3::createPtr(worldH);
}

A_LRect RenderSuite5::getRenderedRegion(FrameReceiptPtr receiptH)
{
    CheckNotNull(receiptH.get(),
                 "Error Getting Rendered Region. Receipt is Null");
    A_LRect region;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RenderSuite5()->AEGP_GetRenderedRegion(
            *receiptH.get(), &region));
    return region;
}

bool RenderSuite5::isRenderedFrameSufficient(RenderOptionsPtr rendered_optionsH,
                                             RenderOptionsPtr proposed_optionsH)
{
    CheckNotNull(rendered_optionsH.get(),
                 "Error Checking if Rendered Frame is Sufficient. Rendered "
                 "Options are Null");
    CheckNotNull(proposed_optionsH.get(),
                 "Error Checking if Rendered Frame is Sufficient. Proposed "
                 "Options are Null");
    A_Boolean is_sufficientB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderSuite5()
                 ->AEGP_IsRenderedFrameSufficient(*rendered_optionsH.get(),
                                                  *proposed_optionsH.get(),
                                                  &is_sufficientB));
    return static_cast<bool>(is_sufficientB);
}

TimeStampPtr RenderSuite5::getCurrentTimestamp()
{
    AEGP_TimeStamp timeStamp;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderSuite5()
                 ->AEGP_GetCurrentTimestamp(&timeStamp));
    return std::make_shared<AEGP_TimeStamp>(timeStamp);
}

bool RenderSuite5::hasItemChangedSinceTimestamp(ItemPtr itemH,
                                                A_Time start_timeP,
                                                A_Time durationP,
                                                TimeStampPtr time_stampP)
{
    CheckNotNull(
        itemH.get(),
        "Error Checking if Item has Changed Since Timestamp. Item is Null");
    CheckNotNull(time_stampP.get(), "Error Checking if Item has Changed Since "
                                    "Timestamp. Time Stamp is Null");

    A_Boolean has_changedB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderSuite5()
                 ->AEGP_HasItemChangedSinceTimestamp(
                     *itemH.get(), &start_timeP, &durationP, time_stampP.get(),
                     &has_changedB));
    return static_cast<bool>(has_changedB);
}

bool RenderSuite5::isItemWorthwhileToRender(RenderOptionsPtr roH,
                                            TimeStampPtr time_stampP)
{
    CheckNotNull(roH.get(), "Error Checking if Item is Worthwhile to Render. "
                            "Render Options are Null");
    CheckNotNull(
        time_stampP.get(),
        "Error Checking if Item is Worthwhile to Render. Time Stamp is Null");
    A_Boolean is_worthwhileB;
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderSuite5()
                 ->AEGP_IsItemWorthwhileToRender(*roH.get(), time_stampP.get(),
                                                 &is_worthwhileB));
    return static_cast<bool>(is_worthwhileB);
}

void RenderSuite5::checkinRenderedFrame(RenderOptionsPtr roH,
                                        TimeStampPtr time_stampP,
                                        A_u_long ticks_to_renderL,
                                        PlatformWorldPtr imageH)
{
    CheckNotNull(roH.get(),
                 "Error Checking in Rendered Frame. Render Options are Null");
    CheckNotNull(time_stampP.get(),
                 "Error Checking in Rendered Frame. Time Stamp is Null");
    CheckNotNull(imageH.get(),
                 "Error Checking in Rendered Frame. Image is Null");
    AE_CHECK(m_suiteManager.GetSuiteHandler()
                 .RenderSuite5()
                 ->AEGP_CheckinRenderedFrame(*roH.get(), time_stampP.get(),
                                             ticks_to_renderL, *imageH.get()));
}

std::string RenderSuite5::getReceiptGuid(FrameReceiptPtr receiptH)
{
    CheckNotNull(receiptH.get(), "Error Getting Receipt GUID. Receipt is Null");
    AEGP_MemHandle guidH;
    AE_CHECK(
        m_suiteManager.GetSuiteHandler().RenderSuite5()->AEGP_GetReceiptGuid(
            *receiptH.get(), &guidH));
    return memHandleToString(guidH);
}

A_Time SecondsToTime(double seconds)
{
    double frameRate =
		CompSuite11().GetCompFramerate(CompSuite11().GetMostRecentlyUsedComp());
    A_u_long scale = static_cast<A_u_long>(frameRate);
    return {static_cast<A_long>(std::round(seconds * scale)), scale};
}

bool isLayerValid(ItemPtr item, CompPtr comp)
{
    return LayerSuite9().IsAddLayerValid(item, comp);
}

double TimeToSeconds(const A_Time &time)
{
    // Scale the value to move the decimal two places to the right
    double scaledValue = static_cast<double>(time.value) * 100.0 /
                         static_cast<double>(time.scale);

    // Round the scaled value to the nearest integer
    double rounded = std::round(scaledValue);

    // Scale the rounded value back down
    return rounded / 100.0;
}


int TimeToFrames(const A_Time& time)
{
    double seconds = TimeToSeconds(time);
    double frameRate =
        CompSuite11().GetCompFramerate(CompSuite11().GetMostRecentlyUsedComp());
    return static_cast<int>(std::round(seconds * frameRate));
}

A_Time FramesToTime(int frames)
{
	double frameRate =
		CompSuite11().GetCompFramerate(CompSuite11().GetMostRecentlyUsedComp());
	A_u_long scale = static_cast<A_u_long>(frameRate);
	return {frames, scale};
}

void RenderQueueSuite1::addCompToRenderQueue(CompPtr comp,
                                             const std::string &path)
{
    CheckNotNull(comp.get(),
				 "Error Adding Comp to Render Queue. Comp is Null");
        AE_CHECK(m_suiteManager.GetSuiteHandler()
            .RenderQueueSuite1()
            ->AEGP_AddCompToRenderQueue(
			*comp.get(), path.c_str()));
}

void RenderQueueSuite1::setRenderQueueState(AE_RenderQueueState state) {
        AE_CHECK(m_suiteManager.GetSuiteHandler()
            .RenderQueueSuite1()
            ->AEGP_SetRenderQueueState(AEGP_RenderQueueState(state)));
}

AE_RenderQueueState RenderQueueSuite1::getRenderQueueState()
{
    AEGP_RenderQueueState state;
	AE_CHECK(m_suiteManager.GetSuiteHandler()
				 .RenderQueueSuite1()
				 ->AEGP_GetRenderQueueState(&state));
	return AE_RenderQueueState(state);
}

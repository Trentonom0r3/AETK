#include <AETK/AEGP/Core/Suites.hpp>
#include <cassert>
/**
 * @function GetNumProjects
 * @brief` Get the number of projects in the current AE session
 *
 * \return
 */
int ProjSuite::GetNumProjects()
{
#ifdef TK_INTERNAL
    auto numProjResult = TaskScheduler::GetInstance().ScheduleTask([this]() {
        A_Err err = A_Err_NONE;
        int numProjects = 0;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetNumProjects(&numProjects));
        return numProjects;
    });
    return numProjResult.get();
#else
    A_Err err = A_Err_NONE;
    int numProjects = 0;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetNumProjects(&numProjects));
    return numProjects;
#endif
}

ProjectPtr ProjSuite::GetProjectByIndex(int projIndex)
{
#ifdef TK_INTERNAL
    auto projectResult = TaskScheduler::GetInstance().ScheduleTask([this, projIndex]() {
        AEGP_ProjectH projectH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectByIndex(projIndex, &projectH));
        return createPtr(projectH);
    });
    return projectResult.get();
#else
    AEGP_ProjectH projectH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectByIndex(projIndex, &projectH));
    return std::make_shared<AEGP_ProjectH>(projectH);
#endif
}

std::string ProjSuite::GetProjectName(ProjectPtr project)
{
#ifdef TK_INTERNAL
    auto nameResult = TaskScheduler::GetInstance().ScheduleTask([this, project]() {
        CheckNotNull(*project, "Error Getting Project Name. Project is Null");
        A_Err err = A_Err_NONE;
        A_char name[256];
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectName(*project, name));
        return std::string(name);
    });
    return nameResult.get();
#else
    CheckNotNull(*project, "Error Getting Project Name. Project is Null");
    A_char name[256];
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectName(*project, name));
    return std::string(name);
#endif
}

std::string ProjSuite::GetProjectPath(ProjectPtr project)
{
#ifdef TK_INTERNAL
    auto pathResult = TaskScheduler::GetInstance().ScheduleTask([this, project]() {
        A_Err err = A_Err_NONE;
        AEGP_MemHandle pathH;
        CheckNotNull(*project, "Error Getting Project Path. Project is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectPath(*project, &pathH));
        return memHandleToString(pathH);
    });
    return pathResult.get();
#else
    AEGP_MemHandle pathH;
    CheckNotNull(*project, "Error Getting Project Path. Project is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectPath(*project, &pathH));
    return memHandleToString(pathH);
#endif
}

ItemPtr ProjSuite::GetProjectRootFolder(ProjectPtr project)
{
#ifdef TK_INTERNAL
    auto rootFolderResult = TaskScheduler::GetInstance().ScheduleTask([this, project]() {
        AEGP_ItemH rootFolderH;
        CheckNotNull(*project, "Error Getting Project Root Folder. Project is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectRootFolder(*project,
                                                                                                       &rootFolderH));
        return std::make_shared<AEGP_ItemH>(rootFolderH);
    });
    return rootFolderResult.get();
#else
    AEGP_ItemH rootFolderH;
    CheckNotNull(*project, "Error Getting Project Root Folder. Project is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectRootFolder(*project, &rootFolderH));
    return std::make_shared<AEGP_ItemH>(rootFolderH);
#endif
}

void ProjSuite::SaveProjectToPath(ProjectPtr project, const std::string &path)
{
#ifdef TK_INTERNAL
    auto saveProjectResult = TaskScheduler::GetInstance().ScheduleTask([this, project, path]() {
        CheckNotNull(*project, "Error Saving Project. Project is Null");
        std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SaveProjectToPath(*project,
                                                                                                    path16.data()));
    });
#else
    CheckNotNull(*project, "Error Saving Project. Project is Null");
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SaveProjectToPath(*project, path16.data()));
#endif
}

TimeDisplay3 ProjSuite::GetProjectTimeDisplay(ProjectPtr project)
{
#ifdef TK_INTERNAL
    auto timeDisplayResult = TaskScheduler::GetInstance().ScheduleTask([this, project]() {
        AEGP_TimeDisplay3 timeDisplay;
        CheckNotNull(*project, "Error Getting Project Time Display. Project is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectTimeDisplay(*project,
                                                                                                        &timeDisplay));
        return TimeDisplay3(timeDisplay);
    });
    return timeDisplayResult.get();
#else
    AEGP_TimeDisplay3 timeDisplay;
    CheckNotNull(*project, "Error Getting Project Time Display. Project is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectTimeDisplay(*project, &timeDisplay));
    return TimeDisplay3(timeDisplay);
#endif
}

void ProjSuite::SetProjectTimeDisplay(ProjectPtr project, TimeDisplay3 timeDisplay)
{
#ifdef TK_INTERNAL
    auto setProjectTimeDisplayResult = TaskScheduler::GetInstance().ScheduleTask([this, project, timeDisplay]() {
        CheckNotNull(*project, "Error Setting Project Time Display. Project is Null");
        const AEGP_TimeDisplay3 timeDisplay3 = timeDisplay.ToAEGPTimeDisplay3();
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SetProjectTimeDisplay(*project,
                                                                                                        &timeDisplay3));
    });
#else
    CheckNotNull(*project, "Error Setting Project Time Display. Project is Null");
    const AEGP_TimeDisplay3 timeDisplay3 = timeDisplay.ToAEGPTimeDisplay3();
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SetProjectTimeDisplay(*project,
                                                                                                    &timeDisplay3));
#endif
}

bool ProjSuite::ProjectIsDirty(ProjectPtr project)
{
#ifdef TK_INTERNAL
    auto isDirtyResult = TaskScheduler::GetInstance().ScheduleTask([this, project]() {
        CheckNotNull(*project, "Error Checking if Project is Dirty. Project is Null");
        A_Boolean isDirty;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_ProjectIsDirty(*project, &isDirty));
        return isDirty;
    });
    return isDirtyResult.get();
#else
    CheckNotNull(*project, "Error Checking if Project is Dirty. Project is Null");
    A_Boolean isDirty;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_ProjectIsDirty(*project, &isDirty));
    return isDirty;
#endif
}

void ProjSuite::SaveProjectAs(ProjectPtr project, const std::string &path)
{
    CheckNotNull(*project, "Error Saving Project As. Project is Null");
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SaveProjectAs(*project, path16.data()));
}

ProjectPtr ProjSuite::NewProject()
{
    AEGP_ProjectH projectH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_NewProject(&projectH));
    return std::make_shared<AEGP_ProjectH>(projectH);
}

ProjectPtr ProjSuite::OpenProjectFromPath(const std::string &path)
{
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
    AEGP_ProjectH projectH;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_OpenProjectFromPath(path16.data(), &projectH));
    return std::make_shared<AEGP_ProjectH>(projectH);
}

ProjBitDepth ProjSuite::GetProjectBitDepth(ProjectPtr project)
{
    AEGP_ProjBitDepth bitDepth;
    CheckNotNull(*project, "Error Getting Project Bit Depth. Project is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectBitDepth(*project, &bitDepth));
    return ProjBitDepth(bitDepth);
}

void ProjSuite::SetProjectBitDepth(ProjectPtr project, ProjBitDepth bitDepth)
{
    CheckNotNull(*project, "Error Setting Project Bit Depth. Project is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SetProjectBitDepth(
        *project, AEGP_ProjBitDepth(bitDepth)));
}

ItemPtr ItemSuite::GetFirstProjItem(ProjectPtr project)
{
    CheckNotNull(*project, "Error Getting First Project Item. Project is Null");
    AEGP_ItemH itemH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetFirstProjItem(*project, &itemH));
    return std::make_shared<AEGP_ItemH>(itemH);
}

ItemPtr ItemSuite::GetNextProjItem(ProjectPtr project, ItemPtr item)
{
    AEGP_ItemH nextItemH;
    CheckNotNull(*project, "Error Getting Next Project Item. Project is Null");
    CheckNotNull(*project, "Error Getting Next Project Item. Current Item is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetNextProjItem(*project, *item, &nextItemH));
    return std::make_shared<AEGP_ItemH>(nextItemH);
}

ItemPtr ItemSuite::GetActiveItem()
{
    AEGP_ItemH itemH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetActiveItem(&itemH));
    if (itemH == NULL)
    {
        return nullptr;
    }
    return std::make_shared<AEGP_ItemH>(itemH);
}

bool ItemSuite::IsItemSelected(ItemPtr item)
{
    A_Boolean isSelected;
    CheckNotNull(*item, "Error Checking if Item is Selected. Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_IsItemSelected(*item, &isSelected));
    return isSelected;
}

void ItemSuite::SelectItem(ItemPtr item, bool select, bool deselectOthers)
{
    CheckNotNull(*item, "Error Selecting Item. Item is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SelectItem(*item, select, deselectOthers));
}

ItemType ItemSuite::GetItemType(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Type. Item is Null");
    AEGP_ItemType itemType;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemType(*item, &itemType));
    return ItemType(itemType);
}

std::string ItemSuite::GetTypeName(ItemType itemType)
{
    A_char name[256];
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetTypeName(AEGP_ItemType(itemType), name));
    return std::string(name);
}

std::string ItemSuite::GetItemName(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Name. Item is Null");
    AEGP_MemHandle nameH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemName(
        *SuiteManager::GetInstance().GetPluginID(), *item, &nameH));
    return memHandleToString(nameH);
}

void ItemSuite::SetItemName(ItemPtr item, const std::string &name)
{
    CheckNotNull(*item, "Error Setting Item Name. Item is Null");
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemName(*item, name16.data()));
}

int ItemSuite::GetItemID(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item ID. Item is Null");
    int id;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemID(*item, &id));
    return id;
}

ItemFlag ItemSuite::GetItemFlags(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Flags. Item is Null");
    int flags;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemFlags(*item, &flags));
    return ItemFlag(flags);
}

void ItemSuite::SetItemUseProxy(ItemPtr item, bool useProxy)
{
    CheckNotNull(*item, "Error Setting Item Use Proxy. Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemUseProxy(*item, useProxy));
}

ItemPtr ItemSuite::GetItemParentFolder(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Parent Folder. Item is Null");
    AEGP_ItemH parentFolderH;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemParentFolder(*item, &parentFolderH));
    return std::make_shared<AEGP_ItemH>(parentFolderH);
}

void ItemSuite::SetItemParentFolder(ItemPtr item, ItemPtr parentFolder)
{
    CheckNotNull(*item, "Error Setting Item Parent Folder. Item is Null");
    CheckNotNull(*parentFolder, "Error Setting Item Parent Folder. Parent Folder is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemParentFolder(*item, *parentFolder));
}

A_Time ItemSuite::GetItemDuration(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Duration. Item is Null");
    A_Time duration;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemDuration(*item, &duration));
    return duration;
}

A_Time ItemSuite::GetItemCurrentTime(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Current Time. Item is Null");
    A_Time currentTime;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemCurrentTime(*item, &currentTime));
    return currentTime;
}

std::tuple<int, int> ItemSuite::GetItemDimensions(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Dimensions. Item is Null");
    int width;
    int height;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemDimensions(*item, &width, &height));
    return std::make_tuple(width, height);
}

A_Ratio ItemSuite::GetItemPixelAspectRatio(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Pixel Aspect Ratio. Item is Null");
    A_Ratio pixelAspectRatio;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemPixelAspectRatio(
        *item, &pixelAspectRatio));
    return pixelAspectRatio;
}

void ItemSuite::DeleteItem(ItemPtr item)
{
    CheckNotNull(*item, "Error Deleting Item. Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_DeleteItem(*item));
}

ItemPtr ItemSuite::CreateNewFolder(const std::string &name, ItemPtr parentFolder)
{
    CheckNotNull(*parentFolder, "Error Creating New Folder. Parent Folder is Null");
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AEGP_ItemH folderH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_CreateNewFolder(name16.data(),
                                                                                              *parentFolder, &folderH));
    return std::make_shared<AEGP_ItemH>(folderH);
}

void ItemSuite::SetItemCurrentTime(ItemPtr item, A_Time newTime)
{
    CheckNotNull(*item, "Error Setting Item Current Time. Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemCurrentTime(*item, &newTime));
}

std::string ItemSuite::GetItemComment(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Comment. Item is Null");
    AEGP_MemHandle commentH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemComment(*item, &commentH));
    return memHandleToString(commentH);
}

void ItemSuite::SetItemComment(ItemPtr item, const std::string &comment)
{
    CheckNotNull(*item, "Error Setting Item Comment. Item is Null");
    std::vector<A_UTF16Char> comment16 = ConvertUTF8ToUTF16(comment);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemComment(*item, comment16.data()));
}

Label ItemSuite::GetItemLabel(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item Label. Item is Null");
    AEGP_LabelID label;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemLabel(*item, &label));
    return Label(label);
}

void ItemSuite::SetItemLabel(ItemPtr item, Label label)
{
    CheckNotNull(*item, "Error Setting Item Label. Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemLabel(*item, AEGP_LabelID(label)));
}

ItemViewPtr ItemSuite::GetItemMRUView(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Item MRU View. Item is Null");
    AEGP_ItemViewP itemViewH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemMRUView(*item, &itemViewH));
    return std::make_shared<AEGP_ItemViewP>(itemViewH);
}

A_Time ItemSuite::GetItemViewPlaybackTime(ItemViewPtr itemView, bool &isCurrentlyPreviewing)
{
    CheckNotNull(*itemView, "Error Getting Item View Playback Time. Item View is Null");
    A_Time time;
    A_Boolean isPreviewing = static_cast<A_Boolean>(isCurrentlyPreviewing);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemViewSuite1()->AEGP_GetItemViewPlaybackTime(
        *itemView, &isPreviewing, &time));
    isCurrentlyPreviewing = isPreviewing;
    return time;
}

SoundDataPtr SoundDataSuite::NewSoundData(SoundDataFormat soundFormat)
{
    AEGP_SoundDataH soundDataH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_NewSoundData(
        &soundFormat.ToAEGPSoundDataFormat(), &soundDataH));
    return std::shared_ptr<AEGP_SoundDataH>(new AEGP_SoundDataH(soundDataH), SoundDataDeleter());
}

SoundDataFormat SoundDataSuite::GetSoundDataFormat(SoundDataPtr soundData)
{
    CheckNotNull(*soundData, "Error Getting Sound Data Format. Sound Data is Null");
    AEGP_SoundDataFormat format;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_GetSoundDataFormat(*soundData, &format));
    return SoundDataFormat(format);
}

void SoundDataSuite::LockSoundDataSamples(SoundDataPtr soundData, void **samples)
{
    CheckNotNull(*soundData, "Error Locking Sound Data Samples. Sound Data is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_LockSoundDataSamples(*soundData,
                                                                                                        samples));
}

void SoundDataSuite::UnlockSoundDataSamples(SoundDataPtr soundData)
{
    CheckNotNull(*soundData, "Error Unlocking Sound Data Samples. Sound Data is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_UnlockSoundDataSamples(*soundData));
}

int SoundDataSuite::GetNumSamples(SoundDataPtr soundData)
{
    CheckNotNull(*soundData, "Error Getting Number of Samples. Sound Data is Null");
    int numSamples;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_GetNumSamples(*soundData, &numSamples));
    return numSamples;
}

CompPtr CompSuite::GetCompFromItem(ItemPtr item)
{
    CheckNotNull(*item, "Error Getting Comp From Item. Item is Null");
    AEGP_CompH compH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFromItem(*item, &compH));
    return std::make_shared<AEGP_CompH>(compH);
}

ItemPtr CompSuite::GetItemFromComp(CompPtr comp)
{
    AEGP_ItemH itemH;
    CheckNotNull(*comp, "Error Getting Item From Comp. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetItemFromComp(*comp, &itemH));
    return std::make_shared<AEGP_ItemH>(itemH);
}

DownsampleFactor CompSuite::GetCompDownsampleFactor(CompPtr comp)
{
    AEGP_DownsampleFactor factor;
    CheckNotNull(*comp, "Error Getting Comp Downsample Factor. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompDownsampleFactor(*comp, &factor));
    return DownsampleFactor(factor);
}

void CompSuite::SetCompDownsampleFactor(CompPtr comp, DownsampleFactor dsf)
{
    CheckNotNull(*comp, "Error Setting Comp Downsample Factor. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompDownsampleFactor(
        *comp, &dsf.ToAEGPDownsampleFactor()));
}

ColorVal CompSuite::GetCompBGColor(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Background Color. Comp is Null");
    AEGP_ColorVal color;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompBGColor(*comp, &color));
    return ColorVal(color);
}

void CompSuite::SetCompBGColor(CompPtr comp, ColorVal color)
{
    CheckNotNull(*comp, "Error Setting Comp Background Color. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompBGColor(*comp,
                                                                                              &color.ToAEGPColorVal()));
}

CompFlag CompSuite::GetCompFlags(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Flags. Comp is Null");
    int flags;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFlags(*comp, &flags));
    return CompFlag(flags);
}

bool CompSuite::GetShowLayerNameOrSourceName(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Show Layer Name or Source Name. Comp is Null");
    A_Boolean showLayerName;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetShowLayerNameOrSourceName(
        *comp, &showLayerName));
    return showLayerName;
}

void CompSuite::SetShowLayerNameOrSourceName(CompPtr comp, bool showLayerName)
{
    CheckNotNull(*comp, "Error Setting Show Layer Name or Source Name. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetShowLayerNameOrSourceName(
        *comp, showLayerName));
}

bool CompSuite::GetShowBlendModes(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Show Blend Modes. Comp is Null");
    A_Boolean showBlendModes;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetShowBlendModes(*comp, &showBlendModes));
    return showBlendModes;
}

void CompSuite::SetShowBlendModes(CompPtr comp, bool showBlendModes)
{
    CheckNotNull(*comp, "Error Setting Show Blend Modes. Comp is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetShowBlendModes(*comp, showBlendModes));
}

double CompSuite::GetCompFramerate(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Frame Rate. Comp is Null");
    double fps;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFramerate(*comp, &fps));
    return fps;
}

void CompSuite::SetCompFrameRate(CompPtr comp, double fps)
{
    CheckNotNull(*comp, "Error Setting Comp Frame Rate. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompFrameRate(*comp, &fps));
}

std::tuple<A_Ratio, A_Ratio> CompSuite::GetCompShutterAnglePhase(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Shutter Angle Phase. Comp is Null");
    A_Ratio angle;
    A_Ratio phase;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompShutterAnglePhase(*comp, &angle,
                                                                                                        &phase));
    return std::make_tuple(angle, phase);
}

std::tuple<A_Time, A_Time> CompSuite::GetCompShutterFrameRange(CompPtr comp, A_Time compTime)
{
    CheckNotNull(*comp, "Error Getting Comp Shutter Frame Range. Comp is Null");
    return std::tuple<A_Time, A_Time>();
}

int CompSuite::GetCompSuggestedMotionBlurSamples(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Suggested Motion Blur Samples. Comp is Null");
    int samples;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompSuggestedMotionBlurSamples(
        *comp, &samples));
    return samples;
}

void CompSuite::SetCompSuggestedMotionBlurSamples(CompPtr comp, int samples)
{
    CheckNotNull(*comp, "Error Setting Comp Suggested Motion Blur Samples. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompSuggestedMotionBlurSamples(
        *comp, samples));
}

int CompSuite::GetCompMotionBlurAdaptiveSampleLimit(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Motion Blur Adaptive Sample Limit. Comp is Null");
    int samples;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompMotionBlurAdaptiveSampleLimit(
        *comp, &samples));
    return samples;
}

void CompSuite::SetCompMotionBlurAdaptiveSampleLimit(CompPtr comp, int samples)
{
    CheckNotNull(*comp, "Error Setting Comp Motion Blur Adaptive Sample Limit. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompMotionBlurAdaptiveSampleLimit(
        *comp, samples));
}

A_Time CompSuite::GetCompWorkAreaStart(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Work Area Start. Comp is Null");
    A_Time workAreaStart;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompWorkAreaStart(*comp, &workAreaStart));
    return workAreaStart;
}

A_Time CompSuite::GetCompWorkAreaDuration(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Work Area Duration. Comp is Null");
    A_Time workAreaDuration;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompWorkAreaDuration(
        *comp, &workAreaDuration));
    return workAreaDuration;
}

void CompSuite::SetCompWorkAreaStartAndDuration(CompPtr comp, A_Time workAreaStart, A_Time workAreaDuration)
{
    CheckNotNull(*comp, "Error Setting Comp Work Area Start and Duration. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompWorkAreaStartAndDuration(
        *comp, &workAreaStart, &workAreaDuration));
}

LayerPtr CompSuite::CreateSolidInComp(CompPtr comp, const std::string &name, int width, int height, ColorVal color,
                                      A_Time duration)
{
    CheckNotNull(*comp, "Error Creating Solid in Comp. Comp is Null");
    AEGP_LayerH layerH;
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateSolidInComp(
        name16.data(), width, height, &color.ToAEGPColorVal(), *comp, &duration, &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

LayerPtr CompSuite::CreateCameraInComp(CompPtr comp, const std::string &name, FloatPoint centerPoint)
{
    CheckNotNull(*comp, "Error Creating Camera in Comp. Comp is Null");
    AEGP_LayerH layerH;
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateCameraInComp(
        name16.data(), centerPoint.ToA_FloatPoint(), *comp, &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

LayerPtr CompSuite::CreateLightInComp(CompPtr comp, const std::string &name, FloatPoint centerPoint)
{
    CheckNotNull(*comp, "Error Creating Light in Comp. Comp is Null");
    AEGP_LayerH layerH;
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateLightInComp(
        name16.data(), centerPoint.ToA_FloatPoint(), *comp, &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

CompPtr CompSuite::CreateComp(ItemPtr parentFolder, const std::string &name, int width, int height,
                              const A_Ratio &pixelAspectRatio, A_Time duration, const A_Ratio &framerate)
{
    AEGP_CompH compH;
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateComp(
        *parentFolder, name16.data(), width, height, &pixelAspectRatio, &duration, &framerate, &compH));
    return std::make_shared<AEGP_CompH>(compH);
}

A_Time CompSuite::GetCompDisplayStartTime(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Display Start Time. Comp is Null");
    A_Time startTime;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompDisplayStartTime(*comp, &startTime));
    return startTime;
}

void CompSuite::SetCompDisplayStartTime(CompPtr comp, A_Time startTime)
{
    CheckNotNull(*comp, "Error Setting Comp Display Start Time. Comp is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompDisplayStartTime(*comp, &startTime));
}

void CompSuite::SetCompDuration(CompPtr comp, A_Time duration)
{
    CheckNotNull(*comp, "Error Setting Comp Duration. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompDuration(*comp, &duration));
}

CompPtr CompSuite::DuplicateComp(CompPtr comp)
{
    CheckNotNull(*comp, "Error Duplicating Comp. Comp is Null");
    AEGP_CompH newCompH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_DuplicateComp(*comp, &newCompH));
    return std::make_shared<AEGP_CompH>(newCompH);
}

A_Time CompSuite::GetCompFrameDuration(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Frame Duration. Comp is Null");
    A_Time frameDuration;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFrameDuration(*comp, &frameDuration));
    return frameDuration;
}

CompPtr CompSuite::GetMostRecentlyUsedComp()
{
    AEGP_CompH compH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetMostRecentlyUsedComp(&compH));
    if (compH == NULL)
    {
        return nullptr;
    }
    return std::make_shared<AEGP_CompH>(compH);
}

LayerPtr CompSuite::CreateVectorLayerInComp(CompPtr comp)
{
    CheckNotNull(*comp, "Error Creating Vector Layer in Comp. Comp is Null");
    AEGP_LayerH layerH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateVectorLayerInComp(*comp, &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

StreamRefPtr CompSuite::GetNewCompMarkerStream(CompPtr parentComp)
{
    CheckNotNull(*parentComp, "Error Getting New Comp Marker Stream. Parent Comp is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetNewCompMarkerStream(
        *SuiteManager::GetInstance().GetPluginID(), *parentComp, &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

bool CompSuite::GetCompDisplayDropFrame(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Display Drop Frame. Comp is Null");
    A_Boolean dropFrame;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompDisplayDropFrame(*comp, &dropFrame));
    return dropFrame;
}

void CompSuite::SetCompDisplayDropFrame(CompPtr comp, bool dropFrame)
{
    CheckNotNull(*comp, "Error Setting Comp Display Drop Frame. Comp is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompDisplayDropFrame(*comp, dropFrame));
}

void CompSuite::ReorderCompSelection(CompPtr comp, int index)
{
    CheckNotNull(*comp, "Error Reordering Comp Selection. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_ReorderCompSelection(*comp, index));
}

MemHandlePtr MemorySuite::NewMemHandle(const std::string &what, AEGP_MemSize size, MemFlag flags)
{
    AEGP_MemHandle memHandle;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_NewMemHandle(
        *SuiteManager::GetInstance().GetPluginID(), what.c_str(), size, AEGP_MemFlag(flags), &memHandle));
    return std::shared_ptr<AEGP_MemHandle>(new AEGP_MemHandle(memHandle), MemHandleDeleter());
}

void MemorySuite::FreeMemHandle(MemHandlePtr memH)
{
    CheckNotNull(*memH, "Error Freeing Memory Handle. Memory Handle is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_FreeMemHandle(*memH));
}

void MemorySuite::LockMemHandle(MemHandlePtr memHandle, void **ptrToPtr)
{
    CheckNotNull(*memHandle, "Error Locking Memory Handle. Memory Handle is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_LockMemHandle(*memHandle, ptrToPtr));
}

void MemorySuite::UnlockMemHandle(MemHandlePtr memHandle)
{
    CheckNotNull(*memHandle, "Error Unlocking Memory Handle. Memory Handle is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_UnlockMemHandle(*memHandle));
}

AEGP_MemSize MemorySuite::GetMemHandleSize(MemHandlePtr memHandle)
{
    CheckNotNull(*memHandle, "Error Getting Memory Handle Size. Memory Handle is Null");
    AEGP_MemSize size;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_GetMemHandleSize(*memHandle, &size));
    return size;
}

void MemorySuite::ResizeMemHandle(const std::string &what, AEGP_MemSize newSize, MemHandlePtr memHandle)
{
    CheckNotNull(*memHandle, "Error Resizing Memory Handle. Memory Handle is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_ResizeMemHandle(what.c_str(), newSize,
                                                                                                *memHandle));
}

void MemorySuite::SetMemReportingOn(bool turnOn)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_SetMemReportingOn(turnOn));
}

std::tuple<int, int> MemorySuite::GetMemStats()
{
    int totalAllocated;
    int totalFreed;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_GetMemStats(
        *SuiteManager::GetInstance().GetPluginID(), &totalAllocated, &totalFreed));
    return std::make_tuple(totalAllocated, totalFreed);
}

int LayerSuite::GetCompNumLayers(CompPtr comp)
{
    CheckNotNull(*comp, "Error Getting Comp Number of Layers. Comp is Null");
    int numLayers;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetCompNumLayers(*comp, &numLayers));
    return numLayers;
}

LayerPtr LayerSuite::GetCompLayerByIndex(CompPtr comp, int layerIndex)
{
    CheckNotNull(*comp, "Error Getting Comp Layer by Index. Comp is Null");
    AEGP_LayerH layerH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetCompLayerByIndex(*comp, layerIndex,
                                                                                                   &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

LayerPtr LayerSuite::GetActiveLayer()
{
    AEGP_LayerH layerH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetActiveLayer(&layerH));
    if (layerH == NULL)
    {
        return nullptr;
    }
    return std::make_shared<AEGP_LayerH>(layerH);
}

int LayerSuite::GetLayerIndex(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Index. Layer is Null");
    int index;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerIndex(*layer, &index));
    return index;
}

ItemPtr LayerSuite::GetLayerSourceItem(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Source Item. Layer is Null");
    AEGP_ItemH itemH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerSourceItem(*layer, &itemH));
    return std::make_shared<AEGP_ItemH>(itemH);
}

int LayerSuite::GetLayerSourceItemID(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Source Item ID. Layer is Null");
    int id;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerSourceItemID(*layer, &id));
    return id;
}

CompPtr LayerSuite::GetLayerParentComp(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Parent Comp. Layer is Null");
    AEGP_CompH compH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerParentComp(*layer, &compH));
    return std::make_shared<AEGP_CompH>(compH);
}

std::tuple<std::string, std::string> LayerSuite::GetLayerName(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Name. Layer is Null");
    AEGP_MemHandle nameH;
    AEGP_MemHandle sourceNameH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerName(
        *SuiteManager::GetInstance().GetPluginID(), *layer, &nameH, &sourceNameH));
    return std::make_tuple(memHandleToString(nameH), memHandleToString(sourceNameH));
}

LayerQual LayerSuite::GetLayerQuality(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Quality. Layer is Null");
    AEGP_LayerQuality quality;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerQuality(*layer, &quality));
    return LayerQual(quality);
}

void LayerSuite::SetLayerQuality(LayerPtr layer, LayerQual quality)
{
    CheckNotNull(*layer, "Error Setting Layer Quality. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerQuality(
        *layer, AEGP_LayerQuality(quality)));
}

LayerFlag LayerSuite::GetLayerFlags(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Flags. Layer is Null");
    int flags;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerFlags(*layer, &flags));
    return LayerFlag(flags);
}

void LayerSuite::SetLayerFlag(LayerPtr layer, LayerFlag singleFlag, bool value)
{
    CheckNotNull(*layer, "Error Setting Layer Flag. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerFlag(
        *layer, AEGP_LayerFlags(singleFlag), value));
}

bool LayerSuite::IsLayerVideoReallyOn(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Checking if Layer Video is Really On. Layer is Null");
    A_Boolean isOn;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayerVideoReallyOn(*layer, &isOn));
    return static_cast<bool>(isOn);
}

bool LayerSuite::IsLayerAudioReallyOn(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Checking if Layer Audio is Really On. Layer is Null");
    A_Boolean isOn;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayerAudioReallyOn(*layer, &isOn));
    return static_cast<bool>(isOn);
}

A_Time LayerSuite::GetLayerCurrentTime(LayerPtr layer, LTimeMode timeMode)
{
    CheckNotNull(*layer, "Error Getting Layer Current Time. Layer is Null");
    A_Time time;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerCurrentTime(
        *layer, AEGP_LTimeMode(timeMode), &time));
    return time;
}

A_Time LayerSuite::GetLayerInPoint(LayerPtr layer, LTimeMode timeMode)
{
    CheckNotNull(*layer, "Error Getting Layer In Point. Layer is Null");
    A_Time time;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerInPoint(
        *layer, AEGP_LTimeMode(timeMode), &time));
    return time;
}

A_Time LayerSuite::GetLayerDuration(LayerPtr layer, LTimeMode timeMode)
{
    CheckNotNull(*layer, "Error Getting Layer Duration. Layer is Null");
    A_Time time;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerDuration(
        *layer, AEGP_LTimeMode(timeMode), &time));
    return time;
}

void LayerSuite::SetLayerInPointAndDuration(LayerPtr layer, LTimeMode timeMode, A_Time inPoint, A_Time duration)
{
    CheckNotNull(*layer, "Error Setting Layer In Point and Duration. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerInPointAndDuration(
        *layer, AEGP_LTimeMode(timeMode), &inPoint, &duration));
}

A_Time LayerSuite::GetLayerOffset(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Offset. Layer is Null");
    A_Time offset;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerOffset(*layer, &offset));
    return offset;
}

void LayerSuite::SetLayerOffset(LayerPtr layer, A_Time offset)
{
    CheckNotNull(*layer, "Error Setting Layer Offset. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerOffset(*layer, &offset));
}

A_Ratio LayerSuite::GetLayerStretch(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Stretch. Layer is Null");
    A_Ratio stretch;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerStretch(*layer, &stretch));
    return stretch;
}

void LayerSuite::SetLayerStretch(LayerPtr layer, A_Ratio stretch)
{
    CheckNotNull(*layer, "Error Setting Layer Stretch. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerStretch(*layer, &stretch));
}

void LayerSuite::SetLayerTransferMode(LayerPtr layer, TransferFlags flags, TrackMatte trackMatte) {}

bool LayerSuite::IsAddLayerValid(ItemPtr itemToAdd, CompPtr intoComp)
{
    CheckNotNull(*itemToAdd, "Error Checking if Add Layer is Valid. Item to Add is Null");
    CheckNotNull(*intoComp, "Error Checking if Add Layer is Valid. Comp is Null");
    A_Boolean isValid;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsAddLayerValid(*itemToAdd, *intoComp,
                                                                                               &isValid));
    return static_cast<bool>(isValid);
}

LayerPtr LayerSuite::AddLayer(ItemPtr itemToAdd, CompPtr intoComp)
{
    CheckNotNull(*itemToAdd, "Error Adding Layer. Item to Add is Null");
    CheckNotNull(*intoComp, "Error Adding Layer. Comp is Null");
    AEGP_LayerH layerH;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_AddLayer(*itemToAdd, *intoComp, &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

void LayerSuite::ReorderLayer(LayerPtr layer, int layerIndex)
{
    CheckNotNull(*layer, "Error Reordering Layer. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_ReorderLayer(*layer, layerIndex));
}

FloatRect LayerSuite::GetLayerMaskedBounds(LayerPtr layer, LTimeMode timeMode, A_Time time)
{
    CheckNotNull(*layer, "Error Getting Layer Masked Bounds. Layer is Null");
    A_FloatRect rect;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerMaskedBounds(
        *layer, AEGP_LTimeMode(timeMode), &time, &rect));
    return FloatRect(rect);
}

ObjectType LayerSuite::GetLayerObjectType(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Object Type. Layer is Null");
    AEGP_ObjectType type;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerObjectType(*layer, &type));
    return ObjectType(type);
}

bool LayerSuite::IsLayer3D(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Checking if Layer is 3D. Layer is Null");
    A_Boolean is3D;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayer3D(*layer, &is3D));
    return static_cast<bool>(is3D);
}

bool LayerSuite::IsLayer2D(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Checking if Layer is 2D. Layer is Null");
    A_Boolean is2D;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayer2D(*layer, &is2D));
    return static_cast<bool>(is2D);
}

bool LayerSuite::IsVideoActive(LayerPtr layer, LTimeMode timeMode, A_Time time)
{
    CheckNotNull(*layer, "Error Checking if Video is Active. Layer is Null");
    A_Boolean isActive;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsVideoActive(
        *layer, AEGP_LTimeMode(timeMode), &time, &isActive));
    return static_cast<bool>(isActive);
}

bool LayerSuite::IsLayerUsedAsTrackMatte(LayerPtr layer, bool fillMustBeActive)
{
    CheckNotNull(*layer, "Error Checking if Layer is Used as Track Matte. Layer is Null");
    A_Boolean isUsed;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayerUsedAsTrackMatte(
        *layer, fillMustBeActive, &isUsed));
    return static_cast<bool>(isUsed);
}

bool LayerSuite::DoesLayerHaveTrackMatte(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Checking if Layer has Track Matte. Layer is Null");
    A_Boolean hasTrackMatte;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_DoesLayerHaveTrackMatte(*layer,
                                                                                                       &hasTrackMatte));
    return static_cast<bool>(hasTrackMatte);
}

A_Time LayerSuite::ConvertCompToLayerTime(LayerPtr layer, A_Time compTime)
{
    CheckNotNull(*layer, "Error Converting Comp to Layer Time. Layer is Null");
    A_Time layerTime;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_ConvertCompToLayerTime(*layer, &compTime,
                                                                                                      &layerTime));
    return layerTime;
}

A_Time LayerSuite::ConvertLayerToCompTime(LayerPtr layer, A_Time layerTime)
{
    CheckNotNull(*layer, "Error Converting Layer to Comp Time. Layer is Null");
    A_Time compTime;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_ConvertLayerToCompTime(
        *layer, &layerTime, &compTime));
    return compTime;
}

int LayerSuite::GetLayerDancingRandValue(LayerPtr layer, A_Time compTime)
{
    CheckNotNull(*layer, "Error Getting Layer Dancing Rand Value. Layer is Null");
    int value;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerDancingRandValue(
        *layer, &compTime, &value));
    return value;
}

AEGP_LayerIDVal LayerSuite::GetLayerID(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer ID. Layer is Null");
    AEGP_LayerIDVal id;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerID(*layer, &id));
    return id;
}

Matrix4 LayerSuite::GetLayerToWorldXform(LayerPtr layer, A_Time compTime)
{
    CheckNotNull(*layer, "Error Getting Layer to World Xform. Layer is Null");
    A_Matrix4 xform;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerToWorldXform(*layer, &compTime,
                                                                                                    &xform));
    return Matrix4(xform);
}

Matrix4 LayerSuite::GetLayerToWorldXformFromView(LayerPtr layer, A_Time viewTime, A_Time compTime)
{
    CheckNotNull(*layer, "Error Getting Layer to World Xform from View. Layer is Null");
    A_Matrix4 xform;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerToWorldXformFromView(
        *layer, &viewTime, &compTime, &xform));
    return Matrix4(xform);
}

void LayerSuite::SetLayerName(LayerPtr layer, const std::string &newName)
{
    CheckNotNull(*layer, "Error Setting Layer Name. Layer is Null");
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(newName);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerName(*layer, name16.data()));
}

LayerPtr LayerSuite::GetLayerParent(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Parent. Layer is Null");
    AEGP_LayerH parentLayerH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerParent(*layer, &parentLayerH));
    return std::make_shared<AEGP_LayerH>(parentLayerH);
}

void LayerSuite::SetLayerParent(LayerPtr layer, LayerPtr parentLayer)
{
    CheckNotNull(*layer, "Error Setting Layer Parent. Layer is Null");
    CheckNotNull(*parentLayer, "Error Setting Layer Parent. Parent Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerParent(*layer, *parentLayer));
}

void LayerSuite::DeleteLayer(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Deleting Layer. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_DeleteLayer(*layer));
}

LayerPtr LayerSuite::DuplicateLayer(LayerPtr origLayer)
{
    CheckNotNull(*origLayer, "Error Duplicating Layer. Original Layer is Null");
    AEGP_LayerH newLayerH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_DuplicateLayer(*origLayer, &newLayerH));
    return std::make_shared<AEGP_LayerH>(newLayerH);
}

LayerPtr LayerSuite::GetLayerFromLayerID(CompPtr parentComp, AEGP_LayerIDVal id)
{
    CheckNotNull(*parentComp, "Error Getting Layer from Layer ID. Parent Comp is Null");
    AEGP_LayerH layerH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerFromLayerID(*parentComp, id,
                                                                                                   &layerH));
    return std::make_shared<AEGP_LayerH>(layerH);
}

AEGP_LabelID LayerSuite::GetLayerLabel(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Label. Layer is Null");
    AEGP_LabelID label;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerLabel(*layer, &label));
    return label;
}

void LayerSuite::SetLayerLabel(LayerPtr layer, AEGP_LabelID label)
{
    CheckNotNull(*layer, "Error Setting Layer Label. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerLabel(*layer, label));
}

LayerSamplingQual LayerSuite::GetLayerSamplingQuality(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Sampling Quality. Layer is Null");
    AEGP_LayerSamplingQuality quality;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerSamplingQuality(*layer, &quality));
    return LayerSamplingQual(quality);
}

void LayerSuite::SetLayerSamplingQuality(LayerPtr layer, LayerSamplingQual quality)
{
    CheckNotNull(*layer, "Error Setting Layer Sampling Quality. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerSamplingQuality(
        *layer, AEGP_LayerSamplingQuality(quality)));
}

LayerPtr LayerSuite::GetTrackMatteLayer(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Track Matte Layer. Layer is Null");
    AEGP_LayerH matteLayerH;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetTrackMatteLayer(*layer, &matteLayerH));
    return std::make_shared<AEGP_LayerH>(matteLayerH);
}

void LayerSuite::SetTrackMatte(LayerPtr layer, LayerPtr trackMatteLayer, TrackMatte trackMatteType)
{
    CheckNotNull(*layer, "Error Setting Track Matte. Layer is Null");
    CheckNotNull(*trackMatteLayer, "Error Setting Track Matte. Track Matte Layer is Null");

    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetTrackMatte(
        *layer, *trackMatteLayer, AEGP_TrackMatte(trackMatteType)));
}

void LayerSuite::RemoveTrackMatte(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Removing Track Matte. Layer is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_RemoveTrackMatte(*layer));
}

bool StreamSuite::IsStreamLegal(LayerPtr layer, LayerStream whichStream)
{
    CheckNotNull(*layer, "Error Checking if Stream is Legal. Layer is Null");
    A_Boolean isLegal;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_IsStreamLegal(
        *layer, AEGP_LayerStream(whichStream), &isLegal));
    return static_cast<bool>(isLegal);
}

bool StreamSuite::CanVaryOverTime(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Checking if Stream can Vary Over Time. Stream is Null");
    A_Boolean canVary;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_CanVaryOverTime(*stream, &canVary));
    return static_cast<bool>(canVary);
}

KeyInterpMask StreamSuite::GetValidInterpolations(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Valid Interpolations. Stream is Null");
    int validInterps;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetValidInterpolations(*stream,
                                                                                                       &validInterps));
    return KeyInterpMask(validInterps);
}

StreamRefPtr StreamSuite::GetNewLayerStream(LayerPtr layer, LayerStream whichStream)
{
    CheckNotNull(*layer, "Error Getting New Layer Stream. Layer is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetNewLayerStream(
        *SuiteManager::GetInstance().GetPluginID(), *layer, AEGP_LayerStream(whichStream), &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

int StreamSuite::GetEffectNumParamStreams(EffectRefPtr effectRef)
{
    int numStreams;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetEffectNumParamStreams(*effectRef,
                                                                                                         &numStreams));
    return numStreams;
}

StreamRefPtr StreamSuite::GetNewEffectStreamByIndex(EffectRefPtr effectRef, int paramIndex)
{
    CheckNotNull(*effectRef, "Error Getting New Effect Stream by Index. Effect is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetNewEffectStreamByIndex(
        *SuiteManager::GetInstance().GetPluginID(), *effectRef, paramIndex, &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

StreamRefPtr StreamSuite::GetNewMaskStream(MaskRefPtr maskRef, MaskStream whichStream)
{
    CheckNotNull(*maskRef, "Error Getting New Mask Stream. Mask is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetNewMaskStream(
        *SuiteManager::GetInstance().GetPluginID(), *maskRef, AEGP_MaskStream(whichStream), &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

std::string StreamSuite::GetStreamName(StreamRefPtr stream, bool forceEnglish)
{
    CheckNotNull(*stream, "Error Getting Stream Name. Stream is Null");
    AEGP_MemHandle nameH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetStreamName(
        *SuiteManager::GetInstance().GetPluginID(), *stream, forceEnglish, &nameH));
    return memHandleToString(nameH);
}

std::string StreamSuite::GetStreamUnitsText(StreamRefPtr stream, bool forceEnglish)
{
    CheckNotNull(*stream, "Error Getting Stream Units Text. Stream is Null");
    A_char *unitsText = nullptr;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetStreamUnitsText(
        *stream, forceEnglish, unitsText));
    return std::string(unitsText);
}

std::tuple<StreamFlag, double, double> StreamSuite::GetStreamProperties(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Stream Properties. Stream is Null");
    AEGP_StreamFlags flags;
    double minVal;
    double maxVal;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetStreamProperties(*stream, &flags,
                                                                                                    &minVal, &maxVal));
    return std::make_tuple(StreamFlag(flags), minVal, maxVal);
}

bool StreamSuite::IsStreamTimevarying(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Checking if Stream is Timevarying. Stream is Null");
    A_Boolean isTimeVarying;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_IsStreamTimevarying(*stream,
                                                                                                    &isTimeVarying));
    return static_cast<bool>(isTimeVarying);
}

StreamType StreamSuite::GetStreamType(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Stream Type. Stream is Null");
    AEGP_StreamType type;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetStreamType(*stream, &type));
    return StreamType(type);
}

StreamValue2Ptr StreamSuite::GetNewStreamValue(StreamRefPtr stream, LTimeMode timeMode, A_Time time, bool preExpression)
{
    CheckNotNull(*stream, "Error Getting New Stream Value. Stream is Null");
    AEGP_StreamValue2 value;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetNewStreamValue(
        *SuiteManager::GetInstance().GetPluginID(), *stream, AEGP_LTimeMode(timeMode), &time, preExpression, &value));
    return std::shared_ptr<AEGP_StreamValue2>(new AEGP_StreamValue2(value), StreamValueDeleter());
}

void StreamSuite::SetStreamValue(StreamRefPtr stream, StreamValue2Ptr value)
{
    CheckNotNull(*stream, "Error Setting Stream Value. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_SetStreamValue(
        *SuiteManager::GetInstance().GetPluginID(), *stream, value.get()));
}

std::tuple<AEGP_StreamVal2, StreamType> StreamSuite::GetLayerStreamValue(LayerPtr layer, LayerStream whichStream,
                                                                         LTimeMode timeMode, A_Time time,
                                                                         bool preExpression)
{
    CheckNotNull(*layer, "Error Getting Layer Stream Value. Layer is Null");
    AEGP_StreamVal2 value;
    AEGP_StreamType type;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetLayerStreamValue(
        *layer, AEGP_LayerStream(whichStream), AEGP_LTimeMode(timeMode), &time, preExpression, &value, &type));
    return std::make_tuple(value, StreamType(type));
}

StreamRefPtr StreamSuite::DuplicateStreamRef(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Duplicating Stream Ref. Stream is Null");
    AEGP_StreamRefH newStreamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_DuplicateStreamRef(
        *SuiteManager::GetInstance().GetPluginID(), *stream, &newStreamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(newStreamH), StreamRefDeleter());
}

int StreamSuite::GetUniqueStreamID(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Unique Stream ID. Stream is Null");
    int id;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetUniqueStreamID(*stream, &id));
    return id;
}

StreamRefPtr DynamicStreamSuite::GetNewStreamRefForLayer(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting New Stream Ref for Layer. Layer is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewStreamRefForLayer(
        *SuiteManager::GetInstance().GetPluginID(), *layer, &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

StreamRefPtr DynamicStreamSuite::GetNewStreamRefForMask(MaskRefPtr mask)
{
    CheckNotNull(*mask, "Error Getting New Stream Ref for Mask. Mask is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewStreamRefForMask(
        *SuiteManager::GetInstance().GetPluginID(), *mask, &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

int DynamicStreamSuite::GetStreamDepth(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Stream Depth. Stream is Null");
    int depth;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetStreamDepth(*stream, &depth));
    return depth;
}

StreamGroupingType DynamicStreamSuite::GetStreamGroupingType(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Stream Grouping Type. Stream is Null");
    AEGP_StreamGroupingType type;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetStreamGroupingType(*stream,
                                                                                                             &type));
    return StreamGroupingType(type);
}

int DynamicStreamSuite::GetNumStreamsInGroup(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Number of Streams in Group. Stream is Null");
    int numStreams;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNumStreamsInGroup(
        *stream, &numStreams));
    return numStreams;
}

DynStreamFlag DynamicStreamSuite::GetDynamicStreamFlags(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Dynamic Stream Flags. Stream is Null");
    AEGP_DynStreamFlags flags;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetDynamicStreamFlags(*stream,
                                                                                                             &flags));
    return DynStreamFlag(flags);
}

void DynamicStreamSuite::SetDynamicStreamFlag(StreamRefPtr stream, DynStreamFlag oneFlag, bool undoable, bool set)
{
    CheckNotNull(*stream, "Error Setting Dynamic Stream Flag. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_SetDynamicStreamFlag(
        *stream, AEGP_DynStreamFlags(oneFlag), undoable, set));
}

StreamRefPtr DynamicStreamSuite::GetNewStreamRefByIndex(StreamRefPtr parentGroup, int index)
{
    CheckNotNull(*parentGroup, "Error Getting New Stream Ref by Index. Parent Group is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewStreamRefByIndex(
        *SuiteManager::GetInstance().GetPluginID(), *parentGroup, index, &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

StreamRefPtr DynamicStreamSuite::GetNewStreamRefByMatchname(StreamRefPtr parentGroup, const std::string &matchName)
{
    CheckNotNull(*parentGroup, "Error Getting New Stream Ref by Matchname. Parent Group is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewStreamRefByMatchname(
        *SuiteManager::GetInstance().GetPluginID(), *parentGroup, matchName.c_str(), &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

void DynamicStreamSuite::DeleteStream(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Deleting Stream. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_DeleteStream(*stream));
}

void DynamicStreamSuite::ReorderStream(StreamRefPtr stream, int newIndex)
{
    CheckNotNull(*stream, "Error Reordering Stream. Stream is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_ReorderStream(*stream, newIndex));
}

int DynamicStreamSuite::DuplicateStream(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Duplicating Stream. Stream is Null");
    int newStreamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_DuplicateStream(
        *SuiteManager::GetInstance().GetPluginID(), *stream, &newStreamH));
    return newStreamH;
}

void DynamicStreamSuite::SetStreamName(StreamRefPtr stream, const std::string &newName)
{
    CheckNotNull(*stream, "Error Setting Stream Name. Stream is Null");
    std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(newName);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_SetStreamName(*stream,
                                                                                                     name16.data()));
}

bool DynamicStreamSuite::CanAddStream(StreamRefPtr parentGroup, const std::string &matchName)
{
    CheckNotNull(*parentGroup, "Error Checking if Can Add Stream. Parent Group is Null");
    A_Boolean canAdd;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_CanAddStream(
        *parentGroup, matchName.c_str(), &canAdd));
    return static_cast<bool>(canAdd);
}

StreamRefPtr DynamicStreamSuite::AddStream(StreamRefPtr parentGroup, const std::string &matchName)
{
    CheckNotNull(*parentGroup, "Error Adding Stream. Parent Group is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_AddStream(
        *SuiteManager::GetInstance().GetPluginID(), *parentGroup, matchName.c_str(), &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

std::string DynamicStreamSuite::GetMatchname(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Matchname. Stream is Null");
    A_char *matchname = nullptr;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetMatchName(*stream, matchname));
    return std::string(matchname);
}

StreamRefPtr DynamicStreamSuite::GetNewParentStreamRef(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting New Parent Stream Ref. Stream is Null");
    AEGP_StreamRefH parentStreamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewParentStreamRef(
        *SuiteManager::GetInstance().GetPluginID(), *stream, &parentStreamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(parentStreamH), StreamRefDeleter());
}

bool DynamicStreamSuite::GetStreamIsModified(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Stream is Modified. Stream is Null");
    A_Boolean isModified;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetStreamIsModified(
        *stream, &isModified));
    return static_cast<bool>(isModified);
}

bool DynamicStreamSuite::IsSeparationLeader(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Checking if Stream is Separation Leader. Stream is Null");
    A_Boolean isLeader;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_IsSeparationLeader(*stream,
                                                                                                          &isLeader));
    return static_cast<bool>(isLeader);
}

bool DynamicStreamSuite::AreDimensionsSeparated(StreamRefPtr leaderStream)
{
    CheckNotNull(*leaderStream, "Error Checking if Dimensions are Separated. Leader Stream is Null");
    A_Boolean areSeparated;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_AreDimensionsSeparated(
        *leaderStream, &areSeparated));
    return static_cast<bool>(areSeparated);
}

void DynamicStreamSuite::SetDimensionsSeparated(StreamRefPtr leaderStream, bool separated)
{
    CheckNotNull(*leaderStream, "Error Setting Dimensions Separated. Leader Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_SetDimensionsSeparated(
        *leaderStream, separated));
}

StreamRefPtr DynamicStreamSuite::GetSeparationFollower(int dimension, StreamRefPtr leaderStream)
{
    CheckNotNull(*leaderStream, "Error Getting Separation Follower. Leader Stream is Null");
    AEGP_StreamRefH followerStreamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetSeparationFollower(
        *leaderStream, dimension, &followerStreamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(followerStreamH), StreamRefDeleter());
}

bool DynamicStreamSuite::IsSeparationFollower(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Checking if Stream is Separation Follower. Stream is Null");
    A_Boolean isFollower;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_IsSeparationFollower(
        *stream, &isFollower));
    return static_cast<bool>(isFollower);
}

StreamRefPtr DynamicStreamSuite::GetSeparationLeader(StreamRefPtr followerStream)
{
    CheckNotNull(*followerStream, "Error Getting Separation Leader. Follower Stream is Null");
    AEGP_StreamRefH leaderStreamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetSeparationLeader(
        *followerStream, &leaderStreamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(leaderStreamH), StreamRefDeleter());
}

A_short DynamicStreamSuite::GetSeparationDimension(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Separation Dimension. Stream is Null");
    A_short dimension;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetSeparationDimension(
        *stream, &dimension));
    return dimension;
}

int KeyframeSuite::GetStreamNumKFs(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Stream Number of Keyframes. Stream is Null");
    int numKFs;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetStreamNumKFs(*stream, &numKFs));
    return numKFs;
}

A_Time KeyframeSuite::GetKeyframeTime(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, LTimeMode timeMode)
{
    CheckNotNull(*stream, "Error Getting Keyframe Time. Stream is Null");
    A_Time time;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeTime(
        *stream, keyIndex, AEGP_LTimeMode(timeMode), &time));
    return time;
}

AEGP_KeyframeIndex KeyframeSuite::InsertKeyframe(StreamRefPtr stream, LTimeMode timeMode, const A_Time &time)
{
    CheckNotNull(*stream, "Error Inserting Keyframe. Stream is Null");
    AEGP_KeyframeIndex keyIndex;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_InsertKeyframe(
        *stream, AEGP_LTimeMode(timeMode), &time, &keyIndex));
    return keyIndex;
}

void KeyframeSuite::DeleteKeyframe(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(*stream, "Error Deleting Keyframe. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_DeleteKeyframe(*stream, keyIndex));
}

StreamValue2Ptr KeyframeSuite::GetNewKeyframeValue(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(*stream, "Error Getting New Keyframe Value. Stream is Null");
    AEGP_StreamValue2 value;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetNewKeyframeValue(
        *SuiteManager::GetInstance().GetPluginID(), *stream, keyIndex, &value));
    return std::shared_ptr<AEGP_StreamValue2>(new AEGP_StreamValue2(value), StreamValueDeleter());
}

void KeyframeSuite::SetKeyframeValue(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, StreamValue2Ptr value)
{
    CheckNotNull(*stream, "Error Setting Keyframe Value. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeValue(*stream, keyIndex,
                                                                                                   &*value));
}

A_short KeyframeSuite::GetStreamValueDimensionality(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Stream Value Dimensionality. Stream is Null");
    A_short dimension;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetStreamValueDimensionality(
        *stream, &dimension));
    return dimension;
}

A_short KeyframeSuite::GetStreamTemporalDimensionality(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Getting Stream Temporal Dimensionality. Stream is Null");
    A_short dimension;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetStreamTemporalDimensionality(
        *stream, &dimension));
    return dimension;
}

std::tuple<StreamValue2Ptr, StreamValue2Ptr> KeyframeSuite::GetNewKeyframeSpatialTangents(StreamRefPtr stream,
                                                                                          AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(*stream, "Error Getting New Keyframe Spatial Tangents. Stream is Null");
    AEGP_StreamValue2 inTan;
    AEGP_StreamValue2 outTan;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetNewKeyframeSpatialTangents(
        *SuiteManager::GetInstance().GetPluginID(), *stream, keyIndex, &inTan, &outTan));
    return std::make_tuple(std::shared_ptr<AEGP_StreamValue2>(new AEGP_StreamValue2(inTan), StreamValueDeleter()),
						   std::shared_ptr<AEGP_StreamValue2>(new AEGP_StreamValue2(outTan), StreamValueDeleter()));
}

void KeyframeSuite::SetKeyframeSpatialTangents(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, StreamValue2Ptr inTan,
                                               StreamValue2Ptr outTan)
{
    CheckNotNull(*stream, "Error Setting Keyframe Spatial Tangents. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeSpatialTangents(
        *stream, keyIndex, &*inTan, &*outTan));
}

std::tuple<KeyframeEase, KeyframeEase>
KeyframeSuite::GetKeyframeTemporalEase(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, int dimension)
{
    CheckNotNull(*stream, "Error Getting Keyframe Temporal Ease. Stream is Null");
    AEGP_KeyframeEase inEase;
    AEGP_KeyframeEase outEase;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeTemporalEase(
        *stream, keyIndex, dimension, &inEase, &outEase));
    return std::make_tuple(KeyframeEase(inEase), KeyframeEase(outEase));
}

void KeyframeSuite::SetKeyframeTemporalEase(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, int dimension,
                                            KeyframeEase inEase, KeyframeEase outEase)
{
    CheckNotNull(*stream, "Error Setting Keyframe Temporal Ease. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeTemporalEase(
        *stream, keyIndex, dimension, &inEase.ToAEGPKeyframeEase(), &outEase.ToAEGPKeyframeEase()));
}

KeyframeFlag KeyframeSuite::GetKeyframeFlags(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(*stream, "Error Getting Keyframe Flags. Stream is Null");
    AEGP_KeyframeFlags flags;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeFlags(*stream, keyIndex,
                                                                                                   &flags));
    return KeyframeFlag(flags);
}

void KeyframeSuite::SetKeyframeFlag(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, KeyframeFlag flag, bool value)
{
    CheckNotNull(*stream, "Error Setting Keyframe Flag. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeFlag(
        *stream, keyIndex, AEGP_KeyframeFlags(flag), value));
}

std::tuple<KeyInterp, KeyInterp> KeyframeSuite::GetKeyframeInterpolation(StreamRefPtr stream,
                                                                         AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(*stream, "Error Getting Keyframe Interpolation. Stream is Null");
    int inInterp;
    int outInterp;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeInterpolation(
        *stream, keyIndex, &inInterp, &outInterp));
    return std::make_tuple(KeyInterp(inInterp), KeyInterp(outInterp));
}

void KeyframeSuite::SetKeyframeInterpolation(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, KeyInterp inInterp,
                                             KeyInterp outInterp)
{
    CheckNotNull(*stream, "Error Setting Keyframe Interpolation. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeInterpolation(
        *stream, keyIndex, int(inInterp), int(outInterp)));
}

AddKeyframesInfoPtr KeyframeSuite::StartAddKeyframes(StreamRefPtr stream)
{
    CheckNotNull(*stream, "Error Starting Add Keyframes. Stream is Null");
    AEGP_AddKeyframesInfoH akH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_StartAddKeyframes(*stream, &akH));
    return std::shared_ptr<AEGP_AddKeyframesInfoH>(new AEGP_AddKeyframesInfoH(akH), AddKeyframesInfoDeleter());
}

AEGP_KeyframeIndex KeyframeSuite::AddKeyframes(AddKeyframesInfoPtr akH, LTimeMode timeMode, const A_Time &time)
{
    CheckNotNull(*akH, "Error Adding Keyframes. Add Keyframes Info is Null");
    AEGP_KeyframeIndex keyIndex;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_AddKeyframes(
        *akH, AEGP_LTimeMode(timeMode), &time, &keyIndex));
    return keyIndex;
}

void KeyframeSuite::SetAddKeyframe(AddKeyframesInfoPtr akH, AEGP_KeyframeIndex keyIndex, StreamValue2Ptr value)
{
    CheckNotNull(*akH, "Error Setting Add Keyframe. Add Keyframes Info is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetAddKeyframe(*akH, keyIndex, &*value));
}

void KeyframeSuite::EndAddKeyframes(AddKeyframesInfoPtr akH)
{
    CheckNotNull(*akH, "Error Ending Add Keyframes. Add Keyframes Info is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_EndAddKeyframes(true, *akH));
}

int KeyframeSuite::GetKeyframeLabelColorIndex(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex)
{
    CheckNotNull(*stream, "Error Getting Keyframe Label Color Index. Stream is Null");
    int keyLabel;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeLabelColorIndex(
        *stream, keyIndex, &keyLabel));
    return keyLabel;
}

void KeyframeSuite::SetKeyframeLabelColorIndex(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, int keyLabel)
{
    CheckNotNull(*stream, "Error Setting Keyframe Label Color Index. Stream is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeLabelColorIndex(
        *stream, keyIndex, keyLabel));
}

std::string TextDocumentSuite::getNewText(TextDocumentPtr text_documentH)
{
    CheckNotNull(*text_documentH, "Error Getting New Text. Text Document is Null");
    AEGP_MemHandle textH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().TextDocumentSuite1()->AEGP_GetNewText(
        *SuiteManager::GetInstance().GetPluginID(), *text_documentH, &textH));
    return memHandleToString(textH);
}

void TextDocumentSuite::setText(TextDocumentPtr text_documentH, const std::string &unicodePS)
{
    CheckNotNull(*text_documentH, "Error Setting Text. Text Document is Null");
    const A_u_short *unicodeP = ConvertUTF8ToUTF16(unicodePS).data();
    int lengthL = static_cast<int>(unicodePS.size());
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().TextDocumentSuite1()->AEGP_SetText(*text_documentH, unicodeP,
                                                                                              lengthL));
}

MarkerValPtr MarkerSuite::getNewMarker()
{
    AEGP_MarkerValP markerP;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_NewMarker(&markerP));
    return std::shared_ptr<AEGP_MarkerValP>(new AEGP_MarkerValP(markerP), MarkerDeleter());
}

MarkerValPtr MarkerSuite::duplicateMarker(MarkerValPtr markerP)
{
    CheckNotNull(*markerP, "Error Duplicating Marker. Marker is Null");
    AEGP_MarkerValP newMarkerP;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_DuplicateMarker(*markerP, &newMarkerP));
    return std::shared_ptr<AEGP_MarkerValP>(new AEGP_MarkerValP(newMarkerP), MarkerDeleter());
}

void MarkerSuite::setMarkerFlag(MarkerValPtr markerP, AEGP_MarkerFlagType flagType, bool valueB)
{
    CheckNotNull(*markerP, "Error Setting Marker Flag. Marker is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerFlag(*markerP, flagType, valueB));
}

bool MarkerSuite::getMarkerFlag(MarkerValPtr markerP, AEGP_MarkerFlagType flagType)
{
    CheckNotNull(*markerP, "Error Getting Marker Flag. Marker is Null");
    A_Boolean valueB;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerFlag(*markerP, flagType, &valueB));
    return static_cast<bool>(valueB);
}

std::string MarkerSuite::getMarkerString(MarkerValPtr markerP, MarkerStringType strType)
{
    CheckNotNull(*markerP, "Error Getting Marker String. Marker is Null");
    AEGP_MemHandle stringH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerString(
        *SuiteManager::GetInstance().GetPluginID(), *markerP, AEGP_MarkerStringType(strType), &stringH));
    return memHandleToString(stringH);
}

void MarkerSuite::setMarkerString(MarkerValPtr markerP, MarkerStringType strType, const std::string &unicodeP)
{
    CheckNotNull(*markerP, "Error Setting Marker String. Marker is Null");
    const A_u_short *unicodeP16 = ConvertUTF8ToUTF16(unicodeP).data();
    int lengthL = static_cast<int>(unicodeP.size());
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerString(
        *markerP, AEGP_MarkerStringType(strType), unicodeP16, lengthL));
}

int MarkerSuite::countCuePointParams(MarkerValPtr markerP)
{
    CheckNotNull(*markerP, "Error Counting Cue Point Params. Marker is Null");
    int countL;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_CountCuePointParams(*markerP, &countL));
    return countL;
}

std::tuple<std::string, std::string> MarkerSuite::getIndCuePointParam(MarkerValPtr markerP, int param_indexL)
{
    CheckNotNull(*markerP, "Error Getting Ind Cue Point Param. Marker is Null");
    AEGP_MemHandle keyH;
    AEGP_MemHandle valueH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetIndCuePointParam(
        *SuiteManager::GetInstance().GetPluginID(), *markerP, param_indexL, &keyH, &valueH));
    return std::make_tuple(memHandleToString(keyH), memHandleToString(valueH));
}

void MarkerSuite::setIndCuePointParam(MarkerValPtr markerP, int param_indexL, const std::string &unicodeKeyP,
                                      const std::string &unicodeValueP)
{
    CheckNotNull(*markerP, "Error Setting Ind Cue Point Param. Marker is Null");
    const A_u_short *unicodeKeyP16 = ConvertUTF8ToUTF16(unicodeKeyP).data();
    int key_lengthL = static_cast<int>(unicodeKeyP.size());
    const A_u_short *unicodeValueP16 = ConvertUTF8ToUTF16(unicodeValueP).data();
    int value_lengthL = static_cast<int>(unicodeValueP.size());
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetIndCuePointParam(
        *markerP, param_indexL, unicodeKeyP16, key_lengthL, unicodeValueP16, value_lengthL));
}

void MarkerSuite::insertCuePointParam(MarkerValPtr markerP, int param_indexL)
{
    CheckNotNull(*markerP, "Error Inserting Cue Point Param. Marker is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_InsertCuePointParam(*markerP, param_indexL));
}

void MarkerSuite::deleteIndCuePointParam(MarkerValPtr markerP, int param_indexL)
{
    CheckNotNull(*markerP, "Error Deleting Ind Cue Point Param. Marker is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_DeleteIndCuePointParam(*markerP,
                                                                                                       param_indexL));
}

void MarkerSuite::setMarkerDuration(MarkerValPtr markerP, const A_Time &durationPT)
{
    CheckNotNull(*markerP, "Error Setting Marker Duration. Marker is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerDuration(*markerP, &durationPT));
}

A_Time MarkerSuite::getMarkerDuration(MarkerValPtr markerP)
{
    CheckNotNull(*markerP, "Error Getting Marker Duration. Marker is Null");
    A_Time durationT;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerDuration(*markerP, &durationT));
    return durationT;
}

void MarkerSuite::setMarkerLabel(MarkerValPtr markerP, int value)
{
    CheckNotNull(*markerP, "Error Setting Marker Label. Marker is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerLabel(*markerP, value));
}

int MarkerSuite::getMarkerLabel(MarkerValPtr markerP)
{
    CheckNotNull(*markerP, "Error Getting Marker Label. Marker is Null");
    int labelL;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerLabel(*markerP, &labelL));
    return labelL;
}

TextOutlinesPtr TextLayerSuite::getNewTextOutlines(LayerPtr layer, const A_Time &layer_time)
{
    CheckNotNull(*layer, "Error Getting New Text Outlines. Layer is Null");
    AEGP_TextOutlinesH outlinesH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().TextLayerSuite1()->AEGP_GetNewTextOutlines(
        *layer, &layer_time, &outlinesH));
    return std::shared_ptr<AEGP_TextOutlinesH>(new AEGP_TextOutlinesH(outlinesH), TextOutlineDeleter());
}

int TextLayerSuite::getNumTextOutlines(TextOutlinesPtr outlines)
{
    CheckNotNull(*outlines, "Error Getting Number of Text Outlines. Outlines is Null");
    int numOutlines;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().TextLayerSuite1()->AEGP_GetNumTextOutlines(*outlines,
                                                                                                      &numOutlines));
    return numOutlines;
}

PF_PathOutlinePtr TextLayerSuite::getIndexedTextOutline(TextOutlinesPtr outlines, int path_index)
{
    return PF_PathOutlinePtr();
}

int EffectSuite::getLayerNumEffects(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Getting Layer Number of Effects. Layer is Null");
    int numEffects;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetLayerNumEffects(*layer, &numEffects));
    return numEffects;
}

EffectRefPtr EffectSuite::getLayerEffectByIndex(LayerPtr layer, AEGP_EffectIndex layer_effect_index)
{
    CheckNotNull(*layer, "Error Getting Layer Effect by Index. Layer is Null");
    AEGP_EffectRefH effectH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetLayerEffectByIndex(
        *SuiteManager::GetInstance().GetPluginID(), *layer, layer_effect_index, &effectH));
    return std::shared_ptr<AEGP_EffectRefH>(new AEGP_EffectRefH(effectH), EffectDeleter());
}

AEGP_InstalledEffectKey EffectSuite::getInstalledKeyFromLayerEffect(EffectRefPtr effect_ref)
{
    CheckNotNull(*effect_ref, "Error Getting Installed Key from Layer Effect. Effect is Null");
    AEGP_InstalledEffectKey key;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetInstalledKeyFromLayerEffect(
        *effect_ref, &key));
    return key;
}

std::tuple<PF_ParamType, PF_ParamDefUnion> EffectSuite::getEffectParamUnionByIndex(EffectRefPtr effect_ref,
                                                                                   PF_ParamIndex param_index)
{
    CheckNotNull(*effect_ref, "Error Getting Effect Param Union by Index. Effect is Null");
    PF_ParamType type;
    PF_ParamDefUnion def;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectParamUnionByIndex(
        *SuiteManager::GetInstance().GetPluginID(), *effect_ref, param_index, &type, &def));
    return std::make_tuple(type, def);
}

EffectFlags EffectSuite::getEffectFlags(EffectRefPtr effect_ref)
{
    CheckNotNull(*effect_ref, "Error Getting Effect Flags. Effect is Null");
    AEGP_EffectFlags flags;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectFlags(*effect_ref, &flags));
    return EffectFlags(flags);
}

void EffectSuite::setEffectFlags(EffectRefPtr effect_ref, EffectFlags effect_flags_set_mask, EffectFlags effect_flags)
{
    CheckNotNull(*effect_ref, "Error Setting Effect Flags. Effect is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_SetEffectFlags(
        *effect_ref, AEGP_EffectFlags(effect_flags_set_mask), AEGP_EffectFlags(effect_flags)));
}

void EffectSuite::reorderEffect(EffectRefPtr effect_ref, int effect_index)
{
    CheckNotNull(*effect_ref, "Error Reordering Effect. Effect is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_ReorderEffect(*effect_ref, effect_index));
}

void EffectSuite::effectCallGeneric(EffectRefPtr effect_ref, const A_Time *timePT, PF_Cmd effect_cmd,
                                    void *effect_extraPV)
{
    CheckNotNull(*effect_ref, "Error Effect Call Generic. Effect is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_EffectCallGeneric(
        *SuiteManager::GetInstance().GetPluginID(), *effect_ref, timePT, effect_cmd, effect_extraPV));
}

EffectRefPtr EffectSuite::applyEffect(LayerPtr layer, AEGP_InstalledEffectKey installed_effect_key)
{
    CheckNotNull(*layer, "Error Applying Effect. Layer is Null");
    AEGP_EffectRefH effectH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_ApplyEffect(
        *SuiteManager::GetInstance().GetPluginID(), *layer, installed_effect_key, &effectH));
    return std::shared_ptr<AEGP_EffectRefH>(new AEGP_EffectRefH(effectH), EffectDeleter());
}

void EffectSuite::deleteLayerEffect(EffectRefPtr effect_ref)
{
    CheckNotNull(*effect_ref, "Error Deleting Layer Effect. Effect is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_DeleteLayerEffect(*effect_ref));
}

int EffectSuite::getNumInstalledEffects()
{
    int numEffects;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetNumInstalledEffects(&numEffects));
    return numEffects;
}

AEGP_InstalledEffectKey EffectSuite::getNextInstalledEffect(AEGP_InstalledEffectKey installed_effect_key)
{
    AEGP_InstalledEffectKey nextKey;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetNextInstalledEffect(
        installed_effect_key, &nextKey));
    return nextKey;
}

std::string EffectSuite::getEffectName(AEGP_InstalledEffectKey installed_effect_key)
{
    A_char *nameP = nullptr;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectName(installed_effect_key, nameP));
    return std::string(nameP);
}

std::string EffectSuite::getEffectMatchName(AEGP_InstalledEffectKey installed_effect_key)
{
    A_char *matchNameP = nullptr;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectMatchName(installed_effect_key,
                                                                                                   matchNameP));
    return std::string(matchNameP);
}

std::string EffectSuite::getEffectCategory(AEGP_InstalledEffectKey installed_effect_key)
{
    A_char *categoryP = nullptr;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectCategory(installed_effect_key,
                                                                                                  categoryP));
    return std::string(categoryP);
}

EffectRefPtr EffectSuite::duplicateEffect(EffectRefPtr original_effect_ref)
{
    CheckNotNull(*original_effect_ref, "Error Duplicating Effect. Original Effect is Null");
    AEGP_EffectRefH newEffectH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_DuplicateEffect(*original_effect_ref,
                                                                                                &newEffectH));
    return std::shared_ptr<AEGP_EffectRefH>(new AEGP_EffectRefH(newEffectH), EffectDeleter());
}

A_u_long EffectSuite::numEffectMask(EffectRefPtr effect_ref)
{
    CheckNotNull(*effect_ref, "Error Getting Number of Effect Masks. Effect is Null");
    A_u_long numMasks;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_NumEffectMask(*effect_ref, &numMasks));
    return numMasks;
}

AEGP_MaskIDVal EffectSuite::getEffectMaskID(EffectRefPtr effect_ref, A_u_long mask_indexL)
{
    CheckNotNull(*effect_ref, "Error Getting Effect Mask ID. Effect is Null");
    AEGP_MaskIDVal id;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectMaskID(*effect_ref,
                                                                                                mask_indexL, &id));
    return id;
}

StreamRefPtr EffectSuite::addEffectMask(EffectRefPtr effect_ref, AEGP_MaskIDVal id_val)
{
    CheckNotNull(*effect_ref, "Error Adding Effect Mask. Effect is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_AddEffectMask(*effect_ref, id_val,
                                                                                              &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

void EffectSuite::removeEffectMask(EffectRefPtr effect_ref, AEGP_MaskIDVal id_val)
{
    CheckNotNull(*effect_ref, "Error Removing Effect Mask. Effect is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_RemoveEffectMask(*effect_ref, id_val));
}

StreamRefPtr EffectSuite::setEffectMask(EffectRefPtr effect_ref, A_u_long mask_indexL, AEGP_MaskIDVal id_val)
{
    CheckNotNull(*effect_ref, "Error Setting Effect Mask. Effect is Null");
    AEGP_StreamRefH streamH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_SetEffectMask(*effect_ref, mask_indexL,
                                                                                              id_val, &streamH));
    return std::shared_ptr<AEGP_StreamRefH>(new AEGP_StreamRefH(streamH), StreamRefDeleter());
}

int MaskSuite::getLayerNumMasks(LayerPtr aegp_layerH)
{
    CheckNotNull(*aegp_layerH, "Error Getting Layer Number of Masks. Layer is Null");
    int numMasks;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetLayerNumMasks(*aegp_layerH, &numMasks));
    return numMasks;
}

MaskRefPtr MaskSuite::getLayerMaskByIndex(LayerPtr aegp_layerH, AEGP_MaskIndex mask_indexL)
{
    CheckNotNull(*aegp_layerH, "Error Getting Layer Mask by Index. Layer is Null");
    AEGP_MaskRefH maskH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetLayerMaskByIndex(*aegp_layerH,
                                                                                                  mask_indexL, &maskH));
    return std::shared_ptr<AEGP_MaskRefH>(new AEGP_MaskRefH(maskH), MaskDeleter());
}

bool MaskSuite::getMaskInvert(MaskRefPtr mask_refH)
{
    CheckNotNull(*mask_refH, "Error Getting Mask Invert. Mask is Null");
    A_Boolean invertB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskInvert(*mask_refH, &invertB));
    return static_cast<bool>(invertB);
}

void MaskSuite::setMaskInvert(MaskRefPtr mask_refH, bool invertB)
{
    CheckNotNull(*mask_refH, "Error Setting Mask Invert. Mask is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskInvert(*mask_refH, invertB));
}

MaskMode MaskSuite::getMaskMode(MaskRefPtr mask_refH)
{
    CheckNotNull(*mask_refH, "Error Getting Mask Mode. Mask is Null");
    PF_MaskMode mode;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskMode(*mask_refH, &mode));
    return MaskMode(mode);
}

void MaskSuite::setMaskMode(MaskRefPtr maskH, MaskMode mode)
{
    CheckNotNull(*maskH, "Error Setting Mask Mode. Mask is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskMode(*maskH, PF_MaskMode(mode)));
}

MaskMBlur MaskSuite::getMaskMotionBlurState(MaskRefPtr mask_refH)
{
    CheckNotNull(*mask_refH, "Error Getting Mask Motion Blur State. Mask is Null");
    AEGP_MaskMBlur blur_state;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskMotionBlurState(*mask_refH,
                                                                                                     &blur_state));
    return MaskMBlur(blur_state);
}

void MaskSuite::setMaskMotionBlurState(MaskRefPtr mask_refH, MaskMBlur blur_state)
{
    CheckNotNull(*mask_refH, "Error Setting Mask Motion Blur State. Mask is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskMotionBlurState(
        *mask_refH, AEGP_MaskMBlur(blur_state)));
}

MaskFeatherFalloff MaskSuite::getMaskFeatherFalloff(MaskRefPtr mask_refH)
{
    CheckNotNull(*mask_refH, "Error Getting Mask Feather Falloff. Mask is Null");
    AEGP_MaskFeatherFalloff feather_falloff;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskFeatherFalloff(*mask_refH,
                                                                                                    &feather_falloff));
    return MaskFeatherFalloff(feather_falloff);
}

void MaskSuite::setMaskFeatherFalloff(MaskRefPtr mask_refH, MaskFeatherFalloff feather_falloffP)
{
    CheckNotNull(*mask_refH, "Error Setting Mask Feather Falloff. Mask is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskFeatherFalloff(
        *mask_refH, AEGP_MaskFeatherFalloff(feather_falloffP)));
}

AEGP_MaskIDVal MaskSuite::getMaskID(MaskRefPtr mask_refH)
{
    CheckNotNull(*mask_refH, "Error Getting Mask ID. Mask is Null");
    AEGP_MaskIDVal id;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskID(*mask_refH, &id));
    return id;
}

MaskRefPtr MaskSuite::createNewMask(LayerPtr layerH, int mask_indexPL0)
{
    CheckNotNull(*layerH, "Error Creating New Mask. Layer is Null");
    AEGP_MaskRefH maskH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_CreateNewMask(*layerH, &maskH,
                                                                                            &mask_indexPL0));
    return std::shared_ptr<AEGP_MaskRefH>(new AEGP_MaskRefH(maskH), MaskDeleter());
}

void MaskSuite::deleteMaskFromLayer(MaskRefPtr mask_refH)
{
    CheckNotNull(*mask_refH, "Error Deleting Mask from Layer. Mask is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_DeleteMaskFromLayer(*mask_refH));
}

ColorVal MaskSuite::getMaskColor(MaskRefPtr mask_refH)
{
    CheckNotNull(*mask_refH, "Error Getting Mask Color. Mask is Null");
    AEGP_ColorVal color;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskColor(*mask_refH, &color));
    return ColorVal(color);
}

void MaskSuite::setMaskColor(MaskRefPtr mask_refH, ColorVal colorP)
{
    CheckNotNull(*mask_refH, "Error Setting Mask Color. Mask is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskColor(*mask_refH,
                                                                                           &colorP.ToAEGPColorVal()));
}

bool MaskSuite::getMaskLockState(MaskRefPtr mask_refH)
{
    CheckNotNull(*mask_refH, "Error Getting Mask Lock State. Mask is Null");
    A_Boolean lockB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskLockState(*mask_refH, &lockB));
    return static_cast<bool>(lockB);
}

void MaskSuite::setMaskLockState(MaskRefPtr mask_refH, bool lockB)
{
    CheckNotNull(*mask_refH, "Error Setting Mask Lock State. Mask is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskLockState(*mask_refH, lockB));
}

bool MaskSuite::getMaskIsRotoBezier(MaskRefPtr mask_refH)
{
    CheckNotNull(*mask_refH, "Error Getting Mask Is Roto Bezier. Mask is Null");
    A_Boolean is_roto_bezierB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskIsRotoBezier(*mask_refH,
                                                                                                  &is_roto_bezierB));
    return static_cast<bool>(is_roto_bezierB);
}

void MaskSuite::setMaskIsRotoBezier(MaskRefPtr mask_refH, bool is_roto_bezierB)
{
    CheckNotNull(*mask_refH, "Error Setting Mask Is Roto Bezier. Mask is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskIsRotoBezier(*mask_refH,
                                                                                                  is_roto_bezierB));
}

MaskRefPtr MaskSuite::duplicateMask(MaskRefPtr orig_mask_refH)
{
    CheckNotNull(*orig_mask_refH, "Error Duplicating Mask. Original Mask is Null");
    AEGP_MaskRefH new_maskH;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_DuplicateMask(*orig_mask_refH, &new_maskH));
    return std::shared_ptr<AEGP_MaskRefH>(new AEGP_MaskRefH(new_maskH), MaskDeleter());
}

bool MaskOutlineSuite::isMaskOutlineOpen(MaskOutlineValPtr mask_outlineH)
{
    CheckNotNull(*mask_outlineH, "Error Checking if Mask Outline is Open. Mask Outline is Null");
    A_Boolean openB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_IsMaskOutlineOpen(*mask_outlineH,
                                                                                                       &openB));
    return static_cast<bool>(openB);
}

void MaskOutlineSuite::setMaskOutlineOpen(MaskOutlineValPtr mask_outlineH, bool openB)
{
    CheckNotNull(*mask_outlineH, "Error Setting Mask Outline Open. Mask Outline is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_SetMaskOutlineOpen(*mask_outlineH,
                                                                                                        openB));
}

int MaskOutlineSuite::getMaskOutlineNumSegments(MaskOutlineValPtr mask_outlineH)
{
    CheckNotNull(*mask_outlineH, "Error Getting Mask Outline Number of Segments. Mask Outline is Null");
    int numSegmentsL;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_GetMaskOutlineNumSegments(
        *mask_outlineH, &numSegmentsL));
    return numSegmentsL;
}

MaskVertex MaskOutlineSuite::getMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_pointL)
{
    AEGP_MaskVertex vertex;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_GetMaskOutlineVertexInfo(
        *mask_outlineH, which_pointL, &vertex));
    return MaskVertex(vertex);
}

void MaskOutlineSuite::setMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_pointL,
                                                MaskVertex vertexP)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_SetMaskOutlineVertexInfo(
        *mask_outlineH, which_pointL, &vertexP.ToAEGPMaskVertex()));
}

void MaskOutlineSuite::createVertex(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex insert_position)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_CreateVertex(*mask_outlineH,
                                                                                                  insert_position));
}

void MaskOutlineSuite::deleteVertex(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex index)
{
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_DeleteVertex(*mask_outlineH, index));
}

int MaskOutlineSuite::getMaskOutlineNumFeathers(MaskOutlineValPtr mask_outlineH)
{
    int numFeathersL;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_GetMaskOutlineNumFeathers(
        *mask_outlineH, &numFeathersL));
    return numFeathersL;
}

MaskFeather MaskOutlineSuite::getMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH,
                                                        AEGP_FeatherIndex which_featherL)
{
    AEGP_MaskFeather feather;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_GetMaskOutlineFeatherInfo(
        *mask_outlineH, which_featherL, &feather));
    return MaskFeather(feather);
}

void MaskOutlineSuite::setMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_featherL,
                                                 MaskFeather featherP)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_SetMaskOutlineFeatherInfo(
        *mask_outlineH, which_featherL, &featherP.ToAEGPMaskFeather()));
}

AEGP_FeatherIndex MaskOutlineSuite::createMaskOutlineFeather(MaskOutlineValPtr mask_outlineH, MaskFeather featherP0)
{
    AEGP_FeatherIndex index;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_CreateMaskOutlineFeather(
        *mask_outlineH, &featherP0.ToAEGPMaskFeather(), &index));
    return index;
}

void MaskOutlineSuite::deleteMaskOutlineFeather(MaskOutlineValPtr mask_outlineH, AEGP_FeatherIndex index)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_DeleteMaskOutlineFeather(
        *mask_outlineH, index));
}

// FootageSuite5

FootagePtr FootageSuite::getMainFootageFromItem(ItemPtr itemH)
{
    CheckNotNull(*itemH, "Error Getting Main Footage from Item. Item is Null");
    AEGP_FootageH footageH;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetMainFootageFromItem(*itemH, &footageH));
    return std::shared_ptr<AEGP_FootageH>(new AEGP_FootageH(footageH), FootageDeleter());
}

FootagePtr FootageSuite::getProxyFootageFromItem(ItemPtr itemH)
{
    CheckNotNull(*itemH, "Error Getting Proxy Footage from Item. Item is Null");
    AEGP_FootageH footageH;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetProxyFootageFromItem(*itemH, &footageH));
    return std::shared_ptr<AEGP_FootageH>(new AEGP_FootageH(footageH), FootageDeleter());
}

std::tuple<int, int> FootageSuite::getFootageNumFiles(FootagePtr footageH)
{
    CheckNotNull(*footageH, "Error Getting Footage Number of Files. Footage is Null");
    int num_filesL;
    int num_framesL;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageNumFiles(
        *footageH, &num_filesL, &num_framesL));
    return std::make_tuple(num_filesL, num_framesL);
}

std::string FootageSuite::getFootagePath(FootagePtr footageH, int frame_numL, int file_indexL)
{
    CheckNotNull(*footageH, "Error Getting Footage Path. Footage is Null");
    AEGP_MemHandle pathH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootagePath(*footageH, frame_numL,
                                                                                                file_indexL, &pathH));
    return memHandleToString(pathH);
}

AEGP_FootageSignature FootageSuite::getFootageSignature(FootagePtr footageH)
{
    CheckNotNull(*footageH, "Error Getting Footage Signature. Footage is Null");
    AEGP_FootageSignature signature;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageSignature(*footageH, &signature));
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
FootagePtr FootageSuite::newFootage(

    std::string pathZ, AEGP_FootageLayerKey layer_infoP0, AEGP_FileSequenceImportOptions *sequence_optionsP0,
    InterpretationStyle interp_style)
{
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(pathZ);
    AEGP_FootageH footageH;
    if (sequence_optionsP0 == NULL)
    {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewFootage(
            *SuiteManager::GetInstance().GetPluginID(), path16.data(), &layer_infoP0, NULL,
            AEGP_InterpretationStyle(interp_style), NULL, &footageH));
    }
    else
    {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewFootage(
            *SuiteManager::GetInstance().GetPluginID(), path16.data(), &layer_infoP0, sequence_optionsP0,
            AEGP_InterpretationStyle(interp_style), NULL, &footageH));
    }
    return std::shared_ptr<AEGP_FootageH>(new AEGP_FootageH(footageH), FootageDeleter());
}

ItemPtr FootageSuite::addFootageToProject(FootagePtr footageH, ItemPtr folderH)
{
    CheckNotNull(*footageH, "Error Adding Footage to Project. Footage is Null");
    if (!folderH)
    {
        folderH = ProjSuite().GetProjectRootFolder(ProjSuite().GetProjectByIndex(0));
    }
    FootagePtr footageH2 = std::make_shared<AEGP_FootageH>(*footageH);
    AEGP_ItemH itemH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_AddFootageToProject(*footageH2,
                                                                                                     *folderH, &itemH));
    return std::make_shared<AEGP_ItemH>(itemH);
}

void FootageSuite::setItemProxyFootage(FootagePtr footageH, ItemPtr itemH)
{
    CheckNotNull(*footageH, "Error Setting Item Proxy Footage. Footage is Null");
    CheckNotNull(*itemH, "Error Setting Item Proxy Footage. Item is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_SetItemProxyFootage(*footageH, *itemH));
}

void FootageSuite::replaceItemMainFootage(FootagePtr footageH, ItemPtr itemH)
{
    CheckNotNull(*footageH, "Error Replacing Item Main Footage. Footage is Null");
    CheckNotNull(*itemH, "Error Replacing Item Main Footage. Item is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_ReplaceItemMainFootage(*footageH, *itemH));
}

AEGP_FootageInterp FootageSuite::getFootageInterpretation(ItemPtr itemH, bool proxyB)
{
    CheckNotNull(*itemH, "Error Getting Footage Interpretation. Item is Null");
    AEGP_FootageInterp interp;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageInterpretation(
        *itemH, proxyB, &interp));
    return interp;
}

void FootageSuite::setFootageInterpretation(ItemPtr itemH, bool proxyB, const AEGP_FootageInterp *interpP)
{
    CheckNotNull(*itemH, "Error Setting Footage Interpretation. Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_SetFootageInterpretation(
        *itemH, proxyB, interpP));
}

AEGP_FootageLayerKey FootageSuite::getFootageLayerKey(FootagePtr footageH)
{
    CheckNotNull(*footageH, "Error Getting Footage Layer Key. Footage is Null");
    AEGP_FootageLayerKey layer_key;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageLayerKey(*footageH, &layer_key));
    return layer_key;
}

FootagePtr FootageSuite::newPlaceholderFootage(std::string nameZ, int width, int height, A_Time durationPT)
{
    AEGP_FootageH footageH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewPlaceholderFootage(
        *SuiteManager::GetInstance().GetPluginID(), nameZ.c_str(), width, height, &durationPT, &footageH));
    return std::shared_ptr<AEGP_FootageH>(new AEGP_FootageH(footageH), FootageDeleter());
}

FootagePtr FootageSuite::newPlaceholderFootageWithPath(std::string pathZ, Platform path_platform,
                                                       AEIO_FileType file_type, int widthL, int heightL,
                                                       A_Time durationPT)
{
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(pathZ);
    AEGP_FootageH footageH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewPlaceholderFootageWithPath(
        *SuiteManager::GetInstance().GetPluginID(), path16.data(), AEGP_Platform(path_platform), file_type, widthL,
        heightL, &durationPT, &footageH));
    return std::shared_ptr<AEGP_FootageH>(new AEGP_FootageH(footageH), FootageDeleter());
}

FootagePtr FootageSuite::newSolidFootage(std::string nameZ, int width, int height, ColorVal colorP)
{
    AEGP_FootageH footageH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewSolidFootage(
        nameZ.c_str(), width, height, &colorP.ToAEGPColorVal(), &footageH));
    return std::shared_ptr<AEGP_FootageH>(new AEGP_FootageH(footageH), FootageDeleter());
}

ColorVal FootageSuite::getSolidFootageColor(ItemPtr itemH, bool proxyB)
{
    CheckNotNull(*itemH, "Error Getting Solid Footage Color. Item is Null");
    AEGP_ColorVal color;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetSolidFootageColor(*itemH, proxyB,
                                                                                                      &color));
    return ColorVal(color);
}

void FootageSuite::setSolidFootageColor(ItemPtr itemH, bool proxyB, ColorVal colorP)
{
    CheckNotNull(*itemH, "Error Setting Solid Footage Color. Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_SetSolidFootageColor(
        *itemH, proxyB, &colorP.ToAEGPColorVal()));
}

void FootageSuite::setSolidFootageDimensions(ItemPtr itemH, bool proxyB, int widthL, int heightL)
{
    CheckNotNull(*itemH, "Error Setting Solid Footage Dimensions. Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_SetSolidFootageDimensions(
        *itemH, proxyB, widthL, heightL));
}

AEGP_SoundDataFormat FootageSuite::getFootageSoundDataFormat(FootagePtr footageH)
{
    CheckNotNull(*footageH, "Error Getting Footage Sound Data Format. Footage is Null");
    AEGP_SoundDataFormat format;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageSoundDataFormat(*footageH,
                                                                                                           &format));
    return format;
}

AEGP_FileSequenceImportOptions FootageSuite::getFootageSequenceImportOptions(FootagePtr footageH)
{
    CheckNotNull(*footageH, "Error Getting Footage Sequence Import Options. Footage is Null");
    AEGP_FileSequenceImportOptions options;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageSequenceImportOptions(
        *footageH, &options));
    return options;
}

void UtilitySuite::reportInfo(const std::string &info_string)
{
    int id = *SuiteManager::GetInstance().GetPluginID();
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite5()->AEGP_ReportInfo(id, info_string.c_str()));
}

void UtilitySuite::reportInfoUnicode(const std::string &info_string)
{
    std::vector<A_UTF16Char> info16 = ConvertUTF8ToUTF16(info_string);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_ReportInfoUnicode(
        *SuiteManager::GetInstance().GetPluginID(), info16.data()));
}

std::tuple<A_short, A_short> UtilitySuite::getDriverPluginInitFuncVersion()
{
    A_short major;
    A_short minor;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetDriverPluginInitFuncVersion(
        &major, &minor));
    return std::make_tuple(major, minor);
}

std::tuple<A_short, A_short> UtilitySuite::getDriverImplementationVersion()
{
    A_short major;
    A_short minor;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetDriverImplementationVersion(
        &major, &minor));
    return std::make_tuple(major, minor);
}

void UtilitySuite::startQuietErrors()
{
    AEGP_ErrReportState *err_stateP = nullptr;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_StartQuietErrors(err_stateP));
}

void UtilitySuite::endQuietErrors(bool report_quieted_errorsB)
{
    AEGP_ErrReportState *err_stateP = nullptr;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_EndQuietErrors(report_quieted_errorsB,
                                                                                                err_stateP));
}

std::string UtilitySuite::getLastErrorMessage(int buffer_size)
{
    A_char *bufferP = nullptr;
    A_Err error = A_Err_NONE;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetLastErrorMessage(buffer_size,
                                                                                                     bufferP, &error));
    return std::string(bufferP);
}

void UtilitySuite::startUndoGroup(const std::string &undo_name)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_StartUndoGroup(undo_name.c_str()));
}

void UtilitySuite::endUndoGroup()
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_EndUndoGroup());
}

void *UtilitySuite::getMainHWND()
{
    void *hwnd;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetMainHWND(&hwnd));
    return hwnd;
}

void UtilitySuite::showHideAllFloaters(bool include_tool_palB)
{
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_ShowHideAllFloaters(include_tool_palB));
}

ColorVal UtilitySuite::getPaintPalForeColor()
{
    AEGP_ColorVal color;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_PaintPalGetForeColor(&color));
    return ColorVal(color);
}

ColorVal UtilitySuite::getPaintPalBackColor()
{
    AEGP_ColorVal color;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_PaintPalGetBackColor(&color));
    return ColorVal(color);
}

void UtilitySuite::setPaintPalForeColor(ColorVal fore_color)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_PaintPalSetForeColor(
        &fore_color.ToAEGPColorVal()));
}

void UtilitySuite::setPaintPalBackColor(ColorVal back_color)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_PaintPalSetBackColor(
        &back_color.ToAEGPColorVal()));
}

std::tuple<bool, ColorVal> UtilitySuite::getCharPalFillColor()
{
    AEGP_ColorVal color;
    A_Boolean is_frontmostB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalGetFillColor(&is_frontmostB,
                                                                                                     &color));
    return std::make_tuple(static_cast<bool>(is_frontmostB), ColorVal(color));
}

std::tuple<bool, ColorVal> UtilitySuite::getCharPalStrokeColor()
{
    AEGP_ColorVal color;
    A_Boolean is_frontmostB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalGetStrokeColor(&is_frontmostB,
                                                                                                       &color));
    return std::make_tuple(static_cast<bool>(is_frontmostB), ColorVal(color));
}

void UtilitySuite::setCharPalFillColor(ColorVal fill_color)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalSetFillColor(
        &fill_color.ToAEGPColorVal()));
}

void UtilitySuite::setCharPalStrokeColor(ColorVal stroke_color)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalSetStrokeColor(
        &stroke_color.ToAEGPColorVal()));
}

bool UtilitySuite::charPalIsFillColorUIFrontmost()
{
    A_Boolean is_frontmostB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalIsFillColorUIFrontmost(
        &is_frontmostB));
    return static_cast<bool>(is_frontmostB);
}

A_Ratio UtilitySuite::convertFpLongToHSFRatio(double numberF)
{
    A_Ratio ratio;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_ConvertFpLongToHSFRatio(numberF, &ratio));
    return ratio;
}

double UtilitySuite::convertHSFRatioToFpLong(A_Ratio ratioR)
{
    double number;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_ConvertHSFRatioToFpLong(ratioR, &number));
    return number;
}

void UtilitySuite::causeIdleRoutinesToBeCalled()
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CauseIdleRoutinesToBeCalled());
}

bool UtilitySuite::getSuppressInteractiveUI()
{
    A_Boolean suppressB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetSuppressInteractiveUI(&suppressB));
    return static_cast<bool>(suppressB);
}

void UtilitySuite::writeToOSConsole(const std::string &text)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_WriteToOSConsole(text.c_str()));
}

void UtilitySuite::writeToDebugLog(const std::string &subsystem, const std::string &eventType, const std::string &text)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_WriteToDebugLog(
        subsystem.c_str(), eventType.c_str(), text.c_str()));
}

std::string UtilitySuite::getPluginPath(PluginPathType path_type)
{
    AEGP_MemHandle pathH;
    std::string path = "";
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetPluginPaths(
        *SuiteManager::GetInstance().GetPluginID(), AEGP_GetPathTypes(path_type), &pathH));
    path = memHandleToString(pathH);
    return path;
}

int RenderQueueItemSuite::getNumRQItems()
{
    int numItemsL;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetNumRQItems(&numItemsL));
    return numItemsL;
}

RQItemRefPtr RenderQueueItemSuite::getRQItemByIndex(int rq_item_index)
{
    AEGP_RQItemRefH rq_itemH;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetRQItemByIndex(rq_item_index, &rq_itemH));
    return std::make_shared<AEGP_RQItemRefH>(rq_itemH);
}

RQItemRefPtr RenderQueueItemSuite::getNextRQItem(RQItemRefPtr current_rq_item)
{
    CheckNotNull(*current_rq_item, "Error Getting Next RQ Item. Current RQ Item is Null");
    AEGP_RQItemRefH next_rq_itemH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetNextRQItem(*current_rq_item,
                                                                                              &next_rq_itemH));
    return std::make_shared<AEGP_RQItemRefH>(next_rq_itemH);
}

int RenderQueueItemSuite::getNumOutputModulesForRQItem(RQItemRefPtr rq_item)
{
    CheckNotNull(*rq_item, "Error Getting Number of Output Modules for RQ Item. RQ Item is Null");
    int numModulesL;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetNumOutputModulesForRQItem(
        *rq_item, &numModulesL));
    return numModulesL;
}

RenderItemStatus RenderQueueItemSuite::getRenderState(RQItemRefPtr rq_item)
{
    CheckNotNull(*rq_item, "Error Getting Render State. RQ Item is Null");
    AEGP_RenderItemStatusType status;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetRenderState(*rq_item, &status));
    return RenderItemStatus(status);
}

void RenderQueueItemSuite::setRenderState(RQItemRefPtr rq_item, RenderItemStatus status)
{
    CheckNotNull(*rq_item, "Error Setting Render State. RQ Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_SetRenderState(
        *rq_item, AEGP_RenderItemStatusType(status)));
}

A_Time RenderQueueItemSuite::getStartedTime(RQItemRefPtr rq_item)
{
    CheckNotNull(*rq_item, "Error Getting Started Time. RQ Item is Null");
    A_Time time;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetStartedTime(*rq_item, &time));
    return time;
}

A_Time RenderQueueItemSuite::getElapsedTime(RQItemRefPtr rq_item)
{
    CheckNotNull(*rq_item, "Error Getting Elapsed Time. RQ Item is Null");
    A_Time time;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetElapsedTime(*rq_item, &time));
    return time;
}

LogType RenderQueueItemSuite::getLogType(RQItemRefPtr rq_item)
{
    CheckNotNull(*rq_item, "Error Getting Log Type. RQ Item is Null");
    AEGP_LogType logtype;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetLogType(*rq_item, &logtype));
    return LogType(logtype);
}

void RenderQueueItemSuite::setLogType(RQItemRefPtr rq_item, LogType logtype)
{
    CheckNotNull(*rq_item, "Error Setting Log Type. RQ Item is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_SetLogType(*rq_item, AEGP_LogType(logtype)));
}

void RenderQueueItemSuite::removeOutputModule(RQItemRefPtr rq_item, OutputModuleRefPtr outmod)
{
    CheckNotNull(*rq_item, "Error Removing Output Module. RQ Item is Null");
    CheckNotNull(*outmod, "Error Removing Output Module. Output Module is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_RemoveOutputModule(*rq_item, *outmod));
}

std::string RenderQueueItemSuite::getComment(RQItemRefPtr rq_item)
{
    CheckNotNull(*rq_item, "Error Getting Comment. RQ Item is Null");
    A_char *commentP = nullptr;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetComment(*rq_item, commentP));
    std::string comment(commentP);
    return comment;
}

void RenderQueueItemSuite::setComment(RQItemRefPtr rq_item, const std::string &comment)
{
    CheckNotNull(*rq_item, "Error Setting Comment. RQ Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_SetComment(*rq_item, comment.c_str()));
}

CompPtr RenderQueueItemSuite::getCompFromRQItem(RQItemRefPtr rq_item)
{
    CheckNotNull(*rq_item, "Error Getting Comp from RQ Item. RQ Item is Null");
    AEGP_CompH compH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetCompFromRQItem(*rq_item, &compH));
    return std::make_shared<AEGP_CompH>(compH);
}

void RenderQueueItemSuite::deleteRQItem(RQItemRefPtr rq_item)
{
    CheckNotNull(*rq_item, "Error Deleting RQ Item. RQ Item is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_DeleteRQItem(*rq_item));
}

OutputModuleRefPtr OutputModuleSuite::getOutputModuleByIndex(RQItemRefPtr rq_itemH, int outmod_indexL)
{
    CheckNotNull(*rq_itemH, "Error Getting Output Module by Index. RQ Item is Null");
    AEGP_OutputModuleRefH outmodH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetOutputModuleByIndex(
        *rq_itemH, outmod_indexL, &outmodH));
    return std::make_shared<AEGP_OutputModuleRefH>(outmodH);
}

EmbeddingType OutputModuleSuite::getEmbedOptions(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    CheckNotNull(*rq_itemH, "Error Getting Embed Options. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Getting Embed Options. Output Module is Null");
    AEGP_EmbeddingType embed_options;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetEmbedOptions(
        *rq_itemH, *outmodH, &embed_options));
    return EmbeddingType(embed_options);
}

void OutputModuleSuite::setEmbedOptions(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, EmbeddingType embed_options)
{
    CheckNotNull(*rq_itemH, "Error Setting Embed Options. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Setting Embed Options. Output Module is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetEmbedOptions(
        *rq_itemH, *outmodH, AEGP_EmbeddingType(embed_options)));
}

PostRenderAction OutputModuleSuite::getPostRenderAction(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    CheckNotNull(*rq_itemH, "Error Getting Post Render Action. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Getting Post Render Action. Output Module is Null");
    AEGP_PostRenderAction post_render_action;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetPostRenderAction(
        *rq_itemH, *outmodH, &post_render_action));
    return PostRenderAction(post_render_action);
}

void OutputModuleSuite::setPostRenderAction(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                                            PostRenderAction post_render_action)
{
    CheckNotNull(*rq_itemH, "Error Setting Post Render Action. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Setting Post Render Action. Output Module is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetPostRenderAction(
        *rq_itemH, *outmodH, AEGP_PostRenderAction(post_render_action)));
}

OutputTypes OutputModuleSuite::getEnabledOutputs(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    CheckNotNull(*rq_itemH, "Error Getting Enabled Outputs. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Getting Enabled Outputs. Output Module is Null");
    AEGP_OutputTypes enabled_types;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetEnabledOutputs(
        *rq_itemH, *outmodH, &enabled_types));
    return OutputTypes(enabled_types);
}

void OutputModuleSuite::setEnabledOutputs(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, OutputTypes enabled_types)
{
    CheckNotNull(*rq_itemH, "Error Setting Enabled Outputs. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Setting Enabled Outputs. Output Module is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetEnabledOutputs(
        *rq_itemH, *outmodH, AEGP_OutputTypes(enabled_types)));
}

VideoChannels OutputModuleSuite::getOutputChannels(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    CheckNotNull(*rq_itemH, "Error Getting Output Channels. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Getting Output Channels. Output Module is Null");
    AEGP_VideoChannels output_channels;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetOutputChannels(
        *rq_itemH, *outmodH, &output_channels));
    return VideoChannels(output_channels);
}

void OutputModuleSuite::setOutputChannels(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                                          VideoChannels output_channels)
{
    CheckNotNull(*rq_itemH, "Error Setting Output Channels. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Setting Output Channels. Output Module is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetOutputChannels(
        *rq_itemH, *outmodH, AEGP_VideoChannels(output_channels)));
}

std::tuple<bool, StretchQuality, bool> OutputModuleSuite::getStretchInfo(RQItemRefPtr rq_itemH,
                                                                         OutputModuleRefPtr outmodH)
{
    CheckNotNull(*rq_itemH, "Error Getting Stretch Info. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Getting Stretch Info. Output Module is Null");
    A_Boolean is_enabledB;
    AEGP_StretchQuality stretch_quality;
    A_Boolean is_onB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetStretchInfo(
        *rq_itemH, *outmodH, &is_enabledB, &stretch_quality, &is_onB));
    return std::make_tuple(static_cast<bool>(is_enabledB), StretchQuality(stretch_quality), static_cast<bool>(is_onB));
}

void OutputModuleSuite::setStretchInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, bool is_enabledB,
                                       StretchQuality stretch_quality)
{
    CheckNotNull(*rq_itemH, "Error Setting Stretch Info. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Setting Stretch Info. Output Module is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetStretchInfo(
        *rq_itemH, *outmodH, is_enabledB, AEGP_StretchQuality(stretch_quality)));
}

std::tuple<bool, LRect> OutputModuleSuite::getCropInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    CheckNotNull(*rq_itemH, "Error Getting Crop Info. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Getting Crop Info. Output Module is Null");
    A_Boolean is_enabledB;
    A_Rect crop_rect;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetCropInfo(
        *rq_itemH, *outmodH, &is_enabledB, &crop_rect));
    return std::make_tuple(static_cast<bool>(is_enabledB), crop_rect);
}

void OutputModuleSuite::setCropInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, bool enableB, LRect crop_rect)
{
    CheckNotNull(*rq_itemH, "Error Setting Crop Info. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Setting Crop Info. Output Module is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetCropInfo(
        *rq_itemH, *outmodH, enableB, crop_rect.ToA_LRect()));
}

std::tuple<AEGP_SoundDataFormat, bool> OutputModuleSuite::getSoundFormatInfo(RQItemRefPtr rq_itemH,
                                                                             OutputModuleRefPtr outmodH)
{
    CheckNotNull(*rq_itemH, "Error Getting Sound Format Info. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Getting Sound Format Info. Output Module is Null");
    AEGP_SoundDataFormat sound_format_info;
    A_Boolean audio_enabledB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetSoundFormatInfo(
        *rq_itemH, *outmodH, &sound_format_info, &audio_enabledB));
    return std::make_tuple(sound_format_info, static_cast<bool>(audio_enabledB));
}

void OutputModuleSuite::setSoundFormatInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                                           AEGP_SoundDataFormat sound_format_info, bool audio_enabledB)
{
    CheckNotNull(*rq_itemH, "Error Setting Sound Format Info. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Setting Sound Format Info. Output Module is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetSoundFormatInfo(
        *rq_itemH, *outmodH, sound_format_info, audio_enabledB));
}

std::string OutputModuleSuite::getOutputFilePath(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    CheckNotNull(*rq_itemH, "Error Getting Output File Path. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Getting Output File Path. Output Module is Null");
    AEGP_MemHandle pathH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetOutputFilePath(
        *rq_itemH, *outmodH, &pathH));
    return memHandleToString(pathH);
}

void OutputModuleSuite::setOutputFilePath(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, const std::string &path)
{
    CheckNotNull(*rq_itemH, "Error Setting Output File Path. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Setting Output File Path. Output Module is Null");
    std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetOutputFilePath(
        *rq_itemH, *outmodH, path16.data()));
}

OutputModuleRefPtr OutputModuleSuite::addDefaultOutputModule(RQItemRefPtr rq_itemH)
{
    CheckNotNull(*rq_itemH, "Error Adding Default Output Module. RQ Item is Null");
    AEGP_OutputModuleRefH outmodH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_AddDefaultOutputModule(*rq_itemH,
                                                                                                             &outmodH));
    return std::make_shared<AEGP_OutputModuleRefH>(outmodH);
}

std::tuple<std::string, std::string, bool, bool> OutputModuleSuite::getExtraOutputModuleInfo(RQItemRefPtr rq_itemH,
                                                                                             OutputModuleRefPtr outmodH)
{
    CheckNotNull(*rq_itemH, "Error Getting Extra Output Module Info. RQ Item is Null");
    CheckNotNull(*outmodH, "Error Getting Extra Output Module Info. Output Module is Null");
    AEGP_MemHandle formatH;
    AEGP_MemHandle infoH;
    A_Boolean has_custom_optionsB;
    A_Boolean has_custom_render_templateB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetExtraOutputModuleInfo(
        *rq_itemH, *outmodH, &formatH, &infoH, &has_custom_optionsB, &has_custom_render_templateB));
    std::string format = memHandleToString(formatH);
    std::string info = memHandleToString(infoH);
    return std::make_tuple(format, info, static_cast<bool>(has_custom_optionsB),
                           static_cast<bool>(has_custom_render_templateB));
}

WorldPtr WorldSuite::newWorld(WorldType type, int widthL, int heightL)
{
    AEGP_WorldH worldH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_New(
        *SuiteManager::GetInstance().GetPluginID(), AEGP_WorldType(type), widthL, heightL, &worldH));
    return std::shared_ptr<AEGP_WorldH>(new AEGP_WorldH(worldH), WorldDeleter());
}

WorldType WorldSuite::getType(WorldPtr worldH)
{
    CheckNotNull(*worldH, "Error Getting World Type. World is Null");
    AEGP_WorldType type;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetType(*worldH, &type));
    return WorldType(type);
}

std::tuple<int, int> WorldSuite::getSize(WorldPtr worldH)
{
    CheckNotNull(*worldH, "Error Getting World Size. World is Null");
    int widthL;
    int heightL;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetSize(*worldH, &widthL, &heightL));
    return std::make_tuple(widthL, heightL);
}

A_u_long WorldSuite::getRowBytes(WorldPtr worldH)
{
    CheckNotNull(*worldH, "Error Getting Row Bytes. World is Null");
    A_u_long row_bytes;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetRowBytes(*worldH, &row_bytes));
    return row_bytes;
}

PF_Pixel8 *WorldSuite::getBaseAddr8(WorldPtr worldH)
{
    CheckNotNull(*worldH, "Error Getting Base Address 8. World is Null");
    PF_Pixel8 *base_addrP;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetBaseAddr8(*worldH, &base_addrP));
    return base_addrP;
}

PF_Pixel16 *WorldSuite::getBaseAddr16(WorldPtr worldH)
{
    CheckNotNull(*worldH, "Error Getting Base Address 16. World is Null");
    PF_Pixel16 *base_addrP;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetBaseAddr16(*worldH, &base_addrP));
    return base_addrP;
}

PF_PixelFloat *WorldSuite::getBaseAddr32(WorldPtr worldH)
{
    CheckNotNull(*worldH, "Error Getting Base Address 32. World is Null");
    PF_PixelFloat *base_addrP;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetBaseAddr32(*worldH, &base_addrP));
    return base_addrP;
}

PF_EffectWorld WorldSuite::fillOutPFEffectWorld(WorldPtr worldH)
{
    CheckNotNull(*worldH, "Error Filling Out PF Effect World. World is Null");
    PF_EffectWorld effect_world;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_FillOutPFEffectWorld(*worldH, &effect_world));
    return effect_world;
}

void WorldSuite::fastBlur(double radiusF, PF_ModeFlags mode, PF_Quality quality, WorldPtr worldH)
{
    CheckNotNull(*worldH, "Error Fast Blurring World. World is Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_FastBlur(radiusF, mode, quality, *worldH));
}

PlatformWorldPtr WorldSuite::newPlatformWorld(AEGP_WorldType type, int widthL, int heightL)
{
    AEGP_PlatformWorldH worldH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_NewPlatformWorld(
        *SuiteManager::GetInstance().GetPluginID(), AEGP_WorldType(type), widthL, heightL, &worldH));
    return std::shared_ptr<AEGP_PlatformWorldH>(new AEGP_PlatformWorldH(worldH), PlatformDeleter());
}

WorldPtr WorldSuite::newReferenceFromPlatformWorld(PlatformWorldPtr platform_worldH)
{
    CheckNotNull(*platform_worldH, "Error Creating Reference from Platform World. Platform World is Null");
    AEGP_WorldH worldH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_NewReferenceFromPlatformWorld(
        *SuiteManager::GetInstance().GetPluginID(), *platform_worldH, &worldH));
    return std::shared_ptr<AEGP_WorldH>(new AEGP_WorldH(worldH), WorldDeleter());
}

RenderOptionsPtr RenderOptionsSuite::newFromItem(ItemPtr itemH)
{
    CheckNotNull(*itemH, "Error Creating Render Options from Item. Item is Null");
    AEGP_RenderOptionsH optionsH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_NewFromItem(
        *SuiteManager::GetInstance().GetPluginID(), *itemH, &optionsH));
    return std::shared_ptr<AEGP_RenderOptionsH>(new AEGP_RenderOptionsH(optionsH), RenderOptionsDeleter());
}

RenderOptionsPtr RenderOptionsSuite::duplicate(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Duplicating Render Options. Options are Null");
    AEGP_RenderOptionsH new_optionsH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_Duplicate(
        *SuiteManager::GetInstance().GetPluginID(), *optionsH, &new_optionsH));
    return std::shared_ptr<AEGP_RenderOptionsH>(new AEGP_RenderOptionsH(new_optionsH), RenderOptionsDeleter());
}

void RenderOptionsSuite::setTime(RenderOptionsPtr optionsH, A_Time time)
{
    CheckNotNull(*optionsH, "Error Setting Time. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetTime(*optionsH.get(), time));
}

A_Time RenderOptionsSuite::getTime(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Time. Options are Null");
    A_Time time;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetTime(*optionsH.get(), &time));
    return time;
}

void RenderOptionsSuite::setTimeStep(RenderOptionsPtr optionsH, A_Time time_step)
{
    CheckNotNull(*optionsH, "Error Setting Time Step. Options are Null");
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetTimeStep(*optionsH, time_step));
}

A_Time RenderOptionsSuite::getTimeStep(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Time Step. Options are Null");
    A_Time time;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetTimeStep(*optionsH, &time));
    return time;
}

void RenderOptionsSuite::setFieldRender(RenderOptionsPtr optionsH, PF_Field field_render)
{
    CheckNotNull(*optionsH, "Error Setting Field Render. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetFieldRender(*optionsH,
                                                                                                      field_render));
}

PF_Field RenderOptionsSuite::getFieldRender(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Field Render. Options are Null");
    PF_Field field_render;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetFieldRender(*optionsH,
                                                                                                      &field_render));
    return field_render;
}

void RenderOptionsSuite::setWorldType(RenderOptionsPtr optionsH, WorldType type)
{
    CheckNotNull(*optionsH, "Error Setting World Type. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetWorldType(
        *optionsH, AEGP_WorldType(type)));
}

WorldType RenderOptionsSuite::getWorldType(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting World Type. Options are Null");
    AEGP_WorldType type;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetWorldType(*optionsH, &type));
    return WorldType(type);
}

void RenderOptionsSuite::setDownsampleFactor(RenderOptionsPtr optionsH, DownsampleFactor dsf)
{
    CheckNotNull(*optionsH, "Error Setting Downsample Factor. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetDownsampleFactor(
        *optionsH, dsf.xS, dsf.yS));
}

DownsampleFactor RenderOptionsSuite::getDownsampleFactor(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Downsample Factor. Options are Null");
    A_short x;
    A_short y;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetDownsampleFactor(*optionsH,
                                                                                                           &x, &y));
    return DownsampleFactor(x, y);
}

void RenderOptionsSuite::setRegionOfInterest(RenderOptionsPtr optionsH, LRect roiP)
{
    CheckNotNull(*optionsH, "Error Setting Region of Interest. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetRegionOfInterest(
        *optionsH, &roiP.ToA_LRect()));
}

LRect RenderOptionsSuite::getRegionOfInterest(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Region of Interest. Options are Null");
    A_LRect roi;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetRegionOfInterest(*optionsH, &roi));
    return LRect(roi);
}

void RenderOptionsSuite::setMatteMode(RenderOptionsPtr optionsH, MatteMode mode)
{
    CheckNotNull(*optionsH, "Error Setting Matte Mode. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetMatteMode(
        *optionsH, AEGP_MatteMode(mode)));
}

MatteMode RenderOptionsSuite::getMatteMode(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Matte Mode. Options are Null");
    AEGP_MatteMode mode;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetMatteMode(*optionsH, &mode));
    return MatteMode(mode);
}

void RenderOptionsSuite::setChannelOrder(RenderOptionsPtr optionsH, ChannelOrder channel_order)
{
    CheckNotNull(*optionsH, "Error Setting Channel Order. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetChannelOrder(
        *optionsH, AEGP_ChannelOrder(channel_order)));
}

ChannelOrder RenderOptionsSuite::getChannelOrder(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Channel Order. Options are Null");
    AEGP_ChannelOrder channel_order;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetChannelOrder(*optionsH,
                                                                                                       &channel_order));
    return ChannelOrder(channel_order);
}

bool RenderOptionsSuite::getRenderGuideLayers(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Render Guide Layers. Options are Null");
    A_Boolean render_themB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetRenderGuideLayers(
        *optionsH, &render_themB));
    return static_cast<bool>(render_themB);
}

void RenderOptionsSuite::setRenderGuideLayers(RenderOptionsPtr optionsH, bool render_themB)
{
    CheckNotNull(*optionsH, "Error Setting Render Guide Layers. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetRenderGuideLayers(
        *optionsH, render_themB));
}

LayerRenderOptionsPtr LayerRenderOptionsSuite::newFromLayer(LayerPtr layer)
{
    CheckNotNull(*layer, "Error Creating Layer Render Options from Layer. Layer is Null");
    AEGP_LayerRenderOptionsH optionsH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_NewFromLayer(
        *SuiteManager::GetInstance().GetPluginID(), *layer, &optionsH));
    return std::shared_ptr<AEGP_LayerRenderOptionsH>(&optionsH, LayerRenderOptionsDeleter());
}

LayerRenderOptionsPtr LayerRenderOptionsSuite::newFromUpstreamOfEffect(EffectRefPtr effect_ref)
{
    CheckNotNull(*effect_ref, "Error Creating Layer Render Options from Upstream of Effect. Effect "
                              "is Null");
    AEGP_LayerRenderOptionsH optionsH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_NewFromUpstreamOfEffect(
        *SuiteManager::GetInstance().GetPluginID(), *effect_ref, &optionsH));
    return std::shared_ptr<AEGP_LayerRenderOptionsH>(new AEGP_LayerRenderOptionsH(optionsH),
                                                     LayerRenderOptionsDeleter());
}

LayerRenderOptionsPtr LayerRenderOptionsSuite::newFromDownstreamOfEffect(EffectRefPtr effect_ref)
{
    CheckNotNull(*effect_ref, "Error Creating Layer Render Options from Downstream of Effect. Effect "
                              "is Null");
    AEGP_LayerRenderOptionsH optionsH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_NewFromDownstreamOfEffect(
        *SuiteManager::GetInstance().GetPluginID(), *effect_ref, &optionsH));
    return std::shared_ptr<AEGP_LayerRenderOptionsH>(new AEGP_LayerRenderOptionsH(optionsH),
                                                     LayerRenderOptionsDeleter());
}

LayerRenderOptionsPtr LayerRenderOptionsSuite::duplicate(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Duplicating Layer Render Options. Options are Null");
    AEGP_LayerRenderOptionsH new_optionsH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_Duplicate(
        *SuiteManager::GetInstance().GetPluginID(), *optionsH, &new_optionsH));
    return std::shared_ptr<AEGP_LayerRenderOptionsH>(new AEGP_LayerRenderOptionsH(new_optionsH),
                                                     LayerRenderOptionsDeleter());
}

void LayerRenderOptionsSuite::setTime(LayerRenderOptionsPtr optionsH, A_Time time)
{
    CheckNotNull(*optionsH, "Error Setting Time. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetTime(*optionsH, time));
}

A_Time LayerRenderOptionsSuite::getTime(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Time. Options are Null");
    A_Time time;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetTime(*optionsH, &time));
    return time;
}

void LayerRenderOptionsSuite::setTimeStep(LayerRenderOptionsPtr optionsH, A_Time time_step)
{
    CheckNotNull(*optionsH, "Error Setting Time Step. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetTimeStep(*optionsH,
                                                                                                        time_step));
}

A_Time LayerRenderOptionsSuite::getTimeStep(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Time Step. Options are Null");
    A_Time time;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetTimeStep(*optionsH, &time));
    return time;
}

void LayerRenderOptionsSuite::setWorldType(LayerRenderOptionsPtr optionsH, WorldType type)
{
    CheckNotNull(*optionsH, "Error Setting World Type. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetWorldType(
        *optionsH, AEGP_WorldType(type)));
}

WorldType LayerRenderOptionsSuite::getWorldType(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting World Type. Options are Null");
    AEGP_WorldType type;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetWorldType(*optionsH, &type));
    return WorldType(type);
}

void LayerRenderOptionsSuite::setDownsampleFactor(LayerRenderOptionsPtr optionsH, DownsampleFactor dsf)
{
    CheckNotNull(*optionsH, "Error Setting Downsample Factor. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetDownsampleFactor(
        *optionsH, dsf.xS, dsf.yS));
}

DownsampleFactor LayerRenderOptionsSuite::getDownsampleFactor(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Downsample Factor. Options are Null");
    A_short x;
    A_short y;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetDownsampleFactor(
        *optionsH, &x, &y));
    return DownsampleFactor(x, y);
}

void LayerRenderOptionsSuite::setMatteMode(LayerRenderOptionsPtr optionsH, MatteMode mode)
{
    CheckNotNull(*optionsH, "Error Setting Matte Mode. Options are Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetMatteMode(
        *optionsH, AEGP_MatteMode(mode)));
}

MatteMode LayerRenderOptionsSuite::getMatteMode(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Getting Matte Mode. Options are Null");
    AEGP_MatteMode mode;
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetMatteMode(*optionsH, &mode));
    return MatteMode(mode);
}

Collection2Ptr CollectionSuite::newCollection()
{
    AEGP_Collection2H collectionH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_NewCollection(
        *SuiteManager::GetInstance().GetPluginID(), &collectionH));
    return std::shared_ptr<AEGP_Collection2H>(new AEGP_Collection2H(collectionH), CollectionDeleter());
}

int CollectionSuite::getCollectionNumItems(Collection2Ptr collectionH)
{
    CheckNotNull(*collectionH, "Error Getting Collection Number of Items. Collection is Null");
    A_u_long numItemsL;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_GetCollectionNumItems(*collectionH,
                                                                                                          &numItemsL));
    return static_cast<int>(numItemsL);
}

AEGP_CollectionItemV2 CollectionSuite::getCollectionItemByIndex(Collection2Ptr collectionH, int indexL)
{
    CheckNotNull(*collectionH, "Error Getting Collection Item by Index. Collection is Null");
    AEGP_CollectionItemV2 item;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_GetCollectionItemByIndex(
        *collectionH, indexL, &item));
    return item;
}

void CollectionSuite::collectionPushBack(Collection2Ptr collectionH, const AEGP_CollectionItemV2 &itemP)
{
    CheckNotNull(*collectionH, "Error Pushing Back to Collection. Collection is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_CollectionPushBack(*collectionH,
                                                                                                       &itemP));
}

void CollectionSuite::collectionErase(Collection2Ptr collectionH, int index_firstL, int index_lastL)
{
    CheckNotNull(*collectionH, "Error Erasing Collection. Collection is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_CollectionErase(
        *collectionH, index_firstL, index_lastL));
}

void RegisterSuite::registerCommandHook(AEGP_HookPriority hook_priority, AEGP_Command command,
                                        AEGP_CommandHook command_hook_func, AEGP_CommandRefcon refconP)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RegisterSuite5()->AEGP_RegisterCommandHook(
        *SuiteManager::GetInstance().GetPluginID(), hook_priority, command, command_hook_func, refconP));
}

void RegisterSuite::registerUpdateMenuHook(AEGP_UpdateMenuHook update_menu_hook_func, AEGP_UpdateMenuRefcon refconP)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RegisterSuite5()->AEGP_RegisterUpdateMenuHook(
        *SuiteManager::GetInstance().GetPluginID(), update_menu_hook_func, refconP));
}

void RegisterSuite::registerDeathHook(AEGP_DeathHook death_hook_func, AEGP_DeathRefcon refconP)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RegisterSuite5()->AEGP_RegisterDeathHook(
        *SuiteManager::GetInstance().GetPluginID(), death_hook_func, refconP));
}

void RegisterSuite::registerIdleHook(AEGP_IdleHook idle_hook_func, AEGP_IdleRefcon refconP)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RegisterSuite5()->AEGP_RegisterIdleHook(
        *SuiteManager::GetInstance().GetPluginID(), idle_hook_func, refconP));
}

void RegisterSuite::registerPresetLocalizationString(const std::string &english_nameZ,
                                                     const std::string &localized_nameZ)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RegisterSuite5()->AEGP_RegisterPresetLocalizationString(
        english_nameZ.c_str(), localized_nameZ.c_str()));
}

AEGP_Command CommandSuite::getUniqueCommand()
{
    AEGP_Command command;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_GetUniqueCommand(&command));
    return command;
}

void CommandSuite::insertMenuCommand(AEGP_Command command, const std::string &nameZ, MenuID menu_id, int after_itemL)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_InsertMenuCommand(
        command, nameZ.c_str(), AEGP_MenuID(menu_id), after_itemL));
}

void CommandSuite::removeMenuCommand(AEGP_Command command)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_RemoveMenuCommand(command));
}

void CommandSuite::setMenuCommandName(AEGP_Command command, const std::string &nameZ)
{
    AE_CHECK(
        SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_SetMenuCommandName(command, nameZ.c_str()));
}

void CommandSuite::enableCommand(AEGP_Command command)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_EnableCommand(command));
}

void CommandSuite::disableCommand(AEGP_Command command)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_DisableCommand(command));
}

void CommandSuite::checkMarkMenuCommand(AEGP_Command command, bool checkB)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_CheckMarkMenuCommand(command, checkB));
}

void CommandSuite::doCommand(AEGP_Command command)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_DoCommand(command));
}

FrameReceiptPtr RenderSuite::renderAndCheckoutFrame(RenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Rendering and Checking Out Frame. Options are Null");
    AEGP_FrameReceiptH receiptH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_RenderAndCheckoutFrame(
        *optionsH, NULL, NULL, &receiptH));
    return std::shared_ptr<AEGP_FrameReceiptH>(new AEGP_FrameReceiptH(receiptH), FrameReceiptDeleter());
}

FrameReceiptPtr RenderSuite::renderAndCheckoutLayerFrame(LayerRenderOptionsPtr optionsH)
{
    CheckNotNull(*optionsH, "Error Rendering and Checking Out Layer Frame. Options are Null");
    AEGP_FrameReceiptH receiptH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_RenderAndCheckoutLayerFrame(
        *optionsH, NULL, NULL, &receiptH));
    return std::shared_ptr<AEGP_FrameReceiptH>(new AEGP_FrameReceiptH(receiptH), FrameReceiptDeleter());
}

A_u_longlong RenderSuite::renderAndCheckoutLayerFrameAsync(LayerRenderOptionsPtr optionsH,
                                                           AEGP_AsyncFrameReadyCallback callback)
{
    CheckNotNull(*optionsH, "Error Rendering and Checking Out Layer Frame Asynchronously. Options "
                            "are Null");
    A_u_longlong id;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_RenderAndCheckoutLayerFrame_Async(
        *optionsH, callback, NULL, &id));
    return id;
}

void RenderSuite::cancelAsyncRequest(AEGP_AsyncRequestId async_request_id)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_CancelAsyncRequest(async_request_id));
}

WorldPtr RenderSuite::getReceiptWorld(FrameReceiptPtr receiptH)
{
    CheckNotNull(*receiptH.get(), "Error Getting Receipt World. Receipt is Null");
    AEGP_WorldH worldH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_GetReceiptWorld(*receiptH, &worldH));
    return std::make_shared<AEGP_WorldH>(worldH);
}

LRect RenderSuite::getRenderedRegion(FrameReceiptPtr receiptH)
{
    CheckNotNull(*receiptH, "Error Getting Rendered Region. Receipt is Null");
    A_LRect region;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_GetRenderedRegion(*receiptH, &region));
    return LRect(region);
}

bool RenderSuite::isRenderedFrameSufficient(RenderOptionsPtr rendered_optionsH, RenderOptionsPtr proposed_optionsH)
{
    CheckNotNull(*rendered_optionsH, "Error Checking if Rendered Frame is Sufficient. Rendered "
                                     "Options are Null");
    CheckNotNull(*proposed_optionsH, "Error Checking if Rendered Frame is Sufficient. Proposed "
                                     "Options are Null");
    A_Boolean is_sufficientB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_IsRenderedFrameSufficient(
        *rendered_optionsH, *proposed_optionsH, &is_sufficientB));
    return static_cast<bool>(is_sufficientB);
}

TimeStampPtr RenderSuite::getCurrentTimestamp()
{
    AEGP_TimeStamp timeStamp;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_GetCurrentTimestamp(&timeStamp));
    return std::make_shared<AEGP_TimeStamp>(timeStamp);
}

bool RenderSuite::hasItemChangedSinceTimestamp(ItemPtr itemH, A_Time start_timeP, A_Time durationP,
                                               TimeStampPtr time_stampP)
{
    CheckNotNull(*itemH, "Error Checking if Item has Changed Since Timestamp. Item is Null");
    CheckNotNull(time_stampP.get(), "Error Checking if Item has Changed Since "
                                    "Timestamp. Time Stamp is Null");

    A_Boolean has_changedB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_HasItemChangedSinceTimestamp(
        *itemH, &start_timeP, &durationP, time_stampP.get(), &has_changedB));
    return static_cast<bool>(has_changedB);
}

bool RenderSuite::isItemWorthwhileToRender(RenderOptionsPtr roH, TimeStampPtr time_stampP)
{
    CheckNotNull(*roH, "Error Checking if Item is Worthwhile to Render. "
                       "Render Options are Null");
    CheckNotNull(time_stampP.get(), "Error Checking if Item is Worthwhile to Render. Time Stamp is Null");
    A_Boolean is_worthwhileB;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_IsItemWorthwhileToRender(
        *roH, time_stampP.get(), &is_worthwhileB));
    return static_cast<bool>(is_worthwhileB);
}

void RenderSuite::checkinRenderedFrame(RenderOptionsPtr roH, TimeStampPtr time_stampP, A_u_long ticks_to_renderL,
                                       PlatformWorldPtr imageH)
{
    CheckNotNull(*roH, "Error Checking in Rendered Frame. Render Options are Null");
    CheckNotNull(time_stampP.get(), "Error Checking in Rendered Frame. Time Stamp is Null");
    CheckNotNull(*imageH, "Error Checking in Rendered Frame. Image is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_CheckinRenderedFrame(
        *roH, time_stampP.get(), ticks_to_renderL, *imageH));
}

std::string RenderSuite::getReceiptGuid(FrameReceiptPtr receiptH)
{
    CheckNotNull(*receiptH, "Error Getting Receipt GUID. Receipt is Null");
    AEGP_MemHandle guidH;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_GetReceiptGuid(*receiptH, &guidH));
    return memHandleToString(guidH);
}

bool isLayerValid(ItemPtr item, CompPtr comp)
{
    return LayerSuite().IsAddLayerValid(item, comp);
}

void RenderQueueSuite::addCompToRenderQueue(CompPtr comp, const std::string &path)
{
    CheckNotNull(*comp, "Error Adding Comp to Render Queue. Comp is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderQueueSuite1()->AEGP_AddCompToRenderQueue(
        *comp, path.c_str()));
}

void RenderQueueSuite::setRenderQueueState(RenderQueueState state)
{
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderQueueSuite1()->AEGP_SetRenderQueueState(
        AEGP_RenderQueueState(state)));
}

RenderQueueState RenderQueueSuite::getRenderQueueState()
{
    AEGP_RenderQueueState state;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderQueueSuite1()->AEGP_GetRenderQueueState(&state));
    return RenderQueueState(state);
}

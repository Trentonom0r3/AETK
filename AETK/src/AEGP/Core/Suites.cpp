#include <AETK/AEGP/Core/Suites.hpp>
#include <cassert>
// #define TK_INTERNAL
/**
 * @function GetNumProjects
 * @brief` Get the number of projects in the current AE session
 *
 * \return
 */
int ProjSuite::GetNumProjects()
{
    auto future = ae::ScheduleOrExecute([]() {
        A_Err err = A_Err_NONE;
        int numProjects = 0;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetNumProjects(&numProjects));
        return numProjects;
    });
    return future.get();
}

ProjectPtr ProjSuite::GetProjectByIndex(int projIndex)
{
    auto future = ae::ScheduleOrExecute([projIndex]() {
        A_Err err = A_Err_NONE;
        AEGP_ProjectH projectH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectByIndex(projIndex, &projectH));
        return makeProjectPtr(projectH);
    });
    return future.get();
}

std::string ProjSuite::GetProjectName(ProjectPtr project)
{
    auto nameResult = ae::ScheduleOrExecute([project]() {
        CheckNotNull(project->get(), "Error Getting Project Name. Project is Null");
        A_Err err = A_Err_NONE;
        A_char name[256];
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectName(*project, name));
        return std::string(name);
    });
    return nameResult.get();
}

std::string ProjSuite::GetProjectPath(ProjectPtr project)
{
    auto pathResult = ae::ScheduleOrExecute([project]() {
        A_Err err = A_Err_NONE;
        AEGP_MemHandle pathH;
        CheckNotNull(project->get(), "Error Getting Project Path. Project is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectPath(*project, &pathH));
        return memHandleToString(pathH);
    });
    return pathResult.get();
}

ItemPtr ProjSuite::GetProjectRootFolder(ProjectPtr project)
{
    auto rootFolderResult = ae::ScheduleOrExecute([project]() {
        AEGP_ItemH rootFolderH;
        CheckNotNull(project->get(), "Error Getting Project Root Folder. Project is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectRootFolder(*project,
                                                                                                       &rootFolderH));
        return makeItemPtr(rootFolderH);
    });
    return rootFolderResult.get();
}

void ProjSuite::SaveProjectToPath(ProjectPtr project, const std::string &path)
{
    auto future = ae::ScheduleOrExecute([project, path]() {
        CheckNotNull(project->get(), "Error Saving Project. Project is Null");
        std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SaveProjectToPath(*project,
                                                                                                    path16.data()));
    });
    future.wait();
}

TimeDisplay3 ProjSuite::GetProjectTimeDisplay(ProjectPtr project)
{
    auto timeDisplayResult = ae::ScheduleOrExecute([project]() {
        AEGP_TimeDisplay3 timeDisplay;
        CheckNotNull(project->get(), "Error Getting Project Time Display. Project is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectTimeDisplay(*project,
                                                                                                        &timeDisplay));
        return TimeDisplay3(timeDisplay);
    });
    return timeDisplayResult.get();
}

void ProjSuite::SetProjectTimeDisplay(ProjectPtr project, TimeDisplay3 timeDisplay)
{
    AEGP_TimeDisplay3 timeDisplay3 = timeDisplay.toAEGP();
    auto future = ae::ScheduleOrExecute([project, timeDisplay3]() {
        CheckNotNull(project->get(), "Error Setting Project Time Display. Project is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SetProjectTimeDisplay(*project,
                                                                                                        &timeDisplay3));
    });
    future.wait();
}

bool ProjSuite::ProjectIsDirty(ProjectPtr project)
{
    auto isDirtyResult = ae::ScheduleOrExecute([project]() {
        CheckNotNull(project->get(), "Error Checking if Project is Dirty. Project is Null");
        A_Boolean isDirty;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_ProjectIsDirty(*project, &isDirty));
        return isDirty;
    });
    return isDirtyResult.get();
}

void ProjSuite::SaveProjectAs(ProjectPtr project, const std::string &path)
{
    auto future = ae::ScheduleOrExecute([project, path]() {
        CheckNotNull(project->get(), "Error Saving Project As. Project is Null");
        std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SaveProjectAs(*project, path16.data()));
    });
    future.wait();
}

ProjectPtr ProjSuite::NewProject()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_ProjectH projectH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_NewProject(&projectH));
        return makeProjectPtr(projectH);
    });
    return future.get();
}

ProjectPtr ProjSuite::OpenProjectFromPath(const std::string &path)
{
    auto future = ae::ScheduleOrExecute([path]() {
        std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
        AEGP_ProjectH projectH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_OpenProjectFromPath(path16.data(),
                                                                                                      &projectH));
        return makeProjectPtr(projectH);
    });
    return future.get();
}

ProjBitDepth ProjSuite::GetProjectBitDepth(ProjectPtr project)
{
    auto future = ae::ScheduleOrExecute([project]() {
        AEGP_ProjBitDepth bitDepth;
        CheckNotNull(project->get(), "Error Getting Project Bit Depth. Project is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectBitDepth(*project, &bitDepth));
        return ProjBitDepth(bitDepth);
    });
    return future.get();
}

void ProjSuite::SetProjectBitDepth(ProjectPtr project, ProjBitDepth bitDepth)
{

    auto future = ae::ScheduleOrExecute([project, bitDepth]() {
        CheckNotNull(project->get(), "Error Setting Project Bit Depth. Project is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_SetProjectBitDepth(
            *project, AEGP_ProjBitDepth(bitDepth)));
    });
    future.wait();
}

ItemPtr ItemSuite::GetFirstProjItem(ProjectPtr project)
{
    auto future = ae::ScheduleOrExecute([project]() {
        CheckNotNull(project->get(), "Error Getting First Project Item. Project is Null");
        AEGP_ItemH itemH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetFirstProjItem(*project, &itemH));
        return makeItemPtr(itemH);
    });
    return future.get();
}

ItemPtr ItemSuite::GetNextProjItem(ProjectPtr project, ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([project, item]() {
        AEGP_ItemH nextItemH;
        CheckNotNull(project->get(), "Error Getting Next Project Item. Project is Null");
        CheckNotNull(project->get(), "Error Getting Next Project Item. Current Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetNextProjItem(*project, *item,
                                                                                                  &nextItemH));
        return makeItemPtr(nextItemH);
    });
    return future.get();
}

ItemPtr ItemSuite::GetActiveItem()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_ItemH itemH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetActiveItem(&itemH));
        CheckNotNull(itemH, "Error Getting Active Item. Active Item is Null");
        return makeItemPtr(itemH);
    });
    return future.get();
}

bool ItemSuite::IsItemSelected(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        A_Boolean isSelected;
        CheckNotNull(item->get(), "Error Checking if Item is Selected. Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_IsItemSelected(*item, &isSelected));
        return isSelected;
    });
    return future.get();
}

void ItemSuite::SelectItem(ItemPtr item, bool select, bool deselectOthers)
{

    auto future = ae::ScheduleOrExecute([item, select, deselectOthers]() {
        CheckNotNull(item->get(), "Error Selecting Item. Item is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SelectItem(*item, select, deselectOthers));
    });
    future.wait();
}

ItemType ItemSuite::GetItemType(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item Type. Item is Null");
        AEGP_ItemType itemType;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemType(*item, &itemType));
        return ItemType(itemType);
    });
    return future.get();
}

std::string ItemSuite::GetTypeName(ItemType itemType)
{

    auto future = ae::ScheduleOrExecute([itemType]() {
        A_char name[256];
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetTypeName(AEGP_ItemType(itemType),
                                                                                              name));
        return std::string(name);
    });
    return future.get();
}

std::string ItemSuite::GetItemName(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        AEGP_MemHandle nameH;
        CheckNotNull(item->get(), "Error Getting Item Name. Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemName(
            *SuiteManager::GetInstance().GetPluginID(), *item, &nameH));
        std::string name = memHandleToString(nameH);
        return name;
    });
    std::string name = future.get();
    return name;
    }

void ItemSuite::SetItemName(ItemPtr item, const std::string &name)
{
    auto future = ae::ScheduleOrExecute([item, name]() {
        CheckNotNull(item->get(), "Error Setting Item Name. Item is Null");
        std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemName(*item, name16.data()));
    });
    future.wait();
}

int ItemSuite::GetItemID(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item ID. Item is Null");
        A_long id;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemID(*item, &id));
        return id;
    });
    return future.get();
}

ItemFlag ItemSuite::GetItemFlags(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item Flags. Item is Null");
        int flags;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemFlags(*item, &flags));
        return ItemFlag(flags);
    });
    return future.get();
}

void ItemSuite::SetItemUseProxy(ItemPtr item, bool useProxy)
{
    auto future = ae::ScheduleOrExecute([item, useProxy]() {
        CheckNotNull(item->get(), "Error Setting Item Use Proxy. Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemUseProxy(*item, useProxy));
    });
    future.wait();
}

ItemPtr ItemSuite::GetItemParentFolder(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item Parent Folder. Item is Null");
        AEGP_ItemH parentFolderH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemParentFolder(*item,
                                                                                                      &parentFolderH));
        return makeItemPtr(parentFolderH);
    });
    return future.get();
}

void ItemSuite::SetItemParentFolder(ItemPtr item, ItemPtr parentFolder)
{
    auto future = ae::ScheduleOrExecute([item, parentFolder]() {
        CheckNotNull(item->get(), "Error Setting Item Parent Folder. Item is Null");
        if (parentFolder == nullptr)
        {
            AEGP_ItemH itemH;
            AEGP_ProjectH proj;
            AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectByIndex(0, &proj));
            AE_CHECK(
                SuiteManager::GetInstance().GetSuiteHandler().ProjSuite6()->AEGP_GetProjectRootFolder(proj, &itemH));
            AE_CHECK(
                SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemParentFolder(*item, itemH));
        }
        else
        {
            AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemParentFolder(
                *item, *parentFolder));
        }
    });
    future.wait();
}

Time ItemSuite::GetItemDuration(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item Duration. Item is Null");
        Time duration;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemDuration(*item,
                                                                                                  &duration.toAEGP()));
        return duration;
    });
    return future.get();
}

Time ItemSuite::GetItemCurrentTime(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item Current Time. Item is Null");
        Time currentTime;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemCurrentTime(
            *item, &currentTime.toAEGP()));
        return currentTime;
    });
    return future.get();
}

std::tuple<int, int> ItemSuite::GetItemDimensions(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item Dimensions. Item is Null");
        int width;
        int height;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemDimensions(*item, &width, &height));
        return std::make_tuple(width, height);
    });
    return future.get();
}

Ratio ItemSuite::GetItemPixelAspectRatio(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item Pixel Aspect Ratio. Item is Null");
        Ratio pixelAspectRatio;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemPixelAspectRatio(
            *item, &pixelAspectRatio.toAEGP()));
        return pixelAspectRatio;
    });
    return future.get();
}

void ItemSuite::DeleteItem(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute(
        [item]() { AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_DeleteItem(*item)); });
    future.wait();
}

ItemPtr ItemSuite::CreateNewFolder(const std::string &name, ItemPtr parentFolder)
{
    auto future = ae::ScheduleOrExecute([name, parentFolder]() {
        CheckNotNull(parentFolder->get(), "Error Creating New Folder. Parent Folder is Null");
        std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
        AEGP_ItemH folderH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_CreateNewFolder(
            name16.data(), *parentFolder, &folderH));
        return makeItemPtr(folderH);
    });
    return future.get();
}

void ItemSuite::SetItemCurrentTime(ItemPtr item, Time newTime)
{
    auto future = ae::ScheduleOrExecute([item, newTime]() {
        CheckNotNull(item->get(), "Error Setting Item Current Time. Item is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemCurrentTime(*item, &newTime.value));
    });
    future.wait();
}

std::string ItemSuite::GetItemComment(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item Comment. Item is Null");
        AEGP_MemHandle commentH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemComment(*item, &commentH));
        return memHandleToString(commentH);
    });
    return future.get();
}

void ItemSuite::SetItemComment(ItemPtr item, const std::string &comment)
{
    auto future = ae::ScheduleOrExecute([item, comment]() {
        CheckNotNull(item->get(), "Error Setting Item Comment. Item is Null");
        std::vector<A_UTF16Char> comment16 = ConvertUTF8ToUTF16(comment);
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemComment(*item, comment16.data()));
    });
    future.wait();
}

Label ItemSuite::GetItemLabel(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item Label. Item is Null");
        AEGP_LabelID label;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemLabel(*item, &label));
        return Label(label);
    });
    return future.get();
}

void ItemSuite::SetItemLabel(ItemPtr item, Label label)
{
    auto future = ae::ScheduleOrExecute([item, label]() {
        CheckNotNull(item->get(), "Error Setting Item Label. Item is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_SetItemLabel(*item, AEGP_LabelID(label)));
    });
    future.wait();
}

ItemViewPtr ItemSuite::GetItemMRUView(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Item MRU View. Item is Null");
        AEGP_ItemViewP itemViewH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemSuite9()->AEGP_GetItemMRUView(*item, &itemViewH));
        return makeItemViewPtr(itemViewH);
    });
    return future.get();
}

Time ItemSuite::GetItemViewPlaybackTime(ItemViewPtr itemView, bool &isCurrentlyPreviewing)
{
    auto future = ae::ScheduleOrExecute([itemView, &isCurrentlyPreviewing]() {
        CheckNotNull(itemView->get(), "Error Getting Item View Playback Time. Item View is Null");
        Time time;
        A_Boolean isPreviewing = static_cast<A_Boolean>(isCurrentlyPreviewing);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().ItemViewSuite1()->AEGP_GetItemViewPlaybackTime(
            *itemView, &isPreviewing, &time.toAEGP()));
        isCurrentlyPreviewing = isPreviewing;
        return time;
    });
    return future.get();
}

SoundDataPtr SoundDataSuite::NewSoundData(SoundDataFormat soundFormat)
{
    auto future = ae::ScheduleOrExecute([&soundFormat]() {
        AEGP_SoundDataH soundDataH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_NewSoundData(
            &soundFormat.toAEGP(), &soundDataH));
        return makeSoundDataPtr(soundDataH);
    });
    return future.get();
}

SoundDataFormat SoundDataSuite::GetSoundDataFormat(SoundDataPtr soundData)
{
    auto future = ae::ScheduleOrExecute([soundData]() {
        CheckNotNull(soundData->get(), "Error Getting Sound Data Format. Sound Data is Null");
        AEGP_SoundDataFormat format;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_GetSoundDataFormat(*soundData,
                                                                                                          &format));
        return SoundDataFormat(format);
    });
    return future.get();
}

void SoundDataSuite::LockSoundDataSamples(SoundDataPtr soundData, void **samples)
{
    auto future = ae::ScheduleOrExecute([soundData, samples]() {
        CheckNotNull(soundData->get(), "Error Locking Sound Data Samples. Sound Data is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_LockSoundDataSamples(*soundData,
                                                                                                            samples));
    });
    future.wait();
}

void SoundDataSuite::UnlockSoundDataSamples(SoundDataPtr soundData)
{

    auto future = ae::ScheduleOrExecute([soundData]() {
        CheckNotNull(soundData->get(), "Error Unlocking Sound Data Samples. Sound Data is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_UnlockSoundDataSamples(*soundData));
    });
    future.wait();
}

int SoundDataSuite::GetNumSamples(SoundDataPtr soundData)
{
    auto future = ae::ScheduleOrExecute([soundData]() {
        CheckNotNull(soundData->get(), "Error Getting Number of Samples. Sound Data is Null");
        int numSamples;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().SoundDataSuite1()->AEGP_GetNumSamples(*soundData,
                                                                                                     &numSamples));
        return numSamples;
    });
    return future.get();
}

CompPtr CompSuite::GetCompFromItem(ItemPtr item)
{
    auto future = ae::ScheduleOrExecute([item]() {
        CheckNotNull(item->get(), "Error Getting Comp From Item. Item is Null");
        AEGP_CompH compH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFromItem(*item, &compH));
        return makeCompPtr(compH);
    });
    return future.get();
}

ItemPtr CompSuite::GetItemFromComp(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Item From Comp. Comp is Null");
        AEGP_ItemH itemH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetItemFromComp(*comp, &itemH));
        return makeItemPtr(itemH);
    });
    return future.get();
}

DownsampleFactor CompSuite::GetCompDownsampleFactor(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        AEGP_DownsampleFactor factor;
        CheckNotNull(comp->get(), "Error Getting Comp Downsample Factor. Comp is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompDownsampleFactor(*comp, &factor));
        return DownsampleFactor(factor);
    });
    return future.get();
}

void CompSuite::SetCompDownsampleFactor(CompPtr comp, DownsampleFactor dsf)
{
    auto future = ae::ScheduleOrExecute([comp, &dsf]() {
        CheckNotNull(comp->get(), "Error Setting Comp Downsample Factor. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompDownsampleFactor(
            *comp, &dsf.toAEGP()));
    });
    future.wait();
}

ColorVal CompSuite::GetCompBGColor(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Background Color. Comp is Null");
        AEGP_ColorVal color;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompBGColor(*comp, &color));
        return ColorVal(color);
    });
    return future.get();
}

void CompSuite::SetCompBGColor(CompPtr comp, ColorVal color)
{
    auto future = ae::ScheduleOrExecute([comp, &color]() {
        CheckNotNull(comp->get(), "Error Setting Comp Background Color. Comp is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompBGColor(*comp, &color.toAEGP()));
    });
    future.wait();
}

CompFlag CompSuite::GetCompFlags(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Flags. Comp is Null");
        int flags;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFlags(*comp, &flags));
        return CompFlag(flags);
    });
    return future.get();
}

bool CompSuite::GetShowLayerNameOrSourceName(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Show Layer Name or Source Name. Comp is Null");
        A_Boolean showLayerName;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetShowLayerNameOrSourceName(
            *comp, &showLayerName));
        return showLayerName;
    });
    return future.get();
}

void CompSuite::SetShowLayerNameOrSourceName(CompPtr comp, bool showLayerName)
{
    auto future = ae::ScheduleOrExecute([comp, showLayerName]() {
        CheckNotNull(comp->get(), "Error Setting Show Layer Name or Source Name. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetShowLayerNameOrSourceName(
            *comp, showLayerName));
    });
    future.wait();
}

bool CompSuite::GetShowBlendModes(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Show Blend Modes. Comp is Null");
        A_Boolean showBlendModes;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetShowBlendModes(*comp,
                                                                                                     &showBlendModes));
        return showBlendModes;
    });
    return future.get();
}

void CompSuite::SetShowBlendModes(CompPtr comp, bool showBlendModes)
{

    auto future = ae::ScheduleOrExecute([comp, showBlendModes]() {
        CheckNotNull(comp->get(), "Error Setting Show Blend Modes. Comp is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetShowBlendModes(*comp, showBlendModes));
    });
    future.wait();
}

double CompSuite::GetCompFramerate(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Frame Rate. Comp is Null");
        double fps;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFramerate(*comp, &fps));
        return fps;
    });
    return future.get();
}

void CompSuite::SetCompFrameRate(CompPtr comp, double fps)
{
    auto future = ae::ScheduleOrExecute([comp, fps]() {
        CheckNotNull(comp->get(), "Error Setting Comp Frame Rate. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompFrameRate(*comp, &fps));
    });
    future.wait();
}

std::tuple<Ratio, Ratio> CompSuite::GetCompShutterAnglePhase(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Shutter Angle Phase. Comp is Null");
        Ratio angle;
        Ratio phase;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompShutterAnglePhase(
            *comp, &angle.toAEGP(), &phase.toAEGP()));
        return std::make_tuple(angle, phase);
    });
    return future.get();
}

std::tuple<Time, Time> CompSuite::GetCompShutterFrameRange(CompPtr comp, Time compTime)
{

    auto future = ae::ScheduleOrExecute([comp, compTime]() {
        CheckNotNull(comp->get(), "Error Getting Comp Shutter Frame Range. Comp is Null");
        return std::tuple<Time, Time>();
    });
    return future.get();
}

int CompSuite::GetCompSuggestedMotionBlurSamples(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Suggested Motion Blur Samples. Comp is Null");
        int samples;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompSuggestedMotionBlurSamples(
            *comp, &samples));
        return samples;
    });
    return future.get();
}

void CompSuite::SetCompSuggestedMotionBlurSamples(CompPtr comp, int samples)
{

    auto future = ae::ScheduleOrExecute([comp, samples]() {
        CheckNotNull(comp->get(), "Error Setting Comp Suggested Motion Blur Samples. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompSuggestedMotionBlurSamples(
            *comp, samples));
    });
    future.wait();
}

int CompSuite::GetCompMotionBlurAdaptiveSampleLimit(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Motion Blur Adaptive Sample Limit. Comp is Null");
        int samples;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompMotionBlurAdaptiveSampleLimit(
            *comp, &samples));
        return samples;
    });
    return future.get();
}

void CompSuite::SetCompMotionBlurAdaptiveSampleLimit(CompPtr comp, int samples)
{
    auto future = ae::ScheduleOrExecute([comp, samples]() {
        CheckNotNull(comp->get(), "Error Setting Comp Motion Blur Adaptive Sample Limit. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompMotionBlurAdaptiveSampleLimit(
            *comp, samples));
    });
    future.wait();
}

Time CompSuite::GetCompWorkAreaStart(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Work Area Start. Comp is Null");
        Time workAreaStart;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompWorkAreaStart(
            *comp, &workAreaStart.toAEGP()));
        return workAreaStart;
    });
    return future.get();
}

Time CompSuite::GetCompWorkAreaDuration(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Work Area Duration. Comp is Null");
        Time workAreaDuration;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompWorkAreaDuration(
            *comp, &workAreaDuration.toAEGP()));
        return workAreaDuration;
    });
    return future.get();
}

void CompSuite::SetCompWorkAreaStartAndDuration(CompPtr comp, Time workAreaStart, Time workAreaDuration)
{
    auto future = ae::ScheduleOrExecute([comp, workAreaStart, workAreaDuration]() {
        CheckNotNull(comp->get(), "Error Setting Comp Work Area Start and Duration. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompWorkAreaStartAndDuration(
            *comp, &workAreaStart.value, &workAreaDuration.value));
    });
    future.wait();
}

LayerPtr CompSuite::CreateSolidInComp(CompPtr comp, const std::string &name, int width, int height, ColorVal color,
                                      Time duration)
{
    auto future = ae::ScheduleOrExecute([comp, name, width, height, &color, &duration]() {
        CheckNotNull(comp->get(), "Error Creating Solid in Comp. Comp is Null");
        AEGP_LayerH layerH;
        std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateSolidInComp(
            name16.data(), width, height, &color.toAEGP(), *comp, &duration.toAEGP(), &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

LayerPtr CompSuite::CreateCameraInComp(CompPtr comp, const std::string &name, FloatPoint centerPoint)
{
    auto future = ae::ScheduleOrExecute([comp, name, &centerPoint]() {
        CheckNotNull(comp->get(), "Error Creating Camera in Comp. Comp is Null");
        AEGP_LayerH layerH;
        std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateCameraInComp(
            name16.data(), centerPoint.toAEGP(), *comp, &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

LayerPtr CompSuite::CreateLightInComp(CompPtr comp, const std::string &name, FloatPoint centerPoint)
{
    auto future = ae::ScheduleOrExecute([comp, name, &centerPoint]() {
        CheckNotNull(comp->get(), "Error Creating Light in Comp. Comp is Null");
        AEGP_LayerH layerH;
        std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateLightInComp(
            name16.data(), centerPoint.toAEGP(), *comp, &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

CompPtr CompSuite::CreateComp(ItemPtr parentFolder, const std::string &name, int width, int height,
                              Ratio pixelAspectRatio, Time duration, Ratio framerate)
{
    auto future =
        ae::ScheduleOrExecute([parentFolder, name, width, height, &pixelAspectRatio, &duration, &framerate]() {
            std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
            AEGP_CompH compH;
            AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateComp(
                *parentFolder, name16.data(), width, height, &pixelAspectRatio.toAEGP(), &duration.toAEGP(),
                &framerate.toAEGP(), &compH));
            return makeCompPtr(compH);
        });
    return future.get();
}

Collection2Ptr CompSuite::GetNewCollectionFromCompSelection(AEGP_PluginID pluginId, CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([pluginId, comp]() {
        CheckNotNull(comp->get(), "Error Getting New Collection From Comp Selection. Comp is Null");
        AEGP_Collection2H collectionH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetNewCollectionFromCompSelection(
            pluginId, *comp, &collectionH));
        return makeCollection2Ptr(collectionH);
    });
    return future.get();
}

Time CompSuite::GetCompDisplayStartTime(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Display Start Time. Comp is Null");
        Time startTime;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompDisplayStartTime(
            *comp, &startTime.toAEGP()));
        return startTime;
    });
    return future.get();
}

void CompSuite::SetCompDisplayStartTime(CompPtr comp, Time startTime)
{
    auto future = ae::ScheduleOrExecute([comp, startTime]() {
        CheckNotNull(comp->get(), "Error Setting Comp Display Start Time. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompDisplayStartTime(
            *comp, &startTime.toAEGP()));
    });
    future.wait();
}

void CompSuite::SetCompDuration(CompPtr comp, Time duration)
{
    auto future = ae::ScheduleOrExecute([comp, duration]() {
        CheckNotNull(comp->get(), "Error Setting Comp Duration. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompDuration(*comp,
                                                                                                   &duration.toAEGP()));
    });
    future.wait();
}

void CompSuite::SetCompDimensions(CompPtr comp, int width, int height)
{
    auto future = ae::ScheduleOrExecute([comp, width, height]() {
        CheckNotNull(comp->get(), "Error Setting Comp Dimensions. Comp is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompDimensions(*comp, width, height));
    });
    future.wait();
}

void CompSuite::SetCompPixelAspectRatio(CompPtr comp, Ratio pixelAspectRatio)
{
    auto future = ae::ScheduleOrExecute([comp, &pixelAspectRatio]() {
        CheckNotNull(comp->get(), "Error Setting Comp Pixel Aspect Ratio. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompPixelAspectRatio(
            *comp, &pixelAspectRatio.toAEGP()));
    });
    future.wait();
}

LayerPtr CompSuite::CreateTextLayerInComp(CompPtr comp, bool newLayer)
{
    auto future = ae::ScheduleOrExecute([comp, newLayer]() {
        CheckNotNull(comp->get(), "Error Creating Text Layer in Comp. Comp is Null");
        AEGP_LayerH layerH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateTextLayerInComp(
            *comp, newLayer, &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

LayerPtr CompSuite::CreateBoxTextLayerInComp(CompPtr comp, FloatPoint boxDimensions, bool newLayer)
{
    auto future = ae::ScheduleOrExecute([comp, &boxDimensions, newLayer]() {
        CheckNotNull(comp->get(), "Error Creating Box Text Layer in Comp. Comp is Null");
        AEGP_LayerH layerH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateBoxTextLayerInComp(
            *comp, newLayer, boxDimensions.toAEGP(), &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

LayerPtr CompSuite::CreateNullInComp(CompPtr comp, const std::string &name, Time duration)
{
    auto future = ae::ScheduleOrExecute([comp, name, duration]() {
        CheckNotNull(comp->get(), "Error Creating Null in Comp. Comp is Null");
        std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(name);
        AEGP_LayerH layerH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateNullInComp(
            name16.data(), *comp, &duration.toAEGP(), &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

CompPtr CompSuite::DuplicateComp(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Duplicating Comp. Comp is Null");
        AEGP_CompH newCompH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_DuplicateComp(*comp, &newCompH));
        return makeCompPtr(newCompH);
    });
    return future.get();
}

Time CompSuite::GetCompFrameDuration(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Frame Duration. Comp is Null");
        Time frameDuration;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompFrameDuration(
            *comp, &frameDuration.toAEGP()));
        return frameDuration;
    });
    return future.get();
}

CompPtr CompSuite::GetMostRecentlyUsedComp()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_CompH compH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetMostRecentlyUsedComp(&compH));
        return makeCompPtr(compH);
    });
    return future.get();
}

LayerPtr CompSuite::CreateVectorLayerInComp(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Creating Vector Layer in Comp. Comp is Null");
        AEGP_LayerH layerH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_CreateVectorLayerInComp(*comp, &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

StreamRefPtr CompSuite::GetNewCompMarkerStream(CompPtr parentComp)
{
    auto future = ae::ScheduleOrExecute([parentComp]() {
        CheckNotNull(parentComp->get(), "Error Getting New Comp Marker Stream. Parent Comp is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetNewCompMarkerStream(
            *SuiteManager::GetInstance().GetPluginID(), *parentComp, &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

bool CompSuite::GetCompDisplayDropFrame(CompPtr comp)
{
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(comp->get(), "Error Getting Comp Display Drop Frame. Comp is Null");
        A_Boolean dropFrame;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_GetCompDisplayDropFrame(*comp,
                                                                                                           &dropFrame));
        return dropFrame;
    });
    return future.get();
}

void CompSuite::SetCompDisplayDropFrame(CompPtr comp, bool dropFrame)
{
    auto future = ae::ScheduleOrExecute([comp, dropFrame]() {
        CheckNotNull(comp->get(), "Error Setting Comp Display Drop Frame. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_SetCompDisplayDropFrame(*comp,
                                                                                                           dropFrame));
    });
    future.wait();
}

void CompSuite::ReorderCompSelection(CompPtr comp, int index)
{
    auto future = ae::ScheduleOrExecute([comp, index]() {
        CheckNotNull(comp->get(), "Error Reordering Comp Selection. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CompSuite11()->AEGP_ReorderCompSelection(*comp, index));
    });
    future.wait();
}

MemHandlePtr MemorySuite::NewMemHandle(const std::string &what, AEGP_MemSize size, MemFlag flags)
{
    AEGP_MemHandle memHandle;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_NewMemHandle(
        *SuiteManager::GetInstance().GetPluginID(), what.c_str(), size, AEGP_MemFlag(flags), &memHandle));
    return makeMemHandlePtr(memHandle);
}

void MemorySuite::FreeMemHandle(MemHandlePtr memH)
{
    CheckNotNull(memH->get(), "Error Freeing Memory Handle. Memory Handle is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_FreeMemHandle(*memH));
}

void MemorySuite::LockMemHandle(MemHandlePtr memHandle, void **ptrToPtr)
{
    CheckNotNull(&memHandle, "Error Locking Memory Handle. Memory Handle is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_LockMemHandle(*memHandle, ptrToPtr));
}

void MemorySuite::UnlockMemHandle(MemHandlePtr memHandle)
{

    CheckNotNull(&memHandle, "Error Unlocking Memory Handle. Memory Handle is Null");
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_UnlockMemHandle(*memHandle));
}

AEGP_MemSize MemorySuite::GetMemHandleSize(MemHandlePtr memHandle)
{
    CheckNotNull(&memHandle, "Error Getting Memory Handle Size. Memory Handle is Null");
    AEGP_MemSize size;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MemorySuite1()->AEGP_GetMemHandleSize(*memHandle, &size));
    return size;
}

void MemorySuite::ResizeMemHandle(const std::string &what, AEGP_MemSize newSize, MemHandlePtr memHandle)
{
    CheckNotNull(&memHandle, "Error Resizing Memory Handle. Memory Handle is Null");
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
    auto future = ae::ScheduleOrExecute([comp]() {
        CheckNotNull(&comp, "Error Getting Comp Number of Layers. Comp is Null");
        int numLayers;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetCompNumLayers(*comp, &numLayers));
        return numLayers;
    });
    return future.get();
}

LayerPtr LayerSuite::GetCompLayerByIndex(CompPtr comp, int layerIndex)
{
    auto future = ae::ScheduleOrExecute([comp, layerIndex]() {
        CheckNotNull(&comp, "Error Getting Comp Layer by Index. Comp is Null.");
        AEGP_LayerH layerH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetCompLayerByIndex(
            *comp, layerIndex, &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

LayerPtr LayerSuite::GetActiveLayer()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_LayerH layerH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetActiveLayer(&layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

int LayerSuite::GetLayerIndex(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        int index;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerIndex(*layer, &index));
        return index;
    });
    return future.get();
}

ItemPtr LayerSuite::GetLayerSourceItem(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Source Item. Layer is Null");
        AEGP_ItemH itemH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerSourceItem(*layer, &itemH));
        return makeItemPtr(itemH);
    });
    return future.get();
}

int LayerSuite::GetLayerSourceItemID(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Source Item ID. Layer is Null");
        int id;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerSourceItemID(*layer, &id));
        return id;
    });
    return future.get();
}

CompPtr LayerSuite::GetLayerParentComp(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Parent Comp. Layer is Null");
        AEGP_CompH compH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerParentComp(*layer, &compH));
        return makeCompPtr(compH);
    });
    return future.get();
}

std::tuple<std::string, std::string> LayerSuite::GetLayerName(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Name. Layer is Null");
        AEGP_MemHandle nameH;
        AEGP_MemHandle sourceNameH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerName(
            *SuiteManager::GetInstance().GetPluginID(), *layer, &nameH, &sourceNameH));
        return std::make_tuple(memHandleToString(nameH), memHandleToString(sourceNameH));
    });
    return future.get();
}

LayerQual LayerSuite::GetLayerQuality(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Quality. Layer is Null");
        AEGP_LayerQuality quality;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerQuality(*layer, &quality));
        return LayerQual(quality);
    });
    return future.get();
}

void LayerSuite::SetLayerQuality(LayerPtr layer, LayerQual quality)
{
    ae::ScheduleOrExecute([layer, quality]() {
        CheckNotNull(&layer, "Error Setting Layer Quality. Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerQuality(
            *layer, AEGP_LayerQuality(quality)));
    }).wait();
}

LayerFlag LayerSuite::GetLayerFlags(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Flags. Layer is Null");
        int flags;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerFlags(*layer, &flags));
        return LayerFlag(flags);
    });
    return future.get();
}

void LayerSuite::SetLayerFlag(LayerPtr layer, LayerFlag singleFlag, bool value)
{
    ae::ScheduleOrExecute([layer, singleFlag, value]() {
        CheckNotNull(&layer, "Error Setting Layer Flag. Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerFlag(
            *layer, AEGP_LayerFlags(singleFlag), value));
    }).wait();
}

bool LayerSuite::IsLayerVideoReallyOn(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Checking if Layer Video is Really On. Layer is Null");
        A_Boolean isOn;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayerVideoReallyOn(*layer, &isOn));
        return static_cast<bool>(isOn);
    });
    return future.get();
}

bool LayerSuite::IsLayerAudioReallyOn(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Checking if Layer Audio is Really On. Layer is Null");
        A_Boolean isOn;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayerAudioReallyOn(*layer, &isOn));
        return static_cast<bool>(isOn);
    });
    return future.get();
}

Time LayerSuite::GetLayerCurrentTime(LayerPtr layer, LTimeMode timeMode)
{
    auto future = ae::ScheduleOrExecute([layer, timeMode]() {
        CheckNotNull(&layer, "Error Getting Layer Current Time. Layer is Null");
        Time time;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerCurrentTime(
            *layer, AEGP_LTimeMode(timeMode), &time.toAEGP()));
        return time;
    });
    return future.get();
}

Time LayerSuite::GetLayerInPoint(LayerPtr layer, LTimeMode timeMode)
{
    auto future = ae::ScheduleOrExecute([layer, timeMode]() {
        CheckNotNull(&layer, "Error Getting Layer In Point. Layer is Null");
        Time time;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerInPoint(
            *layer, AEGP_LTimeMode(timeMode), &time.toAEGP()));
        return time;
    });
    return future.get();
}

Time LayerSuite::GetLayerDuration(LayerPtr layer, LTimeMode timeMode)
{
    auto future = ae::ScheduleOrExecute([layer, timeMode]() {
        CheckNotNull(&layer, "Error Getting Layer Duration. Layer is Null");
        Time time;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerDuration(
            *layer, AEGP_LTimeMode(timeMode), &time.toAEGP()));
        return time;
    });
    return future.get();
}

void LayerSuite::SetLayerInPointAndDuration(LayerPtr layer, LTimeMode timeMode, Time inPoint, Time duration)
{
    ae::ScheduleOrExecute([layer, timeMode, inPoint, duration]() {
        CheckNotNull(&layer, "Error Setting Layer In Point and Duration. Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerInPointAndDuration(
            *layer, AEGP_LTimeMode(timeMode), &inPoint.toAEGP(), &duration.toAEGP()));
    }).wait();
}

Time LayerSuite::GetLayerOffset(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Offset. Layer is Null");
        Time offset;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerOffset(*layer, &offset.toAEGP()));
        return offset;
    });
    return future.get();
}

void LayerSuite::SetLayerOffset(LayerPtr layer, Time offset)
{
    ae::ScheduleOrExecute([layer, offset]() {
        CheckNotNull(&layer, "Error Setting Layer Offset. Layer is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerOffset(*layer, &offset.toAEGP()));
    }).wait();
}

Ratio LayerSuite::GetLayerStretch(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Stretch. Layer is Null");
        Ratio stretch;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerStretch(*layer,
                                                                                                   &stretch.toAEGP()));
        return stretch;
    });
    return future.get();
}

void LayerSuite::SetLayerStretch(LayerPtr layer, Ratio stretch)
{
    auto future = ae::ScheduleOrExecute([layer, &stretch]() {
        CheckNotNull(&layer, "Error Setting Layer Stretch. Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerStretch(*layer,
                                                                                                   &stretch.toAEGP()));
    });
    future.wait();
}

std::tuple<TransferFlags, TrackMatte> LayerSuite::GetLayerTransferMode(LayerPtr layer)
{
    return std::make_tuple(TransferFlags::PRESERVE_ALPHA, TrackMatte::ALPHA);
}

void LayerSuite::SetLayerTransferMode(LayerPtr layer, TransferFlags flags, TrackMatte trackMatte) {}

bool LayerSuite::IsAddLayerValid(ItemPtr itemToAdd, CompPtr intoComp)
{
    auto future = ae::ScheduleOrExecute([itemToAdd, intoComp]() {
        CheckNotNull(&itemToAdd, "Error Checking if Add Layer is Valid. Item to Add is Null");
        CheckNotNull(&intoComp, "Error Checking if Add Layer is Valid. Comp is Null");
        A_Boolean isValid;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsAddLayerValid(
            *itemToAdd, *intoComp, &isValid));
        return static_cast<bool>(isValid);
    });
    return future.get();
}

LayerPtr LayerSuite::AddLayer(ItemPtr itemToAdd, CompPtr intoComp)
{
    auto future = ae::ScheduleOrExecute([itemToAdd, intoComp]() {
        CheckNotNull(&itemToAdd, "Error Adding Layer. Item to Add is Null");
        CheckNotNull(&intoComp, "Error Adding Layer. Comp is Null");
        AEGP_LayerH layerH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_AddLayer(*itemToAdd, *intoComp, &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

void LayerSuite::ReorderLayer(LayerPtr layer, int layerIndex)
{
    auto future = ae::ScheduleOrExecute([layer, layerIndex]() {
        CheckNotNull(&layer, "Error Reordering Layer. Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_ReorderLayer(*layer, layerIndex));
    });
    future.wait();
}

FloatRect LayerSuite::GetLayerMaskedBounds(LayerPtr layer, LTimeMode timeMode, Time time)
{
    auto future = ae::ScheduleOrExecute([layer, timeMode, time]() {
        CheckNotNull(&layer, "Error Getting Layer Masked Bounds. Layer is Null");
        A_FloatRect bounds;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerMaskedBounds(
            *layer, AEGP_LTimeMode(timeMode), &time.toAEGP(), &bounds));
        return FloatRect(bounds);
    });
    return future.get();
}

ObjectType LayerSuite::GetLayerObjectType(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Object Type. Layer is Null");
        AEGP_ObjectType type;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerObjectType(*layer, &type));
        return ObjectType(type);
    });
    return future.get();
}

bool LayerSuite::IsLayer3D(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Checking if Layer is 3D. Layer is Null");
        A_Boolean is3D;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayer3D(*layer, &is3D));
        return static_cast<bool>(is3D);
    });
    return future.get();
}

bool LayerSuite::IsLayer2D(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Checking if Layer is 2D. Layer is Null");
        A_Boolean is2D;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayer2D(*layer, &is2D));
        return static_cast<bool>(is2D);
    });
    return future.get();
}

bool LayerSuite::IsVideoActive(LayerPtr layer, LTimeMode timeMode, Time time)
{
    auto future = ae::ScheduleOrExecute([layer, timeMode, time]() {
        CheckNotNull(&layer, "Error Checking if Video is Active. Layer is Null");
        A_Boolean isActive;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsVideoActive(
            *layer, AEGP_LTimeMode(timeMode), &time.toAEGP(), &isActive));
        return static_cast<bool>(isActive);
    });
    return future.get();
}

bool LayerSuite::IsLayerUsedAsTrackMatte(LayerPtr layer, bool fillMustBeActive)
{
    auto future = ae::ScheduleOrExecute([layer, fillMustBeActive]() {
        CheckNotNull(&layer, "Error Checking if Layer is Used as Track Matte. Layer is Null");
        A_Boolean isUsed;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_IsLayerUsedAsTrackMatte(
            *layer, fillMustBeActive, &isUsed));
        return static_cast<bool>(isUsed);
    });
    return future.get();
}

bool LayerSuite::DoesLayerHaveTrackMatte(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Checking if Layer has Track Matte. Layer is Null");
        A_Boolean hasTrackMatte;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_DoesLayerHaveTrackMatte(
            *layer, &hasTrackMatte));
        return static_cast<bool>(hasTrackMatte);
    });
    return future.get();
}

Time LayerSuite::ConvertCompToLayerTime(LayerPtr layer, Time compTime)
{
    auto future = ae::ScheduleOrExecute([layer, compTime]() {
        CheckNotNull(&layer, "Error Converting Comp to Layer Time. Layer is Null");
        Time layerTime;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_ConvertCompToLayerTime(
            *layer, &compTime.toAEGP(), &layerTime.toAEGP()));
        return layerTime;
    });
    return future.get();
}

Time LayerSuite::ConvertLayerToCompTime(LayerPtr layer, Time layerTime)
{
    auto future = ae::ScheduleOrExecute([layer, layerTime]() {
        CheckNotNull(&layer, "Error Converting Layer to Comp Time. Layer is Null");
        Time compTime;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_ConvertLayerToCompTime(
            *layer, &compTime.toAEGP(), &layerTime.toAEGP()));
        return compTime;
    });
    return future.get();
}

int LayerSuite::GetLayerDancingRandValue(LayerPtr layer, Time compTime)
{
    auto future = ae::ScheduleOrExecute([layer, compTime]() {
        CheckNotNull(&layer, "Error Getting Layer Dancing Rand Value. Layer is Null");
        int randValue;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerDancingRandValue(
            *layer, &compTime.toAEGP(), &randValue));
        return randValue;
    });
    return future.get();
}

AEGP_LayerIDVal LayerSuite::GetLayerID(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer ID. Layer is Null");
        AEGP_LayerIDVal id;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerID(*layer, &id));
        return id;
    });
    return future.get();
}

Matrix4 LayerSuite::GetLayerToWorldXform(LayerPtr layer, Time compTime)
{
    auto future = ae::ScheduleOrExecute([layer, compTime]() {
        CheckNotNull(&layer, "Error Getting Layer to World Xform. Layer is Null");
        A_Matrix4 xform;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerToWorldXform(
            *layer, &compTime.toAEGP(), &xform));
        return Matrix4(xform);
    });
    return future.get();
}

Matrix4 LayerSuite::GetLayerToWorldXformFromView(LayerPtr layer, Time viewTime, Time compTime)
{
    auto future = ae::ScheduleOrExecute([layer, viewTime, compTime]() {
        CheckNotNull(&layer, "Error Getting Layer to World Xform from View. Layer is Null");
        A_Matrix4 xform;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerToWorldXformFromView(
            *layer, &viewTime.toAEGP(), &compTime.toAEGP(), &xform));
        return Matrix4(xform);
    });
    return future.get();
}

void LayerSuite::SetLayerName(LayerPtr layer, const std::string &newName)
{
    auto future = ae::ScheduleOrExecute([layer, newName]() {
        CheckNotNull(&layer, "Error Setting Layer Name. Layer is Null");
        std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(newName);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerName(*layer, name16.data()));
    });
    future.wait();
}

LayerPtr LayerSuite::GetLayerParent(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Parent. Layer is Null");
        AEGP_LayerH parentLayerH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerParent(*layer, &parentLayerH));
        return makeLayerPtr(parentLayerH);
    });
    return future.get();
}

void LayerSuite::SetLayerParent(LayerPtr layer, LayerPtr parentLayer)
{
    auto future = ae::ScheduleOrExecute([layer, parentLayer]() {
        CheckNotNull(&layer, "Error Setting Layer Parent. Layer is Null");
        CheckNotNull(&parentLayer, "Error Setting Layer Parent. Parent Layer is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerParent(*layer, *parentLayer));
    });
    future.wait();
}

void LayerSuite::DeleteLayer(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Deleting Layer. Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_DeleteLayer(*layer));
    });
    future.wait();
}

LayerPtr LayerSuite::DuplicateLayer(LayerPtr origLayer)
{
    auto future = ae::ScheduleOrExecute([origLayer]() {
        CheckNotNull(&origLayer, "Error Duplicating Layer. Original Layer is Null");
        AEGP_LayerH newLayerH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_DuplicateLayer(*origLayer, &newLayerH));
        return makeLayerPtr(newLayerH);
    });
    return future.get();
}

LayerPtr LayerSuite::GetLayerFromLayerID(CompPtr parentComp, AEGP_LayerIDVal id)
{
    auto future = ae::ScheduleOrExecute([parentComp, id]() {
        CheckNotNull(&parentComp, "Error Getting Layer from Layer ID. Parent Comp is Null");
        AEGP_LayerH layerH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerFromLayerID(*parentComp, id,
                                                                                                       &layerH));
        return makeLayerPtr(layerH);
    });
    return future.get();
}

Label LayerSuite::GetLayerLabel(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Label. Layer is Null");
        AEGP_LabelID label;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerLabel(*layer, &label));
        return Label(label);
    });
    return future.get();
}

void LayerSuite::SetLayerLabel(LayerPtr layer, Label label)
{
    auto future = ae::ScheduleOrExecute([layer, label]() {
        CheckNotNull(&layer, "Error Setting Layer Label. Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerLabel(*layer,
                                                                                                 AEGP_LabelID(label)));
    });
    future.wait();
}

LayerSamplingQual LayerSuite::GetLayerSamplingQuality(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Sampling Quality. Layer is Null");
        AEGP_LayerSamplingQuality quality;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetLayerSamplingQuality(*layer,
                                                                                                           &quality));
        return LayerSamplingQual(quality);
    });
    return future.get();
}

void LayerSuite::SetLayerSamplingQuality(LayerPtr layer, LayerSamplingQual quality)
{
    auto future = ae::ScheduleOrExecute([layer, quality]() {
        CheckNotNull(&layer, "Error Setting Layer Sampling Quality. Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetLayerSamplingQuality(
            *layer, AEGP_LayerSamplingQuality(quality)));
    });
    future.wait();
}

LayerPtr LayerSuite::GetTrackMatteLayer(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Track Matte Layer. Layer is Null");
        AEGP_LayerH matteLayerH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_GetTrackMatteLayer(*layer, &matteLayerH));
        return makeLayerPtr(matteLayerH);
    });
    return future.get();
}

void LayerSuite::SetTrackMatte(LayerPtr layer, LayerPtr trackMatteLayer, TrackMatte trackMatteType)
{
    auto future = ae::ScheduleOrExecute([layer, trackMatteLayer, trackMatteType]() {
        CheckNotNull(&layer, "Error Setting Track Matte. Layer is Null");
        CheckNotNull(&trackMatteLayer, "Error Setting Track Matte. Track Matte Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_SetTrackMatte(
            *layer, *trackMatteLayer, AEGP_TrackMatte(trackMatteType)));
    });
    future.wait();
}

void LayerSuite::RemoveTrackMatte(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Removing Track Matte. Layer is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerSuite9()->AEGP_RemoveTrackMatte(*layer));
    });
    future.wait();
}

bool StreamSuite::IsStreamLegal(LayerPtr layer, LayerStream whichStream)
{
    auto future = ae::ScheduleOrExecute([layer, whichStream]() {
        CheckNotNull(&layer, "Error Checking if Stream is Legal. Layer is Null");
        A_Boolean isLegal;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_IsStreamLegal(
            *layer, AEGP_LayerStream(whichStream), &isLegal));
        return static_cast<bool>(isLegal);
    });
    return future.get();
}

bool StreamSuite::CanVaryOverTime(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Checking if Stream Can Vary Over Time. Stream is Null");
        A_Boolean canVary;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_CanVaryOverTime(*stream, &canVary));
        return static_cast<bool>(canVary);
    });
    return future.get();
}

KeyInterpMask StreamSuite::GetValidInterpolations(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Valid Interpolations. Stream is Null");
        A_long validInterps;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetValidInterpolations(
            *stream, &validInterps));
        return KeyInterpMask(validInterps);
    });
    return future.get();
}

StreamRefPtr StreamSuite::GetNewLayerStream(LayerPtr layer, LayerStream whichStream)
{
    auto future = ae::ScheduleOrExecute([layer, whichStream]() {
        CheckNotNull(&layer, "Error Getting New Layer Stream. Layer is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetNewLayerStream(
            *SuiteManager::GetInstance().GetPluginID(), *layer, AEGP_LayerStream(whichStream), &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

int StreamSuite::GetEffectNumParamStreams(EffectRefPtr effectRef)
{
    auto future = ae::ScheduleOrExecute([effectRef]() {
        CheckNotNull(&effectRef, "Error Getting Effect Number of Param Streams. Effect is Null");
        int numStreams;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetEffectNumParamStreams(
            *effectRef, &numStreams));
        return numStreams;
    });
    return future.get();
}

StreamRefPtr StreamSuite::GetNewEffectStreamByIndex(EffectRefPtr effectRef, int paramIndex)
{
    auto future = ae::ScheduleOrExecute([effectRef, paramIndex]() {
        CheckNotNull(&effectRef, "Error Getting New Effect Stream by Index. Effect is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetNewEffectStreamByIndex(
            *SuiteManager::GetInstance().GetPluginID(), *effectRef, paramIndex, &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

StreamRefPtr StreamSuite::GetNewMaskStream(MaskRefPtr maskRef, MaskStream whichStream)
{
    auto future = ae::ScheduleOrExecute([maskRef, whichStream]() {
        CheckNotNull(&maskRef, "Error Getting New Mask Stream. Mask is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetNewMaskStream(
            *SuiteManager::GetInstance().GetPluginID(), *maskRef, AEGP_MaskStream(whichStream), &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

std::string StreamSuite::GetStreamName(StreamRefPtr stream, bool forceEnglish)
{
    auto future = ae::ScheduleOrExecute([stream, forceEnglish]() {
        CheckNotNull(&stream, "Error Getting Stream Name. Stream is Null");
        AEGP_MemHandle nameH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetStreamName(
            *SuiteManager::GetInstance().GetPluginID(), *stream, forceEnglish, &nameH));
        return memHandleToString(nameH);
    });
    return future.get();
}

std::string StreamSuite::GetStreamUnitsText(StreamRefPtr stream, bool forceEnglish)
{
    auto future = ae::ScheduleOrExecute([stream, forceEnglish]() {
        CheckNotNull(&stream, "Error Getting Stream Units Text. Stream is Null");
        // AEGP_FOOTAGE_LAYER_NAME_LEN
        A_char unitsH[AEGP_FOOTAGE_LAYER_NAME_LEN];
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetStreamUnitsText(
            *stream, forceEnglish, unitsH));
        return std::string(unitsH);
    });
    return future.get();
}

std::tuple<StreamFlag, double, double> StreamSuite::GetStreamProperties(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Stream Properties. Stream is Null");
        A_long flags;
        A_FpLong minVal;
        A_FpLong maxVal;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetStreamProperties(
            *stream, &flags, &minVal, &maxVal));
        return std::make_tuple(StreamFlag(flags), minVal, maxVal);
    });
    return future.get();
}

bool StreamSuite::IsStreamTimevarying(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Checking if Stream is Timevarying. Stream is Null");
        A_Boolean isTimevarying;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_IsStreamTimevarying(
            *stream, &isTimevarying));
        return static_cast<bool>(isTimevarying);
    });
    return future.get();
}

StreamType StreamSuite::GetStreamType(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Stream Type. Stream is Null");
        AEGP_StreamType type;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetStreamType(*stream, &type));
        return StreamType(type);
    });
    return future.get();
}

StreamValue2Ptr StreamSuite::GetNewStreamValue(StreamRefPtr stream, LTimeMode timeMode, Time time, bool preExpression)
{
    auto future = ae::ScheduleOrExecute([stream, timeMode, time, preExpression]() {
        CheckNotNull(&stream, "Error Getting New Stream Value. Stream is Null");
        AEGP_StreamValue2 valueH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetNewStreamValue(
            *SuiteManager::GetInstance().GetPluginID(), *stream, AEGP_LTimeMode(timeMode), &time.toAEGP(),
            preExpression, &valueH));
        return makeStreamValue2Ptr(valueH);
    });
    return future.get();
}

void StreamSuite::SetStreamValue(StreamRefPtr stream, StreamValue2Ptr value)
{
    auto future = ae::ScheduleOrExecute([stream, &value]() {
        CheckNotNull(&stream, "Error Setting Stream Value. Stream is Null");
        // CheckNotNull(&value, "Error Setting Stream Value. Value is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_SetStreamValue(
            *SuiteManager::GetInstance().GetPluginID(), *stream, &value->get()));
    });
    future.wait();
}

std::tuple<AEGP_StreamVal2, StreamType> StreamSuite::GetLayerStreamValue(LayerPtr layer, LayerStream whichStream,
                                                                         LTimeMode timeMode, Time time,
                                                                         bool preExpression)
{
    auto future = ae::ScheduleOrExecute([layer, whichStream, timeMode, time, preExpression]() {
        CheckNotNull(&layer, "Error Getting Layer Stream Value. Layer is Null");
        AEGP_StreamVal2 value;
        AEGP_StreamType type;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetLayerStreamValue(
            *layer, AEGP_LayerStream(whichStream), AEGP_LTimeMode(timeMode), &time.toAEGP(), preExpression, &value,
            &type));
        return std::make_tuple(value, StreamType(type));
    });
    return future.get();
}

StreamRefPtr StreamSuite::DuplicateStreamRef(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Duplicating Stream Ref. Stream is Null");
        AEGP_StreamRefH newStreamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_DuplicateStreamRef(
            *SuiteManager::GetInstance().GetPluginID(), *stream, &newStreamH));
        return makeStreamRefPtr(newStreamH);
    });
    return future.get();
}

int StreamSuite::GetUniqueStreamID(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Unique Stream ID. Stream is Null");
        A_long id;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().StreamSuite6()->AEGP_GetUniqueStreamID(*stream, &id));
        return id;
    });
    return future.get();
}

StreamRefPtr DynamicStreamSuite::GetNewStreamRefForLayer(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting New Stream Ref for Layer. Layer is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewStreamRefForLayer(
            *SuiteManager::GetInstance().GetPluginID(), *layer, &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

StreamRefPtr DynamicStreamSuite::GetNewStreamRefForMask(MaskRefPtr mask)
{
    auto future = ae::ScheduleOrExecute([mask]() {
        CheckNotNull(&mask, "Error Getting New Stream Ref for Mask. Mask is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewStreamRefForMask(
            *SuiteManager::GetInstance().GetPluginID(), *mask, &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

int DynamicStreamSuite::GetStreamDepth(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Stream Depth. Stream is Null");
        int depth;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetStreamDepth(*stream, &depth));
        return depth;
    });
    return future.get();
}

StreamGroupingType DynamicStreamSuite::GetStreamGroupingType(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Stream Grouping Type. Stream is Null");
        AEGP_StreamGroupingType type;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetStreamGroupingType(
            *stream, &type));
        return StreamGroupingType(type);
    });
    return future.get();
}

int DynamicStreamSuite::GetNumStreamsInGroup(StreamRefPtr stream)
{

    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Number of Streams in Group. Stream is Null");
        int numStreams;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNumStreamsInGroup(
            *stream, &numStreams));
        return numStreams;
    });
    return future.get();
}

DynStreamFlag DynamicStreamSuite::GetDynamicStreamFlags(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Dynamic Stream Flags. Stream is Null");
        AEGP_DynStreamFlags flags;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetDynamicStreamFlags(
            *stream, &flags));
        return DynStreamFlag(flags);
    });
    return future.get();
}

void DynamicStreamSuite::SetDynamicStreamFlag(StreamRefPtr stream, DynStreamFlag oneFlag, bool undoable, bool set)
{
    auto future = ae::ScheduleOrExecute([stream, oneFlag, undoable, set]() {
        CheckNotNull(&stream, "Error Setting Dynamic Stream Flag. Stream is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_SetDynamicStreamFlag(
            *stream, AEGP_DynStreamFlags(oneFlag), undoable, set));
    });
    future.wait();
}

StreamRefPtr DynamicStreamSuite::GetNewStreamRefByIndex(StreamRefPtr parentGroup, int index)
{
    auto future = ae::ScheduleOrExecute([parentGroup, index]() {
        CheckNotNull(&parentGroup, "Error Getting New Stream Ref by Index. Parent Group is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewStreamRefByIndex(
            *SuiteManager::GetInstance().GetPluginID(), *parentGroup, index, &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

StreamRefPtr DynamicStreamSuite::GetNewStreamRefByMatchname(StreamRefPtr parentGroup, const std::string &matchName)
{
    auto future = ae::ScheduleOrExecute([parentGroup, matchName]() {
        CheckNotNull(&parentGroup, "Error Getting New Stream Ref by Matchname. Parent Group is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewStreamRefByMatchname(
            *SuiteManager::GetInstance().GetPluginID(), *parentGroup, matchName.c_str(), &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

void DynamicStreamSuite::DeleteStream(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Deleting Stream. Stream is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_DeleteStream(*stream));
    });
    future.wait();
}

void DynamicStreamSuite::ReorderStream(StreamRefPtr stream, int newIndex)
{
    auto future = ae::ScheduleOrExecute([stream, newIndex]() {
        CheckNotNull(&stream, "Error Reordering Stream. Stream is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_ReorderStream(*stream, newIndex));
    });
    future.wait();
}

int DynamicStreamSuite::DuplicateStream(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Duplicating Stream. Stream is Null");
        int newStreamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_DuplicateStream(
            *SuiteManager::GetInstance().GetPluginID(), *stream, &newStreamH));
        return newStreamH;
    });
    return future.get();
}

void DynamicStreamSuite::SetStreamName(StreamRefPtr stream, const std::string &newName)
{
    auto future = ae::ScheduleOrExecute([stream, newName]() {
        CheckNotNull(&stream, "Error Setting Stream Name. Stream is Null");
        std::vector<A_UTF16Char> name16 = ConvertUTF8ToUTF16(newName);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_SetStreamName(
            *stream, name16.data()));
    });
    future.wait();
}

bool DynamicStreamSuite::CanAddStream(StreamRefPtr parentGroup, const std::string &matchName)
{
    auto future = ae::ScheduleOrExecute([parentGroup, matchName]() {
        CheckNotNull(&parentGroup, "Error Checking if Can Add Stream. Parent Group is Null");
        A_Boolean canAdd;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_CanAddStream(
            *parentGroup, matchName.c_str(), &canAdd));
        return static_cast<bool>(canAdd);
    });
    return future.get();
}
// # TODO: add ae::ScheduleOrExecute from here!
StreamRefPtr DynamicStreamSuite::AddStream(StreamRefPtr parentGroup, const std::string &matchName)
{
    auto future = ae::ScheduleOrExecute([parentGroup, matchName]() {
        CheckNotNull(&parentGroup, "Error Adding Stream. Parent Group is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_AddStream(
            *SuiteManager::GetInstance().GetPluginID(), *parentGroup, matchName.c_str(), &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

///* << UTF8!! use A_char[AEGP_MAX_STREAM_MATCH_NAME_SIZE] for buffer */
std::string DynamicStreamSuite::GetMatchname(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Matchname. Stream is Null");
        A_char matchname[AEGP_MAX_STREAM_MATCH_NAME_SIZE];
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetMatchName(*stream, matchname));
        std::string matchnameStr(matchname);
        return matchnameStr;
    });
    return future.get();
}

StreamRefPtr DynamicStreamSuite::GetNewParentStreamRef(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting New Parent Stream Ref. Stream is Null");
        AEGP_StreamRefH parentStreamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetNewParentStreamRef(
            *SuiteManager::GetInstance().GetPluginID(), *stream, &parentStreamH));
        return makeStreamRefPtr(parentStreamH);
    });
    return future.get();
}

bool DynamicStreamSuite::GetStreamIsModified(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Stream is Modified. Stream is Null");
        A_Boolean isModified;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetStreamIsModified(
            *stream, &isModified));
        return static_cast<bool>(isModified);
    });
    return future.get();
}

bool DynamicStreamSuite::IsSeparationLeader(StreamRefPtr stream)
{

    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Checking if Stream is Separation Leader. Stream is Null");
        A_Boolean isLeader;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_IsSeparationLeader(
            *stream, &isLeader));
        return static_cast<bool>(isLeader);
    });
    return future.get();
}

bool DynamicStreamSuite::AreDimensionsSeparated(StreamRefPtr leaderStream)
{
    auto future = ae::ScheduleOrExecute([leaderStream]() {
        CheckNotNull(&leaderStream, "Error Checking if Dimensions are Separated. Leader Stream is Null");
        A_Boolean areSeparated;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_AreDimensionsSeparated(
            *leaderStream, &areSeparated));
        return static_cast<bool>(areSeparated);
    });
    return future.get();
}

void DynamicStreamSuite::SetDimensionsSeparated(StreamRefPtr leaderStream, bool separated)
{
    auto future = ae::ScheduleOrExecute([leaderStream, separated]() {
        CheckNotNull(&leaderStream, "Error Setting Dimensions Separated. Leader Stream is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_SetDimensionsSeparated(
            *leaderStream, separated));
    });
    future.wait();
}

StreamRefPtr DynamicStreamSuite::GetSeparationFollower(int dimension, StreamRefPtr leaderStream)
{
    auto future = ae::ScheduleOrExecute([dimension, leaderStream]() {
        CheckNotNull(&leaderStream, "Error Getting Separation Follower. Leader Stream is Null");
        AEGP_StreamRefH followerStreamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetSeparationFollower(
            *leaderStream, dimension, &followerStreamH));
        return makeStreamRefPtr(followerStreamH);
    });
    return future.get();
}

bool DynamicStreamSuite::IsSeparationFollower(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Checking if Stream is Separation Follower. Stream is Null");
        A_Boolean isFollower;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_IsSeparationFollower(
            *stream, &isFollower));
        return static_cast<bool>(isFollower);
    });
    return future.get();
}

StreamRefPtr DynamicStreamSuite::GetSeparationLeader(StreamRefPtr followerStream)
{
    auto future = ae::ScheduleOrExecute([followerStream]() {
        CheckNotNull(&followerStream, "Error Getting Separation Leader. Follower Stream is Null");
        AEGP_StreamRefH leaderStreamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetSeparationLeader(
            *followerStream, &leaderStreamH));
        return makeStreamRefPtr(leaderStreamH);
    });
    return future.get();
}

A_short DynamicStreamSuite::GetSeparationDimension(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Separation Dimension. Stream is Null");
        A_short dimension;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().DynamicStreamSuite4()->AEGP_GetSeparationDimension(
            *stream, &dimension));
        return dimension;
    });
    return future.get();
}

int KeyframeSuite::GetStreamNumKFs(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Stream Number of Keyframes. Stream is Null");
        int numKFs;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetStreamNumKFs(*stream, &numKFs));
        return numKFs;
    });
    return future.get();
}

Time KeyframeSuite::GetKeyframeTime(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, LTimeMode timeMode)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex, timeMode]() {
        CheckNotNull(&stream, "Error Getting Keyframe Time. Stream is Null");
        Time time;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeTime(
            *stream, keyIndex, AEGP_LTimeMode(timeMode), &time.toAEGP()));
        return time;
    });
    return future.get();
}

AEGP_KeyframeIndex KeyframeSuite::InsertKeyframe(StreamRefPtr stream, LTimeMode timeMode, const Time &time)
{
    auto future = ae::ScheduleOrExecute([stream, timeMode, time]() {
        CheckNotNull(&stream, "Error Inserting Keyframe. Stream is Null");
        AEGP_KeyframeIndex keyIndex;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_InsertKeyframe(
            *stream, AEGP_LTimeMode(timeMode), &time.toAEGP(), &keyIndex));
        return keyIndex;
    });
    return future.get();
}

void KeyframeSuite::DeleteKeyframe(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex]() {
        CheckNotNull(&stream, "Error Deleting Keyframe. Stream is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_DeleteKeyframe(*stream, keyIndex));
    });
    future.wait();
}

StreamValue2Ptr KeyframeSuite::GetNewKeyframeValue(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex]() {
        CheckNotNull(&stream, "Error Getting New Keyframe Value. Stream is Null");
        AEGP_StreamValue2 value;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetNewKeyframeValue(
            *SuiteManager::GetInstance().GetPluginID(), *stream, keyIndex, &value));
        return makeStreamValue2Ptr(value);
    });
    return future.get();
}

void KeyframeSuite::SetKeyframeValue(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, StreamValue2Ptr value)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex, value]() {
        CheckNotNull(&stream, "Error Setting Keyframe Value. Stream is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeValue(
            *stream, keyIndex, &value->get()));
    });
    future.wait();
}

A_short KeyframeSuite::GetStreamValueDimensionality(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Stream Value Dimensionality. Stream is Null");
        A_short dimension;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetStreamValueDimensionality(
            *stream, &dimension));
        return dimension;
    });
    return future.get();
}

A_short KeyframeSuite::GetStreamTemporalDimensionality(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Getting Stream Temporal Dimensionality. Stream is Null");
        A_short dimension;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetStreamTemporalDimensionality(
            *stream, &dimension));
        return dimension;
    });
    return future.get();
}

std::tuple<StreamValue2Ptr, StreamValue2Ptr> KeyframeSuite::GetNewKeyframeSpatialTangents(StreamRefPtr stream,
                                                                                          AEGP_KeyframeIndex keyIndex)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex]() {
        CheckNotNull(&stream, "Error Getting New Keyframe Spatial Tangents. Stream is Null");
        AEGP_StreamValue2 inTan, outTan;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetNewKeyframeSpatialTangents(
            *SuiteManager::GetInstance().GetPluginID(), *stream, keyIndex, &inTan, &outTan));
        return std::make_tuple(makeStreamValue2Ptr(inTan), makeStreamValue2Ptr(outTan));
    });
    return future.get();
}

void KeyframeSuite::SetKeyframeSpatialTangents(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, StreamValue2Ptr inTan,
                                               StreamValue2Ptr outTan)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex, inTan, outTan]() {
        CheckNotNull(&stream, "Error Setting Keyframe Spatial Tangents. Stream is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeSpatialTangents(
            *stream, keyIndex, &inTan->get(), &outTan->get()));
    });
    future.wait();
}

std::tuple<KeyframeEase, KeyframeEase>
KeyframeSuite::GetKeyframeTemporalEase(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, int dimension)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex, dimension]() {
        CheckNotNull(&stream, "Error Getting Keyframe Temporal Ease. Stream is Null");
        AEGP_KeyframeEase inEase, outEase;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeTemporalEase(
            *stream, keyIndex, dimension, &inEase, &outEase));
        return std::make_tuple(KeyframeEase(inEase), KeyframeEase(outEase));
    });
    return future.get();
}

void KeyframeSuite::SetKeyframeTemporalEase(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, int dimension,
                                            KeyframeEase inEase, KeyframeEase outEase)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex, dimension, &inEase, &outEase]() {
        CheckNotNull(&stream, "Error Setting Keyframe Temporal Ease. Stream is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeTemporalEase(
            *stream, keyIndex, dimension, &inEase.toAEGP(), &outEase.toAEGP()));
    });
    future.wait();
}

KeyframeFlag KeyframeSuite::GetKeyframeFlags(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex]() {
        CheckNotNull(&stream, "Error Getting Keyframe Flags. Stream is Null");
        AEGP_KeyframeFlags flags;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeFlags(
            *stream, keyIndex, &flags));
        return KeyframeFlag(flags);
    });
    return future.get();
}

void KeyframeSuite::SetKeyframeFlag(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, KeyframeFlag flag, bool value)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex, flag, value]() {
        CheckNotNull(&stream, "Error Setting Keyframe Flag. Stream is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeFlag(
            *stream, keyIndex, AEGP_KeyframeFlags(flag), value));
    });
    future.wait();
}

std::tuple<KeyInterp, KeyInterp> KeyframeSuite::GetKeyframeInterpolation(StreamRefPtr stream,
                                                                         AEGP_KeyframeIndex keyIndex)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex]() {
        CheckNotNull(&stream, "Error Getting Keyframe Interpolation. Stream is Null");
        int inInterp, outInterp;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeInterpolation(
            *stream, keyIndex, &inInterp, &outInterp));
        return std::make_tuple(KeyInterp(inInterp), KeyInterp(outInterp));
    });
    return future.get();
}

void KeyframeSuite::SetKeyframeInterpolation(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, KeyInterp inInterp,
                                             KeyInterp outInterp)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex, inInterp, outInterp]() {
        CheckNotNull(&stream, "Error Setting Keyframe Interpolation. Stream is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeInterpolation(
            *stream, keyIndex, int(inInterp), int(outInterp)));
    });
    future.wait();
}

AddKeyframesInfoPtr KeyframeSuite::StartAddKeyframes(StreamRefPtr stream)
{
    auto future = ae::ScheduleOrExecute([stream]() {
        CheckNotNull(&stream, "Error Starting Add Keyframes. Stream is Null");
        AEGP_AddKeyframesInfoH akH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_StartAddKeyframes(*stream, &akH));
        return makeAddKeyframesInfoPtr(akH);
    });
    return future.get();
}

AEGP_KeyframeIndex KeyframeSuite::AddKeyframes(AddKeyframesInfoPtr akH, LTimeMode timeMode, const Time &time)
{
    auto future = ae::ScheduleOrExecute([akH, timeMode, time]() {
        CheckNotNull(&akH, "Error Adding Keyframes. Add Keyframes Info is Null");
        AEGP_KeyframeIndex keyIndex;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_AddKeyframes(
            *akH, AEGP_LTimeMode(timeMode), &time.toAEGP(), &keyIndex));
        return keyIndex;
    });
    return future.get();
}

void KeyframeSuite::SetAddKeyframe(AddKeyframesInfoPtr akH, AEGP_KeyframeIndex keyIndex, StreamValue2Ptr value)
{
    auto future = ae::ScheduleOrExecute([akH, keyIndex, value]() {
        CheckNotNull(&akH, "Error Setting Add Keyframe. Add Keyframes Info is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetAddKeyframe(*akH, keyIndex,
                                                                                                     &value->get()));
    });
    future.wait();
}

void KeyframeSuite::EndAddKeyframes(AddKeyframesInfoPtr akH)
{
    auto future = ae::ScheduleOrExecute([akH]() {
        CheckNotNull(&akH, "Error Ending Add Keyframes. Add Keyframes Info is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_EndAddKeyframes(true, *akH));
    });
    future.wait();
}

int KeyframeSuite::GetKeyframeLabelColorIndex(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex]() {
        CheckNotNull(&stream, "Error Getting Keyframe Label Color Index. Stream is Null");
        int keyLabel;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_GetKeyframeLabelColorIndex(
            *stream, keyIndex, &keyLabel));
        return keyLabel;
    });
    return future.get();
}

void KeyframeSuite::SetKeyframeLabelColorIndex(StreamRefPtr stream, AEGP_KeyframeIndex keyIndex, int keyLabel)
{
    auto future = ae::ScheduleOrExecute([stream, keyIndex, keyLabel]() {
        CheckNotNull(&stream, "Error Setting Keyframe Label Color Index. Stream is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().KeyframeSuite5()->AEGP_SetKeyframeLabelColorIndex(
            *stream, keyIndex, keyLabel));
    });
    future.wait();
}

std::string TextDocumentSuite::getNewText(TextDocumentPtr text_documentH)
{
    auto future = ae::ScheduleOrExecute([text_documentH]() {
        CheckNotNull(&text_documentH, "Error Getting New Text. Text Document is Null");
        AEGP_MemHandle textH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().TextDocumentSuite1()->AEGP_GetNewText(
            *SuiteManager::GetInstance().GetPluginID(), *text_documentH, &textH));
        return memHandleToString(textH);
    });
    return future.get();
}

void TextDocumentSuite::setText(TextDocumentPtr text_documentH, const std::string &unicodePS)
{
    auto future = ae::ScheduleOrExecute([text_documentH, unicodePS]() {
        CheckNotNull(&text_documentH, "Error Setting Text. Text Document is Null");
        const A_u_short *unicodeP = ConvertUTF8ToUTF16(unicodePS).data();
        int lengthL = static_cast<int>(unicodePS.size());
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().TextDocumentSuite1()->AEGP_SetText(*text_documentH,
                                                                                                  unicodeP, lengthL));
    });
    future.wait();
}

MarkerValPtr MarkerSuite::getNewMarker()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_MarkerValP markerP;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_NewMarker(&markerP));
        return makeMarkerValPtr(markerP);
    });
    return future.get();
}

MarkerValPtr MarkerSuite::duplicateMarker(MarkerValPtr markerP)
{
    auto future = ae::ScheduleOrExecute([markerP]() {
        CheckNotNull(&markerP, "Error Duplicating Marker. Marker is Null");
        AEGP_MarkerValP newMarkerP;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_DuplicateMarker(*markerP, &newMarkerP));
        return makeMarkerValPtr(newMarkerP);
    });
    return future.get();
}

void MarkerSuite::setMarkerFlag(MarkerValPtr markerP, MarkerFlag flagType, bool valueB)
{
    auto future = ae::ScheduleOrExecute([markerP, flagType, valueB]() {
        CheckNotNull(&markerP, "Error Setting Marker Flag. Marker is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerFlag(
            *markerP, AEGP_MarkerFlagType(flagType), valueB));
    });
    future.wait();
}

bool MarkerSuite::getMarkerFlag(MarkerValPtr markerP, MarkerFlag flagType)
{
    auto future = ae::ScheduleOrExecute([markerP, flagType]() {
        CheckNotNull(&markerP, "Error Getting Marker Flag. Marker is Null");
        A_Boolean valueB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerFlag(
            *markerP, AEGP_MarkerFlagType(flagType), &valueB));
        return static_cast<bool>(valueB);
    });
    return future.get();
}

std::string MarkerSuite::getMarkerString(MarkerValPtr markerP, MarkerStringType strType)
{
    auto future = ae::ScheduleOrExecute([markerP, strType]() {
        CheckNotNull(&markerP, "Error Getting Marker String. Marker is Null");
        AEGP_MemHandle stringH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerString(
            *SuiteManager::GetInstance().GetPluginID(), *markerP, AEGP_MarkerStringType(strType), &stringH));
        return memHandleToString(stringH);
    });
    return future.get();
}

void MarkerSuite::setMarkerString(MarkerValPtr markerP, MarkerStringType strType, const std::string &unicodeP)
{
    auto future = ae::ScheduleOrExecute([markerP, strType, unicodeP]() {
        CheckNotNull(&markerP, "Error Setting Marker String. Marker is Null");
        const A_u_short *unicodeP16 = ConvertUTF8ToUTF16(unicodeP).data();
        int lengthL = static_cast<int>(unicodeP.size());
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerString(
            *markerP, AEGP_MarkerStringType(strType), unicodeP16, lengthL));
    });
    future.wait();
}

int MarkerSuite::countCuePointParams(MarkerValPtr markerP)
{
    auto future = ae::ScheduleOrExecute([markerP]() {
        CheckNotNull(&markerP, "Error Counting Cue Point Params. Marker is Null");
        int countL;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_CountCuePointParams(*markerP, &countL));
        return countL;
    });
    return future.get();
}

std::tuple<std::string, std::string> MarkerSuite::getIndCuePointParam(MarkerValPtr markerP, int param_indexL)
{
    auto future = ae::ScheduleOrExecute([markerP, param_indexL]() {
        CheckNotNull(&markerP, "Error Getting Ind Cue Point Param. Marker is Null");
        AEGP_MemHandle keyH, valueH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetIndCuePointParam(
            *SuiteManager::GetInstance().GetPluginID(), *markerP, param_indexL, &keyH, &valueH));
        return std::make_tuple(memHandleToString(keyH), memHandleToString(valueH));
    });
    return future.get();
}

void MarkerSuite::setIndCuePointParam(MarkerValPtr markerP, int param_indexL, const std::string &unicodeKeyP,
                                      const std::string &unicodeValueP)
{
    auto future = ae::ScheduleOrExecute([markerP, param_indexL, unicodeKeyP, unicodeValueP]() {
        CheckNotNull(&markerP, "Error Setting Ind Cue Point Param. Marker is Null");
        const A_u_short *unicodeKeyP16 = ConvertUTF8ToUTF16(unicodeKeyP).data();
        int key_lengthL = static_cast<int>(unicodeKeyP.size());
        const A_u_short *unicodeValueP16 = ConvertUTF8ToUTF16(unicodeValueP).data();
        int value_lengthL = static_cast<int>(unicodeValueP.size());
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetIndCuePointParam(
            *markerP, param_indexL, unicodeKeyP16, key_lengthL, unicodeValueP16, value_lengthL));
    });
    future.wait();
}

void MarkerSuite::insertCuePointParam(MarkerValPtr markerP, int param_indexL)
{
    auto future = ae::ScheduleOrExecute([markerP, param_indexL]() {
        CheckNotNull(&markerP, "Error Inserting Cue Point Param. Marker is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_InsertCuePointParam(*markerP,
                                                                                                        param_indexL));
    });
    future.wait();
}

void MarkerSuite::deleteIndCuePointParam(MarkerValPtr markerP, int param_indexL)
{
    auto future = ae::ScheduleOrExecute([markerP, param_indexL]() {
        CheckNotNull(&markerP, "Error Deleting Ind Cue Point Param. Marker is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_DeleteIndCuePointParam(
            *markerP, param_indexL));
    });
    future.wait();
}

void MarkerSuite::setMarkerDuration(MarkerValPtr markerP, const Time &durationPT)
{
    auto future = ae::ScheduleOrExecute([markerP, durationPT]() {
        CheckNotNull(&markerP, "Error Setting Marker Duration. Marker is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerDuration(
            *markerP, &durationPT.toAEGP()));
    });
    future.wait();
}

Time MarkerSuite::getMarkerDuration(MarkerValPtr markerP)
{
    auto future = ae::ScheduleOrExecute([markerP]() {
        CheckNotNull(&markerP, "Error Getting Marker Duration. Marker is Null");
        Time durationT;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerDuration(
            *markerP, &durationT.toAEGP()));
        return durationT;
    });
    return future.get();
}

void MarkerSuite::setMarkerLabel(MarkerValPtr markerP, int value)
{
    auto future = ae::ScheduleOrExecute([markerP, value]() {
        CheckNotNull(&markerP, "Error Setting Marker Label. Marker is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_SetMarkerLabel(*markerP, value));
    });
    future.wait();
}

int MarkerSuite::getMarkerLabel(MarkerValPtr markerP)
{
    auto future = ae::ScheduleOrExecute([markerP]() {
        CheckNotNull(&markerP, "Error Getting Marker Label. Marker is Null");
        int labelL;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MarkerSuite3()->AEGP_GetMarkerLabel(*markerP, &labelL));
        return labelL;
    });
    return future.get();
}

TextOutlinesPtr TextLayerSuite::getNewTextOutlines(LayerPtr layer, const Time &layer_time)
{
    auto future = ae::ScheduleOrExecute([layer, layer_time]() {
        CheckNotNull(&layer, "Error Getting New Text Outlines. Layer is Null");
        AEGP_TextOutlinesH outlinesH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().TextLayerSuite1()->AEGP_GetNewTextOutlines(
            *layer, &layer_time.toAEGP(), &outlinesH));
        return makeTextOutlinesPtr(outlinesH);
    });
    return future.get();
}

int TextLayerSuite::getNumTextOutlines(TextOutlinesPtr outlines)
{
    auto future = ae::ScheduleOrExecute([outlines]() {
        CheckNotNull(&outlines, "Error Getting Number of Text Outlines. Outlines is Null");
        int numOutlines;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().TextLayerSuite1()->AEGP_GetNumTextOutlines(
            *outlines, &numOutlines));
        return numOutlines;
    });
    return future.get();
}

PF_PathOutlinePtr TextLayerSuite::getIndexedTextOutline(TextOutlinesPtr outlines, int path_index)
{
    return PF_PathOutlinePtr();
}

int EffectSuite::getLayerNumEffects(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Getting Layer Number of Effects. Layer is Null");
        int numEffects;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetLayerNumEffects(*layer, &numEffects));
        return numEffects;
    });
    return future.get();
}

EffectRefPtr EffectSuite::getLayerEffectByIndex(LayerPtr layer, AEGP_EffectIndex layer_effect_index)
{
    auto future = ae::ScheduleOrExecute([layer, layer_effect_index]() {
        CheckNotNull(&layer, "Error Getting Layer Effect by Index. Layer is Null");
        AEGP_EffectRefH effectH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetLayerEffectByIndex(
            *SuiteManager::GetInstance().GetPluginID(), *layer, layer_effect_index, &effectH));
        return makeEffectRefPtr(effectH);
    });
    return future.get();
}

AEGP_InstalledEffectKey EffectSuite::getInstalledKeyFromLayerEffect(EffectRefPtr effect_ref)
{
    auto future = ae::ScheduleOrExecute([effect_ref]() {
        CheckNotNull(&effect_ref, "Error Getting Installed Key from Layer Effect. Effect is Null");
        AEGP_InstalledEffectKey key;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetInstalledKeyFromLayerEffect(
            *effect_ref, &key));
        return key;
    });
    return future.get();
}

std::tuple<PF_ParamType, PF_ParamDefUnion> EffectSuite::getEffectParamUnionByIndex(EffectRefPtr effect_ref,
                                                                                   PF_ParamIndex param_index)
{
    auto future = ae::ScheduleOrExecute([effect_ref, param_index]() {
        CheckNotNull(&effect_ref, "Error Getting Effect Param Union by Index. Effect is Null");
        PF_ParamType type;
        PF_ParamDefUnion def;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectParamUnionByIndex(
            *SuiteManager::GetInstance().GetPluginID(), *effect_ref, param_index, &type, &def));
        return std::make_tuple(type, def);
    });
    return future.get();
}

EffectFlags EffectSuite::getEffectFlags(EffectRefPtr effect_ref)
{
    auto future = ae::ScheduleOrExecute([effect_ref]() {
        CheckNotNull(&effect_ref, "Error Getting Effect Flags. Effect is Null");
        AEGP_EffectFlags flags;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectFlags(*effect_ref, &flags));
        return EffectFlags(flags);
    });
    return future.get();
}

void EffectSuite::setEffectFlags(EffectRefPtr effect_ref, EffectFlags effect_flags_set_mask, EffectFlags effect_flags)
{
    auto future = ae::ScheduleOrExecute([effect_ref, effect_flags_set_mask, effect_flags]() {
        CheckNotNull(&effect_ref, "Error Setting Effect Flags. Effect is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_SetEffectFlags(
            *effect_ref, AEGP_EffectFlags(effect_flags_set_mask), AEGP_EffectFlags(effect_flags)));
    });
    future.wait();
}

void EffectSuite::reorderEffect(EffectRefPtr effect_ref, int effect_index)
{
    auto future = ae::ScheduleOrExecute([effect_ref, effect_index]() {
        CheckNotNull(&effect_ref, "Error Reordering Effect. Effect is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_ReorderEffect(*effect_ref,
                                                                                                  effect_index));
    });
    future.wait();
}

void EffectSuite::effectCallGeneric(EffectRefPtr effect_ref, Time timePT, PF_Cmd effect_cmd, void *effect_extraPV)
{
    auto future = ae::ScheduleOrExecute([effect_ref, timePT, effect_cmd, effect_extraPV]() {
        CheckNotNull(&effect_ref, "Error Effect Call Generic. Effect is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_EffectCallGeneric(
            *SuiteManager::GetInstance().GetPluginID(), *effect_ref, &timePT.toAEGP(), effect_cmd, effect_extraPV));
    });
    future.wait();
}

EffectRefPtr EffectSuite::applyEffect(LayerPtr layer, AEGP_InstalledEffectKey installed_effect_key)
{
    auto future = ae::ScheduleOrExecute([layer, installed_effect_key]() {
        CheckNotNull(&layer, "Error Applying Effect. Layer is Null");
        AEGP_EffectRefH effectH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_ApplyEffect(
            *SuiteManager::GetInstance().GetPluginID(), *layer, installed_effect_key, &effectH));
        return makeEffectRefPtr(effectH);
    });
    return future.get();
}

void EffectSuite::deleteLayerEffect(EffectRefPtr effect_ref)
{
    auto future = ae::ScheduleOrExecute([effect_ref]() {
        CheckNotNull(&effect_ref, "Error Deleting Layer Effect. Effect is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_DeleteLayerEffect(*effect_ref));
    });
    future.wait();
}

int EffectSuite::getNumInstalledEffects()
{
    auto future = ae::ScheduleOrExecute([]() {
        int numEffects;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetNumInstalledEffects(&numEffects));
        return numEffects;
    });
    return future.get();
}

AEGP_InstalledEffectKey EffectSuite::getNextInstalledEffect(AEGP_InstalledEffectKey installed_effect_key)
{
    auto future = ae::ScheduleOrExecute([installed_effect_key]() {
        AEGP_InstalledEffectKey nextKey;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetNextInstalledEffect(
            installed_effect_key, &nextKey));
        return nextKey;
    });
    return future.get();
}

std::string EffectSuite::getEffectName(AEGP_InstalledEffectKey installed_effect_key)
{
    auto future = ae::ScheduleOrExecute([installed_effect_key]() {
        A_char nameP[AEGP_MAX_EFFECT_NAME_SIZE];
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectName(installed_effect_key,
                                                                                                  nameP));
        return std::string(nameP);
    });
    return future.get();
}

std::string EffectSuite::getEffectMatchName(AEGP_InstalledEffectKey installed_effect_key)
{
    auto future = ae::ScheduleOrExecute([installed_effect_key]() {
        A_char matchNameP[AEGP_MAX_EFFECT_MATCH_NAME_SIZE];
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectMatchName(
            installed_effect_key, matchNameP));
        return std::string(matchNameP);
    });
    return future.get();
}

std::string EffectSuite::getEffectCategory(AEGP_InstalledEffectKey installed_effect_key)
{
    auto future = ae::ScheduleOrExecute([installed_effect_key]() {
        A_char categoryP[AEGP_MAX_EFFECT_CATEGORY_NAME_SIZE];
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectCategory(
            installed_effect_key, categoryP));
        return std::string(categoryP);
    });
    return future.get();
}

EffectRefPtr EffectSuite::duplicateEffect(EffectRefPtr original_effect_ref)
{
    auto future = ae::ScheduleOrExecute([original_effect_ref]() {
        CheckNotNull(&original_effect_ref, "Error Duplicating Effect. Original Effect is Null");
        AEGP_EffectRefH newEffectH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_DuplicateEffect(
            *original_effect_ref, &newEffectH));
        return makeEffectRefPtr(newEffectH);
    });
    return future.get();
}

int EffectSuite::numEffectMask(EffectRefPtr effect_ref)
{
    auto future = ae::ScheduleOrExecute([effect_ref]() {
        CheckNotNull(&effect_ref, "Error Getting Number of Effect Masks. Effect is Null");
        A_u_long numMasks;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_NumEffectMask(*effect_ref, &numMasks));
        return numMasks;
    });
    return future.get();
}

int EffectSuite::getEffectMaskID(EffectRefPtr effect_ref, int mask_indexL)
{
    auto future = ae::ScheduleOrExecute([effect_ref, mask_indexL]() {
        CheckNotNull(&effect_ref, "Error Getting Effect Mask ID. Effect is Null");
        AEGP_MaskIDVal id;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_GetEffectMaskID(*effect_ref,
                                                                                                    mask_indexL, &id));
        return id;
    });
    return future.get();
}

StreamRefPtr EffectSuite::addEffectMask(EffectRefPtr effect_ref, AEGP_MaskIDVal id_val)
{
    auto future = ae::ScheduleOrExecute([effect_ref, id_val]() {
        CheckNotNull(&effect_ref, "Error Adding Effect Mask. Effect is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_AddEffectMask(*effect_ref, id_val,
                                                                                                  &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

void EffectSuite::removeEffectMask(EffectRefPtr effect_ref, AEGP_MaskIDVal id_val)
{
    auto future = ae::ScheduleOrExecute([effect_ref, id_val]() {
        CheckNotNull(&effect_ref, "Error Removing Effect Mask. Effect is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_RemoveEffectMask(*effect_ref, id_val));
    });
    future.wait();
}

StreamRefPtr EffectSuite::setEffectMask(EffectRefPtr effect_ref, int mask_indexL, AEGP_MaskIDVal id_val)
{
    auto future = ae::ScheduleOrExecute([effect_ref, mask_indexL, id_val]() {
        CheckNotNull(&effect_ref, "Error Setting Effect Mask. Effect is Null");
        AEGP_StreamRefH streamH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().EffectSuite4()->AEGP_SetEffectMask(
            *effect_ref, mask_indexL, id_val, &streamH));
        return makeStreamRefPtr(streamH);
    });
    return future.get();
}

int MaskSuite::getLayerNumMasks(LayerPtr aegp_layerH)
{
    auto future = ae::ScheduleOrExecute([aegp_layerH]() {
        CheckNotNull(&aegp_layerH, "Error Getting Layer Number of Masks. Layer is Null");
        int numMasks;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetLayerNumMasks(*aegp_layerH, &numMasks));
        return numMasks;
    });
    return future.get();
}

MaskRefPtr MaskSuite::getLayerMaskByIndex(LayerPtr aegp_layerH, AEGP_MaskIndex mask_indexL)
{
    auto future = ae::ScheduleOrExecute([aegp_layerH, mask_indexL]() {
        CheckNotNull(&aegp_layerH, "Error Getting Layer Mask by Index. Layer is Null");
        AEGP_MaskRefH maskH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetLayerMaskByIndex(
            *aegp_layerH, mask_indexL, &maskH));
        return makeMaskRefPtr(maskH);
    });
    return future.get();
}

bool MaskSuite::getMaskInvert(MaskRefPtr mask_refH)
{
    auto future = ae::ScheduleOrExecute([mask_refH]() {
        CheckNotNull(&mask_refH, "Error Getting Mask Invert. Mask is Null");
        A_Boolean invertB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskInvert(*mask_refH, &invertB));
        return static_cast<bool>(invertB);
    });
    return future.get();
}

void MaskSuite::setMaskInvert(MaskRefPtr mask_refH, bool invertB)
{
    auto future = ae::ScheduleOrExecute([mask_refH, invertB]() {
        CheckNotNull(&mask_refH, "Error Setting Mask Invert. Mask is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskInvert(*mask_refH, invertB));
    });
    future.wait();
}

MaskMode MaskSuite::getMaskMode(MaskRefPtr mask_refH)
{
    auto future = ae::ScheduleOrExecute([mask_refH]() {
        CheckNotNull(&mask_refH, "Error Getting Mask Mode. Mask is Null");
        PF_MaskMode mode;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskMode(*mask_refH, &mode));
        return MaskMode(mode);
    });
    return future.get();
}

void MaskSuite::setMaskMode(MaskRefPtr maskH, MaskMode mode)
{
    auto future = ae::ScheduleOrExecute([maskH, mode]() {
        CheckNotNull(&maskH, "Error Setting Mask Mode. Mask is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskMode(*maskH, PF_MaskMode(mode)));
    });
    future.wait();
}

MaskMBlur MaskSuite::getMaskMotionBlurState(MaskRefPtr mask_refH)
{
    auto future = ae::ScheduleOrExecute([mask_refH]() {
        CheckNotNull(&mask_refH, "Error Getting Mask Motion Blur State. Mask is Null");
        AEGP_MaskMBlur blur_state;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskMotionBlurState(*mask_refH,
                                                                                                         &blur_state));
        return MaskMBlur(blur_state);
    });
    return future.get();
}

void MaskSuite::setMaskMotionBlurState(MaskRefPtr mask_refH, MaskMBlur blur_state)
{
    auto future = ae::ScheduleOrExecute([mask_refH, blur_state]() {
        CheckNotNull(&mask_refH, "Error Setting Mask Motion Blur State. Mask is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskMotionBlurState(
            *mask_refH, AEGP_MaskMBlur(blur_state)));
    });
    future.wait();
}

MaskFeatherFalloff MaskSuite::getMaskFeatherFalloff(MaskRefPtr mask_refH)
{
    auto future = ae::ScheduleOrExecute([mask_refH]() {
        CheckNotNull(&mask_refH, "Error Getting Mask Feather Falloff. Mask is Null");
        AEGP_MaskFeatherFalloff feather_falloff;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskFeatherFalloff(
            *mask_refH, &feather_falloff));
        return MaskFeatherFalloff(feather_falloff);
    });
    return future.get();
}

void MaskSuite::setMaskFeatherFalloff(MaskRefPtr mask_refH, MaskFeatherFalloff feather_falloffP)
{
    auto future = ae::ScheduleOrExecute([mask_refH, feather_falloffP]() {
        CheckNotNull(&mask_refH, "Error Setting Mask Feather Falloff. Mask is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskFeatherFalloff(
            *mask_refH, AEGP_MaskFeatherFalloff(feather_falloffP)));
    });
    future.wait();
}

AEGP_MaskIDVal MaskSuite::getMaskID(MaskRefPtr mask_refH)
{
    auto future = ae::ScheduleOrExecute([mask_refH]() {
        CheckNotNull(&mask_refH, "Error Getting Mask ID. Mask is Null");
        AEGP_MaskIDVal id;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskID(*mask_refH, &id));
        return id;
    });
    return future.get();
}

MaskRefPtr MaskSuite::createNewMask(LayerPtr layerH, int mask_indexPL0)
{
    auto future = ae::ScheduleOrExecute([layerH, &mask_indexPL0]() {
        CheckNotNull(&layerH, "Error Creating New Mask. Layer is Null");
        AEGP_MaskRefH maskH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_CreateNewMask(*layerH, &maskH,
                                                                                                &mask_indexPL0));
        return makeMaskRefPtr(maskH);
    });
    return future.get();
}

void MaskSuite::deleteMaskFromLayer(MaskRefPtr mask_refH)
{
    auto future = ae::ScheduleOrExecute([mask_refH]() {
        CheckNotNull(&mask_refH, "Error Deleting Mask from Layer. Mask is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_DeleteMaskFromLayer(*mask_refH));
    });
    future.wait();
}

ColorVal MaskSuite::getMaskColor(MaskRefPtr mask_refH)
{
    auto future = ae::ScheduleOrExecute([mask_refH]() {
        CheckNotNull(&mask_refH, "Error Getting Mask Color. Mask is Null");
        AEGP_ColorVal color;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskColor(*mask_refH, &color));
        return ColorVal(color);
    });
    return future.get();
}

void MaskSuite::setMaskColor(MaskRefPtr mask_refH, ColorVal colorP)
{
    auto future = ae::ScheduleOrExecute([mask_refH, &colorP]() {
        CheckNotNull(&mask_refH, "Error Setting Mask Color. Mask is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskColor(*mask_refH,
                                                                                               &colorP.toAEGP()));
    });
    future.wait();
}

bool MaskSuite::getMaskLockState(MaskRefPtr mask_refH)
{

    auto future = ae::ScheduleOrExecute([mask_refH]() {
        CheckNotNull(&mask_refH, "Error Getting Mask Lock State. Mask is Null");
        A_Boolean lockB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskLockState(*mask_refH, &lockB));
        return static_cast<bool>(lockB);
    });
    return future.get();
}

void MaskSuite::setMaskLockState(MaskRefPtr mask_refH, bool lockB)
{
    auto future = ae::ScheduleOrExecute([mask_refH, lockB]() {
        CheckNotNull(&mask_refH, "Error Setting Mask Lock State. Mask is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskLockState(*mask_refH, lockB));
    });
    future.wait();
}

bool MaskSuite::getMaskIsRotoBezier(MaskRefPtr mask_refH)
{
    auto future = ae::ScheduleOrExecute([mask_refH]() {
        CheckNotNull(&mask_refH, "Error Getting Mask Is Roto Bezier. Mask is Null");
        A_Boolean is_roto_bezierB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_GetMaskIsRotoBezier(
            *mask_refH, &is_roto_bezierB));
        return static_cast<bool>(is_roto_bezierB);
    });
    return future.get();
}

void MaskSuite::setMaskIsRotoBezier(MaskRefPtr mask_refH, bool is_roto_bezierB)
{
    auto future = ae::ScheduleOrExecute([mask_refH, is_roto_bezierB]() {
        CheckNotNull(&mask_refH, "Error Setting Mask Is Roto Bezier. Mask is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_SetMaskIsRotoBezier(*mask_refH,
                                                                                                      is_roto_bezierB));
    });
    future.wait();
}

MaskRefPtr MaskSuite::duplicateMask(MaskRefPtr orig_mask_refH)
{
    auto future = ae::ScheduleOrExecute([orig_mask_refH]() {
        CheckNotNull(&orig_mask_refH, "Error Duplicating Mask. Original Mask is Null");
        AEGP_MaskRefH new_maskH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskSuite6()->AEGP_DuplicateMask(*orig_mask_refH,
                                                                                                &new_maskH));
        return makeMaskRefPtr(new_maskH);
    });
    return future.get();
}

bool MaskOutlineSuite::isMaskOutlineOpen(MaskOutlineValPtr mask_outlineH)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH]() {
        CheckNotNull(&mask_outlineH, "Error Checking if Mask Outline is Open. Mask Outline is Null");
        A_Boolean openB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_IsMaskOutlineOpen(
            *mask_outlineH, &openB));
        return static_cast<bool>(openB);
    });
    return future.get();
}

void MaskOutlineSuite::setMaskOutlineOpen(MaskOutlineValPtr mask_outlineH, bool openB)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH, openB]() {
        CheckNotNull(&mask_outlineH, "Error Setting Mask Outline Open. Mask Outline is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_SetMaskOutlineOpen(
            *mask_outlineH, openB));
    });
    future.wait();
}

int MaskOutlineSuite::getMaskOutlineNumSegments(MaskOutlineValPtr mask_outlineH)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH]() {
        CheckNotNull(&mask_outlineH, "Error Getting Mask Outline Number of Segments. Mask Outline is Null");
        int numSegmentsL;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_GetMaskOutlineNumSegments(
            *mask_outlineH, &numSegmentsL));
        return numSegmentsL;
    });
    return future.get();
}

MaskVertex MaskOutlineSuite::getMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_pointL)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH, which_pointL]() {
        CheckNotNull(&mask_outlineH, "Error Getting Mask Outline Vertex Info. Mask Outline is Null");
        AEGP_MaskVertex vertex;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_GetMaskOutlineVertexInfo(
            *mask_outlineH, which_pointL, &vertex));
        return MaskVertex(vertex);
    });
    return future.get();
}

void MaskOutlineSuite::setMaskOutlineVertexInfo(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_pointL,
                                                MaskVertex vertexP)
{

    auto future = ae::ScheduleOrExecute([mask_outlineH, which_pointL, &vertexP]() {
        CheckNotNull(&mask_outlineH, "Error Setting Mask Outline Vertex Info. Mask Outline is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_SetMaskOutlineVertexInfo(
            *mask_outlineH, which_pointL, &vertexP.toAEGP()));
    });
    future.wait();
}

void MaskOutlineSuite::createVertex(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex insert_position)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH, insert_position]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_CreateVertex(*mask_outlineH,
                                                                                                      insert_position));
    });
    future.wait();
}

void MaskOutlineSuite::deleteVertex(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex index)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH, index]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_DeleteVertex(*mask_outlineH,
                                                                                                      index));
    });
    future.wait();
}

int MaskOutlineSuite::getMaskOutlineNumFeathers(MaskOutlineValPtr mask_outlineH)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH]() {
        CheckNotNull(&mask_outlineH, "Error Getting Mask Outline Number of Feathers. Mask Outline is Null");
        int numFeathersL;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_GetMaskOutlineNumFeathers(
            *mask_outlineH, &numFeathersL));
        return numFeathersL;
    });
    return future.get();
}

MaskFeather MaskOutlineSuite::getMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH,
                                                        AEGP_FeatherIndex which_featherL)
{
    AEGP_MaskFeather feather;
    AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_GetMaskOutlineFeatherInfo(
        *mask_outlineH, which_featherL, &feather));
    return MaskFeather(feather);
    auto future = ae::ScheduleOrExecute([mask_outlineH, which_featherL]() {
        CheckNotNull(&mask_outlineH, "Error Getting Mask Outline Feather Info. Mask Outline is Null");
        AEGP_MaskFeather feather;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_GetMaskOutlineFeatherInfo(
            *mask_outlineH, which_featherL, &feather));
        return MaskFeather(feather);
    });
    return future.get();
}

void MaskOutlineSuite::setMaskOutlineFeatherInfo(MaskOutlineValPtr mask_outlineH, AEGP_VertexIndex which_featherL,
                                                 MaskFeather featherP)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH, which_featherL, &featherP]() {
        CheckNotNull(&mask_outlineH, "Error Setting Mask Outline Feather Info. Mask Outline is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_SetMaskOutlineFeatherInfo(
            *mask_outlineH, which_featherL, &featherP.toAEGP()));
    });
    future.wait();
}

AEGP_FeatherIndex MaskOutlineSuite::createMaskOutlineFeather(MaskOutlineValPtr mask_outlineH, MaskFeather featherP0)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH, &featherP0]() {
        AEGP_FeatherIndex index;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_CreateMaskOutlineFeather(
            *mask_outlineH, &featherP0.toAEGP(), &index));
        return index;
    });
    return future.get();
}

void MaskOutlineSuite::deleteMaskOutlineFeather(MaskOutlineValPtr mask_outlineH, AEGP_FeatherIndex index)
{
    auto future = ae::ScheduleOrExecute([mask_outlineH, index]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().MaskOutlineSuite3()->AEGP_DeleteMaskOutlineFeather(
            *mask_outlineH, index));
    });
    future.wait();
}

// FootageSuite5

FootagePtr FootageSuite::getMainFootageFromItem(ItemPtr itemH)
{
    auto future = ae::ScheduleOrExecute([itemH]() {
        CheckNotNull(&itemH, "Error Getting Main Footage from Item. Item is Null");
        AEGP_FootageH footageH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetMainFootageFromItem(*itemH,
                                                                                                            &footageH));
        return makeFootagePtr(footageH);
    });
    return future.get();
}

FootagePtr FootageSuite::getProxyFootageFromItem(ItemPtr itemH)
{
    auto future = ae::ScheduleOrExecute([itemH]() {
        CheckNotNull(&itemH, "Error Getting Proxy Footage from Item. Item is Null");
        AEGP_FootageH footageH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetProxyFootageFromItem(
            *itemH, &footageH));
        return makeFootagePtr(footageH);
    });
    return future.get();
}

std::tuple<int, int> FootageSuite::getFootageNumFiles(FootagePtr footageH)
{
    auto future = ae::ScheduleOrExecute([footageH]() {
        CheckNotNull(&footageH, "Error Getting Footage Number of Files. Footage is Null");
        int num_filesL;
        int num_framesL;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageNumFiles(
            *footageH, &num_filesL, &num_framesL));
        return std::make_tuple(num_filesL, num_framesL);
    });
    return future.get();
}

std::string FootageSuite::getFootagePath(FootagePtr footageH, int frame_numL, int file_indexL)
{
    auto future = ae::ScheduleOrExecute([footageH, frame_numL, file_indexL]() {
        CheckNotNull(&footageH, "Error Getting Footage Path. Footage is Null");
        AEGP_MemHandle pathH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootagePath(
            *footageH, frame_numL, file_indexL, &pathH));
        return memHandleToString(pathH);
    });
    return future.get();
}

FootageSignature FootageSuite::getFootageSignature(FootagePtr footageH)
{

    auto future = ae::ScheduleOrExecute([footageH]() {
        CheckNotNull(&footageH, "Error Getting Footage Signature. Footage is Null");
        AEGP_FootageSignature signature;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageSignature(*footageH,
                                                                                                         &signature));
        return FootageSignature(signature);
    });
    return future.get();
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

    std::string pathZ, FootageLayerKey layer_infoP0, FileSequenceImportOptions *sequence_optionsP0,
    InterpretationStyle interp_style)
{
    auto future = ae::ScheduleOrExecute([pathZ, &layer_infoP0, sequence_optionsP0, interp_style]() {
        std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(pathZ);
        AEGP_FootageH footageH;
        if (sequence_optionsP0 == NULL)
        {
            AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewFootage(
                *SuiteManager::GetInstance().GetPluginID(), path16.data(), &layer_infoP0.toAEGP(), NULL,
                AEGP_InterpretationStyle(interp_style), NULL, &footageH));
        }
        else
        {
            AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewFootage(
                *SuiteManager::GetInstance().GetPluginID(), path16.data(), &layer_infoP0.toAEGP(),
                &sequence_optionsP0->toAEGP(), AEGP_InterpretationStyle(interp_style), NULL, &footageH));
        }
        return makeFootagePtr(footageH);
    });

    return future.get();
}

ItemPtr FootageSuite::addFootageToProject(FootagePtr footageH, ItemPtr folderH)
{
    auto future = ae::ScheduleOrExecute([footageH, &folderH]() {
        CheckNotNull(&footageH, "Error Adding Footage to Project. Footage is Null");
        if (!folderH)
        {
            folderH = ProjSuite().GetProjectRootFolder(ProjSuite().GetProjectByIndex(0));
        }
        AEGP_ItemH itemH;
        footageH->removeDeleter(); // remove deleter since we're adding to project
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_AddFootageToProject(
            *footageH, *folderH, &itemH));
        return makeItemPtr(itemH);
    });
    return future.get();
}

void FootageSuite::setItemProxyFootage(FootagePtr footageH, ItemPtr itemH)
{
    auto future = ae::ScheduleOrExecute([footageH, itemH]() {
        CheckNotNull(&footageH, "Error Setting Item Proxy Footage. Footage is Null");
        CheckNotNull(&itemH, "Error Setting Item Proxy Footage. Item is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_SetItemProxyFootage(*footageH, *itemH));
    });
    future.wait();
}

void FootageSuite::replaceItemMainFootage(FootagePtr footageH, ItemPtr itemH)
{
    auto future = ae::ScheduleOrExecute([footageH, itemH]() {
        CheckNotNull(&footageH, "Error Replacing Item Main Footage. Footage is Null");
        CheckNotNull(&itemH, "Error Replacing Item Main Footage. Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_ReplaceItemMainFootage(*footageH,
                                                                                                            *itemH));
    });
    future.wait();
}

AEGP_FootageInterp FootageSuite::getFootageInterpretation(ItemPtr itemH, bool proxyB)
{
    auto future = ae::ScheduleOrExecute([itemH, proxyB]() {
        CheckNotNull(&itemH, "Error Getting Footage Interpretation. Item is Null");
        AEGP_FootageInterp interp;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageInterpretation(
            *itemH, proxyB, &interp));
        return interp;
    });
    return future.get();
}

void FootageSuite::setFootageInterpretation(ItemPtr itemH, bool proxyB, const AEGP_FootageInterp *interpP)
{
    auto future = ae::ScheduleOrExecute([itemH, proxyB, interpP]() {
        CheckNotNull(&itemH, "Error Setting Footage Interpretation. Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_SetFootageInterpretation(
            *itemH, proxyB, interpP));
    });
    future.wait();
}

FootageLayerKey FootageSuite::getFootageLayerKey(FootagePtr footageH)
{
    auto future = ae::ScheduleOrExecute([footageH]() {
        CheckNotNull(&footageH, "Error Getting Footage Layer Key. Footage is Null");
        AEGP_FootageLayerKey layer_key;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageLayerKey(*footageH,
                                                                                                        &layer_key));
        return FootageLayerKey(layer_key);
    });
    return future.get();
}

FootagePtr FootageSuite::newPlaceholderFootage(std::string nameZ, int width, int height, Time durationPT)
{
    auto future = ae::ScheduleOrExecute([nameZ, width, height, durationPT]() {
        AEGP_FootageH footageH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewPlaceholderFootage(
            *SuiteManager::GetInstance().GetPluginID(), nameZ.c_str(), width, height, &durationPT.toAEGP(), &footageH));
        return makeFootagePtr(footageH);
    });
    return future.get();
}

FootagePtr FootageSuite::newPlaceholderFootageWithPath(std::string pathZ, Platform path_platform,
                                                       AEIO_FileType file_type, int widthL, int heightL,
                                                       Time durationPT)
{
    auto future = ae::ScheduleOrExecute([pathZ, path_platform, file_type, widthL, heightL, durationPT]() {
        std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(pathZ);
        AEGP_FootageH footageH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewPlaceholderFootageWithPath(
            *SuiteManager::GetInstance().GetPluginID(), path16.data(), AEGP_Platform(path_platform), file_type, widthL,
            heightL, &durationPT.toAEGP(), &footageH));
        return makeFootagePtr(footageH);
    });
    return future.get();
}

FootagePtr FootageSuite::newSolidFootage(std::string nameZ, int width, int height, ColorVal colorP)
{
    auto future = ae::ScheduleOrExecute([nameZ, width, height, &colorP]() {
        AEGP_FootageH footageH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_NewSolidFootage(
            nameZ.c_str(), width, height, &colorP.toAEGP(), &footageH));
        return makeFootagePtr(footageH);
    });
    return future.get();
}

ColorVal FootageSuite::getSolidFootageColor(ItemPtr itemH, bool proxyB)
{
    auto future = ae::ScheduleOrExecute([itemH, proxyB]() {
        CheckNotNull(&itemH, "Error Getting Solid Footage Color. Item is Null");
        AEGP_ColorVal color;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetSolidFootageColor(
            *itemH, proxyB, &color));
        return ColorVal(color);
    });
    return future.get();
}

void FootageSuite::setSolidFootageColor(ItemPtr itemH, bool proxyB, ColorVal colorP)
{
    auto future = ae::ScheduleOrExecute([itemH, proxyB, &colorP]() {
        CheckNotNull(&itemH, "Error Setting Solid Footage Color. Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_SetSolidFootageColor(
            *itemH, proxyB, &colorP.toAEGP()));
    });
    future.wait();
}

void FootageSuite::setSolidFootageDimensions(ItemPtr itemH, bool proxyB, int widthL, int heightL)
{
    auto future = ae::ScheduleOrExecute([itemH, proxyB, widthL, heightL]() {
        CheckNotNull(&itemH, "Error Setting Solid Footage Dimensions. Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_SetSolidFootageDimensions(
            *itemH, proxyB, widthL, heightL));
    });
    future.wait();
}

SoundDataFormat FootageSuite::getFootageSoundDataFormat(FootagePtr footageH)
{
    auto future = ae::ScheduleOrExecute([footageH]() {
        CheckNotNull(&footageH, "Error Getting Footage Sound Data Format. Footage is Null");
        AEGP_SoundDataFormat format;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageSoundDataFormat(
            *footageH, &format));
        return SoundDataFormat(format);
    });
    return future.get();
}

FileSequenceImportOptions FootageSuite::getFootageSequenceImportOptions(FootagePtr footageH)
{
    auto future = ae::ScheduleOrExecute([footageH]() {
        CheckNotNull(&footageH, "Error Getting Footage Sequence Import Options. Footage is Null");
        AEGP_FileSequenceImportOptions options;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().FootageSuite5()->AEGP_GetFootageSequenceImportOptions(
            *footageH, &options));
        return FileSequenceImportOptions(options);
    });
    return future.get();
}

void UtilitySuite::reportInfo(const std::string &info_string)
{
    auto future = ae::ScheduleOrExecute([info_string]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite5()->AEGP_ReportInfo(
            *SuiteManager::GetInstance().GetPluginID(), info_string.c_str()));
    });
    future.wait();
}

void UtilitySuite::reportInfoUnicode(const std::string &info_string)
{
    auto future = ae::ScheduleOrExecute([info_string]() {
        std::vector<A_UTF16Char> info16 = ConvertUTF8ToUTF16(info_string);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_ReportInfoUnicode(
            *SuiteManager::GetInstance().GetPluginID(), info16.data()));
    });
    future.wait();
}

std::tuple<A_short, A_short> UtilitySuite::getDriverPluginInitFuncVersion()
{
    auto future = ae::ScheduleOrExecute([]() {
        A_short major;
        A_short minor;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetDriverPluginInitFuncVersion(
            &major, &minor));
        return std::make_tuple(major, minor);
    });
    return future.get();
}

std::tuple<A_short, A_short> UtilitySuite::getDriverImplementationVersion()
{
    auto future = ae::ScheduleOrExecute([]() {
        A_short major;
        A_short minor;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetDriverImplementationVersion(
            &major, &minor));
        return std::make_tuple(major, minor);
    });
    return future.get();
}

void UtilitySuite::startQuietErrors()
{
    AEGP_ErrReportState *err_stateP = nullptr;
    auto future = ae::ScheduleOrExecute([err_stateP]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_StartQuietErrors(err_stateP));
    });
    future.wait();
}

void UtilitySuite::endQuietErrors(bool report_quieted_errorsB)
{
    AEGP_ErrReportState *err_stateP = nullptr;
    auto future = ae::ScheduleOrExecute([report_quieted_errorsB, err_stateP]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_EndQuietErrors(
            report_quieted_errorsB, err_stateP));
    });
    future.wait();
}

std::string UtilitySuite::getLastErrorMessage(int buffer_size)
{
    auto future = ae::ScheduleOrExecute([buffer_size]() {
        A_Err error = A_Err_NONE;
        A_char bufferP[256];
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetLastErrorMessage(
            buffer_size, bufferP, &error));
        return std::string(bufferP);
    });
    return future.get();
}

void UtilitySuite::startUndoGroup(const std::string &undo_name)
{
    auto future = ae::ScheduleOrExecute([undo_name]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_StartUndoGroup(undo_name.c_str()));
    });
    future.wait();
}

void UtilitySuite::endUndoGroup()
{
    auto future = ae::ScheduleOrExecute(
        []() { AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_EndUndoGroup()); });
    future.wait();
}

void *UtilitySuite::getMainHWND()
{
    auto future = ae::ScheduleOrExecute([]() {
        void *hwnd = nullptr;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetMainHWND(&hwnd));
        return hwnd;
    });
    return future.get();
}

void UtilitySuite::showHideAllFloaters(bool include_tool_palB)
{
    auto future = ae::ScheduleOrExecute([include_tool_palB]() {
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_ShowHideAllFloaters(include_tool_palB));
    });
    future.wait();
}

ColorVal UtilitySuite::getPaintPalForeColor()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_ColorVal color;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_PaintPalGetForeColor(&color));
        return ColorVal(color);
    });
    return future.get();
}

ColorVal UtilitySuite::getPaintPalBackColor()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_ColorVal color;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_PaintPalGetBackColor(&color));
        return ColorVal(color);
    });
    return future.get();
}

void UtilitySuite::setPaintPalForeColor(ColorVal fore_color)
{
    auto future = ae::ScheduleOrExecute([&fore_color]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_PaintPalSetForeColor(
            &fore_color.toAEGP()));
    });
    future.wait();
}

void UtilitySuite::setPaintPalBackColor(ColorVal back_color)
{
    auto future = ae::ScheduleOrExecute([&back_color]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_PaintPalSetBackColor(
            &back_color.toAEGP()));
    });
    future.wait();
}

std::tuple<bool, ColorVal> UtilitySuite::getCharPalFillColor()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_ColorVal color;
        A_Boolean is_frontmostB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalGetFillColor(&is_frontmostB,
                                                                                                         &color));
        return std::make_tuple(static_cast<bool>(is_frontmostB), ColorVal(color));
    });
    return future.get();
}

std::tuple<bool, ColorVal> UtilitySuite::getCharPalStrokeColor()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_ColorVal color;
        A_Boolean is_frontmostB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalGetStrokeColor(
            &is_frontmostB, &color));
        return std::make_tuple(static_cast<bool>(is_frontmostB), ColorVal(color));
    });
    return future.get();
}

void UtilitySuite::setCharPalFillColor(ColorVal fill_color)
{
    auto future = ae::ScheduleOrExecute([&fill_color]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalSetFillColor(
            &fill_color.toAEGP()));
    });
    future.wait();
}

void UtilitySuite::setCharPalStrokeColor(ColorVal stroke_color)
{
    auto future = ae::ScheduleOrExecute([&stroke_color]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalSetStrokeColor(
            &stroke_color.toAEGP()));
    });
    future.wait();
}

bool UtilitySuite::charPalIsFillColorUIFrontmost()
{
    auto future = ae::ScheduleOrExecute([]() {
        A_Boolean is_frontmostB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CharPalIsFillColorUIFrontmost(
            &is_frontmostB));
        return static_cast<bool>(is_frontmostB);
    });
    return future.get();
}

Ratio UtilitySuite::convertFpLongToHSFRatio(double numberF)
{
    auto future = ae::ScheduleOrExecute([numberF]() {
        Ratio ratio;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_ConvertFpLongToHSFRatio(
            numberF, &ratio.toAEGP()));
        return ratio;
    });
    return future.get();
}

double UtilitySuite::convertHSFRatioToFpLong(Ratio ratioR)
{
    auto future = ae::ScheduleOrExecute([&ratioR]() {
        double number;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_ConvertHSFRatioToFpLong(
            ratioR.toAEGP(), &number));
        return number;
    });
    return future.get();
}

void UtilitySuite::causeIdleRoutinesToBeCalled()
{
    auto future = ae::ScheduleOrExecute([]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_CauseIdleRoutinesToBeCalled());
    });
    future.wait();
}

bool UtilitySuite::getSuppressInteractiveUI()
{
    auto future = ae::ScheduleOrExecute([]() {
        A_Boolean suppressB;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetSuppressInteractiveUI(&suppressB));
        return static_cast<bool>(suppressB);
    });
    return future.get();
}

void UtilitySuite::writeToOSConsole(const std::string &text)
{
    auto future = ae::ScheduleOrExecute([text]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_WriteToOSConsole(text.c_str()));
    });
    future.wait();
}

void UtilitySuite::writeToDebugLog(const std::string &subsystem, const std::string &eventType, const std::string &text)
{
    auto future = ae::ScheduleOrExecute([subsystem, eventType, text]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_WriteToDebugLog(
            subsystem.c_str(), eventType.c_str(), text.c_str()));
    });
    future.wait();
}

std::string UtilitySuite::getPluginPath(PluginPathType path_type)
{
    auto future = ae::ScheduleOrExecute([path_type]() {
        AEGP_MemHandle pathH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().UtilitySuite6()->AEGP_GetPluginPaths(
            *SuiteManager::GetInstance().GetPluginID(), AEGP_GetPathTypes(path_type), &pathH));
        return memHandleToString(pathH);
    });
    return future.get();
}

int RenderQueueItemSuite::getNumRQItems()
{
    auto future = ae::ScheduleOrExecute([]() {
        int numItemsL;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetNumRQItems(&numItemsL));
        return numItemsL;
    });
    return future.get();
}

RQItemRefPtr RenderQueueItemSuite::getRQItemByIndex(int rq_item_index)
{
    auto future = ae::ScheduleOrExecute([rq_item_index]() {
        AEGP_RQItemRefH rq_itemH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetRQItemByIndex(rq_item_index,
                                                                                                     &rq_itemH));
        return makeRQItemRefPtr(rq_itemH);
    });
    return future.get();
}

RQItemRefPtr RenderQueueItemSuite::getNextRQItem(RQItemRefPtr current_rq_item)
{
    auto future = ae::ScheduleOrExecute([current_rq_item]() {
        CheckNotNull(&current_rq_item, "Error Getting Next RQ Item. Current RQ Item is Null");
        AEGP_RQItemRefH next_rq_itemH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetNextRQItem(*current_rq_item,
                                                                                                  &next_rq_itemH));
        return makeRQItemRefPtr(next_rq_itemH);
    });
    return future.get();
}

int RenderQueueItemSuite::getNumOutputModulesForRQItem(RQItemRefPtr rq_item)
{
    auto future = ae::ScheduleOrExecute([rq_item]() {
        CheckNotNull(&rq_item, "Error Getting Number of Output Modules for RQ Item. RQ Item is Null");
        int numModulesL;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetNumOutputModulesForRQItem(
            *rq_item, &numModulesL));
        return numModulesL;
    });
    return future.get();
}

RenderItemStatus RenderQueueItemSuite::getRenderState(RQItemRefPtr rq_item)
{
    auto future = ae::ScheduleOrExecute([rq_item]() {
        CheckNotNull(&rq_item, "Error Getting Render State. RQ Item is Null");
        AEGP_RenderItemStatusType status;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetRenderState(*rq_item, &status));
        return RenderItemStatus(status);
    });
    return future.get();
}

void RenderQueueItemSuite::setRenderState(RQItemRefPtr rq_item, RenderItemStatus status)
{
    auto future = ae::ScheduleOrExecute([rq_item, status]() {
        CheckNotNull(&rq_item, "Error Setting Render State. RQ Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_SetRenderState(
            *rq_item, AEGP_RenderItemStatusType(status)));
    });
    future.wait();
}

Time RenderQueueItemSuite::getStartedTime(RQItemRefPtr rq_item)
{
    auto future = ae::ScheduleOrExecute([rq_item]() {
        CheckNotNull(&rq_item, "Error Getting Started Time. RQ Item is Null");
        Time time;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetStartedTime(*rq_item,
                                                                                                   &time.toAEGP()));
        return time;
    });
    return future.get();
}

Time RenderQueueItemSuite::getElapsedTime(RQItemRefPtr rq_item)
{
    auto future = ae::ScheduleOrExecute([rq_item]() {
        CheckNotNull(&rq_item, "Error Getting Elapsed Time. RQ Item is Null");
        Time time;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetElapsedTime(*rq_item,
                                                                                                   &time.toAEGP()));
        return time;
    });
    return future.get();
}

LogType RenderQueueItemSuite::getLogType(RQItemRefPtr rq_item)
{
    auto future = ae::ScheduleOrExecute([rq_item]() {
        CheckNotNull(&rq_item, "Error Getting Log Type. RQ Item is Null");
        AEGP_LogType logtype;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetLogType(*rq_item, &logtype));
        return LogType(logtype);
    });
    return future.get();
}

void RenderQueueItemSuite::setLogType(RQItemRefPtr rq_item, LogType logtype)
{
    auto future = ae::ScheduleOrExecute([rq_item, logtype]() {
        CheckNotNull(&rq_item, "Error Setting Log Type. RQ Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_SetLogType(*rq_item,
                                                                                               AEGP_LogType(logtype)));
    });
    future.wait();
}

void RenderQueueItemSuite::removeOutputModule(RQItemRefPtr rq_item, OutputModuleRefPtr outmod)
{
    auto future = ae::ScheduleOrExecute([rq_item, outmod]() {
        CheckNotNull(&rq_item, "Error Removing Output Module. RQ Item is Null");
        CheckNotNull(&outmod, "Error Removing Output Module. Output Module is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_RemoveOutputModule(*rq_item, *outmod));
    });
    future.wait();
}

std::string RenderQueueItemSuite::getComment(RQItemRefPtr rq_item)
{
    auto future = ae::ScheduleOrExecute([rq_item]() {
        CheckNotNull(&rq_item, "Error Getting Comment. RQ Item is Null");
        A_char commentP;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetComment(*rq_item, &commentP));
        return std::string(&commentP);
    });
    return future.get();
}

void RenderQueueItemSuite::setComment(RQItemRefPtr rq_item, const std::string &comment)
{
    auto future = ae::ScheduleOrExecute([rq_item, comment]() {
        CheckNotNull(&rq_item, "Error Setting Comment. RQ Item is Null");
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_SetComment(*rq_item, comment.c_str()));
    });
    future.wait();
}

CompPtr RenderQueueItemSuite::getCompFromRQItem(RQItemRefPtr rq_item)
{
    auto future = ae::ScheduleOrExecute([rq_item]() {
        CheckNotNull(&rq_item, "Error Getting Comp from RQ Item. RQ Item is Null");
        AEGP_CompH compH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_GetCompFromRQItem(*rq_item, &compH));
        return makeCompPtr(compH);
    });
    return future.get();
}

void RenderQueueItemSuite::deleteRQItem(RQItemRefPtr rq_item)
{
    auto future = ae::ScheduleOrExecute([rq_item]() {
        CheckNotNull(&rq_item, "Error Deleting RQ Item. RQ Item is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RQItemSuite3()->AEGP_DeleteRQItem(*rq_item));
    });
    future.wait();
}

OutputModuleRefPtr OutputModuleSuite::getOutputModuleByIndex(RQItemRefPtr rq_itemH, int outmod_indexL)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmod_indexL]() {
        CheckNotNull(&rq_itemH, "Error Getting Output Module by Index. RQ Item is Null");
        AEGP_OutputModuleRefH outmodH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetOutputModuleByIndex(
            *rq_itemH, outmod_indexL, &outmodH));
        return makeOutputModuleRefPtr(outmodH);
    });
    return future.get();
}

EmbeddingType OutputModuleSuite::getEmbedOptions(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH]() {
        CheckNotNull(&rq_itemH, "Error Getting Embed Options. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Getting Embed Options. Output Module is Null");
        AEGP_EmbeddingType embed_options;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetEmbedOptions(
            *rq_itemH, *outmodH, &embed_options));
        return EmbeddingType(embed_options);
    });
    return future.get();
}

void OutputModuleSuite::setEmbedOptions(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, EmbeddingType embed_options)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH, embed_options]() {
        CheckNotNull(&rq_itemH, "Error Setting Embed Options. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Setting Embed Options. Output Module is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetEmbedOptions(
            *rq_itemH, *outmodH, AEGP_EmbeddingType(embed_options)));
    });
    future.wait();
}

PostRenderAction OutputModuleSuite::getPostRenderAction(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH]() {
        CheckNotNull(&rq_itemH, "Error Getting Post Render Action. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Getting Post Render Action. Output Module is Null");
        AEGP_PostRenderAction post_render_action;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetPostRenderAction(
            *rq_itemH, *outmodH, &post_render_action));
        return PostRenderAction(post_render_action);
    });
    return future.get();
}

void OutputModuleSuite::setPostRenderAction(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                                            PostRenderAction post_render_action)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH, post_render_action]() {
        CheckNotNull(&rq_itemH, "Error Setting Post Render Action. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Setting Post Render Action. Output Module is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetPostRenderAction(
            *rq_itemH, *outmodH, AEGP_PostRenderAction(post_render_action)));
    });
    future.wait();
}

OutputTypes OutputModuleSuite::getEnabledOutputs(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH]() {
        CheckNotNull(&rq_itemH, "Error Getting Enabled Outputs. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Getting Enabled Outputs. Output Module is Null");
        AEGP_OutputTypes enabled_types;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetEnabledOutputs(
            *rq_itemH, *outmodH, &enabled_types));
        return OutputTypes(enabled_types);
    });
    return future.get();
}

void OutputModuleSuite::setEnabledOutputs(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, OutputTypes enabled_types)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH, enabled_types]() {
        CheckNotNull(&rq_itemH, "Error Setting Enabled Outputs. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Setting Enabled Outputs. Output Module is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetEnabledOutputs(
            *rq_itemH, *outmodH, AEGP_OutputTypes(enabled_types)));
    });
    future.wait();
}

VideoChannels OutputModuleSuite::getOutputChannels(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH]() {
        CheckNotNull(&rq_itemH, "Error Getting Output Channels. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Getting Output Channels. Output Module is Null");
        AEGP_VideoChannels output_channels;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetOutputChannels(
            *rq_itemH, *outmodH, &output_channels));
        return VideoChannels(output_channels);
    });
    return future.get();
}

void OutputModuleSuite::setOutputChannels(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                                          VideoChannels output_channels)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH, output_channels]() {
        CheckNotNull(&rq_itemH, "Error Setting Output Channels. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Setting Output Channels. Output Module is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetOutputChannels(
            *rq_itemH, *outmodH, AEGP_VideoChannels(output_channels)));
    });
    future.wait();
}

std::tuple<bool, StretchQuality, bool> OutputModuleSuite::getStretchInfo(RQItemRefPtr rq_itemH,
                                                                         OutputModuleRefPtr outmodH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH]() {
        CheckNotNull(&rq_itemH, "Error Getting Stretch Info. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Getting Stretch Info. Output Module is Null");
        A_Boolean is_enabledB;
        AEGP_StretchQuality stretch_quality;
        A_Boolean is_onB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetStretchInfo(
            *rq_itemH, *outmodH, &is_enabledB, &stretch_quality, &is_onB));
        return std::make_tuple(static_cast<bool>(is_enabledB), StretchQuality(stretch_quality),
                               static_cast<bool>(is_onB));
    });
    return future.get();
}

void OutputModuleSuite::setStretchInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, bool is_enabledB,
                                       StretchQuality stretch_quality)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH, is_enabledB, stretch_quality]() {
        CheckNotNull(&rq_itemH, "Error Setting Stretch Info. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Setting Stretch Info. Output Module is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetStretchInfo(
            *rq_itemH, *outmodH, is_enabledB, AEGP_StretchQuality(stretch_quality)));
    });
    future.wait();
}

std::tuple<bool, LRect> OutputModuleSuite::getCropInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH]() {
        CheckNotNull(&rq_itemH, "Error Getting Crop Info. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Getting Crop Info. Output Module is Null");
        A_Boolean is_enabledB;
        A_Rect crop_rect;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetCropInfo(
            *rq_itemH, *outmodH, &is_enabledB, &crop_rect));
        return std::make_tuple(static_cast<bool>(is_enabledB), LRect(crop_rect));
    });
    return future.get();
}

void OutputModuleSuite::setCropInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, bool enableB, LRect crop_rect)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH, enableB, &crop_rect]() {
        CheckNotNull(&rq_itemH, "Error Setting Crop Info. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Setting Crop Info. Output Module is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetCropInfo(
            *rq_itemH, *outmodH, enableB, crop_rect.toAEGP()));
    });
    future.wait();
}

std::tuple<SoundDataFormat, bool> OutputModuleSuite::getSoundFormatInfo(RQItemRefPtr rq_itemH,
                                                                        OutputModuleRefPtr outmodH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH]() {
        CheckNotNull(&rq_itemH, "Error Getting Sound Format Info. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Getting Sound Format Info. Output Module is Null");
        AEGP_SoundDataFormat sound_format_info;
        A_Boolean audio_enabledB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetSoundFormatInfo(
            *rq_itemH, *outmodH, &sound_format_info, &audio_enabledB));
        return std::make_tuple(SoundDataFormat(sound_format_info), static_cast<bool>(audio_enabledB));
    });
    return future.get();
}

void OutputModuleSuite::setSoundFormatInfo(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH,
                                           SoundDataFormat sound_format_info, bool audio_enabledB)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH, &sound_format_info, audio_enabledB]() {
        CheckNotNull(&rq_itemH, "Error Setting Sound Format Info. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Setting Sound Format Info. Output Module is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetSoundFormatInfo(
            *rq_itemH, *outmodH, sound_format_info.toAEGP(), audio_enabledB));
    });
    future.wait();
}

std::string OutputModuleSuite::getOutputFilePath(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH]() {
        CheckNotNull(&rq_itemH, "Error Getting Output File Path. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Getting Output File Path. Output Module is Null");
        AEGP_MemHandle pathH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_GetOutputFilePath(
            *rq_itemH, *outmodH, &pathH));
        return memHandleToString(pathH);
    });
    return future.get();
}

void OutputModuleSuite::setOutputFilePath(RQItemRefPtr rq_itemH, OutputModuleRefPtr outmodH, const std::string &path)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH, path]() {
        CheckNotNull(&rq_itemH, "Error Setting Output File Path. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Setting Output File Path. Output Module is Null");
        std::vector<A_UTF16Char> path16 = ConvertUTF8ToUTF16(path);
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_SetOutputFilePath(
            *rq_itemH, *outmodH, path16.data()));
    });
    future.wait();
}

OutputModuleRefPtr OutputModuleSuite::addDefaultOutputModule(RQItemRefPtr rq_itemH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH]() {
        CheckNotNull(&rq_itemH, "Error Adding Default Output Module. RQ Item is Null");
        AEGP_OutputModuleRefH outmodH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().OutputModuleSuite4()->AEGP_AddDefaultOutputModule(
            *rq_itemH, &outmodH));
        return makeOutputModuleRefPtr(outmodH);
    });
    return future.get();
}

std::tuple<std::string, std::string, bool, bool> OutputModuleSuite::getExtraOutputModuleInfo(RQItemRefPtr rq_itemH,
                                                                                             OutputModuleRefPtr outmodH)
{
    auto future = ae::ScheduleOrExecute([rq_itemH, outmodH]() {
        CheckNotNull(&rq_itemH, "Error Getting Extra Output Module Info. RQ Item is Null");
        CheckNotNull(&outmodH, "Error Getting Extra Output Module Info. Output Module is Null");
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
    });
    return future.get();
}

WorldPtr WorldSuite::newWorld(WorldType type, int widthL, int heightL)
{
    auto future = ae::ScheduleOrExecute([type, widthL, heightL]() {
        AEGP_WorldH worldH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_New(
            *SuiteManager::GetInstance().GetPluginID(), AEGP_WorldType(type), widthL, heightL, &worldH));
        return makeWorldPtr(worldH);
    });
    return future.get();
}

WorldType WorldSuite::getType(WorldPtr worldH)
{
    auto future = ae::ScheduleOrExecute([worldH]() {
        CheckNotNull(&worldH, "Error Getting World Type. World is Null");
        AEGP_WorldType type;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetType(*worldH, &type));
        return WorldType(type);
    });
    return future.get();
}

std::tuple<int, int> WorldSuite::getSize(WorldPtr worldH)
{
    auto future = ae::ScheduleOrExecute([worldH]() {
        CheckNotNull(&worldH, "Error Getting World Size. World is Null");
        int widthL;
        int heightL;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetSize(*worldH, &widthL, &heightL));
        return std::make_tuple(widthL, heightL);
    });
    return future.get();
}

A_u_long WorldSuite::getRowBytes(WorldPtr worldH)
{
    auto future = ae::ScheduleOrExecute([worldH]() {
        CheckNotNull(&worldH, "Error Getting Row Bytes. World is Null");
        A_u_long row_bytes;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetRowBytes(*worldH, &row_bytes));
        return row_bytes;
    });
    return future.get();
}

PF_Pixel8 *WorldSuite::getBaseAddr8(WorldPtr worldH)
{
    auto future = ae::ScheduleOrExecute([worldH]() {
        CheckNotNull(&worldH, "Error Getting Base Address 8. World is Null");
        PF_Pixel8 *base_addrP;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetBaseAddr8(*worldH, &base_addrP));
        return base_addrP;
    });
    return future.get();
}

PF_Pixel16 *WorldSuite::getBaseAddr16(WorldPtr worldH)
{
    auto future = ae::ScheduleOrExecute([worldH]() {
        CheckNotNull(&worldH, "Error Getting Base Address 16. World is Null");
        PF_Pixel16 *base_addrP;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetBaseAddr16(*worldH, &base_addrP));
        return base_addrP;
    });
    return future.get();
}

PF_PixelFloat *WorldSuite::getBaseAddr32(WorldPtr worldH)
{
    auto future = ae::ScheduleOrExecute([worldH]() {
        CheckNotNull(&worldH, "Error Getting Base Address 32. World is Null");
        PF_PixelFloat *base_addrP;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_GetBaseAddr32(*worldH, &base_addrP));
        return base_addrP;
    });
    return future.get();
}

PF_EffectWorld WorldSuite::fillOutPFEffectWorld(WorldPtr worldH)
{
    auto future = ae::ScheduleOrExecute([worldH]() {
        CheckNotNull(&worldH, "Error Filling Out PF Effect World. World is Null");
        PF_EffectWorld effect_world;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_FillOutPFEffectWorld(*worldH,
                                                                                                        &effect_world));
        return effect_world;
    });
    return future.get();
}

void WorldSuite::fastBlur(double radiusF, PF_ModeFlags mode, PF_Quality quality, WorldPtr worldH)
{
    auto future = ae::ScheduleOrExecute([radiusF, mode, quality, worldH]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_FastBlur(radiusF, mode, quality,
                                                                                            *worldH));
    });
    future.wait();
}

PlatformWorldPtr WorldSuite::newPlatformWorld(WorldType type, int widthL, int heightL)
{
    auto future = ae::ScheduleOrExecute([type, widthL, heightL]() {
        AEGP_PlatformWorldH worldH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_NewPlatformWorld(
            *SuiteManager::GetInstance().GetPluginID(), AEGP_WorldType(type), widthL, heightL, &worldH));
        return makePlatformWorldPtr(worldH);
    });
    return future.get();
}

WorldPtr WorldSuite::newReferenceFromPlatformWorld(PlatformWorldPtr platform_worldH)
{

    auto future = ae::ScheduleOrExecute([platform_worldH]() {
        CheckNotNull(&platform_worldH, "Error Creating Reference from Platform World. Platform World is Null");
        AEGP_WorldH worldH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().WorldSuite3()->AEGP_NewReferenceFromPlatformWorld(
            *SuiteManager::GetInstance().GetPluginID(), *platform_worldH, &worldH));
        return makeWorldPtr(worldH);
    });
    return future.get();
}

RenderOptionsPtr RenderOptionsSuite::newFromItem(ItemPtr itemH)
{
    auto future = ae::ScheduleOrExecute([itemH]() {
        CheckNotNull(&itemH, "Error Creating Render Options from Item. Item is Null");
        AEGP_RenderOptionsH optionsH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_NewFromItem(
            *SuiteManager::GetInstance().GetPluginID(), *itemH, &optionsH));
        return makeRenderOptionsPtr(optionsH);
    });
    return future.get();
}

RenderOptionsPtr RenderOptionsSuite::duplicate(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Duplicating Render Options. Options are Null");
        AEGP_RenderOptionsH new_optionsH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_Duplicate(
            *SuiteManager::GetInstance().GetPluginID(), *optionsH, &new_optionsH));
        return makeRenderOptionsPtr(new_optionsH);
    });
    return future.get();
}

void RenderOptionsSuite::setTime(RenderOptionsPtr optionsH, Time time)
{
    auto future = ae::ScheduleOrExecute([optionsH, time]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetTime(*optionsH,
                                                                                                   time.toAEGP()));
    });
    future.wait();
}

Time RenderOptionsSuite::getTime(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        Time time;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetTime(*optionsH,
                                                                                                   &time.toAEGP()));
        return time;
    });
    return future.get();
}

void RenderOptionsSuite::setTimeStep(RenderOptionsPtr optionsH, Time time_step)
{
    auto future = ae::ScheduleOrExecute([optionsH, time_step]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetTimeStep(
            *optionsH, time_step.toAEGP()));
    });
    future.wait();
}

Time RenderOptionsSuite::getTimeStep(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        Time time;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetTimeStep(*optionsH,
                                                                                                       &time.toAEGP()));
        return time;
    });
    return future.get();
}

void RenderOptionsSuite::setFieldRender(RenderOptionsPtr optionsH, PF_Field field_render)
{
    auto future = ae::ScheduleOrExecute([optionsH, field_render]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetFieldRender(
            *optionsH, field_render));
    });
    future.wait();
}

PF_Field RenderOptionsSuite::getFieldRender(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        PF_Field field_render;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetFieldRender(
            *optionsH, &field_render));
        return field_render;
    });
    return future.get();
}

void RenderOptionsSuite::setWorldType(RenderOptionsPtr optionsH, WorldType type)
{
    auto future = ae::ScheduleOrExecute([optionsH, type]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetWorldType(
            *optionsH, AEGP_WorldType(type)));
    });
    future.wait();
}

WorldType RenderOptionsSuite::getWorldType(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        AEGP_WorldType type;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetWorldType(*optionsH, &type));
        return WorldType(type);
    });
    return future.get();
}

void RenderOptionsSuite::setDownsampleFactor(RenderOptionsPtr optionsH, DownsampleFactor dsf)
{
    auto future = ae::ScheduleOrExecute([optionsH, dsf]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetDownsampleFactor(
            *optionsH, dsf.xS, dsf.yS));
    });
    future.wait();
}

DownsampleFactor RenderOptionsSuite::getDownsampleFactor(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting Downsample Factor. Options are Null");
        A_short x;
        A_short y;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetDownsampleFactor(
            *optionsH, &x, &y));
        return DownsampleFactor(x, y);
    });
    return future.get();
}

void RenderOptionsSuite::setRegionOfInterest(RenderOptionsPtr optionsH, LRect roiP)
{
    auto future = ae::ScheduleOrExecute([optionsH, &roiP]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetRegionOfInterest(
            *optionsH, &roiP.toAEGP()));
    });
    future.wait();
}

LRect RenderOptionsSuite::getRegionOfInterest(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting Region of Interest. Options are Null");
        A_LRect roi;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetRegionOfInterest(
            *optionsH, &roi));
        return LRect(roi);
    });
    return future.get();
}

void RenderOptionsSuite::setMatteMode(RenderOptionsPtr optionsH, MatteMode mode)
{
    auto future = ae::ScheduleOrExecute([optionsH, mode]() {
        CheckNotNull(&optionsH, "Error Setting Matte Mode. Options are Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetMatteMode(
            *optionsH, AEGP_MatteMode(mode)));
    });
    future.wait();
}

MatteMode RenderOptionsSuite::getMatteMode(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting Matte Mode. Options are Null");
        AEGP_MatteMode mode;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetMatteMode(*optionsH, &mode));
        return MatteMode(mode);
    });
    return future.get();
}

void RenderOptionsSuite::setChannelOrder(RenderOptionsPtr optionsH, ChannelOrder channel_order)
{
    auto future = ae::ScheduleOrExecute([optionsH, channel_order]() {
        CheckNotNull(&optionsH, "Error Setting Channel Order. Options are Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetChannelOrder(
            *optionsH, AEGP_ChannelOrder(channel_order)));
    });
    future.wait();
}

ChannelOrder RenderOptionsSuite::getChannelOrder(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting Channel Order. Options are Null");
        AEGP_ChannelOrder channel_order;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetChannelOrder(
            *optionsH, &channel_order));
        return ChannelOrder(channel_order);
    });
    return future.get();
}

void RenderOptionsSuite::setRenderGuideLayers(RenderOptionsPtr optionsH, bool render_themB)
{
    auto future = ae::ScheduleOrExecute([optionsH, render_themB]() {
        CheckNotNull(&optionsH, "Error Setting Render Guide Layers. Options are Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_SetRenderGuideLayers(
            *optionsH, render_themB));
    });
    future.wait();
}

bool RenderOptionsSuite::getRenderGuideLayers(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting Render Guide Layers. Options are Null");
        A_Boolean render_themB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderOptionsSuite3()->AEGP_GetRenderGuideLayers(
            *optionsH, &render_themB));
        return static_cast<bool>(render_themB);
    });
    return future.get();
}
LayerRenderOptionsPtr LayerRenderOptionsSuite::newFromLayer(LayerPtr layer)
{
    auto future = ae::ScheduleOrExecute([layer]() {
        CheckNotNull(&layer, "Error Creating Layer Render Options from Layer. Layer is Null");
        AEGP_LayerRenderOptionsH optionsH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_NewFromLayer(
            *SuiteManager::GetInstance().GetPluginID(), *layer, &optionsH));
        return makeLayerRenderOptionsPtr(optionsH);
    });
    return future.get();
}

LayerRenderOptionsPtr LayerRenderOptionsSuite::newFromUpstreamOfEffect(EffectRefPtr effect_ref)
{
    auto future = ae::ScheduleOrExecute([effect_ref]() {
        CheckNotNull(&effect_ref, "Error Creating Layer Render Options from Upstream of Effect. Effect is Null");
        AEGP_LayerRenderOptionsH optionsH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_NewFromUpstreamOfEffect(
            *SuiteManager::GetInstance().GetPluginID(), *effect_ref, &optionsH));
        return makeLayerRenderOptionsPtr(optionsH);
    });
    return future.get();
}

LayerRenderOptionsPtr LayerRenderOptionsSuite::newFromDownstreamOfEffect(EffectRefPtr effect_ref)
{
    auto future = ae::ScheduleOrExecute([effect_ref]() {
        CheckNotNull(&effect_ref, "Error Creating Layer Render Options from Downstream of Effect. Effect is Null");
        AEGP_LayerRenderOptionsH optionsH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_NewFromDownstreamOfEffect(
                *SuiteManager::GetInstance().GetPluginID(), *effect_ref, &optionsH));
        return makeLayerRenderOptionsPtr(optionsH);
    });
    return future.get();
}

LayerRenderOptionsPtr LayerRenderOptionsSuite::duplicate(LayerRenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Duplicating Layer Render Options. Options are Null");
        AEGP_LayerRenderOptionsH new_optionsH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_Duplicate(
            *SuiteManager::GetInstance().GetPluginID(), *optionsH, &new_optionsH));
        return makeLayerRenderOptionsPtr(new_optionsH);
    });
    return future.get();
}

void LayerRenderOptionsSuite::setTime(LayerRenderOptionsPtr optionsH, Time time)
{
    auto future = ae::ScheduleOrExecute([optionsH, time]() {
        CheckNotNull(&optionsH, "Error Setting Time. Options are Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetTime(*optionsH,
                                                                                                        time.toAEGP()));
    });
    future.wait();
}

Time LayerRenderOptionsSuite::getTime(LayerRenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting Time. Options are Null");
        Time time;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetTime(
            *optionsH, &time.toAEGP()));
        return time;
    });
    return future.get();
}

void LayerRenderOptionsSuite::setTimeStep(LayerRenderOptionsPtr optionsH, Time time_step)
{
    auto future = ae::ScheduleOrExecute([optionsH, time_step]() {
        CheckNotNull(&optionsH, "Error Setting Time Step. Options are Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetTimeStep(
            *optionsH, time_step.toAEGP()));
    });
    future.wait();
}

Time LayerRenderOptionsSuite::getTimeStep(LayerRenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting Time Step. Options are Null");
        Time time_step;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetTimeStep(
            *optionsH, &time_step.toAEGP()));
        return time_step;
    });
    return future.get();
}

void LayerRenderOptionsSuite::setWorldType(LayerRenderOptionsPtr optionsH, WorldType type)
{
    auto future = ae::ScheduleOrExecute([optionsH, type]() {
        CheckNotNull(&optionsH, "Error Setting World Type. Options are Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetWorldType(
            *optionsH, AEGP_WorldType(type)));
    });
    future.wait();
}

WorldType LayerRenderOptionsSuite::getWorldType(LayerRenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting World Type. Options are Null");
        AEGP_WorldType type;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetWorldType(*optionsH,
                                                                                                             &type));
        return WorldType(type);
    });
    return future.get();
}

void LayerRenderOptionsSuite::setDownsampleFactor(LayerRenderOptionsPtr optionsH, DownsampleFactor dsf)
{
    auto future = ae::ScheduleOrExecute([optionsH, dsf]() {
        CheckNotNull(&optionsH, "Error Setting Downsample Factor. Options are Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetDownsampleFactor(
            *optionsH, dsf.xS, dsf.yS));
    });
    future.wait();
}

DownsampleFactor LayerRenderOptionsSuite::getDownsampleFactor(LayerRenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting Downsample Factor. Options are Null");
        A_short x, y;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetDownsampleFactor(
            *optionsH, &x, &y));
        return DownsampleFactor(x, y);
    });
    return future.get();
}
void LayerRenderOptionsSuite::setMatteMode(LayerRenderOptionsPtr optionsH, MatteMode mode)
{
    auto future = ae::ScheduleOrExecute([optionsH, mode]() {
        CheckNotNull(&optionsH, "Error Setting Matte Mode. Options are Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_SetMatteMode(
            *optionsH, AEGP_MatteMode(mode)));
    });
    future.wait();
}

MatteMode LayerRenderOptionsSuite::getMatteMode(LayerRenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Getting Matte Mode. Options are Null");
        AEGP_MatteMode mode;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().LayerRenderOptionsSuite2()->AEGP_GetMatteMode(*optionsH,
                                                                                                             &mode));
        return MatteMode(mode);
    });
    return future.get();
}

Collection2Ptr CollectionSuite::newCollection()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_Collection2H collectionH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_NewCollection(
            *SuiteManager::GetInstance().GetPluginID(), &collectionH));
        return makeCollection2Ptr(collectionH);
    });
    return future.get();
}

int CollectionSuite::getCollectionNumItems(Collection2Ptr collectionH)
{
    auto future = ae::ScheduleOrExecute([collectionH]() {
        CheckNotNull(&collectionH, "Error Getting Collection Number of Items. Collection is Null");
        A_u_long numItemsL;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_GetCollectionNumItems(
            *collectionH, &numItemsL));
        return static_cast<int>(numItemsL);
    });
    return future.get();
}

AEGP_CollectionItemV2 CollectionSuite::getCollectionItemByIndex(Collection2Ptr collectionH, int indexL)
{
    auto future = ae::ScheduleOrExecute([collectionH, indexL]() {
        CheckNotNull(&collectionH, "Error Getting Collection Item by Index. Collection is Null");
        AEGP_CollectionItemV2 item;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_GetCollectionItemByIndex(
            *collectionH, indexL, &item));
        return item;
    });
    return future.get();
}

void CollectionSuite::collectionPushBack(Collection2Ptr collectionH, const AEGP_CollectionItemV2 &itemP)
{
    auto future = ae::ScheduleOrExecute([collectionH, &itemP]() {
        CheckNotNull(&collectionH, "Error Pushing Back to Collection. Collection is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_CollectionPushBack(*collectionH,
                                                                                                           &itemP));
    });
    future.wait();
}

void CollectionSuite::collectionErase(Collection2Ptr collectionH, int index_firstL, int index_lastL)
{
    auto future = ae::ScheduleOrExecute([collectionH, index_firstL, index_lastL]() {
        CheckNotNull(&collectionH, "Error Erasing Collection. Collection is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CollectionSuite2()->AEGP_CollectionErase(
            *collectionH, index_firstL, index_lastL));
    });
    future.wait();
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
    auto future = ae::ScheduleOrExecute([command]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().CommandSuite1()->AEGP_DoCommand(command));
    });
}
FrameReceiptPtr RenderSuite::renderAndCheckoutFrame(RenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Rendering and Checking Out Frame. Options are Null");
        AEGP_FrameReceiptH receiptH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_RenderAndCheckoutFrame(
            *optionsH, NULL, NULL, &receiptH));
        return makeFrameReceiptPtr(receiptH);
    });
    return future.get();
}

FrameReceiptPtr RenderSuite::renderAndCheckoutLayerFrame(LayerRenderOptionsPtr optionsH)
{
    auto future = ae::ScheduleOrExecute([optionsH]() {
        CheckNotNull(&optionsH, "Error Rendering and Checking Out Layer Frame. Options are Null");
        AEGP_FrameReceiptH receiptH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_RenderAndCheckoutLayerFrame(
            *optionsH, NULL, NULL, &receiptH));
        return makeFrameReceiptPtr(receiptH);
    });
    return future.get();
}

AEGP_AsyncRequestId RenderSuite::renderAndCheckoutLayerFrameAsync(LayerRenderOptionsPtr optionsH,
                                                                  AEGP_AsyncFrameReadyCallback callback,
                                                                  AEGP_AsyncFrameRequestRefcon refcon)
{
    auto future = ae::ScheduleOrExecute([optionsH, callback, refcon]() {
        CheckNotNull(&optionsH, "Error Rendering and Checking Out Layer Frame Asynchronously. Options are Null");
        A_u_longlong id;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_RenderAndCheckoutLayerFrame_Async(
            *optionsH, callback, refcon, &id));
        return id;
    });
    return future.get();
}

void RenderSuite::cancelAsyncRequest(AEGP_AsyncRequestId async_request_id)
{
    auto future = ae::ScheduleOrExecute([async_request_id]() {
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_CancelAsyncRequest(async_request_id));
    });
    future.wait();
}

WorldPtr RenderSuite::getReceiptWorld(FrameReceiptPtr receiptH)
{
    auto future = ae::ScheduleOrExecute([receiptH]() {
        CheckNotNull(&receiptH, "Error Getting Receipt World. Receipt is Null");
        AEGP_WorldH worldH;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_GetReceiptWorld(*receiptH, &worldH));
        return makeWorldPtr(worldH, false);
    });
    return future.get();
}

LRect RenderSuite::getRenderedRegion(FrameReceiptPtr receiptH)
{
    auto future = ae::ScheduleOrExecute([receiptH]() {
        CheckNotNull(&receiptH, "Error Getting Rendered Region. Receipt is Null");
        A_LRect region;
        AE_CHECK(
            SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_GetRenderedRegion(*receiptH, &region));
        return LRect(region);
    });
    return future.get();
}

bool RenderSuite::isRenderedFrameSufficient(RenderOptionsPtr rendered_optionsH, RenderOptionsPtr proposed_optionsH)
{
    auto future = ae::ScheduleOrExecute([rendered_optionsH, proposed_optionsH]() {
        CheckNotNull(&rendered_optionsH, "Error Checking if Rendered Frame is Sufficient. Rendered Options are Null");
        CheckNotNull(&proposed_optionsH, "Error Checking if Rendered Frame is Sufficient. Proposed Options are Null");
        A_Boolean is_sufficientB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_IsRenderedFrameSufficient(
            *rendered_optionsH, *proposed_optionsH, &is_sufficientB));
        return static_cast<bool>(is_sufficientB);
    });
    return future.get();
}

TimeStampPtr RenderSuite::getCurrentTimestamp()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_TimeStamp timeStamp;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_GetCurrentTimestamp(&timeStamp));
        return makeTimeStampPtr(timeStamp);
    });
    return future.get();
}

bool RenderSuite::hasItemChangedSinceTimestamp(ItemPtr itemH, Time start_timeP, Time durationP,
                                               TimeStampPtr time_stampP)
{
    auto future = ae::ScheduleOrExecute([itemH, start_timeP, durationP, time_stampP]() {
        CheckNotNull(&itemH, "Error Checking if Item has Changed Since Timestamp. Item is Null");
        CheckNotNull(&time_stampP, "Error Checking if Item has Changed Since Timestamp. Time Stamp is Null");
        A_Boolean has_changedB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_HasItemChangedSinceTimestamp(
            *itemH, &start_timeP.toAEGP(), &durationP.toAEGP(), &time_stampP->get(), &has_changedB));
        return static_cast<bool>(has_changedB);
    });
    return future.get();
}

bool RenderSuite::isItemWorthwhileToRender(RenderOptionsPtr roH, TimeStampPtr time_stampP)
{
    auto future = ae::ScheduleOrExecute([roH, time_stampP]() {
        CheckNotNull(&roH, "Error Checking if Item is Worthwhile to Render. Render Options are Null");
        CheckNotNull(&time_stampP, "Error Checking if Item is Worthwhile to Render. Time Stamp is Null");
        A_Boolean is_worthwhileB;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_IsItemWorthwhileToRender(
            *roH, &time_stampP->get(), &is_worthwhileB));
        return static_cast<bool>(is_worthwhileB);
    });
    return future.get();
}

void RenderSuite::checkinRenderedFrame(RenderOptionsPtr roH, TimeStampPtr time_stampP, A_u_long ticks_to_renderL,
                                       PlatformWorldPtr imageH)
{
    auto future = ae::ScheduleOrExecute([roH, time_stampP, ticks_to_renderL, imageH]() {
        CheckNotNull(&roH, "Error Checking in Rendered Frame. Render Options are Null");
        CheckNotNull(&time_stampP, "Error Checking in Rendered Frame. Time Stamp is Null");
        CheckNotNull(&imageH, "Error Checking in Rendered Frame. Image is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_CheckinRenderedFrame(
            *roH, &time_stampP->get(), ticks_to_renderL, *imageH));
    });
    future.wait();
}

std::string RenderSuite::getReceiptGuid(FrameReceiptPtr receiptH)
{
    auto future = ae::ScheduleOrExecute([receiptH]() {
        CheckNotNull(&receiptH, "Error Getting Receipt GUID. Receipt is Null");
        AEGP_MemHandle guidH;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderSuite5()->AEGP_GetReceiptGuid(*receiptH, &guidH));
        return memHandleToString(guidH);
    });
    return future.get();
}

bool isLayerValid(ItemPtr item, CompPtr comp)
{
    return LayerSuite().IsAddLayerValid(item, comp);
}

void RenderQueueSuite::addCompToRenderQueue(CompPtr comp, const std::string &path)
{
    auto future = ae::ScheduleOrExecute([comp, path]() {
        CheckNotNull(comp->get(), "Error Adding Comp to Render Queue. Comp is Null");
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderQueueSuite1()->AEGP_AddCompToRenderQueue(
            *comp, path.c_str()));
    });
    future.wait();
}

void RenderQueueSuite::setRenderQueueState(RenderQueueState state)
{
    auto future = ae::ScheduleOrExecute([state]() {
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderQueueSuite1()->AEGP_SetRenderQueueState(
            AEGP_RenderQueueState(state)));
    });
    future.wait();
}

RenderQueueState RenderQueueSuite::getRenderQueueState()
{
    auto future = ae::ScheduleOrExecute([]() {
        AEGP_RenderQueueState state;
        AE_CHECK(SuiteManager::GetInstance().GetSuiteHandler().RenderQueueSuite1()->AEGP_GetRenderQueueState(&state));
        return RenderQueueState(state);
    });
    return future.get();
}
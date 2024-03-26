#include "AETK/AEGP/Core/Project.hpp"
#include "AETK/AEGP/Core/Items.hpp"
#include "AETK/AEGP/Core/Base/ItemCollection.hpp"

AE::Project AE::Project::open(const std::string &path)
{
    auto proj = ProjSuite6().OpenProjectFromPath(path);
    return Project(proj);
}

AE::Project AE::Project::newProject(const std::string &path)
{
    auto proj = ProjSuite6().NewProject();
    if (path != "")
    {

        ProjSuite6().SaveProjectToPath(proj, path);
    }

    return Project(proj);
}

std::shared_ptr<AE::ItemCollection> AE::Project::items()
{
    auto folder = m_suite.GetProjectRootFolder(m_proj);
    auto item = std::make_shared<AE::Item>(folder);
    return std::make_shared<AE::ItemCollection>(item);
}

std::string AE::Project::name()
{
    return ProjSuite6().GetProjectName(m_proj);
}

std::string AE::Project::path()
{
    return ProjSuite6().GetProjectPath(m_proj);
}

AE_ProjBitDepth AE::Project::bitDepth()
{
    return ProjSuite6().GetProjectBitDepth(m_proj);
}

void AE::Project::setBitDepth(AE_ProjBitDepth depth)
{
    ProjSuite6().SetProjectBitDepth(m_proj, depth);
}

void AE::Project::save()
{
    ProjSuite6().SaveProjectToPath(m_proj, ProjSuite6().GetProjectPath(m_proj));
}

void AE::Project::saveAs(const std::string &path)
{
    ProjSuite6().SaveProjectAs(m_proj, path);
}

bool AE::Project::isDirty()
{
    return ProjSuite6().ProjectIsDirty(m_proj);
}

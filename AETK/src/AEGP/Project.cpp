#include "AETK/AEGP/Project.hpp"
#include "AETK/AEGP/Items.hpp"
#include "AETK/AEGP/Template/ItemCollection.hpp"

Project Project::open(const std::string &path)
{
    auto proj = ProjSuite().OpenProjectFromPath(path);
    return Project(proj);

}

Project Project::newProject(const std::string &path)
{
    auto proj = ProjSuite().NewProject();
    if (path != "")
    {
        ProjSuite().SaveProjectToPath(proj, path);
    }
    return Project(proj);
}

tk::shared_ptr<ItemCollection> Project::items()
{
    if (!m_itemCollection)
    {
        auto folder = ProjSuite().GetProjectRootFolder(m_proj);
        auto item = tk::make_shared<Item>(folder);
        m_itemCollection = tk::make_shared<ItemCollection>(item);
	}
    return m_itemCollection;
}

std::string Project::name()
{
    return ProjSuite().GetProjectName(m_proj);

}

std::string Project::path()
{
    return ProjSuite().GetProjectPath(m_proj);
}

ProjBitDepth Project::bitDepth()
{
    return ProjSuite().GetProjectBitDepth(m_proj);
}

void Project::setBitDepth(ProjBitDepth depth)
{
    ProjSuite().SetProjectBitDepth(m_proj, depth);
}

void Project::save()
{
    ProjSuite().SaveProjectToPath(m_proj, ProjSuite().GetProjectPath(m_proj));
}

void Project::saveAs(const std::string &path)
{
    ProjSuite().SaveProjectAs(m_proj, path);
}

bool Project::isDirty()
{
    return ProjSuite().ProjectIsDirty(m_proj);
}

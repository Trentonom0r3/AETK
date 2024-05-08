#include "PyFx.hpp"

int pyfx::Project::num_projects()
{
    return ProjSuite().GetNumProjects();
}

ProjectPtr pyfx::Project::get_project_by_index(int index)
{
    return ProjSuite().GetProjectByIndex(index);
}

std::string pyfx::Project::get_project_name(ProjectPtr project)
{
    return ProjSuite().GetProjectName(project);
}


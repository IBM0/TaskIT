#include "Notebook.h"
#include "Operations.h"
#include <iostream>
#include <algorithm>

void Notebook::ReadLabel(const std::string &label)
{
    if (!Operations::notebookTasks.empty())
        Operations::notebookTasks.clear();

    std::copy_if(Operations::Tasks.begin(), Operations::Tasks.end(),
                 std::back_inserter(Operations::notebookTasks), [&](Task p) { return p.notebook == label; });
}
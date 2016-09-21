#include "AbstractFileModule.h"

#include <qfile.h>

QString AbstractFileModule::FixPath(const QString & file_path)
{
	QString path = file_path;

	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '/') {
			path.remove(i, 1);
			path.insert(i++, "\\");
		}
	}

	return path;
}

AbstractFileModule::AbstractFileModule() : application(nullptr), workDocument(nullptr), newDocument(nullptr)
{
}

bool AbstractFileModule::SaveAs(const QString & file_path)
{
	QString path = FixPath(file_path);

	if (QFile::exists(file_path))
	{
		if (!QFile::remove(file_path))
		{
            throw "Failed to remove file";
		}
	}

	newDocument->dynamicCall("SaveAs(const QString&)", path);
	return true;
}


AbstractFileModule::~AbstractFileModule()
{
}

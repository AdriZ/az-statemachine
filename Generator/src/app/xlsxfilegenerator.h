#ifndef XLSXFILEGENERATOR_H
#define XLSXFILEGENERATOR_H

#include "smdescription.h"
#include "xlsxdocument.h"


class XlsxFileGenerator
{
public:
    XlsxFileGenerator(QString whole_file_path);

    void generate(const SMDescription &sm_desc);

private:
    QString m_whole_file_path;
    QXlsx::Document m_xlsx;
};

#endif // XLSXFILEGENERATOR_H

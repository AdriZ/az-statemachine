#ifndef XLSXFILEGENERATOR_H
#define XLSXFILEGENERATOR_H

#include "smdescription.h"
#include "xlsxdocument.h"



class XlsxFileGenerator
{
public:
    typedef struct
    {
        int id;
        QString name;
        QString next_ids;
        QString next_labels;
        QString shape;
    } t_line;

public:
    XlsxFileGenerator(const QString &whole_file_path);

    void generate(const SMDescription &sm_desc);

private:
    QString m_whole_file_path;
    QXlsx::Document m_xlsx;

    QList<t_line> m_line_list;

    static void initLine(t_line &line);
    static void buildLineList(QList<t_line> &line_list, const SMDescription &sm_desc);
    static void fillXlsx(QXlsx::Document &xlsx, const QList<t_line> &line_list);
};

#endif // XLSXFILEGENERATOR_H

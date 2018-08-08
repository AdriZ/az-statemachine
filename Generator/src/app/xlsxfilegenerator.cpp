#include "xlsxfilegenerator.h"

XlsxFileGenerator::XlsxFileGenerator(QString whole_file_path)
    : m_whole_file_path(whole_file_path)
{

}

void XlsxFileGenerator::generate(const SMDescription &sm_desc)
{
    m_xlsx.write("A1", "Hello Qt!");
    m_xlsx.saveAs(m_whole_file_path.toUtf8());
}

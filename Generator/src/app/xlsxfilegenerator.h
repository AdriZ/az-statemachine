#ifndef XLSXFILEGENERATOR_H
#define XLSXFILEGENERATOR_H

#include "smdescription.h"
#include "xlsxdocument.h"


/**
 * @brief The XlsxFileGenerator class
 * Export an Excel (.xlsx) file representative of a state machine.
 * The Excel file is compatible with this note :
 * https://support.office.com/en-us/article/create-a-data-visualizer-diagram-17211b46-d144-4ca2-9ea7-b0f48f0ae0a6?ui=en-US
 * in order to be directly imported into Microsoft Visio.
 */
class XlsxFileGenerator
{
public:
    /**
     * Constructor. Do nothing and could be private as methods are all statics.
     */
    XlsxFileGenerator();

    /**
     * Generate the Excel file.
     *
     * @param[in] whole_file_path
     *      Path+name to save the .xlsx file.
     * @param[in] sm_desc
     *      State machine description.
     */
    static void generate(const QString &whole_file_path,
                         const SMDescription &sm_desc);

    /**
     * Generate the Excel file.
     *
     * @param[out] file
     *      File or IODevice to save the .xlsx.
     * @param[in] sm_desc
     *      State machine description.
     *
     * @warning Method not tested
     */
    static void generate(QIODevice * file,
                         const SMDescription &sm_desc);

private:
    /** Description of one state in the .xlsx
     *  correspond to: https://support.office.com/en-us/article/create-a-data-visualizer-diagram-17211b46-d144-4ca2-9ea7-b0f48f0ae0a6?ui=en-US
     */
    typedef struct
    {
        int id;             ///> Unique identifier
        QString name;       ///> Name of the state
        QString next_ids;   ///> Identifiers of possible next states (coma separated)
        QString next_labels;///> Labels (condition methods) to pass in these next states (coma separated)
        QString shape;      ///> Shape of the state
    } t_line;

    /**
     * Generate the Excel file.
     *
     * @param[out] xlsx
     *      Xlsx document to write
     * @param[in] sm_desc
     *      State machine description.
     */
    static void generate(QXlsx::Document &xlsx,
                         const SMDescription &sm_desc);

    /**
     * Init a t_line strcuture with 0 and empty strings.
     *
     * @param[out] line
     *      Line to init.
     */
    static void initLine(t_line &line);

    /**
     * Extract the state machines data to create a list t_line ready to be
     * write in an Excel file.
     *
     * @param[out] line_list
     *      Line list to write.
     * @param[in] sm_desc
     *      State machine which have to be exported
     */
    static void buildLineList(QList<t_line> &line_list,
                              const SMDescription &sm_desc);

    /**
     * Write an Excel document with the line list previously built thanks to buildLineList().
     *
     * @param[out] xlsx
     *      Excel document to complete
     * @param[in] line_list
     *      Excel lines to write
     * @param[in] sm_desc
     *      State machine descritpion (just used to extract title)
     */
    static void fillXlsx(QXlsx::Document &xlsx,
                         const QList<t_line> &line_list,
                         const SMDescription &sm_desc);
};

#endif // XLSXFILEGENERATOR_H

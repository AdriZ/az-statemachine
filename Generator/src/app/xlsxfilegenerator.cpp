#include "xlsxfilegenerator.h"
#include <QtDebug>
#include <QDate>

XlsxFileGenerator::XlsxFileGenerator(const QString &whole_file_path)
    : m_whole_file_path(whole_file_path)
{

}

void XlsxFileGenerator::generate(const SMDescription &sm_desc)
{
    buildLineList(m_line_list, sm_desc);
    fillXlsx(m_xlsx, sm_desc, m_line_list);

    m_xlsx.saveAs(m_whole_file_path);
}

void XlsxFileGenerator::initLine(XlsxFileGenerator::t_line &line)
{
    line.id = 0;
    line.name = "";
    line.next_ids = "";
    line.next_labels = "";
    line.shape = "";
}

void XlsxFileGenerator::buildLineList(QList<t_line> &line_list, const SMDescription &sm_desc)
{
    t_line _line;

    // For each state
    for( int _state_id = 0; _state_id < sm_desc.getStateList().size(); _state_id++ )
    {
        const t_state &_state = sm_desc.getStateList().at(_state_id);

        initLine(_line);
        _line.id = _state.id;
        _line.name = _state.name;
        _line.shape = "Process";

        // Seek transitions
        for ( int _transition_id = 0; _transition_id < sm_desc.getTransitionList().size(); _transition_id++ )
        {
            const t_transition &_transi = sm_desc.getTransitionList().at(_transition_id);

            // Transition from current state found
            if ( _transi.fromState == _state.name )
            {
                // Save the next id
                int _next_id;
                if ( sm_desc.getStateId(_next_id, _transi.toState) )
                {
                    if ( !_line.next_ids.isEmpty() )
                    {
                        _line.next_ids += ",";
                    }
                    _line.next_ids += QString::number(_next_id);
                }

                // Save the next condition
                if ( !_line.next_labels.isEmpty() )
                {
                    _line.next_labels += ",";
                }
                _line.next_labels += _transi.condition;

            }
        }

        line_list += _line;
    }
}

void XlsxFileGenerator::fillXlsx(QXlsx::Document &xlsx,
                                 const SMDescription &sm_desc,
                                 const QList<XlsxFileGenerator::t_line> &line_list)
{
    int _cell_line = 1;

    // Title
    xlsx.write(_cell_line, 1, sm_desc.getTitle());
    _cell_line++;

    // Informations
    xlsx.write(_cell_line, 1, "Generation date:");
    xlsx.write(_cell_line, 2, QDate::currentDate());
    _cell_line++;

    xlsx.write(_cell_line, 1, "How to import in Visio:");
    xlsx.write(_cell_line, 2, "https://support.office.com/en-us/article/create-a-data-visualizer-diagram-17211b46-d144-4ca2-9ea7-b0f48f0ae0a6?ui=en-US&rs=en-US&ad=US#ID0EBAEAAA=ID");
    _cell_line++;

    // Empty line
    _cell_line++;

    // Tab header
    xlsx.write(_cell_line, 1, "Process Step ID");
    xlsx.write(_cell_line, 2, "Process Step Description");
    xlsx.write(_cell_line, 3, "Next Step ID");
    xlsx.write(_cell_line, 4, "Connector Label");
    xlsx.write(_cell_line, 5, "Shape Type");
    _cell_line++;

    // Whole lines describing the finite state machine
    for( int _line_id = 0; _line_id < line_list.size(); _line_id++ )
    {
        xlsx.write(_cell_line, 1, line_list.at(_line_id).id);
        xlsx.write(_cell_line, 2, line_list.at(_line_id).name);
        xlsx.write(_cell_line, 3, line_list.at(_line_id).next_ids);
        xlsx.write(_cell_line, 4, line_list.at(_line_id).next_labels);
        xlsx.write(_cell_line, 5, line_list.at(_line_id).shape);
        _cell_line++;
    }
}

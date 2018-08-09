#include "xlsxfilegenerator.h"
#include <QtDebug>

XlsxFileGenerator::XlsxFileGenerator(const QString &whole_file_path)
    : m_whole_file_path(whole_file_path)
{

}

void XlsxFileGenerator::generate(const SMDescription &sm_desc)
{
    buildLineList(m_line_list, sm_desc);
    fillXlsx(m_xlsx, m_line_list);

//    m_xlsx.write("A1", "Hello Qt!");
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

void XlsxFileGenerator::fillXlsx(QXlsx::Document &xlsx, const QList<XlsxFileGenerator::t_line> &line_list)
{
//    char _col;
    QString _cell;

    for( int _line_id = 0; _line_id < line_list.size(); _line_id++ )
    {
//        _col = 'A';
        _cell = 'A' + QString::number(_line_id+1);
        xlsx.write(_cell, line_list.at(_line_id).id);
        _cell = 'B' + QString::number(_line_id+1);
        xlsx.write(_cell, line_list.at(_line_id).name);
        _cell = 'C' + QString::number(_line_id+1);
        xlsx.write(_cell, line_list.at(_line_id).next_ids);
        _cell = 'D' + QString::number(_line_id+1);
        xlsx.write(_cell, line_list.at(_line_id).next_labels);
        _cell = 'E' + QString::number(_line_id+1);
        xlsx.write(_cell, line_list.at(_line_id).shape);
    }
}

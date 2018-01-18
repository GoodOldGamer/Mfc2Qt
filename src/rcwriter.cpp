/* UI Converter MFC2QT (C) 2018 Holger Gerth
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QXmlStreamReader>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QGroupBox>
#include <QMessageBox>

#include "objectdata.h"
#include "rcwriter.h"

namespace
{
    const char* RCCTAG       = "RCC";
    const char* QRESOURCETAG = "qresource";
    const char* PREFIXATTR   = "prefix";
    const char* DEFPREFIX    = "res";
    const char* FILETAG      = "file";

    const char* INCLUDEGUARDS  = "<!INCLUDEGUARD!>";
    const char* ENUMID         = "<!ENUMID!>";
    const char* HEADERFILE     = "<!HEADERFILE!>";
    const char* CASESTATEMENTS = "<!CASESTATEMENTS!>";

    QString createEnum( const QStringList& ids )
    {
        QString enums;
        foreach( const QString& val, ids ) {
            if ( !enums.isEmpty() ) {
                enums += ",\n";
            }
            enums += val;
        }
        return enums;
    }

    QString createCaseStatements( const QMap<QString,QString>& strings )
    {
        QString cases;
        foreach( const QString& key, strings.keys() ) {
            cases += "\tcase " + key + ":\n";
            cases += "\t\treturn \"" + strings.value( key ) + "\";\n";
        }
        return cases;
    }

} // unnamed namespace

void RCWriter::writeQtRcFile( const QString& outputDir, const QString& filename, const QStringList& icons )
{
    auto filePath = outputDir + QDir::separator() + filename;
    QFile file( filePath );
    if ( !file.open(QIODevice::WriteOnly) ) {
        QMessageBox::critical( QApplication::focusWidget(), "Error writing resource file", QString("Failed to open output file %1!").arg(filePath) );
        return;
    }

    QXmlStreamWriter writer( &file );
    writer.setAutoFormatting( true );

    writer.writeStartElement( RCCTAG );
    writer.writeStartElement( QRESOURCETAG );
    writer.writeAttribute( PREFIXATTR, DEFPREFIX );

    for( int i = 0; i < icons.size(); ++i ) {
        QString repl = icons.at(i);
        repl = repl.remove( QRegExp( "\\(?!\\)" ) );
        writer.writeTextElement( FILETAG, repl );
    }

    writer.writeEndElement(); //QRESOURCETAG
    writer.writeEndElement(); //RCCTAG
}

void RCWriter::writeStringFile( const QString& outputDir, const QString& cppfile, const QString& headerfile, const QMap<QString,QString>& strings)
{
    QFile headerTemplate( ":/templates/STRING_TEMPLATE_H" );
    if ( !headerTemplate.open(QIODevice::ReadOnly) ) {
        QMessageBox::critical( QApplication::focusWidget(), "Error writing string file", "Failed to open header template!" );
        return;
    }
    QString headerData = headerTemplate.readAll();
    headerTemplate.close();

    QString includeguards = headerfile.toUpper();
    includeguards.replace( ".", "_" );
    includeguards = "__" + includeguards + "_";

    QString enums = createEnum( strings.keys() );

    headerData.replace( INCLUDEGUARDS, includeguards );
    headerData.replace( ENUMID, enums );

    auto headerFilePath = outputDir + QDir::separator() + headerfile;
    QFile header( headerFilePath );
    if( !header.open(QIODevice::WriteOnly) ) {
        QMessageBox::critical( QApplication::focusWidget(), "Error writing string file", QString("Failed to open header file %1!").arg(headerFilePath) );
        return;
    }
    header.write( headerData.toStdString().c_str() );
    header.close();

    QFile cppTemplate( ":/templates/STRING_TEMPLATE_CPP" );
    if( !cppTemplate.open(QIODevice::ReadOnly) ) {
        QMessageBox::critical( QApplication::focusWidget(), "Error writing string file", "Failed to open cpp template!" );
        return;
    }
    QString cppData = cppTemplate.readAll();
    cppTemplate.close();

    QString cases = createCaseStatements( strings );

    cppData.replace( HEADERFILE, "\"" + headerfile + "\"" );
    cppData.replace( CASESTATEMENTS, cases);

    auto cppFilePath = outputDir + QDir::separator() + cppfile;
    QFile cpp( cppFilePath );
    if( !cpp.open(QIODevice::WriteOnly) ) {
        QMessageBox::critical( QApplication::focusWidget(), "Error writing string file", QString("Failed to open cpp file! %1!").arg(cppFilePath) );
        return;
    }
    cpp.write( cppData.toStdString().c_str() );
    cpp.close();
}

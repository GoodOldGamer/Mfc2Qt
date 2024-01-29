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

#include <QDebug>
#include <QThread>
#include <QtGlobal>
#include <QSettings>

#include <QFileDialog>
#include <QCheckBox>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QTimer>
#include <QDesktopServices>

#include "ressourcedef.h"
#include "rcscanner.h"
#include "rcwriter.h"
#include "dialogpreview.h"
#include "dialoglistdelegate.h"
#include "mainwindow.h"

ConverterMainWindow::ConverterMainWindow()
    : cppStrings( "strings.cpp" )
    , headerStrings( "strings.h" )
    , qrcFile( "resource.qrc" )
    , dialogsModel( new DialogListModel(this) )
{
    ui.setupUi( this );

    ui.dialogList->setModel( dialogsModel );
    ui.dialogList->setItemDelegate( new DialogListDelegate(this) );
    ui.dialogList->horizontalHeader()->hide();
    ui.dialogList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui.dialogList->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect( ui.acClose, &QAction::triggered, this, &ConverterMainWindow::close );
    connect( ui.chooseRessourcefile, &QPushButton::clicked, this, &ConverterMainWindow::selectResourceFile );
    connect( ui.chooseOutputDir, &QPushButton::clicked, this, &ConverterMainWindow::selectOutputDir );
    connect( ui.acAbout, &QAction::triggered, this, &ConverterMainWindow::about );
    connect( ui.acHelp, &QAction::triggered, this, &ConverterMainWindow::help );
    connect( ui.ressourceFile, &QLineEdit::editingFinished, this, &ConverterMainWindow::readResourceFile );

    ui.progressBar->setVisible( false );

    QSettings settings;
    restoreGeometry( settings.value("mainWindowGeometry").toByteArray() );
    restoreState( settings.value("mainWindowState").toByteArray() );
}

ConverterMainWindow::~ConverterMainWindow()
{
    QSettings settings;
    settings.setValue( "mainWindowGeometry", saveGeometry() );
    settings.setValue( "mainWindowState", saveState() );
}

void ConverterMainWindow::about()
{
    QString text = "UI Converter MFC2QT (C) 2018 Holger Gerth\n\n"\
                   "This program is free software: you can redistribute it and/or modify\n"\
                   "it under the terms of the GNU General Public License as published by\n"\
                   "the Free Software Foundation, either version 3 of the License, or\n"\
                   "(at your option) any later version.\n\n"\
                   "This program is distributed in the hope that it will be useful,\n"\
                   "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"\
                   "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"\
                   "GNU General Public License for more details.\n\n"\
                   "You should have received a copy of the GNU General Public License\n"\
                   "along with this program. If not, see <http://www.gnu.org/licenses/>.";

    QMessageBox::about(this, tr("About MfC2Qt"), text);
}

void ConverterMainWindow::selectResourceFile()
{
    QString rcFile = QFileDialog::getOpenFileName( this, QString::fromLatin1( "Select resource file" ), "", tr( "Resource file (*.rc *.rc2)" ) );
    if ( rcFile.isEmpty() ) return;

    ui.ressourceFile->setText( rcFile );

    readResourceFile();
}

void ConverterMainWindow::readResourceFile()
{
    QTimer::singleShot(200, this, &ConverterMainWindow::parseRCFile);
}

// <2DO> threading
// <2DO> show progress
void ConverterMainWindow::parseRCFile()
{
    QString filePath = ui.ressourceFile->text();
    if ( filePath.isEmpty() ) {
        return;
    }

    RCScanner rcScanner(this);
    rcScanner.readFile( filePath );

    std::vector<ObjectDataSP> dialogs;
    QStringList dialogIDs = rcScanner.getDialogIDs();
    foreach( const QString& id, dialogIDs )
    {
        dialogs.push_back(rcScanner.getDialogData(id));
    }

    dialogImages = rcScanner.getImages();
    dialogStrings = rcScanner.getStringTable();
    dialogsModel->setDialogData(dialogs);
}

void ConverterMainWindow::selectOutputDir()
{
    QString outputDir = QFileDialog::getExistingDirectory( this, QString::fromLatin1( "Select output directory..." ), "" );
    if ( outputDir.isEmpty() ) return;

    ui.outputDir->setText( outputDir );
}

void ConverterMainWindow::help()
{
    // <2DO> implement help
    QMessageBox::information(this, "Help", "Not available.");
}

void ConverterMainWindow::showPreviewDialog(ObjectDataWP dlgDataPtr)
{
    auto dialog = createDialog(dlgDataPtr);
    if (dialog == nullptr) return;

    auto pos = rect().topRight();
    pos = mapToGlobal(pos);

    // adjust position
    dialog->move(pos.x() + 10, pos.y() - dialog->style()->pixelMetric( QStyle::PM_TitleBarHeight ));

    dialog->show();
    dialog->raise();
    dialog->activateWindow();
}

void ConverterMainWindow::saveDialog(ObjectDataWP dlgDataPtr)
{
    auto dialog = createDialog(dlgDataPtr);
    if (dialog == nullptr) return;

    // <2DO> write only dialog specific resources?
    RCWriter::writeQtRcFile( ui.outputDir->text(), qrcFile, dialogImages );
    RCWriter::writeStringFile( ui.outputDir->text(), cppStrings, headerStrings, dialogStrings );

    auto key = dialog->objectName();
    auto filename = key.mid( key.indexOf( "(" ) + 1, key.indexOf( ")" ) - key.indexOf( "(" ) - 1);
    auto fullPath = ui.outputDir->text() + QDir::separator() + filename + ".ui";

    QFile file( fullPath );
    if ( !file.open(QIODevice::WriteOnly) ) {
        QMessageBox::critical(this, "Error", "Failed to open output file!");
        return;
    }

    dialog->save(file);
    file.close();

    QMessageBox::information(this, tr("File saved"), tr("File saved as %1").arg(fullPath));
}

DialogPreview * ConverterMainWindow::createDialog(ObjectDataWP dlgDataPtr)
{
    auto dlgDataSP = dlgDataPtr.lock();
    if (!dlgDataSP) return nullptr;

    auto dialogData = dynamic_cast<DialogData*>(dlgDataSP.get());
    if (!dialogData) return nullptr;

    auto it = dialogCache.find(dialogData->getName());
    if ( it != dialogCache.end())
        return it->second;

    auto dialog = dynamic_cast<DialogPreview*>( dialogData->createQObject(this) );

    auto style = dialog->style();
    auto size = dialog->size();

    // add frame and title bar to size
    size.setWidth( size.width() + 2 * style->pixelMetric( QStyle::PM_MDIFrameWidth ) );
    size.setHeight( size.height() + style->pixelMetric( QStyle::PM_MDIFrameWidth ) + style->pixelMetric( QStyle::PM_TitleBarHeight ) );

    dialog->resize( size );

    dialogCache[dialogData->getName()] = dialog;

    return dialog;
}

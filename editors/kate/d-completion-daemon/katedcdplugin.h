#ifndef KATE_DCD_PLUGIN_H
#define KATE_DCD_PLUGIN_H
/* Description : Kate DCD plugin
 *
 * Copyright (C) 2013 by Tobias Pankrath <tobias@pankrath.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <ktexteditor/view.h>
#include <ktexteditor/document.h>

#include <kate/plugin.h>
#include <kate/application.h>
#include <kate/documentmanager.h>
#include <kate/mainwindow.h>
#include <kate/pluginconfigpageinterface.h>

class KateDcdCompletion;

//******************************************************************/
class KateDcdPlugin : public Kate::Plugin, public Kate::PluginConfigPageInterface
{
    Q_OBJECT
    Q_INTERFACES(Kate::PluginConfigPageInterface)

    public:
        explicit KateDcdPlugin(QObject* parent = 0, const QList<QVariant> & = QList<QVariant>());
        virtual ~KateDcdPlugin() {}

        Kate::PluginView *createView(Kate::MainWindow *mainWindow);

        // PluginConfigPageInterface
        uint configPages() const { return 1; };
        Kate::PluginConfigPage *configPage (uint number = 0, QWidget *parent = 0, const char *name = 0);
        QString configPageName (uint number = 0) const;
        QString configPageFullName (uint number = 0) const;
        KIcon configPageIcon (uint number = 0) const;
};

//******************************************************************/
class KateDcdConfigPage : public Kate::PluginConfigPage {
    Q_OBJECT
public:
    explicit KateDcdConfigPage( QWidget* parent = 0, KateDcdPlugin *plugin = 0 );
    ~KateDcdConfigPage() {}
    
    void apply();
    void reset();
    void defaults() {}

private:
    KateDcdPlugin      *m_plugin;
};


class KateDcdPluginView : public Kate::PluginView
{
    Q_OBJECT
public:
    KateDcdPluginView (KateDcdPlugin* plugin, Kate::MainWindow *mainWindow);
    virtual ~KateDcdPluginView ();

    /**
     * Load session specific settings here.
     * This function is called whenever a Kate session is loaded. You
     * should use the given \p config and prefix \p groupPrefix to store the
     * data. The group prefix exist so that the group does not clash with
     * other applications that use the same config file.
     * \param config the KConfig object which is to be used
     * \param groupPrefix the group prefix which is to be used
     * \see writeSessionConfig()
     */
    virtual void readSessionConfig (KConfigBase* config, const QString& groupPrefix);

    /**
     * Store session specific settings here.
     * This function is called whenever a Kate session is saved. You
     * should use the given \p config and prefix \p groupPrefix to store the
     * data. The group prefix exists so that the group does not clash with
     * other applications that use the same config file.
     * \param config the KConfig object which is to be used
     * \param groupPrefix the group prefix which is to be used
     * \see readSessionConfig()
     */
    virtual void writeSessionConfig (KConfigBase* config, const QString& groupPrefix);

public slots:
    void onViewCreated(KTextEditor::View* view);
    void onPluginViewCreated(QString name, Kate::PluginView* view);
    void onPluginViewDeleted(QString name, Kate::PluginView* view);
    void readProjectConfig();

private:
    KateDcdPlugin* m_plugin;
    KateDcdCompletion* m_completion;
    Kate::PluginView* m_projectPluginView;
};
#endif


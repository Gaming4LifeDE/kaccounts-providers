/*************************************************************************************
 *  Copyright (C) 2019 by Rituka Patwal <ritukapatwal21@gmail.com>                   * 
 *  Copyright (C) 2015 by Martin Klapetek <mklapetek@kde.org>                        *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 2                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/

#ifndef QMLHELPER_H
#define QMLHELPER_H

#include <QObject>
#include <QStringList>
#include <QtWidgets>
#include <QWebEngineView>
#include <QWebEnginePage> 
#include <QWebEngineHttpRequest> 

namespace KIO
{
    class Job;
};

class KJob;

class QmlHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking NOTIFY isWorkingChanged)
    Q_PROPERTY(bool noError READ noError NOTIFY noErrorChanged)
    Q_PROPERTY(bool isLoginComplete READ isLoginComplete NOTIFY isLoginCompleteChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged)

public:
    QmlHelper(QObject *parent = 0);
    ~QmlHelper();

    Q_INVOKABLE void checkServer(const QString &server);
    Q_INVOKABLE void finish(bool contactsEnabled);
    bool isWorking();
    bool noError();
    bool isLoginComplete();
    QString errorMessage() const;

Q_SIGNALS:
    void isWorkingChanged();
    void noErrorChanged();
    void errorMessageChanged();
    void isLoginCompleteChanged();
    void wizardFinished(const QString &username, const QString &password, const QVariantMap &data);

private Q_SLOTS:
    void fileChecked(KJob *job);
    void dataReceived(KIO::Job *job, const QByteArray &data);
    void authCheckResult(KJob *job);
    void finalUrlHandler(const QUrl &url);

private:
    void checkServer(const QUrl &url);
    void figureOutServer(const QUrl &url);
    void setWorking(bool start);
    void serverCheckResult();
    void openWebView();
    void wrongUrlDetected();

    QByteArray m_json;
    QString m_errorMessage;
    QString m_server;
    QString m_username;
    QString m_password;
    QUrl m_finalUrl;
    QWebEngineView * m_view = new QWebEngineView;
    QStringList m_disabledServices;
    bool m_isWorking = false;
    bool m_noError = false;
    bool m_isLoginComplete = false;

};

#endif // QMLHELPER_H

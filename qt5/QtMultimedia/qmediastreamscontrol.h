/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef QMEDIASTREAMSCONTROL_H
#define QMEDIASTREAMSCONTROL_H

#include <QtMultimedia/qmediacontrol.h>
#include <QtMultimedia/qmultimedia.h>
#include <QtMultimedia/qtmultimediadefs.h>
#include <QtMultimedia/qmediaenumdebug.h>

QT_BEGIN_NAMESPACE

// Required for QDoc workaround
class QString;

class Q_MULTIMEDIA_EXPORT QMediaStreamsControl : public QMediaControl
{
    Q_OBJECT
    Q_ENUMS(SteamType)
public:
    enum StreamType { UnknownStream, VideoStream, AudioStream, SubPictureStream, DataStream };

    virtual ~QMediaStreamsControl();

    virtual int streamCount() = 0;
    virtual StreamType streamType(int streamNumber) = 0;

    virtual QVariant metaData(int streamNumber, const QString &key) = 0;

    virtual bool isActive(int streamNumber) = 0;
    virtual void setActive(int streamNumber, bool state) = 0;

Q_SIGNALS:
    void streamsChanged();
    void activeStreamsChanged();

protected:
    QMediaStreamsControl(QObject *parent = 0);
};

#define QMediaStreamsControl_iid "org.qt-project.qt.mediastreamscontrol/5.0"
Q_MEDIA_DECLARE_CONTROL(QMediaStreamsControl, QMediaStreamsControl_iid)

QT_END_NAMESPACE

Q_DECLARE_METATYPE(QMediaStreamsControl::StreamType)

Q_MEDIA_ENUM_DEBUG(QMediaStreamsControl, StreamType)

#endif // QMEDIASTREAMSCONTROL_H


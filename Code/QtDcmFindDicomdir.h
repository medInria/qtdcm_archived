/*
    QtDcm is a C++ Qt based library for communication and conversion of Dicom images.
    Copyright (C) 2011  Alexandre Abadie <Alexandre.Abadie@univ-rennes1.fr>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#ifndef QTDCMFINDDICOMDIR_H_
#define QTDCMFINDDICOMDIR_H_

#include <QtGui>

class DcmItem;

class QtDcmFindDicomdirPrivate;

class QtDcmFindDicomdir : public QObject
{
    Q_OBJECT

public:
    QtDcmFindDicomdir ( QObject * parent = 0);
    virtual ~QtDcmFindDicomdir();

    void setDcmItem ( DcmItem * item );

    void findPatients();

    void findStudies ( const QString & patientName );

    void findSeries ( const QString & patientName, const QString & studyUid );

    void findImages ( const QString & seriesUID );

private:
    QtDcmFindDicomdirPrivate * d;
};

#endif /* QTDCMFINDDICOMDIR_H_ */

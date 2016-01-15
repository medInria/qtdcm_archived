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

// Dcmtk includes
#include <dcmtk/dcmdata/dcelem.h>
#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmnet/dfindscu.h>

#ifdef WITH_OPENSSL
#include "dcmtk/dcmtls/tlstrans.h"
#include "dcmtk/dcmtls/tlslayer.h"
#endif

// QtDcm includes
#include <QtDcmPatient.h>
#include <QtDcmStudy.h>
#include <QtDcmSerie.h>
#include <QtDcmImage.h>
#include <QtDcmManager.h>

#include <QtDcmFindCallback.h>

class QtDcmFindCallbackPrivate
{
public:
    int type;
};

QtDcmFindCallback::QtDcmFindCallback ( int type ) :
        d ( new QtDcmFindCallbackPrivate )
{
    d->type = type;
}

QtDcmFindCallback::~QtDcmFindCallback()
{
    delete d;
    d = NULL;
}

void QtDcmFindCallback::callback ( T_DIMSE_C_FindRQ *request, int responseCount, T_DIMSE_C_FindRSP *rsp, DcmDataset *responseIdentifiers )
{
    Q_UNUSED(request)
    Q_UNUSED(responseCount)
    Q_UNUSED(rsp)
    
    QMap<QString, QString> infosMap;

    OFString info;

    switch ( d->type )
    {

    case PATIENT:
        responseIdentifiers->findAndGetOFString ( DCM_PatientName, info );
        infosMap.insert ( "Name", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_PatientID, info );
        infosMap.insert ( "ID", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_PatientSex, info );
        infosMap.insert ( "Sex", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_PatientBirthDate, info );
        infosMap.insert ( "Birthdate", QString ( info.c_str() ) );

        QtDcmManager::instance()->foundPatient ( infosMap );

        break;

    case STUDY:
        responseIdentifiers->findAndGetOFString ( DCM_StudyDescription, info );
        infosMap.insert ( "Description", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_StudyDate, info );
        infosMap.insert ( "Date", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_StudyID, info );
        infosMap.insert ( "ID", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_StudyInstanceUID, info );
        infosMap.insert ( "UID", QString ( info.c_str() ) );

        QtDcmManager::instance()->foundStudy ( infosMap );

        break;

    case SERIE:
        responseIdentifiers->findAndGetOFString ( DCM_SeriesDescription, info );
        infosMap.insert ( "Description", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_StudyDate, info );
        infosMap.insert ( "Date", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_Modality, info );
        infosMap.insert ( "Modality", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_SeriesInstanceUID, info );
        infosMap.insert ( "ID", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_InstitutionName, info );
        infosMap.insert ( "Institution", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_PerformingPhysicianName, info );
        infosMap.insert ( "Operator", QString ( info.c_str() ) );
        responseIdentifiers->findAndGetOFString ( DCM_NumberOfSeriesRelatedInstances, info );
        infosMap.insert ( "InstanceCount", QString ( info.c_str() ) );

        QtDcmManager::instance()->foundSerie ( infosMap );
        break;

    case IMAGE:
        responseIdentifiers->findAndGetOFString ( DCM_SOPInstanceUID, info );

//         QtDcmManager::instance()->setPreviewImageUID ( QString ( info.c_str() ) );
        break;

    case IMAGES:
        OFString number;
        responseIdentifiers->findAndGetOFString ( DCM_SOPInstanceUID, info );
        responseIdentifiers->findAndGetOFString ( DCM_InstanceNumber, number );

        if ( !number.length() )
            number = "0";

        QtDcmManager::instance()->foundImage ( QString ( info.c_str() ), QString ( number.c_str() ).toInt() );

//         responseIdentifiers->print ( std::cout );

        break;
    }
}

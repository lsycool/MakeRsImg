// MakeRsImg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gdal_priv.h"
#include <iostream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	char ImgName[256];
	int datatype;
	long imgWidth;
	long imgHeight;
	int band;
	GDALDataType type;
	cout<<"GDT_Unknown = 0  "<<"GDT_Byte = 1  "<<"GDT_UInt16 = 2 "<<endl<<"GDT_Int16 = 3  "<<"GDT_UInt32 = 4  "<<"GDT_Int32 = 5  "<<endl;
	cout<<"GDT_Float32 = 6  "<<"GDT_Float64 = 7  "<<"GDT_CInt16 = 8  "<<endl<<"GDT_CInt32 = 9  "<<"GDT_CFloat32 = 10  "<<"GDT_CFloat64 = 11  "<<endl<<endl;

	while (TRUE)
	{
		cout<<"���Ӱ������"<<endl;
		cin>>ImgName;
		cout<<"Ӱ�����ͣ�"<<endl;
		cin>>datatype;
		cout<<"��������"<<endl;
		cin>>band;
		cout<<"Ӱ�񳤣�"<<endl;
		cin>>imgHeight;
		cout<<"Ӱ���"<<endl;
		cin>>imgWidth;
		switch (datatype)
		{
		case 0:
			type = GDT_Unknown;
			break;
		case 1:
			type = GDT_Byte;
			break;
		case 2:
			type = GDT_UInt16;
			break;
		case 3:
			type = GDT_Int16;
			break;
		case 4:
			type = GDT_UInt32;
			break;
		case 5:
			type = GDT_Int32;
			break;
		case 6:
			type = GDT_Float32;
			break;
		case 7:
			type = GDT_Float64;
			break;
		case 8:
			type = GDT_CInt16;
			break;
		case 9:
			type = GDT_CInt32;
			break;
		case 10:
			type = GDT_CFloat32;
			break;
		case 11:
			type = GDT_CFloat64;
			break;
		default:
			type = GDT_Byte;
			break;
		}

		GDALAllRegister();
		CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");	//open input file
		char **driverMetadata;
		GDALDriverH outputDriver = GDALGetDriverByName("GTiff");
		driverMetadata = GDALGetMetadata( outputDriver, NULL );
		if ( outputDriver == NULL )
		{
			return 0; //return NULL, driver does not exist
		}
		driverMetadata = GDALGetMetadata( outputDriver, NULL );
		if ( !CSLFetchBoolean( driverMetadata, GDAL_DCAP_CREATE, false ) )
		{
			return NULL; //driver exist, but it does not support the create operation
		}
		char **papszOptions = NULL;
		GDALDatasetH outputDataset = GDALCreate( outputDriver, ImgName, imgWidth, imgHeight, band, type, papszOptions );
		if ( outputDataset == NULL )
		{
			return 0;
		}

		double geotransform[6];
		GDALSetGeoTransform( outputDataset, geotransform );
		GDALSetProjection( outputDataset, "" );
		long nBitsPerPix = GDALGetDataTypeSize(type);
		void* Outdata = CPLCalloc(imgWidth*imgHeight,(nBitsPerPix/8));
		if(GDALDatasetRasterIO(outputDataset,
			GF_Write,						//IO��ʽ
			0,0,							//Ӱ��������ʼλ��x,y
			imgWidth,imgHeight,				//Ӱ�����ݿ��
			Outdata,						//ָ�򻺳�������ָ��
			imgWidth,imgHeight,				//���������ݿ��
			GDT_Byte,							//��������������
			band,							//���ȡ�Ĳ�����
			NULL,							//���ȡ�Ĳ����б�
			0,								//����������һ������ռ�õ��ֽ���
			0,								//������һ��������ռ�õ��ֽ���
			0)==CE_Failure )				//���������ݴ洢��ʽ 0ΪRRRRGGGGBBBB-bsp 1ΪRGBRGBRGB-bip	
		{
			cout<<"�����ļ�ʧ�ܣ�"<<endl;
			return 0;
		}
		else
		{
			cout<<"�����ļ��ɹ���"<<endl<<endl;
		}
	}
	return 0;
}

///*! Unknown or unspecified type */ 		  GDT_Unknown = 0,
///*! Eight bit unsigned integer */           GDT_Byte = 1,
///*! Sixteen bit unsigned integer */         GDT_UInt16 = 2,
///*! Sixteen bit signed integer */           GDT_Int16 = 3,
///*! Thirty two bit unsigned integer */      GDT_UInt32 = 4,
///*! Thirty two bit signed integer */        GDT_Int32 = 5,
///*! Thirty two bit floating point */        GDT_Float32 = 6,
///*! Sixty four bit floating point */        GDT_Float64 = 7,
///*! Complex Int16 */                        GDT_CInt16 = 8,
///*! Complex Int32 */                        GDT_CInt32 = 9,
///*! Complex Float32 */                      GDT_CFloat32 = 10,
///*! Complex Float64 */                      GDT_CFloat64 = 11,
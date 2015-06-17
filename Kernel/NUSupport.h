/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2010.
E-mail:		alexab@ailab.ru
url:        http://ailab.ru
Version:    1.0.0

This file - part of the project: Neuro Modeler Software Developer Kit (NMSDK)

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */
#ifndef NUSupportH
#define NUSupportH

#include "NSupport.h"

namespace NMSDK {

//using namespace RDK;

// Записывает изображение в bitmap
RDK_LIB_TYPE RDK::UBitmap& operator << (RDK::UBitmap &bmp, const RDK::UItemData &data);

// Записывает изображение в data
// data.DataSize устанавливается = 1
// Формал записи: Width,Height,ColorModel,<данные>
RDK_LIB_TYPE RDK::UItemData& operator >> (const RDK::UBitmap &bmp, RDK::UItemData &data);

// Записывает изображение в data
// Предполагает, что память уже выделена
// Формал записи: Width,Height,ColorModel,<данные>
RDK_LIB_TYPE const RDK::UItemData& operator >> (const RDK::UBitmap &bmp, const RDK::UItemData &data);
}
#endif

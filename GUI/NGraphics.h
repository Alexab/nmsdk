// ===========================================================
// Version:        1.0.0
// ===========================================================
/* ***********************************************************
@Copyright Alexander V. Bakhshiev, 2009.
E-mail:		alexab@ailab.ru
url:            http://ailab.ru

This file - part of the project: Neuro Modeler Software Developer Kit (NMSDK)

File License:        BSD License
Project License:     BSD License
See file license.txt for more information
*********************************************************** */
#ifndef N_GRAPHICS_H
#define N_GRAPHICS_H

#include "../Libraries/Nmsdk-BasicLib/Core/NSupport.h"
#include "rdk.h"

namespace NMSDK {

//using namespace RDK;
using RDK::UColorT;
using RDK::UBColor;
using RDK::UBitmap;
using RDK::UAGraphics;
using RDK::UGraphics;
using RDK::UBitmapFont;


/*
	Структура, описывающая объект NAContainer* как визуальный элемент
*/
struct NVDescription
{
// ------------------------
// Идентификационные параметры
// ------------------------
// Одномерный индекс i
int Index;

// 3D индекс (i,j,k)
// I,J - координаты ячейки в плоскости K
int I, J, K;

// Имя элемента
string Name;

// Id элемента (если -1 - Id не определен)
UId Id;

// Тип элемента
// 0 - не определено
// 1 - конечный элемент NAItem
// 2 - элемент-сеть NANet
int Type;
// ------------------------

// ------------------------
// Геометрические параметры
// ------------------------
// Координаты элемента в пикселях
int X,Y;

// Радиус элемента в пикселях
int Radius;

// Цвет контура элемента
UColorT ContourColor;

// Толщина контура элемента в пикселях
int ContourWidth;

// Цвет заливки элемента
UColorT FillColor;

// Цвет исходящих связей
UColorT LinkColor;

// Толщина контура связи
int LinkWidth;
// ------------------------

// ------------------------
// Индикаторы
// ------------------------
// Заполнение индикаторов в %
// (если -1, то отключен)
double TopIndicator,BottomIndicator,LeftIndicator,RightIndicator;
// ------------------------

// ------------------------
// Конструкторы и деструкторы
// ------------------------
NVDescription(void);
~NVDescription(void);
// ------------------------
};

/*
	Класс графического отображения НС
*/
class NGraphics
{
protected: // Данные
// Указатель на НС
UNet *Net;

// Таблица соответствий между нейронами сети и описаний визуальных элементов
map<UId,NVDescription> Descriptions;

// Движок для отображения сети
UAGraphics* GEngine;

protected: // Параметры
// ---------------------------
// Настройки отображения
// ---------------------------
// Реальная ширина и высота изображения
int CanvasWidth, CanvasHeight;

// Число элементов в строке
int ElementsXRes;

// Число строк элементов
int ElementsYRes;

// Цвет пустых индикаторов
UColorT IndicatorEmptyColorTop;
UColorT IndicatorEmptyColorBottom;
UColorT IndicatorEmptyColorLeft;
UColorT IndicatorEmptyColorRight;

// Цвет полных индикаторов
UColorT IndicatorFullColorTop;
UColorT IndicatorFullColorBottom;
UColorT IndicatorFullColorLeft;
UColorT IndicatorFullColorRight;

// Цвет фона
UColorT FoneColor;
// ---------------------------


public: // Методы
// ---------------------------
// Конструкторы и деструкторы
// ---------------------------
NGraphics(void);
~NGraphics(void);
// ---------------------------

// ---------------------------
// Методы доступа к данным
// ---------------------------
// Возвращает указатель на НС
UNet* GetNet(void);

// Возвращает элемент таблицы соответствий
NVDescription& GetDescription(const UId &id);

// Возвращает всю таблицу соответсвий
const map<UId,NVDescription>& GetDescriptions(void);

// Возвращает указатель на движок отображения
UAGraphics* GetGEngine(void);

// Связывает класс с новой НС
// Если net == 0 то отключает класс от текущей НС и возвращает true
bool SetNet(UNet *net);

// Связывает класс с новой НС
// Если engine == 0 то возвращает false и не делеает ничего
bool SetEngine(UAGraphics* engine);

// Обновляет таблицу соответствий
void UpdateDescriptions(void);
// ---------------------------

// ---------------------------
// Методы размещения элементов по графическому полю
// ---------------------------
// Метод автоматического распределения существующих элементов по полю
void BuildDestinations(void);

// Метод автоматического распределения нераспределенных элементов
// (нераспределенные элементы имеют координаты -1,-1)
void UpdateDestinations(void);

// Устанавливает координаты размещения элемента id
// Возвращает false если элемент не найден или координаты некорректны
// Метод не проверяет свободна-ли занимаемая область
bool SetDestination(const UId &id, int x, int y);
// ---------------------------

// ---------------------------
// Основные методы отображения
// ---------------------------
// Метод перерисовки всех элементов
void Draw(void);

// Метод обновления изображения отдельного элемента сети
// Возвращает false если элемент не найден
bool Draw(const UId &id);

// Метод отображения связей элемента сети
// (показывает с какими элементами связан этот элемент)
// links==true - отображает схему связей линиями
// highlight==true - подсвечивает все нейроны связанные с этим
// (сам нейрон подсвечивается в случае, если на него есть обратные связи)
// contour==true - окружает контуром нейроны связанные с этим
// (в контур могут попасть и не связанные нейроны)
bool DrawLinks(const UId &id,
			   bool links=true, bool highlight=false, bool contour=false);
// ---------------------------

// ---------------------------
// Вспомогательные методы отображения
// ---------------------------
// Отрисовывает элемент в заданной позиции
void Paint(NVDescription &ndescr, bool highlight=false);

// Отрисовывает конечный элемент (NAItem*) с центром в заданной позиции
void PaintItem(NVDescription &ndescr, bool highlight=false);

// Отрисовывает элемент-сеть (NANet*) с центром в заданной позиции
void PaintNet(NVDescription &ndescr, bool highlight=false);

// Отрисовывает связь
void PaintLink(NVDescription &out, NVDescription &in,
			   bool links=true, bool highlight=true, bool contour=true);


// Отрисовывает индикатор с заданными параметрами
// Направление direction задается следующим образом
// 1 - индикатор заполняется слева направо
// 2 - индикатор заполняется справа налево
// 3 - индикатор заполняется сверху вниз
// 4 - индикатор заполняется снизу вверх
void PaintIndicator(int x,int y, int width, int height,
				   double precent, int direction, UColorT full, UColorT empty);

// Отрисовывает окружность
// ---------------------------
};

}
#endif



﻿# GyverLamp for Arduino

Ещё одна облегченная версия прошивки лампы GyverLamp oт AlexGyver под ATmega382P.

_Ссылка на оригинал: https://github.com/AlexGyver/GyverLamp_

## Краткое описание

Лампа на адресных светодиодах c красивыми эффектами свечения:
* Конфетти (sparkles)
* Огонь (fire)
* Вертикальная радуга (rainbow vertical)
* Горизонтальная радуга (rainbow horizontal)
* Цвета (colors)
* Безумие (madness noise)
* Облака (cloud noise)
* Лава (lava noise)
* Плазма (plasma noise)
* Радужный шум (rainbow noise)
* Радужный шум с затемнениями (rainbow stripe noise)
* Зебра (zebra noise)
* Лес (forest noise)
* Oкеан (ocean noise)
* Цвет (color)
* Снег (snow)
* Матрица (matrix old)
* Белая лампа (white lamp)

## Основные отличия
от GyverLamp v1.4:
* Микроконтроллер ESP8622 заменён на ATMega328p
* убран будильник;
* убрана работа с Wi-Fi
*	эффект "Светляки" заменен на "Белая лампа"
* добавлена цветовая индикация для регулировок
* управление переработано для одного энкодера с кнопкой

## Управление

### Включение и выключение лампы

**Одиночное нажатие** кнопки энкодера включает или выключает лампу.

### Регулировка яркости текущего эффекта

**Просто вращая** энкодер можно изменить яркость текущего эффекта.
При этом в центре матрицы будет отображаться **красный столбик**, высота которого будет также изменяться пропорционально значению яркости.

### Смена текущего эффекта

**Двукратное нажатие** на кнопку энкодера переводит лампу в режим переключения эффектов (при этом нижний ряд лампы закрашивается красным цветом).
Теперь вращение энкодера будет последовательно "листать" эффекты.

_* Лампа сама вернётся в обычный режим, при котором вращение энкодера регулирует яркость, спустя 5 секунд бездействия. При этом красная полоска внизу исчезнет._

### Регулировка "масштаба" текущего эффекта

_* Обратите внимание, термин "масштаб" используется не в буквальном смысле. Как правило, это настройка "интенсивности" эффекта, количества элементов эффекта (например, количество снежинок) или его цветовая палитра (например, можно сделать синий огонь). В общем, регулировка по-разному влияет на различные эффекты — удачных экспериментов :)_

**Трехкратное нажатие** кнопки энкодера переводит лампу в режим регулировки "масштаба" текущего эффекта. В этом режиме вращение энкодера будет изменять значение "масштаба". При этом в центре матрицы будет отображаться **голубой столбик**, высота которого будет также изменяться пропорционально значению "масштаба".

_* Лампа сама вернётся в обычный режим, при котором вращение энкодера регулирует яркость, спустя 5 секунд бездействия. При этом голубой столбик исчезнет._

### Регулировка скорости проигрывания текущего эффекта

**Четырёхкратное нажатие** кнопки энкодера переводит лампу в режим регулировки скорости текущего эффекта. В этом режиме вращение энкодера будет изменять значение скорости. При этом в центре матрицы будет отображаться **зелёный столбик**, высота которого будет также изменяться пропорционально значению скорости.

_* Лампа сама вернётся в обычный режим, при котором вращение энкодера регулирует яркость, спустя 5 секунд бездействия. При этом зелёный столбик исчезнет._

### Сброс к "заводским" настройкам

**Пятикратное нажатие** кнопки энкодера сбрасывает сохранённые настройки лампы.

## Подключение

Пины настроенные в config.h:
* D4: Матрица
* D5: Энкодер DT
* D6: Энкодер CLK
* D7: Энкодер SW

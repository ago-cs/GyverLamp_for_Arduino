#pragma once
// ============= НАСТРОЙКИ =============

//// -------- РАССВЕТ -------
//#define DAWN_BRIGHT 200       // макс. яркость рассвета
//#define DAWN_TIMEOUT 1        // сколько рассвет светит после времени будильника, минут

// ---------- МАТРИЦА ---------
#define BRIGHTNESS 80      // стандартная маскимальная яркость (0-255)
#define CURRENT_LIMIT 1000 // лимит по току в миллиамперах, автоматически управляет яркостью (пожалей свой блок питания!) 0 - выключить лимит

#define WIDTH 16  // ширина матрицы
#define HEIGHT 16 // высота матрицы

#define COLOR_ORDER GRB // порядок цветов на ленте. Если цвет отображается некорректно - меняйте. Начать можно с RGB

#define MATRIX_TYPE 0      // тип матрицы: 0 - зигзаг, 1 - параллельная
#define CONNECTION_ANGLE 3 // угол подключения: 0 - левый нижний, 1 - левый верхний, 2 - правый верхний, 3 - правый нижний
#define STRIP_DIRECTION 1  // направление ленты из угла: 0 - вправо, 1 - вверх, 2 - влево, 3 - вниз
// при неправильной настройке матрицы вы получите предупреждение "Wrong matrix parameters! Set to default"
// шпаргалка по настройке матрицы здесь! https://alexgyver.ru/matrix_guide/

#define numHold_Time 1500 // время отображения индикатора уровня яркости/скорости/масштаба

// ============= ДЛЯ РАЗРАБОТЧИКОВ =============
#define LED_PIN 4 // пин ленты
#define BTN_PIN 7 // пин кнопки

#define ENCDR_CLK 6 // пины
#define ENCDR_DT 5  // энкодера

#define MODE_AMOUNT 18
#define NUM_LEDS WIDTH *HEIGHT
#define SEGMENTS 1 // диодов в одном "пикселе" (для создания матрицы из кусков ленты)
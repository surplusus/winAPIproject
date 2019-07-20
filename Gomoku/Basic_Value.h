#pragma once

const int BoardWidth = 700;
const int BoardHeight = 700;
const int BoardStartX = 30;
const int BoardStartY = 30;
const int BasicPxl = 30;
const int CirSize = 13;

enum TYPE_COL { NONE=0, BLACK, WHITE };
enum TYPE_EVENT {T_INIT = 0, T_RENDER, T_UPDATE, T_PUTSTONE};
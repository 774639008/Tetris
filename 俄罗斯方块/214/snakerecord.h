#ifndef _SNAKERECORD_H_
#define _SNAKERECORD_H_

#include "tetrisLogicModel.h"

int data_to_file(TetrisManager *manager);   //数据写入文件

char *read_char(char *filename);

#endif // _SNAKERECORD_H_

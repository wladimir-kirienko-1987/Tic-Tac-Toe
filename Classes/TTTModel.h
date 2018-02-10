#pragma once


#define BOARD_SIZE 3

//Тип клетки доски
typedef enum{
	_e=-1, //пусто
	_0=0,  //нолик
	_x=1,  //крестик
} tCell;

typedef enum{
	_0_win = 0, //победа ноликов
	_x_win = 1, //победа крестов
	_draw = 2,  //ничья
	_next = 3 //играем дальше
} tGameState;



class TTTModelExeption;

class TTTModel
{
	//Доска
	tCell Board[BOARD_SIZE][BOARD_SIZE];

public:
	TTTModel(void);
	//Сделать ход
	void Set(tCell CellType,int x,int y);
	//Проверить поле
	tCell Get(int x,int y);
	//Узнать состояние игры
	tGameState CheckState();

	~TTTModel(void);
};

typedef enum{
	Default=-1,
	EmptySet=0, //Ошибка: выбрано заполнение пустым
	BoardOvf=1,  //Ошибка: вышли за границы поля
	AlreadyFill=2,  //Ошибка: клетка уже заполнена
} tModelExeption;

class TTTModelExeption{
	tModelExeption ME;	
public:
	TTTModelExeption();
	void SetType(tModelExeption tME);
	tModelExeption GetType();
};

#include "TTTModel.h"

TTTModel::TTTModel(void)
{	
	//Очистка доски
	for (int i=0;i<BOARD_SIZE;i++)
		for (int j=0;j<BOARD_SIZE;j++)
			Board[i][j] = _e;
}

TTTModel::~TTTModel(void)
{

}

void TTTModel::Set(tCell CellType,int x,int y)
{
	TTTModelExeption e;
	//Ошибка: выбрано заполнение пустым
	if (CellType==_e){ 
		e.SetType(EmptySet); 
		throw e;
	}
	//Ошибка: вышли за границы поля
	if ( (x>2||x<0) || (y>2||y<0) ){
		e.SetType(BoardOvf);
		throw e;
	}
	//Ошибка: клетка уже заполнена
	if (Board[x][y] != _e){
		e.SetType(AlreadyFill);
		throw e;
	}
	//Выставляем клетку
	Board[x][y] = CellType;
}

tCell  TTTModel::Get(int x,int y)
{
	TTTModelExeption e;
	//Ошибка: вышли за границы поля
	if ( (x>2||x<0) && (y>2||y<0) ){
		e.SetType(BoardOvf);
		throw e;
	}

	return Board[x][y];
}

tGameState TTTModel::CheckState()
{
	tGameState GameState = _next;
	
	//Board[x][y] 
	
	//проверка линий
	for (int i=0;i<BOARD_SIZE;i++)
	{
		if (((Board[i][0] == Board[i][1]) && (Board[i][1] == Board[i][2])) && (Board[i][0] != _e))
		{
			if ((Board[i][0]) == _x) GameState = _x_win;
			else GameState = _0_win;
			break;
		}

		if (((Board[0][i] == Board[1][i]) && (Board[1][i] == Board[2][i])) && (Board[0][i] != _e))
		{
			if ((Board[0][i]) == _x) GameState = _x_win;
			else GameState = _0_win;
			break;
		}

	}	
	
	
	if ((GameState == _0_win) || (GameState == _x_win))
	{
		return GameState;
	}

	//проверка диагоналей
	if (((Board[0][0] == Board[1][1]) && (Board[1][1] == Board[2][2])) && (Board[0][0] != _e))
	{
			if ((Board[0][0]) == _x) GameState = _x_win;
			else GameState = _0_win;
	}
	
	if ((GameState == _0_win) || (GameState == _x_win))
	{
		return GameState;
	}

	if (((Board[2][0] == Board[1][1]) && (Board[1][1] == Board[0][2])) && (Board[2][0] != _e))
	{
			if ((Board[2][0]) == _x) GameState = _x_win;
			else GameState = _0_win;	
	}

	if ((GameState == _0_win) || (GameState == _x_win))
	{
		return GameState;
	}

	//Ничья если нет продолжения
	GameState = _draw;
	//Проверка на продолжение
	for (int i=0;i<BOARD_SIZE;i++)
		for (int j=0;j<BOARD_SIZE;j++)
			if (Board[i][j] == _e){ 
				GameState = _next;
				break;
			}

	return GameState;	
}



TTTModelExeption::TTTModelExeption():ME(Default)
{
}

void TTTModelExeption::SetType(tModelExeption tME)
{
	ME = tME;
}

tModelExeption TTTModelExeption::GetType()
{
	return ME;
}
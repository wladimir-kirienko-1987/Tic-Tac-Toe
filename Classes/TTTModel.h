#pragma once


#define BOARD_SIZE 3

//��� ������ �����
typedef enum{
	_e=-1, //�����
	_0=0,  //�����
	_x=1,  //�������
} tCell;

typedef enum{
	_0_win = 0, //������ �������
	_x_win = 1, //������ �������
	_draw = 2,  //�����
	_next = 3 //������ ������
} tGameState;



class TTTModelExeption;

class TTTModel
{
	//�����
	tCell Board[BOARD_SIZE][BOARD_SIZE];

public:
	TTTModel(void);
	//������� ���
	void Set(tCell CellType,int x,int y);
	//��������� ����
	tCell Get(int x,int y);
	//������ ��������� ����
	tGameState CheckState();

	~TTTModel(void);
};

typedef enum{
	Default=-1,
	EmptySet=0, //������: ������� ���������� ������
	BoardOvf=1,  //������: ����� �� ������� ����
	AlreadyFill=2,  //������: ������ ��� ���������
} tModelExeption;

class TTTModelExeption{
	tModelExeption ME;	
public:
	TTTModelExeption();
	void SetType(tModelExeption tME);
	tModelExeption GetType();
};
